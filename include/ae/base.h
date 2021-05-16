// © Nikola Stepanoski
// SPDX-License-Identifier: BSL-1.0

#ifndef AE_BASE_H
#define AE_BASE_H

#ifdef _MSC_VER
    #define WINCHECK
    #ifndef _CRT_SECURE_NO_WARNINGS
        #define _CRT_SECURE_NO_WARNINGS
    #endif
#endif

#ifdef __cplusplus
    #define AE_C_BEGIN extern "C" {
    #define AE_C_END }
    
    // always use at least C++17
    #if __cplusplus > 201703L
        #define AECONSTEXPR20 constexpr
    #else
        #define AECONSTEXPR20 inline
    #endif
    #define AERESTRICT

#else
    #define AE_C_BEGIN
    #define AE_C_END
    #ifdef WINCHECK
        #define AERESTRICT __restrict
    #else
        #define AERESTRICT restrict
    #endif

#endif
    #define AEAPI __cdecl

#endif
