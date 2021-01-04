
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
}


///////////////////////////////////////////////////////////////////////////////
//
//  Visit the node.
//
///////////////////////////////////////////////////////////////////////////////

void Modify::visit ( GSG::Scene::Nodes::Groups::Transform &trans, PropertyMap &props )
{
  BaseClass::visit ( trans, props );
}
void Modify::visit ( GSG::Scene::Nodes::Groups::Group &group, PropertyMap &props )
{
  BaseClass::visit ( group, props );
}
void Modify::visit ( GSG::Scene::Nodes::Shapes::Geometry &geom, PropertyMap &props )
{
  BaseClass::visit ( geom, props );
}
void Modify::visit ( GSG::Scene::Nodes::Shapes::Shape &shape, PropertyMap &props )
{
  BaseClass::visit ( shape, props );
}
void Modify::visit ( GSG::Scene::Nodes::Node &node, PropertyMap &props )
{
  BaseClass::visit ( node, props );
}


} // namespace Callbacks
} // namespace Visitors
} // namespace Scene
} // namespace GSG
