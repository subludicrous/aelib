/**
* Name: aelib.hpp
* Description: Aesthetic library main header.
* Created on: 2020-12-16
* © 2020, 2021 subludicrous
* Licensed under the terms of the MIT licence.
*/

#ifndef AE_LIB_HPP
#define AE_LIB_HPP

#include <ae/stdio.h>
#include <ae/string.h>

#include <iostream>
#include <string>
#include <vector>
#include <string_view>

namespace aelib {

    // from ae/stdio.h
    using ::u8fopen;
    using ::press_any_key;
    using ::wpress_any_key;

    // from ae/string.h
    using ::uint_to_binstr;
    using ::auint_to_binstr;
    using ::u8c_to_u32c;
    using ::u32c_to_u8c;

#ifdef WINCHECK

    class unicode_thing {
    public:
        unicode_thing(const unicode_thing&) = delete;
        unicode_thing(unicode_thing&&) = delete;
        unicode_thing() = default;

        bool good() const;

        unicode_thing& operator>>(bool& val);

        unicode_thing& operator>>(unsigned short& val);

        unicode_thing& operator>>(short& val);

        unicode_thing& operator>>(unsigned int& val);

        unicode_thing& operator>>(int& val);

        unicode_thing& operator>>(unsigned long& val);

        unicode_thing& operator>>(long& val);

        unicode_thing& operator>>(unsigned long long& val);

        unicode_thing& operator>>(long long& val);

        unicode_thing& operator>>(float& val);

        unicode_thing& operator>>(double& val);

        unicode_thing& operator>>(long double& val);

        unicode_thing& operator>>(std::string& val);
    };

    extern unicode_thing u8cin;

    std::string AEAPI read_line();

#else
    auto& u8cin = std::cin;
    using std::getline;
#endif

    [[nodiscard]]
    constexpr bool AEAPI is_power_of_2(unsigned int const i) noexcept {
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

    constexpr auto REPLACEMENT = u8"\uFFFD";

    constexpr bool AEAPI is_ascii(const char c) noexcept {
        if (static_cast<unsigned char>(c) & 0x80Ui8) {
            return false;
        } else return true;
    }

    constexpr bool AEAPI is_ascii(const std::string_view s) noexcept {
        for (const char x : s) {
            if (!is_ascii(x)) {
                return false;
            }
        }
        return true;
    }

    constexpr std::size_t AEAPI u8bytes(const char c) noexcept {
        std::size_t u8s{};
        for (auto x = static_cast<unsigned char>(c); x & 0x80Ui8; x <<= 1U) {
            u8s++;
        }
        return u8s;
    }

    void AEAPI uint_to_binstr(std::string& binstr, std::uint64_t val, std::size_t bits);

    inline void AEAPI uint_to_binstr(std::string& binstr, std::uint8_t val) {
        uint_to_binstr(binstr, val, 8);
    }

    inline void AEAPI uint_to_binstr(std::string& binstr, std::uint16_t val) {
        uint_to_binstr(binstr, val, 16);
    }

    inline void AEAPI uint_to_binstr(std::string& binstr, std::uint32_t val) {
        uint_to_binstr(binstr, val, 32);
    }

    inline void AEAPI uint_to_binstr(std::string& binstr, std::uint64_t val) {
        uint_to_binstr(binstr, val, 64);
    }

    /// <summary>
    /// Converts a UTF-32 character to UTF-8.
    /// </summary>
    /// <param name="code">The UTF-32 character.</param>
    /// <returns>A 'std::string' holding the UTF-8 character.</returns>
    [[nodiscard]]
    std::string AEAPI u32c_to_u8c(char32_t code);

#ifdef WINCHECK

    [[nodiscard]]
    std::string AEAPI u16str_to_u8str(std::wstring_view s);

    [[nodiscard]]
    std::wstring AEAPI u8str_to_u16str(std::string_view s);

    class unicodization {
    private:
        const bool args;
        int argc;
        char **argv;
        unsigned long original_mode;
        unsigned int cp;
        int prev_mode;
    public:
        unicodization(const unicodization&) = delete;
        unicodization(unicodization&&) = delete;
        unicodization();
        unicodization(int argc, char**& argv);
        ~unicodization();
    };

#endif

    inline void cppize(int const argc, const char * const * const argv, std::vector<std::string_view>& cppargs) {
        cppargs.reserve(static_cast<std::size_t>(argc));
        for (auto argn = 0; argn < argc; argn++) {
            cppargs.push_back(argv[argn]);
        }
    }

    template<size_t sz>
    inline void print_buf(const char(&str)[sz]) {
        for (auto elem = 0U; elem < sz; elem++) {
            auto const c = static_cast<unsigned char>(str[elem]);
            const char cp = std::isalnum(c) ? c : '.';
            std::printf("Elem. %02u: 0x%02x\n", elem, c);
        }
    }

    inline void print_buf(const std::string_view str) {
        for (auto elem = 0U; elem < str.size(); elem++) {
            auto const c = static_cast<unsigned char>(str[elem]);
            std::printf("Elem. %02u: 0x%02x\n", elem, c);
        }
    }

    template<size_t sz>
    inline void print_binbuf(const char(&str)[sz]) {
        char bbuf[9]{};
        for (auto elem = 0U; elem < sz; elem++) {
            auto const c = static_cast<unsigned char>(str[elem]);
            aelib::uint_to_binstr(bbuf, c, 8);
            std::printf("Elem. %02u: 0b%s\n", elem, bbuf);
        }
    }

    inline void print_binbuf(const std::string_view str) {
        char bbuf[9]{};
        for (auto elem = 0U; elem < str.size(); elem++) {
            auto const c = static_cast<unsigned char>(str[elem]);
            aelib::uint_to_binstr(bbuf, c, 8);
            std::printf("Elem. %02u: 0b%s\n", elem, bbuf);
        }
    }

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
}

#endif // !AE_LIB_HPP
