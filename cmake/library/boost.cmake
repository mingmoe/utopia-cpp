#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

find_package(
	Boost
	REQUIRED
)

function(u_add_boost_library)
    target_include_directories(${ARGV} SYSTEM PUBLIC ${Boost_INCLUDE_DIRS})

    if(NOT MSVC)
        message(STATUS "note:build without msvc need link libbacktrace with link argument -lbacktrace")
        message(STATUS "note:build without msvc need link libdl with link argument -ldl")
       
        target_link_libraries(${ARGV} PUBLIC "dl")
        target_link_libraries(${ARGV} PUBLIC "backtrace")

        target_compile_definitions(${ARGV} PUBLIC BOOST_STACKTRACE_USE_BACKTRACE)
    endif()
endfunction(u_add_boost_library)

