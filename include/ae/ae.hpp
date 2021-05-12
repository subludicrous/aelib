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

    constexpr std::size_t AEAPI u8bytes(const char c) noexcept {
        std::size_t u8s{};
        for (auto x = static_cast<unsigned char>(c); x & 0x80Ui8; x <<= 1U) {
            u8s++;
        }
        return u8s;
    }

    void AEAPI uint_to_binstr(std::string& binstr, std::uint64_t val, std::size_t bits);

    inline void AEAPI uint_to_binstr(std::string& binstr, std::uint8_t const val) {
        uint_to_binstr(binstr, val, 8);
    }

    inline void AEAPI uint_to_binstr(std::string& binstr, std::uint16_t const val) {
        uint_to_binstr(binstr, val, 16);
    }

    inline void AEAPI uint_to_binstr(std::string& binstr, std::uint32_t const val) {
        uint_to_binstr(binstr, val, 32);
    }

    inline void AEAPI uint_to_binstr(std::string& binstr, std::uint64_t const val) {
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
        unicodization(int argc, char**& argv);
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
