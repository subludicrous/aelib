// © subludicrous
// SPDX-License-Identifier: BSL-1.0

#ifndef AE_AE_HPP
#define AE_AE_HPP

#include <ae/base.h>
#include <vector>
#include <string_view>
#include <string>

namespace ae {
    /**
    * @return UTF-8 std::string read from std::cin
    */
    std::string getline(char delim = '\n');

#if AE_NO_DEFAULT_UTF8

    class u8ization final {
    private:
        bool aight;
        int argc;
        char ** argv;
        void * handle;
        unsigned long original_mode;
        unsigned int cp;
        int prev_mode;
    public:
        u8ization(u8ization const&) = delete;
        u8ization(u8ization&&) = delete;
        u8ization() noexcept;
        u8ization(int argc, char**& argv) noexcept;
        ~u8ization();
        
        operator bool() const noexcept;
        void check_opt_exit(
            char const * output = "Failed to initialize UTF-8 environment.\n"
        ) const noexcept;
    };

    std::vector<std::string_view> AE_API cppize(int argc, char const * const * argv);

#endif // AE_NO_DEFAULT_UTF8
}

#endif
