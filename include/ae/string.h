/**
* Name: aestring.h
* Description: A Unicode® (among other things) string library.
* Created on: 2021-02-02
* © 2021 subludicrous
* Licensed under the terms of the MIT licence.
*/

#ifndef AE_STRING_H
#define AE_STRING_H

#include <aebase.h>

#include <uchar.h>
#include <stdint.h>
#include <stdbool.h>

AELIB_C_BEGIN

int AEAPI uint_to_binstr(char *binstr, uint64_t val, size_t bits);

char *AEAPI auint_to_binstr(uint64_t input, size_t bits);

/// <summary>
/// This function shifts to the next character in a UTF-8 string. TODO
/// </summary>
/// <param name="str">todo</param>
/// <param name="len"></param>
/// <returns></returns>
//const char* u8str_nextc(const char* str, int len = 1);

/// <summary>
/// Converts a UTF-8 character to UTF-32.
/// </summary>
/// <param name="str">A UTF-8 character.</param>
/// <returns>A Unicode® codepoint.</returns>
char32_t AEAPI u8c_to_u32c(const char* str);

/// <summary>
/// Converts a UTF-32 character to UTF-8.
/// </summary>
/// <param name="code">The UTF-32 character.</param>
/// <param name="u8str">The buffer to which to write the UTF-8 bytes.</param>
/// <returns>The number of UTF-8 bytes representing the character.</returns>
size_t AEAPI u32c_to_u8c(char32_t code, char *u8str);

#ifdef WINCHECK

char * AEAPI au16str_to_u8str_winapi(const wchar_t * utf16str);

wchar_t * AEAPI au8str_to_u16str_winapi(const char * utf8str);

bool AEAPI main_unicodize(
	unsigned long * const AERESTRICT poriginal_mode,
	unsigned int * AERESTRICT pcp,
	int * AERESTRICT pprev_mode);

void AEAPI main_deunicodize(
	unsigned long original_mode,
	unsigned int cp,
	int prev_mode);

char ** AEAPI get_u8argv(void);

void AEAPI free_u8argv(int argc, char ** argv);

// todo also u8set, get etc

char ** AEAPI get_u8envp(void);

void AEAPI free_u8envp(char ** envp);

#endif

AELIB_C_END

#endif
