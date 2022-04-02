//===--------------- debug.hpp - debug辅助工具 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020-2022 moe-org All rights reserved.
//
//===-------------------------------------------------------===//
/// \file
/// 处理一些debug相关的内容
//===-------------------------------------------------------===//

#ifndef UTOPIA_CORE_DEBUG_HPP
#define UTOPIA_CORE_DEBUG_HPP

namespace utopia::core {

    /// @brief 触发debug中断
    /// @note 在非debug模式下无操作
    void debug_break([[maybe_unused]] const char *reason = nullptr);

}   // namespace utopia::core

#endif
