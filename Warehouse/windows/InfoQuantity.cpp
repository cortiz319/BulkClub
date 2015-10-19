#include "InfoQuantity.h"

void InfoQuantity::render_main(zr_window *window)
{

	zr_context context;
	zr_begin(&context, window);
	{
		Item **sortedItems = items;
		Item *temp;
		float   total = 0;
		int     grandTotal = 0;
		int i, j;

		// Sorts the list by number
		for (i = 1; i < *num_items; i++) {
			  j = i;
			  while (j > 0 && sortedItems[j-1]->item_name > sortedItems[j]->item_name) {
					temp = sortedItems[j];
					sortedItems[j] = sortedItems[j - 1];
					sortedItems[j - 1] = temp;
					j--;
			  }
		}

		// Header for window
		zr_header(&context, "Quantity Info", 0, 0, ZR_HEADER_LEFT);
		zr_layout_row_dynamic(&context, 30, 1);
		zr_label(&context, "This window allows you to get the info on items sold!", ZR_TEXT_LEFT);

		// Output the info into the window for total purchases
	    for(int i = 0; i < *num_items; i++)
		{
	    	zr_layout_row_dynamic(&context, 30, 3);

	    	// Names and id
			zr_label(&context, ("ITEM NAME: " + patch::to_string(sortedItems[i]->item_name)).c_str() , ZR_TEXT_LEFT);
			zr_label(&context, ("SOLD: " + patch::to_string(sortedItems[i]->quantity_sold)).c_str(), ZR_TEXT_LEFT);
			zr_label(&context, string("$" + patch::to_string(sortedItems[i]->price.dollars) + "." + ((sortedItems[i]->price.cents > 9) ? patch::to_string(sortedItems[i]->price.cents) : ("0" + patch::to_string(sortedItems[i]->price.cents)))).c_str(), ZR_TEXT_LEFT);
			total += ((static_cast<float>(sortedItems[i]->price.dollars) + sortedItems[i]->price.cents/100.0)) * sortedItems[i]->quantity_sold;

			grandTotal += total;
		}

		zr_layout_row_dynamic(&context, 30, 1);
		zr_label(&context, ("* GRAND TOTAL: $" + patch::to_string(total)).c_str() , ZR_TEXT_LEFT);

		zr_layout_row_static(&context, 30, 240, 6);
		if (zr_button_text(&context, "Back", ZR_BUTTON_DEFAULT)) { changeWindow(MAIN);}

	}
	zr_end(&context, window);

}
