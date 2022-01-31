#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
#
# 设置vcpkg
#
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

include(FetchContent)

message(STATUS "download vcpkg, wait...")

FetchContent_Declare(
    vcpkg
    URL "https://github.com/microsoft/vcpkg/archive/master.zip"
    SOURCE_DIR "${U_LIBRARY_DIR}"
    BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/vcpkg"
)
FetchContent_MakeAvailable(vcpkg)

set(CMAKE_TOOLCHAIN_FILE "${U_LIBRARY_DIR}/scripts/buildsystems/vcpkg.cmake"
  CACHE STRING "vcpkg toolchain file")
