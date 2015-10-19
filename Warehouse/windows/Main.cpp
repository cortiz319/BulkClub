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
			changeWindow(SALESREPORT);
		}
		if (zr_button_text(&context, "2. Total purchases", ZR_BUTTON_DEFAULT)) {
			changeWindow(TOTALPURCHASES);
		}
		if (zr_button_text(&context, "3. Quantity sold", ZR_BUTTON_DEFAULT)) {
			changeWindow(INFOQUANTITY);
		}
		zr_layout_row_static(&context, 30, 240, 3);
		if (zr_button_text(&context, "4. Rebate of Members", ZR_BUTTON_DEFAULT)) {
			changeWindow(REBATES);
		}
		if (zr_button_text(&context, "5. Membership expirations", ZR_BUTTON_DEFAULT)) {
			changeWindow(EXPIRE);
		}
		if (zr_button_text(&context, "6. Modify members", ZR_BUTTON_DEFAULT)) {
			changeWindow(ADDUSER);
		}
		zr_layout_row_static(&context, 30, 240, 3);
		if (zr_button_text(&context, "7. Add an item", ZR_BUTTON_DEFAULT)) {
			changeWindow(ADDITEM);
		}
		if (zr_button_text(&context, "8. Get info on item", ZR_BUTTON_DEFAULT)) {
			changeWindow(INFOITEM);
		}
		if (zr_button_text(&context, "9. Get info on member", ZR_BUTTON_DEFAULT)) {
			changeWindow(MEMBERINFO);
		}
		zr_layout_row_static(&context, 30, 240, 3);
		if (zr_button_text(&context, "10. Should convert to executive", ZR_BUTTON_DEFAULT)) {
			changeWindow(REGULARTOEXEC);
		}
		if (zr_button_text(&context, "11. Should convert to regular", ZR_BUTTON_DEFAULT)) {
			changeWindow(EXECTOREGULAR);
		}
		if (zr_button_text(&context, "12. Save changes", ZR_BUTTON_DEFAULT)) {
			changeWindow(SAVEDATA);
		}

		for (int i = 0; i < 8; i++)
		zr_layout_row_static(&context, 30, 240, 1);
		zr_layout_row_static(&context, 30, 240, 6);
		if (zr_button_text(&context, "Exit", ZR_BUTTON_DEFAULT)) {
			exit();
		}
	}
	zr_end(&context, window);
}
