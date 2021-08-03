// © subludicrous
// SPDX-License-Identifier: BSL-1.0

#ifndef WINAPI_IMPORTS_H
#define WINAPI_IMPORTS_H

#include <ae/base.h>

#if AE_NO_DEFAULT_UTF8

// Windows types
#define WINAPI __stdcall
typedef int BOOL, *LPBOOL;
typedef void *HANDLE, *HLOCAL;
typedef unsigned long DWORD, *LPDWORD;
typedef unsigned int UINT;
typedef wchar_t * LPWSTR;
typedef wchar_t const * LPCWSTR, * LPCWCH;
typedef char * LPSTR;
typedef char const * LPCCH;
typedef long long LONG_PTR;

#define CP_UTF8                            (65001U)
#define MB_PRECOMPOSED                     (1U)
#define STD_OUTPUT_HANDLE                  ((DWORD)-11)
#define STD_ERROR_HANDLE                   ((DWORD)-12)
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#define INVALID_HANDLE_VALUE               ((HANDLE)(LONG_PTR)-1)

AE_C_BEGIN

__declspec(dllimport) int      WINAPI MultiByteToWideChar(
    UINT CodePage,
    DWORD dwFlags,
    LPCCH lpMultiByteStr,
    int cbMultiByte,
    LPWSTR lpWideCharStr,
    int cchWideChar
);

__declspec(dllimport) int      WINAPI WideCharToMultiByte(
    UINT CodePage,
    DWORD dwFlags,
    LPCWCH lpWideCharStr,
    int cchWideChar,
    LPSTR lpMultiByteStr,
    int cbMultiByte,
    LPCCH lpDefaultChar,
    LPBOOL lpUsedDefaultChar
);

__declspec(dllimport) HANDLE   WINAPI GetStdHandle(DWORD nStdHandle);

__declspec(dllimport) BOOL     WINAPI GetConsoleMode(
    HANDLE hConsoleHandle,
    LPDWORD lpMode
);

__declspec(dllimport) BOOL     WINAPI SetConsoleMode(
    HANDLE hConsoleHandle,
    DWORD dwMode
);

__declspec(dllimport) UINT     WINAPI GetConsoleOutputCP(void);

__declspec(dllimport) BOOL     WINAPI SetConsoleOutputCP(UINT CodePage);

__declspec(dllimport) HLOCAL   WINAPI LocalFree(HLOCAL hMem);

__declspec(dllimport) LPWSTR   WINAPI GetCommandLineW(void);

__declspec(dllimport) LPWSTR * WINAPI CommandLineToArgvW(
    LPCWSTR lpCmdLine,
    int * pNumArgs
);

AE_C_END

#endif // AE_NO_DEFAULT_UTF8

#endif
