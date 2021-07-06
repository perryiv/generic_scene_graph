
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

#ifndef _GSG_BASE_OBJECTS_OBJECT_CLASS_H_
#define _GSG_BASE_OBJECTS_OBJECT_CLASS_H_

#include "GSG/Config.h"
#include "GSG/Base/Export.h"

#include "Usul/Base/Referenced.h"
#include "Usul/Pointers/Pointers.h"
#include "Usul/Tools/NoCopying.h"

#include <string>

#define GSG_DECLARE_OBJECT_CLASS_BASE(class_name) \
  USUL_REFERENCED_CLASS ( class_name ); \
  typedef ValidAccessRefPtr Ptr; \
  static std::string className(); \
  virtual std::string getClassName()

#define GSG_DECLARE_OBJECT_CLASS(class_name) \
  GSG_DECLARE_OBJECT_CLASS_BASE ( class_name ) override \

#define GSG_IMPLEMENT_OBJECT_CLASS(class_name) \
  std::string class_name::className() { return std::string ( #class_name ); } \
  std::string class_name::getClassName() { return class_name::className(); }


namespace GSG {
namespace Base {
namespace Objects {


class GSG_BASE_EXPORT Object : public Usul::Base::Referenced,
  public Usul::Tools::NoCopying
{
public:

  GSG_DECLARE_OBJECT_CLASS_BASE ( Object );

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


#endif // _GSG_BASE_OBJECTS_OBJECT_CLASS_H_
