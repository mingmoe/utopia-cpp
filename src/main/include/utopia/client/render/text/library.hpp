//===--------------- library.hpp - Library声明和实现 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020-2022 moe-org All rights reserved.
//
//===-------------------------------------------------------------===//
/// \file
/// 负责声明utopia::client::render::text::Library和实现此类
//===-------------------------------------------------------------===//

#ifndef UTOPIA_CLIENT_RENDER_TEXT_LIBRARY_HPP
#define UTOPIA_CLIENT_RENDER_TEXT_LIBRARY_HPP

#ifndef UTOPIA_PLATFORM_CLIENT
    #error this file is only compiled in client of utopia
#endif

#include <ft2build.h>
#include FT_FREETYPE_H
#include <fmt/core.h>
#include <memory>

#include <utopia/client/render/text/error.hpp>
#include <utopia/core/assert.hpp>

namespace utopia::client::render::text {

    namespace {
        void deleteFreeTypeLibrary(FT_Library *ptr) {
            auto ft_error = FT_Done_FreeType(*ptr);

            if(ft_error != 0) {
                auto s = fmt::format("delete free type error with code:{}",
                                     ft_error);
                utopia::core::failed(std::string_view{ s });
            }
        }
    }   // namespace

    using FTLibrarySharedPtr = std::shared_ptr<FT_Library>;

    /// @brief 文本渲染的基库
    class Library {
      private:

        FTLibrarySharedPtr freetype_{ nullptr };

        Library() : freetype_(new FT_Library{}, &deleteFreeTypeLibrary) {
            auto error = FT_Init_FreeType(freetype_.get());
            assert_freetype_error(error);
        }

      public:

        ~Library()                   = default;

        Library(const Library &)     = default;
        Library(Library &&) noexcept = default;
        Library &operator=(const Library &) = default;
        Library &operator=(Library &&) noexcept = default;

        /// @brief 获取Freetype库
        [[nodiscard]] inline FTLibrarySharedPtr get_freetype() const noexcept {
            return this->freetype_;
        }

        /// @brief     创建一个库，可能会抛出异常
        /// @exception FreetypeException 创建失败则抛出此异常
        [[nodiscard]] static inline std::shared_ptr<Library> create() {
            return // NOLINTNEXTLINE
                std::shared_ptr<Library>(new Library{});
        }
    };
}   // namespace utopia::client::text

#endif
