// © subludicrous
// SPDX-License-Identifier: BSL-1.0

#ifndef AE_MEMORY_H
#define AE_MEMORY_H

#include <ae/base.h>
#include <stddef.h>

AE_BEGIN

AE_C_BEGIN

extern void *aligned_malloc(
    size_t total_size,
    size_t alignment
);

extern void aligned_free(void *ptr);

AE_C_END

AE_END

#endif // AE_MEMORY_H
