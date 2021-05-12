/**
* Name: aelib.cpp
* Description: The implementation for 'aelib.hpp'.
* Created on: 2020-12-09
* © 2020, 2021 subludicrous
* Licensed under the terms of the MIT licence.
*/

#include <ae/ae.hpp>

#include <stdexcept>
#include <cwchar>

namespace ae {

#ifdef WINCHECK

    bool unicode_thing::good() const {
        return std::wcin.good();
    }

    unicode_thing& unicode_thing::operator>>(bool& val) {
        std::wcin >> val;
        return *this;
    }

    unicode_thing& unicode_thing::operator>>(unsigned short& val) {
        std::wcin >> val;
        return *this;
    }
    unicode_thing& unicode_thing::operator>>(short& val) {
        std::wcin >> val;
        return *this;
    }

    unicode_thing& unicode_thing::operator>>(unsigned int& val) {
        std::wcin >> val;
        return *this;
    }

    unicode_thing& unicode_thing::operator>>(int& val) {
        std::wcin >> val;
        return *this;
    }

    unicode_thing& unicode_thing::operator>>(unsigned long& val) {
        std::wcin >> val;
        return *this;
    }

    unicode_thing& unicode_thing::operator>>(long& val) {
        std::wcin >> val;
        return *this;
    }

    unicode_thing& unicode_thing::operator>>(unsigned long long& val) {
        std::wcin >> val;
        return *this;
    }

    unicode_thing& unicode_thing::operator>>(long long& val) {
        std::wcin >> val;
        return *this;
    }

    unicode_thing& unicode_thing::operator>>(float& val) {
        std::wcin >> val;
        return *this;
    }

    unicode_thing& unicode_thing::operator>>(double& val) {
        std::wcin >> val;
        return *this;
    }

    unicode_thing& unicode_thing::operator>>(long double& val) {
        std::wcin >> val;
        return *this;
    }

    unicode_thing& unicode_thing::operator>>(std::string& val) {
        std::wstring wval;
        std::wcin >> wval;
        val = u16str_to_u8str(wval);
        return *this;
    }

    unicode_thing u8cin{};

    std::string AEAPI read_line() {
        std::wstring wstr;
        std::getline(std::wcin, wstr);
        return u16str_to_u8str(wstr);
    }

    std::wstring AEAPI u8str_to_u16str(const std::string_view s) {
        const auto res = au8str_to_u16str_winapi(s.data());
        if (res == nullptr) {
            throw std::runtime_error("Allocation error");
        } else {
            std::wstring wstr(res);
            std::free(res);
            return wstr;
        }
    }

    std::string u16str_to_u8str(const std::wstring_view s) {
        const auto res = au16str_to_u8str_winapi(s.data());
        if (res == nullptr) {
            throw std::runtime_error("Allocation error");
        } else {
            std::string str(res);
            std::free(res);
            return str;
        }
    }

    std::string AEAPI u32c_to_u8c(const char32_t codepoint) {
        char buf[5]{ 0, 0, 0, 0, 0 };
        ::u32c_to_u8c(codepoint, buf);
        return std::string(buf);
    }

#endif // _MSC_VER

    void uint_to_binstr(std::string& binstr, const std::uint64_t val, const std::size_t bits) {
        if (bits > 64) {
            throw std::logic_error("'bits' is too big.");
        }
        if (bits == 0) {
            throw std::logic_error("'bits' is zero.");
        }
        binstr.clear();
        binstr.reserve(bits);
        for (std::uint64_t i = 0x1Ui64 << (bits - 1Ui64); i; i >>= 1U) {
            binstr.push_back((val & i) ? '1' : '0');
        }
    }

    unicodization::unicodization(int const argc, char ** & argv) : args(true) {
        main_unicodize(&original_mode, &cp, &prev_mode);
        auto const u8argv = get_u8argv();
        if (u8argv == nullptr) {
            throw std::runtime_error("'get_u8argv' failed.");
        }
        argv = u8argv;
        this->argc = argc;
        this->argv = u8argv;
    }

    unicodization::unicodization() : args(false), argc(0), argv(nullptr) {
        main_unicodize(&original_mode, &cp, &prev_mode);
    }

    unicodization::~unicodization() {
        main_deunicodize(original_mode, cp, prev_mode);
        if (args) {
            free_u8argv(argc, argv);
        }
    }
}
