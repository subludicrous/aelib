// © subludicrous
// SPDX-License-Identifier: BSL-1.0

#include <ae/win_u8.h>
#include <ae/winapi_imports.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef AE_NO_DEFAULT_UTF8

char * * AE_API get_u8argv(void) {
	int argc;
	// The pointer returned by GetCommandLineW() is managed by the system
	wchar_t * * const wargv = CommandLineToArgvW(GetCommandLineW(), &argc);
	if (wargv == NULL)
	{
		return NULL;
	}

	// make char * * from wchar_t * *
	char * * const argv = calloc((1Ui64 + argc), sizeof(char *));
	if (argv == NULL) {
		return false;
	}
	bool failed = false;
	for (int i = 0; i < argc; i++) {
		char * const temp = au16s_to_u8s_winapi(wargv[i]);
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
		return NULL;
	}
	return argv;
}

void AE_API free_u8argv(int const argc, char * * const argv) {
	for (int i = 0; i < argc; i++) {
		free(argv[i]);
	}
	free(argv);
}

bool AE_API main_u8ize(
	unsigned long * const AE_RESTRICT poriginal_mode,
	unsigned int * const AE_RESTRICT pcp,
	int * const AE_RESTRICT pprev_mode,
	void ** const AE_RESTRICT phandle
) {
	// PART 1: GET UTF-8 ARGV
	// MOVED TO get_u8argv
	// PART 2: SET OUTPUT
	// save old codepage
	HANDLE const hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == NULL || hStdOut == INVALID_HANDLE_VALUE) {
		return false;
	}
	*phandle = hStdOut;

	DWORD mode = 0;
	if (!GetConsoleMode(hStdOut, &mode)) {
		return false;
	}
	// Hold original mode to restore on exit
	*poriginal_mode = mode;
	mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	if (!SetConsoleMode(hStdOut, mode)) {
		return false;
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

void AE_API main_deu8ize(
	unsigned long const original_mode,
	unsigned int const cp,
	int const prev_mode,
	void * const handle
) {
	// PART 1: FREE UTF-8 ARGV
	// moved
	// PART 2: RESET OUTPUT
	SetConsoleMode(handle, original_mode);
	SetConsoleOutputCP(cp);
	// PART 3: RESET OUTPUT
	(void) _setmode(_fileno(stdin), prev_mode);
}

//todo
char ** AE_API get_u8envp(void) {
	return NULL;
}

void AE_API free_u8envp(char ** envp) {
	char * const * envp2 = envp;
	while (true) {
		char * const env = *envp;
		if (!env) break;
		free(env);
		envp2++;
	}
	free(envp);
}

char * AE_API au16s_to_u8s_winapi(wchar_t const * const utf16str) {
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

wchar_t * AE_API au8s_to_u16s_winapi(char const * const utf8str) {
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
