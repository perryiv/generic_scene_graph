
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

#include "GSG/Scene/Visitors/Callbacks/Const.h"
#include "GSG/Scene/Nodes/Groups/Transform.h"
#include "GSG/Scene/Nodes/Shapes/Geometry.h"

#include "Usul/Tools/NoThrow.h"

#include <functional>


namespace GSG {
namespace Scene {
namespace Visitors {
namespace Callbacks {


// Add the boilerplate code.
GSG_IMPLEMENT_VISITOR_CLASS ( Const )


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor.
//
///////////////////////////////////////////////////////////////////////////////

Const::Const() : BaseClass(),
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

Const::~Const()
{
  USUL_TOOLS_NO_THROW ( 1609779504, std::bind ( &Const::_destroyConst, this ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destroy this instance.
//
///////////////////////////////////////////////////////////////////////////////

void Const::_destroyConst()
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
  inline void call ( CallbackType cb, const NodeType &node, Const::PropertyMap &props )
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

void Const::visit ( const GSG::Scene::Nodes::Groups::Transform &trans, PropertyMap &props )
{
  Details::call ( _transformCallbackBefore, trans, props );
  BaseClass::visit ( trans, props );
  Details::call ( _transformCallbackAfter, trans, props );
}
void Const::visit ( const GSG::Scene::Nodes::Groups::Group &group, PropertyMap &props )
{
  Details::call ( _groupCallbackBefore, group, props );
  BaseClass::visit ( group, props );
  Details::call ( _groupCallbackAfter, group, props );
}
void Const::visit ( const GSG::Scene::Nodes::Shapes::Geometry &geom, PropertyMap &props )
{
  Details::call ( _geometryCallback, geom, props );
  BaseClass::visit ( geom, props );
}
void Const::visit ( const GSG::Scene::Nodes::Shapes::Shape &shape, PropertyMap &props )
{
  Details::call ( _shapeCallback, shape, props );
  BaseClass::visit ( shape, props );
}
void Const::visit ( const GSG::Scene::Nodes::Node &node, PropertyMap &props )
{
  Details::call ( _nodeCallback, node, props );
  BaseClass::visit ( node, props );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Set the callbacks.
//
///////////////////////////////////////////////////////////////////////////////

void Const::setTransformCallback ( TransformCallback cb, When when )
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
void Const::setGroupCallback ( GroupCallback cb, When when )
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
void Const::setGeometryCallback ( GeometryCallback cb )
{
  _geometryCallback = cb;
}
void Const::setShapeCallback ( ShapeCallback cb )
{
  _shapeCallback = cb;
}
void Const::setNodeCallback ( NodeCallback cb )
{
  _nodeCallback = cb;
}


} // namespace Callbacks
} // namespace Visitors
} // namespace Scene
} // namespace GSG
