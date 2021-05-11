/**
* Name: aestdio.h
* Description: Adds asprintf and vasprintf.
* Created on: 2021-02-02
* © 2021 subludicrous
* Licensed under the terms of the MIT licence.
*/

#ifndef AELIB_STDIO_H
#define AELIB_STDIO_H

#include <aebase.h>

#include <stdarg.h>
#include <wctype.h>
#include <stdio.h>

AELIB_C_BEGIN

int AEAPI vasprintf(char ** AERESTRICT ptr, const char * AERESTRICT format, va_list arg);

int AEAPI asprintf(char ** AERESTRICT ptr, const char * AERESTRICT format, ...);

int AEAPI vaswprintf(wchar_t ** AERESTRICT ptr, const wchar_t * AERESTRICT format, va_list arg);

int AEAPI aswprintf(wchar_t ** AERESTRICT ptr, const wchar_t * AERESTRICT format, ...);

/// <summary>
/// Prints 'Press any key to continue . . .' and waits for wchar_t input.
/// </summary>
/// <returns>A 'int' representing the typed character.</returns>
int AEAPI press_any_key(void);

/// <summary>
/// Prints 'Press any key to continue . . .' and waits for wchar_t input.
/// </summary>
/// <returns>A 'wint_t' representing the typed character.</returns>
wint_t AEAPI wpress_any_key(void);

/// <summary>
/// Opens file with UTF-8 arguments. Sets 'errno' on file open error.
/// 'errno' remains previous value if an encoding error occurs.
/// </summary>
/// <param name="filename">Name of the file in UTF-8.</param>
/// <param name="mode">The mode to open the file in.</param>
/// <returns>A pointer to a 'FILE' or 'NULL' in the case of an error.</returns>
FILE *AEAPI u8fopen(const char *filename, const char *mode);

AELIB_C_END

#endif
