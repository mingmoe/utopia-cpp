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
    if(bitmap.get_x_size() != static_cast<uint64_t>(this->handle_->w) ||
       bitmap.get_y_size() != static_cast<uint64_t>(this->handle_->h)) {
        throw SdlException{ "from utopia:bitmap size not match" };
    }

    auto locker = lock();

    // NOLINTNEXTLINE
    auto           buffer = reinterpret_cast<char *>(this->handle_->pixels);

    const int      bpp    = this->handle_->format->BytesPerPixel;


    const uint64_t x      = bitmap.get_x_size();
    const uint64_t y      = bitmap.get_y_size();

    const uint64_t pitch  = this->handle_->pitch;

    for(uint64_t y_index = 0, y_base = 0; y_index != y;
        y_index++, y_base += pitch) {

        for(uint64_t x_index = 0, x_base = 0; x_index != x;
            x_index++, x_base += bpp) {
            auto     bit   = bitmap.get_point(x_index, y_index);

            auto     value = SDL_MapRGBA(this->handle_->format,
                                     bit.red,
                                     bit.green,
                                     bit.blue,
                                     bit.alpha);
            uint8_t *base_index =
                reinterpret_cast<uint8_t *>(&buffer[y_base + x_base]);
            uint16_t *buffer2 = reinterpret_cast<uint16_t *>(base_index);
            uint32_t *buffer4 = reinterpret_cast<uint32_t *>(base_index);

            switch(bpp) {
                case 1:
                    *base_index = (value & std::numeric_limits<uint8_t>::max());
                    break;
                case 2:
                    *buffer2 = (value & std::numeric_limits<uint16_t>::max());
                    break;
                case 3:
                    base_index[0] =
                        (value & static_cast<uint32_t>(
                                     std::numeric_limits<uint8_t>::max()));
                    base_index[1] =
                        (value &
                         static_cast<uint32_t>(
                             std::numeric_limits<uint8_t>::max() << 8)) >>
                        8;
                    base_index[2] =
                        (value &
                         static_cast<uint32_t>(
                             std::numeric_limits<uint8_t>::max() << 16)) >>
                        16;
                    break;
                case 4:
                    *buffer4 = value;
                default:
                    break;
            }
        }
    }
}
