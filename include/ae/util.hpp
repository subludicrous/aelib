/**
* ae/util.hpp
* Author: subludicrous
* Licence: see LICENCE.txt
* Created on: 2021-05-11
*/

#ifndef AE_UTIL_HPP
#define AE_UTIL_HPP

#include <string_view>
#include <ae/string.h>

namespace ae {
    // replace with std's in C++23
    template<typename ch>
    [[nodiscard]]
    constexpr bool contains(std::basic_string_view<ch> const sv, std::basic_string_view<ch> const what) noexcept {
        return sv.find(what) != sv.npos;
    }

    // replace with std's in C++20
    template<typename ch>
    [[nodiscard]]
    constexpr bool starts_with(std::basic_string_view<ch> const sv, std::basic_string_view<ch> const prefix) {
        return sv.substr(0, prefix.size()) == prefix;
    }

    [[nodiscard]]
    constexpr bool is_power_of_2(unsigned long long const i) noexcept {
        return (i & (i - 1U)) == 0U;
    }

    [[nodiscard]]
    constexpr std::uint8_t lobyte(std::uint16_t const word) noexcept {
        return static_cast<std::uint8_t>(word & 0x00FFU);
    }

    [[nodiscard]]
    constexpr std::uint8_t hibyte(std::uint16_t const word) noexcept {
        return static_cast<std::uint8_t>(word >> 8U);
    }

    [[nodiscard]]
    constexpr std::uint16_t reverse_endian(std::uint16_t const word) noexcept {
        return static_cast<std::uint16_t>((lobyte(word) << 8U) + hibyte(word));
    }

    template<size_t sz>
    inline void print_hexbuf(char const (&str)[sz]) {
        for (auto elem = 0U; elem < sz; elem++) {
            auto const c = static_cast<unsigned char>(str[elem]);
            const char cp = std::isalnum(c) ? c : '.';
            std::printf("Elem. %02u: 0x%02x\n", elem, c);
        }
    }

    inline void print_hexbuf(std::string_view const str) {
        for (auto elem = 0U; elem < str.size(); elem++) {
            auto const c = static_cast<unsigned char>(str[elem]);
            std::printf("Elem. %02u: 0x%02x\n", elem, c);
        }
    }

    template<size_t sz>
    inline void print_binbuf(char const (&str)[sz]) {
        char bbuf[9]{};
        for (auto elem = 0U; elem < sz; elem++) {
            auto const c = static_cast<unsigned char>(str[elem]);
            ae::uint_to_binstr(bbuf, c, 8);
            std::printf("Elem. %02u: 0b%s\n", elem, bbuf);
        }
    }

    inline void print_binbuf(std::string_view const str) {
        char bbuf[9]{};
        for (auto elem = 0U; elem < str.size(); elem++) {
            auto const c = static_cast<unsigned char>(str[elem]);
            ae::uint_to_binstr(bbuf, c, 8);
            std::printf("Elem. %02u: 0b%s\n", elem, bbuf);
        }
    }
}

#endif
