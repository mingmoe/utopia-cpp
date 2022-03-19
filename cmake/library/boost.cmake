#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

set(U_ENABLED_BOOST_LIB 
"stacktrace" "config" "core" "winapi" "predef" "static_assert"
"type_traits" "array" "assert" "throw_exception" "container_hash")

function(u_add_boost_library)
    foreach(B_LIB IN LISTS U_ENABLED_BOOST_LIB)
        target_include_directories(${ARGV} SYSTEM PUBLIC 
        "${U_UTOPIA_DEPENDENCE_DIR}/boost/libs/${B_LIB}/include")
    endforeach()

    # for linux,link dl
    if(U_UNDER_LINUX)
        target_link_libraries(${ARGV} PUBLIC dl)
    endif()
endfunction(u_add_boost_library)
