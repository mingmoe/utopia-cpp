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

#include <SDL2/SDL.h>
#include <type_traits>

#include <utopia/core/exception.hpp>

namespace utopia::client::render::sdl {

    DEFINED_UTOPIA_SIMPLE_EXCEPTION(Sdl);

    /// @brief 抛出SdlException。使用SDL_GetError来构造异常信息
    [[noreturn]] inline void throw_sdl_exception() {
        throw SdlException{ SDL_GetError() };
    }

    /// @brief 如果参数为nullptr，则抛出SDL异常。
    /// @note 只用于构造SDL错误
    template<typename T>
    inline void null_then_throw_sdl_exception(T ptr) {
        static_assert(std::is_pointer_v<T>, "need a pointer about SDL");

        if(ptr == nullptr) {
            throw_sdl_exception();
        }
    }

    /// @brief 参数不为0时则抛出sdl异常
    inline void nonzero_then_throw_sdl_exception(int result) {
        if(result != 0) {
            throw_sdl_exception();
        }
    }

}   // namespace utopia::client::render::sdl

#endif
