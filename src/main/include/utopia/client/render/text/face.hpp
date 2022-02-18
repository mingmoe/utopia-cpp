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
        inline void delete_freetype_face(FT_Face *ptr) {
            auto err = FT_Done_Face(*ptr);
            assert_freetype_error(err);
        }
        inline void delete_harfbuzz_font(hb_font_t *ptr) {
            hb_font_destroy(ptr);
        }
    }   // namespace

    /// @brief 字面类
    /// 这个类同时持有字面属性，比如字体大小。一个字体文件可以有多个字面。
    class Face {
      private:

        std::shared_ptr<Library>   library_{ nullptr };
        std::shared_ptr<Font>      source_{ nullptr };
        std::shared_ptr<FT_Face>   ft_face_{ nullptr };
        std::shared_ptr<hb_font_t> hb_font_{ nullptr };

        int                        x_size_{ 0 };
        int                        y_size_{ 0 };
        float                      point_{ 0 };

        Face(std::shared_ptr<Font> source) :
            source_(source), library_(source->get_freetype_lib()) {
            // init harfbuzz
            auto hb_font = hb_font_create(source->get_harfbuzz_face().get());
            hb_font_.reset(hb_font, &delete_harfbuzz_font);

            // init freetype
            auto faced = new FT_Face{};

            auto err   = FT_New_Memory_Face(
                *source->get_freetype_lib()->get_freetype().get(),
                // NOLINTNEXTLINE
                reinterpret_cast<const FT_Byte *>(
                    source->get_source()->get_font_source().data()),
                utopia::core::safe_convert<FT_Long>(
                    source->get_source()->get_font_source().size_bytes()),
                source->get_face_index(),
                faced);

            assert_freetype_error(err);

            ft_face_.reset(faced, &delete_freetype_face);

            // init size
            this->set_size(14, 14, 14);
        }

      public:

        ~Face()            = default;
        Face(const Face &) = delete;
        Face(Face &&)      = delete;
        Face &operator=(const Face &) = delete;
        Face &operator=(Face &&) = delete;

        /// @brief     创建一个字面，可能会抛出异常
        /// @param source 字体源
        /// @param face_index 字体索引
        /// @exception FreetypeException 创建失败则抛出此异常
        [[nodiscard]] static inline std::shared_ptr<Face>
            create(std::shared_ptr<Font> source) {
            return   // NOLINTNEXTLINE
                std::shared_ptr<Face>(new Face{ source });
        }


        /// @brief 设置字体的大小
        ///
        /// @param x 水平方向像素
        /// @param y 垂直方向像素
        /// @param point 字体磅值
        void set_size(int x, int y, float point);

        /// @brief 获取字体x轴像素大小
        [[nodiscard]] inline int get_x_size() {
            return x_size_;
        }

        /// @brief 获取字体y轴像素大小
        [[nodiscard]] inline int get_y_size() {
            return y_size_;
        }

        /// @brief 获取字体磅数
        [[nodiscard]] inline float get_point() {
            return point_;
        }

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
