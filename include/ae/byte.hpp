// © subludicrous
// SPDX-License-Identifier: BSL-1.0

#ifndef AE_BYTE_HPP
#define AE_BYTE_HPP

#include <concepts>

namespace ae {
    class byte {
    public:
        using type = unsigned char;
        using calc_type = unsigned int;
    private:
        type m_b;
    public:
        [[nodiscard]]
        byte() noexcept = default;
        [[nodiscard]]
        constexpr byte(calc_type const bval) noexcept {
            m_b = static_cast<type>(bval);
        }
        [[nodiscard]]
        constexpr byte(byte const& b) noexcept = default;
        // don't move this trivial type
        byte(byte &&) = delete;
        byte(byte const &&) = delete;
        constexpr byte& operator=(byte const& b) noexcept = default;

        template <std::integral T>
        [[nodiscard]]
        constexpr operator T() const noexcept {
            return static_cast<T>(m_b);
        }
        [[nodiscard]]
        constexpr byte operator<<(
            std::integral auto const shift
        ) const noexcept {
            return calc_type(m_b) << shift;
        }
        [[nodiscard]]
        constexpr byte operator>>(
            std::integral auto const shift
        ) const noexcept {
            return calc_type(m_b) >> shift;
        }
        [[nodiscard]]
        constexpr byte operator&(byte const other) const noexcept {
            return calc_type(m_b) & other.m_b;
        }
        [[nodiscard]]
        constexpr byte operator|(byte const other) const noexcept {
            return calc_type(m_b) | other.m_b;
        }
        [[nodiscard]]
        constexpr byte operator xor(byte const other) const noexcept {
            return calc_type(m_b) xor other.m_b;
        }
        [[nodiscard]]
        constexpr byte operator compl() const noexcept {
            return compl calc_type(m_b);
        }
        [[nodiscard]]
        constexpr byte& operator<<=(std::integral auto const shift) noexcept {
            *this = *this << shift;
            return *this;
        }
        [[nodiscard]]
        constexpr byte& operator>>=(std::integral auto const shift) noexcept {
            *this = *this >> shift;
            return *this;
        }
        [[nodiscard]]
        constexpr byte& operator&=(byte const other) noexcept {
            *this = *this & other;
            return *this;
        }
        [[nodiscard]]
        constexpr byte& operator|=(byte const other) noexcept {
            *this = *this | other;
            return *this;
        }
        [[nodiscard]]
        constexpr byte& operator xor_eq(byte const other) noexcept {
            *this = *this xor other;
            return *this;
        }
    };

    inline namespace literals {
        [[nodiscard]]
        constexpr byte operator""_b(unsigned long long int val) {
            return static_cast<byte>(val);
        }
    }
}

#endif
