#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
# this file is under MIT License.
# See https://opensource.org/licenses/MIT for license information.
# Copyright (c) 2020-2022 moe-org All rights reserved.
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

set(U_DEPENDENCE_ASIO_INCLUDE_DIR "${U_UTOPIA_DEPENDENCE_DIR}/asio/asio/include")
set(U_DEPENDENCE_ASIO_DEFINEDS 
"BOOST_DATE_TIME_NO_LIB" "BOOST_REGEX_NO_LIB"
"ASIO_NO_DEPRECATED"
)

function(u_add_asio_library)
    target_include_directories(${ARGV} SYSTEM PUBLIC ${U_DEPENDENCE_ASIO_INCLUDE_DIR})
    target_compile_definitions(${ARGV} PUBLIC ${U_DEPENDENCE_ASIO_DEFINEDS})
endfunction(u_add_asio_library)
