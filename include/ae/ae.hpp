/**
* ae/ae.hpp
* Author: subludicrous
* Licence: see LICENCE.txt
* Created on: 2021-12-16
*/

#ifndef AE_LIB_HPP
#define AE_LIB_HPP

#include <ae/stdio.h>
#include <ae/string.h>

#include <iostream>
#include <string>
#include <vector>
#include <string_view>
#include <algorithm>

using namespace std::string_view_literals;

namespace ae {

    // from ae/stdio.h
    using ::u8fopen;
    using ::press_any_key;
    using ::wpress_any_key;

    // from ae/string.h
    using ::uint_to_binstr;
    using ::auint_to_binstr;

#ifdef WINCHECK

    class win_in_u8 {
    public:
        win_in_u8(const win_in_u8&) = delete;
        win_in_u8(win_in_u8&&) = delete;
        win_in_u8() = default;

        bool good() const;

        win_in_u8& operator>>(bool& val);

        win_in_u8& operator>>(unsigned short& val);

        win_in_u8& operator>>(short& val);

        win_in_u8& operator>>(unsigned int& val);

        win_in_u8& operator>>(int& val);

        win_in_u8& operator>>(unsigned long& val);

        win_in_u8& operator>>(long& val);

        win_in_u8& operator>>(unsigned long long& val);

        win_in_u8& operator>>(long long& val);

        win_in_u8& operator>>(float& val);

        win_in_u8& operator>>(double& val);

        win_in_u8& operator>>(long double& val);

        win_in_u8& operator>>(std::string& val);

        std::string read_line();
    };

    extern win_in_u8 u8cin;

#else
    auto& u8cin = std::cin;
#endif

    [[nodiscard]]
    constexpr bool AEAPI is_power_of_2(unsigned long long const i) noexcept {
        return (i & (i - 1U)) == 0U;
    }

    [[nodiscard]]
    constexpr std::uint8_t AEAPI lobyte(std::uint16_t const word) noexcept {
        return static_cast<std::uint8_t>(word & 0x00FFU);
    }

    [[nodiscard]]
    constexpr std::uint8_t AEAPI hibyte(std::uint16_t const word) noexcept {
        return static_cast<std::uint8_t>(word >> 8U);
    }

    [[nodiscard]]
    constexpr std::uint16_t AEAPI reverse_endian(std::uint16_t const word) noexcept {
        return static_cast<std::uint16_t>((lobyte(word) << 8U) + hibyte(word));
    }

    constexpr auto REPLACEMENT = u8"\uFFFD"sv;

    constexpr bool AEAPI is_ascii(char const c) noexcept {
        if (static_cast<unsigned char>(c) & 0x80Ui8) {
            return false;
        } else return true;
    }

    constexpr bool AEAPI is_ascii(std::string_view const s) noexcept {
        return std::all_of(
            std::begin(s),
            std::end(s),
            [](decltype(s)::value_type const el) {
                return is_ascii(el);
            }
        );
    }

#ifdef WINCHECK

    [[nodiscard]]
    std::string AEAPI u16str_to_u8str(std::wstring_view s);

    [[nodiscard]]
    std::wstring AEAPI u8str_to_u16str(std::string_view s);

    class unicodization final {
    private:
        bool const args;
        int argc;
        char ** argv;
        unsigned long original_mode;
        unsigned int cp;
        int prev_mode;
    public:
        unicodization(unicodization const&) = delete;
        unicodization(unicodization&&) = delete;
        unicodization();
        unicodization(int argc, char**& argv) noexcept;
        ~unicodization();
    };

#endif

    inline void cppize(int const argc, char const * const * const argv, std::vector<std::string_view>& cppargs) {
        cppargs.reserve(static_cast<std::size_t>(argc));
        for (auto argn = 0; argn < argc; argn++) {
            cppargs.push_back(argv[argn]);
        }
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

#endif // !AE_LIB_HPP
