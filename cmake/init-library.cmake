#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
#
# 设置vcpkg
#
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

include(FetchContent)

# 检查配置
if("${UTOPIA_PUBLIC_VCPKG_SOURCE_CN}" STREQUAL ON)
    set(X_VCPKG_ASSET_SOURCES "x-azurl,http://106.15.181.5/")
    set(ENV{X_VCPKG_ASSET_SOURCES} "x-azurl,http://106.15.181.5/")
endif()

if("${UTOPIA_PUBLIC_VCPKG_CLONE_CN}" STREQUAL ON)
    set(U_VCPKG_SOURCE "https://gitee.com/ming-moe/vcpkg")
else()
    set(U_VCPKG_SOURCE "https://github.com/microsoft/vcpkg")
endif()

# 我们使用静态链接 :-)
set(VCPKG_LIBRARY_LINKAGE "static")

# clone
message(STATUS "clone/update vcpkg from ${U_VCPKG_SOURCE}, wait...")

FetchContent_Declare(
    vcpkg
    GIT_REPOSITORY "${U_VCPKG_SOURCE}"
    SOURCE_DIR "${U_LIBRARY_DIR}"
    BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/vcpkg"
)

# use
FetchContent_MakeAvailable(vcpkg)

set(CMAKE_TOOLCHAIN_FILE "${U_LIBRARY_DIR}/scripts/buildsystems/vcpkg.cmake"
  CACHE STRING "vcpkg toolchain file")

unset(U_VCPKG_SOURCE)
