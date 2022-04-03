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
#include <unicode/schriter.h>
#include <unicode/unistr.h>
#include <vector>

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

    /**
     * @brief 将字符串根据换行符分割成行
     * @param text 字符串
     * @return 每一行字符串
     * @note 返回的vector持有的是来自参数的临时字符串。即参数的tempSubString()调用。
    */
    inline std::vector<icu::UnicodeString>
        split_line(icu::UnicodeString &text) {
        // 分行
        std::vector<icu::UnicodeString> lines;

        icu::StringCharacterIterator    it{ text };

        decltype(text.countChar32())    last_index = 0;

        while(it.hasNext()) {
            auto c = it.next32();
            if(c == '\n') {
                lines.push_back(
                    text.tempSubStringBetween(last_index, it.getIndex()));
                last_index = it.getIndex() + 1;
            }
        }
        // add last line
        lines.push_back(text.tempSubStringBetween(last_index));

        return lines;
    }

}   // namespace utopia::core::i18n

#endif
