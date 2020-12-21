
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2020, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Base class for all scene-graph shape nodes.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _GENERIC_SCENE_GRAPH_NODES_SHAPES_SHAPE_CLASS_H_
#define _GENERIC_SCENE_GRAPH_NODES_SHAPES_SHAPE_CLASS_H_

#include "GSG/Scene/Nodes/Node.h"


namespace GSG {
namespace Scene {
namespace Nodes {
namespace Shapes {


class GSG_EXPORT Shape : public GSG::Scene::Nodes::Node
{
public:

  typedef GSG::Scene::Nodes::Node BaseClass;
  typedef BaseClass::Mutex Mutex;
  typedef BaseClass::Guard Guard;

  GSG_DECLARE_NODE_CLASS ( Shape );

  Shape();

protected:

  virtual ~Shape();

private:

  void _destroyShape();
};


} // namespace Shapes
} // namespace Nodes
} // namespace Scene
} // namespace GSG


#endif // _GENERIC_SCENE_GRAPH_NODES_SHAPES_SHAPE_CLASS_H_
