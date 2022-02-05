#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
#
# 定义一些编译器选项
#
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

# clang tidy设置
if(NOT DEFINED UTOPIA_PUBLIC_CLANG_TIDY_PATH)
    set(UTOPIA_PUBLIC_CLANG_TIDY_PATH "clang-tidy")
endif()

if("${UTOPIA_PUBLIC_ENABLE_CLANG_TIDY}" STREQUAL ON)
    if(NOT MSVC)
        function(u_open_clang_tidy)
            set(CMAKE_CXX_CLANG_TIDY 
            ${UTOPIA_PUBLIC_CLANG_TIDY_PATH}
            --use-color
            PARENT_SCOPE
        )
        endfunction(u_open_clang_tidy)
    else()
        message(STATUS "因为某些问题，使用MSVC将会禁用clang-tidy")
        function(u_open_clang_tidy)
        endfunction(u_open_clang_tidy)
    endif()
else()
    function(u_open_clang_tidy)
    endfunction(u_open_clang_tidy)
endif()

function(u_close_clang_tidy)
    if(DEFINED CMAKE_CXX_CLANG_TIDY)
        unset(CMAKE_CXX_CLANG_TIDY)
        unset(CMAKE_CXX_CLANG_TIDY PARENT_SCOPE)
    endif()
endfunction(u_close_clang_tidy)

u_close_clang_tidy()

# 设置编译选项
if(MSVC) # for msvc
    set(U__TEMP__FLAGS_ 
    "/DWIN32 /D_WINDOWS /utf-8 /W4 /permissive- /EHsc /GR /Zc:__cplusplus /D_CRT_SECURE_NO_WARNINGS")
    set(U__TEMP__FLAGS_DEBUG "/Od /Z7 /MDd")
    set(U__TEMP__FLAGS_RELEASE "/O2 /MD /DNDEBUG")

    set(CMAKE_C_FLAGS "${U__TEMP__FLAGS_} /std:c11")
    set(CMAKE_C_FLAGS_DEBUG "${U__TEMP__FLAGS_DEBUG}")
    set(CMAKE_C_FLAGS_RELEASE "${U__TEMP__FLAGS_RELEASE}")

    set(CMAKE_CXX_FLAGS "${U__TEMP__FLAGS_} /std:c++20")
    set(CMAKE_CXX_FLAGS_DEBUG "${U__TEMP__FLAGS_DEBUG}")
    set(CMAKE_CXX_FLAGS_RELEASE "${U__TEMP__FLAGS_RELEASE}")

    unset(U__TEMP__FLAGS_)
    unset(U__TEMP__FLAGS_DEBUG)
    unset(U__TEMP__FLAGS_RELEASE)

else() # for gcc\clang

    set(U__TEMP__FLAGS_ "-Wall -Wextra -Werror")
    set(U__TEMP__FLAGS_DEBUG "-O0 -g3 -ggdb")
    set(U__TEMP__FLAGS_RELEASE "-O3 -g0 -DNDEBUG")

    set(CMAKE_C_FLAGS "${U__TEMP__FLAGS_} -std=c11")
    set(CMAKE_C_FLAGS_DEBUG "${U__TEMP__FLAGS_DEBUG}")
    set(CMAKE_C_FLAGS_RELEASE "${U__TEMP__FLAGS_RELEASE}")

    set(CMAKE_CXX_FLAGS "${U__TEMP__FLAGS_} -std=c++20 -fcxx-exceptions")
    set(CMAKE_CXX_FLAGS_DEBUG "${U__TEMP__FLAGS_DEBUG}")
    set(CMAKE_CXX_FLAGS_RELEASE "${U__TEMP__FLAGS_RELEASE}")


    unset(U__TEMP__FLAGS_)
    unset(U__TEMP__FLAGS_DEBUG)
    unset(U__TEMP__FLAGS_RELEASE)
endif()


# 第三方编译选项列表
set(U_COMPILE_OPTIONS_INFO_LIST "")

# 引入第三方选项
file(GLOB_RECURSE U_COMPILE_OPTIONS_SETTINGS "${U_CMAKE_MODULE_DIR}/options/*")

foreach(OPTION IN LISTS U_COMPILE_OPTIONS_SETTINGS)
    message(STATUS "loading compiler options from:${OPTION}")
    include(${OPTION})
endforeach()

unset(U_COMPILE_OPTIONS_SETTINGS)

# 打印信息
message(STATUS "//==--- utopia compiler options ---==//")
message(STATUS "定义变量为ON来启用编译选项")
message(STATUS "option | usage | from")
foreach(OPTION IN LISTS U_COMPILE_OPTIONS_INFO_LIST)
    message(STATUS ${OPTION})
endforeach()
message(STATUS "//==--- utopia compiler options ---==//")

unset(U_COMPILE_OPTIONS_INFO_LIST)
