#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

find_package(GTest CONFIG REQUIRED)

include(GoogleTest)

function(u_add_google_test)
    target_link_libraries(${ARGV} PRIVATE GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)
    gtest_discover_tests(${ARGV})
endfunction(u_add_google_test)

list(APPEND U_3RD_LIBRARY_FUNCTION_LIST "u_add_google_test | ${CMAKE_CURRENT_LIST_FILE}")
