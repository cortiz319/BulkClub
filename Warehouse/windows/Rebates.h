#ifndef WINDOWS_REBATES_H_
#define WINDOWS_REBATES_H_

#include "Window.h"
#include <cstring>

class Rebates : public Window {

private:
	int state;
	int fail;
public:
	Rebates(int *p_a_d, Item ** i, int *n_i, Member **m,
			int *n_m, Trip **t, int n_d) : Window(p_a_d, i, n_i, m, n_m, t, n_d) {
		ID = REBATES;
		state = 0;
		fail = 0;
	}
	~Rebates(){}
	void render_main(zr_window *window);
	void init() {
		state = 0;
		fail = 0;
	}
};

#endif /* WINDOWS_REBATES_H_ */
