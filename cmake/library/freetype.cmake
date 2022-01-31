#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

find_package(freetype CONFIG REQUIRED)

function(u_add_freetype_library)
    target_link_libraries(${ARGV} PRIVATE freetype)
endfunction(u_add_freetype_library)

message(STATUS "add library by u_add_freetype_library")
