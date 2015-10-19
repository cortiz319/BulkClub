#include "Member.h"
#include "Executive.h"
#include "Regular.h"

Member::Member(const Member &member) {
	expiration_date = member.expiration_date;
	name = member.name;
	if (member.number_items_purchased != 0) {
		items_purchased = new Item[member.number_items_purchased];
		for (int i = 0; i < member.number_items_purchased; i++)
			items_purchased[i] = member.items_purchased[i];
	} else {
		items_purchased = NULL;
		number_items_purchased = 0;
	}
	number_items_purchased = member.number_items_purchased;
	number = member.number;
	total_spent = member.total_spent;
	member_type = member.member_type;
	if (member.member_type == EXECUTIVE) {
		const Executive* temp_e = static_cast<const Executive*>(&member);
		Executive* curr = static_cast<Executive*>(this); // call me a boss
		curr->rebate_amount = temp_e->rebate_amount;
	} else {
		const Regular* temp_r = static_cast<const Regular*>(&member);
		Regular* curr = static_cast<Regular*>(this); // call me a boss
		curr->potential_rebate_amount = temp_r->potential_rebate_amount;
	}
}
