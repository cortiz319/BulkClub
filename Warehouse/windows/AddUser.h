#ifndef WINDOWS_ADDUSER_H_
#define WINDOWS_ADDUSER_H_

#include "Window.h"

const int NAME = 0;
const int NUMBER = 1;
const int S_NAME = 2;
const int S_NUMBER = 3;
const int S_NUMBER_1 = 4;
const int S_NAME_1 = 5;
const int ITEM_NAME = 6;
const int ITEM_QUANTITY = 7;

class AddUser : public Window {
private:
	int state;
	int fail;
	int amount;
	zr_edit_box **eb;
	zr_char **edit_buffer;
	zr_size selected, selected_d, selected_m, selected_y;
	zr_state active, active_d, active_m, active_y;
	char **values;
	int *days, *months, *years;
	Member *temp;
public:
	AddUser(int *p_a_d, Item ** i, int *n_i, Member **m,
			int *n_m, Trip **t, int n_d) : Window(p_a_d, i, n_i, m, n_m, t, n_d) {
		amount = 10;
		eb = new zr_edit_box*[amount];
		edit_buffer = new zr_char*[amount];
		for (int i = 0; i < amount; i++) {
			eb[i] = new zr_edit_box;
			edit_buffer[i] = new zr_char[MAX_BUFFER];
			zr_edit_box_init_fixed(eb[i], edit_buffer[i], MAX_BUFFER, NULL, NULL);
		}
		ID = ADDUSER;
		state = 0;
		fail = 0;
		selected = 0;
		selected_d = 0;
		selected_m = 0;
		selected_y = 0;
		active = false;
		active_d = false;
		active_m = false;
		active_y = false;
		values = new char*[2];
		days = new int[31];
		months = new int[12];
		years = new int[2]; //expiration date must be in the future

		values[0] = "Regular";
		values[1] = "Executive";

		for (int i = 0; i < 31; i++) days[i] = i + 1;
		for (int i = 0; i < 12; i++) months[i] = i + 1;
		years[0] = 2016;
		years[1] = 2015;

		temp = NULL;
	}
	~AddUser() {}
	void render_main(zr_window *);
	void init() {
		state = 0;
		fail = 0;
		selected = 0;
		selected_d = 0;
		selected_m = 0;
		selected_y = 0;
		active = false;
		active_d = false;
		active_m = false;
		active_y = false;
		for (int i = 0; i < amount; i++) {
			zr_edit_box_clear(eb[i]);
		}

		temp = NULL;
	}
};

#endif /* WINDOWS_ADDUSER_H_ */
