#ifndef INITIALIZER_H_
#define INITIALIZER_H_

#include <sstream>
#include <string>
#include <math.h>
#include "../member/Member.h"
#include "../member/Executive.h"
#include "../member/Regular.h"
#include "../util/Item.h"
#include "../util/Trip.h"

//this is happening, cry about it
#define MAX_ITEMS 256
#define TAX_RATE 0.0875
#define REBATE_PERCENTAGE 0.03

using namespace std;

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

void Initialize_Everything(const int num_days, const int num_members, int &num_items, Member **members, Trip **trips, Item **items, const int *purchases_a_day) {
	//variable declaration
	ifstream infile("res/warehouse_shoppers.txt");
	ifstream **days;
	string line, name;
	int id, iterator, temp_d, temp_c, temp_v, temp_v2; //temporary dollar, temporary cents, temporary var+2
	Item *temp_i; //temporary item
	Member *temp_m; //temporary member
	Executive *temp_e; //temprary executive member

	//variable initialization
	days = new ifstream*[num_days];
	for (char i = 49; i < num_days + 49; i++) days[i - 49] = new ifstream(string("res/day" + string(1, i) + ".txt").c_str());
	iterator = 0;

	//getting data from res/warehouse_shoppers.txt and populating array members
	while (getline(infile, line)) {
		//name
		name = line;
		//ID
		getline(infile, line);
		id = atoi(static_cast<const char*>(line.c_str()));
		//Type
		getline(infile, line);
		if (line[0] == 'E') members[iterator] = new Executive();
		else members[iterator] = new Regular();
		members[iterator]->name = name;
		members[iterator]->number = id;
		members[iterator]->items_purchased = new Item[MAX_ITEMS];
		members[iterator]->number_items_purchased = 0;
		//date
		getline(infile, line);
		members[iterator]->expiration_date.month =
				atoi(static_cast<const char*>(line.substr(0, 2).c_str()));
		members[iterator]->expiration_date.day =
				atoi(static_cast<const char*>(line.substr(3, 2).c_str()));
		members[iterator]->expiration_date.year =
				atoi(static_cast<const char*>(line.substr(6, 4).c_str()));

		iterator++;
	}

	//getting data from day1-5.txt and populating arrays items and trips
	for (int i = 0; i < num_days; i++) {
		for (int k = 0; k < purchases_a_day[i]; k++) {
			getline(*days[i], line);
			//date
			//these are not real two dimensional arrays, don't be fooled
			trips[i][k].purchase_date.month =
					atoi(static_cast<const char*>(line.substr(0, 2).c_str()));
			trips[i][k].purchase_date.day =
					atoi(static_cast<const char*>(line.substr(3, 2).c_str()));
			trips[i][k].purchase_date.year =
					atoi(static_cast<const char*>(line.substr(6, 4).c_str()));
			//ID
			getline(*days[i], line);
			trips[i][k].id = atoi(static_cast<const char*>(line.c_str()));
			//name
			getline(*days[i], line);
			temp_i = search_for_item(line, items, num_items);
			if (temp_i != NULL) {
				trips[i][k].item = temp_i;
				//quantity
				getline(*days[i], line);
				trips[i][k].quantity = atoi(static_cast<const char*>(line.substr(line.find('.')+ 3).c_str()));
				temp_i->quantity_sold += trips[i][k].quantity;
			} else {
				items[num_items] = new Item();
				items[num_items]->quantity_sold = 0;
				items[num_items]->item_name = line;
				getline(*days[i], line);
				//price
				items[num_items]->price.dollars = atoi(static_cast<const char*>(line.substr(0, line.find('.')).c_str()));
				items[num_items]->price.cents = atoi(static_cast<const char*>(line.substr(line.find('.') + 1, 2).c_str()));
				trips[i][k].item = items[num_items];
				//quantity
				trips[i][k].quantity = atoi(static_cast<const char*>(line.substr(line.find('.')+ 3).c_str()));
				items[num_items]->quantity_sold += trips[i][k].quantity;
				num_items++;
			}
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
				}
			}
		}
	}
}


#endif /* INITIALIZER_H_ */
