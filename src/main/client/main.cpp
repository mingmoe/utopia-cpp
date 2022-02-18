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

static auto source = utopia::client::render::text::FileFontSource::create(
    "C:\\Users\\mingm\\Project\\utopia\\build\\src\\main\\client\\Debug\\font.ttf");

static auto library = utopia::client::render::text::Library::create();

static auto font =
    utopia::client::render::text::Font::create(source, library, 0);

static auto face     = utopia::client::render::text::Face::create(font);

static auto renderer = utopia::client::render::text::Renderer::create(face);

static auto shaper   = utopia::client::render::text::Shaper::create();

std::unique_ptr<utopia::client::render::sdl::Texture>
    get_font(char32_t id, utopia::client::render::sdl::Renderer &render) {

    face->set_size(50, 50, 14);

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

    utopia::client::render::sdl::Window   window{ "PHP", 1024, 768 };

    utopia::client::render::sdl::Renderer renderer{ window.get_ptr() };

    // 排版
    shaper->add_text(UNICODE_STRING_SIMPLE("😅😅😅"), 0, -1);

    shaper->set_direction_left_to_right(true);
    shaper->set_language("en-US");
    shaper->set_script("215");

    auto result = shaper->shape(face);

    std::vector<std::pair<std::unique_ptr<utopia::client::render::sdl::Texture>,
                          SDL_Rect>>
        text_results{};

    for(auto &signle_char : result) {
        auto font = get_font(signle_char.glyph_index, renderer);
        auto goes = SDL_Rect{};

        //goes.x    = signle_char.x_advance;
        //goes.y    = signle_char.y_advance;
        goes.x = 50;

        text_results.push_back(std::make_pair(std::move(font), goes));
    }

    SDL_Rect texture_rect;
    texture_rect.x        = 50;   // the x coordinate
    texture_rect.y        = 50;   // the y coordinate
    texture_rect.w        = 50;   // the width of the texture
    texture_rect.h        = 50;   // the height of the texture

    SDL_Rect current_rect = texture_rect;

    while(true) {

        SDL_RenderClear(renderer.get_ptr());

        for(auto &s_char : text_results) {
            auto texture = &s_char.first;
            auto pos     = &s_char.second;

            SDL_RenderCopy(renderer.get_ptr(),
                           texture->get()->get_ptr(),
                           NULL,
                           &current_rect);

            current_rect.x += pos->x;
        }
        current_rect = texture_rect;

        SDL_RenderPresent(renderer.get_ptr());
    }

    return 0;
}

#endif
