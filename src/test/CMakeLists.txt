#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

u_close_clang_tidy()

set(U_TEST_SOURCE_FILE 
    "${CMAKE_CURRENT_SOURCE_DIR}/core/convert_test.cpp"
)

add_executable(
    ${U_PROJECT_TEST}
    ${U_MAIN_SOURCE_FILE_WITHOUT_MAIN}
    ${U_MAIN_SOURCE_HEADER_FILE}
    ${U_TEST_SOURCE_FILE}
)

u_add_standard_options(${U_PROJECT_TEST})
u_add_google_test(${U_PROJECT_TEST})
