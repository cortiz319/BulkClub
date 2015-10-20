#include "TotalPurchases.h"

void TotalPurchases::render_main(zr_window *window)
{

	zr_context context;
	zr_begin(&context, window);
	{
		Member* membersList[*num_members];
		Member* temp;
		bool    purchase;
		int     numItems = 0;
		float   total = 0;
		int     grandTotal = 0;
		float   grandPtotal = 0;
		int i, j;

		// Creates new list to sort
		for(int i = 0; i < *num_members; i++)
			membersList[i] = members[i];


		// Sorts the list by number
		for (i = 1; i < *num_members; i++) {
			  j = i;
			  while (j > 0 && membersList[j-1]->number > membersList[j]->number) {
					temp = membersList[j];
					membersList[j] = membersList[j - 1];
					membersList[j - 1] = temp;
					j--;
			  }
		}

		// Header for window
		zr_header(&context, "Total Purchases", 0, 0, ZR_HEADER_LEFT);
		zr_layout_row_dynamic(&context, 30, 1);
		zr_label(&context, "This window allows you to get the total purchases!", ZR_TEXT_LEFT);

		// Output the info into the window for total purchases
	    for(int i = 0; i < *num_members; i++)
		{
	    	numItems = 0;
	    	total = 0;
	    	purchase = false;

	    	zr_layout_row_dynamic(&context, 30, 2);

	    	// Names and ids
			zr_label(&context, ("NAME: " + patch::to_string(membersList[i]->name)).c_str() , ZR_TEXT_LEFT);
			zr_label(&context, ("MEMBER ID: " + patch::to_string(membersList[i]->number)).c_str(), ZR_TEXT_LEFT);

			zr_layout_row_dynamic(&context, 30, 3);
			zr_label(&context, "ITEMS", ZR_TEXT_LEFT);
			zr_label(&context, "QUANTITY", ZR_TEXT_LEFT);
			zr_label(&context, "PRICE", ZR_TEXT_LEFT);
			zr_layout_row_dynamic(&context, 30, 1);
			zr_label(&context, "----------------------------------------------------------------------------------------------------------" , ZR_TEXT_LEFT);

			for (int k = 0; k < membersList[i]->number_items_purchased; k++) {
				zr_layout_row_dynamic(&context, 30, 3);
				zr_label(&context, ("-" + membersList[i]->items_purchased[k].item_name).c_str() , ZR_TEXT_LEFT);
				zr_label(&context, patch::to_string(membersList[i]->items_purchased[k].quantity_sold).c_str(), ZR_TEXT_LEFT);
				zr_label(&context, ("$" +(patch::to_string(membersList[i]->items_purchased[k].price.dollars) + "." + ((membersList[i]->items_purchased[k].price.cents > 9) ? patch::to_string(membersList[i]->items_purchased[k].price.cents) : ("0" + patch::to_string(membersList[i]->items_purchased[k].price.cents))))).c_str(), ZR_TEXT_LEFT);
				total += (static_cast<float>(membersList[i]->items_purchased[k].price.dollars) + membersList[i]->items_purchased[k].price.cents/100.0) * membersList[i]->items_purchased->quantity_sold;
				numItems += membersList[i]->items_purchased->quantity_sold;
			}
			zr_layout_row_dynamic(&context, 30, 1);
			zr_label(&context, "----------------------------------------------------------------------------------------------------------" , ZR_TEXT_LEFT);
			zr_layout_row_dynamic(&context, 30, 1);
			zr_label(&context, ("* TOTAL PURCHASES: " + patch::to_string(numItems)).c_str() , ZR_TEXT_LEFT);

			zr_layout_row_dynamic(&context, 30, 1);
			zr_label(&context, ("* TOTAL PRICE: $" + patch::to_string(total)).c_str(), ZR_TEXT_LEFT);

			grandTotal += numItems;
			grandPtotal += total;
		}


		zr_label(&context, "----------------------------------------------------------------------------------------------------------" , ZR_TEXT_LEFT);
    	zr_layout_row_dynamic(&context, 30, 1);
		zr_label(&context, ("GRAND TOTAL ITEMS: " + patch::to_string(grandTotal)).c_str(), ZR_TEXT_LEFT);
    	zr_layout_row_dynamic(&context, 30, 1);
		zr_label(&context, ("GRAND TOTAL PRICE: $" + patch::to_string(grandPtotal)).c_str() , ZR_TEXT_LEFT);

		zr_layout_row_static(&context, 30, 240, 6);
		if (zr_button_text(&context, "Back", ZR_BUTTON_DEFAULT)) { changeWindow(MAIN);}

	}
	zr_end(&context, window);

}
