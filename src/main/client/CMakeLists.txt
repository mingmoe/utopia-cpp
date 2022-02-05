#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

set(U_CLIENT_MAIN_SOURCE_FILE 
)
set(U_CLIENT_HEADER_FILE
    "${U_MAIN_INCLUDE_DIR}/utopia/client/text/source.hpp"
)

add_executable(
    ${U_PROJECT}
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
    ${U_MAIN_SOURCE_FILE_WITHOUT_MAIN}
    ${U_MAIN_SOURCE_HEADER_FILE}
    ${U_CLIENT_MAIN_SOURCE_FILE}
    ${U_CLIENT_HEADER_FILE}
)

u_add_standard_options(${U_PROJECT})
u_add_sdl2_library(${U_PROJECT})
u_add_harfbuzz_library(${U_PROJECT})
u_add_freetype_library(${U_PROJECT})
