//===--------------- renderer.cpp - Renderer实现 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020-2022 moe-org All rights reserved.
//
//===----------------------------------------------------------===//
/// \file
/// 负责实现utopia::client::render::text::Renderer。
//===----------------------------------------------------------===//

#include <ft2build.h>

#include <utopia/client/render/bitmap.hpp>
#include <utopia/client/render/text/error.hpp>
#include <utopia/client/render/text/renderer.hpp>
#include <utopia/core/convert.hpp>
#include FT_FREETYPE_H

using utopia::core::safe_convert;

uint32_t utopia::client::render::text::Renderer::get_glyph_id(
    char32_t unicode_code) {
    const auto code =
        FT_Get_Char_Index(*this->face_->get_ft_face().get(), unicode_code);
    return code;
}

utopia::client::render::Bitmap
    utopia::client::render::text::Renderer::render(uint32_t id) {
    const auto face_shared = this->face_->get_ft_face();
    const auto face_ptr    = face_shared.get();
    const auto face        = *face_ptr;
    const auto glyph       = face->glyph;

    auto       err         = FT_Load_Glyph(face, id, FT_LOAD_COLOR);

    check_freetype_error(err);

    err = FT_Render_Glyph(glyph, FT_RENDER_MODE_NORMAL);

    check_freetype_error(err);

    // 复制位图
    auto                           bitmap = glyph->bitmap;

    utopia::client::render::Bitmap output{ safe_convert<pos_t>(bitmap.width),
                                           safe_convert<pos_t>(bitmap.rows) };

    // 解析格式
    // 我们只支持 FT_PIXEL_MODE_GRAY 和 FT_PIXEL_MODE_BGRA
    if(bitmap.pixel_mode == FT_PIXEL_MODE_BGRA) {
        decltype(bitmap.rows)  row_index   = 0;
        decltype(bitmap.pitch) row_base    = 0;
        decltype(bitmap.width) width_index = 0;
        decltype(bitmap.width) width_base  = 0;
        const auto             rate        = bitmap.pitch;
        const auto             buffer      = bitmap.buffer;

        while(row_index != bitmap.rows) {

            while(width_index != bitmap.width) {
                auto b = buffer[row_base + width_base];
                auto g = buffer[row_base + width_base + 1];
                auto r = buffer[row_base + width_base + 2];
                auto a = buffer[row_base + width_base + 3];

                output.write_point(
                    width_index,
                    row_index,
                    BitmapBit{ .red = r, .green = g, .blue = b, .alpha = a });

                width_index++;
                width_base += 4;
            }

            row_index++;
            row_base += rate;
            width_base  = 0;
            width_index = 0;
        }
    }
    else if(bitmap.pixel_mode == FT_PIXEL_MODE_GRAY) {
        size_t     row_base  = 0;
        const auto rate      = bitmap.pitch;
        const auto num_grays = bitmap.num_grays;
        const auto buffer    = bitmap.buffer;

        for(size_t row_index = 0; row_index != bitmap.rows;
            row_index++, row_base += rate) {
            for(size_t width_index = 0; width_index != bitmap.width;
                width_index++) {

                auto g     = buffer[row_base + width_index];

                auto rgb_a = static_cast<decltype(BitmapBit::alpha)>(
                    std::numeric_limits<decltype(BitmapBit::alpha)>::max() *
                    (static_cast<double>(g) / static_cast<double>(num_grays)));

                output.write_point(
                    width_index,
                    row_index,
                    BitmapBit{ .red   = rgb_a,
                               .green = rgb_a,
                               .blue  = rgb_a,
                               .alpha = std::numeric_limits<
                                   decltype(BitmapBit::alpha)>::max() });
            }
        }
    }
    else {
        throw FreetypeException{
            "from utopia:unknown freetype-render bitmap format"
        };
    }

    return output;
}


utopia::client::render::text::GlyphInformation
    utopia::client::render::text::Renderer::get_info(uint32_t id) {

    const auto face_shared = this->face_->get_ft_face();
    const auto face_ptr    = face_shared.get();
    const auto face        = *face_ptr;
    const auto glyph       = face->glyph;

    const auto err         = FT_Load_Glyph(face, id, FT_LOAD_COLOR);

    check_freetype_error(err);

    utopia::client::render::text::GlyphInformation info{};
    const auto                                     metrics = glyph->metrics;
    info.height       = static_cast<int64_t>(metrics.height / 26.6);
    info.width        = static_cast<int64_t>(metrics.width / 26.6);
    info.horiAdvance  = static_cast<int64_t>(metrics.horiAdvance / 26.6);
    info.horiBearingX = static_cast<int64_t>(metrics.horiBearingX / 26.6);
    info.horiBearingY = static_cast<int64_t>(metrics.horiBearingY / 26.6);
    info.vertAdvance  = static_cast<int64_t>(metrics.vertAdvance / 26.6);
    info.vertBearingX = static_cast<int64_t>(metrics.vertBearingX / 26.6);
    info.vertBearingY = static_cast<int64_t>(metrics.vertBearingY / 26.6);

    return info;
}
