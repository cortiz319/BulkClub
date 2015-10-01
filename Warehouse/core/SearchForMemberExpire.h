/*
 * SearchForMemberExpire.h
 *
 *  Created on: Oct 1, 2015
 *      Author: Johnathan
 */

#ifndef CORE_SEARCHFORMEMBEREXPIRE_H_
#define CORE_SEARCHFORMEMBEREXPIRE_H_

#include "../member/Member.h"
#include <math.h>
#include <limits>
#include <iostream>
using namespace std;

int GetAndCheckInput(const int UPPER_LIMIT, const int LOWER_LIMIT, string prompt)
{
	int menuOption;
	bool invalid;		//CALC - T/F for invalid input

	//PROCESSING - DO-WHILE LOOP - Used to output the the menu, prompt the
	//			   user for a selection and error check input.
	do
	{
		//CALC - Initialized invalid to false
		invalid = false;

		cout << "\n" << prompt;

		//INPUT - Prompts the user for their selection
		//PROCESSING - IF-THEN-ELSIF STATEMENT - Used to error check the
		//			   input and and output error messages if a non-integer
		//			   digit is entered or if the selection is outside of
		//			   the allowed range
		if (!(cin >> menuOption))
		{
			cout << endl;
			cout << "**** Please input a number between " << LOWER_LIMIT
				<< " and " << UPPER_LIMIT << " ****"
				<< endl << endl;

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			invalid = true;
		}
		else if (menuOption < LOWER_LIMIT || menuOption > UPPER_LIMIT)
		{
			cout << endl << "**** The number " << menuOption << " is an "
				<< "invalid entry.     ****" << endl
				<< "**** Please input a number between " << LOWER_LIMIT
				<< " and " << UPPER_LIMIT << " ****" << endl << endl;
			invalid = true;
		}
	} while (invalid);

	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	return menuOption;
}

void search_for_expiration(Member **members)
{
	int month;
	int index;
	month = GetAndCheckInput(12, 1, "Enter A Month To Search: ");

	for (index = 0; index < 12; index++)
	{
		if (month == members[index]->expiration_date.month)
		{
			cout << "\n" << members[index]->name;
			if(members[index]->member_type == 1)
			{
				cout << "\nRenewal Fee: $110.00\n";
			}
			else
			{
				cout << "\nRenewal Fee: $55.00\n";
			}
		}
	}
cout << endl;
}


#endif /* CORE_SEARCHFORMEMBEREXPIRE_H_ */
