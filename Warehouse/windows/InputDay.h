#ifndef WINDOWS_INPUTDAY_H_
#define WINDOWS_INPUTDAY_H_

#include "Window.h"

class InputDay : public Window {
private:
	zr_edit_box eb;
	zr_char edit_buffer[MAX_BUFFER];
public:
	InputDay(int *p_a_d, Item ** i, int *n_i, Member **m,
			int *n_m, Trip **t, int n_d) : Window(p_a_d, i, n_i, m, n_m, t, n_d) {
		ID = INPUTDAY;
		zr_edit_box_init_fixed(&eb, edit_buffer, MAX_BUFFER, NULL, NULL);
		//eb.filter = zr_input_filter(ZR_INPUT_DEC);
	}
	~InputDay() {}
	void render_main(zr_window *);
};

#endif /* WINDOWS_INPUTDAY_H_ */
