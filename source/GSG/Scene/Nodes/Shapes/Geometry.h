
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2020, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Shape node based on vertex buffers.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _GENERIC_SCENE_GRAPH_NODES_SHAPES_GEOMETRY_CLASS_H_
#define _GENERIC_SCENE_GRAPH_NODES_SHAPES_GEOMETRY_CLASS_H_

#include "GSG/Scene/Nodes/Shapes/Shape.h"


namespace GSG {
namespace Scene {
namespace Nodes {
namespace Shapes {


class GSG_EXPORT Geometry : public GSG::Scene::Nodes::Shapes::Shape
{
public:

  typedef GSG::Scene::Nodes::Shapes::Shape BaseClass;
  typedef BaseClass::Mutex Mutex;
  typedef BaseClass::Guard Guard;

  GSG_DECLARE_NODE_CLASS ( Geometry );

  // Constructor
  Geometry();

protected:

  virtual ~Geometry();

private:

  void _destroyGeometry();
};


} // namespace Shapes
} // namespace Nodes
} // namespace Scene
} // namespace GSG


#endif // _GENERIC_SCENE_GRAPH_NODES_SHAPES_GEOMETRY_CLASS_H_
