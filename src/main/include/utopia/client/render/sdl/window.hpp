//===--------------- window.hpp - 窗口定义 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020-2022 moe-org All rights reserved.
//
//===---------------------------------------------------===//
/// \file
/// 封装SDL_Window
//===---------------------------------------------------===//

#ifndef UTOPIA_CLIENT_RENDER_SDL_WINDOWS_HPP
#define UTOPIA_CLIENT_RENDER_SDL_WINDOWS_HPP

#ifndef UTOPIA_PLATFORM_CLIENT
    #error this file is only compiled in client of utopia
#endif

#include <SDL2/SDL.h>
#include <cstdint>
#include <string_view>

#include <utopia/client/render/sdl/error.hpp>

namespace utopia::client::render::sdl {


    /// @brief SDL_Window的封装
    class Window {
      private:

        SDL_Window *handle_{ nullptr };
        int         width_;
        int         height_;

      public:

        /// @brief 构造一个窗口
        /// @param width 窗口宽度
        /// @param heigh 窗口高度
        Window(std::string_view title,
               int              width,
               int              height,
               uint32_t         flag = 0) :
            width_(width),
            height_(height) {
            handle_ = SDL_CreateWindow(title.data(),
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       width,
                                       height,
                                       flag);
            check_sdl_nullptr_error(handle_);
        }

        ~Window() noexcept {
            SDL_DestroyWindow(this->handle_);
        }

        Window(const Window &) = delete;
        Window &operator=(const Window &) = delete;
        Window(Window &&)                 = delete;
        Window &operator=(Window &&) = delete;

        /// @brief 获取SDL_Window指针
        /// @note 指针的生命周期同this。禁止用户手动释放此指针。
        [[nodiscard]] inline SDL_Window *get_ptr() {
            return handle_;
        }

        [[nodiscard]] inline int get_width() {
            SDL_GetWindowSize(handle_, &width_, &height_);
            return width_;
        }

        [[nodiscard]] inline int get_heighy() {
            SDL_GetWindowSize(handle_, &width_, &height_);
            return height_;
        }
    };

}   // namespace utopia::client::render::sdl

#endif
