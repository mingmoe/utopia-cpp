//===--------------- surface.cpp - Surface实现 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020-2022 moe-org All rights reserved.
//
//===-------------------------------------------------------===//
/// \file
/// 这个文件是utopia::client::render::sdl::Surface的实现。
//===-------------------------------------------------------===//

#include <cstdint>

#include <utopia/client/render/sdl/surface.hpp>


void utopia::client::render::sdl::Surface::set_from_bitmap(Bitmap &bitmap) {
    if(this->handle_->format->format != SDL_PIXELFORMAT_RGBA8888) {
        throw SdlException{ "from utopia:unknown surface pixel format" };
    }
    if(bitmap.get_x_size() != this->handle_->w ||
       bitmap.get_y_size() != this->handle_->h) {
        throw SdlException{ "from utopia:bitmap size not match" };
    }

    auto locker = lock();

    // NOLINTNEXTLINE
    auto           buffer = reinterpret_cast<char *>(this->handle_->pixels);

    const uint64_t x      = bitmap.get_x_size();
    const uint64_t y      = bitmap.get_y_size();

    const uint64_t rate   = this->handle_->pitch;

    for(uint64_t y_index = 0, y_base = 0; y_index != y;
        y_index++, y_base += rate) {
        for(uint64_t x_index = 0, x_base = 0; x_index != x;
            x_index++, x_base += 4) {
            auto bit                    = bitmap.get_point(x_index, y_index);

            buffer[y_base + x_base]     = bit.red;
            buffer[y_base + x_base + 1] = bit.green;
            buffer[y_base + x_base + 2] = bit.blue;
            buffer[y_base + x_base + 3] = bit.alpha;
        }
    }
}
