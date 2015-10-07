#ifndef GUI_H_
#define GUI_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <windows.h>
#include <windowsx.h>
#include "gui/zahnrad.h"

using namespace std;

/* Types */
typedef struct XFont {
    HFONT handle;
    int height;
    int ascent;
    int descent;
} XFont;

typedef struct XSurface {
    int save;
    HDC hdc;
    HBITMAP bitmap;
    HRGN region;
    unsigned int width;
    unsigned int height;
} XSurface;

typedef struct XWindow {
    HINSTANCE hInstance;
    WNDCLASS wc;
    HWND hWnd;
    HDC hdc;
    RECT rect;
    XSurface *backbuffer;
    XFont *font;
    unsigned int width;
    unsigned int height;
} XWindow;

typedef struct Attributes {
	zr_style style;
	zr_user_font font;
	zr_command_queue queue;
	zr_window window;
	struct zr_input input;
	bool running;
} Attributes;

long long timestamp(LARGE_INTEGER);

XFont* font_new(HDC, const char *, int);

zr_size font_get_text_width(zr_handle, const zr_char *, zr_size);

void font_del(XFont *);

XSurface* surface_new(HDC, unsigned int, unsigned int);

void surface_resize(XSurface *, HDC, unsigned int, unsigned int);

void surface_del(XSurface *);

void surface_scissor(XSurface *, short, short, unsigned short,
		unsigned short);

void surface_draw_line(XSurface *, short, short, short, short,
		unsigned char,  unsigned char, unsigned char);

void surface_draw_rect(XSurface *, short, short, unsigned short,
		unsigned short, unsigned char, unsigned char, unsigned char);

void surface_draw_circle(XSurface *, short, short, unsigned short,
		unsigned short, unsigned char,  unsigned char, unsigned char);

void surface_draw_triangle(XSurface *, short, short, short, short,
		short, short, unsigned char,  unsigned char, unsigned char);

void surface_draw_text(XSurface *, XFont *, short, short, unsigned short,
		unsigned short, const char *, unsigned int, unsigned char,
		unsigned char, unsigned char, unsigned char, unsigned char,
		unsigned char);

void surface_clear(XSurface *, unsigned char,  unsigned char,
		unsigned char);

void surface_begin(XSurface *);

void surface_end(XSurface *, HDC);

void draw(XSurface *, zr_command_queue *);

void input_key(struct zr_input *, MSG *, zr_bool);

void input_text(struct zr_input *, MSG *);

void input_motion(struct zr_input *, MSG *);

void input_btn(struct zr_input *, MSG *, zr_bool);

void set_style(zr_style *);

#endif /* GUI_H_ */
