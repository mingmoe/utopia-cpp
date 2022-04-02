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

#include <SDL.h>
#include <cstdint>
#include <string_view>
#include <unicode/unistr.h>

#include <utopia/client/render/sdl/error.hpp>
#include <utopia/core/i18n/icu.hpp>
#include <utopia/core/pointer.hpp>
#include <utopia/core/convert.hpp>

namespace utopia::client::render::sdl {

    /// @brief SDL_Window的封装
    class Window {
      private:

        SDL_Window *handle_{ nullptr };
        int         width_;
        int         height_;

      public:

        /// @brief 从已有窗口构造一个窗口
        Window(utopia::core::MovedPointer<SDL_Window> &&win) {
            this->handle_ = win.release();
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

    /// @brief SDL窗口构造器
    class WindowBuilder {
      private:

        icu::UnicodeString title_{ UNICODE_STRING_SIMPLE("UTOPIA") };
        uint32_t           width_{ 1024 };
        uint32_t           height_{ 768 };
        uint32_t           flag_{ 0 };

      public:

        WindowBuilder(const WindowBuilder &) = delete;
        WindowBuilder &operator=(const WindowBuilder &) = delete;
        WindowBuilder(WindowBuilder &&)                 = delete;
        WindowBuilder &operator=(WindowBuilder &&) = delete;

        inline void    set_size(uint32_t width, uint32_t height) noexcept {
            this->width_ = width;
            this->height_ = height;
        }

        inline void set_title(icu::UnicodeString title) {
            this->title_ = title;
        }

        inline void set_full_screen(bool enable) noexcept {
            if(enable) {
                this->flag_ |= SDL_WINDOW_FULLSCREEN_DESKTOP;
            }
            else {
                this->flag_ &= !SDL_WINDOW_FULLSCREEN_DESKTOP;
            }
        }

        [[nodiscard]] inline Window create() {

            std::unique_ptr<char[]> title_c{};

            icu::StringByteSink sink{ new std::string{} };

            this->title_.toUTF8(sink);

            auto window = SDL_CreateWindow(title_c.get(),
                                           SDL_WINDOWPOS_CENTERED,
                                           SDL_WINDOWPOS_CENTERED,
                                           this->width_,
                                           this->height_,
                                           this->flag_);
            check_sdl_nullptr_error(window);

            return Window{ utopia::core::move_ptr<SDL_Window>(window) };
        }
    };


}   // namespace utopia::client::render::sdl

#endif
