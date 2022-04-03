//===--------------- bitmap.hpp - 位图定义 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020-2022 moe-org All rights reserved.
//
//===---------------------------------------------------===//
/// \file
/// 这个文件定义了用于输出的位图
//===---------------------------------------------------===//

#ifndef UTOPIA_CLIENT_RENDER_BITMAP_HPP
#define UTOPIA_CLIENT_RENDER_BITMAP_HPP

#ifndef UTOPIA_PLATFORM_CLIENT
    #error this file is only compiled in client of utopia
#endif

#include <cstdint>
#include <iostream>
#include <span>
#include <string>

#include <utopia/core/exception.hpp>

namespace utopia::client::render {

    /// @brief 位图中的每一位。RGBA。
    struct BitmapBit {
        uint8_t red{ 0 };
        uint8_t green{ 0 };
        uint8_t blue{ 0 };
        uint8_t alpha{ 0 };
    };

    /// @brief 位图
    class Bitmap {
      private:

        // 以[y][x]的顺序访问
        BitmapBit **data_{ nullptr };

        // 大小
        uint64_t x_size_{ 0 };
        uint64_t y_size_{ 0 };

      public:

        /// @brief 初始化一个位图
        /// @param x_size x轴大小
        /// @param y_size y轴大小
        /// @exception
        Bitmap(uint64_t x_size, uint64_t y_size) :
            x_size_(x_size), y_size_(y_size) {

            if(x_size == 0) {
                throw utopia::core::IllegalArgumentException{
                    "x_size must not be 0"
                };
            }

            if(y_size == 0) {
                throw utopia::core::IllegalArgumentException{
                    "y_size must not be 0"
                };
            }

            data_ = new BitmapBit *[y_size];

            for(uint64_t ptr = 0; ptr != y_size; ptr++) {
                data_[ptr] = new BitmapBit[x_size];

                for(uint64_t x_ptr = 0; x_ptr != x_size; x_ptr++) {
                    data_[ptr][x_ptr] = BitmapBit{};
                }
            }
        }

        // 重写五法则类
        // 允许复制和移动
        ~Bitmap() {
            if(data_ != nullptr) {
                for(uint64_t ptr = 0; ptr != y_size_; ptr++) {
                    delete[] data_[ptr];
                }
                delete[] data_;

                data_ = nullptr;
            }
            x_size_ = 0;
            y_size_ = 0;
        }

        Bitmap(const Bitmap &origin) {
            *this = origin;
        }
        Bitmap &operator=(const Bitmap &origin) {
            this->clear_and_resize(origin.get_x_size(), origin.get_y_size());

            for(decltype(this->x_size_) x = 0; x != this->x_size_; x++) {
                for(decltype(this->y_size_) y = 0; y != this->y_size_; y++) {
                    write_point(x, y, origin.get_point(x, y));
                }
            }

            return *this;
        }

        Bitmap(Bitmap &&origin) noexcept {
            *this = origin;
        }

        Bitmap &operator=(Bitmap &&origin) noexcept {
            this->~Bitmap();   // free this

            this->data_   = origin.data_;
            this->x_size_ = origin.x_size_;
            this->y_size_ = origin.y_size_;

            // 我们不手动调用origin的析构函数
            // 否则data_会被delete[]
            origin.data_   = nullptr;
            origin.x_size_ = 0;
            origin.y_size_ = 0;

            return *this;
        }

        /// @brief 获取位图x轴大小
        inline uint64_t get_x_size() const noexcept {
            return this->x_size_;
        }

        /// @brief 获取位图y轴大小
        inline uint64_t get_y_size() const noexcept {
            return this->y_size_;
        }

        /// @brief 判断点是否在位图内
        /// @note 坐标位置自0开始，如同数组下标
        /// @return 在位图范围内返回true，否则返回false
        inline bool is_in_range(uint64_t x, uint64_t y) const noexcept {
            if(x >= x_size_) {
                return false;
            }
            if(y >= y_size_) {
                return false;
            }
            return true;
        }

        /// @brief 获取位图点
        /// @param x x轴
        /// @param y y轴
        /// @note 坐标位置自0开始，如同数组下标
        /// @return 位图点。如果坐标超出范围则抛出OutOfRangeException
        inline BitmapBit get_point(uint64_t x, uint64_t y) const {
            if(!is_in_range(x, y)) {
                throw utopia::core::OutOfRangeException{
                    "position out of range of bitmap"
                };
            }

            return this->data_[y][x];
        }

        /// @brief 在指定坐标写入点
        /// @note 坐标位置自0开始，如同数组下标
        /// @exception OutOfRangeException 如果坐标超出范围则抛出
        inline void
            write_point(uint64_t x, uint64_t y, const BitmapBit &point) {
            if(!is_in_range(x, y)) {
                throw utopia::core::OutOfRangeException{
                    "position out of range of bitmap"
                };
            }

            this->data_[y][x] = point;
        }

        /// @brief 清空位图并重新设置位图大小
        /// @param x_size x轴大小
        /// @param y_size y轴大小
        inline void clear_and_resize(uint64_t x_size, uint64_t y_size) {
            this->~Bitmap();
            *this = Bitmap{ x_size, y_size };
        }

        /**
         * @brief 将位图复制到指定位图的指定坐标
         * @param target 目标位图
         * @param target_x 开始写入的目标位置
         * @param target_y 开始写入的目标位置
         * @note 如果开始写入的目标位置超出目标位图大小，则抛出异常。在写入过程中超出除外。
        */
        inline void
            copy_into(Bitmap &target, uint64_t target_x, uint64_t target_y) {
            if(!target.is_in_range(target_x, target_y)) {
                throw utopia::core::OutOfRangeException{
                    "target position out of range of bitmap"
                };
            }

            for(uint64_t x = 0; x != get_x_size(); x++) {
                for(uint64_t y = 0; y != get_y_size(); y++) {
                    if(target.is_in_range(x + target_x, y + target_y)) {
                        target.write_point(x + target_x,
                                           y + target_y,
                                           this->get_point(x, y));
                    }
                }
            }
        }
    };
    /**
     * @brief 将位数写做字符串
     * @param c 占位字符
     * @return 写后的字符串
    */
    inline void write_bitmap_as_chars(Bitmap       &bitmap,
                                      std::ostream &output = std::cout,
                                      char          c      = '*') {
        for(uint64_t y = 0; y != bitmap.get_y_size(); y++) {
            for(uint64_t x = 0; x != bitmap.get_x_size(); x++) {
                auto color = bitmap.get_point(x, y);
                output << "\033[38;2;" << std::to_string(color.red) << ";"
                       << std::to_string(color.green) << ";"
                       << std::to_string(color.blue) << "m" << c;
            }
            output << "\n";
        }
        output << "\033[0m";
    }


}   // namespace utopia::client::render

#endif
