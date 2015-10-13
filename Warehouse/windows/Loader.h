#ifndef WINDOWS_LOADER_H_
#define WINDOWS_LOADER_H_

#define MAX_BUFFER  64
#include <windows.h>
#include "../member/Executive.h"
#include "Window.h"
#include "../core/Initializer.h"

struct threadParams{
    void* param1;
    int param2;
    int param3;
    int param4;
    int *param5;
    Member **param6;
    Trip **param7;
    Item **param8;
    int *param9;
    int *param10;
};

struct param {
	void *member;
};

class Loader : public Window {
private:
	zr_edit_box eb;
	zr_char edit_buffer[MAX_BUFFER];
	int state;
	DWORD threadDescriptor;
public:
	Loader(int *p_a_d, Item ** i, int *n_i, Member **m,
			int n_m, Trip **t, int n_d) : Window(p_a_d, i, n_i, m, n_m, t, n_d) {
		ID = LOADER;
		state = 0;
		zr_edit_box_init_fixed(&eb, edit_buffer, MAX_BUFFER, NULL, NULL);
		threadDescriptor = 0;
	}
	~Loader() {}
	void render_main(zr_window *);
};

#endif /* WINDOWS_LOADER_H_ */
