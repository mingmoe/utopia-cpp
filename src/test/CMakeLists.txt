#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

u_close_clang_tidy()

set(U_TEST_SOURCE_FILE 
    "${CMAKE_CURRENT_SOURCE_DIR}/core/convert_test.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/core/check_ops_test.cpp"
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX test FILES ${U_TEST_SOURCE_FILE})

add_executable(
    ${U_PROJECT_TEST}
    ${U_CORE_TOTAL_FILE}
    ${U_SERVER_TEST_FILE}
    ${U_CLIENT_TEST_FILE}
    ${U_TEST_SOURCE_FILE}
)

# 为特定的编译目标添加宏
target_compile_definitions(${U_PROJECT_TEST} PUBLIC UTOPIA_PLATFORM_SERVER)
target_compile_definitions(${U_PROJECT_TEST} PUBLIC UTOPIA_PLATFORM_CLIENT)
target_compile_definitions(${U_PROJECT_TEST} PUBLIC UTOPIA_PLATFORM_TEST)

u_add_standard_options(${U_PROJECT_TEST})

u_add_google_test(${U_PROJECT_TEST})
