#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

if(U_DEBUG_MODE)
set(U_DEPENDENCE_HARFBUZZ_INCLUDE_DIR 
"${U_UTOPIA_LINUX_PRE_DIR}/debug/harfbuzz/include")

u_import_static_library(U_HARFBUZZ 
"${U_UTOPIA_LINUX_PRE_DIR}/debug/harfbuzz/lib/x86_64-linux-gnu/libharfbuzz.a")

else()

set(U_DEPENDENCE_HARFBUZZ_INCLUDE_DIR 
"${U_UTOPIA_LINUX_PRE_DIR}/harfbuzz/include")

u_import_static_library(U_HARFBUZZ 
"${U_UTOPIA_LINUX_PRE_DIR}/harfbuzz/lib/x86_64-linux-gnu/libharfbuzz.a")

endif()
    

function(u_add_harfbuzz_library)
    target_include_directories(${ARGV} SYSTEM PUBLIC ${U_DEPENDENCE_HARFBUZZ_INCLUDE_DIR})
    target_link_libraries(${ARGV} PUBLIC U_HARFBUZZ)
endfunction()

function(u_install_harfbuzz)
endfunction()
