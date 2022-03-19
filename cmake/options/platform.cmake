#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
#
# 为各种平台定义宏
#
# See https://opensource.org/licenses/MIT for license information.
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

message(STATUS "check compile option:U_PUBLIC_COLORFUL_DIAGNOSTICS")

if(MSVC)
    set(U_CONFIG_HEADER_SETTING_COMPILE "UTOPIA_USE_MSVC")
elseif(U_USE_GCC)
    set(U_CONFIG_HEADER_SETTING_COMPILE "UTOPIA_USE_GCC")
else()
    set(U_CONFIG_HEADER_SETTING_COMPILE "UTOPIA_USE_CLANG")
endif()

if(UNIX AND NOT APPLE)
    set(U_CONFIG_HEADER_SETTING_SYSTEM "UTOPIA_UNDER_LINUX")
elseif(WIN32)
    set(U_CONFIG_HEADER_SETTING_SYSTEM "UTOPIA_UNDER_WINDOWS")
else()
    set(U_CONFIG_HEADER_SETTING_SYSTEM "UTOPIA_UNDER_APPLE")
endif()
