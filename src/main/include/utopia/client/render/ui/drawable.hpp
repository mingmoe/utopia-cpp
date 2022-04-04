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

#ifndef UTOPIA_CLIENT_RENDER_UI_DRAWABLE_HPP
#define UTOPIA_CLIENT_RENDER_UI_DRAWABLE_HPP

#include <utopia/client/render/ui/context.hpp>

namespace utopia::client::render::ui {

    /// @brief 一个接口。代表可渲染组件。
    class Drawable {
      public:

        Drawable()                 = default;
        virtual ~Drawable()        = default;

        Drawable(const Drawable &) = delete;
        Drawable(Drawable &&)      = delete;
        Drawable &operator=(const Drawable &) = delete;
        Drawable &operator=(Drawable &&) = delete;

        /// @brief 渲染
        virtual void draw_to(
            std::shared_ptr<utopia::client::render::ui::Context> context) = 0;
    };

}   // namespace utopia::inline client::inline render::inline ui

#endif
