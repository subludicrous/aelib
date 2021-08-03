// © subludicrous
// SPDX-License-Identifier: BSL-1.0

#include <ae/ae.hpp>
#include <ae/win_u8.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>

namespace ae {
    std::string getline(char const delim) {
        if constexpr (AE_NO_DEFAULT_UTF8) {
            std::wstring ws;
            std::getline(
                std::wcin,
                ws,
                wchar_t{ static_cast<unsigned char>(delim) }
            );
            return u16_to_u8(ws);
        } else {
            std::string s;
            std::getline(std::cin, s, delim);
            return s;
        }
    }

#ifdef _MSC_VER
    // uninit'd vals wouldn't be used
#pragma warning(suppress: 26495)
#endif
    u8ization::u8ization(int const argc, char ** & argv) noexcept {
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

#ifdef _MSC_VER
    // uninit'd vals wouldn't be used
#pragma warning(suppress: 26495)
#endif
    u8ization::u8ization() noexcept : argv(nullptr) {
        aight = main_u8ize(&original_mode, &cp, &prev_mode, &handle);
    }

    u8ization::~u8ization() {
        if (aight) {
            main_deu8ize(original_mode, cp, prev_mode, handle);
            if (argv != nullptr) {
                free_u8argv(argc, argv);
            }
        }
    }

    u8ization::operator bool() const noexcept {
        return aight;
    }

    void u8ization::check_opt_exit(char const * const output) const noexcept {
        if (output != nullptr) {
            std::fputs(output, stderr);
        }
        std::exit(EXIT_FAILURE);
    }

    std::vector<std::string_view> AE_API cppize(
        int const argc,
        char const * const * const argv
    ) {
        std::vector<std::string_view> cppargs;
        cppargs.reserve(static_cast<std::size_t>(argc));
        for (int argn = 0; argn < argc; argn++) {
            cppargs.push_back(argv[argn]);
        }
        return cppargs;
    }
}
