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
    const constexpr auto max = std::numeric_limits<signed>::max();
    const constexpr auto min = std::numeric_limits<decltype(max)>::min();
    signed               opt{ 0 };

    auto                 result = utopia::core::safe_add(max, 1, opt);

    EXPECT_FALSE(result);

    result = utopia::core::safe_add(max, -1, opt);

    EXPECT_TRUE(result);

    result = utopia::core::safe_add(min, -1, opt);

    EXPECT_FALSE(result);

    result = utopia::core::safe_add(min, max, opt);

    EXPECT_TRUE(result);
}


TEST(Core, SafeSubTest) {
    const constexpr auto max = std::numeric_limits<signed>::max();
    const constexpr auto min = std::numeric_limits<decltype(max)>::min();
    signed               opt{ 0 };

    auto                 result = utopia::core::safe_sub(max, 1, opt);

    EXPECT_TRUE(result);

    result = utopia::core::safe_sub(max, -1, opt);

    EXPECT_FALSE(result);

    result = utopia::core::safe_sub(min, -1, opt);

    EXPECT_TRUE(result);

    result = utopia::core::safe_sub(min, max, opt);

    EXPECT_FALSE(result);
}

TEST(Core, SafeMulTest) {
    const constexpr auto max = std::numeric_limits<signed>::max();
    signed               opt{ 0 };

    auto                 result = utopia::core::safe_mul(max, 2, opt);

    EXPECT_FALSE(result);
}

TEST(Core, SafeDivTest) {
    const constexpr auto max = std::numeric_limits<signed>::max();
    signed               opt{ 0 };

    auto                 result = utopia::core::safe_div(max, 0, opt);

    EXPECT_FALSE(result);
}
