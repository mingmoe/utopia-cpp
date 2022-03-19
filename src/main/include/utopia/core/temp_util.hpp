//===--------------- temp_util.hpp - 一些模板工具定义 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020-2022 moe-org All rights reserved.
//
//===-------------------------------------------------------------===//
/// \file
/// 定义了一些模板工具。
//===-------------------------------------------------------------===//

#ifndef UTOPIA_CORE_TEMP_UTIL_HPP
#define UTOPIA_CORE_TEMP_UTIL_HPP

#include <algorithm>

namespace utopia::core {

    /// @brief 字符串字面值
    template<size_t N>
    struct StringLiteral {
        constexpr StringLiteral(const char (&str)[N]) {
            std::copy_n(str, N, value);
        }

        char value[N];
    };

}   // namespace utopia::core

#endif
