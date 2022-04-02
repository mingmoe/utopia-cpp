#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

set(U_DEPENDENCE_FREETYPE_INCLUDE_DIR 
"${U_UTOPIA_PREBUILT_DIR}/freetype-win/include")

u_import_win_library(U_FREETYPE 
"${U_UTOPIA_PREBUILT_DIR}/freetype-win/release dll/win64/freetype.lib"
"${U_UTOPIA_PREBUILT_DIR}/freetype-win/release dll/win64/freetype.dll")


function(u_add_freetype_library)
    target_include_directories(${ARGV} SYSTEM PUBLIC ${U_DEPENDENCE_FREETYPE_INCLUDE_DIR})
    target_link_libraries(${ARGV} PUBLIC U_FREETYPE)

    add_custom_command(TARGET ${ARGV} POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${U_UTOPIA_PREBUILT_DIR}/freetype-win/release dll/win64/freetype.dll"
        $<TARGET_FILE_DIR:${ARGV}>)
endfunction()

function(u_install_freetype)
    install(IMPORTED_RUNTIME_ARTIFACTS U_FREETYPE ${ARGV})
endfunction()

