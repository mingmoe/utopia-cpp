//===--------------- main.cpp - 入口函数定义 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020 - 2022 moe - org All rights reserved.
//
//===-----------------------------------------------------===//
/// \file
/// 这个文件定义了utopia的入口函数(main)。
/// 不应该与测试相链接。
//===-----------------------------------------------------===//

#ifndef UTOPIA_PLATFORM_TEST
    #ifndef UTOPIA_PLATFORM_CLIENT
        #error this file is only compiled in client of utopia
    #endif

    #include <iostream>
    #include <memory>

    #include <utopia/client/render/text/text.hpp>

/// @brief      入口函数
// @param argc 参数数量
// @param argv 参数
/// @return 程序返回值。如果正常退出返回0，否则返回非0值；
int main(int /*argc*/, char * /*argv*/[]) {

    auto source =
        utopia::client::render::text::FileFontSource::create(
            "C:\\Users\\mingm\\Project\\utopia\\build\\src\\main\\client\\Debug\\font.ttf");

    auto library  = utopia::client::render::text::Library::create();

    auto font     = utopia::client::render::text::Font::create(source, library);

    auto face     = utopia::client::render::text::Face::create(font, 0);

    face->set_size(24, 24, 14);

    auto renderer = utopia::client::render::text::Renderer::create(face);

    auto code     = renderer->get_glyph_id(U'行');

    std::cout << "code:" << code << std::endl;

    auto bitmap   = renderer->render(code);

    auto x        = bitmap.get_x_size();
    auto y        = bitmap.get_y_size();

    for(uint64_t y_ptr = 0; y_ptr < y; y_ptr++) {
        for(uint64_t x_ptr = 0; x_ptr < x; x_ptr++) {
            auto bit = bitmap.get_point(x_ptr, y_ptr);

            if(bit.alpha != 0) {
                std::cout << "*";
            }
            else {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }
    
    return 0;
}

#endif
