#ifndef REGULAR_H_
#define REGULAR_H_

#include "Member.h"

class Regular : public Member {
public:
	Price potential_rebate_amount; //Keep this this way. See res/Public_Variables_Manifesto
	Regular() { potential_rebate_amount.cents = 0;  potential_rebate_amount.dollars = 0; member_type = REGULAR; }
	~Regular() {}
	Regular(const Regular &member) {
		expiration_date = member.expiration_date;
		name = member.name;
		items_purchased = new Item[MAX_ITEMS];
		number_items_purchased = member.number_items_purchased;
		if (member.number_items_purchased != 0) {
			for (int i = 0; i < member.number_items_purchased; i++)
				items_purchased[i] = member.items_purchased[i];
		}
		number_items_purchased = member.number_items_purchased;
		number = member.number;
		total_spent = member.total_spent;
		member_type = member.member_type;
		potential_rebate_amount = member.potential_rebate_amount;
	}
};

#endif /* REGULAR_H_ */
