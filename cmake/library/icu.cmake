#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

find_package(ICU REQUIRED COMPONENTS io)

function(u_add_icu_library)
    target_include_directories(${ARGV} SYSTEM PRIVATE ICU ICU::io)
endfunction(u_add_icu_library)

