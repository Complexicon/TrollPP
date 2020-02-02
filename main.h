#pragma once

#pragma comment(linker, \
    "\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include "utils.h"
#include <iostream>
#include <map>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

const int MOUSESHAKE = 30;

int w = GetSystemMetrics(SM_CXSCREEN);
int h = GetSystemMetrics(SM_CYSCREEN);

HDC hdc = GetDC(0);