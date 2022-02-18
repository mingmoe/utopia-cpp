#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

set(U_TEST_NEED_SOURCE_FILES)

macro(u_add_test_source SOURCE_FILES)
    list(APPEND U_TEST_NEED_SOURCE_FILES ${SOURCE_FILES})
    set(U_TEST_NEED_SOURCE_FILES "${U_TEST_NEED_SOURCE_FILES}" PARENT_SCOPE)
endmacro(u_add_test_source)

u_add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/main")

# note:test depends on main
u_add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/test")
