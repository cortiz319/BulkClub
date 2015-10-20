#include "Initializer.h"

namespace patch { //this is for to_string
    template < typename T > std::string to_string( const T& n ) {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

Member* search_for_member(int ID, Member **members, int num) { //also consider making this more efficient as well
	int iterator = 0;
	while (iterator < num && members[iterator]->number != ID) { iterator++; }
	return (iterator >= num) ? NULL : members[iterator];
}

Item* search_for_item(string name, Item **is, int num) { //we should probably consider making this more efficient
	int iterator = 0;
	while (iterator < num && is[iterator]->item_name != name) { iterator++; }
	return (iterator >= num) ? NULL : is[iterator];
}

bool Initialize_Everything(const int num_days, int &num_members, int &num_items, Member **members, Trip **trips, Item **items, int *purchases_a_day, const char* directory, bool orig) {
	//variable declaration
	ifstream infile(string(string(directory) + "/warehouse_shoppers" + ((orig) ? "_orig" : "") + ".txt").c_str());
	if (!infile) return false;
	ifstream **days;
	string line, name;
	int id, temp_d, temp_c, temp_v, temp_v2; //temporary dollar, temporary cents, temporary var+2
	Item *temp_i; //temporary item
	Member *temp_m; //temporary member
	Executive *temp_e; //temprary executive member
	Regular *temp_r; //temprary executive member

	//variable initialization
	days = new ifstream*[num_days];
	for (int i = 0; i < num_days; i++) days[i] = NULL;
	for (char i = 49; i < num_days + 49; i++) {
		days[i - 49] = new ifstream(string(string(directory) + "/day" + string(1, i) + ((orig) ? "_orig" : "") + ".txt").c_str());
		if (!*days[i - 49]) {
			for (int i2 = 0; i2 < num_days; i2++) {
				if (days[i2] != NULL) delete days[i2];
			}
			delete days;
			return false;
		}
	}
	num_members = 0;

	//getting data from res/warehouse_shoppers.txt and populating array members
	while (getline(infile, line)) {
		//name
		name = line;
		//ID
		getline(infile, line);
		id = atoi(static_cast<const char*>(line.c_str()));
		//Type
		getline(infile, line);
		if (line[0] == 'E') members[num_members] = new Executive();
		else members[num_members] = new Regular();
		members[num_members]->name = name;
		members[num_members]->number = id;
		members[num_members]->items_purchased = new Item[MAX_ITEMS];
		members[num_members]->number_items_purchased = 0;
		//date
		getline(infile, line);
		members[num_members]->expiration_date.month =
				atoi(static_cast<const char*>(line.substr(0, 2).c_str()));
		members[num_members]->expiration_date.day =
				atoi(static_cast<const char*>(line.substr(3, 2).c_str()));
		members[num_members]->expiration_date.year =
				atoi(static_cast<const char*>(line.substr(6, 4).c_str()));

		num_members++;
	}

	//getting data from day1-5.txt and populating arrays items and trips
	for (int i = 0; i < num_days; i++) {
		while (getline(*days[i], line)) {
			//date
			//these are not real two dimensional arrays, don't be fooled
			trips[i][purchases_a_day[i]].purchase_date.month =
					atoi(static_cast<const char*>(line.substr(0, 2).c_str()));
			trips[i][purchases_a_day[i]].purchase_date.day =
					atoi(static_cast<const char*>(line.substr(3, 2).c_str()));
			trips[i][purchases_a_day[i]].purchase_date.year =
					atoi(static_cast<const char*>(line.substr(6, 4).c_str()));
			//ID
			getline(*days[i], line);
			trips[i][purchases_a_day[i]].id = atoi(static_cast<const char*>(line.c_str()));
			//name
			getline(*days[i], line);
			temp_i = search_for_item(line, items, num_items);
			if (temp_i != NULL) {
				trips[i][purchases_a_day[i]].item = new Item();
				trips[i][purchases_a_day[i]].item->item_name = temp_i->item_name;
				trips[i][purchases_a_day[i]].item->price = temp_i->price;

				//quantity
				getline(*days[i], line);
				trips[i][purchases_a_day[i]].quantity = atoi(static_cast<const char*>(line.substr(line.find('.')+ 3).c_str()));
				trips[i][purchases_a_day[i]].item->quantity_sold = trips[i][purchases_a_day[i]].quantity;
				temp_i->quantity_sold += trips[i][purchases_a_day[i]].quantity;
			} else {
				items[num_items] = new Item();
				items[num_items]->quantity_sold = 0;
				items[num_items]->item_name = line;
				getline(*days[i], line);
				//price
				items[num_items]->price.dollars = atoi(static_cast<const char*>(line.substr(0, line.find('.')).c_str()));
				items[num_items]->price.cents = atoi(static_cast<const char*>(line.substr(line.find('.') + 1, 2).c_str()));

				trips[i][purchases_a_day[i]].item = new Item();
				trips[i][purchases_a_day[i]].item->item_name = items[num_items]->item_name;
				trips[i][purchases_a_day[i]].item->price = items[num_items]->price;

				//quantity
				trips[i][purchases_a_day[i]].quantity = atoi(static_cast<const char*>(line.substr(line.find('.') + 3).c_str()));
				trips[i][purchases_a_day[i]].item->quantity_sold = trips[i][purchases_a_day[i]].quantity;
				items[num_items]->quantity_sold += trips[i][purchases_a_day[i]].quantity;
				num_items++;
			}
			purchases_a_day[i]++;
		}
	}
	//processing days 1-5
	for (int i = 0; i < num_days; i++) {
		for (int k = 0; k < purchases_a_day[i]; k++) {
			temp_m = search_for_member(trips[i][k].id, members, num_members);
			if (temp_m != NULL) {
				temp_m->items_purchased[temp_m->number_items_purchased].item_name = trips[i][k].item->item_name;
				temp_m->items_purchased[temp_m->number_items_purchased].price = trips[i][k].item->price;
				temp_m->items_purchased[temp_m->number_items_purchased].quantity_sold = trips[i][k].item->quantity_sold;

				temp_d = temp_m->items_purchased[temp_m->number_items_purchased].price.dollars * temp_m->items_purchased[temp_m->number_items_purchased].quantity_sold;
				temp_c = temp_m->items_purchased[temp_m->number_items_purchased].price.cents * temp_m->items_purchased[temp_m->number_items_purchased].quantity_sold;
				temp_m->number_items_purchased++;
				temp_d += (temp_c / 100); //if cents exceeds 100 then add to dollars
				temp_c -= 100 * (temp_c / 100); //if cents exceeds 100 then reset to 99

				temp_v = int(roundf((float(temp_d) * TAX_RATE) * 100.0) + roundf((float(temp_c) * TAX_RATE) * 100.0)); //sexy integer based rounding. few inefficient floats used
				temp_v2 = int(roundf((float(temp_d) * REBATE_PERCENTAGE) * 100.0) + roundf((float(temp_c) * REBATE_PERCENTAGE) * 100.0));
				temp_d += temp_v / 100;
				temp_c += temp_v - ((temp_v / 100) * 100);
				temp_d += (temp_c / 100); //if cents exceeds 100 then add to dollars
				temp_c -= 100 * (temp_c / 100); //if cents exceeds 100 then reset to 99

				temp_m->total_spent.dollars += temp_d;
				temp_m->total_spent.cents += temp_c;
				temp_m->total_spent.dollars += (temp_m->total_spent.cents / 100); //if cents exceeds 100 then add to dollars
				temp_m->total_spent.cents -= 100 * (temp_m->total_spent.cents / 100); //if cents exceeds 100 then reset to 99
				if (temp_m->member_type == EXECUTIVE) {
					temp_e = dynamic_cast<Executive *>(temp_m);
					if (temp_e != NULL) { //don't really need this check but just in case
						temp_e->rebate_amount.dollars += temp_v2 / 100;
						temp_e->rebate_amount.cents += temp_v2 - ((temp_v2 / 100) * 100);
						temp_e->rebate_amount.dollars += (temp_e->rebate_amount.cents / 100); //if cents exceeds 100 then add to dollars
						temp_e->rebate_amount.cents -= 100 * (temp_e->rebate_amount.cents / 100); //if cents exceeds 100 then reset to 99
					}
				} else {
					temp_r = dynamic_cast<Regular *>(temp_m);
					if (temp_r != NULL) { //don't really need this check but just in case
						temp_r->potential_rebate_amount.dollars += temp_v2 / 100;
						temp_r->potential_rebate_amount.cents += temp_v2 - ((temp_v2 / 100) * 100);
						temp_r->potential_rebate_amount.dollars += (temp_r->potential_rebate_amount.cents / 100); //if cents exceeds 100 then add to dollars
						temp_r->potential_rebate_amount.cents -= 100 * (temp_r->potential_rebate_amount.cents / 100); //if cents exceeds 100 then reset to 99
					}
				}
			}
		}
	}
	return true;
}

void WriteToFile(Member **members, int num_members, Trip **trips, int *purchases_a_day, const char* directory) {
	ofstream ofs(string(string(directory) + "/warehouse_shoppers.txt").c_str());
	for (int i = 0; i < num_members; i++) {
		ofs << members[i]->name << endl;
		ofs << members[i]->number << endl;
		ofs << ((members[i]->member_type == EXECUTIVE) ? "Executive" : "Regular") << endl;
		ofs << ((members[i]->expiration_date.month > 9) ? patch::to_string(members[i]->expiration_date.month) : ("0" + patch::to_string(members[i]->expiration_date.month))) << "/" << ((members[i]->expiration_date.day > 9) ? patch::to_string(members[i]->expiration_date.day) : ("0" + patch::to_string(members[i]->expiration_date.day))) << "/" << members[i]->expiration_date.year << endl;
	}
	ofs.close();

	for (int i = 0; i < 5; i++) {
		ofstream ofs(string(string(directory) + "/day" + patch::to_string(i + 1) + ".txt").c_str());
		for (int k = 0; k < purchases_a_day[i]; k++) {
			ofs << trips[i][k].purchase_date.month << "/" << ((trips[i][k].purchase_date.day > 9) ? patch::to_string(trips[i][k].purchase_date.day) : ("0" + patch::to_string(trips[i][k].purchase_date.day))) << "/" << trips[i][k].purchase_date.year << endl;
			ofs << trips[i][k].id << endl;
			ofs << trips[i][k].item->item_name << endl;
			ofs << trips[i][k].item->price.dollars << "." << ((trips[i][k].item->price.cents > 9) ? patch::to_string(trips[i][k].item->price.cents) : ("0" + patch::to_string(trips[i][k].item->price.cents))) << "\t" << trips[i][k].quantity << endl;
		}
		ofs.close();
	}
}

