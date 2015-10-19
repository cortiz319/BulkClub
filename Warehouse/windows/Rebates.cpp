#include "Rebates.h"

void Rebates::render_main(zr_window *window){
	Executive* temp;
	zr_context context;
	zr_begin(&context, window);
	{
		zr_header(&context, "REBATES FOR MEMBERS", 0, 0, ZR_HEADER_LEFT);
		for(int i = 0; i < *num_members; i++)
		{
			if(members[i]->member_type == 1)
			{
				temp = static_cast<Executive*>(members[i]);
				zr_layout_row_dynamic(&context, 30, 2);
				zr_label(&context, ("Member Name: " + temp->name).c_str(), ZR_TEXT_LEFT);
				zr_label(&context, ("Rebate: $" + patch::to_string(temp->rebate_amount.dollars) + "." + ((temp->rebate_amount.cents > 9) ? patch::to_string(temp->rebate_amount.cents) : ("0" + patch::to_string(temp->rebate_amount.cents)))).c_str(), ZR_TEXT_LEFT);
				zr_layout_row_static(&context, 30, 240, 2);
			}
		}
		zr_layout_row_dynamic(&context, 30, 2);
		zr_layout_row_static(&context, 30, 240, 6);

		if (zr_button_text(&context, "Back", ZR_BUTTON_DEFAULT)) { changeWindow(MAIN);}
	}
	zr_end(&context, window);
}
