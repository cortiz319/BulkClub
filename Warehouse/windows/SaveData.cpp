#include "SaveData.h"

void SaveData::render_main(zr_window *window) {
	zr_context context;
	zr_begin(&context, window);
	{
		zr_header(&context, "Save data", 0, 0, ZR_HEADER_LEFT);
		zr_layout_row_dynamic(&context, 30, 1);
		if (fail == 1) zr_label(&context, "Error! Could not load from specified directory", ZR_TEXT_LEFT);
		if (fail == 2) zr_label(&context, "Successfully loaded defaults", ZR_TEXT_LEFT); //not really a fail
		if (fail == 3) zr_label(&context, "Successfully wrote changes to disk", ZR_TEXT_LEFT); //not really a fail
		zr_layout_row_dynamic(&context, 30, 1);
		zr_label(&context, "Please input the directory where the core files lie:", ZR_TEXT_LEFT);
		zr_layout_row_static(&context, 30, 240, 3);
		zr_editbox(&context, &eb);
		zr_layout_row_static(&context, 30, 240, 3);
		if (zr_button_text(&context, "Save all changes", ZR_BUTTON_DEFAULT)) {
			WriteToFile(members, *num_members, trips, purchases_a_day, static_cast<char*>(eb.buffer.memory.ptr));
			fail = 3;
		}
		if (zr_button_text(&context, "Load defaults", ZR_BUTTON_DEFAULT)) {
			for (int i = 0; i < *num_members; i++) delete members[i];
			for (int i = 0; i < *num_items; i++) delete items[i];
			for (int i = 0; i < num_days; i++) delete [] trips[i];
			for (int i = 0; i < num_days; i++) trips[i] = new Trip[MAX_ITEMS];
			for (int i = 0; i < num_days; i++) purchases_a_day[i] = 0;
			*num_items = 0;
			*num_members = 0;
			bool out = Initialize_Everything(num_days, *num_members, *num_items, members,
					trips, items, purchases_a_day, static_cast<char*>(eb.buffer.memory.ptr), true);
			if (out) {
				fail = 2;
				WriteToFile(members, *num_members, trips, purchases_a_day, static_cast<char*>(eb.buffer.memory.ptr));
			} else fail = 1;
		}
		for (int i = 0; i < 9; i++)
		zr_layout_row_static(&context, 30, 240, 1);
		zr_layout_row_static(&context, 30, 240, 6);
		if (zr_button_text(&context, "Back", ZR_BUTTON_DEFAULT)) {
			changeWindow(MAIN);
		}
	}
	zr_end(&context, window);
}

void SaveData::init() {
	fail = 0;
	zr_edit_box_clear(&eb);
}
