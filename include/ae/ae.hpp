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
        unicodization(int argc, char**& argv);
        ~unicodization();
    };

#endif

    inline std::vector<std::string_view> cppize(int const argc, char const * const * const argv) {
        std::vector<std::string_view> cppargs;
        cppargs.reserve(static_cast<std::size_t>(argc));
        for (auto argn = 0; argn < argc; argn++) {
            cppargs.push_back(argv[argn]);
        }
        return std::move(cppargs);
    }
}

#endif // !AE_LIB_HPP
