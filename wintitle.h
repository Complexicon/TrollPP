#pragma once
#include "main.h"

LPCWSTR wintitle = L"lol";

BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam)
{
    SendMessageTimeoutW(hwnd, WM_SETTEXT, NULL, (LPARAM)wintitle, SMTO_ABORTIFHUNG,
        100, NULL);
    return TRUE;
}