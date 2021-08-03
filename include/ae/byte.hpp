
#ifndef AE_BYTE_HPP
#define AE_BYTE_HPP

#include <cstddef>

namespace ae {
    using ::std::byte;
    inline namespace literals {
        [[nodiscard]]
        constexpr byte operator""_b(unsigned long long int val) {
            return static_cast<byte>(val);
        }
    }

    [[nodiscard]]
    constexpr byte to_byte(unsigned char const bv) {
        return static_cast<byte>(bv);
    }

    [[nodiscard]]
    constexpr unsigned int to_int(byte const b) {
        return std::to_integer<unsigned int>(b);
    }
}

#endif

class byte {
private:
    unsigned char m_b;
public:

};
