#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
#
# 为MSVC定义NOMINMAX宏
#
# See https://opensource.org/licenses/MIT for license information.
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

# 不再定义max\min宏（来自傻逼的windows.h)
if(DEFINED U_UNDER_WINDOWS)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /DNOMINMAX")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DNOMINMAX")
endif()
