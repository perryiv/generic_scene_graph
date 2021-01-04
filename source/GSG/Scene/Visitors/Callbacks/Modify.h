
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2020, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Scene visitor that simply calls registered functions.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _GENERIC_SCENE_GRAPH_VISITORS_CALLBACKS_MODIFY_VISITOR_CLASS_H_
#define _GENERIC_SCENE_GRAPH_VISITORS_CALLBACKS_MODIFY_VISITOR_CLASS_H_

#include "GSG/Scene/Visitors/Visitor.h"

#include <functional>


namespace GSG {
namespace Scene {
namespace Visitors {
namespace Callbacks {


class GSG_EXPORT Modify : public GSG::Scene::Visitors::Visitor
{
public:

  GSG_DECLARE_VISITOR_CLASS ( Modify );

  typedef GSG::Scene::Visitors::Visitor BaseClass;
  typedef BaseClass::PropertyMap PropertyMap;

  typedef std::function < void ( GSG::Scene::Nodes::Groups::Transform &, PropertyMap & ) > TransformCallback;
  typedef std::function < void ( GSG::Scene::Nodes::Groups::Group &, PropertyMap & ) > GroupCallback;
  typedef std::function < void ( GSG::Scene::Nodes::Node &, PropertyMap & ) > NodeCallback;
  typedef std::function < void ( GSG::Scene::Nodes::Shapes::Geometry &, PropertyMap & ) > GeometryCallback;
  typedef std::function < void ( GSG::Scene::Nodes::Shapes::Shape &, PropertyMap & ) > ShapeCallback;

  Modify();

  virtual void visit ( GSG::Scene::Nodes::Groups::Transform &, PropertyMap & ) override;
  virtual void visit ( GSG::Scene::Nodes::Groups::Group &, PropertyMap & ) override;
  virtual void visit ( GSG::Scene::Nodes::Node &, PropertyMap & ) override;
  virtual void visit ( GSG::Scene::Nodes::Shapes::Geometry &, PropertyMap & ) override;
  virtual void visit ( GSG::Scene::Nodes::Shapes::Shape &, PropertyMap & ) override;

protected:

  virtual ~Modify();

private:

  void _destroyModify();

  TransformCallback _transformCallback;
  GroupCallback _groupCallback;
  GeometryCallback _geometryCallback;
  ShapeCallback _shapeCallback;
  NodeCallback _nodeCallback;
};


} // namespace Callbacks
} // namespace Visitors
} // namespace Scene
} // namespace GSG


#endif // _GENERIC_SCENE_GRAPH_VISITORS_CALLBACKS_MODIFY_VISITOR_CLASS_H_
