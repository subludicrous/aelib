
#ifndef AE_BYTE_HPP
#define AE_BYTE_HPP

#include <cstddef>

namespace ae {
    inline namespace literals {
        [[nodiscard]]
        constexpr std::byte operator""_b(unsigned long long int val) {
            return static_cast<std::byte>(val);
        }
    }
}

#endif
