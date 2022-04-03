//===--------------- shaper.hpp - Shaper声明 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020-2022 moe-org All rights reserved.
//
//===------------------------------------------------------===//
/// \file
/// 声明了Shaper类。此类是对harfbuzz的封装，用于文本排版。
//===------------------------------------------------------===//

#ifndef UTOPIA_CLIENT_RENDER_TEXT_SHAPER_HPP
#define UTOPIA_CLIENT_RENDER_TEXT_SHAPER_HPP

#ifndef UTOPIA_PLATFORM_CLIENT
    #error this file is only compiled in client of utopia
#endif

#include <harfbuzz/hb.h>
#include <memory>
#include <string>
#include <unicode/unistr.h>
#include <vector>

#include <utopia/client/render/text/error.hpp>
#include <utopia/client/render/text/face.hpp>
#include <utopia/client/render/text/font.hpp>
#include <utopia/core/convert.hpp>

namespace utopia::client::render::text {

    namespace {
        inline void delete_harfbuzz_buffer(hb_buffer_t *ptr) {
            hb_buffer_destroy(ptr);
        }
        inline void check_harfbuzz_buffer_allocation(hb_buffer_t *ptr) {
            if(!hb_buffer_allocation_successful(ptr)) {
                throw HarfbuzzException{
                    "from utopia:harfbuzz allocation failed down"
                };
            }
        }
        inline void
            check_harfbuzz_buffer_allocation(std::shared_ptr<hb_buffer_t> ptr) {
            check_harfbuzz_buffer_allocation(ptr.get());
        }
    }   // namespace

    /// @brief 文本方向
    enum class TextDirection
    {
        LeftToRight,
        RightToLeft
    };

    /// @brief 排版结果
    struct Glyph {
        int32_t x_advance{ 0 };
        int32_t y_advance{ 0 };
        int32_t x_offset{ 0 };
        int32_t y_offset{ 0 };
        /// @brief 字符id
        uint32_t glyph_index{ 0 };
        /// @brief harfbuzz集群
        uint32_t cluster{ 0 };
    };

    /// @brief 文本塑形器
    class Shaper {
      private:

        std::shared_ptr<hb_buffer_t> buffer_;

        Shaper() {
            auto buf = hb_buffer_create();

            check_harfbuzz_buffer_allocation(buf);

            buffer_.reset(buf, &delete_harfbuzz_buffer);
        }

      public:

        ~Shaper()              = default;

        Shaper(const Shaper &) = delete;
        Shaper(Shaper &&)      = delete;
        Shaper &operator=(const Shaper &) = delete;
        Shaper &operator=(Shaper &&) = delete;

        /// @brief 构造一个Shaper
        /// @param face 要使用的字体
        [[nodiscard]] static inline std::shared_ptr<Shaper> create() {
            return std::shared_ptr<Shaper>(new Shaper{});   // NOLINT
        }

        /// @brief 添加一段文本到缓冲区
        /// @param strs 文本
        /// @param begin 要添加的文本的字符偏移量
        /// @param len 要添加的文本字符长度
        inline void
            add_text(icu::UnicodeString strs, uint32_t begin, uint32_t len) {
            auto strs_buf = strs.getBuffer();
            auto strs_len = strs.getCapacity();

            hb_buffer_add_utf16(buffer_.get(),
                                reinterpret_cast<const uint16_t *>(strs_buf),
                                strs_len,
                                begin,
                                len);

            check_harfbuzz_buffer_allocation(buffer_);
        }

        /// @brief 设置脚本
        /// @param script_name 脚本的ISO 15924名称
        inline void set_script(std::string script_name) {
            auto script = hb_script_from_string(
                script_name.c_str(),
                utopia::core::safe_convert<int>(script_name.size()));

            hb_buffer_set_script(buffer_.get(), script);
        }

        /// @brief 设置语言
        /// @param language_name  BCP47语言标签
        inline void set_language(std::string language_name) {
            auto language = hb_language_from_string(
                language_name.c_str(),
                utopia::core::safe_convert<int>(language_name.size()));

            hb_buffer_set_language(buffer_.get(), language);
        }

        /// @brief 设置语言方向
        /// @param left_to_right 如果为true则从左到右。如果设置为false则从右到左。
        inline void set_direction(TextDirection direction) {
            if(direction == TextDirection::LeftToRight) {
                hb_buffer_set_direction(buffer_.get(), HB_DIRECTION_LTR);
            }
            else {
                hb_buffer_set_direction(buffer_.get(), HB_DIRECTION_RTL);
            }
        }

        /// @brief 为文本排版
        inline std::vector<Glyph> shape(std::shared_ptr<Face> face) {

            hb_shape(face->get_hb_font().get(), buffer_.get(), nullptr, 0);

            unsigned int     glyph_count{ 0 };
            hb_glyph_info_t *glyph_info =
                hb_buffer_get_glyph_infos(buffer_.get(), &glyph_count);
            hb_glyph_position_t *glyph_pos =
                hb_buffer_get_glyph_positions(buffer_.get(), &glyph_count);

            std::vector<Glyph> glyphs{};
            glyphs.reserve(glyph_count);

            for(decltype(glyph_count) index = 0; index != glyph_count;
                index++) {
                auto pos  = glyph_pos[index];
                auto info = glyph_info[index];
                glyphs.push_back(Glyph{ .x_advance   = pos.x_advance,
                                        .y_advance   = pos.y_advance,
                                        .x_offset    = pos.x_offset,
                                        .y_offset    = pos.y_offset,
                                        .glyph_index = info.codepoint,
                                        .cluster     = info.cluster });
            }

            return glyphs;
        }

        /// @brief 清空塑形引擎状态
        inline void reset() {
            hb_buffer_reset(this->buffer_.get());
        }
    };
}   // namespace utopia::inline client::inline render::inline text


#endif
