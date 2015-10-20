#ifndef EXECUTIVE_H_
#define EXECUTIVE_H_

#include "Member.h"

class Executive : public Member {
public:
	Price rebate_amount; //Keep this this way. See res/Public_Variables_Manifesto
	Executive() { rebate_amount.cents = 0;  rebate_amount.dollars = 0; member_type = EXECUTIVE; }
	~Executive() {}
	Executive(const Executive &member) {
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
		rebate_amount = member.rebate_amount;
	}
};

#endif /* EXECUTIVE_H_ */
