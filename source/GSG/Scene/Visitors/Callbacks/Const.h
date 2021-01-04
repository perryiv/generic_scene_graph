
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

#ifndef _GENERIC_SCENE_GRAPH_VISITORS_CALLBACKS_CONST_VISITOR_CLASS_H_
#define _GENERIC_SCENE_GRAPH_VISITORS_CALLBACKS_CONST_VISITOR_CLASS_H_

#include "GSG/Scene/Visitors/Visitor.h"

#include <functional>


namespace GSG {
namespace Scene {
namespace Visitors {
namespace Callbacks {


class GSG_EXPORT Const : public GSG::Scene::Visitors::Visitor
{
public:

  GSG_DECLARE_VISITOR_CLASS ( Const );

  typedef GSG::Scene::Visitors::Visitor BaseClass;
  typedef BaseClass::PropertyMap PropertyMap;

  typedef std::function < void ( const GSG::Scene::Nodes::Groups::Transform &, PropertyMap & ) > TransformCallback;
  typedef std::function < void ( const GSG::Scene::Nodes::Groups::Group &, PropertyMap & ) > GroupCallback;
  typedef std::function < void ( const GSG::Scene::Nodes::Node &, PropertyMap & ) > NodeCallback;
  typedef std::function < void ( const GSG::Scene::Nodes::Shapes::Geometry &, PropertyMap & ) > GeometryCallback;
  typedef std::function < void ( const GSG::Scene::Nodes::Shapes::Shape &, PropertyMap & ) > ShapeCallback;

  Const();

  virtual void visit ( const GSG::Scene::Nodes::Groups::Transform &, PropertyMap & ) override;
  virtual void visit ( const GSG::Scene::Nodes::Groups::Group &, PropertyMap & ) override;
  virtual void visit ( const GSG::Scene::Nodes::Node &, PropertyMap & ) override;
  virtual void visit ( const GSG::Scene::Nodes::Shapes::Geometry &, PropertyMap & ) override;
  virtual void visit ( const GSG::Scene::Nodes::Shapes::Shape &, PropertyMap & ) override;

protected:

  virtual ~Const();

private:

  void _destroyConst();

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


#endif // _GENERIC_SCENE_GRAPH_VISITORS_CALLBACKS_CONST_VISITOR_CLASS_H_
