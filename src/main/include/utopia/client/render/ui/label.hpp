//===--------------- label.hpp - label头文件 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020-2022 moe-org All rights reserved.
//
//===------------------------------------------------------------===//
/// \file
/// 声明Label类。此类代表一段文本。
//===------------------------------------------------------------===//

#ifndef UTOPIA_CLIENT_RENDER_UI_LABEL_HPP
#define UTOPIA_CLIENT_RENDER_UI_LABEL_HPP

#include <unicode/unistr.h>

#include <utopia/client/render/ui/drawable.hpp>

namespace utopia::inline client::inline render::inline ui {

    class Label : public Drawable {
      private:

        /// @brief 要渲染的文本
        icu::UnicodeString text_;

      public:
    };


}   // namespace utopia::inline client::inline render::inline ui


#endif
