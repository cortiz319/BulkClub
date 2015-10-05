#include "Main.h"

void Main::render_main(zr_window *window) {
	struct zr_context context;
	zr_begin(&context, window);
	{
		zr_header(&context, "Main ", 0, 0, ZR_HEADER_LEFT);
		zr_layout_row_static(&context, 30, 80, 1);
		if (zr_button_text(&context, "button", ZR_BUTTON_DEFAULT)) {
			/* event handling */
		}
		zr_layout_row_dynamic(&context, 30, 2);
		if (zr_option(&context, "easy", option == EASY)) option = EASY;
		if (zr_option(&context, "hard", option == HARD)) option = HARD;
		zr_layout_row_dynamic(&context, 30, 1);
		zr_editbox(&context, &eb);
	}
	zr_end(&context, window);
}

