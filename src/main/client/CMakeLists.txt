#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

set(U_CLIENT_TEST_FILE
    PARENT_SCOPE
)

set(U_CLIENT_SOURCE_FILE 
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/render/text/face.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/render/text/renderer.cpp"
    
    "${CMAKE_CURRENT_SOURCE_DIR}/render/sdl/surface.cpp"
)
set(U_CLIENT_HEADER_FILE
    "${U_MAIN_INCLUDE_DIR}/utopia/client/render/bitmap.hpp"

    "${U_MAIN_INCLUDE_DIR}/utopia/client/render/text/source.hpp"
    "${U_MAIN_INCLUDE_DIR}/utopia/client/render/text/font.hpp"
    "${U_MAIN_INCLUDE_DIR}/utopia/client/render/text/face.hpp"
    "${U_MAIN_INCLUDE_DIR}/utopia/client/render/text/library.hpp"
    "${U_MAIN_INCLUDE_DIR}/utopia/client/render/text/error.hpp"
    "${U_MAIN_INCLUDE_DIR}/utopia/client/render/text/renderer.hpp"
    "${U_MAIN_INCLUDE_DIR}/utopia/client/render/text/text.hpp"

    "${U_MAIN_INCLUDE_DIR}/utopia/client/render/sdl/error.hpp"
    "${U_MAIN_INCLUDE_DIR}/utopia/client/render/sdl/window.hpp"
    "${U_MAIN_INCLUDE_DIR}/utopia/client/render/sdl/renderer.hpp"
    "${U_MAIN_INCLUDE_DIR}/utopia/client/render/sdl/surface.hpp"
    "${U_MAIN_INCLUDE_DIR}/utopia/client/render/sdl/texture.hpp"
    "${U_MAIN_INCLUDE_DIR}/utopia/client/render/sdl/sdl.hpp"
)
set(U_CLIENT_TOTAL_FILE ${U_CLIENT_SOURCE_FILE} ${U_CLIENT_HEADER_FILE})

u_set_core_source_group()

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX client FILES ${U_CLIENT_SOURCE_FILE})
source_group(TREE ${U_MAIN_SOURCE_DIR} FILES ${U_CLIENT_HEADER_FILE})


add_executable(
    ${U_PROJECT}
    ${U_CORE_TOTAL_FILE}
    ${U_CLIENT_TOTAL_FILE}
)

# 为特定的编译目标添加宏
target_compile_definitions(${U_PROJECT} PUBLIC UTOPIA_PLATFORM_CLIENT)

u_add_standard_options(${U_PROJECT})
u_add_sdl2_library(${U_PROJECT})
u_add_harfbuzz_library(${U_PROJECT})
u_add_freetype_library(${U_PROJECT})
