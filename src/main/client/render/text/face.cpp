//===--------------- face.cpp - 字面类型实现 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020-2022 moe-org All rights reserved.
//
//===----------------------------------------------------===//
/// \file
/// 这个文件实现了字体字面类型(utopia::client::Face)。
//===----------------------------------------------------===//

#include <utopia/client/render/text/error.hpp>
#include <utopia/client/render/text/face.hpp>

void utopia::client::render::text::Face::set_size(int x, int y, float point) {
    x_size_ = x;
    y_size_ = y;
    point_  = point;

    // 设置磅值
    hb_font_set_ptem(this->hb_font_.get(), static_cast<float>(point));

    auto ft_error_code = FT_Set_Char_Size(
        *this->ft_face_.get(),
        // 磅值
        static_cast<FT_F26Dot6>(std::floor(point * 64)),
        static_cast<FT_F26Dot6>(std::floor(point * 64)),
        // dpi will be ignored because we will call FT_Set_Pixel_Sizes
        72,
        72);

    check_freetype_error(ft_error_code);

    // 设置像素大小
    hb_font_set_ppem(this->hb_font_.get(), x, y);

    ft_error_code = FT_Set_Pixel_Sizes(*ft_face_.get(), x, y);

    check_freetype_error(ft_error_code);

    // 设置字体的比例为这个像素大小
    // ref:https://github.com/harfbuzz/harfbuzz/discussions/3453#discussioncomment-2206597
    hb_font_set_scale(hb_font_.get(), x, y);
}
