//===--------------- surface.hpp - Surface定义 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020-2022 moe-org All rights reserved.
//
//===--------------------------------------------------------===//
/// \file
/// 封装SDL_Surface
//===--------------------------------------------------------===//


#ifndef UTOPIA_CLIENT_RENDER_SDL_SURFACE_HPP
#define UTOPIA_CLIENT_RENDER_SDL_SURFACE_HPP

#ifndef UTOPIA_PLATFORM_CLIENT
    #error this file is only compiled in client of utopia
#endif

#include <SDL.h>
#include <utopia/core/guard.hpp>
#include <utopia/client/render/sdl/error.hpp>
#include <utopia/client/render/bitmap.hpp>

namespace utopia::client::render::sdl {

    using SurfaceGuard = utopia::core::Guard<SDL_Surface, decltype(SDL_UnlockSurface)>;

    /// @brief SDL_Surface封装
    class Surface {
      private:

        SDL_Surface *handle_{ nullptr };

      public:

        /// @brief 创建一个新Surface
        /// @param width surface宽度
        /// @param height surface高度
        Surface(int      width,
                int      height,
                int      depth  = 32,
                uint32_t format = SDL_PIXELFORMAT_RGBA8888) {
            handle_ =
                SDL_CreateRGBSurfaceWithFormat(0, width, height, depth, format);

            check_sdl_nullptr_error(handle_);
        }


        ~Surface() noexcept {
            SDL_FreeSurface(this->handle_);
        }

        Surface(const Surface &) = delete;
        Surface &operator=(const Surface &) = delete;
        Surface(Surface &&)                 = delete;
        Surface &operator=(Surface &&) = delete;

        /// @brief 设置surface的RLE加速
        /// @param is_open 设置为true开启加速，否则关闭加速
        /// @exception SdlException sdl抛出错误
        inline void set_rle(bool is_open) {
            int error{ 0 };
            if(is_open) {
                error = SDL_SetSurfaceRLE(handle_, 1);
            }
            else {
                error = SDL_SetSurfaceRLE(handle_, 0);
            }
            check_sdl_nonzero_error(error);
        }

        /// @note 指针的生命周期同this。禁止用户手动释放此指针。
        [[nodiscard]] inline SDL_Surface *get_ptr() {
            return handle_;
        }

        /// @brief 上锁
        /// @exception SdlException 错误
        [[nodiscard]] inline SurfaceGuard lock() {
            auto err = SDL_LockSurface(handle_);

            check_sdl_nonzero_error(err);

            return SurfaceGuard{ this->handle_, &SDL_UnlockSurface };
        }

        /// @brief 复制位图到surface
        /// @note 此函数需要surface的像素格式为SDL_PIXELFORMAT_RGBA8888。
        /// 否则会抛出SdlException。
        /// 如果surface和bitmap的大小不一样，也抛出SdlException。
        void set_from_bitmap(Bitmap &bitmap);
    };


}   // namespace utopia::client::render::sdl

#endif
