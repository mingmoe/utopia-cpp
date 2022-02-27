//===--------------- icu.hpp - 一些国际化工具定义 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020-2022 moe-org All rights reserved.
//
//===--------------------------------------------------------===//
/// \file
/// 定义了一些国际化的工具
//===--------------------------------------------------------===//

#ifndef UTOPIA_CORE_I18N_ICU_HPP
#define UTOPIA_CORE_I18N_ICU_HPP

#include <fmt/core.h>
#include <unicode/errorcode.h>

#include <utopia/core/assert.hpp>
#include <utopia/core/exception.hpp>

namespace utopia::core::i18n {

    using IcuExcpetion = utopia::core::UniversalException<"IcuExcpetion">;

    /// @brief 检查ICU错误代码。如果代码不为success，则抛出IcuExcpetion
    /// @param code 错误代码
    inline void check_icu_error_code(UErrorCode code) {
        icu::ErrorCode err{};
        err.set(code);

        if(err.isFailure()) {
            auto msg = fmt::format("icu error({}):{}", code, err.errorName());

            throw IcuExcpetion{ msg };
        }
    }

}   // namespace utopia::core::i18n

#endif
