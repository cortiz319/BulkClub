#include "MemberInfo.h"

void MemberInfo::render_main(zr_window *window) {
	zr_context context;
	zr_begin(&context, window);
	{
		if (state == 0) {
			zr_header(&context, "Search by", 0, 0, ZR_HEADER_LEFT);
			zr_layout_row_dynamic(&context, 30, 1);
			zr_label(&context, "This window allows you to search for a user and bring up their purchase history", ZR_TEXT_LEFT);
			zr_layout_row_dynamic(&context, 30, 1);
			zr_label(&context, "How would you like to search for the member?:", ZR_TEXT_LEFT);
			zr_layout_row_static(&context, 30, 240, 3);
			if (zr_button_text(&context, "Search by member number", ZR_BUTTON_DEFAULT)) {
				state = 1;
				fail = 0;
			}
			if (zr_button_text(&context, "Search by member name", ZR_BUTTON_DEFAULT)) {
				state = 2;
				fail = 0;
			}
			for (int i = 0; i < 10; i++)
			zr_layout_row_static(&context, 30, 240, 1);
			zr_layout_row_static(&context, 30, 240, 6);
			if (zr_button_text(&context, "Back", ZR_BUTTON_DEFAULT)) {
				changeWindow(MAIN);
			}
		} else if (state == 1) {
			zr_header(&context, "Search by member number", 0, 0, ZR_HEADER_LEFT);
			zr_layout_row_dynamic(&context, 30, 1);
			if (fail == 1) zr_label(&context, "Error! Could not read input number, please try again", ZR_TEXT_LEFT);
			if (fail == 2) zr_label(&context, "Error! Could not find member", ZR_TEXT_LEFT);
			zr_layout_row_dynamic(&context, 30, 1);
			zr_label(&context, "Please input a number:", ZR_TEXT_LEFT);
			zr_layout_row_static(&context, 30, 240, 3);
			zr_editbox(&context, &eb);
			zr_layout_row_dynamic(&context, 30, 6);
			if (zr_button_text(&context, "Submit", ZR_BUTTON_DEFAULT)) {
				int iterator = 0, mult = eb.glyphes - 1, ret = 0;
				char *arr = static_cast<char* >(eb.buffer.memory.ptr);
				while (iterator < eb.glyphes && arr[iterator] >= 48 && arr[iterator] <= 57) {
					ret += int(arr[iterator] - 48) * round(pow(10, mult));
					mult--;
					iterator++;
				}
				if (iterator >= eb.glyphes && eb.glyphes != 0) {
					iterator = 0;
					while (iterator < *num_members && members[iterator]->number != ret) iterator++;
					if (iterator >= *num_members) {
						fail = 2;
					} else {
						state = 3;
						fail = 0;
						curr = members[iterator];
					}
				} else {
					fail = 1;
				}
			}
			for (int i = 0; i < 9; i++)
			zr_layout_row_static(&context, 30, 240, 1);
			zr_layout_row_static(&context, 30, 240, 6);
			if (zr_button_text(&context, "Back", ZR_BUTTON_DEFAULT)) {
				state = 0;
				fail = 0;
			}
		} else if (state == 2) {
			zr_header(&context, "Search by member name", 0, 0, ZR_HEADER_LEFT);
			zr_layout_row_dynamic(&context, 30, 1);
			if (fail == 1) zr_label(&context, "Error! Empty field", ZR_TEXT_LEFT);
			if (fail == 2) zr_label(&context, "Error! Could not find member", ZR_TEXT_LEFT);
			zr_layout_row_dynamic(&context, 30, 1);
			zr_label(&context, "Please input a name:", ZR_TEXT_LEFT);
			zr_layout_row_static(&context, 30, 240, 3);
			zr_editbox(&context, &eb);
			zr_layout_row_dynamic(&context, 30, 6);
			if (zr_button_text(&context, "Submit", ZR_BUTTON_DEFAULT)) {
				if (eb.glyphes != 0) {
					int iterator = 0, iterator2 = 0;
					char *arr = static_cast<char* >(eb.buffer.memory.ptr);
					while (iterator < *num_members) {
						if (eb.glyphes != members[iterator]->name.size()) {
							iterator++;
							continue;
						}
						while (iterator2 < eb.glyphes && arr[iterator2] == members[iterator]->name[iterator2]) iterator2++;
						if (iterator2 >= eb.glyphes) break;
						iterator2 = 0;
						iterator++;
					}
					if (iterator >= *num_members) {
						fail = 2;
					} else {
						state = 3;
						fail = 0;
						curr = members[iterator];
					}
				} else {
					fail = 1;
				}
			}
			for (int i = 0; i < 9; i++)
			zr_layout_row_static(&context, 30, 240, 1);
			zr_layout_row_static(&context, 30, 240, 6);
			if (zr_button_text(&context, "Back", ZR_BUTTON_DEFAULT)) {
				state = 0;
				fail = 0;
			}
		} else if (state == 3) {
			zr_header(&context, "Member info", 0, 0, ZR_HEADER_LEFT);
			zr_layout_row_dynamic(&context, 30, 1);
			if (curr == NULL) { //should never happen but it's a pre-caution
				zr_label(&context, "Error! Something went wrong", ZR_TEXT_LEFT);
				for (int i = 0; i < 12; i++)
				zr_layout_row_static(&context, 30, 240, 1);
				zr_layout_row_static(&context, 30, 240, 6);
				if (zr_button_text(&context, "Back", ZR_BUTTON_DEFAULT)) {
					state = 0;
					fail = false;
				}
			} else {
				zr_label(&context, string("Here is the purchase history for " + curr->name + " (ID:" + patch::to_string(curr->number) + ")").c_str(), ZR_TEXT_LEFT);
				for (int i = 0; i < curr->number_items_purchased; i++) {
					zr_layout_row_dynamic(&context, 30, 3);
					zr_label(&context, string(" - " + curr->items_purchased[i].item_name).c_str(), ZR_TEXT_LEFT);
					zr_label(&context, string("Price: " + patch::to_string(curr->items_purchased[i].price.dollars) + "." + ((curr->items_purchased[i].price.cents > 9) ? patch::to_string(curr->items_purchased[i].price.cents) : ("0" + patch::to_string(curr->items_purchased[i].price.cents)))).c_str(), ZR_TEXT_LEFT);
					zr_label(&context, string("Quantity purchased: " + patch::to_string(curr->items_purchased[i].quantity_sold)).c_str(), ZR_TEXT_LEFT);
				}
				zr_layout_row_static(&context, 30, 240, 1);
				zr_layout_row_static(&context, 30, 240, 6);
				if (zr_button_text(&context, "Back", ZR_BUTTON_DEFAULT)) {
					state = 0;
					fail = false;
				}
			}
		}
	}
	zr_end(&context, window);
}

