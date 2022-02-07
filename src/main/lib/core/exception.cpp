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

Exception::Exception(const char                 *msg,
                     const std::source_location &local) noexcept :
    line_(local.line()),
    file_(local.file_name()) {
    // 检查信息字符串
    if(msg == nullptr) {
        msg = "unknown reason";
    }

    this->msg_         = std::string{ msg };

    this->stack_trace_ = boost::stacktrace::stacktrace();
}

string Exception::get_msg() const {
    std::ostringstream buf;

    // 输出异常信息
    buf << this->get_name() << ":";
    buf << this->msg_.c_str() << "\n";

    // 输出上下文信息
    buf << "at " << file_.c_str() << ":"
        << (line_ != 0 ? std::to_string(line_) : "unknown") << "\n";

    // 打印堆栈
    buf << "===== exception stack trace begin =====\n";
    buf << boost::stacktrace::to_string(this->stack_trace_);
    buf << "=====  exception stack trace end  =====\n";

    return buf.str();
}

void Exception::print_to(std::ostream &output) const {
    auto msg = this->get_msg();
    output.write(msg.data(), core::safe_convert<std::streamsize>(msg.length()));
}


const char *Exception::what() const noexcept {
    return msg_.c_str();
}
