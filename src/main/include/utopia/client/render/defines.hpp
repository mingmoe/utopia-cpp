//===--------------- defines.hpp - 一些类型定义 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020-2022 moe-org All rights reserved.
//
//===-------------------------------------------------------===//
/// \file
/// 这个文件定义了一些简单的类型
//===-------------------------------------------------------===//

#ifndef UTOPIA_CLIENT_RENDER_DEFINES_HPP
#define UTOPIA_CLIENT_RENDER_DEFINES_HPP

#ifndef UTOPIA_PLATFORM_CLIENT
    #error this file is only compiled in client of utopia
#endif

#include <cstdint>

namespace utopia::client::render {

    using pos_t = int;

    /**
     * \brief 长方形
     */
    struct Rectangle {
        pos_t x{0};
        pos_t y{ 0 };
        pos_t x_size{ 0 };
        pos_t y_size{ 0 };
    };






}   // namespace utopia::client::render

#endif
