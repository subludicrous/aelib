// © Nikola Stepanoski
// SPDX-License-Identifier: BSL-1.0

#include <ae/ae.hpp>
#include <ae/winspec.h>
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
        val = u16_to_u8(wval);
        return *this;
    }

    std::string win_in_u8::read_line() {
        std::wstring wstr;
        std::getline(std::wcin, wstr);
        return u16_to_u8(wstr);
    }

    win_in_u8 u8cin{};

#ifdef _MSC_VER
    // uninit'd vals wouldn't be used
#pragma warning(suppress: 26495)
#endif
    unicodization::unicodization(int const argc, char ** & argv) {
        aight = main_u8ize(&original_mode, &cp, &prev_mode, &handle);
        if (!aight) {
            return;
        }
        auto const u8argv = get_u8argv();
        if (u8argv == nullptr) {
            aight = false;
            main_deu8ize(original_mode, cp, prev_mode, handle);
            return;
        }
        argv = u8argv;
        this->argc = argc;
        this->argv = u8argv;
    }

    unicodization::unicodization() : argc(0), argv(nullptr) {
        aight = main_u8ize(&original_mode, &cp, &prev_mode, &handle);
    }

    unicodization::~unicodization() {
        if (aight) {
            main_deu8ize(original_mode, cp, prev_mode, handle);
            if (argc) {
                free_u8argv(argc, argv);
            }
        }
    }

    unicodization::operator bool() const noexcept {
        return aight;
    }

#endif

    std::vector<std::string_view> AEAPI cppize(
        int const argc,
        char const * const * const argv
    ) {
        std::vector<std::string_view> cppargs;
        cppargs.reserve(static_cast<std::size_t>(argc));
        for (auto argn = 0; argn < argc; argn++) {
            cppargs.push_back(argv[argn]);
        }
        return std::move(cppargs);
    }
}
