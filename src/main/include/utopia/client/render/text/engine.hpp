//===--------------- engine.hpp - Engine头文件 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020-2022 moe-org All rights reserved.
//
//===----------------------------------------------------------===//
/// \file
/// 声明Engine类。此类负责对文本渲染进行系统性的管理。
//===----------------------------------------------------------===//

#ifndef UTOPIA_CLIENT_RENDER_TEXT_ENGINE_HPP
#define UTOPIA_CLIENT_RENDER_TEXT_ENGINE_HPP

#include <algorithm>
#include <map>
#include <memory>
#include <unicode/unistr.h>
#include <utility>
#include <vector>

#include <utopia/client/render/text/text.hpp>

namespace utopia::client::render::text {

    /// @brief 一个附带本地化信息的文本段
    struct TextParagraph {
        std::string        language;
        std::string        script;
        TextDirection      direction;
        icu::UnicodeString text;
        uint32_t           max_width_one_line{
            std::numeric_limits<decltype(max_width_one_line)>::max()
        };
    };

    /// @brief 字体渲染所需要的信息
    struct TextRenderSetting {
        float    point;
        uint32_t x_pixel;
        uint32_t y_pixel;
    };

    /// @brief 用于渲染一段文本所需要的信息。
    struct TextRenderInfo {
        TextParagraph     para;
        TextRenderSetting setting;
    };

    struct CompareFontPriority {
        bool operator()(const uint64_t &a, const uint64_t &b) const {
            return a < b;
        }
    };

    /// @brief 文本渲染引擎。
    /// 会处理更多细节，例如字体优先级，字体渲染效果，双向unicode字符等。
    class Engine {
      private:

        /// @biref pair.1 代表字体优先级
        /// pair.2 代表字体
        std::map<uint64_t,
                 std::vector<std::pair<std::shared_ptr<Face>,
                                       std::shared_ptr<Renderer>>>,
                 CompareFontPriority>
                                       font_list_{};

        std::shared_ptr<text::Library> library_{};

        std::shared_ptr<text::Shaper>  text_sharper_;

        Engine() {
            library_     = Library::create();
            text_sharper_ = Shaper::create();
        }

      public:

        /// @brief     创建一个字体渲染引擎
        /// @exception FreetypeException 创建失败则抛出此异常
        [[nodiscard]] static inline std::shared_ptr<Engine> create() {
            return std::shared_ptr<Engine>{ new Engine() };
        }

        /// @brief 添加字体
        /// @param font 要添加的字体
        /// @param priority 字体优先级
        void add_font(uint64_t priority, std::shared_ptr<Face> font);

        /// @brief 获取字体列表
        /// @return 字体列表。pair.first代表字体的优先级。
        [[nodiscard]] std::map<
            uint64_t,
            std::vector<
                std::pair<std::shared_ptr<Face>, std::shared_ptr<Renderer>>>,
            CompareFontPriority>
            get_font_list();

        /**
         * @brief 对于一个unicode代码点，获取第一个拥有该代码点对应字形的字体。
         * @param unicode_code unicode代码点
         * @param output_id 输出的id，如果没有找到任何一个字符有对应字形，返回0
         * @return 如果找到，则返回找到的字体。
        */
        [[nodiscard]] std::pair<std::shared_ptr<Face>,
                                std::shared_ptr<Renderer>>
            get_first_exist_glyph(uint32_t unicode_code, uint32_t &output_id);

        /// @brief 渲染单个字符（注意:这不会使用排版引擎）
        /// @param unicode_code unicode代码点
        /// @param settings 字体效果
        /// @note 如果碰到没有找到的字符，使用U+FFFD代码点继续查找。
        /// 还是找不到则返回空位图，大小同settings参数的pixel大小。
        [[nodiscard]] Bitmap render(uint32_t          unicode_code,
                                    TextRenderSetting settings);

        /// @brief 渲染一段字符串
        /// @param para 段落信息
        [[nodiscard]] Bitmap render_paragraph(TextRenderInfo &para);
    };


}   // namespace utopia::client::render::text


#endif
