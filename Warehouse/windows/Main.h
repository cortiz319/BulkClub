#ifndef WINDOWS_MAIN_H_
#define WINDOWS_MAIN_H_

#include "Window.h"

class Main : public Window {
private:
public:
	Main(int *p_a_d, Item ** i, int *n_i, Member **m,
			int *n_m, Trip **t, int n_d) : Window(p_a_d, i, n_i, m, n_m, t, n_d) {
		ID = MAIN;
	}
	~Main() {}
	void render_main(zr_window *);
	void init() {}
};

#endif /* WINDOWS_MAIN_H_ */
