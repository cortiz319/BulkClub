#ifndef ITEM_H_
#define ITEM_H_

#include <string>
#include "Price.h"

using namespace std;

struct Item {
	Price price;
	string item_name;
	int quantity_sold;
	bool deleted = false;
};

#endif /* ITEM_H_ */
