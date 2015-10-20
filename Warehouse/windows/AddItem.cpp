#include "AddItem.h"

void AddItem::render_main(zr_window *window){
	zr_context context;
	zr_context layout;
	zr_begin(&context, window);
	{
		if(state == 0) {
			zr_header(&context, "Add and Delete Item", 0, 0, ZR_HEADER_LEFT);

			zr_layout_row_static(&context, 30, 240, 3);
			if (zr_button_text(&context, "Add Item", ZR_BUTTON_DEFAULT)) {
				state = 1;
				fail = 0;
			}
			if (zr_button_text(&context, "Delete Item", ZR_BUTTON_DEFAULT)) {
				state = 2;
				fail = 0;
			}

			for (int i = 0; i < 12; i++)
			zr_layout_row_static(&context, 30, 240, 1);
			zr_layout_row_static(&context, 30, 240, 6);
			if (zr_button_text(&context, "Back", ZR_BUTTON_DEFAULT)) { changeWindow(MAIN);}
		} else if(state == 1) {
			zr_header(&context, "Add Item", 0, 0, ZR_HEADER_LEFT);
			zr_layout_row_dynamic(&context, 30, 1);
			if (fail == 1) zr_label(&context, "Error! Item name is empty", ZR_TEXT_LEFT);
			if (fail == 2) zr_label(&context, "Error! Dollar is empty (is it empty? does it contain regular characters?)", ZR_TEXT_LEFT);
			if (fail == 3) zr_label(&context, "Error! Cents is empty", ZR_TEXT_LEFT);
			if (fail == 5) zr_label(&context, "Error! Cents is longer then two characters", ZR_TEXT_LEFT);
			if (fail == 4) zr_label(&context, "Created Item successfully!", ZR_TEXT_LEFT);
			zr_layout_row_dynamic(&context, 30, 1);
			zr_label(&context, "Please input the necessary data to create an item:", ZR_TEXT_LEFT);
			zr_layout_row_static(&context, 30, 240, 3);
			zr_label(&context, "Item Name:", ZR_TEXT_LEFT);
			zr_editbox(&context, eb[ITEM]);
			zr_layout_row_static(&context, 30, 240, 3);
			zr_label(&context, "Dollars:", ZR_TEXT_LEFT);
			zr_editbox(&context, eb[DOLLAR]);
			zr_layout_row_static(&context, 30, 240, 3);
			zr_label(&context, "Cents:", ZR_TEXT_LEFT);
			zr_editbox(&context, eb[CENTS]);

			for (int i = 0; i < 8; i++)
			zr_layout_row_static(&context, 30, 240, 1);
			zr_layout_row_static(&context, 30, 240, 6);
			if (zr_button_text(&context, "Submit", ZR_BUTTON_DEFAULT)) {
				if (eb[ITEM]->glyphes == 0) fail = 1;
				else if (eb[DOLLAR]->glyphes == 0) fail = 2;
				else if (eb[CENTS]->glyphes == 0) fail =3;
				else {
					// Dollars
					char *arrD = static_cast<char* >(eb[DOLLAR]->buffer.memory.ptr);
					char *arrC = static_cast<char* >(eb[CENTS]->buffer.memory.ptr);
					int iteratorD = 0, multD = eb[DOLLAR]->glyphes - 1, retD = 0;
					int iteratorC = 0, multC = eb[CENTS]->glyphes - 1, retC = 0;

					while (iteratorD < eb[DOLLAR]->glyphes && arrD[iteratorD] >= 48 && arrD[iteratorD] <= 57) {
						retD += int(arrD[iteratorD] - 48) * round(pow(10, multD));
						multD--;
						iteratorD++;
					}

					while (iteratorC < eb[CENTS]->glyphes && arrC[iteratorC] >= 48 && arrC[iteratorC] <= 57) {
						retC += int(arrC[iteratorC] - 48) * round(pow(10, multC));
						multC--;
						iteratorC++;
					}

					if (eb[DOLLAR]->glyphes <= 0) {
						fail = 2;
					} else if (eb[CENTS]->glyphes <= 0) {
						fail = 3;
					} else if (eb[CENTS]->glyphes > 2) {
						fail = 5;
					} else {
						fail = 4;
						int iterator = 0;
						Item** temp = items;
						*num_items += 1;
						Item** temp2 = new Item*[*num_items];
						for (int i = 0; i < *num_items - 1; i++){
							temp2[i] = new Item();
							temp2[i]->item_name = temp[i]->item_name;
							temp2[i]->price.cents = temp[i]->price.cents;
							temp2[i]->price.dollars = temp[i]->price.dollars;
							temp2[i]->quantity_sold = temp[i]->quantity_sold;
						}
						temp2[*num_items - 1] = new Item();
						temp2[*num_items - 1]->item_name = string(static_cast<char *>(eb[ITEM]->buffer.memory.ptr));
						temp2[*num_items - 1]->price.dollars = retD;
						temp2[*num_items - 1]->price.cents = retC;
						temp2[*num_items - 1]->quantity_sold = 0;

						for(int i = 0; i < num_days; i++)
						{
							for(int j = 0; j < purchases_a_day[i]; j++)
							{
								iterator = 0;
								while (iterator < *num_items && trips[i][j].item->item_name != temp2[iterator]->item_name) {
									iterator++;
								}
								trips[i][j].item = temp2[iterator];
							}
						}
						items = temp2;
						for (int i = 0; i < *num_items - 1; i++) delete temp[i];
						delete [] temp;
						issue_update(); //super important!
					}
				}
			}
			if (zr_button_text(&context, "Back", ZR_BUTTON_DEFAULT)) {
				state = 0;
				fail = 0;
			}
		} else if (state == 2) {
			zr_header(&context, "Delete Item", 0, 0, ZR_HEADER_LEFT);
			zr_layout_row_static(&context, 30, 240, 3);
			if (zr_button_text(&context, "Search by item name", ZR_BUTTON_DEFAULT)) {
				state = 3;
				fail = 0;
			}
			for (int i = 0; i < 12; i++)
			zr_layout_row_static(&context, 30, 240, 1);
			zr_layout_row_static(&context, 30, 240, 6);
			if (zr_button_text(&context, "Back", ZR_BUTTON_DEFAULT)) {
				state = 0;
				fail = 0;
			}
		} else if(state == 3) {
			zr_header(&context, "Delete Item", 0, 0, ZR_HEADER_LEFT);
			zr_layout_row_dynamic(&context, 30, 1);
			if (fail == 1) zr_label(&context, "Error! Empty field", ZR_TEXT_LEFT);
			if (fail == 2) zr_label(&context, "Error! Could not find item", ZR_TEXT_LEFT);
			if (fail == 3) zr_label(&context, "Success! Deleted item", ZR_TEXT_LEFT); //not really a fail
			zr_layout_row_dynamic(&context, 30, 1);
			zr_label(&context, "Please input an item:", ZR_TEXT_LEFT);
			zr_layout_row_static(&context, 30, 240, 3);
			zr_editbox(&context, eb[S_ITEM]);
			zr_layout_row_dynamic(&context, 30, 6);
			if (zr_button_text(&context, "Submit", ZR_BUTTON_DEFAULT)) {
				if (eb[S_ITEM]->glyphes != 0) {
					int iterator = 0, iterator2 = 0;
					char *arr = static_cast<char* >(eb[S_ITEM]->buffer.memory.ptr);
					while (iterator < *num_items) {
						if (eb[S_ITEM]->glyphes != items[iterator]->item_name.size()) {
							iterator++;
							continue;
						}
						while (iterator2 < eb[S_ITEM]->glyphes && arr[iterator2] == items[iterator]->item_name[iterator2]) iterator2++;
						if (iterator2 >= eb[S_ITEM]->glyphes) break;
						iterator2 = 0;
						iterator++;
					}
					if (iterator >= *num_items) {
						fail = 2;
					} else {
						fail = 3;
						items[iterator]->deleted = true;
						issue_update(); //super important!
					}
				} else {
					fail = 1;
				}
				zr_layout_row_static(&context, 30, 240, 1);
				zr_layout_row_static(&context, 30, 240, 6);
				if (zr_button_text(&context, "Back", ZR_BUTTON_DEFAULT)) { changeWindow(MAIN);}
			}
			for (int i = 0; i < 9; i++)
			zr_layout_row_static(&context, 30, 240, 1);
			zr_layout_row_static(&context, 30, 240, 6);
			if (zr_button_text(&context, "Back", ZR_BUTTON_DEFAULT)) { changeWindow(MAIN);}
		}
	}
	zr_end(&context, window);
}
