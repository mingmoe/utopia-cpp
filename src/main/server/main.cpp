//===--------------- main.cpp - 入口函数定义 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020 - 2022 moe - org All rights reserved.
//
//===-----------------------------------------------------===//
/// \file
/// 这个文件定义了utopia服务器的入口函数(main)。
/// 不应该与测试相链接。
//===-----------------------------------------------------===//

#ifndef UTOPIA_PLATFORM_TEST
    #ifndef UTOPIA_PLATFORM_SERVER
        #error this file is only compiled in server of utopia
    #endif

    #include <iostream>
    #include <memory>

    #include <utopia/core/convert.hpp>

/// @brief      入口函数
// @param argc 参数数量
// @param argv 参数
/// @return 程序返回值。如果正常退出返回0，否则返回非0值；
int main(int /*argc*/, char * /*argv*/[]) {

    return 0;
}


#endif
