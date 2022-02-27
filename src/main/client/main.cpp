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
    #include <vector>

    #include <utopia/client/render/sdl/sdl.hpp>
    #include <utopia/client/render/text/text.hpp>
#include <utopia/core/debug.hpp>

static auto source = utopia::client::render::text::FileFontSource::create(
    "C:\\Users\\mingm\\Project\\utopia\\build\\src\\main\\client\\Debug\\font.ttf");

static auto library = utopia::client::render::text::Library::create();

static auto font =
    utopia::client::render::text::Font::create(source, library, 0);

static auto face     = utopia::client::render::text::Face::create(font);

static auto renderer = utopia::client::render::text::Renderer::create(face);

static auto shaper   = utopia::client::render::text::Shaper::create();

std::unique_ptr<utopia::client::render::sdl::Texture>
    get_font(char32_t code, utopia::client::render::sdl::Renderer &render) {

    face->set_size(50, 50, 14);

    auto                                 id     = renderer->get_glyph_id(code);
    auto                                 bitmap = renderer->render(id);

    utopia::client::render::sdl::Surface surface{
        static_cast<int>(bitmap.get_x_size()),
        static_cast<int>(bitmap.get_y_size())
    };

    surface.set_from_bitmap(bitmap);

    auto texture = std::make_unique<utopia::client::render::sdl::Texture>(
        surface.get_ptr(),
        render.get_ptr());

    return std::move(texture);
}


/// @brief      入口函数
// @param argc 参数数量
// @param argv 参数
/// @return 程序返回值。如果正常退出返回0，否则返回非0值；
int main(int /*argc*/, char * /*argv*/[]) {

    utopia::client::render::sdl::Window   window{ "😅", 1024, 768 };

    utopia::client::render::sdl::Renderer w_renderer{ window.get_ptr() };

    std::vector<std::unique_ptr<utopia::client::render::sdl::Texture>> bitmaps;

    bitmaps.push_back(std::move(get_font('😅', w_renderer)));

    SDL_Rect current_rect{};
    current_rect.x = 50;
    current_rect.y = 50;
    current_rect.w = 500;
    current_rect.h = 500;

    while(true) {

        SDL_RenderClear(w_renderer.get_ptr());

        for(auto &s_char : bitmaps) {
            SDL_RenderCopy(w_renderer.get_ptr(),
                           s_char->get_ptr(),
                           NULL,
                           &current_rect);
        }

        SDL_RenderPresent(w_renderer.get_ptr());
    }

    return 0;
}

#endif
