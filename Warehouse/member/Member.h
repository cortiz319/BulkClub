#ifndef MEMBER_H_
#define MEMBER_H_

#define MAX_ITEMS 256

#include <string>
#include <iostream>
#include "../util/Date.h"
#include "../util/Price.h"
#include "../util/Item.h"

using namespace std;

typedef int Member_t;

const Member_t REGULAR = 0;
const Member_t EXECUTIVE = 1;

//DONT INITILIZE AN INSTANCE OF THIS CLASS
class Member {
public:
	string name; //Keep this this way. See res/Public_Variables_Manifesto
	int number, number_items_purchased;
	Price total_spent;
	Member_t member_type;
	Date expiration_date;
	Item *items_purchased;
	Member() { total_spent.cents = 0; total_spent.dollars = 0; items_purchased = NULL; number_items_purchased = 0; }
	virtual ~Member() { if (items_purchased != NULL) delete [] items_purchased; }
};

#endif /* MEMBER_H_ */
