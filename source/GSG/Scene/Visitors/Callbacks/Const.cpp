
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

#include "GSG/Scene/Visitors/Callbacks/Const.h"

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
  _transformCallback(),
  _groupCallback(),
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
}


///////////////////////////////////////////////////////////////////////////////
//
//  Visit the node.
//
///////////////////////////////////////////////////////////////////////////////

void Const::visit ( const GSG::Scene::Nodes::Groups::Transform &trans, PropertyMap &props )
{
  BaseClass::visit ( trans, props );
}
void Const::visit ( const GSG::Scene::Nodes::Groups::Group &group, PropertyMap &props )
{
  BaseClass::visit ( group, props );
}
void Const::visit ( const GSG::Scene::Nodes::Node &node, PropertyMap &props )
{
  BaseClass::visit ( node, props );
}
void Const::visit ( const GSG::Scene::Nodes::Shapes::Geometry &geom, PropertyMap &props )
{
  BaseClass::visit ( geom, props );
}
void Const::visit ( const GSG::Scene::Nodes::Shapes::Shape &shape, PropertyMap &props )
{
  BaseClass::visit ( shape, props );
}


} // namespace Callbacks
} // namespace Visitors
} // namespace Scene
} // namespace GSG
