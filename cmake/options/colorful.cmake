#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
#
# 为编译器启动彩色输出
#
# See https://opensource.org/licenses/MIT for license information.
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

if(NOT MSVC AND "${U_PUBLIC_COLORFUL_DIAGNOSTICS}" STREQUAL ON)
    message(STATUS "enable compiler option:colorful")
    
    if(DEFINED U_USE_CLANG)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fcolor-diagnostics")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcolor-diagnostics")
    elseif(DEFINED U_USE_GCC)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fdiagnostics-color=always")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always")
    endif()

endif()

list(APPEND U_COMPILE_OPTIONS_INFO_LIST 
"U_PUBLIC_COLORFUL_DIAGNOSTICS | 为gcc和clang启用彩色输出 | ${CMAKE_CURRENT_LIST_FILE}")

