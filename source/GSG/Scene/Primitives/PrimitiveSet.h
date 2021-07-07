
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2021, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Base class for all scene primitives.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _GSG_PRIMITIVES_PRIMITIVE_SET_CLASS_H_
#define _GSG_PRIMITIVES_PRIMITIVE_SET_CLASS_H_

#include "GSG/Config.h"

#include "GSG/Base/Objects/Object.h"

#include "GSG/Scene/Export.h"

#define GSG_DECLARE_PRIMITIVE_CLASS(class_name) \
  GSG_DECLARE_OBJECT_CLASS ( class_name )

#define GSG_IMPLEMENT_PRIMITIVE_CLASS(class_name) \
  GSG_IMPLEMENT_OBJECT_CLASS ( class_name )


namespace GSG {
namespace Scene {
namespace Primitives {


class GSG_SCENE_EXPORT PrimitiveSet : public GSG::Base::Objects::Object
{
public:

  typedef GSG::Base::Objects::Object BaseClass;

  GSG_DECLARE_PRIMITIVE_CLASS ( PrimitiveSet );

protected:

  PrimitiveSet();
  virtual ~PrimitiveSet();

private:

  void _destroyPrimitiveSet();
};


} // namespace Primitives
} // namespace Scene
} // namespace GSG


#endif // _GSG_PRIMITIVES_PRIMITIVE_SET_CLASS_H_
