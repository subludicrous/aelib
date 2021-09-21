// © subludicrous
// SPDX-License-Identifier: BSL-1.0

#ifndef AE_TYPE_TRAITS_HPP
#define AE_TYPE_TRAITS_HPP

// ad hoc type traits

#include <ae/base.h>

namespace ae {
    template <typename T, T Val>
    struct integral_constant {
        using value_type = T;
        using type = integral_constant;

        static constexpr value_type value = Val;

        [[nodiscard]]
        constexpr operator value_type() const noexcept {
            return value;
        }

        [[nodiscard]]
        constexpr value_type operator()() const noexcept {
            return value;
        }
    };

    template <bool Val>
    using bool_constant = integral_constant<bool, Val>;
    using true_type = bool_constant<true>;
    using false_type = bool_constant<false>;

    // ENABLE IF
    template <bool Cond, typename T = void>
    struct enable_if {};

    template <typename T>
    struct enable_if<true, T> {
        using type = T;
    };

    // IS SAME
    template <typename T1, typename T2>
    constexpr bool is_same_v = false;

    template <typename T>
    constexpr bool is_same_v<T, T> = true;

    template <typename T1, typename T2>
    struct is_same : bool_constant<is_same_v<T1, T2>> {};

    // IS LVALUE REFERENCE
    template <typename T>
    constexpr bool is_lvalue_reference_v = false;

    template <typename T>
    constexpr bool is_lvalue_reference_v<T &> = true;

    template <typename T>
    struct is_lvalue_reference : bool_constant<is_lvalue_reference_v<T>> {};
    
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

    // FORWARD, MOVE
    template <typename T>
    constexpr T &&forward(remove_reference_t<T> &thing) noexcept {
        return static_cast<T &&>(thing);
    }

    template <typename T>
    constexpr T &&forward(remove_reference_t<T> &&thing) noexcept {
        static_assert(!is_lvalue_reference_v<T>,
            "T mustn't be an lvalue reference.");
        return static_cast<T &&>(thing);
    }

    template<typename T>
    constexpr remove_reference_t<T> &&move(T &&thing) noexcept {
        return static_cast<remove_reference_t<T> &&>(thing);
    }
}

#endif // AE_TYPE_TRAITS_HPP
