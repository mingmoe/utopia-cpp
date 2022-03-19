#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

set(U_DEPENDENCE_ICU_INCLUDE_DIR 
"${U_UTOPIA_PREBUILT_DIR}/icu-linux/icu/usr/local/include")
   
#==============================================
u_import_shared_library(U_ICU_UC 
"${U_UTOPIA_PREBUILT_DIR}/icu-linux/icu/usr/local/lib/libicuuc.so.70.1")
#==============================================
u_import_shared_library(U_ICU_DT
"${U_UTOPIA_PREBUILT_DIR}/icu-linux/icu/usr/local/lib/libicudata.so.70.1")
#==============================================
u_import_shared_library(U_ICU_IO
"${U_UTOPIA_PREBUILT_DIR}/icu-linux/icu/usr/local/lib/libicuio.so.70.1")
#==============================================
u_import_shared_library(U_ICU_I18N
"${U_UTOPIA_PREBUILT_DIR}/icu-linux/icu/usr/local/lib/libicui18n.so.70.1")
#==============================================

function(u_add_icu_library)
    target_include_directories(${ARGV} SYSTEM PUBLIC ${U_DEPENDENCE_ICU_INCLUDE_DIR})
    target_link_libraries(${ARGV} PUBLIC U_ICU_UC U_ICU_DT U_ICU_IO U_ICU_I18N)
endfunction()

function(u_install_icu)
    install(IMPORTED_RUNTIME_ARTIFACTS U_ICU_UC ${ARGV})
    install(IMPORTED_RUNTIME_ARTIFACTS U_ICU_DT ${ARGV})
    install(IMPORTED_RUNTIME_ARTIFACTS U_ICU_IO ${ARGV})
    install(IMPORTED_RUNTIME_ARTIFACTS U_ICU_I18N ${ARGV})
endfunction()

