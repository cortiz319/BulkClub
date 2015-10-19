#ifndef WINDOWS_MEMBEREXPIRATION_H_
#define WINDOWS_MEMBEREXPIRATION_H_

#include "Window.h"

class MemberExpiration : public Window {

private:
	int * months;
	zr_size selected, size;
	zr_state active;
	int state;
	int fail;
public:
	MemberExpiration(int *p_a_d, Item ** i, int *n_i, Member **m,
			int *n_m, Trip **t, int n_d) : Window(p_a_d, i, n_i, m, n_m, t, n_d) {
		ID = EXPIRE;
		state = 0;
		fail = 0;
		size = 12;
		selected = 0;
		active = false;
		months = new int[size];

		for(int i = 0; i < size; i++) {
			months[i] = i+1;
		}
	}
	~MemberExpiration(){}
	void render_main(zr_window *window);
	void init() {
		state = 0;
		fail = 0;
		selected = 0;
		active = false;
	}
};




#endif /* WINDOWS_MEMBEREXPIRATION_H_ */
