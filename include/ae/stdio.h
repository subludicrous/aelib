/**
* ae/stdio.h
* Author: subludicrous
* Licence: see LICENCE.txt
* Created on: 2021-02-02
*/

#ifndef AE_STDIO_H
#define AE_STDIO_H

#include <ae/base.h>
#include <stdarg.h>
#include <stdio.h>

AE_C_BEGIN

int AEAPI vasprintf(char ** AERESTRICT ptr, char const * AERESTRICT format, va_list arg);

int AEAPI asprintf(char ** AERESTRICT ptr, char const * AERESTRICT format, ...);

int AEAPI vaswprintf(wchar_t ** AERESTRICT ptr, wchar_t const * AERESTRICT format, va_list arg);

int AEAPI aswprintf(wchar_t ** AERESTRICT ptr, wchar_t const * AERESTRICT format, ...);

/// <summary>
/// Prints 'Press any key to continue . . .' and waits for char input.
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
FILE * AEAPI u8fopen(char const * AERESTRICT filename, char const * AERESTRICT mode);

AE_C_END

#endif
