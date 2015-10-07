#include "InputDay.h"

void InputDay::render_main(zr_window *window) {
	zr_context context;
	zr_begin(&context, window);
	{
		zr_header(&context, "Input", 0, 0, ZR_HEADER_LEFT);
		zr_layout_row_dynamic(&context, 30, 1);
		zr_label(&context, "Please input a number:", ZR_TEXT_LEFT);
		zr_layout_row_static(&context, 30, 240, 3);
		zr_editbox(&context, &eb);
	}
	zr_end(&context, window);
}

