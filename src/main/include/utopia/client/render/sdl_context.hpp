//===--------------- sdl_context.hpp - SDL窗口上下文定义 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020-2022 moe-org All rights reserved.
//
//===----------------------------------------------------------------===//
/// \file
/// 这个文件定义了用于SDL窗口的渲染上下文。
//===----------------------------------------------------------------===//

#ifndef UTOPIA_CLIENT_RENDER_SDL_CONTEXT_HPP
#define UTOPIA_CLIENT_RENDER_SDL_CONTEXT_HPP

#ifndef UTOPIA_PLATFORM_CLIENT
    #error this file is only compiled in client of utopia
#endif

#include <memory>

#include <utopia/client/render/sdl/sdl.hpp>

namespace utopia::client::render {

    /**
     * @brief SDL渲染上下文
    */
    class SdlRenderContext {
      private:

        std::shared_ptr<sdl::Window>   window_;
        std::shared_ptr<sdl::Renderer> renderer_;

        SdlRenderContext(std::shared_ptr<sdl::Window>   window,
                         std::shared_ptr<sdl::Renderer> renderer) :
            window_(window),
            renderer_(renderer) {}

      public:

        [[nodiscard]] inline static std::shared_ptr<SdlRenderContext>
            create(std::shared_ptr<sdl::Window>   window,
                   std::shared_ptr<sdl::Renderer> renderer) {
            return std::shared_ptr<SdlRenderContext>(
                new SdlRenderContext{ std::move(window), std::move(renderer) });
        }

        ~SdlRenderContext()                        = default;

        SdlRenderContext(const SdlRenderContext &) = delete;
        SdlRenderContext &operator=(const SdlRenderContext &) = delete;
        SdlRenderContext(SdlRenderContext &&)                 = delete;
        SdlRenderContext &operator=(SdlRenderContext &&) = delete;

        [[nodiscard]] inline std::shared_ptr<sdl::Window> get_window() {
            return this->window_;
        }

        [[nodiscard]] inline std::shared_ptr<sdl::Renderer> get_renderer() {
            return this->renderer_;
        }
    };

}   // namespace utopia::client::render

#endif
