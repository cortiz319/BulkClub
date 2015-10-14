#include "GUI.h"

long long timestamp(LARGE_INTEGER freq) {
    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);
    return (1000LL * now.QuadPart) / freq.QuadPart;
}

XFont* font_new(HDC hdc, const char *name, int height) {
    HFONT old;
    TEXTMETRIC metrics;
    XFont *font = static_cast<XFont*>(malloc(sizeof(XFont)));
    if (!font) return NULL;
    font->height = height;
    font->handle = CreateFont(height, 0, 0, 0, 0, FALSE, FALSE, FALSE,
        ANSI_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
        ANTIALIASED_QUALITY, DEFAULT_PITCH, name);

    old = static_cast<HFONT>(SelectObject(hdc, font->handle));
    GetTextMetrics(hdc, &metrics);
    font->ascent = metrics.tmAscent;
    font->descent = metrics.tmDescent;
    SelectObject(hdc, old);
    return font;
}

zr_size font_get_text_width(zr_handle handle, const zr_char *text, zr_size len) {
    SIZE size;
    HFONT old;
    XWindow *win = static_cast<XWindow*>(handle.ptr);
    XFont *font = win->font;
    XSurface *surf = win->backbuffer;
    if (!font ||!text || !len) return 0;

    old = static_cast<HFONT>(SelectObject(surf->hdc, font->handle));
    GetTextExtentPoint32(surf->hdc, (LPCTSTR)text, (int)len, &size);
    SelectObject(surf->hdc, old);
    return size.cx;
}

void font_del(XFont *font) {
    if (font->handle)
    DeleteObject(font->handle);
    free(font);
}

XSurface* surface_new(HDC hdc, unsigned int width, unsigned int height) {
    XSurface *surf = static_cast<XSurface*>(malloc(sizeof(XSurface)));
    if (!surf) return NULL;
    surf->hdc = CreateCompatibleDC(hdc);
    surf->bitmap = CreateCompatibleBitmap(hdc, width, height);
    surf->width = width;
    surf->height = height;
    surf->region = NULL;
    return surf;
}

void surface_resize(XSurface *surf, HDC hdc, unsigned int width, unsigned int height) {
    DeleteObject(surf->bitmap);
    surf->bitmap = CreateCompatibleBitmap(hdc, width, height);
    surf->width = width;
    surf->height = height;
}

void surface_del(XSurface *surf) {
    if (surf->region) DeleteObject(surf->region);
    DeleteDC(surf->hdc);
    DeleteObject(surf->bitmap);
    free(surf);
}

void surface_scissor(XSurface *surf, short x, short y, unsigned short w, unsigned short h) {
    if (surf->region) DeleteObject(surf->region);
    surf->region = CreateRectRgn(x, y, x + w, y + h);
    SelectClipRgn(surf->hdc, surf->region);
}

void surface_draw_line(XSurface *surf, short x0, short y0, short x1, short y1,
    unsigned char r,  unsigned char g, unsigned char b) {
    HPEN hPen;
    HPEN old;
    hPen = CreatePen(PS_SOLID, 1, RGB(r,g,b));
    old = static_cast<HPEN>(SelectObject(surf->hdc, hPen));
    MoveToEx(surf->hdc, x0, y0, NULL);
    LineTo(surf->hdc, x1, y1);
    SelectObject(surf->hdc, old);
    DeleteObject(hPen);
}

void surface_draw_rect(XSurface *surf, short x, short y, unsigned short w, unsigned short h,
    unsigned char r,  unsigned char g, unsigned char b) {
    HBRUSH hBrush;
    HBRUSH old;
    RECT rect;
    rect.left = (LONG)x;
    rect.top = (LONG)y;
    rect.right = (LONG)(x + w);
    rect.bottom = (LONG)(y + h);
    hBrush = CreateSolidBrush(RGB(r,g,b));
    old = static_cast<HBRUSH>(SelectObject(surf->hdc, hBrush));
    FillRect(surf->hdc, &rect, hBrush);
    SelectObject(surf->hdc, old);
    DeleteObject(hBrush);
}

