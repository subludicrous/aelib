/**
* ae/unicode.hpp
* Author: subludicrous
* Licence: see LICENCE.txt
* Created on: 2021-05-06
*/

#ifndef AE_UNICODE_HPP
#define AE_UNICODE_HPP

#include <cstddef>
#include <string_view>

namespace ae {
    [[nodiscard]]
    constexpr std::size_t u8bytes(char const c) noexcept {
        std::size_t u8s{};
        for (auto x = static_cast<unsigned char>(c); x & 0x80Ui8; x <<= 1U) {
            u8s++;
        }
        return u8s;
    }

    // assumes legit UTF-8
    [[nodiscard]]
    constexpr std::size_t u8len(std::string_view const str) noexcept {
        std::size_t sz{};
        for (auto it = std::cbegin(str); it != std::cend(str); ) {
            auto b = u8bytes(*it);
            if (b == 0) ++b;
            ++sz;
            it += static_cast<std::ptrdiff_t>(b);
        }
        return sz;
    }

    // assumes legit UTF-8
    [[nodiscard]]
    constexpr char32_t u8_to_u32(char const * const u8str) noexcept {
        constexpr std::byte cont_mask{ 0x80U };
        //std::byte const first{ *u8str };
        auto const first = static_cast<std::byte>(*u8str);
        if (!std::to_integer<bool>(first & cont_mask)) {
            // i.e. is ASCII
            return std::to_integer<char32_t>(first);
        }
        unsigned int cont_byte_count{};
        {
            // count continuation bytes
            auto copy_first = first;
            while (std::to_integer<bool>((copy_first <<= 1U) & cont_mask)) {
                ++cont_byte_count;
            }
        }
        // move the 6 x's of cont. bs 10XX'XXXX into result
        char32_t result{};
        // going from last to first
        for (auto i = cont_byte_count; i > 0U; --i) {
            // get byte
            auto cb = static_cast<std::byte>(*(u8str + i));
            //std::byte cb{ *(u8str + i) };
            // remove cont. mask
            cb &= ~cont_mask;
            // make a part of the codepoint
            auto part = std::to_integer<char32_t>(cb);
            // shift these bits to the right place
            part <<= (6 * (cont_byte_count - i));
            result |= part;
        }
        auto const first_byte_mask = std::byte{ 0xFFU } >> (cont_byte_count + 1); // + 1 for 1st byte
        result |= std::to_integer<char32_t>(first & first_byte_mask) << (6 * cont_byte_count);
        return result;
    }

    // assumes legit UTF-32
    [[nodiscard]]
    constexpr std::size_t req_bytes_u8(char32_t const codepoint) noexcept {
        if (codepoint <= 0x7FUi32) {
            return 1U;
        }
        if (codepoint <= 0x7FFUi32) {
            return 2U;
        }
        if (codepoint <= 0xFFFFUi32) {
            return 3U;
        }
        return 4U;
    }

    [[nodiscard]]
    constexpr bool validate_utf8_helper(char const * const cp, std::size_t const byte_count) noexcept {
        // overlong encodings
        // a sequence that decodes to an invalid code point
        // i.e. U+D800 through U+DFFF and seqs after U+10FFFF
        auto const codepoint = u8_to_u32(cp);
        if (codepoint > 0x10FFFFUi32 ||
            codepoint >= 0xD800Ui32 && codepoint <= 0xDFFFUi32) {
            return false;
        }
        auto const req_u8size = req_bytes_u8(codepoint);
        return req_u8size == byte_count;
    }

    // using u8"" can be weird on windows
    [[nodiscard]]
    constexpr bool validate_utf8(std::string_view const str) noexcept {
        // We have to check: 
        // an unexpected continuation byte
        // a non-continuation byte before the end of the character

        constexpr std::size_t max_bytes = 4;
        for (std::size_t pos{}; ; ) {
            if (pos == str.size()) {
                break;
            }
            auto const b = u8bytes(str[pos]);
            if (b == 0) {
                // ASCII byte
                ++pos;
                continue;
            }
            if (b == 1) {
                // lone continuation byte
                return false;
            }
            if (b > max_bytes) {
                return false;
            }
            // 2, 3 or 4
            auto const left_cont_bs = b - 1; // 1, 2 or 3
            // check that the left chars are cont. bytes
            auto const codepoint_beg = pos;
            auto const codepoint_end = pos + left_cont_bs; // inclusive
            if (codepoint_end >= str.size()) {
                return false;
            }
            while (pos < codepoint_end) {
                ++pos;
                if (!(static_cast<unsigned char>(str[pos]) & 0x80U)) {
                    // not cont. b
                    return false;
                }
            }
            // passed checks for invalid bytes
            // now we check for overlong seqs and invalid codepoints
            if (!validate_utf8_helper(str.data() + codepoint_beg, codepoint_end + 1 - codepoint_beg)) {
                return false;
            }
            ++pos;
        }
        return true;
    }

    // assumes legit UTF-32
    [[nodiscard]]
    constexpr std::size_t u32_to_u8(
        char32_t const codepoint,
        char * const out
    ) {
        auto const bc = req_bytes_u8(codepoint);
        
    }

    [[nodiscard]]
    constexpr auto u8_nextc(char const * const u8str) {

    }
}

#endif
