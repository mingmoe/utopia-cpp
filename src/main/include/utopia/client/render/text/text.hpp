//===--------------- text.hpp - 文本渲染头文件 ---------------===//
//
// this file is under the MIT License
// See https://opensource.org/licenses/MIT for license information.
// Copyright(c) 2020-2022 moe-org All rights reserved.
//
//===------------------------------------------------------===//
/// \file
/// 引入所有与文本渲染有关的头文件
//===------------------------------------------------------===//

// 类型映射指南:
// FT_Library -> Library
// hb_blob -> Font
// hb_face -> Font
// FT_Face -> Face 
// hb_font -> Face

#include <utopia/client/render/text/error.hpp>
#include <utopia/client/render/text/source.hpp>
#include <utopia/client/render/text/library.hpp>
#include <utopia/client/render/text/face.hpp>
#include <utopia/client/render/text/font.hpp>
#include <utopia/client/render/text/renderer.hpp>
#include <utopia/client/render/text/shaper.hpp>