void surface_draw_circle(XSurface *surf, short x, short y, unsigned short w, unsigned short h,
    unsigned char r,  unsigned char g, unsigned char b) {
    HBRUSH hBrush;
    HBRUSH old;
    hBrush = CreateSolidBrush(RGB(r,g,b));
    old = static_cast<HBRUSH>(SelectObject(surf->hdc, hBrush));
    Ellipse(surf->hdc, x, y, (x + w), (y + h));
    SelectObject(surf->hdc, old);
    DeleteObject(hBrush);
}

void surface_draw_triangle(XSurface *surf, short x0, short y0, short x1, short y1,
    short x2, short y2, unsigned char r,  unsigned char g, unsigned char b) {
    HBRUSH old;
    HBRUSH hBrush;
    POINT pnt[3];
    pnt[0].x = (LONG)x0;
    pnt[0].y = (LONG)y0;
    pnt[1].x = (LONG)x1;
    pnt[1].y = (LONG)y1;
    pnt[2].x = (LONG)x2;
    pnt[2].y = (LONG)y2;

    hBrush = CreateSolidBrush(RGB(r,g,b));
    old = static_cast<HBRUSH>(SelectObject(surf->hdc, hBrush));
    Polygon(surf->hdc, pnt, 3);
    SelectObject(surf->hdc, old);
    DeleteObject(hBrush);
}

void surface_draw_text(XSurface *surf, XFont *font, short x, short y, unsigned short w,
    unsigned short h, const char *text, unsigned int len,
    unsigned char bg_r, unsigned char bg_g, unsigned char bg_b,
    unsigned char fg_r, unsigned char fg_g, unsigned char fg_b) {
    RECT format;
    UINT bg = RGB(bg_r, bg_g, bg_b);
    UINT fg = RGB(fg_r, fg_g, fg_b);
    HFONT old = static_cast<HFONT>(SelectObject(surf->hdc, font->handle));

    format.left = x;
    format.top = y;
    format.right = x + w;
    format.bottom = y + h;

    SetBkColor(surf->hdc, bg);
    SetTextColor(surf->hdc, fg);
    SetBkMode(surf->hdc, OPAQUE);
    DrawText(surf->hdc, text, len, &format, DT_LEFT|DT_SINGLELINE|DT_VCENTER);
    SelectObject(surf->hdc, old);
}

void surface_clear(XSurface *surf, unsigned char r,  unsigned char g, unsigned char b) {
	surface_draw_rect(surf,0,0,(unsigned short)surf->width,(unsigned short)surf->height, r, g, b);
}

void surface_begin(XSurface *surf) {
    surf->save = SaveDC(surf->hdc);
    SelectObject(surf->hdc, surf->bitmap);
}

void surface_end(XSurface *surf, HDC hdc) {
    BitBlt(hdc, 0, 0, surf->width, surf->height, surf->hdc, 0, 0, SRCCOPY);
    RestoreDC(hdc, surf->save);
}

