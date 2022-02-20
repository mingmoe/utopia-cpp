#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
#
# 管理依赖
#
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

# 引入第三方库
file(GLOB_RECURSE U_3RD_LIBRARY_CMAKE_LIST "${U_CMAKE_MODULE_DIR}/library/*")

foreach(LIB_CMAKE IN LISTS U_3RD_LIBRARY_CMAKE_LIST)
    message(STATUS "load 3rd library support:${LIB_CMAKE}")
    u_include_at_root(${LIB_CMAKE})
endforeach()

unset(U_3RD_LIBRARY_CMAKE_LIST)
