/**
* ae/prestd.hpp
* Author: subludicrous
* Licence: see LICENCE.txt
* Created on: 2021-05-11
*/

#ifndef AE_PRESTD_HPP
#define AE_PRESTD_HPP

#include <string_view>

namespace ae {
    // replace with std's in C++23
    template<typename ch>
    [[nodiscard]]
    constexpr bool contains(std::basic_string_view<ch> const sv, std::basic_string_view<ch> const what) noexcept {
        return sv.find(what) != sv.npos;
    }

    // replace with std's in C++20
    template<typename ch>
    [[nodiscard]]
    constexpr bool starts_with(std::basic_string_view<ch> const sv, std::basic_string_view<ch> const prefix) {
        return sv.substr(0, prefix.size()) == prefix;
    }
}

#endif
