/**
* Name: aebase.h
* Description: A base header for aelib.
* Created on: 2021-02-02
* © 2021 subludicrous
* Licensed under the terms of the MIT licence.
*/

#ifndef AELIB_BASE_H
#define AELIB_BASE_H

#ifdef _MSC_VER
#define WINCHECK
#endif

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif // !_CRT_SECURE_NO_WARNINGS

#ifdef __cplusplus
#define AELIB_C_BEGIN extern "C" {
#else
#define AELIB_C_BEGIN
#endif

#ifdef __cplusplus
#define AELIB_C_END }
#else
#define AELIB_C_END
#endif

#define AEAPI __cdecl

#ifdef _MSC_VER
#define AERESTRICT __restrict
#else
#define AERESTRICT restrict
#endif

#endif
