/**
* Name: 'aestdio.c'
* Description: Implementation of 'aestdio.h'.
* Created on: 2021-02-02
* © 2021 subludicrous
* Licensed under the terms of the MIT licence
*/

#include <aestdio.h>

#include <aestring.h>

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

int AEAPI vasprintf(char ** AERESTRICT ptr, const char * const AERESTRICT format, const va_list arg) {
	va_list copy;
	va_copy(copy, arg);
	// _vscprintf tells you how big the buffer needs to be
	const int len = _vscprintf(format, copy);
	va_end(copy);
	if (len == -1) {
		return -1;
	}
	const size_t size = (size_t) len + 1ULL;
	char *const str = malloc(size);
	if (!str) {
		return -1;
	}
	const int err = vsprintf(str, format, arg);
	if (err == -1) {
		free(str);
		return -1;
	}
	*ptr = str;
	return err;
}

int AEAPI asprintf(char ** const AERESTRICT ptr, const char * const AERESTRICT format, ...) {
	va_list ap;
	va_start(ap, format);
	const int r = vasprintf(ptr, format, ap);
	va_end(ap);
	return r;
}

int AEAPI vaswprintf(wchar_t ** const AERESTRICT ptr, const wchar_t * const AERESTRICT format, const va_list arg) {
	va_list copy;
	va_copy(copy, arg);
	const int len = _vscwprintf(format, copy);
	va_end(copy);
	if (len == -1) {
		return -1;
	}
	const size_t size = (size_t) len + 1ULL;
	wchar_t *const str = malloc(size * sizeof(wchar_t));
	if (str == NULL) {
		return -1;
	}
	const int err = vswprintf(str, size, format, arg);
	if (err == -1) {
		free(str);
		return -1;
	}
	*ptr = str;
	return err;
}

int AEAPI aswprintf(wchar_t ** const AERESTRICT ptr, const wchar_t * const AERESTRICT format, ...) {
	va_list ap;
	va_start(ap, format);
	const int r = vaswprintf(ptr, format, ap);
	va_end(ap);
	return r;
}

int AEAPI press_any_key(void) {
	puts("Press any key to continue . . .");
	// the fastest way to do this 0% CPU vs 10+% with other
	return _getch();
}

wint_t AEAPI wpress_any_key(void) {
	_putws(L"Press any key to continue . . .");
	// the fastest way to do this 0% CPU vs 10+% with other
	return _getwch();
}

FILE * AEAPI u8fopen(const char *const filename, const char *const mode) {
#ifdef WINCHECK
	wchar_t *const wfilename = au8str_to_u16str_winapi(filename);
	wchar_t *const wmode = au8str_to_u16str_winapi(mode);
	if ((wfilename == NULL) || (wmode == NULL)) {
		return NULL;
	}
	FILE *const file = _wfopen(wfilename, wmode);
	free(wfilename);
	free(wmode);
	return file;
#else
	return fopen(filename, mode);
#endif
}
