/*
 * No documenting here :)
 */

#ifndef CORE_SALESREPORT_H_
#define CORE_SALESREPORT_H_

#include "../member/Member.h"
#include "../core/Initializer.h"

#include<iomanip>

const int SALES_REPORT = 30;

void SearchItem(string itemName, Item **is, int num)
{
	/*
	 * I had code to output the dates of the item sold but took it out.
	 * Not entirely sure if it made sense given the specs.
	 */
	Item* searchItem;
	searchItem = search_for_item(itemName, is, num );

	cout << "ITEM: ";
	if(searchItem != NULL)
		cout << itemName << " quantity sold: " << searchItem->quantity_sold;
	else
		cout << itemName << " was not found.";
	cout << endl << endl;
}

void Report(Member **members)
{
	Member* membersList[num_members];
	Member* temp;
	bool    purchase;
	int     numItems = 0;
	int     grandTotal = 0;

    int i, j;

	for(int i = 0; i < num_members; i++)
		membersList[i] = members[i];


    for (i = 1; i < num_members; i++) {
          j = i;
          while (j > 0 && membersList[j-1]->number > membersList[j]->number) {
                temp = membersList[j];
                membersList[j] = membersList[j - 1];
                membersList[j - 1] = temp;
                j--;
          }
    }

    for(int i = 0; i < num_members; i++)
	{
    	numItems = 0;
    	purchase = false;
    	cout << left;
    	cout << setw(SALES_REPORT) << "NAME:" << "MEMBER ID\n";
		cout << setw(SALES_REPORT) << membersList[i]->name
			 << membersList[i]->number << endl << endl;
		cout << "   ";
		cout << setw(SALES_REPORT-3) << "ITEM(S)" << "QUANTITY\n";
		for(int k = 0; k < num_days; k++)
		{
			for(int j = 0; j < purchases_a_day[k]; j++)
			{
				if(membersList[i]->number == trips[k][j].id)
				{
					purchase = true;
					cout << "   ";
					cout << setw(SALES_REPORT-3) << trips[k][j].item->item_name;;
					cout << trips[k][j].item->quantity_sold << endl;
					numItems += trips[k][j].item->quantity_sold;
				}
			}
		}

		// Used this to check if any member has not purchased an item.
		// Testing revealed two have not purchased anything.
		if(!purchase)
			cout << "\n*** Has not purchases any item! ***\n";
		else
			cout << "\n   " << setw(SALES_REPORT-3) << "TOTAL PURCHASES:" << numItems;

		grandTotal += numItems;
		cout << endl;
	}

    cout << "*****************************************************\n";
    cout << "Grand TOTAL ITEMS PURCHASED: " << grandTotal << endl;
    cout << "*****************************************************\n\n";

    cout << right;

}

void SalesReport(int day, Member **members, int num)
{
	Member* searchMem;
	int numExec = 0;
	int numReg = 0;
	float revenue = 0;
	int j;
	Member* compare;
	bool found = false;

	cout << setw(SALES_REPORT) << "ITEMS" << "QUANTITY\n";
	for(int i =0; i < purchases_a_day[day-1]; i++)
	{
		cout << setw(SALES_REPORT) << trips[day-1][i].item->item_name
			 <<  trips[day-1][i].item->quantity_sold <<endl;

		revenue += (trips[day-1][i].item->price.dollars * trips[day-1][i].item->price.cents/100.0) * trips[day-1][i].item->quantity_sold;
	}

	cout << "\nMEMBERS\n";
	for(int i =0; i < purchases_a_day[day-1]; i++)
	{
		j = i+1;
		searchMem = search_for_member(trips[day-1][i].id, members, num);
		found = false;

		while(j < purchases_a_day[day-1] && !found)
		{
			compare = search_for_member(trips[day-1][j].id, members, num);

			if(searchMem->name == compare->name)
				found = true;

			j++;
		}

		if(!found)
		{
			cout << searchMem->name << endl;
			(searchMem->member_type ==1? numExec++: numReg++);
		}
	}
	cout << endl;

	cout << setw(SALES_REPORT) << "Number of EXECUTIVE members : " << numExec << endl;
	cout << setw(SALES_REPORT) << "Number of REGULAR members   : "   << numReg << endl;

	cout << fixed << setprecision(2);
	cout << "\nRevenue for day " << day << " is: $" << revenue << endl << endl;

	cout << right;
}

#endif /* CORE_SALESREPORT_H_ */
