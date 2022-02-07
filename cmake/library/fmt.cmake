#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

find_package(fmt CONFIG REQUIRED)

function(u_add_fmt_library)
 target_link_libraries(${ARGV} PRIVATE fmt::fmt)
endfunction(u_add_fmt_library)

list(APPEND U_3RD_LIBRARY_FUNCTION_LIST "u_add_fmt_library | ${CMAKE_CURRENT_LIST_FILE}")
