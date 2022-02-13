//===--------------- face.hpp - 字面类型声明 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020-2022 moe-org All rights reserved.
//
//===----------------------------------------------------===//
/// \file
/// 这个文件定义了字体字面类型(utopia::client::render::text::Face)的声明。
/// 根据FreeType的说法：一个字体(文件)(utopia::client::render::text::Font)可能被打包了多个`字体`。
/// 便用Face代表其中一个`字体`。
//===----------------------------------------------------===//

#ifndef UTOPIA_CLIENT_RENDER_TEXT_FACE_HPP
#define UTOPIA_CLIENT_RENDER_TEXT_FACE_HPP

#ifndef UTOPIA_PLATFORM_CLIENT
    #error this file is only compiled in client of utopia
#endif

#include <ft2build.h>
#include <memory>

#include <utopia/client/render/text/error.hpp>
#include <utopia/client/render/text/font.hpp>
#include <utopia/client/render/text/library.hpp>
#include <utopia/core/convert.hpp>

#include FT_FREETYPE_H
#include <harfbuzz/hb.h>

namespace utopia::client::render::text {

    namespace {
        inline void deleteFreetypeFace(FT_Face *ptr) {
            auto err = FT_Done_Face(*ptr);
            throwFreetypeError(err);
        }
        inline void deleteHarfbuzzFace(hb_face_t *ptr) {
            hb_face_destroy(ptr);
        }
        inline void deleteHarfbuzzFont(hb_font_t *ptr) {
            hb_font_destroy(ptr);
        }
    }   // namespace

    /// @brief 字面类
    class Face {
      private:

        const uint16_t             face_index_;
        std::shared_ptr<Font>      source_;
        std::shared_ptr<FT_Face>   ft_face_;
        std::shared_ptr<hb_face_t> hb_face_;
        std::shared_ptr<hb_font_t> hb_font_;

        Face(std::shared_ptr<Font> source, uint16_t face_index) :
            face_index_(face_index), source_(source) {
            // init harfbuzz
            auto hb_face =
                hb_face_create(source->get_harfbuzz_blob().get(), face_index);
            hb_face_.reset(hb_face, &deleteHarfbuzzFace);

            auto hb_font = hb_font_create(hb_face);
            hb_font_.reset(hb_font, &deleteHarfbuzzFont);

            // init freetype
            auto faced = new FT_Face{};

            auto err   = FT_New_Memory_Face(
                *source->get_freetype_lib()->get_freetype().get(),
                // NOLINTNEXTLINE
                reinterpret_cast<const FT_Byte *>(
                    source->get_source()->get_font_source().data()),
                utopia::core::safe_convert<FT_Long>(
                    source->get_source()->get_font_source().size_bytes()),
                face_index,
                faced);

            throwFreetypeError(err);

            ft_face_.reset(faced, &deleteFreetypeFace);

            // init size
            this->set_size(14, 14, 14);
        }

      public:

        /// @brief     创建一个字面，可能会抛出异常
        /// @param source 字体源
        /// @param face_index 字体索引
        /// @exception FreetypeException 创建失败则抛出此异常
        [[nodiscard]] static inline std::shared_ptr<Face>
            create(std::shared_ptr<Font> source, uint16_t face_index) {
            return   // NOLINTNEXTLINE
                std::shared_ptr<Face>(new Face{ source, face_index });
        }


        /// @brief 设置字体的大小
        ///
        /// @param x 水平方向像素
        /// @param y 垂直方向像素
        /// @param point 字体磅值
        void                         set_size(int x, int y, double point);

        inline std::shared_ptr<Font> get_parent() {
            return this->source_;
        }
        inline std::shared_ptr<FT_Face> get_ft_face() {
            return this->ft_face_;
        }
        inline std::shared_ptr<hb_font_t> get_hb_font() {
            return this->hb_font_;
        };
    };


}   // namespace utopia::client::render::text

#endif
