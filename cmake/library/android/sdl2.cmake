#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

set(U_DEPENDENCE_SDL_INCLUDE_DIR 
"${U_UTOPIA_ANDROID_PRE_DIR}/sdl2/include")
set(U_DEPENDENCE_SDL_LINK_LIBRARIES
"${U_UTOPIA_ANDROID_PRE_DIR}/sdl2/lib/libSDL2.so")

function(u_add_sdl2_library)
    target_include_directories(${ARGV} SYSTEM PUBLIC ${U_DEPENDENCE_SDL_INCLUDE_DIR})
    target_link_libraries(${ARGV} PUBLIC ${U_DEPENDENCE_SDL_LINK_LIBRARIES})
endfunction()
