// © subludicrous
// SPDX-License-Identifier: BSL-1.0

#include <ae/base.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

static bool is_power_of_two(size_t const s) {
    return (s != 0u) && (s & (s - 1u)) == 0;
}

extern void *AE_API aligned_malloc(
    size_t const total_size,
    size_t const alignment
) {
    if (!is_power_of_two(alignment)) {
        return NULL;
    }

    uintptr_t up = (uintptr_t) malloc(total_size + alignment);
    uintptr_t const orig = up;
    if (!up) {
        return NULL;
    }
    // align to bottom
    up &= (uintptr_t) (0u - alignment);
    // add, so it is aligned to higher address, that we actually own
    up += alignment;
    uintptr_t *const to_dispatch = (uintptr_t *) up;
    // store original ptr into [-1]
    *(to_dispatch - 1) = orig;
    return to_dispatch;
}

extern void AE_API aligned_free(void *const ptr) {
    uintptr_t *pactual = ptr;
    --pactual;
    free((void *) *pactual);
}
