#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
#
# 环境检查
#
# 同时会设置三个变量
# U_USE_(GCC|CLANG|MSVC)
# 如果使用不支持的编译器，默认U_USE_CLANG
# 
# 标准编译套件:
# msvc >= 19.30.0
# gcc >= 11.0.0
# clang >= 13.0.0
#
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "11.0.0")
		message(WARNING "gcc version may be too old")
		message(STATUS "official-build use gcc 11 or higher")
	endif()

    set(U_USE_GCC "true")

elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "13.0.0")
		message(WARNING "clang version may be too old")
		message(STATUS "official-build use clang 13 or higher")
	endif()

    set(U_USE_CLANG "true")

elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "19.30.0")
		message(WARNING "msvc version may be too old")
		message(STATUS "official-build use msvc 19.30 or higher")
	endif()
    
    set(U_USE_MSVC "true")

else()
	message(
		WARNING 
		"unknow c++ compiler:${CMAKE_CXX_COMPILER_ID}. something may go wrong"
	)

    set(U_USE_CLANG "true")
endif()

# 只支持Debug和Release模式
if(NOT CMAKE_BUILD_TYPE MATCHES "^(Debug)|(Release)$")
    message(FATAL_ERROR "unknown build type:${CMAKE_BUILD_TYPE} only support Debug or Release")
else()
    message(STATUS "utopia build type:${CMAKE_BUILD_TYPE}")
endif()
