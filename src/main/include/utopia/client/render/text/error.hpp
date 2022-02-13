//===--------------- error.hpp - 用于文本渲染的错误处理机制 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020-2022 moe-org All rights reserved.
//
//===-----------------------------------------------------------------===//
/// \file
/// 定义一些文本渲染的错误处理负责函数。
//===-----------------------------------------------------------------===//

#ifndef UTOPIA_CLIENT_TEXT_ERROR_HPP
#define UTOPIA_CLIENT_TEXT_ERROR_HPP

#ifndef UTOPIA_PLATFORM_CLIENT
    #error this file is only compiled in client of utopia
#endif

#include <ft2build.h>
#include FT_FREETYPE_H
#include <fmt/core.h>
#include <string>

#include <utopia/core/exception.hpp>

namespace utopia::client::render::text {

    DEFINED_UTOPIA_SIMPLE_EXCEPTION(Freetype);
    DEFINED_UTOPIA_SIMPLE_EXCEPTION(Harfbuzz);

    /// @brief 如果错误代码不代表`成功`，则抛出freetype异常。
    /// @param error_code 错误代码
    inline void throwFreetypeError(FT_Error error_code) {
        if(error_code != 0) {
            auto        err_info = FT_Error_String(error_code);
            std::string msg =
                fmt::format("freetype error(code={}):{}",
                            error_code,
                            err_info == nullptr ? "NULL" : err_info);
            throw FreetypeException{ msg };
        }
    }

}   // namespace utopia::client::text

#endif
