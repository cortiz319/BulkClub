#include "SalesReport.h"


#include <string>
#include<iomanip>
#include <sstream>

//	out << setw(SALES_REPORT) << "ITEMS" << "QUANTITY\n";
//	for(int i =0; i < purchases_a_day[day-1]; i++)
//	{
//		compare = search_for_member(trips[day-1][i].id, members, num);
//		if(m_type == 1 && compare->member_type == 0){
//			out << setw(SALES_REPORT) << trips[day-1][i].item->item_name
//				 <<  trips[day-1][i].item->quantity_sold <<endl;
//
//			revenue += (trips[day-1][i].item->price.dollars * trips[day-1][i].item->price.cents/100.0) * trips[day-1][i].item->quantity_sold;
//
//		} else if(m_type == 2 && compare->member_type == 1) {
//			out << setw(SALES_REPORT) << trips[day-1][i].item->item_name
//				 <<  trips[day-1][i].item->quantity_sold <<endl;
//
//			revenue += (trips[day-1][i].item->price.dollars * trips[day-1][i].item->price.cents/100.0) * trips[day-1][i].item->quantity_sold;
//		} else {
//			out << setw(SALES_REPORT) << trips[day-1][i].item->item_name
//				 <<  trips[day-1][i].item->quantity_sold <<endl;
//
//			revenue += (trips[day-1][i].item->price.dollars * trips[day-1][i].item->price.cents/100.0) * trips[day-1][i].item->quantity_sold;
//
//		}
//
//	}
//	out << "\nMEMBERS\n";
//	for(int i =0; i < purchases_a_day[day-1]; i++)
//	{
//		j = i+1;
//		searchMem = search_for_member(trips[day-1][i].id, members, num);
//		found = false;
//
//		while(j < purchases_a_day[day-1] && !found)
//		{
//			compare = search_for_member(trips[day-1][j].id, members, num);
//
//			if(m_type == 1){
//				if(searchMem->name == compare->name && compare->member_type == 0)
//					found = true;
//			}else if(m_type == 2){
//				if(searchMem->name == compare->name && compare->member_type == 1)
//					found = true;
//			} else 	{
//				if(searchMem->name == compare->name)
//					found = true;
//			}
//
//			j++;
//		}
//
//		if(!found)
//		{
//			out << searchMem->name << endl;
//			(searchMem->member_type ==1? numExec++: numReg++);
//		}
//	}
//	out << endl;
//
//	if(m_type == 1){
//		out << setw(SALES_REPORT) << "Number of REGULAR members   : "   << numReg << endl;
//	}else if(m_type == 2){
//
//		out << setw(SALES_REPORT) << "Number of EXECUTIVE members : " << numExec << endl;
//	} else 	{
//
//		out << setw(SALES_REPORT) << "Number of EXECUTIVE members : " << numExec << endl;
//		out << setw(SALES_REPORT) << "Number of REGULAR members   : "   << numReg << endl;
//	}
//
//	out << fixed << setprecision(2);
//	out << "\nRevenue for day " << day << " is: $" << revenue << endl << endl;
//
//	out << right;

