
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2021, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Primitive types.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _GSG_CONSTANTS_PRIMITIVE_MODES_H_
#define _GSG_CONSTANTS_PRIMITIVE_MODES_H_

#include "GSG/Scene/Export.h"


namespace GSG {
namespace Constants {


struct GSG_SCENE_EXPORT Mode
{
  #define LINE_NUMBER_OFFSET 1000
  static constexpr unsigned int LINE_LOOP                = LINE_NUMBER_OFFSET + __LINE__;
  static constexpr unsigned int LINE_STRIP               = LINE_NUMBER_OFFSET + __LINE__;
  static constexpr unsigned int LINE_STRIP_ADJACENCY     = LINE_NUMBER_OFFSET + __LINE__;
  static constexpr unsigned int LINES                    = LINE_NUMBER_OFFSET + __LINE__;
  static constexpr unsigned int LINES_ADJACENCY          = LINE_NUMBER_OFFSET + __LINE__;
  static constexpr unsigned int PATCHES                  = LINE_NUMBER_OFFSET + __LINE__;
  static constexpr unsigned int POINTS                   = LINE_NUMBER_OFFSET + __LINE__;
  static constexpr unsigned int POLYGON                  = LINE_NUMBER_OFFSET + __LINE__;
  static constexpr unsigned int QUAD_STRIP               = LINE_NUMBER_OFFSET + __LINE__;
  static constexpr unsigned int QUADS                    = LINE_NUMBER_OFFSET + __LINE__;
  static constexpr unsigned int TRIANGLE_FAN             = LINE_NUMBER_OFFSET + __LINE__;
  static constexpr unsigned int TRIANGLE_STRIP           = LINE_NUMBER_OFFSET + __LINE__;
  static constexpr unsigned int TRIANGLE_STRIP_ADJACENCY = LINE_NUMBER_OFFSET + __LINE__;
  static constexpr unsigned int TRIANGLES                = LINE_NUMBER_OFFSET + __LINE__;
  static constexpr unsigned int TRIANGLES_ADJACENCY      = LINE_NUMBER_OFFSET + __LINE__;
  #undef LINE_NUMBER_OFFSET
};


} // namespace Constants
} // namespace GSG


#endif // _GSG_CONSTANTS_PRIMITIVE_MODES_H_
