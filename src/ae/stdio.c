// ? subludicrous
// SPDX-License-Identifier: BSL-1.0

#include <ae/stdio.h>
#include <ae/win_u8.h>
#include <stdlib.h>
#include <conio.h>

int AE_API vasprintf(
	char ** AE_RESTRICT ptr,
	char const * const AE_RESTRICT format,
	va_list const arg
) {
	va_list copy;
	va_copy(copy, arg);
	// _vscprintf tells you how big the buffer needs to be
	int const len = _vscprintf(format, copy);
	va_end(copy);
	if (len == -1) {
		return -1;
	}
	size_t const size = (size_t) len + 1ULL;
	char * const str = malloc(size);
	if (!str) {
		return -1;
	}
	int const err = vsprintf(str, format, arg);
	if (err == -1) {
		free(str);
		return -1;
	}
	*ptr = str;
	return err;
}

int AE_API asprintf(
	char ** const AE_RESTRICT ptr,
	char const * const AE_RESTRICT format,
	...
) {
	va_list ap;
	va_start(ap, format);
	int const r = vasprintf(ptr, format, ap);
	va_end(ap);
	return r;
}

int AE_API vaswprintf(
	wchar_t ** const AE_RESTRICT ptr,
	wchar_t const * const AE_RESTRICT format,
	va_list const arg
) {
	va_list copy;
	va_copy(copy, arg);
	int const len = _vscwprintf(format, copy);
	va_end(copy);
	if (len == -1) {
		return -1;
	}
	size_t const size = (size_t) len + 1ULL;
	wchar_t * const str = malloc(size * sizeof(wchar_t));
	if (str == NULL) {
		return -1;
	}
	int const err = vswprintf(str, size, format, arg);
	if (err == -1) {
		free(str);
		return -1;
	}
	*ptr = str;
	return err;
}

int AE_API aswprintf(
	wchar_t ** const AE_RESTRICT ptr,
	wchar_t const * const AE_RESTRICT format,
	...
) {
	va_list ap;
	va_start(ap, format);
	int const r = vaswprintf(ptr, format, ap);
	va_end(ap);
	return r;
}

int AE_API press_any_key(void) {
	puts("Press any key to continue . . .");
	// the fastest way to do this 0% CPU vs 10+% with other
	return _getch();
}

FILE * AE_API u8fopen(
	char const * const AE_RESTRICT filename,
	char const * const AE_RESTRICT mode
) {
#if AE_NO_DEFAULT_UTF8
	wchar_t * const wfilename = au8s_to_u16s_winapi(filename);
	if (wfilename == NULL) {
		return NULL;
	}
	wchar_t * const wmode = au8s_to_u16s_winapi(mode);
	if (wmode == NULL) {
		free(wfilename);
		return NULL;
	}
	FILE * const file = _wfopen(wfilename, wmode);
	free(wfilename);
	free(wmode);
	return file;
#else
	return fopen(filename, mode);
#endif
}
