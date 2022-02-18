#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
#
# 管理依赖
#
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

# 可用的第三方库列表
set(U_3RD_LIBRARY_FUNCTION_LIST "")

# 引入第三方库
file(GLOB_RECURSE U_3RD_LIBRARY_CMAKE_LIST "${U_CMAKE_MODULE_DIR}/library/*")
foreach(LIB_CMAKE IN LISTS U_3RD_LIBRARY_CMAKE_LIST)
    message(STATUS "load 3rd library support:${LIB_CMAKE}")
    u_include(${LIB_CMAKE})
endforeach()

unset(U_3RD_LIBRARY_CMAKE_LIST)

# 打印信息
message(STATUS "//==--- utopia 3rd library list ---==//")
message(STATUS "function | from")
foreach(LIB IN LISTS U_3RD_LIBRARY_FUNCTION_LIST)
    message(STATUS ${LIB})
endforeach()
message(STATUS "//==--- utopia 3rd library list ---==//")

# 拉完屎擦干净是好习惯
unset(U_3RD_LIBRARY_FUNCTION_LIST)
