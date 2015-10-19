#ifndef WINDOWS_SAVEDATA_H_
#define WINDOWS_SAVEDATA_H_

#include "../core/Initializer.h"
#include "Window.h"

class SaveData : public Window {
private:
	int state;
	int fail;
	zr_edit_box eb;
	zr_char edit_buffer[MAX_BUFFER];
public:
	SaveData(int *p_a_d, Item ** i, int *n_i, Member **m,
			int *n_m, Trip **t, int n_d) : Window(p_a_d, i, n_i, m, n_m, t, n_d) {
		ID = SAVEDATA;
		state = 0;
		fail = 0;
		zr_edit_box_init_fixed(&eb, edit_buffer, MAX_BUFFER, NULL, NULL);
	}
	~SaveData() {}
	void render_main(zr_window *);
	void init();
};

#endif /* WINDOWS_SAVEDATA_H_ */
