#ifndef WINDOWS_TOTALPURCHASES_H_
#define WINDOWS_TOTALPURCHASES_H_


#include "../core/Initializer.h"
#include "Window.h"

class TotalPurchases : public Window {

private:
	int state;
	int fail;
public:
	TotalPurchases(int *p_a_d, Item ** i, int *n_i, Member **m,
			int *n_m, Trip **t, int n_d) : Window(p_a_d, i, n_i, m, n_m, t, n_d) {
		ID = TOTALPURCHASES;
		state = 0;
		fail = 0;
	}
	~TotalPurchases(){}
	void render_main(zr_window *window);
	void init() {
		state = 0;
		fail = 0;
	}
};

#endif /* WINDOWS_TOTALPURCHASES_H_ */
