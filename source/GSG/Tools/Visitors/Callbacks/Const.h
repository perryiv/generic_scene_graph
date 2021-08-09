
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2021, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Scene visitor that simply calls registered functions.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _GSG_TOOLS_VISITORS_CALLBACKS_CONST_VISITOR_CLASS_H_
#define _GSG_TOOLS_VISITORS_CALLBACKS_CONST_VISITOR_CLASS_H_

#include "GSG/Config.h"
#include "GSG/Scene/Visitors/Visitor.h"
#include "GSG/Tools/Export.h"

#include <functional>


namespace GSG {
namespace Tools {
namespace Visitors {
namespace Callbacks {


class GSG_TOOLS_EXPORT Const : public GSG::Scene::Visitors::Visitor
{
public:

  GSG_DECLARE_VISITOR_CLASS ( Const );

  typedef GSG::Scene::Visitors::Visitor BaseClass;
  typedef BaseClass::PropertyMap PropertyMap;

  typedef std::function < void ( const GSG::Scene::Nodes::Groups::Transform &, PropertyMap & ) > TransformCallback;
  typedef std::function < void ( const GSG::Scene::Nodes::Groups::Group &,     PropertyMap & ) > GroupCallback;
  typedef std::function < void ( const GSG::Scene::Nodes::Node &,              PropertyMap & ) > NodeCallback;
  typedef std::function < void ( const GSG::Scene::Nodes::Shapes::Geometry &,  PropertyMap & ) > GeometryCallback;
  typedef std::function < void ( const GSG::Scene::Nodes::Shapes::Shape &,     PropertyMap & ) > ShapeCallback;

  Const();

  virtual void visit ( const GSG::Scene::Nodes::Groups::Transform &, PropertyMap & ) override;
  virtual void visit ( const GSG::Scene::Nodes::Groups::Group &,     PropertyMap & ) override;
  virtual void visit ( const GSG::Scene::Nodes::Node &,              PropertyMap & ) override;
  virtual void visit ( const GSG::Scene::Nodes::Shapes::Geometry &,  PropertyMap & ) override;
  virtual void visit ( const GSG::Scene::Nodes::Shapes::Shape &,     PropertyMap & ) override;

  enum When { BEFORE_TRAVERSAL, AFTER_TRAVERSAL };

  void setTransformCallback ( TransformCallback, When );
  void setGroupCallback     ( GroupCallback, When );
  void setGeometryCallback  ( GeometryCallback );
  void setShapeCallback     ( ShapeCallback );
  void setNodeCallback      ( NodeCallback );

protected:

  virtual ~Const();

private:

  void _destroyConst();

  TransformCallback _transformCallbackBefore;
  TransformCallback _transformCallbackAfter;
  GroupCallback _groupCallbackBefore;
  GroupCallback _groupCallbackAfter;
  GeometryCallback _geometryCallback;
  ShapeCallback _shapeCallback;
  NodeCallback _nodeCallback;
};


} // namespace Callbacks
} // namespace Visitors
} // namespace Tools
} // namespace GSG


#endif // _GSG_TOOLS_VISITORS_CALLBACKS_CONST_VISITOR_CLASS_H_
