#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

add_subdirectory("${U_UTOPIA_DEPENDENCE_DIR}/fmt" EXCLUDE_FROM_ALL)

function(u_add_fmt_library)
    target_link_libraries(${ARGV} PRIVATE fmt::fmt-header-only)
endfunction(u_add_fmt_library)
