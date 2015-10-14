#include "AddUser.h"

void AddUser::render_main(zr_window* window) {
	zr_context context;
	zr_begin(&context, window);
	{
		if (state == 0) {
			zr_header(&context, "Add/Delete Users", 0, 0, ZR_HEADER_LEFT);
			zr_layout_row_dynamic(&context, 30, 1);
			zr_label(&context, "Please select an action:", ZR_TEXT_LEFT);

			zr_layout_row_static(&context, 30, 240, 3);
			if (zr_button_text(&context, "Add User", ZR_BUTTON_DEFAULT)) {
				state = 1;
			}
			if (zr_button_text(&context, "Delete User", ZR_BUTTON_DEFAULT)) {
				state = 2;
			}
			for (int i = 0; i < 11; i++)
			zr_layout_row_static(&context, 30, 240, 1);
			zr_layout_row_static(&context, 30, 240, 6);
			if (zr_button_text(&context, "Back", ZR_BUTTON_DEFAULT)) {
				changeWindow(MAIN);
			}
		} else if (state == 1) {
			zr_header(&context, "Add User", 0, 0, ZR_HEADER_LEFT);
			zr_layout_row_dynamic(&context, 30, 1);
			zr_label(&context, "Please input the necessary data to create a user:", ZR_TEXT_LEFT);
		} else if (state == 2) {
			zr_header(&context, "Delete User", 0, 0, ZR_HEADER_LEFT);
			zr_layout_row_dynamic(&context, 30, 1);
			zr_label(&context, "The following members should convert from Executive to Regular:", ZR_TEXT_LEFT);

		}
	}
	zr_end(&context, window);
}


