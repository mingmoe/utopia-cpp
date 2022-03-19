#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory("${U_UTOPIA_DEPENDENCE_DIR}/googletest" EXCLUDE_FROM_ALL)

include(GoogleTest)

function(u_add_google_test)
    # GTest::gmock GTest::gmock_main
    target_link_libraries(${ARGV} PRIVATE GTest::gtest GTest::gtest_main)
    gtest_discover_tests(${ARGV})
endfunction(u_add_google_test)
