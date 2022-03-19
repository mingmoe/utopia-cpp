#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

set(U_DEPENDENCE_ICU_INCLUDE_DIR 
"${U_UTOPIA_ANDROID_PRE_DIR}/icu/include")
set(U_DEPENDENCE_ICU_LINK_LIBRARIES 
"${U_UTOPIA_ANDROID_PRE_DIR}/icu/lib/libicudata.a"
"${U_UTOPIA_ANDROID_PRE_DIR}/icu/lib/libicui18n.a"
"${U_UTOPIA_ANDROID_PRE_DIR}/icu/lib/libicuuc.a")

function(u_add_icu_library)
    target_include_directories(${ARGV} SYSTEM PUBLIC ${U_DEPENDENCE_ICU_INCLUDE_DIR})
    target_link_libraries(${ARGV} PUBLIC ${U_DEPENDENCE_ICU_LINK_LIBRARIES})
endfunction()
