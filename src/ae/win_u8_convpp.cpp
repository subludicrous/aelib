// ? subludicrous
// SPDX-License-Identifier: BSL-1.0

#include <cstdlib>
#include <ae/win_u8.h>

namespace ae {
    std::wstring AE_API u8_to_u16(std::string_view const s) {
        auto const res = au8s_to_u16s_winapi(s.data());
        if (res == nullptr) {
            throw std::bad_alloc{};
        } else {
            std::wstring wstr(res);
            std::free(res);
            return wstr;
        }
    }

    std::string AE_API u16_to_u8(std::wstring_view const s) {
        auto const res = au16s_to_u8s_winapi(s.data());
        if (res == nullptr) {
            throw std::bad_alloc{};
        } else {
            std::string str(res);
            std::free(res);
            return std::move(str);
        }
    }
}
