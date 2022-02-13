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

        /// @brief 从窗口创建一个渲染器
        /// @param window 窗口
        /// @param present_sync 是否与刷新率同步。（设置SDL_RENDERER_PRESENTVSYNC)
        /// @param target_texture 是否设置渲染目标为texture。（设置SDL_RENDERER_TARGETTEXTURE)
        /// @param renderer_type 渲染器类型
        Renderer(SDL_Window     *window,
                 bool            present_sync = false,
                 bool            target_texture = false,
                 SdlRendererType renderer_type  = SdlRendererType::Hardware) {
            uint32_t flag{ 0 };

            if(present_sync) {
                flag |= SDL_RENDERER_PRESENTVSYNC;
            }
            if(target_texture) {
                flag |= SDL_RENDERER_TARGETTEXTURE;
            }
            flag |= static_cast<uint32_t>(renderer_type);

            handle_ = SDL_CreateRenderer(window, -1, flag);

            null_then_throw_sdl_exception(handle_);
        }

        /// @brief 以surface为上下文创建渲染器
        Renderer(SDL_Surface     *surface) {
            handle_ = SDL_CreateSoftwareRenderer(surface);
            null_then_throw_sdl_exception(handle_);
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


}   // namespace utopia::client::render::sdl

#endif