void draw(XSurface *surf, struct zr_command_queue *queue) {
    const struct zr_command *cmd;
    zr_foreach_command(cmd, queue) {
        switch (cmd->type) {
        case ZR_COMMAND_NOP: break;
        case ZR_COMMAND_SCISSOR: {
            const struct zr_command_scissor *s = zr_command(scissor, cmd);
            surface_scissor(surf, s->x, s->y, s->w, s->h);
        } break;
        case ZR_COMMAND_LINE: {
            const struct zr_command_line *l = zr_command(line, cmd);
            surface_draw_line(surf, l->begin.x, l->begin.y, l->end.x,
                l->end.y, l->color.r, l->color.g, l->color.b);
        } break;
        case ZR_COMMAND_RECT: {
            const struct zr_command_rect *r = zr_command(rect, cmd);
            surface_draw_rect(surf, r->x, r->y, r->w, r->h,
                r->color.r, r->color.g, r->color.b);
        } break;
        case ZR_COMMAND_CIRCLE: {
            const struct zr_command_circle *c = zr_command(circle, cmd);
            surface_draw_circle(surf, c->x, c->y, c->w, c->h,
                c->color.r, c->color.g, c->color.b);
        } break;
        case ZR_COMMAND_TRIANGLE: {
            const struct zr_command_triangle *t = zr_command(triangle, cmd);
            surface_draw_triangle(surf, t->a.x, t->a.y, t->b.x, t->b.y,
                t->c.x, t->c.y, t->color.r, t->color.g, t->color.b);
        } break;
        case ZR_COMMAND_TEXT: {
            const struct zr_command_text *t = zr_command(text, cmd);
            XWindow *win = static_cast<XWindow*>(t->font->userdata.ptr);
            surface_draw_text(surf, win->font, t->x, t->y, t->w, t->h, (const char*)t->string,
                    (unsigned int)t->length, t->background.r, t->background.g, t->background.b,
                    t->foreground.r, t->foreground.g, t->foreground.b);
        } break;
        case ZR_COMMAND_IMAGE:
        case ZR_COMMAND_CURVE:
        case ZR_COMMAND_ARC:
        default: break;
        }
    }
    zr_command_queue_clear(queue);
}

void input_key(struct zr_input *in, MSG *msg, zr_bool down) {
	switch (msg->wParam) {
		case VK_SHIFT: zr_input_key(in, ZR_KEY_SHIFT, down); break;
		case VK_DELETE: zr_input_key(in, ZR_KEY_DEL, down); break;
		case VK_RETURN: zr_input_key(in, ZR_KEY_ENTER, down); break;
		case VK_BACK: zr_input_key(in, ZR_KEY_BACKSPACE, down); break;
		case VK_LEFT: zr_input_key(in, ZR_KEY_LEFT, down); break;
		case VK_RIGHT: zr_input_key(in, ZR_KEY_RIGHT, down); break;
		default: break;
	}
}

void input_text(struct zr_input *in, MSG *msg) {
    char glyph;
    if (msg->wParam < 32 || msg->wParam >= 128) return;
    glyph = (zr_char)msg->wParam;
    zr_input_char(in, glyph);
}

void input_motion(struct zr_input *in, MSG *msg) {
    const zr_int x = GET_X_LPARAM(msg->lParam);
    const zr_int y = GET_Y_LPARAM(msg->lParam);
    zr_input_motion(in, x, y);
}

void input_btn(struct zr_input *in, MSG *msg, zr_bool down) {
    const zr_int x = GET_X_LPARAM(msg->lParam);
    const zr_int y = GET_Y_LPARAM(msg->lParam);
    zr_input_button(in, ZR_BUTTON_LEFT, x, y, down);
}

