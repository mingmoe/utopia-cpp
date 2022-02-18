#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

u_open_clang_tidy()

# 设置变量等
set(U_MAIN_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(U_MAIN_INCLUDE_DIR "${U_MAIN_INCLUDE_DIR}" PARENT_SCOPE)
set(U_MAIN_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(U_MAIN_SOURCE_DIR "${U_MAIN_SOURCE_DIR}" PARENT_SCOPE)

message(STATUS "utopia main include directory:${U_MAIN_INCLUDE_DIR}")
message(STATUS "utopia main source directory:${U_MAIN_SOURCE_DIR}")

# 标准选项
# 这些选项将会给core,client,server和test一起使用
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
u_add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/core")
u_add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/client")
u_add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/server")

# 我们的测试可还需要这些源文件
set(U_TEST_NEED_SOURCE_FILES ${U_TEST_NEED_SOURCE_FILES} PARENT_SCOPE)
