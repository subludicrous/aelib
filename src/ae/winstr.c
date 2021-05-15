/**
* ae/win_u8.h impl.
* Author: subludicrous
* Licence: see LICENCE.txt
* Created on: 2021-05-15
*/

#include <ae/winspec.h>
#include <winapi_imports.h>
#include <stdlib.h>

#ifdef WINCHECK

char * AEAPI au16s_to_u8s_winapi(wchar_t const * const utf16str) {
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

wchar_t * AEAPI au8s_to_u16s_winapi(char const * const utf8str) {
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