/*
 * No documenting here :)
 */

#ifndef CORE_SALESREPORT_H_
#define CORE_SALESREPORT_H_

#include "../member/Member.h"
#include "../core/Initializer.h"

#include<iomanip>

void SalesReport(int day, Member **members, int num)
{
	const int SALES_REPORT = 30;
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
