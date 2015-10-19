#include "Loader.h"

DWORD WINAPI mythread(void *threadParams) {
	struct threadParams* params = (struct threadParams*)threadParams;
	bool out = Initialize_Everything(params->param3, *params->param4,
			*params->param5, params->param6, params->param7, params->param8,
			params->param9,
			string(static_cast<const char*>(params->param1)).substr(0, params->param2).c_str(), false);
	if (out) *params->param10 = 2;
	else *params->param10 = 3;
	return 0;
}

void Loader::render_main(zr_window *window) {
	zr_context context;
	zr_begin(&context, window);
	{
		if (state == 1) {
			zr_header(&context, "Loading", 0, 0, ZR_HEADER_LEFT);
			zr_layout_row_dynamic(&context, 30, 1);
			zr_label(&context, "Loading right now", ZR_TEXT_LEFT);
		} else if (state == 2) {
			issue_update(); //update variable globally. This is important!
			zr_header(&context, "Success!", 0, 0, ZR_HEADER_LEFT);
			zr_layout_row_dynamic(&context, 30, 1);
			zr_label(&context, "Loading right now", ZR_TEXT_LEFT);
			changeWindow(MAIN); //to main window!
		} else {
			zr_header(&context, "Welcome to the BulkClub!", 0, 0, ZR_HEADER_LEFT);
			zr_layout_row_dynamic(&context, 30, 1);
			if (state == 3) zr_label(&context, "Error! Could not load from specified directory", ZR_TEXT_LEFT);
			zr_layout_row_dynamic(&context, 30, 1);
			zr_label(&context, "Please input the directory where the core files lie:", ZR_TEXT_LEFT);
			zr_layout_row_static(&context, 30, 240, 3);
			zr_editbox(&context, &eb);
			zr_layout_row_dynamic(&context, 30, 6);
			if (zr_button_text(&context, "Submit", ZR_BUTTON_DEFAULT)) {
				state = 1;
				threadParams *params1 = new threadParams;
				params1->param1 = eb.buffer.memory.ptr;
				params1->param2 = eb.glyphes;
				params1->param3 = num_days;
				params1->param4 = num_members;
				params1->param5 = num_items;
				params1->param6 = members;
				params1->param7 = trips;
				params1->param8 = items;
				params1->param9 = purchases_a_day;
				params1->param10 = &state;
				CreateThread(NULL, 0, mythread, (void*) params1, 0, &threadDescriptor);
			}
		}
	}
	zr_end(&context, window);
}
