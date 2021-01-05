
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

#include "GSG/Scene/Visitors/Callbacks/Modify.h"
#include "GSG/Scene/Nodes/Groups/Transform.h"
#include "GSG/Scene/Nodes/Shapes/Geometry.h"

#include "Usul/Tools/NoThrow.h"

#include <functional>


namespace GSG {
namespace Scene {
namespace Visitors {
namespace Callbacks {


// Add the boilerplate code.
GSG_IMPLEMENT_VISITOR_CLASS ( Modify )


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor.
//
///////////////////////////////////////////////////////////////////////////////

Modify::Modify() : BaseClass(),
  _transformCallbackBefore(),
  _transformCallbackAfter(),
  _groupCallbackBefore(),
  _groupCallbackAfter(),
  _geometryCallback(),
  _shapeCallback(),
  _nodeCallback()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor.
//
///////////////////////////////////////////////////////////////////////////////

Modify::~Modify()
{
  USUL_TOOLS_NO_THROW ( 1609779503, std::bind ( &Modify::_destroyModify, this ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destroy this instance.
//
///////////////////////////////////////////////////////////////////////////////

void Modify::_destroyModify()
{
  _transformCallbackBefore = nullptr;
  _transformCallbackAfter = nullptr;
  _groupCallbackBefore = nullptr;
  _groupCallbackAfter = nullptr;
  _geometryCallback = nullptr;
  _shapeCallback = nullptr;
  _nodeCallback = nullptr;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Call the function if it is valid.
//
///////////////////////////////////////////////////////////////////////////////

namespace Details
{
  template < class CallbackType, class NodeType >
  inline void call ( CallbackType cb, NodeType &node, Modify::PropertyMap &props )
  {
    if ( cb )
    {
      cb ( node, props );
    }
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Visit the node.
//
///////////////////////////////////////////////////////////////////////////////

void Modify::visit ( GSG::Scene::Nodes::Groups::Transform &trans, PropertyMap &props )
{
  Details::call ( _transformCallbackBefore, trans, props );
  BaseClass::visit ( trans, props );
  Details::call ( _transformCallbackAfter, trans, props );
}
void Modify::visit ( GSG::Scene::Nodes::Groups::Group &group, PropertyMap &props )
{
  Details::call ( _groupCallbackBefore, group, props );
  BaseClass::visit ( group, props );
  Details::call ( _groupCallbackAfter, group, props );
}
void Modify::visit ( GSG::Scene::Nodes::Shapes::Geometry &geom, PropertyMap &props )
{
  Details::call ( _geometryCallback, geom, props );
  BaseClass::visit ( geom, props );
}
void Modify::visit ( GSG::Scene::Nodes::Shapes::Shape &shape, PropertyMap &props )
{
  Details::call ( _shapeCallback, shape, props );
  BaseClass::visit ( shape, props );
}
void Modify::visit ( GSG::Scene::Nodes::Node &node, PropertyMap &props )
{
  Details::call ( _nodeCallback, node, props );
  BaseClass::visit ( node, props );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Set the callbacks.
//
///////////////////////////////////////////////////////////////////////////////

void Modify::setTransformCallback ( TransformCallback cb, When when )
{
  if ( BEFORE_TRAVERSAL == when )
  {
    _transformCallbackBefore = cb;
  }
  else if ( AFTER_TRAVERSAL == when )
  {
    _transformCallbackAfter = cb;
  }
}
void Modify::setGroupCallback ( GroupCallback cb, When when )
{
  if ( BEFORE_TRAVERSAL == when )
  {
    _groupCallbackBefore = cb;
  }
  else if ( AFTER_TRAVERSAL == when )
  {
    _groupCallbackAfter = cb;
  }
}
void Modify::setGeometryCallback ( GeometryCallback cb )
{
  _geometryCallback = cb;
}
void Modify::setShapeCallback ( ShapeCallback cb )
{
  _shapeCallback = cb;
}
void Modify::setNodeCallback ( NodeCallback cb )
{
  _nodeCallback = cb;
}


} // namespace Callbacks
} // namespace Visitors
} // namespace Scene
} // namespace GSG
