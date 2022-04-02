//===--------------- renderer.hpp - 渲染器定义 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020-2022 moe-org All rights reserved.
//
//===-------------------------------------------------------===//
/// \file
/// 封装SDL_Renderer
//===-------------------------------------------------------===//


#ifndef UTOPIA_CLIENT_RENDER_SDL_RENDERER_HPP
#define UTOPIA_CLIENT_RENDER_SDL_RENDERER_HPP

#ifndef UTOPIA_PLATFORM_CLIENT
    #error this file is only compiled in client of utopia
#endif

#include <SDL.h>

#include <utopia/core/pointer.hpp>

namespace utopia::client::render::sdl {

    /// @brief SDL_Renderer渲染器类型
    enum class SdlRendererType : uint32_t
    {
        /// @brief 软件渲染器
        Software = SDL_RENDERER_SOFTWARE,
        /// @brief 硬件渲染器
        Hardware = SDL_RENDERER_ACCELERATED
    };

    /// @brief SDL_Renderer的封装
    class Renderer {
      private:

        SDL_Renderer *handle_{ nullptr };

      public:

        /// @brief 以surface为上下文创建渲染器
        Renderer(SDL_Surface *surface) {
            handle_ = SDL_CreateSoftwareRenderer(surface);
            check_sdl_nullptr_error(handle_);
        }

        /// @brief 从已有指针构造，将会转移所有权
        Renderer(utopia::core::MovedPointer<SDL_Renderer> &&renderer) {
            this->handle_ = renderer.release();
        }

        ~Renderer() noexcept {
            SDL_DestroyRenderer(this->handle_);
        }

        Renderer(const Renderer &) = delete;
        Renderer &operator=(const Renderer &) = delete;
        Renderer(Renderer &&)                 = delete;
        Renderer &operator=(Renderer &&) = delete;

        /// @note 指针的生命周期同this。禁止用户手动释放此指针。
        [[nodiscard]] inline SDL_Renderer *get_ptr() {
            return handle_;
        }
    };


    /// @brief 渲染器构建器
    class RendererBuilder {
      private:

        uint32_t                flag_{ 0 };

        std::shared_ptr<Window> win_;

        int                     index_{ -1 };

      public:

        inline void set_preset_sync(bool enable) {
            if(enable) {
                flag_ |= SDL_RENDERER_PRESENTVSYNC;
            }
            else {
                flag_ &= !SDL_RENDERER_PRESENTVSYNC;
            }
        }

        inline void set_target_texture(bool enable) {
            if(enable) {
                flag_ |= SDL_RENDERER_TARGETTEXTURE;
            }
            else {
                flag_ &= !SDL_RENDERER_TARGETTEXTURE;
            }
        }

        inline void set_type(SdlRendererType type) {
            if(type == SdlRendererType::Hardware) {
                flag_ |= static_cast<uint32_t>(type);
                flag_ &= !static_cast<uint32_t>(SdlRendererType::Software);
            }
            else {
                flag_ |= static_cast<uint32_t>(type);
                flag_ &= !static_cast<uint32_t>(SdlRendererType::Hardware);
            }
        }

        inline void set_window(std::shared_ptr<Window> win) {
            this->win_ = win;
        }

        inline void set_index(int index) {
            this->index_ = index;
        }

        [[nodiscard]] inline Renderer create() {

            auto handle =
                SDL_CreateRenderer(this->win_->get_ptr(), index_, flag_);

            check_sdl_nullptr_error(handle);

            return Renderer{ utopia::core::move_ptr<SDL_Renderer>(handle) };
        }
    };


}   // namespace utopia::client::render::sdl

#endif
