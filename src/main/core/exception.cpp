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

#include <boost/stacktrace.hpp>
#include <mutex>
#include <sstream>

#include <utopia/config/configured.hpp>
#include <utopia/core/convert.hpp>
#include <utopia/core/exception.hpp>
#include <utopia/core/debug.hpp>

using namespace std;
using namespace utopia::core;

Exception::Exception(const std::string          &msg,
                     const utopia::core::SourceLocation &local) noexcept :
    line_(local.line()),
    file_(local.file_name()), msg_(msg),
    stack_trace_(boost::stacktrace::stacktrace()) {
    debug_break();
}

string Exception::get_msg() const {
    format_message();
    return *this->formatted_msg_;
}

void Exception::print_to(std::ostream &output) const {
    format_message();
    output << this->get_msg();
}


const char *Exception::what() const noexcept {
    format_message();
    return this->formatted_msg_->c_str();
}

void Exception::format_message() const {
    if(this->formatted_msg_->length() != 0) {
        return;
    }

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

    this->formatted_msg_.release();
    this->formatted_msg_ = std::move(std::make_unique<std::string>());
    this->formatted_msg_->append(buf.str());
    return;
}

#ifdef UTOPIA_UNDER_WINDOWS
    #include <Windows.h>
#endif

#include <cerrno>
#include <sstream>

std::string utopia::core::get_last_system_error_msg() {
    std::ostringstream buf{};

    auto               errno_code = errno;

    if(errno_code == 0) {
        buf << "no errno error(code=0)";
    }
    else {
        buf << "errno error(code=" << std::to_string(errno_code)
            << "):" << std::strerror(errno_code);
    }

#ifdef UTOPIA_UNDER_WINDOWS
    buf << "\n";

    auto win_error_code = ::GetLastError();

    if(win_error_code == 0) {
        buf << "no windows error(code=0)";
    }
    else {

        LPSTR win_error_msg_buffer = nullptr;

        auto  size                 = ::FormatMessageA(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
                FORMAT_MESSAGE_IGNORE_INSERTS,
            nullptr,
            win_error_code,
            0,
            reinterpret_cast<LPSTR>(&win_error_msg_buffer),
            0,
            nullptr);

        std::string message(win_error_msg_buffer, size);

        buf << "found windows error(code=" << std::to_string(win_error_code)
            << "):" << message;

        LocalFree(win_error_msg_buffer);
    }
#endif

    return buf.str();
}
