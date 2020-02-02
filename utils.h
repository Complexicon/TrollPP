#pragma once
#include <wincrypt.h>

HCRYPTPROV prov;

int random()
{
    if (prov == 0)
        if (!CryptAcquireContext(&prov, NULL, NULL, PROV_RSA_FULL,
                CRYPT_SILENT | CRYPT_VERIFYCONTEXT))
            ExitProcess(1);

    int out;
    CryptGenRandom(prov, sizeof(out), (BYTE*)(&out));
    return out & 0x7fffffff;
}