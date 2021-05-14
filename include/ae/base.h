/**
* ae/base.h
* Author: subludicrous
* Licence: see LICENCE.txt
* Created on: 2021-02-02
*/

#ifndef AE_BASE_H
#define AE_BASE_H

#ifdef _MSC_VER
#define WINCHECK

#define AERESTRICT __restrict

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#else
#define AERESTRICT restrict

#endif

#ifdef __cplusplus

#define AE_C_BEGIN extern "C" {
#define AE_C_END }

#else

#define AE_C_BEGIN
#define AE_C_END

#endif

#define AEAPI __cdecl

#endif
