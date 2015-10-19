#ifndef WINDOWS_MEMBERINFO_H_
#define WINDOWS_MEMBERINFO_H_

#include "Window.h"

class MemberInfo : public Window {
private:
	int state;
	int fail;
	zr_edit_box eb;
	zr_char edit_buffer[MAX_BUFFER];
	Member *curr;
public:
	MemberInfo(int *p_a_d, Item ** i, int *n_i, Member **m,
			int *n_m, Trip **t, int n_d) : Window(p_a_d, i, n_i, m, n_m, t, n_d) {
		ID = MEMBERINFO;
		state = 0;
		zr_edit_box_init_fixed(&eb, edit_buffer, MAX_BUFFER, NULL, NULL);
		fail = 0;
		curr = NULL;
	}
	~MemberInfo() {}
	void render_main(zr_window *);
	void init() {
		zr_edit_box_clear(&eb);
		fail = 0;
		state = 0;
	}
};

#endif /* WINDOWS_MEMBERINFO_H_ */
