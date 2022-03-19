#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

set(U_DEPENDENCE_FREETYPE_INCLUDE_DIR 
"${U_UTOPIA_ANDROID_PRE_DIR}/freetype/include/freetype2")

set(U_DEPENDENCE_FREETYPE_LINK_LIBRARIES 
"${U_UTOPIA_ANDROID_PRE_DIR}/freetype/lib/libfreetype.a")

function(u_add_freetype_library)
    target_include_directories(${ARGV} SYSTEM PUBLIC ${U_DEPENDENCE_FREETYPE_INCLUDE_DIR})
    target_link_libraries(${ARGV} PUBLIC ${U_DEPENDENCE_FREETYPE_LINK_LIBRARIES})
endfunction()
