// © subludicrous
// SPDX-License-Identifier: BSL-1.0

#ifndef AE_NEW_HPP
#define AE_NEW_HPP

#include <ae/base.h>
#include <new>

namespace ae {
    /**
     * @brief Placement new wrapper.
     * @param buffer: Buffer to construct into.
     * @return A reference to constructed object.
    */
    template <typename T>
    [[nodiscard]]
    T &ctor(void * const buffer) noexcept {
        return *reinterpret_cast<T *>(new (buffer) T);
    }

    /**
     * @brief Wrapper for ~T();
     * @param val
     * @return
    */
    template <typename T>
    void dtor(T &val) noexcept {
        val.~T();
    }

    /**
     * @brief Arrays have no pseudo-dtor call ~T();
     * @param val: A reference to an array.
    */
    template <typename T, std::size_t N>
    void dtor(T(&val)[N]) {
        for (auto i = N; i > 0u; ) {
            --i;
            dtor(val[i]);
        }
    }
}

#endif
