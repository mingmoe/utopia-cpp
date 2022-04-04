//===--------------- group.hpp - group头文件 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020-2022 moe-org All rights reserved.
//
//===------------------------------------------------------------===//
/// \file
/// 声明Group接口。这个接口管理一组Drawable组件。
//===------------------------------------------------------------===//

#ifndef UTOPIA_CLIENT_RENDER_UI_GROUP_HPP
#define UTOPIA_CLIENT_RENDER_UI_GROUP_HPP

#include <map>
#include <memory>

#include <utopia/client/render/ui/drawable.hpp>

namespace utopia::client::render::ui {

    /// @brief 一个接口。代表可渲染组件。
    class Group {
      private:

        uint64_t next_id_{ 0 };

        /**
         * \brief 组件列表
         */
        std::map<uint64_t, std::shared_ptr<Drawable>> items_{};

      public:

        Group()              = default;
        virtual ~Group()     = default;

        Group(const Group &) = delete;
        Group(Group &&)      = delete;
        Group &operator=(const Group &) = delete;
        Group &operator=(Group &&) = delete;

        /**
         * @brief 添加组件
        * @return 组件id
         */
        inline uint64_t add_item(std::shared_ptr<Drawable> item) {
            auto id = next_id_;
            next_id_++;
            items_.insert(std::make_pair(id, item));
            return id;
        }

        /**
         * \brief 删除组件
         * \param id 组件id
         */
        inline void remove_item(uint64_t id) {
            items_.erase(id);
        }

        inline void clear() {
            items_.clear();
        }

        inline std::map<uint64_t, std::shared_ptr<Drawable>> get_items() {
            return items_;
        }

        inline void draw(
            std::shared_ptr<utopia::client::render::ui::Context> context) {
            for(const auto &item : items_) {
                item.second->draw_to(context);
            }
        }
    };

}   // namespace utopia::client::render::ui

#endif
