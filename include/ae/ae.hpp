// © Nikola Stepanoski
// SPDX-License-Identifier: BSL-1.0

#ifndef AE_LIB_HPP
#define AE_LIB_HPP

#include <ae/base.h>
#include <iostream>
#include <vector>
#include <string_view>

using namespace std::string_view_literals;

namespace ae {

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

#ifdef WINCHECK

    class unicodization final {
    private:
        bool aight;
        int argc;
        char ** argv;
        void * handle;
        unsigned long original_mode;
        unsigned int cp;
        int prev_mode;
    public:
        unicodization(unicodization const&) = delete;
        unicodization(unicodization&&) = delete;
        unicodization();
        unicodization(int argc, char**& argv);
        ~unicodization();
        operator bool() const noexcept;
    };

#endif

    std::vector<std::string_view> AEAPI cppize(int argc, char const * const * argv);
}

#endif