void set_style(zr_style *style) {
	style->colors[ZR_COLOR_TEXT] = zr_rgba(255, 255, 255, 255);
	style->colors[ZR_COLOR_TEXT_HOVERING] = zr_rgba(120, 120, 120, 255);
	style->colors[ZR_COLOR_TEXT_ACTIVE] = zr_rgba(100, 100, 100, 255);
	style->colors[ZR_COLOR_WINDOW] = zr_rgba(65, 65, 65, 255);
	style->colors[ZR_COLOR_HEADER] = zr_rgba(40, 40, 40, 255);
	style->colors[ZR_COLOR_BORDER] = zr_rgba(38, 38, 38, 255);
	style->colors[ZR_COLOR_BUTTON] = zr_rgba(50, 50, 50, 255);
	style->colors[ZR_COLOR_BUTTON_HOVER] = zr_rgba(35, 35, 35, 255);
	style->colors[ZR_COLOR_BUTTON_ACTIVE] = zr_rgba(40, 40, 40, 255);
	style->colors[ZR_COLOR_TOGGLE] = zr_rgba(100, 100, 100, 255);
	style->colors[ZR_COLOR_TOGGLE_HOVER] = zr_rgba(120, 120, 120, 255);
	style->colors[ZR_COLOR_TOGGLE_CURSOR] = zr_rgba(45, 45, 45, 255);
	style->colors[ZR_COLOR_SLIDER] = zr_rgba(38, 38, 38, 255);
	style->colors[ZR_COLOR_SLIDER_CURSOR] = zr_rgba(100, 100, 100, 255);
	style->colors[ZR_COLOR_SLIDER_CURSOR_HOVER] = zr_rgba(120, 120, 120, 255);
	style->colors[ZR_COLOR_SLIDER_CURSOR_ACTIVE] = zr_rgba(150, 150, 150, 255);
	style->colors[ZR_COLOR_PROGRESS] = zr_rgba(38, 38, 38, 255);
	style->colors[ZR_COLOR_PROGRESS_CURSOR] = zr_rgba(100, 100, 100, 255);
	style->colors[ZR_COLOR_PROGRESS_CURSOR_HOVER] = zr_rgba(120, 120, 120, 255);
	style->colors[ZR_COLOR_PROGRESS_CURSOR_ACTIVE] = zr_rgba(150, 150, 150, 255);
	style->colors[ZR_COLOR_INPUT] = zr_rgba(45, 45, 45, 255);
	style->colors[ZR_COLOR_INPUT_CURSOR] = zr_rgba(100, 100, 100, 255);
	style->colors[ZR_COLOR_INPUT_TEXT] = zr_rgba(255, 255, 255, 255);
	style->colors[ZR_COLOR_SPINNER] = zr_rgba(45, 45, 45, 255);
	style->colors[ZR_COLOR_SPINNER_TRIANGLE] = zr_rgba(100, 100, 100, 255);
	style->colors[ZR_COLOR_HISTO] = zr_rgba(120, 120, 120, 255);
	style->colors[ZR_COLOR_HISTO_BARS] = zr_rgba(45, 45, 45, 255);
	style->colors[ZR_COLOR_HISTO_NEGATIVE] = zr_rgba(255, 255, 255, 255);
	style->colors[ZR_COLOR_HISTO_HIGHLIGHT] = zr_rgba( 255, 0, 0, 255);
	style->colors[ZR_COLOR_PLOT] = zr_rgba(100, 100, 100, 255);
	style->colors[ZR_COLOR_PLOT_LINES] = zr_rgba(45, 45, 45, 255);
	style->colors[ZR_COLOR_PLOT_HIGHLIGHT] = zr_rgba(255, 0, 0, 255);
	style->colors[ZR_COLOR_SCROLLBAR] = zr_rgba(40, 40, 40, 255);
	style->colors[ZR_COLOR_SCROLLBAR_CURSOR] = zr_rgba(100, 100, 100, 255);
	style->colors[ZR_COLOR_SCROLLBAR_CURSOR_HOVER] = zr_rgba(120, 120, 120, 255);
	style->colors[ZR_COLOR_SCROLLBAR_CURSOR_ACTIVE] = zr_rgba(150, 150, 150, 255);
	style->colors[ZR_COLOR_TABLE_LINES] = zr_rgba(100, 100, 100, 255);
	style->colors[ZR_COLOR_TAB_HEADER] = zr_rgba(40, 40, 40, 255);
	style->colors[ZR_COLOR_SHELF] = zr_rgba(40, 40, 40, 255);
	style->colors[ZR_COLOR_SHELF_TEXT] = zr_rgba(150, 150, 150, 255);
	style->colors[ZR_COLOR_SHELF_ACTIVE] = zr_rgba(30, 30, 30, 255);
	style->colors[ZR_COLOR_SHELF_ACTIVE_TEXT] = zr_rgba(150, 150, 150, 255);
	style->colors[ZR_COLOR_SCALER] = zr_rgba(100, 100, 100, 255);
}
