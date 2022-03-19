#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
#
# 设置第三方库
#
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

#==============================================
# 定义一些便捷函数
function(u_import_win_library U_LIB_NAME U_LIB_STATIC U_LIB_SHARED)
    
    add_library(${U_LIB_NAME} SHARED IMPORTED GLOBAL)

    set_property(TARGET ${U_LIB_NAME} 
        PROPERTY IMPORTED_LOCATION ${U_LIB_SHARED})
             
    set_property(TARGET ${U_LIB_NAME} 
        PROPERTY IMPORTED_IMPLIB ${U_LIB_STATIC})
    
endfunction()

#==============================================
function(u_import_shared_library U_LIB_NAME U_LIB_SHARED)

    add_library(${U_LIB_NAME} SHARED IMPORTED GLOBAL)

    set_property(TARGET ${U_LIB_NAME} 
    PROPERTY IMPORTED_LOCATION ${U_LIB_SHARED})

endfunction()
#==============================================

function(u_import_static_library U_LIB_NAME U_LIB_STATIC)

    add_library(${U_LIB_NAME} STATIC IMPORTED GLOBAL)

    set_property(TARGET ${U_LIB_NAME} 
    PROPERTY IMPORTED_LOCATION ${U_LIB_STATIC})

endfunction()

#==============================================

# 引入第三方库
file(GLOB U_THIRD_PARTY_LIBS "${U_CMAKE_MODULE_DIR}/library/*.cmake")

foreach(LIB IN LISTS U_THIRD_PARTY_LIBS)
    message(STATUS "loading common library from:${LIB}")
    u_include_at_root(${LIB})
endforeach()


if(U_UNDER_WINDOWS)
    file(GLOB_RECURSE U_THIRD_PARTY_LIBS "${U_CMAKE_MODULE_DIR}/library/windows/*.cmake")
elseif(U_ANDROID_MODE)
    file(GLOB_RECURSE U_THIRD_PARTY_LIBS "${U_CMAKE_MODULE_DIR}/library/android/*.cmake")
else()
    file(GLOB_RECURSE U_THIRD_PARTY_LIBS "${U_CMAKE_MODULE_DIR}/library/linux/*.cmake")
endif()

foreach(LIB IN LISTS U_THIRD_PARTY_LIBS)
    message(STATUS "loading platform library from:${LIB}")
    u_include_at_root(${LIB})
endforeach()

unset(U_THIRD_PARTY_LIBS)

