// © subludicrous
// SPDX-License-Identifier: BSL-1.0

#include <ae/base.h>

#ifndef __cplusplus
    #include <stddef.h>
#else
namespace std {
    // ad hoc
    using size_t = decltype(sizeof 0);
}
#endif

AE_BEGIN

AE_C_BEGIN

void *aligned_malloc(AE_STD size_t total_size, AE_STD size_t alignment);

void aligned_free(void *ptr);

AE_C_END

AE_END
