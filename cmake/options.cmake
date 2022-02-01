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

function(u_open_clang_tidy)
    if(DEFINED UTOPIA_PUBLIC_ENABLE_CLANG_TIDY)
        set(CMAKE_CXX_CLANG_TIDY 
        ${UTOPIA_PUBLIC_CLANG_TIDY_PATH}
        --use-color
        )
        set(CMAKE_CXX_CLANG_TIDY ${CMAKE_CXX_CLANG_TIDY} PARENT_SCOPE)
    endif()
endfunction(u_open_clang_tidy)

function(u_close_clang_tidy)
    if(DEFINED CMAKE_CXX_CLANG_TIDY)
        unset(CMAKE_CXX_CLANG_TIDY)
        unset(CMAKE_CXX_CLANG_TIDY PARENT_SCOPE)
    endif()
endfunction(u_close_clang_tidy)

u_close_clang_tidy()

# 设置编译选项
if(MSVC) # for msvc
    # 检查: 启用运行时检查,缓冲区安全检查,附加安全检查,地址消毒
    set(U__TEMP__CHECK_FLAGS "/RTC1 /GS /sdl")
    # 如果使用地址消毒，使用:/fsanitize=address /fsanitize-address-use-after-return

    set(U__TEMP__FLAGS_ "/DWIN32 /D_WINDOWS /utf-8 /W4 /permissive-")
    set(U__TEMP__FLAGS_DEBUG "/Od /Z7 ${U__TEMP__CHECK_FLAGS} /MDd")
    set(U__TEMP__FLAGS_RELEASE "/O2 /MD /DNDEBUG")

    set(CMAKE_C_FLAGS "${U__TEMP__FLAGS_} /std:c11")
    set(CMAKE_C_FLAGS_DEBUG "${U__TEMP__FLAGS_DEBUG}")
    set(CMAKE_C_FLAGS_RELEASE "${U__TEMP__FLAGS_RELEASE}")

    set(CMAKE_CXX_FLAGS "${U__TEMP__FLAGS_} /std:c++20 /GR /EHsc /Zc:__cplusplus")
    set(CMAKE_CXX_FLAGS_DEBUG "${U__TEMP__FLAGS_DEBUG}")
    set(CMAKE_CXX_FLAGS_RELEASE "${U__TEMP__FLAGS_RELEASE}")

else() # for gcc\clang

    # 编译器检查选项
    set(U__TEMP__CHECK_FLAGS 
# 检查: 启用地址消毒,启用未定义行为检测器
"-fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls -fsanitize=undefined -fsanitize-address-use-after-scope")

    #==--- 对gcc\clang进行微调
    if(DEFINED U_USE_CLANG)
        set(U__TEMP__CHECK_FLAGS "${U__TEMP__CHECK_FLAGS} -fsanitize-address-use-after-return=always ")
    else()
        # 此if分支为gcc保留 :-)
        set(U__TEMP__CHECK_FLAGS "${U__TEMP__CHECK_FLAGS}")
    endif()
    #==---

    set(U__TEMP__FLAGS_ "-Wall -Wextra")
    set(U__TEMP__FLAGS_DEBUG "-O0 -g3 -ggdb ${U__TEMP__CHECK_FLAGS}")
    set(U__TEMP__FLAGS_RELEASE "-O3 -g0 -DNDEBUG")

    set(CMAKE_C_FLAGS "${U__TEMP__FLAGS_} -std=c11")
    set(CMAKE_C_FLAGS_DEBUG "${U__TEMP__FLAGS_DEBUG}")
    set(CMAKE_C_FLAGS_RELEASE "${U__TEMP__FLAGS_RELEASE}")

    set(CMAKE_CXX_FLAGS "${U__TEMP__FLAGS_} -std=c++20")
    set(CMAKE_CXX_FLAGS_DEBUG "${U__TEMP__FLAGS_DEBUG}")
    set(CMAKE_CXX_FLAGS_RELEASE "${U__TEMP__FLAGS_RELEASE}")
endif()

# 不再定义max\min宏（来自傻逼windows.h)
if(MSVC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /DNOMINMAX")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DNOMINMAX")
endif()
