#pragma comment(linker, \
    "\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include "payloads.hpp"
#include <iostream>
#include <map>

using namespace std;

void printHelp(const char* a)
{
    printf("usage: %s [payload] [loops | inf for infinite] [delay] {text}\n", a);
    printf("payloads:\n");
    printf("mouse - mouse glitching around\n");
    printf("glitch - screen glitches\n");
    printf("tunnel - screen tunnel effect\n");
    printf("invert - invert screen colors\n");
    printf("errorcursor - draw error on cursor\n");
    printf("text - draw text on random position\n");
    printf("epilepsy - screen flashing\n");
    printf("trapmouse - cant move mouse anymore regardless of loops\n");
    printf("soundspam - spams windows sounds\n");
    printf("melt - screen melt effect\n");
    printf("earthquake - screen shaking\n");
    printf("msgbox - spams messageboxes in random positions\n");
    printf("killWindowsNow - very bad\n");
    printf("msgboxmousefollow - msgboxes follow the mouse\n");
}

int main(int argc, char* argv[])
{

    setWinTitle(L"Gay");

    SetTextColor(hdc, RGB(255, 0, 0));
    SetBkColor(hdc, RGB(0, 0, 0));
    SetBkMode(hdc, OPAQUE);

    map<string, void (*)()> funcMap = {
        { "mouse", moveMouse },
        { "glitch", screenGlitch },
        { "tunnel", screenTunnel },
        { "invert", screenInvert },
        { "errorcursor", drawErrorCursor },
        { "msgbox", spawnMsgBox },
        { "earthquake", payloadEarthquake },
        { "melt", melt },
        { "soundspam", payloadSound },
        { "epilepsy", epilepsy },
        { "killWindowsNow", Utils::bluescreen },
        { "trapmouse", trapMouseForever },
        { "msgboxmousefollow", msgboxmousefollow },
    };

    string payload = "msgbox";
    int loops = 1;
    int delay = 10;

    if (argc >= 2)
        payload = argv[1];
    if (argc >= 3)
        if (strcmp(argv[2], "inf") == 0)
            loops = INT32_MAX;
        else
            loops = atoi(argv[2]);
    if (argc >= 4)
        delay = atoi(argv[3]);

    switch (argc) {
    case 2:
        funcMap[payload]();
        break;
    case 3:
    case 4:
        for (int i = 0; i < loops; i++) {
            funcMap[payload]();
            Sleep(delay);
        }
        break;
    case 5:
        if (payload == "text")
            for (int i = 0; i < loops; i++) {
                drawText(argv[4]);
                Sleep(delay);
            }
        break;
    default:
        printHelp(argv[0]);
        break;
    }
    return 0;
}