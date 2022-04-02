//===--------------- icu.cpp - icu的测试 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020 - 2022 moe - org All rights reserved.
//
//===--------------------------------------------------===//
/// \file
/// 这个文件对utopia/core/i18n/icu.hpp进行了测试
//===--------------------------------------------------===//

#include <gtest/gtest.h>

#include <utopia/core/i18n/icu.hpp>

TEST(CoreI18nIcu, SpiltLine) {
    auto str = UNICODE_STRING_SIMPLE("Hello\nWorld\n");

    auto vector = utopia::core::i18n::split_line(str);

    EXPECT_EQ(vector.size(), 3);
    EXPECT_EQ(vector[0].compare(UNICODE_STRING_SIMPLE("Hello")), 0);
    EXPECT_EQ(vector[1].compare(UNICODE_STRING_SIMPLE("World")), 0);
    EXPECT_EQ(vector[2].compare(UNICODE_STRING_SIMPLE("")), 0);
}
