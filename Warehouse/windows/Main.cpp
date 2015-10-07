#include "Main.h"

//not to be confused with main.cpp!

void Main::render_main(zr_window *window) {
	zr_context context;
	zr_begin(&context, window);
	{
		zr_header(&context, "Main", 0, 0, ZR_HEADER_LEFT);
		zr_layout_row_dynamic(&context, 30, 1);
		zr_label(&context, "Please select an option:", ZR_TEXT_LEFT);
		zr_layout_row_static(&context, 30, 240, 3);
		if (zr_button_text(&context, "1. Sales Report", ZR_BUTTON_DEFAULT)) {
			changeWindow(2);
		}
		if (zr_button_text(&context, "2. Total purchases", ZR_BUTTON_DEFAULT)) {
			/* event handling */
		}
		if (zr_button_text(&context, "3. Quantity sold", ZR_BUTTON_DEFAULT)) {
			/* event handling */
		}
		zr_layout_row_static(&context, 30, 240, 3);
		if (zr_button_text(&context, "4. Rebate of Members", ZR_BUTTON_DEFAULT)) {
			/* event handling */
		}
		if (zr_button_text(&context, "5. Membership expirations", ZR_BUTTON_DEFAULT)) {
			/* event handling */
		}
		if (zr_button_text(&context, "6. Add a Member", ZR_BUTTON_DEFAULT)) {
			/* event handling */
		}
		zr_layout_row_static(&context, 30, 240, 3);
		if (zr_button_text(&context, "7. Add an item", ZR_BUTTON_DEFAULT)) {
			/* event handling */
		}
		if (zr_button_text(&context, "8. Get info on item", ZR_BUTTON_DEFAULT)) {
			/* event handling */
		}
		if (zr_button_text(&context, "9. Get info on member", ZR_BUTTON_DEFAULT)) {
			/* event handling */
		}
		zr_layout_row_static(&context, 30, 240, 3);
		if (zr_button_text(&context, "10. Should convert to executive", ZR_BUTTON_DEFAULT)) {
			/* event handling */
		}
		if (zr_button_text(&context, "11. Should convert to regular", ZR_BUTTON_DEFAULT)) {
			/* event handling */
		}
		if (zr_button_text(&context, "12. Save changes", ZR_BUTTON_DEFAULT)) {
			/* event handling */
		}
	}
	zr_end(&context, window);
}
