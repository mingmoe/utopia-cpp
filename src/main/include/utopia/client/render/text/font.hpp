//===--------------- font.hpp - 字体类型声明 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020-2022 moe-org All rights reserved.
//
//===----------------------------------------------------===//
/// \file
/// 这个文件定义了字体类型(utopia::client::render::text::Font)的声明。
//===----------------------------------------------------===//
#ifndef UTOPIA_CLIENT_RENDER_TEXT_FONT_HPP
#define UTOPIA_CLIENT_RENDER_TEXT_FONT_HPP

#ifndef UTOPIA_PLATFORM_CLIENT
    #error this file is only compiled in client of utopia
#endif

#include <ft2build.h>

#include <utopia/client/render/text/source.hpp>
#include FT_FREETYPE_H
#include <harfbuzz/hb.h>
#include <memory>

#include <utopia/client/render/text/library.hpp>
#include <utopia/core/convert.hpp>

namespace utopia::client::render::text {

    namespace {
        inline void delete_harfbuzz_blob(hb_blob_t *ptr) {
            hb_blob_destroy(ptr);
        }
        inline void delete_harfbuzz_face(hb_face_t *ptr) {
            hb_face_destroy(ptr);
        }
    }   // namespace

    /// @brief 字体类。只持有字体资源，不持有字体属性（比如字体大小）。
    /// 有点重量级。省着点用。
    class Font {
      private:

        std::shared_ptr<FontSource> source_{ nullptr };
        std::shared_ptr<hb_blob_t>  hb_blob_{ nullptr };
        std::shared_ptr<hb_face_t>  hb_face_{ nullptr };
        std::shared_ptr<Library>    library_{ nullptr };
        const uint16_t              face_index_;

        Font(std::shared_ptr<FontSource> source,
             std::shared_ptr<Library>    library,
             uint16_t                    face_index) :
            source_(source),
            library_(library), face_index_(face_index) {

            // harfbuzz blob
            auto hb = hb_blob_create_or_fail(
                source->get_font_source().data(),
                utopia::core::safe_convert<unsigned int>(
                    source->get_font_source().size_bytes()),
                HB_MEMORY_MODE_READONLY,
                nullptr,
                nullptr);

            if(hb == nullptr) {
                throw HarfbuzzException{
                    "hb_blob_create_or_fail() failed down"
                };
            }

            hb_blob_.reset(hb, &delete_harfbuzz_blob);

            // harfbuzz face
            auto hb_face = hb_face_create(hb, face_index);
            hb_face_.reset(hb_face, &delete_harfbuzz_face);
        }

      public:

        ~Font()            = default;
        Font(Font &&)      = delete;
        Font(const Font &) = delete;
        Font &operator=(const Font &) = delete;
        Font &operator=(Font &&) = delete;

        [[nodiscard]] inline std::shared_ptr<FontSource>
            get_source() const noexcept {
            return this->source_;
        }

        [[nodiscard]] inline std::shared_ptr<Library>
            get_freetype_lib() const noexcept {
            return this->library_;
        }

        [[nodiscard]] inline std::shared_ptr<hb_blob_t>
            get_harfbuzz_blob() const noexcept {
            return this->hb_blob_;
        }

        [[nodiscard]] inline std::shared_ptr<hb_face_t>
            get_harfbuzz_face() const noexcept {
            return this->hb_face_;
        }

        [[nodiscard]] inline uint16_t get_face_index() const noexcept {
            return this->face_index_;
        }

        /// @brief     创建一个字体，可能会抛出异常
        /// @exception HarfbuzzException 创建失败则抛出此异常
        /// @param source 字体源
        /// @param library 文本库
        /// @param face_index 字体在字体集中的索引
        [[nodiscard]] static inline std::shared_ptr<Font>
            create(std::shared_ptr<FontSource> source,
                   std::shared_ptr<Library>    library,
                   uint16_t                    face_index) {
            return   // NOLINTNEXTLINE
                std::shared_ptr<Font>(new Font{ source, library, face_index });
        }
    };

}   // namespace utopia::client::render::text

#endif
