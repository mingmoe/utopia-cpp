#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# 设置源文件
set(
    U_CORE_SOURCE_FILE
    "${CMAKE_CURRENT_SOURCE_DIR}/exception.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/assert.cpp"
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

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX core FILES ${U_CORE_SOURCE_FILE})
source_group(TREE ${U_MAIN_SOURCE_DIR} FILES ${U_CORE_HEADER_FILE})

# 添加目标
add_library(${U_PROJECT_CORE} STATIC ${U_CORE_TOTAL_FILE})

u_add_standard_options(${U_PROJECT_CORE})
