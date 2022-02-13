#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

set(U_SERVER_TEST_FILE
    PARENT_SCOPE
)

set(U_SERVER_SOURCE_FILE 
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
)
set(U_SERVER_HEADER_FILE
)
set(U_SERVER_TOTAL_FILE ${U_SERVER_SOURCE_FILE} ${U_SERVER_HEADER_FILE})

u_set_core_source_group()

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX server FILES ${U_SERVER_SOURCE_FILE})
source_group(TREE ${U_MAIN_SOURCE_DIR} FILES ${U_SERVER_HEADER_FILE})


add_executable(
    ${U_PROJECT_SERVER}
    ${U_CORE_TOTAL_FILE}
    ${U_SERVER_TOTAL_FILE}
)

# 为特定的编译目标添加宏
target_compile_definitions(${U_PROJECT_SERVER} PUBLIC UTOPIA_PLATFORM_SERVER)

u_add_standard_options(${U_PROJECT_SERVER})
