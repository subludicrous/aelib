// © subludicrous
// SPDX-License-Identifier: BSL-1.0

#ifndef AE_TYPE_TRAITS_HPP
#define AE_TYPE_TRAITS_HPP

// ad hoc type traits

#include <ae/base.h>

namespace ae {
    // IS LVALUE REFERENCE
    template <typename T>
    struct is_lvalue_reference {
        static constexpr bool value = false;
    };

    template <typename T>
    struct is_lvalue_reference<T &> {
        static constexpr bool value = true;
    };

    template <typename T>
    constexpr bool is_lvalue_reference_v = is_lvalue_reference<T>::value;
    
    // REMOVE REFERENCE
    template <typename T>
    struct remove_reference {
        using type = T;
    };

    template <typename T>
    struct remove_reference<T &> {
        using type = T;
    };

    template <typename T>
    struct remove_reference<T &&> {
        using type = T;
    };

    template <typename T>
    using remove_reference_t = typename remove_reference<T>::type;

    template <typename T>
    constexpr T &&forward(remove_reference_t<T> &thing) noexcept {
        return static_cast<T &&>(thing);
    }

    template <typename T>
    constexpr T &&forward(remove_reference_t<T> &&thing) noexcept {
        static_assert(is_lvalue_reference_v<T>,
            "T mustn't be an lvalue reference.");
        return static_cast<T &&>(thing);
    }

    template<typename T>
    constexpr remove_reference_t<T> &&move(T &&thing) noexcept {
        static_cast<remove_reference_t<T> &&>(thing);
    }
}

#endif // AE_TYPE_TRAITS_HPP
