#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

u_open_clang_tidy()

set(U_MAIN_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(U_MAIN_INCLUDE_DIR "${U_MAIN_INCLUDE_DIR}" PARENT_SCOPE)
set(U_MAIN_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(U_MAIN_SOURCE_DIR "${U_MAIN_SOURCE_DIR}" PARENT_SCOPE)

message(STATUS "utopia include directory:${U_MAIN_INCLUDE_DIR}")

# 设置核心源文件。这些源文件同时被server和client使用
set(
    U_CORE_SOURCE_FILE
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/core/exception.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/core/assert.cpp"
)

set(
    U_CORE_HEADER_FILE
    "${U_MAIN_INCLUDE_DIR}/utopia/core/exception.hpp"
    "${U_MAIN_INCLUDE_DIR}/utopia/core/convert.hpp"
    "${U_MAIN_INCLUDE_DIR}/utopia/core/assert.hpp"
    "${U_MAIN_INCLUDE_DIR}/utopia/core/check_ops.hpp"
    "${U_MAIN_INCLUDE_DIR}/utopia/core/concepts.hpp"
    "${U_MAIN_INCLUDE_DIR}/utopia/core/guard.hpp"
)
set(U_CORE_TOTAL_FILE ${U_CORE_SOURCE_FILE} ${U_CORE_HEADER_FILE})

# 设置IDE项目结构
function(u_set_core_source_group)
    source_group(TREE "${U_MAIN_SOURCE_DIR}/lib" FILES ${U_CORE_SOURCE_FILE})
    source_group(TREE ${U_MAIN_SOURCE_DIR} FILES ${U_CORE_HEADER_FILE})
endfunction(u_set_core_source_group)

# 标准选项
# 这些选项将会给client,server和test一起使用
function(u_add_standard_options)
    u_add_boost_library(${ARGV})
    u_include_configure_header(${ARGV})
    u_add_fmt_library(${ARGV})
    target_include_directories(
        ${ARGV}
        PUBLIC
        "${U_MAIN_INCLUDE_DIR}"
    )
endfunction(u_add_standard_options)

# 添加子项目
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/client")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/server")

# 我们的测试可还需要这些源文件
set(U_CLIENT_TEST_FILE ${U_CLIENT_TEST_FILE} PARENT_SCOPE)
set(U_SERVER_TEST_FILE ${U_SERVER_TEST_FILE} PARENT_SCOPE)
