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
#include <utopia/client/render/text/text.hpp>

namespace utopia::inline client::inline render::inline ui {

    /// @brief 上下文
    class Context {
      private:

        /// @brief 渲染窗口
        std::shared_ptr<utopia::Window> window_;
        /// @brief 渲染器
        std::shared_ptr<utopia::sdl::Renderer> renderer_;
        /// @brief 渲染引擎
        std::shared_ptr<utopia::Engine> text_engine_;

      public:
    };


}   // namespace utopia::inline client::inline render::inline ui


#endif
