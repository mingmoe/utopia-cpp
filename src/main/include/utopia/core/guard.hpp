//===--------------- guard.hpp - Gurad定义 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020-2022 moe-org All rights reserved.
//
//===----------------------------------------------------===//
/// \file
/// 提供了一个Guard类来管理生命周期。在析构时会对指定指针调用指定函数。
//===----------------------------------------------------===//


#ifndef UTOPIA_CORE_GUARD_HPP
#define UTOPIA_CORE_GUARD_HPP

#include <type_traits>
#include <utility>

#include <utopia/core/assert.hpp>
#include <utopia/core/concepts.hpp>

namespace utopia::core {

    /// @brief Guard封装。
    /// 此类负责管理指针资源。在析构的时候会将指针作为参数传入到一个函数内。
    template<typename Type, typename UnlockFunc>
        requires std::is_same_v<void(Type *), UnlockFunc>
    class Guard {
      private:

        Type       *handle_{ nullptr };
        UnlockFunc *unlock_func_{ nullptr };

      public:

        Guard(Type *obj, UnlockFunc *func) {
            if(func == nullptr) {
                utopia::core::failed(
                    "Guard need a non-null unlock func");
            }

            this->handle_      = obj;
            this->unlock_func_ = func;
        }

        ~Guard() {
            if(handle_ != nullptr && unlock_func_ != nullptr) {
                unlock_func_(handle_);
                handle_ = nullptr;
            }
        }

        Guard(const Guard<Type, UnlockFunc> &) = delete;
        Guard &operator=(const Guard<Type, UnlockFunc> &) = delete;

        Guard(Guard<Type, UnlockFunc> &&origin) {
            *this = std::move(origin);
        }

        Guard &operator=(Guard<Type, UnlockFunc> &&origin) {
            this->~Guard();
            this->handle_       = origin.handle_;
            this->unlock_func_  = origin.unlock_func_;

            origin.handle_      = nullptr;
            origin.unlock_func_ = nullptr;
        }
    };

}   // namespace utopia::client::render::sdl

#endif
