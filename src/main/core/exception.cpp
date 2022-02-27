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
#include <utopia/config/configured.hpp>

using namespace std;
using namespace utopia::core;

Exception::Exception(const std::string          &msg,
                     const std::source_location &local) noexcept :
    line_(local.line()),
    file_(local.file_name()), msg_(msg),
    stack_trace_(boost::stacktrace::stacktrace()) {}

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
        buf << "not found windows error(code=0)";
    }
    else {

        LPSTR       win_error_msg_buffer = nullptr;

        auto        size = ::FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                                        FORMAT_MESSAGE_FROM_SYSTEM |
                                        FORMAT_MESSAGE_IGNORE_INSERTS,
                                    nullptr,
                                    win_error_code,
                                    0,
            reinterpret_cast<LPSTR>(& win_error_msg_buffer),
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
