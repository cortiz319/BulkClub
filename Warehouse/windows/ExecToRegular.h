#ifndef WINDOWS_EXECTOREGULAR_H_
#define WINDOWS_EXECTOREGULAR_H_

#include "Window.h"

class ExecToRegular : public Window {
private:
	Executive *temp_e;
public:
	ExecToRegular(int *p_a_d, Item ** i, int *n_i, Member **m,
			int *n_m, Trip **t, int n_d) : Window(p_a_d, i, n_i, m, n_m, t, n_d) {
		ID = EXECTOREGULAR;
		temp_e = NULL;
	}
	~ExecToRegular() {}
	void render_main(zr_window *);
	void init() {}
};

#endif /* WINDOWS_EXECTOREGULAR_H_ */
