//===--------------- debug.cpp - debug工具实现 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020-2022 moe-org All rights reserved.
//
//===--------------------------------------------------------===//
/// \file
/// 实现了debug.hpp定义的函数。
//===--------------------------------------------------------===//

#include <cstdlib>

#include <utopia/config/configured.hpp>
#include <utopia/core/debug.hpp>

#if defined(UTOPIA_UNDER_APPLE) || defined(UTOPIA_UNDER_LINUX)
    #include <csignal>
    #include <cstdio>
    #include <cstdlib>
#endif

void utopia::core::debug_break([[maybe_unused]] const char *reason) {
#ifdef UTOPIA_DEBUG_MODE
    #ifdef UTOPIA_USE_MSVC
    __debugbreak();
    #endif

    #if defined(UTOPIA_USE_CLANG) || defined(UTOPIA_USE_GCC)

        #if __has_builtin(__builtin_debugtrap)
    __builtin_debugtrap();

        #elif defined(SIGTRAP)
    std::raise(SIGTRAP);

        #else
    std::printf("\ndebug break:abort()\n");
    std::abort();
        #endif

    #endif
#endif
}
