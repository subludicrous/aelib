// © subludicrous
// SPDX-License-Identifier: BSL-1.0

// miscellaneous

#ifndef UTIL_HPP
#define UTIL_HPP

#include <string_view>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cctype>

namespace ae {
    // doesn't null terminate
    template <std::size_t bits>
    constexpr void int_to_bin(
        char (&bbuf)[bits + 1u],
        std::uintmax_t const val
    ) {
        static_assert(bits > 1u && bits <= (sizeof (std::uintmax_t) * 8));
        char * binstr = bbuf;
        for (auto i = std::uintmax_t{ 0x1u } << (bits - 1u); i; i >>= 1u) {
            *binstr = (val & i) ? '1' : '0';
            binstr++;
        }
    }

    // replace with std's in C++23
    template <typename ch>
    [[nodiscard]]
    constexpr bool contains(
        std::basic_string_view<ch> const sv,
        std::basic_string_view<ch> const what
    ) noexcept {
        return sv.find(what) != sv.npos;
    }

    // replace with std's in C++20
    template <typename ch>
    [[nodiscard]]
    constexpr bool starts_with(
        std::basic_string_view<ch> const sv,
        std::basic_string_view<ch> const prefix
    ) {
        return sv.substr(0, prefix.size()) == prefix;
    }

    [[nodiscard]]
    constexpr bool is_power_of_2(std::uintmax_t const i) noexcept {
        return i != 0u && (i & (i - 1u)) == 0u;
    }

    [[nodiscard]]
    constexpr std::uint8_t lobyte(std::uint16_t const word) noexcept {
        return static_cast<std::uint8_t>(word & 0x00FFu);
    }

    [[nodiscard]]
    constexpr std::uint8_t hibyte(std::uint16_t const word) noexcept {
        return static_cast<std::uint8_t>(word >> 8u);
    }

    [[nodiscard]]
    constexpr std::uint16_t reverse_endian(std::uint16_t const word) noexcept {
        return static_cast<std::uint16_t>((lobyte(word) << 8u) + hibyte(word));
    }

    template <std::size_t sz>
    inline void print_hexbuf(char const (&str)[sz]) {
        for (auto elem = 0U; elem < sz; elem++) {
            auto const c = static_cast<unsigned char>(str[elem]);
            char const cp = std::isalnum(c) ? c : '.';
            std::printf("Elem. %02u: 0x%02x\n", elem, c);
        }
    }

    inline void print_hexbuf(std::string_view const str) {
        for (auto elem = 0U; elem < str.size(); elem++) {
            auto const c = static_cast<unsigned char>(str[elem]);
            std::printf("Elem. %02u: 0x%02x\n", elem, c);
        }
    }

    template <std::size_t sz>
    inline void print_binbuf(char const (&str)[sz]) {
        char bbuf[9];
        bbuf[8] = '\0';
        for (auto elem = 0U; elem < sz; elem++) {
            auto const c = static_cast<unsigned char>(str[elem]);
            int_to_bin<8>(bbuf, c);
            std::printf("Elem. %02u: 0b%s\n", elem, bbuf);
        }
    }

    inline void print_binbuf(std::string_view const str) {
        char bbuf[9];
        bbuf[8] = '\0';
        for (auto elem = 0U; elem < str.size(); elem++) {
            auto const c = static_cast<unsigned char>(str[elem]);
            int_to_bin<8>(bbuf, c);
            std::printf("Elem. %02u: 0b%s\n", elem, bbuf);
        }
    }
}

#endif
