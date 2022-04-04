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
#include <unicode/schriter.h>

#include <utopia/client/render/text/text.hpp>
#include <utopia/core/i18n/icu.hpp>

using namespace utopia::client::render;
using namespace utopia::client::render::text;

[[nodiscard]] std::pair<std::shared_ptr<Face>, std::shared_ptr<Renderer>>
    Engine::get_first_exist_glyph(uint32_t unicode_code, uint32_t &output_id) {

    // 防止我们在没有任何字体的情况下不返回0
    output_id  = 0;

    auto &list = this->font_list_;

    for(auto p = list.cbegin(); p != list.cend(); p++) {
        auto &vec = p->second;

        for(auto it = vec.cbegin(); it != vec.cend(); it++) {
            auto &renderer = it->second;

            output_id      = renderer->get_glyph_id(unicode_code);

            if(output_id == 0) {
                // not found
                // next!
                continue;
            }

            // found
            return *it;
        }
    }

    // not found for all face
    return std::make_pair(std::shared_ptr<Face>{ nullptr },
                          std::shared_ptr<Renderer>{ nullptr });
}

void Engine::add_font(uint64_t priority, std::shared_ptr<Face> font) {

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

    uint32_t id{ 0 };
    auto     face = this->get_first_exist_glyph(unicode_code, id);

    if(id != 0) {
        face.first->set_size(settings.x_pixel,
                             settings.y_pixel,
                             settings.point);
        return face.second->render(id);
    }
    else if(unicode_code != U'\uFFFD') {
        // not found,return �
        return render(U'\uFFFD', settings);
    }
    else {
        // not found again,return empty
        return Bitmap{ core::safe_convert<pos_t>(settings.x_pixel),
                       core::safe_convert<pos_t>(settings.y_pixel) };
    }
}

// 这个更是重量级
// 目前，我们没有为复杂脚本设计
// 仅仅简单渲染简单脚本
[[nodiscard]] Bitmap Engine::render_paragraph(TextRenderInfo &para) {

    // 分行
    auto lines = core::i18n::split_line(para.para.text);

    // 准备断行

    const auto max_width_one_line = para.para.max_width_one_line;
    const auto space_size =
        static_cast<uint32_t>(std::floor(para.setting.x_pixel / 2));


    std::vector<icu::UnicodeString> output_lines;

    // 开始断行
    for(auto &line : lines) {
        int64_t                      width = 0;

        icu::StringCharacterIterator it{ line };

        UChar32                      c{ 0 };
        int32_t                      last_index = 0;

        // 每个字符遍历
        while((c = it.next32PostInc()) != it.DONE) {


            if(width >= max_width_one_line) {
                output_lines.push_back(std::move(
                    line.tempSubStringBetween(last_index, it.getIndex())));
                last_index = it.getIndex();
                width      = 0;
            }

            if(c == ' ') {
                width += space_size;
            }
            else {
                uint32_t id{ 0 };
                auto     face = this->get_first_exist_glyph(c, id);


                if(id != 0) {
                    face.first->set_size(para.setting.x_pixel,
                                         para.setting.y_pixel,
                                         para.setting.point);

                    width += face.second->get_info(id).width;
                }
                else {
                    width += para.setting.x_pixel;
                }
            }
        }
        // last line
        output_lines.push_back(
            std::move(line.tempSubStringBetween(last_index)));
    }
    // 渲染
    Bitmap bitmap{ core::safe_convert<pos_t>(max_width_one_line),
                   core::safe_convert<pos_t>(output_lines.size() *
                                             para.setting.y_pixel) };

    pos_t  line_index{ 0 };

    for(auto &line : output_lines) {

        icu::StringCharacterIterator it{ line };
        pos_t                        width_index{ 0 };

        UChar32                      c{ 0 };

        while((c = it.next32PostInc()) != it.DONE) {

            if(c == ' ') {
                width_index += space_size;
            }
            else {

                auto rendered = this->render(c, para.setting);
                rendered.copy_into(bitmap, width_index, line_index);

                width_index += rendered.get_x_size();
            }
        }

        line_index += para.setting.y_pixel;
    }

    return bitmap;
}
