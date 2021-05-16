/**
* ae/win_u8.h impl.
* Author: subludicrous
* Licence: see LICENCE.txt
* Created on: 2021-05-15
*/

#include <ae/winspec.h>
#include <winapi_imports.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef WINCHECK

char * * AEAPI get_u8argv(void) {
	int argc;
	// The pointer returned by GetCommandLineW() is managed by the system
	wchar_t * * const wargv = CommandLineToArgvW(GetCommandLineW(), &argc);
	if (wargv == NULL)
	{
		return false;
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
		return false;
	}
	return argv;
}

void AEAPI free_u8argv(int const argc, char * * const argv) {
	for (int i = 0; i < argc; i++) {
		free(argv[i]);
	}
	free(argv);
}

bool AEAPI main_u8ize(
	unsigned long * const AERESTRICT poriginal_mode,
	unsigned int * const AERESTRICT pcp,
	int * const AERESTRICT pprev_mode,
	void ** const AERESTRICT phandle
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

void AEAPI main_deu8ize(
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
char ** AEAPI get_u8envp(void) {
	return NULL;
}

void AEAPI free_u8envp(char ** envp) {
	char * const * envp2 = envp;
	while (true) {
		char * const env = *envp;
		if (!env) break;
		free(env);
		envp2++;
	}
	free(envp);
}

#endif
