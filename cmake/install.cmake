#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
#
# 设置第三方库
#
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

install(TARGETS ${U_PROJECT_CLIENT}
    DESTINATION "client")

u_install_sdl2(DESTINATION "client")
u_install_harfbuzz(DESTINATION "client")
u_install_icu(DESTINATION "client")
u_install_freetype(DESTINATION "client")

install(TARGETS ${U_PROJECT_SERVER}
    DESTINATION "server")
u_install_icu(DESTINATION "server")
