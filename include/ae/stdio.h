// © subludicrous
// SPDX-License-Identifier: BSL-1.0

#ifndef AE_STDIO_H
#define AE_STDIO_H

#include <ae/base.h>

#ifndef __cplusplus
#include <stdarg.h>
#include <stdio.h>
#include <wctype.h> // for wchar_t in C
#else
#include <cstdarg>
#include <cstdio>
#endif

AE_BEGIN

AE_C_BEGIN

int AE_API vasprintf(
    char ** AE_RESTRICT ptr,
    char const * AE_RESTRICT format,
    AE_STD va_list arg
);

int AE_API asprintf(
    char ** AE_RESTRICT ptr,
    char const * AE_RESTRICT format,
    ...
);

int AE_API vaswprintf(
    wchar_t ** AE_RESTRICT ptr,
    wchar_t const * AE_RESTRICT format,
    AE_STD va_list arg
);

int AE_API aswprintf(
    wchar_t ** AE_RESTRICT ptr,
    wchar_t const * AE_RESTRICT format,
    ...
);

/// <summary>
/// Prints 'Press any key to continue . . .' and waits for char input.
/// </summary>
/// <returns>A 'int' representing the typed character.</returns>
int AE_API press_any_key(void);

/// <summary>
/// Opens file with UTF-8 arguments. Sets 'errno' on file open error.
/// 'errno' remains previous value if an encoding error occurs.
/// </summary>
/// <param name="filename">Name of the file in UTF-8.</param>
/// <param name="mode">The mode to open the file in.</param>
/// <returns>A pointer to a 'FILE' or 'NULL' in the case of an error.</returns>
AE_STD FILE * AE_API u8fopen(
    char const * AE_RESTRICT filename,
    char const * AE_RESTRICT mode
);

AE_C_END

AE_END

#endif

