#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

set(U_DEPENDENCE_SDL_INCLUDE_DIR 
"${U_UTOPIA_PREBUILT_DIR}/sdl-win/include")

#==============================================
u_import_win_library(U_SDL2 
"${U_UTOPIA_PREBUILT_DIR}/sdl-win/lib/x64/SDL2.lib"
"${U_UTOPIA_PREBUILT_DIR}/sdl-win/lib/x64/SDL2.dll")
#==============================================
u_import_static_library(U_SDL2_MAIN 
"${U_UTOPIA_PREBUILT_DIR}/sdl-win/lib/x64/SDL2main.lib")
#==============================================

function(u_add_sdl2_library)
    target_include_directories(${ARGV} SYSTEM PUBLIC ${U_DEPENDENCE_SDL_INCLUDE_DIR})
    target_link_libraries(${ARGV} PUBLIC U_SDL2 U_SDL2_MAIN)

    
    add_custom_command(TARGET ${ARGV} POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${U_UTOPIA_PREBUILT_DIR}/sdl-win/lib/x64/SDL2.dll"
        $<TARGET_FILE_DIR:${ARGV}>)
endfunction()

function(u_install_sdl2)
    install(IMPORTED_RUNTIME_ARTIFACTS U_SDL2 ${ARGV})
endfunction()
