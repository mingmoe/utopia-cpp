#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

add_executable(
    ${U_PROJECT_SERVER}
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
    ${U_MAIN_SOURCE_FILE_WITHOUT_MAIN}
    ${U_MAIN_SOURCE_HEADER_FILE}
)

u_add_standard_options(${U_PROJECT_SERVER})
