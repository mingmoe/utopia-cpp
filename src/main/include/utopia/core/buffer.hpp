//===--------------- buffer.hpp - 缓冲区实现 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020-2022 moe-org All rights reserved.
//
//===-----------------------------------------------------===//
/// \file
/// 这个文件定义了utopia::core::Buffer类。
/// 这个类代表一个二进制数据缓冲区。但是并不持有这个缓冲区的所有权。
/// 可以简单理解为返回一个缓冲区信息。
//===-----------------------------------------------------===//

#ifndef UTOPIA_CORE_BUFFER_HPP
#define UTOPIA_CORE_BUFFER_HPP

#include <cstdint>

#include <utopia/core/exception.hpp>

namespace utopia::core {

    /// @brief 一个封装缓冲区的类
    struct Buffer {
        std::uint8_t *buffer{ nullptr };
        std::uint64_t size{ 0 };
    };
}   // namespace utopia::core

#endif   // _UTOPIA_CORE_BUFFER_HPP_
