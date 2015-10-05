#ifndef WINDOWS_MAIN_H_
#define WINDOWS_MAIN_H_

#define MAX_BUFFER  64
#include "Window.h"

class Main : public Window {
private:
	zr_edit_box eb;
	zr_char edit_buffer[MAX_BUFFER];
	enum {EASY, HARD};
	zr_size option;
	zr_float value;
public:
	Main() {
		ID = 0;
		zr_edit_box_init_fixed(&eb, edit_buffer, MAX_BUFFER, NULL, NULL);
		option = EASY;
		value = 0.6f;
	}
	~Main() {}
	void render_main(zr_window *);
};

#endif /* WINDOWS_MAIN_H_ */
