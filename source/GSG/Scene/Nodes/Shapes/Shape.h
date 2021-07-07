
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2021, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Base class for all scene-graph shape nodes.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _GSG_NODES_SHAPES_SHAPE_CLASS_H_
#define _GSG_NODES_SHAPES_SHAPE_CLASS_H_

#include "GSG/Scene/Nodes/Node.h"


namespace GSG {
namespace Scene {
namespace Nodes {
namespace Shapes {


class GSG_SCENE_EXPORT Shape : public GSG::Scene::Nodes::Node
{
public:

  typedef GSG::Scene::Nodes::Node BaseClass;
  typedef BaseClass::Mutex Mutex;
  typedef BaseClass::Guard Guard;

  GSG_DECLARE_NODE_CLASS ( Shape );

protected:

  Shape();
  virtual ~Shape();

private:

  void _destroyShape();
};


} // namespace Shapes
} // namespace Nodes
} // namespace Scene
} // namespace GSG


#endif // _GSG_NODES_SHAPES_SHAPE_CLASS_H_
