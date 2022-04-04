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

    #include <utopia/client/render/render.hpp>
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

    WindowBuilder   win_builder{};
    auto            win = win_builder.create();

    RendererBuilder renderer_builder{};

    renderer_builder.set_window(win);
    auto      render = renderer_builder.create();

    ui::Group group{};
    auto      sdl_context = SdlRenderContext::create(win, render);
    auto      context     = ui::Context::create(sdl_context);

    context->get_text_engine()->add_font(1, font);


    auto           label = std::make_shared<ui::Label>();

    TextRenderInfo info{};
    info.para.text = UNICODE_STRING_SIMPLE(
        "马之千里者，一食或尽粟一石。食马者不知其能千里而食也。是马也，虽有千里之能，食不饱，力不足，才美不外见，且欲与常马等不可得，安求其能千里也？");
    info.para.max_width_one_line = 1000;
    info.setting.point           = 14;
    info.setting.x_pixel         = 40;
    info.setting.y_pixel         = 40;

    render::Rectangle rectangle{};
    rectangle.x      = 50;
    rectangle.y      = 50;
    rectangle.x_size = 1000;
    rectangle.y_size = 240;
    label->set_pos(rectangle);
    label->set_text(info);

    group.add_item(label);


    SDL_Event test_event;


    SDL_SetRenderDrawColor(render->get_ptr(), 255, 255, 255, 0);

    while(true) {
        SDL_RenderPresent(render->get_ptr());
        SDL_RenderClear(render->get_ptr());
        group.draw(context);

        while(SDL_PollEvent(&test_event)) {
        }
    }


    return 0;
}

#endif
