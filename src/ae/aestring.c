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
#include <fcntl.h>
#include <io.h>

int AEAPI uint_to_binstr(char *binstr, const uint64_t val, const size_t bits) {
	if (!binstr || !bits || bits > 64Ui64) {
		return EINVAL;
	}
	for (uint64_t i = 0x1Ui64 << (bits - 1Ui64); i; i >>= 1U) {
		*binstr = (val & i) ? '1' : '0';
		binstr++;
	}
	return 0;
}

char * AEAPI auint_to_binstr(const uint64_t input, const size_t bits) {
	if (bits > 64i64) return NULL;

	char * const output = malloc(bits + 1Ui64);
	if (!output) {
		return NULL;
	}
	output[bits] = '\0'; // null terminator 
	// 1 << 31 = 0x80 00 00 00
	char *p = output;
	for (uint64_t i = 0x1Ui64 << (bits - 1); i; i >>= 1) {
		*p = (input & i) ? '1' : '0';
		p++;
	}
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
	const size_t req_size = (size_t) MultiByteToWideChar(CP_UTF8, 0, utf8str, -1, NULL, 0);
	wchar_t * const utf16str = malloc(sizeof(wchar_t) * req_size);
	if (utf16str == NULL) {
		return NULL;
	}
	const int written = MultiByteToWideChar(CP_UTF8, 0, utf8str, -1, utf16str, (int) req_size);
	if ((size_t) written != req_size) {
		free(utf16str);
		return NULL;
	}
	return utf16str;
}

char ** AEAPI get_u8argv(void) {
	int argc;
	// The pointer returned by GetCommandLineW() is managed by the system
	wchar_t **const wargv = CommandLineToArgvW(GetCommandLineW(), &argc);
	if (wargv == NULL)
	{
		return false;
	}

	// make char ** from wchar_t **
	char **const argv = calloc((1Ui64 + argc), sizeof(char *));
	if (argv == NULL) {
		return false;
	}
	bool failed = false;
	for (int i = 0; i < argc; i++) {
		char *const temp = au16str_to_u8str_winapi(wargv[i]);
		if (temp == NULL) {
			failed = true;
			break;
		} else {
			argv[i] = temp;
		}
	}
	// single call to LocalFree required to free
	LocalFree(wargv);
	if (failed) {
		// free all arguments allocated before the fail
		free_u8argv(argc, argv);
		return false;
	}
	return argv;
}

void AEAPI free_u8argv(int const argc, char **const argv) {
	for (int i = 0; i < argc; i++) {
		free(argv[i]);
	}
	free(argv);
}

bool AEAPI main_unicodize(
	unsigned long * const AERESTRICT poriginal_mode,
	unsigned int * const AERESTRICT pcp,
	int * const AERESTRICT pprev_mode)
{
	// PART 1: GET UTF-8 ARGV
	// MOVED TO get_u8argv
	// PART 2: SET OUTPUT
	// save old codepage
	const HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == NULL || hStdOut == INVALID_HANDLE_VALUE) {
		return false;
	}

	DWORD mode = 0;
	if (!GetConsoleMode(hStdOut, &mode)) {
		return false;
	}
	// Hold original mode to restore on exit
	*poriginal_mode = mode;
	mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	if (!SetConsoleMode(hStdOut, mode)) {
	}

	*pcp = GetConsoleOutputCP();
	if (!SetConsoleOutputCP(CP_UTF8)) {
		SetConsoleMode(hStdOut, *poriginal_mode); // reset mode
		return false;
	}

	// PART 3: SET INPUT

	*pprev_mode = _setmode(_fileno(stdin), _O_U16TEXT);

	return true;
}

void AEAPI main_deunicodize(
	unsigned long const original_mode,
	unsigned int const cp,
	int const prev_mode
) {
	// PART 1: FREE UTF-8 ARGV
	// moved
	// PART 2: RESET OUTPUT
	const HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleMode(hStdOut, original_mode);
	SetConsoleOutputCP(cp);
	// PART 3: RESET OUTPUT
	_setmode(_fileno(stdin), prev_mode);
}

//todo
char ** AEAPI get_u8envp(void)
{
	return NULL;
}

void AEAPI free_u8envp(char ** envp)
{
	char * env;
	while (env = *envp) {
		free(env);
		envp++;
	}
}

#endif

// a note on format
/** UTF-8
* 0x000000 - 0x00007F 1 byte
* 0x000080 - 0x0007FF 2 bytes
* 0x000800 - 0x00FFFF 3 bytes
* 0x010000 - 0x10FFFF 4 bytes
*/
