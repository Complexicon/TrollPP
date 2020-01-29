#include "main.h"

const int MOUSESHAKE = 30;
POINT cursor;
HDC hdc = GetDC(0);
int ix = GetSystemMetrics(SM_CXICON) / 2;
int iy = GetSystemMetrics(SM_CYICON) / 2;
int w = GetSystemMetrics(SM_CXSCREEN);
int h = GetSystemMetrics(SM_CYSCREEN);

void moveMouse()
{
    GetCursorPos(&cursor);
    SetCursorPos(cursor.x + (rand() % MOUSESHAKE - MOUSESHAKE / 2), cursor.y + (rand() % MOUSESHAKE - MOUSESHAKE / 2));
}

void drawErrorCursor()
{
    GetCursorPos(&cursor);
    DrawIcon(hdc, cursor.x - ix, cursor.y - iy, LoadIcon(NULL, IDI_EXCLAMATION));
}

void screenGlitch()
{
    int x1 = rand() % (w - 1000);
    int y1 = rand() % (h - 1000);
    int x2 = rand() % (w - 1000);
    int y2 = rand() % (h - 1000);
    BitBlt(hdc, x1, y1, w, h, hdc, x2, y2, SRCERASE);
}

void epilepsy()
{
    BitBlt(hdc, 0, 0, w, h, hdc, 0, 0, WHITENESS);
    Sleep(10);
    BitBlt(hdc, 0, 0, w, h, hdc, 0, 0, BLACKNESS);
}

void screenInvert()
{
    BitBlt(hdc, 0, 0, w, h, hdc, 0, 0, NOTSRCCOPY);
}

void screenTunnel()
{
    StretchBlt(hdc, 50, 50, w - 100, h - 100, hdc, 0, 0, w, h, SRCCOPY);
}

void drawText(const char *text)
{
    int x1 = rand() % w;
    int y1 = rand() % h;
    RECT rect = {x1, y1, x1, y1};
    DrawTextA(hdc, text, -1, &rect, DT_NOCLIP);
}