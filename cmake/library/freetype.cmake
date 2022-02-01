#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

find_package(freetype CONFIG REQUIRED)

function(u_add_freetype_library)
    target_link_libraries(${ARGV} PRIVATE freetype)
endfunction(u_add_freetype_library)

list(APPEND U_3RD_LIBRARY_FUNCTION_LIST "u_add_freetype_library | ${CMAKE_CURRENT_LIST_FILE}")
