#include "ExecToRegular.h"

void ExecToRegular::render_main(zr_window* window) {
	zr_context context;
	zr_begin(&context, window);
	{
		zr_header(&context, "Conversions", 0, 0, ZR_HEADER_LEFT);
		zr_layout_row_dynamic(&context, 30, 1);
		zr_label(&context, "The following members should convert from Executive to Regular:", ZR_TEXT_LEFT);
		for (int i = 0; i < *num_members; i++) {
			if (members[i]->member_type == EXECUTIVE && (members[i]->total_spent.dollars * 3 / 100) < 55) {
				temp_e = static_cast<Executive *>(members[i]);
				zr_layout_row_static(&context, 30, 240, 3);
				zr_label(&context, string(" - " + temp_e->name + " (ID:" + patch::to_string(temp_e->number) + ")").c_str(), ZR_TEXT_LEFT);
				zr_label(&context, string("Spent: " + patch::to_string(temp_e->total_spent.dollars) + "." + ((temp_e->total_spent.cents > 9) ? patch::to_string(temp_e->total_spent.cents) : ("0" + patch::to_string(temp_e->total_spent.cents)))).c_str(), ZR_TEXT_LEFT);
				zr_label(&context, string("Rebate: " + patch::to_string(temp_e->rebate_amount.dollars) + "." + ((temp_e->rebate_amount.cents > 9) ? patch::to_string(temp_e->rebate_amount.cents) : ("0" + patch::to_string(temp_e->rebate_amount.cents)))).c_str(), ZR_TEXT_LEFT);
			}
		}
		zr_layout_row_static(&context, 30, 240, 6);
		if (zr_button_text(&context, "Back", ZR_BUTTON_DEFAULT)) {
			changeWindow(MAIN);
		}
	}
	zr_end(&context, window);
}
