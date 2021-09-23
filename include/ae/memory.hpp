// © subludicrous
// SPDX-License-Identifier: BSL-1.0

#ifndef AE_MEMORY_HPP
#define AE_MEMORY_HPP

#include <ae/base.h>
#include <ae/type_traits.hpp>
#include <cstdlib>
#include <new>

namespace ae {
    // placement new wrappers

    /**
     * @brief Placement new wrapper.
     * @param buffer: Buffer to construct into.
     * @return A reference to constructed object.
    */
    template <typename T, typename ...Args>
    [[nodiscard]]
    T &ctor(void * const buffer, Args ...args) noexcept {
        return *reinterpret_cast<T *>(new (buffer) T(move(args)...));
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

    // unchecked

    template <typename T>
    [[nodiscard]]
    inline T *tmalloc(std::size_t const elems) noexcept {
        return static_cast<T *>(std::malloc(elems * sizeof(T)));
    }

    template <typename T>
    inline void tfree(T *const ptr) noexcept {
        std::free(ptr);
    }

    template <typename T>
    [[nodiscard]]
    inline T *trealloc(T *const ptr, std::size_t const elems) noexcept {
        return static_cast<T *>(std::realloc(ptr, elems * sizeof(T)));
    }

    // checked

    [[noreturn]]
    inline void abort_noexcept() noexcept {
        std::abort();
    }

    template <typename T, void(&AllocFailHandler)() noexcept = abort_noexcept>
    [[nodiscard]]
    inline T *tmalloc_s(std::size_t const amount) noexcept {
        T *const ret = tmalloc<T>(amount);
        if (!ret) {
            AllocFailHandler();
        }
        return ret;
    }

    template <typename T, void(&AllocFailHandler)() noexcept = abort_noexcept>
    [[nodiscard]]
    inline T *trealloc_s(T *const ptr, std::size_t const amount) noexcept {
        T *const ret = trealloc<T>(ptr, amount);
        if (!ret) {
            AllocFailHandler();
        }
        return ret;
    }

    template <
        typename T,
        void (&FailHandler)() noexcept,
        T *(&AllocFn)(std::size_t) noexcept =
        tmalloc_s<T, FailHandler>,
        T *(&ReAllocFn)(T *, std::size_t) noexcept = 
        trealloc_s<T, FailHandler>,
        void (&FreeFn)(T *) noexcept = tfree<T>>
    struct c_allocator {
        using value_type = T;
        using alloc_fn_t = value_type * (std::size_t) noexcept;
        using realloc_fn_t = T * (value_type *, std::size_t) noexcept;
        using free_fn_t = void(value_type *) noexcept;
        static constexpr alloc_fn_t &alloc_fn = AllocFn;
        static constexpr realloc_fn_t &realloc_fn = ReAllocFn;
        static constexpr free_fn_t &free_fn = FreeFn;
    };

    template <typename T>
    using basic_c_allocator = c_allocator<T, abort_noexcept>;
    template <typename T>
    using unchecked_allocator = c_allocator<
        T,
        abort_noexcept, // unused
        tmalloc<T>,
        trealloc<T>,
        tfree<T>>;

    template <typename T, void (&CleanFn)(T) noexcept>
    struct autoclean {
        using value_type = T;
        static constexpr decltype(auto) clean_fn = CleanFn;
        value_type value;
        [[nodiscard]]
        constexpr autoclean(T const created) noexcept {
            value = created;
        }
        constexpr ~autoclean() {
            clean_fn(value);
        }
        void operator=(autoclean const &) = delete;
        void operator=(autoclean &&) = delete;
    };

    template <typename T>
    using automem = autoclean<T *, tfree<T>>;

    [[nodiscard]]
    constexpr char const *optstr(char const *const str) noexcept {
        return str != nullptr ? str : "";
    }
}

#endif // AE_MEMORY_HPP
