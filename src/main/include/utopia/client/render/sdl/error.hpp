//===--------------- error.hpp - 错误定义 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020-2022 moe-org All rights reserved.
//
//===--------------------------------------------------===//
/// \file
/// 对一些SDL错误进行了封装处理
//===--------------------------------------------------===//

#ifndef UTOPIA_CLIENT_RENDER_SDL_ERROR_HPP
#define UTOPIA_CLIENT_RENDER_SDL_ERROR_HPP

#ifndef UTOPIA_PLATFORM_CLIENT
    #error this file is only compiled in client of utopia
#endif

#include <SDL.h>
#include <type_traits>

#include <utopia/core/exception.hpp>
#include <fmt/core.h>

namespace utopia::client::render::sdl {

    using SdlException = utopia::core::UniversalException<"SdlException">;

    /// @brief 抛出SdlException。使用SDL_GetError来构造异常信息
    [[noreturn]] inline void throw_sdl_exception() {
        auto msg = fmt::format("sdl error:{}", SDL_GetError());
        throw SdlException{ msg };
    }

    /// @brief 如果参数为nullptr，则抛出SDL异常。
    /// @note 只用于构造SDL错误
    template<typename T>
    inline void check_sdl_nullptr_error(T ptr) {
        static_assert(std::is_pointer_v<T>, "need a pointer about SDL");

        if(ptr == nullptr) {
            throw_sdl_exception();
        }
    }

    /// @brief 参数不为0时则抛出sdl异常
    inline void check_sdl_nonzero_error(int result) {
        if(result != 0) {
            throw_sdl_exception();
        }
    }

}   // namespace utopia::client::render::sdl

#endif
