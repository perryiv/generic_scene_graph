
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2020, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Base class for all reference-counted objects.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _GENERIC_SCENE_GRAPH_BASE_OBJECTS_OBJECT_CLASS_H_
#define _GENERIC_SCENE_GRAPH_BASE_OBJECTS_OBJECT_CLASS_H_

#include "GSG/Config.h"
#include "GSG/Export.h"

#include "Usul/Base/Referenced.h"
#include "Usul/Pointers/Pointers.h"
#include "Usul/Tools/NoCopying.h"

#define GSG_DECLARE_OBJECT_CLASS(class_name) \
  USUL_REFERENCED_CLASS ( class_name ); \
  typedef ValidAccessRefPtr Ptr

#define GSG_IMPLEMENT_OBJECT_CLASS(class_name)


namespace GSG {
namespace Base {
namespace Objects {


class GSG_EXPORT Object : public Usul::Base::Referenced,
  public Usul::Tools::NoCopying
{
public:

  GSG_DECLARE_OBJECT_CLASS ( Object );

  typedef Usul::Base::Referenced BaseClass;

protected:

  Object();
  virtual ~Object();

private:

  void _destroyObject();
};


} // namespace Objects
} // namespace Base
} // namespace GSG


#endif // _GENERIC_SCENE_GRAPH_BASE_OBJECTS_OBJECT_CLASS_H_
