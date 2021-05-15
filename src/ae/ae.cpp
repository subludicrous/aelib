/**
* Name: aelib.cpp
* Description: The implementation for 'aelib.hpp'.
* Created on: 2020-12-09
* © 2020, 2021 subludicrous
* Licensed under the terms of the MIT licence.
*/

#include <ae/ae.hpp>
#include <ae/winspec.h>
#include <stdexcept>
#include <cwchar>

namespace ae {

#ifdef WINCHECK

    bool win_in_u8::good() const {
        return std::wcin.good();
    }

    win_in_u8& win_in_u8::operator>>(bool& val) {
        std::wcin >> val;
        return *this;
    }

    win_in_u8& win_in_u8::operator>>(unsigned short& val) {
        std::wcin >> val;
        return *this;
    }
    win_in_u8& win_in_u8::operator>>(short& val) {
        std::wcin >> val;
        return *this;
    }

    win_in_u8& win_in_u8::operator>>(unsigned int& val) {
        std::wcin >> val;
        return *this;
    }

    win_in_u8& win_in_u8::operator>>(int& val) {
        std::wcin >> val;
        return *this;
    }

    win_in_u8& win_in_u8::operator>>(unsigned long& val) {
        std::wcin >> val;
        return *this;
    }

    win_in_u8& win_in_u8::operator>>(long& val) {
        std::wcin >> val;
        return *this;
    }

    win_in_u8& win_in_u8::operator>>(unsigned long long& val) {
        std::wcin >> val;
        return *this;
    }

    win_in_u8& win_in_u8::operator>>(long long& val) {
        std::wcin >> val;
        return *this;
    }

    win_in_u8& win_in_u8::operator>>(float& val) {
        std::wcin >> val;
        return *this;
    }

    win_in_u8& win_in_u8::operator>>(double& val) {
        std::wcin >> val;
        return *this;
    }

    win_in_u8& win_in_u8::operator>>(long double& val) {
        std::wcin >> val;
        return *this;
    }

    win_in_u8& win_in_u8::operator>>(std::string& val) {
        std::wstring wval;
        std::wcin >> wval;
        val = u16str_to_u8str(wval);
        return *this;
    }

    std::string win_in_u8::read_line() {
        std::wstring wstr;
        std::getline(std::wcin, wstr);
        return u16str_to_u8str(wstr);
    }

    win_in_u8 u8cin{};

    std::wstring AEAPI u8str_to_u16str(std::string_view const s) {
        auto const res = au8s_to_u16s_winapi(s.data());
        if (res == nullptr) {
            throw std::bad_alloc{};
        } else {
            std::wstring wstr(res);
            std::free(res);
            return wstr;
        }
    }

    std::string u16str_to_u8str(const std::wstring_view s) {
        const auto res = au16s_to_u8s_winapi(s.data());
        if (res == nullptr) {
            throw std::bad_alloc{};
        } else {
            std::string str(res);
            std::free(res);
            return std::move(str);
        }
    }

#endif // _MSC_VER

    unicodization::unicodization(int const argc, char ** & argv) : args(true) {
        auto const k = main_u8ize(&original_mode, &cp, &prev_mode);
        if (!k) {
            throw std::runtime_error("'main_u8ize' failed.");
        }
        auto const u8argv = get_u8argv();
        if (u8argv == nullptr) {
            throw std::runtime_error("'get_u8argv' failed.");
        }
        argv = u8argv;
        this->argc = argc;
        this->argv = u8argv;
    }

    unicodization::unicodization() : args(false), argc(0), argv(nullptr) {
        auto const k = main_u8ize(&original_mode, &cp, &prev_mode);
        if (!k) {
            throw std::runtime_error("'main_u8ize' failed.");
        }
    }

    unicodization::~unicodization() {
        main_deu8ize(original_mode, cp, prev_mode);
        if (args) {
            free_u8argv(argc, argv);
        }
    }
}
