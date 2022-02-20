#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
#
# 开启地址消毒
#
# See https://opensource.org/licenses/MIT for license information.
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

if("${U_PUBLIC_OPTION_SANITIZE}" STREQUAL ON)
    message(STATUS "enable compiler option:sanitize")

    if(NOT MSVC)
        set(U_SANITIZE_OPTIONS "-fsanitize=address -fno-omit-frame-pointer")
        set(U_SANITIZE_OPTIONS "${U_SANITIZE_OPTIONS} -fno-optimize-sibling-calls") 
        set(U_SANITIZE_OPTIONS "${U_SANITIZE_OPTIONS} -fsanitize-address-use-after-scope")
        set(U_SANITIZE_OPTIONS "${U_SANITIZE_OPTIONS} -fsanitize=undefined")

        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${U_SANITIZE_OPTIONS}")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${U_SANITIZE_OPTIONS}")

        if(DEFINED U_USE_CLANG)
            set(U_SANITIZE_OPTIONS "-fsanitize-address-use-after-return=always")
        else()
            set(U_SANITIZE_OPTIONS "")
        endif()
    
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${U_SANITIZE_OPTIONS}")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${U_SANITIZE_OPTIONS}")

        unset(U_SANITIZE_OPTIONS)

    else()
        set(U_SANITIZE_OPTIONS "/fsanitize=address")
        set(U_SANITIZE_OPTIONS "${U_SANITIZE_OPTIONS} /fsanitize-address-use-after-return")
        
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${U_SANITIZE_OPTIONS}")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${U_SANITIZE_OPTIONS}")

        unset(U_SANITIZE_OPTIONS)
    endif()
endif()

