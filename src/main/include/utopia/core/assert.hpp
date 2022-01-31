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

#ifndef _UTOPIA_CORE_CONVERTER_HPP_
#define _UTOPIA_CORE_CONVERTER_HPP_

#include <concepts>
#include <string_view>
#include <type_traits>

namespace utopia {
    namespace core {

#define UTOPIA_ASSERT(COND, MSG) utopia::core::uassert(COND, std::string_view(MSG))
#define UTOPIA_FAILED(MSG) utopia::core::failed(std::string_view(MSG))

        /// @brief 断言函数。即使Release了也有效。
        /// @param condition 如果为false，则打印调试信息并退出。
        /// @param reason 如果condition为false，则输出此条信息（作为调试信息的一部分）。
        /// 设置为nullptr则不输出。
        void uassert(bool condition, std::string_view reason);

        /// @brief          快速失败。等价于void uassert(false, std::string_view);
        /// @param reason   失败的原因。
        [[noreturn]] void failed(std::string_view reason);

    }   // namespace core
}   // namespace utopia


#endif
