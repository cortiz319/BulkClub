#include "AddUser.h"

void AddUser::render_main(zr_window* window) {
	zr_context context;
	zr_context layout;
	zr_begin(&context, window);
	{
		if (state == 0) {
			zr_header(&context, "Modify Users", 0, 0, ZR_HEADER_LEFT);
			zr_layout_row_dynamic(&context, 30, 1);
			zr_label(&context, "Please select an action:", ZR_TEXT_LEFT);

			zr_layout_row_static(&context, 30, 240, 3);
			if (zr_button_text(&context, "Add User", ZR_BUTTON_DEFAULT)) {
				state = 1;
				fail = 0;
			}
			if (zr_button_text(&context, "Delete User", ZR_BUTTON_DEFAULT)) {
				state = 2;
				fail = 0;
			}
			if (zr_button_text(&context, "Add purchase to user", ZR_BUTTON_DEFAULT)) {
				state = 3;
				fail = 0;
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
			if (fail == 1) zr_label(&context, "Error! Name is empty", ZR_TEXT_LEFT);
			if (fail == 2) zr_label(&context, "Error! ID number is invalid (is it empty? does it contain regular characters?)", ZR_TEXT_LEFT);
			if (fail == 3) zr_label(&context, "Error! ID number already exists", ZR_TEXT_LEFT);
			if (fail == 4) zr_label(&context, "Created member successfully!", ZR_TEXT_LEFT); //not really a fail
			zr_layout_row_dynamic(&context, 30, 1);
			zr_label(&context, "Please input the necessary data to create a user:", ZR_TEXT_LEFT);
			zr_layout_row_static(&context, 30, 240, 3);
			zr_label(&context, "Name:", ZR_TEXT_LEFT);
			zr_editbox(&context, eb[NAME]);
			zr_layout_row_static(&context, 30, 240, 3);
			zr_label(&context, "ID number:", ZR_TEXT_LEFT);
			zr_editbox(&context, eb[NUMBER]);
			zr_layout_row_static(&context, 30, 240, 3);
			zr_label(&context, "Membership type:", ZR_TEXT_LEFT);
			zr_combo_begin(&context, &layout, values[selected], &active);
			{
				zr_layout_row_dynamic(&layout, 25, 1);
				for (int i = 0; i < 2; ++i) {
					if (selected == i) continue;
					if (zr_combo_item(&layout, ZR_TEXT_LEFT, values[i])) {
						selected = i;
					}
				}
			}
			zr_combo_end(&context, &layout, &active);
			zr_layout_row_static(&context, 30, 100, 6);
			zr_label(&context, "Expiration date:", ZR_TEXT_LEFT);
			zr_combo_begin(&context, &layout, patch::to_string(months[selected_m]).c_str(), &active_m);
			{
				zr_layout_row_dynamic(&layout, 25, 1);
				for (int i = 0; i < 12; ++i) {
					if (selected_m == i) continue;
					if (zr_combo_item(&layout, ZR_TEXT_LEFT, patch::to_string(months[i]).c_str())) {
						selected_m = i;
					}
				}
			}
			zr_combo_end(&context, &layout, &active_m);
			zr_label(&context, "/", ZR_TEXT_LEFT);
			zr_combo_begin(&context, &layout, patch::to_string(days[selected_d]).c_str(), &active_d);
			{
				zr_layout_row_dynamic(&layout, 25, 1);
				for (int i = 0; i < 31; ++i) {
					if (selected_d == i) continue;
					if (zr_combo_item(&layout, ZR_TEXT_LEFT, patch::to_string(days[i]).c_str())) {
						selected_d = i;
					}
				}
			}
			zr_combo_end(&context, &layout, &active_d);
			zr_label(&context, "/", ZR_TEXT_LEFT);
			zr_combo_begin(&context, &layout, patch::to_string(years[selected_y]).c_str(), &active_y);
			{
				zr_layout_row_dynamic(&layout, 25, 1);
				for (int i = 0; i < 2; ++i) {
					if (selected_y == i) continue;
					if (zr_combo_item(&layout, ZR_TEXT_LEFT, patch::to_string(years[i]).c_str())) {
						selected_y = i;
					}
				}
			}
			zr_combo_end(&context, &layout, &active_y);
			zr_layout_row_static(&context, 30, 240, 3);
			zr_label(&context, "(Hint! Expiration date must be in future)", ZR_TEXT_LEFT);
			for (int i = 0; i < 6; i++)
			zr_layout_row_static(&context, 30, 240, 1);
			zr_layout_row_static(&context, 30, 240, 6);
			if (zr_button_text(&context, "Submit", ZR_BUTTON_DEFAULT)) {
				if (eb[NAME]->glyphes == 0) fail = 1;
				else if (eb[NUMBER]->glyphes == 0) fail = 2;
				else {
					int iterator = 0, mult = eb[NUMBER]->glyphes - 1, ret = 0;
					char *arr = static_cast<char* >(eb[NUMBER]->buffer.memory.ptr);
					while (iterator < eb[NUMBER]->glyphes && arr[iterator] >= 48 && arr[iterator] <= 57) {
						ret += int(arr[iterator] - 48) * round(pow(10, mult));
						mult--;
						iterator++;
					}
					if (iterator >= eb[NUMBER]->glyphes) {
						iterator = 0;
						while (iterator < *num_members && members[iterator]->number != ret) iterator++;
						if (iterator >= *num_members) {
							fail = 4;
							Member** temp = members;
							*num_members += 1;
							Member** temp2 = new Member*[*num_members];
							for (int i = 0; i < *num_members - 1; i++) temp2[i] = new Member(*temp[i]);
							if (selected == 0) temp2[*num_members - 1] = new Regular();
							else temp2[*num_members - 1] = new Executive();
							temp2[*num_members - 1]->name = string(static_cast<char *>(eb[NAME]->buffer.memory.ptr));
							temp2[*num_members - 1]->number = ret;
							temp2[*num_members - 1]->expiration_date.day = days[selected_d];
							temp2[*num_members - 1]->expiration_date.month = months[selected_m];
							temp2[*num_members - 1]->expiration_date.year = years[selected_y];
							members = temp2;
							for (int i = 0; i < *num_members - 1; i++) delete temp[i];
							delete [] temp;
							issue_update(); //super important!
						} else {
							fail = 3;
						}
					} else {
						fail = 2;
					}
				}
			}
			if (zr_button_text(&context, "Back", ZR_BUTTON_DEFAULT)) {
				state = 0;
				fail = 0;
			}
		} else if (state == 2) {
			zr_header(&context, "Delete User", 0, 0, ZR_HEADER_LEFT);
			zr_layout_row_dynamic(&context, 30, 1);
			zr_label(&context, "How would you like to search for the member?:", ZR_TEXT_LEFT);
			zr_layout_row_static(&context, 30, 240, 3);
			if (zr_button_text(&context, "Search by member number", ZR_BUTTON_DEFAULT)) {
				state = 4;
				fail = 0;
			}
			if (zr_button_text(&context, "Search by member name", ZR_BUTTON_DEFAULT)) {
				state = 5;
				fail = 0;
			}
			for (int i = 0; i < 11; i++)
			zr_layout_row_static(&context, 30, 240, 1);
			zr_layout_row_static(&context, 30, 240, 6);
			if (zr_button_text(&context, "Back", ZR_BUTTON_DEFAULT)) {
				state = 0;
				fail = 0;
			}
		} else if (state == 3) {
			zr_header(&context, "Add Purchase to User", 0, 0, ZR_HEADER_LEFT);
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
			for (int i = 0; i < 11; i++)
			zr_layout_row_static(&context, 30, 240, 1);
			zr_layout_row_static(&context, 30, 240, 6);
			if (zr_button_text(&context, "Back", ZR_BUTTON_DEFAULT)) {
				state = 0;
				fail = 0;
			}
		} else if (state == 4) {
			zr_header(&context, "Delete User - Search by member number", 0, 0, ZR_HEADER_LEFT);
			zr_layout_row_dynamic(&context, 30, 1);
			if (fail == 1) zr_label(&context, "Error! Could not read input number, please try again", ZR_TEXT_LEFT);
			if (fail == 2) zr_label(&context, "Error! Could not find member", ZR_TEXT_LEFT);
			if (fail == 3) zr_label(&context, "Success! Deleted member", ZR_TEXT_LEFT); //not really a fail
			zr_layout_row_dynamic(&context, 30, 1);
			zr_label(&context, "Please input a number:", ZR_TEXT_LEFT);
			zr_layout_row_static(&context, 30, 240, 3);
			zr_editbox(&context, eb[S_NUMBER]);
			zr_layout_row_dynamic(&context, 30, 6);
			if (zr_button_text(&context, "Submit", ZR_BUTTON_DEFAULT)) {
				int iterator = 0, mult = eb[S_NUMBER]->glyphes - 1, ret = 0;
				char *arr = static_cast<char* >(eb[S_NUMBER]->buffer.memory.ptr);
				while (iterator < eb[S_NUMBER]->glyphes && arr[iterator] >= 48 && arr[iterator] <= 57) {
					ret += int(arr[iterator] - 48) * round(pow(10, mult));
					mult--;
					iterator++;
				}
				if (iterator >= eb[S_NUMBER]->glyphes && eb[S_NUMBER]->glyphes != 0) {
					iterator = 0;
					while (iterator < *num_members && members[iterator]->number != ret) iterator++;
					if (iterator >= *num_members) {
						fail = 2;
					} else {
						fail = 3;
						int off = 0;
						Member** temp = members;
						*num_members -= 1;
						Member** temp2 = new Member*[*num_members];
						for (int i = 0; i < *num_members + 1; i++) if (i != iterator) temp2[i - off] = new Member(*temp[i]); else off++;
						Trip** temp_t = new Trip*[num_days];
						int *p_a_d = new int[num_days];
						for (int i = 0; i < num_days; i++) temp_t[i] = new Trip[MAX_ITEMS];
						for (int i = 0; i < num_days; i++) p_a_d[i] = 0;
						for (int i = 0; i < num_days; i++) {
							for (int k = 0; k < purchases_a_day[i]; k++) {
								if (trips[i][k].id == members[iterator]->number) {
									trips[i][k].item->quantity_sold -= trips[i][k].quantity; //thank you pointer! risky move though
								} else {
									temp_t[i][p_a_d[i]] = trips[i][k];
									p_a_d[i]++;
								}
							}
						}
						for (int i = 0; i < num_days; i++) delete trips[i];
						delete [] trips;
						trips = temp_t;
						purchases_a_day = p_a_d;
						members = temp2;
						for (int i = 0; i < *num_members + 1; i++) delete temp[i];
						delete [] temp;
						issue_update(); //super important!
					}
				} else {
					fail = 1;
				}
			}
			for (int i = 0; i < 9; i++)
			zr_layout_row_static(&context, 30, 240, 1);
			zr_layout_row_static(&context, 30, 240, 6);
			if (zr_button_text(&context, "Back", ZR_BUTTON_DEFAULT)) {
				state = 2;
				fail = 0;
			}
		} else if (state == 5) {
			zr_header(&context, "Delete User - Search by member name", 0, 0, ZR_HEADER_LEFT);
			zr_layout_row_dynamic(&context, 30, 1);
			if (fail == 1) zr_label(&context, "Error! Empty field", ZR_TEXT_LEFT);
			if (fail == 2) zr_label(&context, "Error! Could not find member", ZR_TEXT_LEFT);
			if (fail == 3) zr_label(&context, "Success! Deleted member", ZR_TEXT_LEFT); //not really a fail
			zr_layout_row_dynamic(&context, 30, 1);
			zr_label(&context, "Please input a name:", ZR_TEXT_LEFT);
			zr_layout_row_static(&context, 30, 240, 3);
			zr_editbox(&context, eb[S_NAME]);
			zr_layout_row_dynamic(&context, 30, 6);
			if (zr_button_text(&context, "Submit", ZR_BUTTON_DEFAULT)) {
				if (eb[S_NAME]->glyphes != 0) {
					int iterator = 0, iterator2 = 0;
					char *arr = static_cast<char* >(eb[S_NAME]->buffer.memory.ptr);
					while (iterator < *num_members) {
						if (eb[S_NAME]->glyphes != members[iterator]->name.size()) {
							iterator++;
							continue;
						}
						while (iterator2 < eb[S_NAME]->glyphes && arr[iterator2] == members[iterator]->name[iterator2]) iterator2++;
						if (iterator2 >= eb[S_NAME]->glyphes) break;
						iterator2 = 0;
						iterator++;
					}
					if (iterator >= *num_members) {
						fail = 2;
					} else {
						fail = 3;
						int off = 0;
						Member** temp = members;
						*num_members -= 1;
						Member** temp2 = new Member*[*num_members];
						for (int i = 0; i < *num_members + 1; i++) if (i != iterator) temp2[i - off] = new Member(*temp[i]); else off++;
						Trip** temp_t = new Trip*[num_days];
						int *p_a_d = new int[num_days];
						for (int i = 0; i < num_days; i++) temp_t[i] = new Trip[MAX_ITEMS];
						for (int i = 0; i < num_days; i++) p_a_d[i] = 0;
						for (int i = 0; i < num_days; i++) {
							for (int k = 0; k < purchases_a_day[i]; k++) {
								if (trips[i][k].id == members[iterator]->number) {
									trips[i][k].item->quantity_sold -= trips[i][k].quantity; //thank you pointer! risky move though
								} else {
									temp_t[i][p_a_d[i]] = trips[i][k];
									p_a_d[i]++;
								}
							}
						}
						for (int i = 0; i < num_days; i++) delete trips[i];
						delete [] trips;
						trips = temp_t;
						purchases_a_day = p_a_d;
						members = temp2;
						for (int i = 0; i < *num_members + 1; i++) delete temp[i];
						delete [] temp;
						issue_update(); //super important!
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
		}
	}
	zr_end(&context, window);
}
