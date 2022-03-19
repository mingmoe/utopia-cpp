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
message(STATUS "UTOPIA_PUBLIC_ENABLE_CLANG_TIDY | 定义此变量为ON来启用clang-tidy | OFF")
message(STATUS "UTOPIA_PUBLIC_CLANG_TIDY_PATH | clang tidy path | clang-tidy ")
message(STATUS "//==--- utopia config helper ---==//")

if(NOT DEFINED UTOPIA_PUBLIC_ENABLE_CLANG_TIDY)
    set(UTOPIA_PUBLIC_ENABLE_CLANG_TIDY OFF)
endif()
if(NOT DEFINED UTOPIA_PUBLIC_CLANG_TIDY_PATH)
    set(UTOPIA_PUBLIC_CLANG_TIDY_PATH "clang-tidy")
endif()
if(NOT DEFINED U_PUBLIC_COLORFUL_DIAGNOSTICS)
    set(U_PUBLIC_COLORFUL_DIAGNOSTICS "ON")
endif()
