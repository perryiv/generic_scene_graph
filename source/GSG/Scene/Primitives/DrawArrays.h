
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2020, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Primitive set that draws the arrays.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _GENERIC_SCENE_GRAPH_PRIMITIVES_DRAW_ARRAYS_CLASS_H_
#define _GENERIC_SCENE_GRAPH_PRIMITIVES_DRAW_ARRAYS_CLASS_H_

#include "GSG/Scene/Primitives/PrimitiveSet.h"


namespace GSG {
namespace Scene {
namespace Primitives {


class GSG_EXPORT DrawArrays : public PrimitiveSet
{
public:

  typedef PrimitiveSet BaseClass;

  GSG_DECLARE_PRIMITIVE_CLASS ( DrawArrays );

  DrawArrays();

protected:

  virtual ~DrawArrays();

private:

  void _destroyDrawArrays();
};


} // namespace Primitives
} // namespace Scene
} // namespace GSG


#endif // _GENERIC_SCENE_GRAPH_PRIMITIVES_DRAW_ARRAYS_CLASS_H_
