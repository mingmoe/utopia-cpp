#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
#
# cmake配置
#
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

message(STATUS "//==--- utopia config helper ---==//")
message(STATUS "variable | usage | default value")
message(STATUS "UTOPIA_PUBLIC_ENABLE_CLANG_TIDY | 定义此变量为ON来启用clang-tidy | ON")
message(STATUS "UTOPIA_PUBLIC_CLANG_TIDY_PATH | clang tidy path | clang-tidy ")
message(STATUS "UTOPIA_PUBLIC_VCPKG_CLONE_CN | 定义此变量为ON来让clone vcpkg操作使用gitee镜像 | defined ")
message(STATUS "UTOPIA_PUBLIC_VCPKG_SOURCE_CN | 定义此变量为ON来让vcpkg使用国内源更新 | defined ")
message(STATUS "//==--- utopia config helper ---==//")

if(NOT DEFINED UTOPIA_PUBLIC_ENABLE_CLANG_TIDY)
    set(UTOPIA_PUBLIC_ENABLE_CLANG_TIDY ON)
endif()
if(NOT DEFINED UTOPIA_PUBLIC_VCPKG_CLONE_CN)
    set(UTOPIA_PUBLIC_VCPKG_CLONE_CN ON)
endif()
if(NOT DEFINED UTOPIA_PUBLIC_VCPKG_SOURCE_CN)
    set(UTOPIA_PUBLIC_VCPKG_SOURCE_CN ON)
endif()
