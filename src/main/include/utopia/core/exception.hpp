//===--------------- exception.hpp - 异常声明 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020-2022 moe-org All rights reserved.
//
//===-----------------------------------------------------===//
/// \file
/// 这个文件声明了utopia::Exception。
/// 这个类应该是整个utopia异常系统的基类。
//===-----------------------------------------------------===//

#ifndef UTOPIA_CORE_EXCEPTION_HPP
#define UTOPIA_CORE_EXCEPTION_HPP

#include <utopia-configured.hpp>

#include <cerrno>
#include <cstring>
#include <exception>
#include <fmt/core.h>
#include <memory>
#include <source_location>
#include <string>
#include <string_view>

#include <boost/stacktrace.hpp>

namespace utopia::core {

    /**
		 * @brief utopia项目的异常。
		 * 
		 * 所有utopia项目内的异常应该继承此类
		*/
    class Exception : public std::exception {
      public:

        /// @brief 构造一个异常
        /// @param msg 异常信息
        /// @param local 构造异常的源代码位置
        Exception(const char                 *msg,
                  const std::source_location &local =
                      std::source_location::current());

        // define some default functions
        Exception(const Exception &) = delete;
        Exception &operator=(const Exception &) = delete;
        Exception(Exception &&) noexcept        = default;
        Exception &operator=(Exception &&) noexcept = default;
        ~Exception() override                       = default;

        /// @brief  获取异常名称
        /// @return 异常的名称
        [[nodiscard]] inline virtual std::string get_name() const noexcept {
            return std::string{ "UtopiaException" };
        }


        /// @brief 获取原始信息(即构造函数的msg参数)
        /// @return 原始信息的复制
        [[nodiscard]] inline virtual std::string
            get_origin_msg() const noexcept {
            return std::string{ this->msg_ };
        }

        /// @brief	获取异常信息字符串
        /// @return	获取异常信息字符串。注:此函数返回的不等价于构造此函数所使用的字符串。
        [[nodiscard]] virtual std::string get_msg() const;

        /// @brief			输出异常信息到流
        /// @param output	要输出的流
        virtual void print_to(std::ostream &output) const;


        /// @brief  return value same as get_origin_msg().data();
        [[nodiscard]] const char *what() const noexcept override;

      private:

        // 这些数据不应该在构造函数之外修改
        std::string msg_{ nullptr };    // utf-8信息字符串，非空
        std::string file_{ nullptr };   // 文件名称，可空

        uint64_t    line_{ 0 };   // 行号，为0则视为未知行号

        boost::stacktrace::stacktrace stack_trace_{};   // 构造时的堆栈追踪
    };

    // NOLINTBEGIN(*-macro-*)

    // 用于定义一个新异常
    // NOLINTNEXTLINE
#define DEFINED_UTOPIA_EXCEPTION(exceptionName)                                \
    class exceptionName##Exception : public Exception {                        \
      public:                                                                  \
                                                                               \
        exceptionName##Exception(const char                 *msg,              \
                                 const std::source_location &local =           \
                                     std::source_location::current()) noexcept \
            :                                                                  \
            Exception(msg, local) {}                                           \
                                                                               \
        inline virtual std::string get_name() const noexcept override {        \
            return std::string{ #exceptionName "Exception" };                  \
        }                                                                      \
    }

    /// @brief  参数为nullptr异常
    // NOLINTNEXTLINE
    DEFINED_UTOPIA_EXCEPTION(ArgumentNullptr);

    /// @brief  IO异常
    // NOLINTNEXTLINE
    DEFINED_UTOPIA_EXCEPTION(IO);

    // NOLINTEND(*-macro-*)

#undef DEFINED_UTOPIA_EXCEPTION

}   // namespace utopia::core

#endif
