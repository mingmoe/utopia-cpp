//===--------------- source_location.hpp - source_location定和实现 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020-2022 moe-org All rights reserved.
//
//===---------------------------------------------------------------------------===//
/// \file
/// 为傻逼clang提供了一个std::source_location
//===---------------------------------------------------------------------------===//

#ifndef UTOPIA_INCLUDE_CORE_SOURCE_LOCATION_HPP
#define UTOPIA_INCLUDE_CORE_SOURCE_LOCATION_HPP

namespace utopia::core {

    /// @brief 来自标准库的实现
    struct SourceLocation {
        [[nodiscard]] static constexpr SourceLocation current(
            const uint_least32_t _Line_     = __builtin_LINE(),
            const uint_least32_t _Column_   = __builtin_COLUMN(),
            const char *const    _File_     = __builtin_FILE(),
            const char *const    _Function_ = __builtin_FUNCTION()) noexcept {
            SourceLocation _Result;
            _Result._line     = _Line_;
            _Result._column   = _Column_;
            _Result._file     = _File_;
            _Result._function = _Function_;
            return _Result;
        }

        [[nodiscard]] constexpr SourceLocation() noexcept = default;

        [[nodiscard]] constexpr uint_least32_t line() const noexcept {
            return _line;
        }
        [[nodiscard]] constexpr uint_least32_t column() const noexcept {
            return _column;
        }
        [[nodiscard]] constexpr const char *file_name() const noexcept {
            return _file;
        }
        [[nodiscard]] constexpr const char *function_name() const noexcept {
            return _function;
        }

      private:

        uint_least32_t _line{ 0 };
        uint_least32_t _column{ 0 };
        const char    *_file     = "";
        const char    *_function = "";
    };


}   // namespace utopia::core

#endif
