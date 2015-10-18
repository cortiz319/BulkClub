#include "InfoItem.h"
#include "../core/Initializer.h"

void InfoItem::render_main(zr_window *window)
{
	zr_context context;
	Item* searchItem = 0;
	zr_begin(&context, window);
	{
		if(state == 0)
		{
			zr_header(&context, "Get Item Info", 0, 0, ZR_HEADER_LEFT);
			zr_layout_row_dynamic(&context, 30, 1);
			zr_label(&context, "This window allows you to get info for an item", ZR_TEXT_LEFT);

			zr_layout_row_dynamic(&context, 30, 3);
			zr_label(&context, "Please input an item:", ZR_TEXT_LEFT);
			zr_layout_row_dynamic(&context, 30, 3);
			zr_editbox(&context, &eb);

			if(zr_button_text(&context, "Enter", ZR_BUTTON_DEFAULT))
			{
				state = 1;
			}
			for (int i = 0; i < 9; i++)
			zr_layout_row_static(&context, 30, 240, 1);
			zr_layout_row_static(&context, 30, 240, 6);

			if (zr_button_text(&context, "Back", ZR_BUTTON_DEFAULT)) {
				changeWindow(MAIN);
				state = 0;
				fail = 0;
			}

		} else if(state == 1){
			char *arr = static_cast<char* >(eb.buffer.memory.ptr);

			searchItem = search_for_item(arr, items, *num_members);

			if(searchItem != NULL){
				zr_header(&context, "Search for Item", 0, 0, ZR_HEADER_LEFT);
				float total = 0;
				zr_layout_row_dynamic(&context, 30, 3);
				zr_label(&context, "ITEM", ZR_TEXT_LEFT);
				zr_label(&context, "QUANTITY", ZR_TEXT_LEFT);
				zr_label(&context, "PRICE", ZR_TEXT_LEFT);
				zr_layout_row_dynamic(&context, 30, 3);
				zr_label(&context, searchItem->item_name.c_str(), ZR_TEXT_LEFT);
				zr_label(&context, patch::to_string(searchItem->quantity_sold).c_str(), ZR_TEXT_LEFT);
				zr_label(&context, (patch::to_string(searchItem->price.dollars) + "." + ((searchItem->price.cents > 9) ? patch::to_string(searchItem->price.cents ) : ("0" + patch::to_string(searchItem->price.cents )))).c_str(), ZR_TEXT_LEFT);
				total = searchItem->quantity_sold * (static_cast<float>(searchItem->price.dollars) + searchItem->price.cents/100.0);
				zr_layout_row_dynamic(&context, 30, 3);
				zr_label(&context, "REVENUE", ZR_TEXT_LEFT);
				zr_label(&context, "", ZR_TEXT_LEFT);
				zr_label(&context, patch::to_string(total).c_str(), ZR_TEXT_LEFT);
			}else if(eb.glyphes == 0){
				zr_layout_row_dynamic(&context, 30, 1);
				zr_label(&context, "Please enter an item name.", ZR_TEXT_LEFT);
			}else{
				zr_layout_row_dynamic(&context, 30, 1);
				zr_label(&context, (patch::to_string(arr) + " was not found").c_str(), ZR_TEXT_LEFT);
			}

			for (int i = 0; i < 9; i++)
			zr_layout_row_static(&context, 30, 240, 1);
			zr_layout_row_static(&context, 30, 240, 6);

			if (zr_button_text(&context, "Back", ZR_BUTTON_DEFAULT)) {
				changeWindow(MAIN);
				state = 0;
				fail = 0;
			}
		}

	}
	zr_end(&context, window);
}
