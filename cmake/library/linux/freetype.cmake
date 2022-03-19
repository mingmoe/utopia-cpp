#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

# use system library for linux and apple
find_package(Freetype REQUIRED)
    
function(u_add_freetype_library)
    target_include_directories(${ARGV} SYSTEM PUBLIC ${FREETYPE_INCLUDE_DIRS})
    target_link_libraries(${ARGV} PUBLIC Freetype::Freetype)
endfunction()

function(u_install_freetype)
    message(STATUS "note:freetype is used from system and won't install to prefix")
endfunction()
