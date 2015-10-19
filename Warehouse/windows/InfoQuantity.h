#ifndef WINDOWS_INFOQUANTITY_H_
#define WINDOWS_INFOQUANTITY_H_

#include "../core/Initializer.h"
#include "Window.h"

class InfoQuantity : public Window {

private:
	int state;
	int fail;
public:
	InfoQuantity(int *p_a_d, Item ** i, int *n_i, Member **m,
			int *n_m, Trip **t, int n_d) : Window(p_a_d, i, n_i, m, n_m, t, n_d) {
		ID = INFOQUANTITY;
		state = 0;
		fail = 0;
	}
	~InfoQuantity(){}
	void render_main(zr_window *window);
	void init() {
		state = 0;
		fail = 0;
	}
};





#endif /* WINDOWS_INFOQUANTITY_H_ */
