#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

u_open_clang_tidy()

set(
    U_MAIN_SOURCE_FILE_WITHOUT_MAIN
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/core/exception.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/core/assert.cpp"
)

set(
    U_MAIN_SOURCE_HEADER_FILE
    "${CMAKE_CURRENT_SOURCE_DIR}/include/utopia/core/exception.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/utopia/core/convert.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/utopia/core/assert.hpp"
)

set(U_MAIN_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(U_MAIN_INCLUDE_DIR "${U_MAIN_INCLUDE_DIR}" PARENT_SCOPE)

message(STATUS "utopia include directory:${U_MAIN_INCLUDE_DIR}")

# 这些依赖将会给client,server和test一起使用
function(u_add_standard_options)
    u_add_boost_library(${ARGV})
    u_include_configure_header(${ARGV})
    target_include_directories(
        ${ARGV}
        PUBLIC
        "${U_MAIN_INCLUDE_DIR}"
    )
endfunction(u_add_standard_options)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/client")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/server")
