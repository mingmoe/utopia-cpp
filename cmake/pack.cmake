#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
#
# 打包发布
#
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

set(CPACK_PACKAGE_NAME "${U_PROJECT}")
set(CPACK_PACKAGE_VENDOR "moe-org")

set(CPACK_PACKAGE_DIRECTORY ${U_PACKAGE_OPT_DIR})

set(CPACK_PACKAGE_HOMEPAGE_URL "https://github.com/moe-org")

set(CPACK_PACKAGE_FILE_NAME "${U_PROJECT}-${U_VERSION}-${U_COMPILE_MODE}")

set(CPACK_THREADS 0)
set(CPACK_ARCHIVE_THREADS 0)

set(CPACK_GENERATOR "ZIP")

include(CPack)
