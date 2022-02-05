//===--------------- convert.hpp - 类型转换实现 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020-2022 moe-org All rights reserved.
//
//===--------------------------------------------------------===//
/// \file
/// 这个文件定义了各种类型之间的安全经过检查的转换。
/// 所有适合的类型转换应该使用这个文件定义的内容。
//===--------------------------------------------------------===//

#ifndef UTOPIA_CORE_CONVERT_HPP
#define UTOPIA_CORE_CONVERT_HPP

#include <cassert>
#include <concepts>
#include <cstdint>
#include <limits>
#include <type_traits>

#include <utopia/core/assert.hpp>
#include <utopia/core/exception.hpp>

namespace utopia::core {

    /// @brief      安全的无符号数到有符号数之间的转换。
    /// @param input 输入
    /// @param output 输出。如果转换失败则不赋值。
    /// @return     转换成功返回true，否则返回false。
    template<std::signed_integral TO, std::unsigned_integral FROM>
    constexpr inline bool safeSignCast(FROM input, TO &output) {
        const constexpr auto outputMax =
            static_cast<uintmax_t>(std::numeric_limits<TO>::max());

        const auto uinput = static_cast<uintmax_t>(input);

        if(uinput > outputMax) {
            return false;
        }
        output = static_cast<TO>(uinput);
        return true;
    }

    /// @brief      安全的有符号数到无符号数之间的转换。
    /// @param input 输入
    /// @param output 输出。如果转换失败则不赋值。
    /// @return     转换成功返回true，否则返回false。
    template<std::unsigned_integral TO, std::signed_integral FROM>
    constexpr inline bool safeSignCast(FROM input, TO &output) {
        if(input < 0) {
            return false;
        }
        return safeNumberCast<TO, uintmax_t>(static_cast<uintmax_t>(input),
                                             output);
    }

    /// @brief      安全整数转换。只支持相同的符号。
    /// @param from 输入
    /// @param to    输出。如果转换失败则不操作。
    /// @return     如果转换成功则返回true，否则返回false。
    template<std::integral TO, std::integral FROM>
    constexpr inline bool safeNumberCast(FROM input, TO &output) {
        static_assert(
            std::numeric_limits<TO>::is_signed ==
                std::numeric_limits<FROM>::is_signed,
            "safeNumberCast只允许相同的符号进行转换！请使用safeSignCast进行不同符号的转换。");

        if(std::numeric_limits<TO>::is_signed) {
            if(static_cast<intmax_t>(input) > std::numeric_limits<TO>::max() ||
               static_cast<intmax_t>(input) < std::numeric_limits<TO>::min()) {
                return false;
            }
        }
        else {
            if(static_cast<uintmax_t>(input) > std::numeric_limits<TO>::max() ||
               static_cast<uintmax_t>(input) < std::numeric_limits<TO>::min()) {
                return false;
            }
        }

        output = static_cast<TO>(input);
        return true;
    }

    /// @brief          安全的整数转换。转换失败则退出程序。输入和输出可以拥有任意符号。
    /// @param input    输入
    /// @return         输出
    template<std::integral TO, std::integral FROM>
    constexpr inline TO safeConvert(FROM input) {
        if constexpr(std::numeric_limits<TO>::is_signed ==
                     std::numeric_limits<FROM>::is_signed) {
            TO output = 0;
            if(safeNumberCast<TO, FROM>(input, output)) {
                return output;
            }
            utopia::core::failed("number convert failed down:out of range!");
        }
        else {
            TO output = 0;
            if(safeSignCast<TO, FROM>(input, output)) {
                return output;
            }
            utopia::core::failed("number convert failed down:out of range!");
        }
    }

}   // namespace utopia::core

#endif
