#ifndef WINDOWS_SALESREPORT_H_
#define WINDOWS_SALESREPORT_H_

#include "../core/Initializer.h"
#include "Window.h"
#include <cstring>

class SalesReport : public Window {

private:
	char ** values;
	char ** days;
	zr_size selected, size, selected_days;
	zr_state active, active_d;
	char* dateToChar;
	int state;
	int fail;
public:
	SalesReport(int *p_a_d, Item ** i, int *n_i, Member **m,
			int *n_m, Trip **t, int n_d) : Window(p_a_d, i, n_i, m, n_m, t, n_d) {
		ID = SALESREPORT;
		state = 0;
		fail = 0;

		size = 3;
		values = new char*[size];
		days = new char*[num_days];
		selected = 0;
		selected_days = 0;
		active = false;
		active_d = false;

		// Just In Case
		for(int i = 0; i < num_days; i++) {
			days[i] = "Day";
		}

		values[0] = "Default";
		values[1] = "Regular";
		values[2] = "Executive";

	}
	~SalesReport(){
		delete [] days;
		delete [] dateToChar;
	}
	void render_main(zr_window *window);
	void init() {
		state = 0;
		fail = 0;
		selected = 0;
		selected_days = 0;
		active = false;
		active_d = false;
	}
};

#endif /* WINDOWS_SALESREPORT_H_ */
