#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

find_path(UTF8H_INCLUDE_DIRS "utf8h/utf8.h" PARENT_SCOPE)

function(u_add_utf8_library)
    target_include_directories(${ARGV} PRIVATE ${UTF8H_INCLUDE_DIRS})
endfunction(u_add_utf8_library)

message(STATUS "add library by u_add_utf8_library")
