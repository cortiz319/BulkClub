#ifndef WINDOWS_ADDITEM_H_
#define WINDOWS_ADDITEM_H_

#include "Window.h"

const int ITEM = 0;
const int DOLLAR = 1;
const int CENTS = 2;
const int S_ITEM = 3;

class AddItem : public Window {
private:
	int state;
	int fail;
	int amount;
	zr_edit_box **eb;
	zr_char **edit_buffer;
public:
	AddItem(int *p_a_d, Item ** i, int *n_i, Member **m,
			int *n_m, Trip **t, int n_d) : Window(p_a_d, i, n_i, m, n_m, t, n_d) {
		ID = ADDITEM;
		state = 0;
		fail = 0;

		amount = 10;
		eb = new zr_edit_box*[amount];
		edit_buffer = new zr_char*[amount];
		for (int i = 0; i < amount; i++) {
			eb[i] = new zr_edit_box;
			edit_buffer[i] = new zr_char[MAX_BUFFER];
			zr_edit_box_init_fixed(eb[i], edit_buffer[i], MAX_BUFFER, NULL, NULL);
		}

	}
	~AddItem() {}
	void render_main(zr_window *);
	void init() {
		state = 0;
		fail = 0;
		for (int i = 0; i < amount; i++) {
			zr_edit_box_clear(eb[i]);
		}
	}
};

#endif /* WINDOWS_ADDITEM_H_ */
