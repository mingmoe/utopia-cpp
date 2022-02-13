//===--------------- assert.hpp - 断言函数定义 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020-2022 moe-org All rights reserved.
//
//===------------------------------------------------------===//
/// \file
/// 这个文件定义了utopia项目使用的断言函数。
/// 这个函数实现了一个拥有更多功能的断言（比如打印堆栈）。
//===------------------------------------------------------===//

#ifndef UTOPIA_CORE_ASSERT_HPP
#define UTOPIA_CORE_ASSERT_HPP

#include <concepts>
#include <source_location>
#include <string_view>
#include <type_traits>

namespace utopia::core {

    /// @brief 断言函数。即使Release了也有效。
    /// @param condition 如果为false，则打印调试信息并退出。
    /// @param reason 如果condition为false，则输出此条信息（作为调试信息的一部分）。
    /// @param source 源代码位置
    /// 设置为nullptr则不输出。
    void
        u_assert(bool                 condition,
                 std::string_view     reason,
                 std::source_location source = std::source_location::current());

    /// @brief          快速失败。等价于void uassert(false, std::string_view);
    /// @param source 源代码位置
    /// @param reason   失败的原因。
    [[noreturn]] void
        failed(std::string_view     reason,
               std::source_location source = std::source_location::current());

}   // namespace utopia::core


#endif
