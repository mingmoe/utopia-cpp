#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
#
# 为各种平台定义红
#
# See https://opensource.org/licenses/MIT for license information.
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

function(u_add_platform_define)
  foreach(arg IN LISTS ARGN)
    message(STATUS "add global define:${arg}")

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D${arg}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D${arg}")

    add_compile_definitions(${arg})
  endforeach()
endfunction(u_add_platform_define)

if(MSVC)
    u_add_platform_define("UTOPIA_USE_MSVC")
elseif(U_USE_GCC)
    u_add_platform_define("UTOPIA_USE_GCC")
else()
    u_add_platform_define("UTOPIA_USE_CLANG")
endif()

if(UNIX AND NOT APPLE)
    u_add_platform_define("UTOPIA_IN_LINUX")
elseif(WIN32)
    u_add_platform_define("UTOPIA_IN_WINDOWS")
else()
    u_add_platform_define("UTOPIA_IN_APPLE")
endif()

list(APPEND U_COMPILE_OPTIONS_INFO_LIST 
"必须开启，否则编译错误 | 为各种平台定义宏 | ${CMAKE_CURRENT_LIST_FILE}")
