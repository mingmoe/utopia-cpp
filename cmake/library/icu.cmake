#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

find_package(ICU REQUIRED COMPONENTS io)

function(u_add_icu_library)
    target_include_directories(${ARGV} PRIVATE ICU ICU::io)
endfunction(u_add_icu_library)

list(APPEND U_3RD_LIBRARY_FUNCTION_LIST "u_add_icu_library | ${CMAKE_CURRENT_LIST_FILE}")
