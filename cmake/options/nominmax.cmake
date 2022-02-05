#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
#
# 为MSVC定义NOMINMAX宏
#
# See https://opensource.org/licenses/MIT for license information.
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

# 不再定义max\min宏（来自傻逼windows.h)
if(MSVC)
    message(STATUS "enable compiler option:nomaxmin")

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /DNOMINMAX")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DNOMINMAX")
endif()

list(APPEND U_COMPILE_OPTIONS_INFO_LIST 
"必须开启，否则编译错误 | 为MSVC定义NOMINMAX宏 | ${CMAKE_CURRENT_LIST_FILE}")
