// © subludicrous
// SPDX-License-Identifier: BSL-1.0

#include <ae/base.h>

#ifndef __cplusplus
    #include <stddef.h>
#else
    #include <cstdlib>
#endif

AE_BEGIN

AE_C_BEGIN

void *aligned_malloc(AE_STD size_t total_size, AE_STD size_t alignment);

void aligned_free(void *ptr);

AE_C_END

#ifdef __cplusplus

template <typename T, std::size_t amount = 1>
[[nodiscard]]
inline T *pmalloc() noexcept {
    return static_cast<T *>(std::malloc(amount * sizeof(T)));
}

template <typename T>
inline void pfree(T *const ptr) noexcept {
    std::free(ptr);
}

template <
    typename T,
    T *(&alloc)() noexcept = pmalloc<T>,
    void (&dealloc)(T *) noexcept = pfree<T>
>
class automem {
public:
    using value_type = T;
    using pointer_type = value_type *;
    pointer_type value;
    [[nodiscard]]
    constexpr automem() noexcept : value(alloc()) {}
    constexpr ~automem() {
        dealloc(value);
    }
    [[nodiscard]]
    explicit constexpr operator pointer_type() const noexcept {
        return value;
    }
    void operator=(automem const &) = delete;
    void operator=(automem &&) = delete;
};

template <typename T, void (&fnclean)(T) noexcept = pfree>
class autoclean {
public:
    using value_type = T;
    value_type value;
    [[nodiscard]]
    constexpr autoclean(T const created) noexcept {
        value = created;
    }
    constexpr ~autoclean() {
        fnclean(value);
    }
    [[nodiscard]]
    explicit constexpr operator value_type() const noexcept {
        return value;
    }
    void operator=(autoclean const &) = delete;
    void operator=(autoclean &&) = delete;
};

[[nodiscard]]
constexpr char const *optstr(char const *const str) noexcept {
    return str != nullptr ? str : "";
}

#endif 

AE_END
