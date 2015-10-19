#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <windows.h>
#include <windowsx.h>
#include <assert.h>
#include <string.h>
#include <iostream>
#include <string>
#include <fstream>
#include "windows/SaveData.h"
#include "windows/SalesReport.h"
#include "windows/TotalPurchases.h"
#include "windows/AddUser.h"
#include "windows/ExecToRegular.h"
#include "windows/RegularToExec.h"
#include "windows/TotalPurchases.h"
#include "windows/InfoQuantity.h"
#include "windows/AddItem.h"
#include "windows/MemberExpiration.h"
#include "windows/Rebates.h"
#include "windows/Loader.h"
#include "windows/MemberInfo.h"
#include "windows/InfoItem.h"
#include "windows/Window.h"
#include "windows/Main.h"
#include "gui/zahnrad.h"
#include "GUI.h"
#include "member/Member.h"
#include "member/Regular.h"
#include "member/Executive.h"
#include "util/Trip.h"
#include "util/Item.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define MAX_MEMORY  (32 * 1024)
#define MAX_BUFFER  64
#define UNUSED(a)   ((void)(a))
#define MAX_ITEMS 256

using namespace std;

//variable declaration
XWindow xw;
Attributes gui;
Window **windows;
int num_windows = 14;
int window_index = 0;

int *num_members;
int num_days = 5;
int *purchases_a_day;
Item **items;
int *num_items;
Member **members; //sexy right?
Trip **trips; //it's ra1ning 2-dimensional arrays!
int window; //for saving window data

//INSTRUCTIONS TO ADD gdi32!!
//"BulkClub"->Properties->C/C++ Build->Settings->
//MinGW C++ Linker->Libraries->Libraries (-l)->
//*click icon with green plus sign*->Type "gdi32" without quotes->
//Ok->Apply->Ok

//GUI documentation: https://github.com/vurtun/zahnrad

// How to add a window
// 1. Add new .h and .cpp file to 'windows' folder
// 2. Create class and include Window publically
// 3. Implement class. Take a look at other windows as an example.
// 4. Include .h file above
// 5. Go to line 133 (approx.) here and initialize you class (follow format exactly of other classes)
// 6. Go to Window.h and add a const int for your class
// 7. Happiness!

