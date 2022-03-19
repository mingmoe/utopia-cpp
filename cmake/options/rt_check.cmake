#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
#
# 开启运行时检查
#
# See https://opensource.org/licenses/MIT for license information.
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

message(STATUS "check compile option:U_PUBLIC_OPTION_RT_CHECK")

if("${U_PUBLIC_OPTION_RT_CHECK}" STREQUAL ON AND "${U_PUBLIC_OPTION_SANITIZE}" STREQUAL ON)
    message(FATAL_ERROR "运行时检查和地址消毒不兼容!")
endif()

if(MSVC AND "${U_PUBLIC_OPTION_RT_CHECK}" STREQUAL ON)
    message(STATUS "enable compiler option:runtime check")

    set(U_RT_CHECK "/sdl /RTC1 /GS")

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${U_RT_CHECK}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${U_RT_CHECK}")

    unset(U_RT_CHECK)
endif()

