//===--------------- context.hpp - context头文件 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020-2022 moe-org All rights reserved.
//
//===----------------------------------------------------------===//
/// \file
/// 声明Context类。此类集合渲染所需要的信息。如Window和Renderer等。
//===----------------------------------------------------------===//

#ifndef UTOPIA_CLIENT_RENDER_UI_CONTEXT_HPP
#define UTOPIA_CLIENT_RENDER_UI_CONTEXT_HPP

#include <memory>

#include <utopia/client/render/sdl/sdl.hpp>
#include <utopia/client/render/sdl_context.hpp>
#include <utopia/client/render/text/text.hpp>

namespace utopia::client::render::ui {

    /// @brief 渲染上下文
    class Context {
      private:

        std::shared_ptr<utopia::client::render::SdlRenderContext> context_;

        std::shared_ptr<utopia::client::render::text::Engine>     text_engine_;

        explicit Context(std::shared_ptr<utopia::client::render::SdlRenderContext> sdl) :
            context_(sdl), text_engine_(text::Engine::create()) {}

      public:

        [[nodiscard]] inline static std::shared_ptr<Context> create(
            std::shared_ptr<utopia::client::render::SdlRenderContext> sdl) {
            return std::shared_ptr<Context>(new Context{ sdl });
        }

        ~Context()               = default;

        Context(const Context &) = delete;
        Context &operator=(const Context &) = delete;
        Context(Context &&)                 = delete;
        Context &operator=(Context &&) = delete;

        [[nodiscard]] inline std::shared_ptr<
            utopia::client::render::SdlRenderContext>
            get_sdl_context() {
            return this->context_;
        }

        [[nodiscard]] inline std::shared_ptr<
            utopia::client::render::text::Engine>
            get_text_engine() {
            return this->text_engine_;
        }

        inline std::unique_ptr<sdl::Texture> render_to_texture(const Bitmap& bitmap) {
            sdl::Surface surface{ bitmap.get_x_size(), bitmap.get_y_size() };

            surface.set_from_bitmap(bitmap);

            auto texture = std::make_unique<sdl::Texture>(
                surface.get_ptr(),
                this->get_sdl_context()->get_renderer()->get_ptr()
            );

            return texture;
        }

        inline void draw_texture(std::unique_ptr<sdl::Texture>& texture,
            const Rectangle& pos) {
            SDL_Rect rect{};
            rect.x = pos.x;
            rect.y = pos.y;
            rect.w = pos.x_size;
            rect.h = pos.y_size;

            SDL_RenderCopy(this->get_sdl_context()->get_renderer()->get_ptr(),
                           texture->get_ptr(),
                           nullptr,
                           &rect);
        }

    };


}   // namespace utopia::client::render::ui


#endif
