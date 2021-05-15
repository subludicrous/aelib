/**
* ae/winspec.h
* Author: subludicrous
* Licence: see LICENCE.txt
* Created on: 2021-05-15
*/

#ifndef AE_WINSPEC_H
#define AE_WINSPEC_H

#include <ae/base.h>

#ifdef WINCHECK

#include <uchar.h>
#include <stdbool.h>

AE_C_BEGIN

char * AEAPI au16str_to_u8str_winapi(const wchar_t * utf16str);

wchar_t * AEAPI au8str_to_u16str_winapi(const char * utf8str);

bool AEAPI main_u8ize(
	unsigned long * const AERESTRICT poriginal_mode,
	unsigned int * AERESTRICT pcp,
	int * AERESTRICT pprev_mode
);

void AEAPI main_deu8ize(
	unsigned long original_mode,
	unsigned int cp,
	int prev_mode
);

char ** AEAPI get_u8argv(void);

void AEAPI free_u8argv(int argc, char ** argv);

// todo also u8set, get etc

char ** AEAPI get_u8envp(void);

void AEAPI free_u8envp(char ** envp);

AE_C_END

#endif

#endif
