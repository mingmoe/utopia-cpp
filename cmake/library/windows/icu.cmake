#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

set(U_DEPENDENCE_ICU_INCLUDE_DIR 
"${U_UTOPIA_PREBUILT_DIR}/icu-win/include")
#==============================================
u_import_win_library(U_ICU_UC 
"${U_UTOPIA_PREBUILT_DIR}/icu-win/lib64/icuuc.lib" 
"${U_UTOPIA_PREBUILT_DIR}/icu-win/bin64/icuuc70.dll")
#==============================================
u_import_win_library(U_ICU_DT
"${U_UTOPIA_PREBUILT_DIR}/icu-win/lib64/icudt.lib" 
"${U_UTOPIA_PREBUILT_DIR}/icu-win/bin64/icudt70.dll")
#==============================================
u_import_win_library(U_ICU_IO
"${U_UTOPIA_PREBUILT_DIR}/icu-win/lib64/icuio.lib" 
"${U_UTOPIA_PREBUILT_DIR}/icu-win/bin64/icuio70.dll")
#==============================================
u_import_win_library(U_ICU_IN
"${U_UTOPIA_PREBUILT_DIR}/icu-win/lib64/icuin.lib" 
"${U_UTOPIA_PREBUILT_DIR}/icu-win/bin64/icuin70.dll")
#==============================================

function(u_add_icu_library)
    target_include_directories(${ARGV} SYSTEM PUBLIC ${U_DEPENDENCE_ICU_INCLUDE_DIR})
    target_link_libraries(${ARGV} PUBLIC U_ICU_UC U_ICU_DT U_ICU_IO U_ICU_IN)
    
    add_custom_command(TARGET ${ARGV} POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${U_UTOPIA_PREBUILT_DIR}/icu-win/bin64/icuio70.dll"
        $<TARGET_FILE_DIR:${ARGV}>)
    add_custom_command(TARGET ${ARGV} POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${U_UTOPIA_PREBUILT_DIR}/icu-win/bin64/icuuc70.dll"
        $<TARGET_FILE_DIR:${ARGV}>)
    add_custom_command(TARGET ${ARGV} POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${U_UTOPIA_PREBUILT_DIR}/icu-win/bin64/icudt70.dll"
        $<TARGET_FILE_DIR:${ARGV}>)
    add_custom_command(TARGET ${ARGV} POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${U_UTOPIA_PREBUILT_DIR}/icu-win/bin64/icuin70.dll"
        $<TARGET_FILE_DIR:${ARGV}>)
endfunction()

function(u_install_icu)
    install(IMPORTED_RUNTIME_ARTIFACTS U_ICU_UC ${ARGV})
    install(IMPORTED_RUNTIME_ARTIFACTS U_ICU_DT ${ARGV})
    install(IMPORTED_RUNTIME_ARTIFACTS U_ICU_IO ${ARGV})
    install(IMPORTED_RUNTIME_ARTIFACTS U_ICU_IN ${ARGV})
endfunction()
