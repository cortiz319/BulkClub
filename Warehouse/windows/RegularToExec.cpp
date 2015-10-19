#include "RegularToExec.h"

void RegularToExec::render_main(zr_window* window) {
	zr_context context;
	zr_begin(&context, window);
	{
		zr_header(&context, "Conversions", 0, 0, ZR_HEADER_LEFT);
		zr_layout_row_dynamic(&context, 30, 1);
		zr_label(&context, "The following members should convert from Regular to Executive:", ZR_TEXT_LEFT);
		for (int i = 0; i < *num_members; i++) {
			if (members[i]->member_type == REGULAR && (members[i]->total_spent.dollars * 3 / 100) > 55) {
				temp_r = static_cast<Regular *>(members[i]);
				zr_layout_row_static(&context, 30, 240, 3);
				zr_label(&context, string(" - " + temp_r->name + " (ID:" + patch::to_string(temp_r->number) + ")").c_str(), ZR_TEXT_LEFT);
				zr_label(&context, string("Spent: " + patch::to_string(temp_r->total_spent.dollars) + "." + ((temp_r->total_spent.cents > 9) ? patch::to_string(temp_r->total_spent.cents) : ("0" + patch::to_string(temp_r->total_spent.cents)))).c_str(), ZR_TEXT_LEFT);
				zr_label(&context, string("Potential rebate: " + patch::to_string(temp_r->potential_rebate_amount.dollars) + "." + ((temp_r->potential_rebate_amount.cents > 9) ? patch::to_string(temp_r->potential_rebate_amount.cents) : ("0" + patch::to_string(temp_r->potential_rebate_amount.cents)))).c_str(), ZR_TEXT_LEFT);
			}
		}
		zr_layout_row_static(&context, 30, 240, 6);
		if (zr_button_text(&context, "Back", ZR_BUTTON_DEFAULT)) {
			changeWindow(MAIN);
		}
	}
	zr_end(&context, window);
}
