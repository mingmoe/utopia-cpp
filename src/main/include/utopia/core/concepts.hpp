//===--------------- concepts.hpp - concepts补全 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020-2022 moe-org All rights reserved.
//
//===------------------------------------------------------===//
/// \file
/// 这个文件对c++20的concepts进行了补全
//===------------------------------------------------------===//

#ifndef UTOPIA_CORE_CONCEPTS_HPP
#define UTOPIA_CORE_CONCEPTS_HPP

namespace utopia::core {

    /// @brief 定义了()运算符
    template<typename T>
    concept callable = requires(T f) {
        f();
    };

    template<typename T>
    concept pointer = requires(T f) {
        f = nullptr;
    };


}   // namespace utopia::core


#endif
