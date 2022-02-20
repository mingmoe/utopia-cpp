#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

find_package(GTest CONFIG REQUIRED)

include(GoogleTest)

function(u_add_google_test)
    # GTest::gmock GTest::gmock_main
    target_link_libraries(${ARGV} PRIVATE GTest::gtest GTest::gtest_main)
    gtest_discover_tests(${ARGV})
endfunction(u_add_google_test)

