#ifndef WINDOWS_INFOITEM_H_
#define WINDOWS_INFOITEM_H_

#include "Window.h"

class InfoItem : public Window {
private:
	int state;
	int fail;
	zr_edit_box eb;
	zr_char edit_buffer[MAX_BUFFER];
	Member *mem;
public:
	InfoItem(int *p_a_d, Item ** i, int *n_i, Member **m,
			int *n_m, Trip **t, int n_d) : Window(p_a_d, i, n_i, m, n_m, t, n_d) {
		ID = INFOITEM;
		zr_edit_box_init_fixed(&eb, edit_buffer, MAX_BUFFER, NULL, NULL);
		state = 0;
		fail  = 0;
		mem   = 0;
	}
	~InfoItem() {}
	void render_main(zr_window *);
	void init() {
		zr_edit_box_clear(&eb);
		fail = 0;
		state = 0;
	}
};

#endif /* WINDOWS_INFOITEM_H_ */
