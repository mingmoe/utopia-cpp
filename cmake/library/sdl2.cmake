#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

find_package(SDL2 CONFIG REQUIRED)
find_package(sdl2-gfx CONFIG REQUIRED)
find_package(sdl2-image CONFIG REQUIRED)
find_package(sdl2-mixer CONFIG REQUIRED)

function(u_add_sdl2_library)
    target_link_libraries(${ARGV} PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2::SDL2_gfx SDL2::SDL2_image SDL2::SDL2_mixer)
endfunction(u_add_sdl2_library)
