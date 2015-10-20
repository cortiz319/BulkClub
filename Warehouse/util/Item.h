#ifndef ITEM_H_
#define ITEM_H_

#include <string>
#include "Price.h"

using namespace std;

struct Item {
	Item() { deleted = false; }
	Price price;
	string item_name;
	int quantity_sold;
	bool deleted;
};

#endif /* ITEM_H_ */
