/**
* Name: aestring.h
* Description: A Unicode® (among other things) string library.
* Created on: 2021-02-02
* © 2021 subludicrous
* Licensed under the terms of the MIT licence.
*/

#ifndef AE_STRING_H
#define AE_STRING_H

#include <ae/base.h>
#include <stdint.h>

AE_C_BEGIN

int AEAPI uint_to_binstr(char * binstr, uint64_t val, size_t bits);

char * AEAPI auint_to_binstr(uint64_t input, size_t bits);

AE_C_END

#ifdef __cplusplus

namespace ae {
    using ::uint_to_binstr;
    using ::auint_to_binstr;
}

#endif

#endif
