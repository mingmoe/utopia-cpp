//===--------------- exception.cpp - 异常实现 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020-2022 moe-org All rights reserved.
//
//===-----------------------------------------------------===//
/// \file
/// 这个文件实现了utopia::core::Exception
//===-----------------------------------------------------===//

#include <mutex>
#include <sstream>

#include <utopia/core/convert.hpp>
#include <utopia/core/exception.hpp>

#include <boost/stacktrace.hpp>

using namespace std;
using namespace utopia::core;

Exception::Exception(string_view    msg,
                     const uint64_t line,
                     const char    *file) noexcept :
    Exception(msg.data(), line, file) {}

Exception::Exception(const char8_t *msg,
                     const uint64_t line,
                     const char    *file) noexcept :
    Exception(reinterpret_cast<const char *>(msg), line, file) {} // NOLINT

Exception::Exception(const char    *msg,
                     const uint64_t line,
                     const char    *file) noexcept {
    // 检查信息字符串
    if(msg == nullptr) {
        msg = "unknown reason";
    }

    this->msg_ = std::make_unique<std::string>(msg);

    // check file and line number
    if(file != nullptr) {
        file_ = std::make_unique<std::string>(file);
    }

    line_              = line;

    this->stack_trace_ = boost::stacktrace::stacktrace();
}

string Exception::getMsg() const {
    std::ostringstream buf;

    // 输出异常信息
    buf << this->getExceptionName() << ":";
    buf << this->msg_->c_str() << "\n";

    // 输出可选的上下文信息
    if(file_ != nullptr) {
        buf << "at " << file_->c_str() << ":"
            << (line_ != 0 ? std::to_string(line_) : "unknown") << "\n";
    }

    // 打印堆栈
    buf << "===== exception stack trace begin =====\n";
    buf << boost::stacktrace::to_string(this->stack_trace_);
    buf << "=====  exception stack trace end  =====\n";

    return buf.str();
}

void Exception::printTo(std::ostream &output) const {
    auto msg = this->getMsg();
    output.write(msg.data(), core::safeConvert<std::streamsize>(msg.length()));
}


const char *Exception::what() const noexcept {
    return msg_->c_str();
}
