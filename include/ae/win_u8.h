// © subludicrous
// SPDX-License-Identifier: BSL-1.0

#ifndef AE_WIN_U8_H
#define AE_WIN_U8_H

#include <ae/base.h>
#ifdef __cplusplus
#include <string>
#include <string_view>
#else
#include <wctype.h>
#endif

#ifdef AE_NO_DEFAULT_UTF8

AE_BEGIN

AE_C_BEGIN

char * AE_API au16s_to_u8s_winapi(wchar_t const * utf16str);

wchar_t * AE_API au8s_to_u16s_winapi(char const * utf8str);

bool AE_API main_u8ize(
	unsigned long * AE_RESTRICT poriginal_mode,
	unsigned int * AE_RESTRICT pcp,
	int * AE_RESTRICT pprev_mode,
	void * * AE_RESTRICT phandle
);

void AE_API main_deu8ize(
	unsigned long original_mode,
	unsigned int cp,
	int prev_mode,
	void * handle
);

char * * AE_API get_u8argv(void);

void AE_API free_u8argv(int argc, char * * argv);

// todo also u8set, get etc

char * * AE_API get_u8envp(void);

void AE_API free_u8envp(char * * envp);

AE_C_END

#ifdef __cplusplus

[[nodiscard]]
std::string AE_API u16_to_u8(std::wstring_view s);

[[nodiscard]]
std::wstring AE_API u8_to_u16(std::string_view s);

#endif // __cplusplus

AE_END

#endif // AE_NO_DEFAULT_UTF8

#endif
