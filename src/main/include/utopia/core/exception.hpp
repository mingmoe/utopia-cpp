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

#ifndef _UTOPIA_CORE_EXCEPTION_HPP_
#define _UTOPIA_CORE_EXCEPTION_HPP_

#include <utopia-configured.hpp>

#include <exception>
#include <memory>
#include <mutex>
#include <string>
#include <string_view>

#include <boost/stacktrace.hpp>

namespace utopia {
    namespace core {

#define BUILD_UTOPIA_EXCEPTION(msg)                                            \
    utopia::core::Exception(u8##msg, __LINE__, __FILE__)
#define THROW_UTOPIA_EXCEPTION(msg) throw BUILD_UTOPIA_EXCEPTION(msg)

        /**
		 * @brief utopia项目的异常。
		 * 
		 * 所有utopia项目内的异常应该继承此类
		*/
        class Exception : std::exception {
          public:
            /**
			* @brief	构造一个包含调用信息的异常
			 * @param msg 不为null的字符串
			 * @param line 行号，如果为0则视为未知行号
			 * @Param file 文件名称，如果为null则视为未知文件
			*/
            Exception(std::string_view msg,
                      const uint64_t   line,
                      const char      *file) noexcept;

            /**
			* @brief	构造一个包含调用信息的异常
			 * @param msg 不为null的字符串
			 * @param line 行号，如果为0则视为未知行号
			 * @Param file 文件名称，如果为null则视为未知文件
			*/
            Exception(const char8_t *msg,
                      const uint64_t line,
                      const char    *file) noexcept;

            /**
			* @brief	构造一个包含调用信息的异常
			 * @param msg 不为null的字符串
			 * @param line 行号，如果为0则视为未知行号
			 * @Param file 文件名称，如果为null则视为未知文件
			*/
            Exception(const char    *msg,
                      const uint64_t line,
                      const char    *file) noexcept;

            // define some default functions
            Exception(const Exception &)     = default;
            Exception(Exception &&) noexcept = default;
            Exception &operator=(const Exception &) = default;
            Exception &operator=(Exception &&) noexcept = default;
            virtual ~Exception()                        = default;

            /**
			 * @brief 获取原始信息(即构造函数的msg参数)
			 * @return 原始信息的复制
			*/
            inline virtual std::string getOriginMsg() const noexcept {
                return std::string(*this->msg_.get());
            }

            /**
			 * @brief	获取异常信息字符串
			 * @return	获取异常信息字符串。注:此函数返回的不等价于构造此函数所使用的字符串。
			*/
            virtual std::string getMsg() const;

            /**
			 * @brief			输出到流
			 * @param output	要输出的流
			*/
            virtual void printTo(std::ostream &output) const;

            /**
			 * @brief  return value same as GetOriginMsg().data();
			*/
            virtual const char *what() const noexcept override;
          private:
            // 这些数据不应该在构造函数之外修改
            std::unique_ptr<std::string> msg_{
                nullptr
            };   // utf-8信息字符串，非空
            std::unique_ptr<std::string> file_{ nullptr };   // 文件名称，可空

            uint64_t line_{ 0 };   // 行号，为0则视为未知行号

            boost::stacktrace::stacktrace stack_trace_{};   // 构造时的堆栈追踪
        };

    }   // namespace core
}   // namespace utopia

#endif
