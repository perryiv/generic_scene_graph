
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2021, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  The root of the tree that gets rendered.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _GSG_TOOLS_TREE_ROOT_CLASS_H_
#define _GSG_TOOLS_TREE_ROOT_CLASS_H_

#include "GSG/Config.h"
#include "GSG/Base/Objects/Object.h"
#include "GSG/Tools/Export.h"
#include "GSG/Tools/Tree/Layer.h"

#include <map>


namespace GSG {
namespace Tools {
namespace Tree {


class GSG_TOOLS_EXPORT Root : public GSG::Base::Objects::Object
{
public:

  GSG_DECLARE_OBJECT_CLASS ( Root );

  typedef GSG::Base::Objects::Object BaseClass;
  typedef std::map < int, Layer::ValidAccessRefPtr > Layers;

  // Constructor.
  Root();

  // Clear all the layers.
  void clear();

  // Get the layer. Make it if we have to.
  Layer *getLayer ( int );

protected:

  // Use reference counting.
  virtual ~Root();

private:

  void _destroyRoot();

  Layers _layers;
};


} // namespace Tree
} // namespace Tools
} // namespace GSG


#endif // _GSG_TOOLS_TREE_ROOT_CLASS_H_