LRESULT CALLBACK wnd_proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_DESTROY:
        PostQuitMessage(WM_QUIT);
        gui.running = false;
        break;
    case WM_SIZE:
        if (xw.backbuffer) {
        xw.width = LOWORD(lParam);
        xw.height = HIWORD(lParam);
        surface_resize(xw.backbuffer, xw.hdc, xw.width, xw.height);
        } break;
    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    return 0;
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prev, LPSTR lpCmdLine, int shown) {
	FreeConsole();
    xw.wc.style = CS_HREDRAW|CS_VREDRAW;
    xw.wc.lpfnWndProc = wnd_proc;
    xw.wc.hInstance = hInstance;
    xw.wc.lpszClassName = "GUI";
    RegisterClass(&xw.wc);
    xw.hWnd = CreateWindowEx(
        0, xw.wc.lpszClassName, "BulkClub!",
        WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX|WS_MAXIMIZEBOX|WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        0, 0, hInstance, 0);

    xw.hdc = GetDC(xw.hWnd);
    GetClientRect(xw.hWnd, &xw.rect);
    xw.backbuffer = surface_new(xw.hdc, xw.rect.right, xw.rect.bottom);
    xw.font = font_new(xw.hdc, "Times New Roman", 16);
    xw.width = xw.rect.right;
    xw.height = xw.rect.bottom;

    gui.font.userdata = zr_handle_ptr(&xw);
    gui.font.height = (zr_float)xw.font->height;
    gui.font.width =  font_get_text_width;
    zr_style_default(&gui.style, ZR_DEFAULT_ALL, &gui.font);
    zr_command_queue_init_fixed(&gui.queue, malloc(MAX_MEMORY), MAX_MEMORY);

    zr_window_init(&gui.window, zr_rect(5, 5, WINDOW_WIDTH - 20, WINDOW_HEIGHT - 40),
	ZR_WINDOW_BORDER,
	&gui.queue, &gui.style, &gui.input);

    set_style(&gui.style);

    purchases_a_day = new int[5];
    members = new Member*[MAX_ITEMS];
	trips = new Trip*[num_days];
	items = new Item*[MAX_ITEMS];
	for (int i = 0; i < num_days; i++) trips[i] = new Trip[MAX_ITEMS];
	for (int i = 0; i < num_days; i++) purchases_a_day[i] = 0;
	num_items = new int;
	*num_items = 0;
	num_members = new int;
	*num_members = 0;

    windows = new Window*[num_windows];
    for (int i = 0; i < num_windows; i++) windows[i] = NULL;
    windows[LOADER] = new Loader(purchases_a_day, items, num_items, members, num_members, trips, num_days);
    windows[MAIN] = new Main(purchases_a_day, items, num_items, members, num_members, trips, num_days);
    windows[SALESREPORT] = new SalesReport(purchases_a_day, items, num_items, members, num_members, trips, num_days);
    windows[MEMBERINFO] = new MemberInfo(purchases_a_day, items, num_items, members, num_members, trips, num_days);
    windows[REGULARTOEXEC] = new RegularToExec(purchases_a_day, items, num_items, members, num_members, trips, num_days);
    windows[EXECTOREGULAR] = new ExecToRegular(purchases_a_day, items, num_items, members, num_members, trips, num_days);
    windows[ADDUSER] = new AddUser(purchases_a_day, items, num_items, members, num_members, trips, num_days);
    windows[INFOITEM] = new InfoItem(purchases_a_day, items, num_items, members, num_members, trips, num_days);
    windows[TOTALPURCHASES] = new TotalPurchases(purchases_a_day, items, num_items, members, num_members, trips, num_days);
    windows[INFOQUANTITY] = new InfoQuantity(purchases_a_day, items, num_items, members, num_members, trips, num_days);
    windows[REBATES] = new Rebates(purchases_a_day, items, num_items, members, num_members, trips, num_days);
    windows[EXPIRE] = new MemberExpiration(purchases_a_day, items, num_items, members, num_members, trips, num_days);
    windows[SAVEDATA] = new SaveData(purchases_a_day, items, num_items, members, num_members, trips, num_days);
    windows[ADDITEM] = new AddItem(purchases_a_day, items, num_items, members, num_members, trips, num_days);
    //load your windows here!

    gui.running = true;

    while (gui.running) {
        /* Input */
        MSG msg;
        zr_input_begin(&gui.input);
        while (PeekMessage(&msg, xw.hWnd, 0, 0, PM_REMOVE)) {
        	if (msg.message == WM_KEYDOWN)
        		input_key(&gui.input, &msg, zr_true);
			else if (msg.message == WM_KEYUP)
				input_key(&gui.input, &msg, zr_false);
			else if (msg.message == WM_LBUTTONDOWN)
				input_btn(&gui.input, &msg, zr_true);
			else if (msg.message == WM_LBUTTONUP)
				input_btn(&gui.input, &msg, zr_false);
			else if (msg.message == WM_MOUSEMOVE)
				input_motion(&gui.input, &msg);
			else if (msg.message == WM_CHAR)
				input_text(&gui.input, &msg);
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        zr_input_end(&gui.input);

        windows[window_index]->render_main(&gui.window);
        if (windows[window_index]->exit_program()) gui.running = false;
        if (windows[window_index]->do_update()) {
        	windows[window_index]->set_data(purchases_a_day, items, num_items, members, num_members, trips, num_days);
        	for (int i = 0; i < num_windows; i++){
        		if (i != window_index && windows[i] != NULL) windows[i]->update_data(purchases_a_day, items, num_items, members, num_members, trips, num_days);
        	}
        }
        window = windows[window_index]->setWindow();
        if (window_index != window) {
        	windows[window_index]->init();
        	window_index = window;
        }

        surface_begin(xw.backbuffer);
        surface_clear(xw.backbuffer, 100, 100, 100);
        draw(xw.backbuffer, &gui.queue);
        surface_end(xw.backbuffer, xw.hdc);
    }

    free(zr_buffer_memory(&gui.queue.buffer));
    font_del(xw.font);
    surface_del(xw.backbuffer);
    ReleaseDC(xw.hWnd, xw.hdc);
    return 0;
}
