//===--------------- u_assert.cpp - 断言函数实现 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020-2022 moe-org All rights reserved.
//
//===-------------------------------------------------------===//
/// \file
/// 这个文件实现了utopia::core::u_assert
//===-------------------------------------------------------===//

#include <boost/stacktrace.hpp>
#include <cstdio>
#include <iostream>
#include <string_view>

#include <utopia/core/assert.hpp>
#include <fmt/core.h>

void utopia::core::u_assert(bool                 condition,
                            std::string_view     reason,
                            std::source_location source) {
    if(!condition) {
        auto position = fmt::format("at {}(line {} column {})::{}", source.file_name(),
            source.line(),source.column(),source.function_name());

        std::cerr << "utopia assert failed down!\n"
                  << reason << "\n"
                  << position << "\n"
                  << "//==--- call stack start ---==//\n";

        std::cerr << boost::stacktrace::to_string(
            boost::stacktrace::stacktrace());

        std::cerr << "//==---  call stack end  ---==//\n";

        std::abort();
    }
}

[[noreturn]] void utopia::core::failed(std::string_view     reason,
                                       std::source_location source) {
    utopia::core::u_assert(false, reason, source);
    abort();
}
