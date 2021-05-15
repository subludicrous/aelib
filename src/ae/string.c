/**
* Name: aestring.c
* Description: A Unicode® (among other things) string library.
* Created on: 2021-02-02
* © 2021 subludicrous
* Licensed under the terms of the MIT licence.
*/

#include <ae/string.h>

#include <winapi_imports.h>

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef WINCHECK

#include <fcntl.h>
#include <io.h>

#endif

void uint_to_binstr_base(char * binstr, uint64_t const val, size_t const bits) {
	for (uint64_t i = 0x1Ui64 << (bits - 1Ui64); i; i >>= 1U) {
		*binstr = (val & i) ? '1' : '0';
		binstr++;
	}
}

int AEAPI uint_to_binstr(char *binstr, const uint64_t val, const size_t bits) {
	if (!binstr || !bits || bits > 64Ui64) {
		return EINVAL;
	}
	uint_to_binstr_base(binstr, val, bits);
	return 0;
}

char * AEAPI auint_to_binstr(uint64_t const input, size_t const bits) {
	if (bits > 64i64) return NULL;

	char * const output = malloc(bits + 1Ui64);
	if (!output) {
		return NULL;
	}
#if _MSC_VER
#pragma warning(disable: 6386)
#endif
	output[bits] = '\0';
	uint_to_binstr_base(output, input, bits);
	return output;
}

#ifdef WINCHECK

char * AEAPI au16str_to_u8str_winapi(const wchar_t * const utf16str) {
	size_t const req_size = (size_t) WideCharToMultiByte(CP_UTF8, 0, utf16str, -1, NULL, 0, NULL, NULL);
	char * const utf8str = malloc(req_size);
	if (utf8str == NULL) {
		return NULL;
	}
	int const written = WideCharToMultiByte(CP_UTF8, 0, utf16str, -1, utf8str, (int) req_size, NULL, NULL);
	if ((size_t) written != req_size) {
		free(utf8str);
		return NULL;
	}
	return utf8str;
}

wchar_t * AEAPI au8str_to_u16str_winapi(const char * const utf8str) {
	size_t const req_size = (size_t) MultiByteToWideChar(CP_UTF8, 0, utf8str, -1, NULL, 0);
	wchar_t * const utf16str = malloc(sizeof(wchar_t) * req_size);
	if (utf16str == NULL) {
		return NULL;
	}
	int const written = MultiByteToWideChar(CP_UTF8, 0, utf8str, -1, utf16str, (int) req_size);
	if ((size_t) written != req_size) {
		free(utf16str);
		return NULL;
	}
	return utf16str;
}

#endif
