// © subludicrous
// SPDX-License-Identifier: BSL-1.0

#ifndef AE_BASE_H
#define AE_BASE_H

#ifdef __cplusplus
    #define AE_C_BEGIN extern "C" {
    #define AE_C_END }
    
    #if __cplusplus > 201703L
        #define AECONSTEXPR20 constexpr
    #elif __cplusplus == 201703L
        #define AECONSTEXPR20 inline
    #else
        #error "Requires C++17 or later"
    #endif

    #define AE_STD ::std::
    #define AE_BEGIN namespace ae {
    #define AE_END }

    #define AE_RESTRICT __restrict

#else
    #include <stdbool.h>

    #define AE_C_BEGIN
    #define AE_C_END

    #define AE_STD
    #define AE_BEGIN
    #define AE_END

    #define AE_RESTRICT restrict

#endif
    #define AE_API __cdecl

#endif

#ifdef _MSC_VER
    #define AE_NO_DEFAULT_UTF8 true
    #ifndef _CRT_SECURE_NO_WARNINGS
        #define _CRT_SECURE_NO_WARNINGS
    #endif
    #ifndef _CRT_NONSTDC_NO_WARNINGS
        #define _CRT_NONSTDC_NO_WARNINGS
    #endif
#endif
