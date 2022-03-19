//===--------------- drawable.hpp - drawable头文件 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020-2022 moe-org All rights reserved.
//
//===------------------------------------------------------------===//
/// \file
/// 声明Drawable接口。此接口代表一个类可以被渲染。
//===------------------------------------------------------------===//

#ifndef UTOPIA_CLIENT_RENDER_UI_DRAWABLE
#define UTOPIA_CLIENT_RENDER_UI_DRAWABLE

#include <utopia/client/render/sdl/renderer.hpp>
#include <utopia/client/render/sdl/window.hpp>

namespace utopia::inline client::inline render::inline ui {

    /// @brief 一个接口。代表可渲染组件。
    class Drawable {
      public:

        Drawable()                 = default;
        virtual ~Drawable()        = default;

        Drawable(const Drawable &) = delete;
        Drawable(Drawable &&)      = delete;
        Drawable &operator=(const Drawable &) = delete;
        Drawable &operator=(Drawable &&) = delete;

        /// @brief 渲染目的地
        virtual void draw_to(utopia::Window   &window,
                             utopia::sdl::Renderer &renderer) = 0;
    };

}   // namespace utopia::inline client::inline render::inline ui

#endif
