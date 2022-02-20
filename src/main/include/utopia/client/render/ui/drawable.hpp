//===--------------- drawable.hpp - drawable头文件 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020-2022 moe-org All rights reserved.
//
//===------------------------------------------------------------===//
/// \file
/// 声明Drawable类。此类代表一个类可以被渲染。
//===------------------------------------------------------------===//

namespace utopia::client::render::ui {

    /// @brief 一个接口。代表可渲染组件。
    class Drawable {
      public:

        virtual ~Drawable()        = default;

        Drawable(const Drawable &) = delete;
        Drawable(Drawable &&)      = delete;
        Drawable &operator=(const Drawable &) = delete;
        Drawable &operator=(Drawable &&) = delete;
    };

}   // namespace utopia::client::render::ui
