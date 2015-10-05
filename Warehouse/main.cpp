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
#include "Windows/Window.h"
#include "Windows/Main.h"
#include "gui/zahnrad.h"
#include "GUI.h"
#include "member/Member.h"
#include "member/Regular.h"
#include "member/Executive.h"
#include "util/Trip.h"
#include "util/Item.h"
#include "core/Initializer.h"

#define DTIME       16
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define MAX_MEMORY  (32 * 1024)
#define MAX_BUFFER  64

using namespace std;

//variable declaration
XWindow xw;
Attributes gui;
Window **windows;
int num_windows = 0;
int window_index = 0;
const int num_members = 12; //change if needed
const int num_days = 5;
const int purchases_a_day[] = {13, 12, 10, 12, 13};
Item **items;
int num_items;
Member **members; //sexy right?
Trip **trips; //it's ra1ning 2-dimensional arrays!

//INSTRUCTIONS TO ADD gdi32!!
//"BulkClub"->Properties->C/C++ Build->Settings->
//MinGW C++ Linker->Libraries->Libraries (-l)->
//*click icon with green plus sign*->Type "gdi32" without quotes->
//Ok->Apply->Ok

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
    LARGE_INTEGER freq;
    long long start;
    long long dt;

    QueryPerformanceFrequency(&freq);
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

    members = new Member*[num_members];
	trips = new Trip*[num_days];
	items = new Item*[MAX_ITEMS];
	for (int i = 0; i < num_days; i++) trips[i] = new Trip[purchases_a_day[i]];
	num_items = 0;

    windows = new Window*[num_windows];
    windows[0] = new Main();
    //load your windows here!

    Initialize_Everything(num_days, num_members, num_items, members, trips, items, purchases_a_day);

    gui.running = true;

    while (gui.running) {
        /* Input */
        MSG msg;
        start = timestamp(freq);
        zr_input_begin(&gui.input);
        while (PeekMessage(&msg, xw.hWnd, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_KEYDOWN) key(&gui.input, &msg, zr_true);
            else if (msg.message == WM_KEYUP) key(&gui.input, &msg, zr_false);
            else if (msg.message == WM_LBUTTONDOWN) btn(&gui.input, &msg, zr_true);
            else if (msg.message == WM_LBUTTONUP) btn(&gui.input, &msg, zr_false);
            else if (msg.message == WM_MOUSEMOVE) motion(&gui.input, &msg);
            else if (msg.message == WM_CHAR) text(&gui.input, &msg);
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        zr_input_end(&gui.input);

        windows[window_index]->render_main(&gui.window);

        surface_begin(xw.backbuffer);
        surface_clear(xw.backbuffer, 100, 100, 100);
        draw(xw.backbuffer, &gui.queue);
        surface_end(xw.backbuffer, xw.hdc);

        dt = timestamp(freq) - start;
        if (dt < DTIME) Sleep(DTIME - (DWORD)dt);
    }

    free(zr_buffer_memory(&gui.queue.buffer));
    font_del(xw.font);
    surface_del(xw.backbuffer);
    ReleaseDC(xw.hWnd, xw.hdc);
    return 0;
}

