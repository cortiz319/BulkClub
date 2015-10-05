#ifndef WINDOWS_WINDOW_H_
#define WINDOWS_WINDOW_H_

#include <iostream>
#include "../gui/zahnrad.h"

class Window {
public:
	int ID;
	Window() {}
	virtual ~Window() {}
	virtual void render_main(zr_window *) = 0;
};

#endif /* WINDOWS_WINDOW_H_ */
