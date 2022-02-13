//===--------------- check_ops.hpp - 算数检查函数定义 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020-2022 moe-org All rights reserved.
//
//===-------------------------------------------------------------===//
/// \file
/// 为加减乘除等运算定义了溢出检查函数。
//===-------------------------------------------------------------===//

#ifndef UTOPIA_CORE_CHECK_OPS_HPP
#define UTOPIA_CORE_CHECK_OPS_HPP

#include <concepts>
#include <type_traits>

#include <utopia/core/assert.hpp>

namespace utopia::core {

    // non-built-in-function from:
    // https://wiki.sei.cmu.edu/confluence/display/c/INT32-C.+Ensure+that+operations+on+signed+integers+do+not+result+in+overflow

    /// @brief 安全整数加法
    /// @param first 第一个加数
    /// @param second 第二个加数
    /// @param output 输出。如果加法没有溢出，则修改此值为加法结果。否则不修改此值。
    /// @return 如果加法没有溢出，则返回true，否则返回false。
    template<std::integral T>
    [[nodiscard]] bool
        safe_add(T first, T second, std::remove_const_t<T> &output) noexcept{
#ifdef UTOPIA_USE_GCC || UTOPIA_USE_CLANG
        return !__builtin_add_overflow(first, second, &output);
#endif
        auto valued = ((second > 0) &&
                       (first > (std::numeric_limits<T>::max() - second))) ||
                      ((second < 0) &&
                       (first < (std::numeric_limits<T>::min() - second)));

        if(!valued) {
            output = first + second;
        }
        return !valued;
    }

    /// @brief 安全整数加法
    /// @param first 第一个加数
    /// @param second 第二个加数
    /// @return 返回结果。如果溢出则调用utopia::core::failed();
    template<std::integral T>
    [[nodiscard]] T safe_add(T first, T second) noexcept {
        T output{ 0 };
        if(!safe_add<T>(first, second, &output)) {
            utopia::core::failed("safe number add overflow");
        }
        return output;
    }

    /// @brief 安全整数减法
    /// @param first 被减数
    /// @param second 减数
    /// @param output 输出。如果结果没有溢出，则修改此值为结果。否则不修改此值。
    /// @return 如果结果没有溢出，则返回true，否则返回false。
    template<std::integral T>
    [[nodiscard]] bool
        safe_sub(T first, T second, std::remove_const_t<T> &output) noexcept {
#ifdef UTOPIA_USE_GCC || UTOPIA_USE_CLANG
        return !__builtin_sub_overflow(first, second, &output);
#endif
        auto valued =
            (second > 0 && first < std::numeric_limits<T>::min() + second) ||
            (second < 0 && first > std::numeric_limits<T>::max() + second);

        if(!valued) {
            output = first - second;
        }
        return !valued;
    }

    /// @brief 安全整数减法
    /// @param first 被减数
    /// @param second 减数
    /// @return 返回结果。如果溢出则调用utopia::core::failed();
    template<std::integral T>
    [[nodiscard]] T safe_sub(T first, T second) noexcept {
        T output{ 0 };
        if(!safe_sub<T>(first, second, &output)) {
            utopia::core::failed("safe number sub overflow");
        }
        return output;
    }


    /// @brief 安全整数乘法
    /// @param first 因数
    /// @param second 因数
    /// @param output 输出。如果结果没有溢出，则修改此值为结果。否则不修改此值。
    /// @return 如果结果没有溢出，则返回true，否则返回false。
    template<std::integral T>
    [[nodiscard]] bool
        safe_mul(T first, T second, std::remove_const_t<T> &output) noexcept {
#ifdef UTOPIA_USE_GCC || UTOPIA_USE_CLANG
        return !__builtin_mul_overflow(first, second, &output);
#endif
        if(first > 0) {    /* si_a is positive */
            if(second > 0) { /* si_a and si_b are positive */
                if(first > (std::numeric_limits<T>::max() / second)) {
                    /* Handle error */
                    return false;
                }
            }
            else { /* si_a positive, si_b nonpositive */
                if(second < (std::numeric_limits<T>::min() / first)) {
                    /* Handle error */
                    return false;
                }
            } /* si_a positive, si_b nonpositive */
        }
        else {               /* si_a is nonpositive */
            if(second > 0) { /* si_a is nonpositive, si_b is positive */
                if(first < (std::numeric_limits<T>::min() / second)) {
                    /* Handle error */
                    return false;
                }
            }
            else { /* si_a and si_b are nonpositive */
                if((first != 0) &&
                   (second < (std::numeric_limits<T>::max() / first))) {
                    /* Handle error */
                    return false;
                }
            } /* End if si_a and si_b are nonpositive */
        }     /* End if si_a is nonpositive */

        output = first * second;
        return true;
    }

    /// @brief 安全整数乘法
    /// @param first 因数
    /// @param second 因数
    /// @return 返回结果。如果溢出则调用utopia::core::failed();
    template<std::integral T>
    [[nodiscard]] T safe_mul(T first, T second) noexcept {
        T output{ 0 };
        if(!safe_mul<T>(first, second, &output)) {
            utopia::core::failed("safe number mul overflow");
        }
        return output;
    }

    template<std::integral T>
    [[nodiscard]] bool
        safe_div(T first, T second, std::remove_const_t<T> &output) noexcept {
        if constexpr(std::is_signed_v<T>) {
            if((second == 0) ||
               ((first == std::numeric_limits<T>::min()) && (second == -1))) {
                return false;
            }
            else {
                output = first / second;
                return true;
            }
        }
        else {
            if(second == 0) {
                return false;
            }
            else {
                output = first / second;
                return true;
            }
        }
    }

    template<std::integral T>
    [[nodiscard]] bool
        safe_rem(T first, T second, std::remove_const_t<T> &output) {
        if constexpr(std::is_signed_v<T>) noexcept {
                if((second == 0) || ((first == std::numeric_limits<T>::min()) &&
                                     (second == -1))) {
                /* Handle error */
                return false;
            }
            else {
                output = first % second;
                return true;
            }
        }
        else {
            if(second == 0) {
                return false;
            }
            else {
                output = first % second;
                return true;
            }
        }
    }

}   // namespace utopia::core


#endif
