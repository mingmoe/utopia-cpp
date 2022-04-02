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

    /// @brief 上下文
    class Context {
      private:

        std::shared_ptr<utopia::client::render::SdlRenderContext> context_;

        Context(std::shared_ptr<utopia::client::render::SdlRenderContext> sdl) :
            context_(sdl) {}

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
            get_sdl_conetxt() {
            return this->context_;
        }
    };


}   // namespace utopia::client::render::ui


#endif
