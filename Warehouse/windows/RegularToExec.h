#ifndef WINDOWS_REGULARTOEXEC_H_
#define WINDOWS_REGULARTOEXEC_H_

#include "Window.h"

class RegularToExec : public Window {
private:
	Regular *temp_r;
public:
	RegularToExec(int *p_a_d, Item ** i, int *n_i, Member **m,
			int *n_m, Trip **t, int n_d) : Window(p_a_d, i, n_i, m, n_m, t, n_d) {
		ID = REGULARTOEXEC;
		temp_r = NULL;
	}
	~RegularToExec() {}
	void render_main(zr_window *);
	void init() {}
};

#endif /* WINDOWS_REGULARTOEXEC_H_ */
