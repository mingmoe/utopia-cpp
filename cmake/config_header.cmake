#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
#
# 生成配置头文件
#
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

set(U_CONFIG_HEADER_SOURCE 
    "${CMAKE_SOURCE_DIR}/src/config.hpp")
set(U_CONFIG_HEADER_INCLUDE_DIR 
    "${CMAKE_CURRENT_BINARY_DIR}/utopia-configed/include")
set(U_CONFIG_HEADER_OUTPUT 
    "${U_CONFIG_HEADER_INCLUDE_DIR}/utopia/config/configured.hpp")

# 设置提示信息
set(
	"this_file_is_waiting_to_be_configured_by_CMake" 
	"this file has been configured by cmake. origin:${U_CONFIG_HEADER_SOURCE}"
)

configure_file(
	${U_CONFIG_HEADER_SOURCE}
	${U_CONFIG_HEADER_OUTPUT}
)

# helper function
function(u_include_configure_header)
    include_directories(
    ${ARGV}
    PUBLIC
    ${U_CONFIG_HEADER_INCLUDE_DIR}
    )
endfunction(u_include_configure_header)
