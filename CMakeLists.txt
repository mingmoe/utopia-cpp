#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
#
# utopia项目的根构建文件
#
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# note for build system ADVENTURERS:
# cmake files under cmake all is included at root
# 
#=====--------------------------------------------------------------------
cmake_minimum_required (VERSION 3.21)

# 设置u_include和u_add_subdirectory用于替换include和add_subdirectory
# 这主要是因为: 我们需要获取我们用到的所有cmake文件

set(U_TOTAL_CMAKE_FILES "${CMAKE_CURRENT_LIST_FILE}")

#==============================================
macro(u_include_at_root INCLUDE_FILE_ARG)
    get_filename_component(INCLUDE_FILE ${INCLUDE_FILE_ARG} ABSOLUTE)

    message(STATUS "include cmake:${INCLUDE_FILE}")
    
    list(APPEND U_TOTAL_CMAKE_FILES ${INCLUDE_FILE})
    set(U_TOTAL_CMAKE_FILES ${U_TOTAL_CMAKE_FILES})

    include(${INCLUDE_FILE})

    unset(${INCLUDE_FILE})
    unset(${INCLUDE_FILE_ARG})
endmacro(u_include_at_root)

macro(u_include INCLUDE_FILE_ARG)
    u_include_at_root(${INCLUDE_FILE_ARG})
    set(U_TOTAL_CMAKE_FILES ${U_TOTAL_CMAKE_FILES} PARENT_SCOPE)
endmacro(u_include)

#==============================================

macro(u_add_subdirectory_at_root SUBDIR_ARG)
    get_filename_component(SUBDIR ${SUBDIR_ARG} ABSOLUTE)

    message(STATUS "include subdirectory:${SUBDIR}/CMakeLists.txt")

    list(APPEND U_TOTAL_CMAKE_FILES "${SUBDIR}/CMakeLists.txt")
    set(U_TOTAL_CMAKE_FILES ${U_TOTAL_CMAKE_FILES})

    add_subdirectory(${SUBDIR})

    unset(${SUBDIR_ARG})
    unset(${SUBDIR})
endmacro(u_add_subdirectory_at_root)

macro(u_add_subdirectory SUBDIR_ARG)
    u_add_subdirectory_at_root(${SUBDIR_ARG})
    set(U_TOTAL_CMAKE_FILES ${U_TOTAL_CMAKE_FILES} PARENT_SCOPE)
endmacro()

#==============================================

# 引入项目模块
u_include_at_root("${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.cmake")
u_include_at_root("${CMAKE_CURRENT_SOURCE_DIR}/cmake/define.cmake")
u_include_at_root("${U_CMAKE_MODULE_DIR}/init-library.cmake")

project(${U_PROJECT} VERSION ${U_VERSION} LANGUAGES CXX C)

# 设置环境 c++ 20 && c 11
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_STANDARD_REQUIRED True)


# 引入项目
u_include_at_root("${U_CMAKE_MODULE_DIR}/checker.cmake")
u_include_at_root("${U_CMAKE_MODULE_DIR}/options.cmake")
u_include_at_root("${U_CMAKE_MODULE_DIR}/import-library.cmake")
u_include_at_root("${U_CMAKE_MODULE_DIR}/config_header.cmake")

u_add_subdirectory_at_root("${U_UTOPIA_SOURCE_DIR}")

# 添加cmake自定义项目
# 这主要用于IDE管理cmake文件
add_custom_target(
    "${U_PROJECT}-cmake"
    SOURCES ${U_TOTAL_CMAKE_FILES}
)

source_group(TREE ${CMAKE_SOURCE_DIR} PREFIX CMake FILES ${U_TOTAL_CMAKE_FILES})
