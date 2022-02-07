//===--------------- source.hpp - 字体源 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020-2022 moe-org All rights reserved.
//
//===--------------------------------------------------===//
/// \file
/// 这个文件声明了utopia::client::text::FontSource和一系列子类。
/// 这个类负责提供字体来源，如FontFileSource等。
//===--------------------------------------------------===//

#ifndef UTOPIA_TEXT_SOURCE_HPP
#define UTOPIA_TEXT_SOURCE_HPP

#include <cerrno>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <span>
#include <string>
#include <utopia/core/exception.hpp>

namespace utopia::client::text {

    /// @brief 字体源的抽象类
    /// @note 禁用复制构造(赋值)函数，只使用移动构造(赋值)函数
    class FontSource {
      public:

        FontSource()                       = default;
        virtual ~FontSource()              = default;
        FontSource(FontSource &&) noexcept = default;
        FontSource &operator=(FontSource &&) noexcept = default;

        FontSource(const FontSource &)                = delete;
        FontSource &operator=(const FontSource &) = delete;

        /// @brief  获取字体标识符。供人类阅读。
        /// @return 字体的标识符，如文件路径，URL等。
        [[nodiscard]] virtual inline std::string
            get_source_name() const noexcept {
            return std::string{ "unknown unnamed font" };
        }

        /// @brief  获取字体
        /// @return 字体源文件的缓冲区
        [[nodiscard]] virtual std::span<const char>
            get_font_source() const noexcept = 0;
    };

    /// @brief 来自文件的字体
    class FileFontSource : public FontSource {
      private:

        std::string          full_path_{};
        std::span<const char> buffer_{};

      public:

        /// @brief 从文件构造一个字体。
        /// 有点重量级：将会把文件读取到内存，直到析构。
        /// @param fontFile 字体文件。如果无法打开则抛出IOException
        explicit FileFontSource(const std::string &fontFile) {
            // 获取绝对路径&&文件大小
            std::uintmax_t        file_size{ 0 };
            std::filesystem::path abs_path;

            try {
                std::filesystem::path path{ fontFile };

                abs_path         = std::filesystem::absolute(path);

                this->full_path_ = abs_path.generic_string();

                file_size        = std::filesystem::file_size(path);
            }
            catch(std::filesystem::filesystem_error &err) {
                THROW_UTOPIA_EXCEPTION(err.what(), IOException);
            }

            // 读取文件
            std::ifstream ifs{ this->full_path_, std::ios::binary };

            if((!ifs.is_open()) || (!ifs.good())) {
                THROW_UTOPIA_EXCEPTION_FROM_ERRNO(IOException);
            }

            auto *buffer = new char[file_size];   // NOLINT

            ifs.read(buffer, file_size);

            if(!ifs.eof()) {
                THROW_UTOPIA_EXCEPTION(
                    "read std::filesystem::file_size() bytes but not reach EOF",
                    IOException);
            }

            ifs.close();

            this->buffer_ = std::span<const char>{ buffer, file_size };
        }

        /// 析构，同时释放缓冲区内存
        ~FileFontSource() override {
            if(buffer_.data() != nullptr) {
                delete[] buffer_.data();
                buffer_ = std::span<const char>{};
            }
        }

        /// @brief 移动构造函数
        FileFontSource(FileFontSource &&origin) noexcept {
            *this = std::move(origin);
        }

        /// @brief 移动赋值函数
        FileFontSource &operator=(FileFontSource &&origin) noexcept {
            this->full_path_  = std::move(origin.full_path_);
            this->buffer_     = std::move(origin.buffer_);

            origin.full_path_ = std::string{};
            origin.buffer_    = std::span<const char>{};

            return *this;
        }

        // 复制函数都被删除
        FileFontSource(const FileFontSource &) = delete;
        FileFontSource &operator=(const FileFontSource &) = delete;

        /// @brief    获取文件路径
        /// @return   文件路径。不一定等于构造函数传入的路径
        std::string get_file_path() {
            return full_path_;
        }

        /// @brief 直接返回文件的绝对路径
        [[nodiscard]] inline std::string
            get_source_name() const noexcept override {
            return this->full_path_;
        }

        /// @brief 返回文件内容
        [[nodiscard]] inline std::span<const char>
            get_font_source() const noexcept override {
            return this->buffer_;
        }
    };

}   // namespace utopia::client::text

#endif   // _UTOPIA_TEXT_SOURCE_HPP_
