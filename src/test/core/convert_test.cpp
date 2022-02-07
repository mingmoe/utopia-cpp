//===--------------- convert_test.cpp - convert.hpp的测试 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020 - 2022 moe - org All rights reserved.
//
//===-------------------------------------------------------------------===//
/// \file
/// 这个文件对utopia/core/convert.hpp进行了测试
//===-------------------------------------------------------------------===//

#include <limits>

#include <utopia/core/convert.hpp>

#include <gtest/gtest.h>

TEST(Core, NumberConvert) {

    signed output = 0;

    auto   inOfRange =
        utopia::core::safe_number_cast<signed, long long>(1L, output);

    auto outOfRange = utopia::core::safe_number_cast<signed, long long>(
        static_cast<long long>(std::numeric_limits<signed>::max()) + 1,
        output);

    EXPECT_TRUE(inOfRange);
    EXPECT_FALSE(outOfRange);

    EXPECT_EQ(output, 1);
}


TEST(Core, FromUnsignedToSignedCast) {
    signed long output = 0;

    auto inOfRange     = utopia::core::safe_sign_cast<signed long>(1ULL, output);

    auto outOfRange    = utopia::core::safe_sign_cast<signed long>(
        std::numeric_limits<unsigned long>::max(),
        output);

    EXPECT_TRUE(inOfRange);
    EXPECT_FALSE(outOfRange);

    EXPECT_EQ(output, 1L);
}


TEST(Core, FromSignedToUnsignedCast) {

    unsigned output = 0;

    auto inOfRange  = utopia::core::safe_sign_cast<unsigned>(1LL, output);

    auto outOfRange = utopia::core::safe_sign_cast<unsigned>(-1LL, output);

    
    auto     outOfRange2 =
        utopia::core::safe_sign_cast<unsigned>(static_cast<signed long long>
            (std::numeric_limits<unsigned>::max()) + 1,
                                             output);

    EXPECT_TRUE(inOfRange);
    EXPECT_FALSE(outOfRange);
    EXPECT_FALSE(outOfRange2);

    EXPECT_EQ(output, 1UL);
}
