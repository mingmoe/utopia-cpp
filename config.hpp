//=================================================================
// file:         config.hpp
// Copyright (c) 2020-2021 moe-org 保留所有权利
//=================================================================

#pragma once

// =======================================
// note
// @this_file_is_waiting_to_be_configured_by_CMake@
// =======================================

namespace utopia {
	namespace config {

		/**
		* @brief 编译器ID
		*/
		constexpr const char* COMPILER_ID = "@CMAKE_CXX_COMPILER_ID@";

		/**
		* @brief 编译器版本
		*/
		constexpr const char* COMPILER_VERSION = "@CMAKE_CXX_COMPILER_VERSION@";

		/**
		* @brief 构建版本
		*/
		constexpr const char* UTOPIA_VERSION = "@U_VERSION@";

		/**
		* @brief 构建类型
		*/
		constexpr const char* BUILD_TYPE = "@CMAKE_BUILD_TYPE@";
	}
}
