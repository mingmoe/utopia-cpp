//===--------------- texture.hpp - Texture定义 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020-2022 moe-org All rights reserved.
//
//===--------------------------------------------------------===//
/// \file
/// 封装SDL_Texture
//===--------------------------------------------------------===//


#ifndef UTOPIA_CLIENT_RENDER_SDL_TEXTURE_HPP
#define UTOPIA_CLIENT_RENDER_SDL_TEXTURE_HPP

#ifndef UTOPIA_PLATFORM_CLIENT
    #error this file is only compiled in client of utopia
#endif

namespace utopia::client::render::sdl {

    /// @brief SDL_Surface封装
    class Texture {
      private:

        SDL_Texture *handle_{nullptr};

      public:

        /// @brief 从surface和renderer创建一个texture
        Texture(SDL_Surface *surface, SDL_Renderer *renderer) {
            handle_ = SDL_CreateTextureFromSurface(renderer, surface);

            check_sdl_nullptr_error(handle_);
        }

        /// @brief 从渲染上下文创建一个texture
        /// @param renderer渲染器
        /// @param width texture宽度
        /// @param height texture高度
        /// @param format 见SDL_CreateTexture
        /// @param access 见SDL_CreateTexture
        Texture(SDL_Renderer *renderer,
                int           width,
                int           height,
                uint32_t      format = SDL_PIXELFORMAT_RGBA8888,
                int           access = SDL_TEXTUREACCESS_STREAMING) {

            handle_ =
                SDL_CreateTexture(renderer, format, access, width, height);

            check_sdl_nullptr_error(handle_);
        }


        ~Texture() noexcept {
            SDL_DestroyTexture(this->handle_);
        }

        Texture(const Texture &) = delete;
        Texture &operator=(const Texture &) = delete;
        Texture(Texture &&)                 = delete;
        Texture &operator=(Texture &&) = delete;

        /// @note 指针的生命周期同this。禁止用户手动释放此指针。
        [[nodiscard]] inline SDL_Texture *get_ptr() {
            return handle_;
        }
    };

}   // namespace utopia::client::render::sdl

#endif
