//===--------------- pointer.hpp - 指针有关的定义 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020-2022 moe-org All rights reserved.
//
//===---------------------------------------------------------===//
/// \file
/// 提供了一些有关指针的东西。
//===---------------------------------------------------------===//

#ifndef UTOPIA_CORE_POINTER_HPP
#define UTOPIA_CORE_POINTER_HPP

#include <utility>

#include <utopia/core/debug.hpp>

namespace utopia::core {

    /// @brief 代表被移动过的指针
    template<typename T>
    class MovedPointer {
        mutable T *src_;

      public:
        MovedPointer(MovedPointer &&origin) {
            *this = std::move(origin);
        }
        MovedPointer &operator=(MovedPointer &&origin) {
            src_ = origin.release();
            return *this;
        }

        MovedPointer(const MovedPointer &) = delete;
        MovedPointer &operator=(const MovedPointer &) = delete;

        ~MovedPointer() {
            if(src_ != nullptr) {
                debug_break("pointer not released");
            }
        }

        /// @note 将会把原指针置为空
        explicit MovedPointer(T *&p) noexcept {
            src_ = p;
            p    = nullptr;
        }

        /// @note 如果release多次，后续调用会返回空指针。
        T *release() {
            auto p = src_;
            src_   = nullptr;
            return p;
        }
    };

    template<typename T>
    MovedPointer<T> move_ptr(T *&p) {
        return std::move(MovedPointer<T>{ p });
    }

}   // namespace utopia::core

#endif
