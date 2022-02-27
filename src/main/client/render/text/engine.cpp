//===--------------- engine.cpp - 字体渲染引擎实现 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020-2022 moe-org All rights reserved.
//
//===----------------------------------------------------------===//
/// \file
/// 这个文件实现了字体渲染引擎(utopia::client::Engine)。
//===----------------------------------------------------------===//

#include <unicode/brkiter.h>

#include <utopia/client/render/text/text.hpp>
#include <utopia/core/i18n/icu.hpp>

using namespace utopia::client::render;
using namespace utopia::client::render::text;

[[nodiscard]] void Engine::add_font(uint64_t              priority,
                                    std::shared_ptr<Face> font) {

    auto it = this->font_list_.find(priority);

    if(it == this->font_list_.cend()) {
        std::vector<std::pair<std::shared_ptr<Face>, std::shared_ptr<Renderer>>>
            fonts{};
        fonts.push_back(std::pair(font, Renderer::create(font)));
        font_list_.insert(std::make_pair(priority, fonts));
    }
    else {
        it->second.push_back(std::pair(font, Renderer::create(font)));
    }
}
std::map<
    uint64_t,
    std::vector<std::pair<std::shared_ptr<Face>, std::shared_ptr<Renderer>>>,
    CompareFontPriority>
    Engine::get_font_list() {
    return this->font_list_;
}

[[nodiscard]] Bitmap Engine::render(uint32_t          unicode_code,
                                    TextRenderSetting settings) {
    auto &list = this->font_list_;

    for(auto p = list.cbegin(); p != list.cend(); p++) {
        auto &vec = p->second;

        for(auto it = vec.cbegin(); it != vec.cend(); it++) {
            auto &renderer = it->second;
            auto &face     = it->first;

            auto  id       = renderer->get_glyph_id(unicode_code);

            if(id == 0) {
                // not found
                // next!
                continue;
            }

            // found, render
            face->set_size(settings.x_pixel, settings.y_pixel, settings.point);
            return renderer->render(id);
        }
    }

    return Bitmap{ settings.x_pixel, settings.y_pixel };
}

// 这个更是重量级
[[nodiscard]] Bitmap Engine::render_paragraph(TextRenderInfo &para) {
    // first, we shape
    this->text_shaper_->reset();
    this->text_shaper_->set_direction(para.para.direction);
    this->text_shaper_->set_language(para.para.language);
    this->text_shaper_->set_script(para.para.script);
    this->text_shaper_->add_text(para.para.text,
                                 para.para.paragraph_start_index,
                                 para.para.paragraph_length);
    auto        data = this->text_shaper_->shape(nullptr);

    UErrorCode  err = U_ZERO_ERROR;

    icu::Locale locale{ para.para.language.c_str() };
    auto        brk = icu::BreakIterator::createWordInstance(locale, err);

    core::i18n::check_icu_error_code(err);

    brk->setText(para.para.text);

    


    return Bitmap{ 1, 1 };
}
