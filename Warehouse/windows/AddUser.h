#ifndef WINDOWS_ADDUSER_H_
#define WINDOWS_ADDUSER_H_

#include "Window.h"

class AddUser : public Window {
private:
	int state;
public:
	AddUser(int *p_a_d, Item ** i, int *n_i, Member **m,
			int *n_m, Trip **t, int n_d) : Window(p_a_d, i, n_i, m, n_m, t, n_d) {
		ID = ADDUSER;
		state = 0;
	}
	~AddUser() {}
	void render_main(zr_window *);
};

#endif /* WINDOWS_ADDUSER_H_ */
