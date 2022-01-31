#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

find_package(harfbuzz CONFIG REQUIRED)

function(u_add_harfbuzz_library)
    target_include_directories(${ARGV} PRIVATE harfbuzz harfbuzz::harfbuzz)
endfunction(u_add_harfbuzz_library)

message(STATUS "add library by u_add_harfbuzz_library")
