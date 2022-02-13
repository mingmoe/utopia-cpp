//===--------------- check_opts_test.cpp - check_ops.hpp的测试 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020 - 2022 moe - org All rights reserved.
//
//===------------------------------------------------------------------------===//
/// \file
/// 这个文件对utopia/core/check_ops.hpp进行了测试
//===------------------------------------------------------------------------===//

#include <gtest/gtest.h>
#include <limits>

#include <utopia/core/check_ops.hpp>

TEST(Core, SafeSignedAddTest) {
    const auto    max = std::numeric_limits<signed>::max();
    const auto    min = std::numeric_limits<decltype(max)>::min();
    signed result{ 0 };

    auto          result = utopia::core::safe_add(max, 1, result);

    EXPECT_FALSE(result);

    result = utopia::core::safe_add(max, -1, result);

    EXPECT_TRUE(result);

    result = utopia::core::safe_add(min, -1, result);

    EXPECT_FALSE(result);

    result = utopia::core::safe_add(min, max, result);

    EXPECT_TRUE(result);
}


TEST(Core, SafeSubTest) {
    const auto max = std::numeric_limits<signed>::max();
    const auto min = std::numeric_limits<decltype(max)>::min();
    signed     result{ 0 };

    auto       result = utopia::core::safe_sub(max, 1, result);

    EXPECT_TRUE(result);

    result = utopia::core::safe_sub(max, -1, result);

    EXPECT_FALSE(result);

    result = utopia::core::safe_sub(min, -1, result);

    EXPECT_TRUE(result);

    result = utopia::core::safe_sub(min, max, result);

    EXPECT_FALSE(result);
}

TEST(Core, SafeMulTest) {
    const auto max = std::numeric_limits<signed>::max();
    const auto min = std::numeric_limits<decltype(max)>::min();
    signed     result{ 0 };

    auto       result = utopia::core::safe_mul(max, 2, result);

    EXPECT_FALSE(result);
}

TEST(Core, SafeDivTest) {
    const auto max = std::numeric_limits<signed>::max();
    const auto min = std::numeric_limits<decltype(max)>::min();
    signed     result{ 0 };

    auto       result = utopia::core::safe_div(max, 0, result);

    EXPECT_FALSE(result);
}
