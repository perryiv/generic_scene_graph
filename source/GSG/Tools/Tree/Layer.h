
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2021, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  A layer in the render-tree.
//  The depth buffer should be cleared before rendering its children.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _GSG_TOOLS_TREE_LAYER_CLASS_H_
#define _GSG_TOOLS_TREE_LAYER_CLASS_H_

#include "GSG/Config.h"
#include "GSG/Base/Objects/Object.h"
#include "GSG/Tools/Export.h"


namespace GSG {
namespace Tools {
namespace Tree {


class GSG_TOOLS_EXPORT Layer : public GSG::Base::Objects::Object
{
public:

  GSG_DECLARE_OBJECT_CLASS ( Layer );

  typedef GSG::Base::Objects::Object BaseClass;

  // Constructor.
  Layer();

protected:

  // Use reference counting.
  virtual ~Layer();

private:

  void _destroyLayer();
};


} // namespace Tree
} // namespace Tools
} // namespace GSG


#endif // _GSG_TOOLS_TREE_LAYER_CLASS_H_
