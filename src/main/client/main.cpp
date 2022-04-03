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
    #include <unicode/ustream.h>
    #include <vector>

    #include <utopia/client/render/sdl/sdl.hpp>
    #include <utopia/client/render/text/text.hpp>
    #include <utopia/core/convert.hpp>
    #include <utopia/core/debug.hpp>

using namespace utopia::client;
using namespace utopia::client::render;
using namespace utopia::client::render::text;
using namespace utopia::client::render::sdl;
using namespace utopia::core;
using namespace std;

std::shared_ptr<Face> load_font(std::string path) {
    auto source  = FileFontSource::create(path);
    auto library = Library::create();

    auto font    = Font::create(source, library, 0);
    auto face    = Face::create(font);

    return face;
}

/// @brief      入口函数
// @param argc 参数数量
// @param argv 参数
/// @return 程序返回值。如果正常退出返回0，否则返回非0值；
int main(int /*argc*/, char * /*argv*/[]) {

    auto font = load_font(
        R"PATH(C:\Users\mingm\Project\utopia\build\src\main\client\Debug\unifont.ttf)PATH");

    auto engine = Engine::create();

    engine->add_font(1, font);

    TextRenderInfo info{};
    info.para.text               = UNICODE_STRING_SIMPLE("海纳百川，有容乃大");
    info.para.max_width_one_line = 200;
    info.setting.point           = 14;
    info.setting.x_pixel         = 40;
    info.setting.y_pixel         = 40;
    auto            bitmap       = engine->render_paragraph(info);

    WindowBuilder   win_builder{};
    auto            win = win_builder.create();

    RendererBuilder renderer_builder{};

    renderer_builder.set_window(win);
    auto    render = renderer_builder.create();

    Surface surface{ safe_convert<int>(bitmap.get_x_size()),
                     safe_convert<int>(bitmap.get_y_size()) };
    surface.set_from_bitmap(bitmap);

    Texture  texture{ surface.get_ptr(), render->get_ptr() };

    SDL_Rect rect{};
    rect.x = 50;
    rect.y = 50;
    rect.w = bitmap.get_x_size();
    rect.h = bitmap.get_y_size();

    write_bitmap_as_chars(bitmap);


    SDL_SetRenderDrawColor(render->get_ptr(), 255, 255, 255, 0);

    while(true) {
        SDL_RenderPresent(render->get_ptr());
        SDL_RenderClear(render->get_ptr());
        SDL_RenderCopy(render->get_ptr(), texture.get_ptr(), nullptr, &rect);
    }


    return 0;
}

#endif
