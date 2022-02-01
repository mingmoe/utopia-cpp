#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
#
# utopia项目的根构建文件
#
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# note for build system ADVENTURERS:
# this file and those cmake files under cmake directory is included
# 
#=====--------------------------------------------------------------------
cmake_minimum_required (VERSION 3.21)

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/define.cmake")
include("${U_CMAKE_MODULE_DIR}/init-library.cmake")

project(${U_PROJECT} VERSION ${U_VERSION} LANGUAGES CXX C)

# 设置环境 c++ 20 && c 11
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_STANDARD_REQUIRED True)


# 引入项目
include("${U_CMAKE_MODULE_DIR}/checker.cmake")
include("${U_CMAKE_MODULE_DIR}/options.cmake")
include("${U_CMAKE_MODULE_DIR}/import-library.cmake")
include("${U_CMAKE_MODULE_DIR}/config_header.cmake")

add_subdirectory("${U_UTOPIA_SOURCE_DIR}")
