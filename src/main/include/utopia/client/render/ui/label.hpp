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

#include <utopia/client/render/render.hpp>

namespace utopia::client::render::ui {

    /**
     * \brief 一段文字标签
     */
    class Label : public Drawable {
      private:

        utopia::client::render::text::TextRenderInfo info_{};

        Rectangle                                    pos_;

        std::unique_ptr<sdl::Texture>                texture_{ nullptr };

      public:

        Label()              = default;
        ~Label() override    = default;

        Label(const Label &) = delete;
        Label(Label &&)      = delete;
        Label      &operator=(const Label &) = delete;
        Label      &operator=(Label &&) = delete;

        inline void set_pos(Rectangle &rect) {
            this->pos_ = rect;
        }

        inline void set_text(text::TextRenderInfo &info) {
            texture_.reset();
            this->info_ = info;
        }

        virtual void draw_to(
            std::shared_ptr<utopia::client::render::ui::Context> context)
            override {

            if(texture_.get() == nullptr) {
                const auto bitmap =
                    context->get_text_engine()->render_paragraph(this->info_);

                texture_ = std::move(context->render_to_texture(bitmap));
            }

            context->draw_texture(texture_, this->pos_);
        }
    };


}   // namespace utopia::client::render::ui


#endif
