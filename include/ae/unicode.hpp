// © subludicrous
// SPDX-License-Identifier: BSL-1.0

#ifndef AE_UNICODE_HPP
#define AE_UNICODE_HPP

#include <ae/base.h>
#include <ae/byte.hpp>
#include <string_view>
#include <string>
#include <algorithm>

using namespace std::string_view_literals;

namespace ae {
    static constexpr auto replacement = "\xef\xbf\xbd"sv;

    [[nodiscard]]
    constexpr auto u8bytes(char const c) noexcept {
        unsigned int u8s{};
        for (byte x = c; x & 0x80_b; x <<= 1u) {
            ++u8s;
        }
        return u8s;
    }

    // assumes legit UTF-8
    [[nodiscard]]
    constexpr auto u8len(std::string_view const str) noexcept {
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
        constexpr auto cont_mask = 0x80_b;
        byte const first = *u8str;
        if (!(first & cont_mask)) {
            // i.e. is ASCII
            return char32_t(first);
        }
        auto const cont_byte_count = u8bytes(char(first)) - 1u;
        // move the 6 x's of cont. bs 10XX'XXXX into result
        char32_t result{};
        // going from last to first
        for (auto i = cont_byte_count; i > 0u; --i) {
            // get byte
            byte cb = *(u8str + i);
            // remove cont. mask
            cb &= ~cont_mask;
            // make a part of the codepoint
            auto part = char32_t(cb);
            // shift these bits to the right place
            part <<= (6 * (cont_byte_count - i));
            result |= part;
        }
        // + 1 for 1st byte
        auto const first_byte_mask = 0xFF_b >> (cont_byte_count + 1);
        auto const fb_shift = (6 * cont_byte_count);
        result |= char32_t(first & first_byte_mask) << fb_shift;
        return result;
    }

    // assumes legit UTF-32
    [[nodiscard]]
    constexpr std::size_t req_bytes_u8(char32_t const codepoint) noexcept {
        if (codepoint <= 0x7Fu) {
            return 1u;
        }
        if (codepoint <= 0x7FFu) {
            return 2u;
        }
        if (codepoint <= 0xFFFFu) {
            return 3u;
        }
        return 4u;
    }

    [[nodiscard]]
    constexpr bool validate_u8_helper(
        char const * const cp,
        std::size_t const byte_count
    ) noexcept {
        // overlong encodings
        // a sequence that decodes to an invalid code point
        // i.e. U+D800 through U+DFFF and seqs after U+10FFFF
        auto const codepoint = u8_to_u32(cp);
        if (codepoint > 0x10FFFFu ||
            codepoint >= 0xD800u && codepoint <= 0xDFFFu) {
            return false;
        }
        auto const req_u8size = req_bytes_u8(codepoint);
        return req_u8size == byte_count;
    }

    // using u8"" can be weird on windows
    [[nodiscard]]
    constexpr bool validate_u8(std::string_view const str) noexcept {
        // We have to check: 
        // an unexpected continuation byte
        // a non-continuation byte before the end of the character

        constexpr auto max_bytes{ 4u };
        for (std::size_t pos{}; ; ) {
            if (pos == str.size()) {
                break;
            }
            auto const b = u8bytes(str[pos]);
            if (b == 0u) {
                // ASCII byte
                ++pos;
                continue;
            }
            if (b == 1u) {
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
                if (!(byte(str[pos]) & 0x80_b)) {
                    // not cont. b
                    return false;
                }
            }
            // passed checks for invalid bytes
            // now we check for overlong seqs and invalid codepoints
            if (!validate_u8_helper(
                str.data() + codepoint_beg,
                codepoint_end + 1 - codepoint_beg
            )) {
                return false;
            }
            ++pos;
        }
        return true;
    }

    // assumes legit UTF-32, writes null
    // @return required size w/o '\\0'
    constexpr std::size_t u32_to_u8(
        char32_t codepoint,
        char * const out
    ) noexcept {
        auto const bcount = req_bytes_u8(codepoint);

        if (out == nullptr) {
            return bcount;
        }
        constexpr auto contb = 0x80_b;

        // null terminator
        out[bcount] = '\0';

        if (bcount == 1U) {
            out[0] = static_cast<char>(codepoint);
            return bcount;
        }

        // from end backwards
        constexpr auto shift = 6u;
        byte u8part{};
        for (auto bc2 = bcount - 1u; bc2 >= 1; bc2--) {
            constexpr auto cont_part = 0x3F_b;
            u8part = codepoint;
            codepoint >>= shift;
            u8part &= cont_part; // xx11 1111
            u8part |= contb; // 10xx xxxx
            out[bc2] = char(u8part);
        }
        // first
        auto const bmask = 0xF0_b << (4u - bcount);
        u8part = codepoint;
        u8part |= bmask; // add bytes' count mask
        out[0] = char(u8part);

        return bcount;
    }

    // assumes legit UTF-32
    [[nodiscard]]
    constexpr auto u8_next(char const * const u8str) noexcept {
        auto const b = static_cast<std::ptrdiff_t>(u8bytes(*u8str));
        return b == 0 ? u8str + 1 : u8str + b;
    }

    [[nodiscard]]
    constexpr auto is_ascii(char const c) noexcept {
        return !bool(0x80_b & c);
    }

    [[nodiscard]]
    AECONSTEXPR20 auto is_ascii(std::string_view const s) noexcept {
        return std::all_of(
            std::begin(s),
            std::end(s),
            [](decltype(s)::value_type const el) {
                return is_ascii(el);
            }
        );
    }
}

#endif
