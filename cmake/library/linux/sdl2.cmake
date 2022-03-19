#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

# use system library for linux and apple
find_package(SDL2 REQUIRED)
    
function(u_add_sdl2_library)
    target_include_directories(${ARGV} SYSTEM PUBLIC ${SDL2_INCLUDE_DIRS})
    target_link_libraries(${ARGV} PUBLIC ${SDL2_LIBRARIES})
endfunction()

function(u_install_sdl2)
    message(STATUS "note:sdl2 is used from system and won't install to prefix")
endfunction()
