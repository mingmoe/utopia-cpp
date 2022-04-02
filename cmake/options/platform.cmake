#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
#
# 为各种平台定义宏
#
# See https://opensource.org/licenses/MIT for license information.
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

if(U_USE_MSVC)
    set(U_CONFIG_SETTING_COMPILE "UTOPIA_USE_MSVC")
elseif(U_USE_GCC)
    set(U_CONFIG_SETTING_COMPILE "UTOPIA_USE_GCC")
else()
    set(U_CONFIG_SETTING_COMPILE "UTOPIA_USE_CLANG")
endif()

if(U_UNDER_LINUX)
    set(U_CONFIG_SETTING_SYSTEM "UTOPIA_UNDER_LINUX")
elseif(U_UNDER_WINDOWS)
    set(U_CONFIG_SETTING_SYSTEM "UTOPIA_UNDER_WINDOWS")
else()
    set(U_CONFIG_SETTING_SYSTEM "UTOPIA_UNDER_APPLE")
endif()

if(U_DEBUG_MODE)
    set(U_CONFIG_SETTING_MODE "UTOPIA_DEBUG_MODE")
else()
    set(U_CONFIG_SETTING_MODE "UTOPIA_RELEASE_MODE")
endif()


set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D${U_CONFIG_SETTING_COMPILE}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D${U_CONFIG_SETTING_SYSTEM}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D${U_CONFIG_SETTING_MODE}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D${U_CONFIG_SETTING_COMPILE}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D${U_CONFIG_SETTING_SYSTEM}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D${U_CONFIG_SETTING_MODE}")

if(U_ANDROID_MODE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DUTOPIA_ANDROID_MODE")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DUTOPIA_ANDROID_MODE")
endif()


unset(U_CONFIG_SETTING_COMPILE)
unset(U_CONFIG_SETTING_SYSTEM)
unset(U_CONFIG_SETTING_MODE)
