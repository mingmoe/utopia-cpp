#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
#
# 定义一些全局变量
#
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

# 基本信息
set(U_PROJECT "utopia")
set(U_VERSION "0.1.0")

message(STATUS "utopia version:${U_VERSION}")

# cmake模块目录
set(U_CMAKE_MODULE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# 项目源码目录
set(U_UTOPIA_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

# 项目测试
set(U_PROJECT_TEST "${U_PROJECT}_test")

# 服务器项目
set(U_PROJECT_SERVER "${U_PROJECT}_server")

# 第三方模块目录
set(U_LIBRARY_DIR "${CMAKE_SOURCE_DIR}/utopia-library")
