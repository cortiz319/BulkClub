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

		for(int i = 0; i < *num_members; i++)
			membersList[i] = members[i];


		for (i = 1; i < *num_members; i++) {
			  j = i;
			  while (j > 0 && membersList[j-1]->number > membersList[j]->number) {
					temp = membersList[j];
					membersList[j] = membersList[j - 1];
					membersList[j - 1] = temp;
					j--;
			  }
		}

		zr_header(&context, "Total Purchases", 0, 0, ZR_HEADER_LEFT);
		zr_layout_row_dynamic(&context, 30, 1);
		zr_label(&context, "This window allows you to get the total purchases!", ZR_TEXT_LEFT);

	    for(int i = 0; i < *num_members; i++)
		{
	    	numItems = 0;
	    	total = 0;
	    	purchase = false;
	    	zr_layout_row_dynamic(&context, 30, 2);
			zr_label(&context, "NAME", ZR_TEXT_LEFT);
			zr_label(&context, "MEMBER ID", ZR_TEXT_LEFT);


	    	zr_layout_row_dynamic(&context, 30, 2);

			zr_label(&context, patch::to_string(membersList[i]->name).c_str() , ZR_TEXT_LEFT);
			zr_label(&context, patch::to_string(membersList[i]->number).c_str(), ZR_TEXT_LEFT);

			zr_layout_row_dynamic(&context, 30, 3);
			zr_label(&context, "ITEMS", ZR_TEXT_LEFT);
			zr_label(&context, "QUANTITY", ZR_TEXT_LEFT);
			zr_label(&context, "PRICE", ZR_TEXT_LEFT);
			for(int k = 0; k < num_days; k++)
			{
				for(int j = 0; j < purchases_a_day[k]; j++)
				{
					if(membersList[i]->number == trips[k][j].id)
					{
						purchase = true;

				    	zr_layout_row_dynamic(&context, 30, 3);

						zr_label(&context, ("-" + trips[k][j].item->item_name).c_str() , ZR_TEXT_LEFT);
						zr_label(&context, patch::to_string(trips[k][j].item->quantity_sold).c_str(), ZR_TEXT_LEFT);
						zr_label(&context, (patch::to_string(trips[k][j].item->price.dollars) + "." + ((trips[k][j].item->price.cents > 9) ? patch::to_string(trips[k][j].item->price.cents) : ("0" + patch::to_string(trips[k][j].item->price.cents)))).c_str(), ZR_TEXT_LEFT);
						total += ((float)trips[k][j].item->price.dollars + trips[k][j].item->price.cents/100.0) * trips[k][j].quantity;
						numItems += trips[k][j].item->quantity_sold;
					}
				}
			}
			zr_layout_row_dynamic(&context, 30, 1);
			zr_label(&context, "-------------------------------------------------------------------------------------------------------------------------" , ZR_TEXT_LEFT);


			// Used this to check if any member has not purchased an item.
			// Testing revealed two have not purchased anything.
			if(!purchase)
			{
		    	zr_layout_row_dynamic(&context, 30, 1);
				zr_label(&context, "*** HAS NOT PURCHASED ANY ITEM ***" , ZR_TEXT_LEFT);
			}else{
		    	zr_layout_row_dynamic(&context, 30, 2);
				zr_label(&context, "TOTAL PURCHASES" , ZR_TEXT_LEFT);
				zr_label(&context, patch::to_string(numItems).c_str() , ZR_TEXT_LEFT);

		    	zr_layout_row_dynamic(&context, 30, 3);
				zr_label(&context, "TOTAL PRICE" , ZR_TEXT_LEFT);
				zr_label(&context, "" , ZR_TEXT_LEFT);
				zr_label(&context, patch::to_string(total).c_str() , ZR_TEXT_LEFT);
			}

			grandTotal += numItems;
			grandPtotal += total;
		}

		zr_label(&context, "-------------------------------------------------------------------------------------------------------------------------" , ZR_TEXT_LEFT);
    	zr_layout_row_dynamic(&context, 30, 2);
		zr_label(&context, "GRAND TOTAL ITEMS" , ZR_TEXT_LEFT);
		zr_label(&context, patch::to_string(grandTotal).c_str() , ZR_TEXT_LEFT);
    	zr_layout_row_dynamic(&context, 30, 2);
		zr_label(&context, "GRAND TOTAL PRICE" , ZR_TEXT_LEFT);
		zr_label(&context, patch::to_string(grandPtotal).c_str() , ZR_TEXT_LEFT);


		if (zr_button_text(&context, "Back", ZR_BUTTON_DEFAULT)) { changeWindow(MAIN);}

	}
	zr_end(&context, window);

}