void SalesReport::render_main(zr_window *window){

	const int SALES_REPORT = 30;

	ostringstream out;
	Member* searchMem;
	int numExec = 0;
	int numReg = 0;
	float revenue = 0;
	int j;
	Member* compare;
	bool found = false;

	zr_context context;
	zr_context layout;
	zr_begin(&context, window);
	{
		zr_header(&context, "Sales Report", 0, 0, ZR_HEADER_LEFT);
		zr_layout_row_dynamic(&context, 30, 1);
		zr_label(&context, "This window allows you to get a sales report!", ZR_TEXT_LEFT);
		zr_layout_row_dynamic(&context, 30, 1);
		zr_label(&context, "Which member type would you like to search by?:", ZR_TEXT_LEFT);
		zr_layout_row_static(&context, 30, 240, 2);

		zr_combo_begin(&context, &layout, values[selected], &active);
		{
			zr_layout_row_dynamic(&layout, 25, 1);
			for (int i = 0; i < size; ++i) {
				if (selected == i) continue;
				if (zr_combo_item(&layout, ZR_TEXT_LEFT, values[i])) {
					selected = i;
				}
			}

		}

		zr_combo_end(&context, &layout, &active);
		zr_combo_begin(&context, &layout, days[selected_days], &active_d);
		{
			zr_layout_row_dynamic(&layout, 25, 1);
			for (int i = 0; i < num_days; ++i) {
				if (selected_days == i) continue;
				if (zr_combo_item(&layout, ZR_TEXT_LEFT, days[i])) {
					selected_days = i;
				}
			}

		}
		zr_combo_end(&context, &layout, &active_d);
		zr_layout_row_dynamic(&context, 30, 2);
		zr_label(&context, "ITEMS:", ZR_TEXT_LEFT);
		zr_label(&context, "QUANTITY", ZR_TEXT_LEFT);

		revenue = 0;
		for(int i =0; i < purchases_a_day[selected_days];i++)
		{
			compare = search_for_member(trips[selected_days][i].id, members, *num_members);
			if(selected == 1 && compare->member_type == 0){
				zr_layout_row_dynamic(&context, 30, 2);
				zr_label(&context, trips[selected_days][i].item->item_name.c_str() , ZR_TEXT_LEFT);
				zr_label(&context, patch1::to_string(trips[selected_days][i].item->quantity_sold).c_str() , ZR_TEXT_LEFT);
				revenue += (trips[selected_days][i].item->price.dollars * trips[selected_days][i].item->price.cents/100.0) * trips[selected_days][i].item->quantity_sold;

			} else if(selected == 2 && compare->member_type == 1) {
				zr_layout_row_dynamic(&context, 30, 2);
				zr_label(&context, trips[selected_days][i].item->item_name.c_str() , ZR_TEXT_LEFT);
				zr_label(&context, patch1::to_string(trips[selected_days][i].item->quantity_sold).c_str() , ZR_TEXT_LEFT);
				revenue += (trips[selected_days][i].item->price.dollars * trips[selected_days][i].item->price.cents/100.0) * trips[selected_days][i].item->quantity_sold;
			} else if(selected == 0){
				zr_layout_row_dynamic(&context, 30, 2);
				zr_label(&context, trips[selected_days][i].item->item_name.c_str() , ZR_TEXT_LEFT);
				zr_label(&context, patch1::to_string(trips[selected_days][i].item->quantity_sold).c_str() , ZR_TEXT_LEFT);
				revenue += (trips[selected_days][i].item->price.dollars * trips[selected_days][i].item->price.cents/100.0) * trips[selected_days][i].item->quantity_sold;
			}
		}
		zr_layout_row_dynamic(&context, 30, 2);
		zr_label(&context, "Revenue", ZR_TEXT_LEFT);
		zr_label(&context, patch1::to_string(revenue).c_str(), ZR_TEXT_LEFT);

		for(int i =0; i < purchases_a_day[selected_days]; i++)
		{
			j = i+1;
			searchMem = search_for_member(trips[selected_days][i].id, members, *num_members);
			found = false;

			while(j < purchases_a_day[selected_days] && !found)
			{
				compare = search_for_member(trips[selected_days][j].id, members, *num_members);

				if(searchMem->name == compare->name)
					found = true;

				j++;
			}

			if(!found)
			{
				if(selected == 1 && searchMem->member_type == 0){
					zr_layout_row_dynamic(&context, 30, 1);
					zr_label(&context, patch1::to_string(searchMem->name).c_str(), ZR_TEXT_LEFT);
					(searchMem->member_type ==1? numExec++: numReg++);
				} else if(selected == 2 && searchMem->member_type == 1) {
					zr_layout_row_dynamic(&context, 30, 1);
					zr_label(&context, patch1::to_string(searchMem->name).c_str(), ZR_TEXT_LEFT);
					(searchMem->member_type ==1? numExec++: numReg++);
				} else if(selected == 0){
					zr_layout_row_dynamic(&context, 30, 1);
					zr_label(&context, patch1::to_string(searchMem->name).c_str(), ZR_TEXT_LEFT);
					(searchMem->member_type ==1? numExec++: numReg++);
				}

			}
		}

		if(selected == 2){
			zr_layout_row_dynamic(&context, 30, 2);
			zr_label(&context, "EXECUTIVE members", ZR_TEXT_LEFT);
			zr_label(&context, patch1::to_string(numExec).c_str(), ZR_TEXT_LEFT);
		} else if(selected == 1) {
			if(searchMem->name == compare->name)
				zr_layout_row_dynamic(&context, 30, 2);
				zr_label(&context, "REGULAR members", ZR_TEXT_LEFT);
				zr_label(&context, patch1::to_string(numReg).c_str(), ZR_TEXT_LEFT);
		} else if(selected == 0){
			zr_layout_row_dynamic(&context, 30, 2);
			zr_label(&context, "REGULAR members", ZR_TEXT_LEFT);
			zr_label(&context, patch1::to_string(numReg).c_str(), ZR_TEXT_LEFT);
			zr_layout_row_dynamic(&context, 30, 2);
			zr_label(&context, "EXECUTIVE members", ZR_TEXT_LEFT);
			zr_label(&context, patch1::to_string(numExec).c_str(), ZR_TEXT_LEFT);
		}

		zr_layout_row_dynamic(&context, 30, 2);


		for (int i = 0; i < 10; i++)
			zr_layout_row_static(&context, 30, 240, 1);
			zr_layout_row_static(&context, 30, 240, 6);

		if (zr_button_text(&context, "Back", ZR_BUTTON_DEFAULT)) { changeWindow(MAIN);}

		//zr_editbox(&context, &eb);
	}
	zr_end(&context, window);

}
