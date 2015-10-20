#include "MemberExpiration.h"

void MemberExpiration::render_main(zr_window *window)
{

	zr_context context;
	zr_context layout;
	zr_begin(&context, window);
	{
		zr_header(&context, "Get member expiration", 0, 0, ZR_HEADER_LEFT);
		zr_layout_row_dynamic(&context, 30, 1);
		zr_label(&context, "Please select a month:", ZR_TEXT_LEFT);

		zr_label(&context, "Months:", ZR_TEXT_LEFT);
		zr_layout_row_dynamic(&context, 30, 3);
		zr_combo_begin(&context, &layout, patch::to_string(months[selected]).c_str(), &active);
		{
			zr_layout_row_dynamic(&layout, 25, 3);
			for (int i = 0; i < size; ++i) {
				if (selected == i) continue;
				if (zr_combo_item(&layout, ZR_TEXT_LEFT, patch::to_string(months[i]).c_str())) {
					selected = i;
				}
			}
		}
		zr_combo_end(&context, &layout, &active);

		for(int i = 0; i < *num_members; i++)
		{
			if(members[i]->expiration_date.month == (selected + 1))
			{
				zr_layout_row_dynamic(&context, 30, 2);
				zr_label(&context, ("Member Name: " + members[i]->name).c_str(), ZR_TEXT_LEFT);
				if(members[i]->member_type == 1)
					zr_label(&context, "Renewal Cost: $111.00", ZR_TEXT_LEFT);
				else
					zr_label(&context, "Renewal Cost: $55.00", ZR_TEXT_LEFT);
			}
		}

		zr_layout_row_static(&context, 30, 240, 6);
		if (zr_button_text(&context, "Back", ZR_BUTTON_DEFAULT)) { changeWindow(MAIN);}

	}
	zr_end(&context, window);
}
