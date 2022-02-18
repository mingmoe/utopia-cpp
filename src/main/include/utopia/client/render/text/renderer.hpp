//===--------------- renderer.hpp - Renderer声明 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020-2022 moe-org All rights reserved.
//
//===----------------------------------------------------------===//
/// \file
/// 负责声明utopia::client::render::text::Renderer.此类用于使用FreeType渲染字体。
/// 此类的抽象级别较低，仅仅输出位图。
//===----------------------------------------------------------===//

#ifndef UTOPIA_CLIENT_RENDER_TEXT_RENDERER_HPP
#define UTOPIA_CLIENT_RENDER_TEXT_RENDERER_HPP

#ifndef UTOPIA_PLATFORM_CLIENT
    #error this file is only compiled in client of utopia
#endif

#include <ft2build.h>
#include FT_FREETYPE_H
#include <fmt/core.h>
#include <memory>
#include <optional>

#include <utopia/client/render/text/error.hpp>
#include <utopia/client/render/text/face.hpp>
#include <utopia/client/render/bitmap.hpp>

namespace utopia::client::render::text {

    /// @brief 字体渲染器。此类的抽象级别较低，仅仅输出位图。
    /// 得为每一个Face构造一个渲染器。
    class Renderer {
      private:

        /// @brief 字体面
        std::shared_ptr<Face> face_;

        Renderer(std::shared_ptr<Face> face) : face_(face){};

      public:

        ~Renderer()                     = default;

        Renderer(const Renderer &)      = delete;
        Renderer(Renderer &&)           = delete;
        Renderer &operator=(const Renderer &) = delete;
        Renderer &operator=(Renderer &&) = delete;

        /// @brief 根据字符编码获取字体id
        /// @param unicode_code unicode字符编码
        /// @return 字符id，如果为0则说明未找到字符。
        uint32_t get_glyph_id(char32_t unicode_code);

        /// @brief 渲染位图
        /// @param id 字符id
        /// @note 字符id不是unicode编码
        /// @exception FreetypeException 渲染错误
        /// @return 渲染后的位图
        utopia::client::render::Bitmap render(uint32_t id);

        /// @brief 构造一个Renderer
        /// @param face 要使用的字体
        [[nodiscard]] static inline std::shared_ptr<Renderer>
            create(std::shared_ptr<Face> face) {
            return std::shared_ptr<Renderer>(new Renderer{ face });   // NOLINT
        }
    };

}   // namespace utopia::client::text

#endif
