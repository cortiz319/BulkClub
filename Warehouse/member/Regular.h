#ifndef REGULAR_H_
#define REGULAR_H_

#include "Member.h"

class Regular : public Member {
public:
	Price potential_rebate_amount; //Keep this this way. See res/Public_Variables_Manifesto
	Regular() { potential_rebate_amount.cents = 0;  potential_rebate_amount.dollars = 0; member_type = REGULAR; }
	~Regular() {}
};

#endif /* REGULAR_H_ */
