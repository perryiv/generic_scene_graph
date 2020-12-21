
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2020, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Base class for all scene visitors.
//
///////////////////////////////////////////////////////////////////////////////

#include "GSG/Scene/Visitors/Visitor.h"
#include "GSG/Scene/Nodes/Groups/Group.h"

#include "Usul/Tools/NoThrow.h"

#include <functional>


namespace GSG {
namespace Scene {
namespace Visitors {


// Add the boilerplate code.
GSG_IMPLEMENT_VISITOR_CLASS ( Visitor );


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor.
//
///////////////////////////////////////////////////////////////////////////////

Visitor::Visitor() : BaseClass()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor.
//
///////////////////////////////////////////////////////////////////////////////

Visitor::~Visitor()
{
  USUL_TOOLS_NO_THROW ( 1592287229, std::bind ( &Visitor::_destroyVisitor, this ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destroy this instance.
//
///////////////////////////////////////////////////////////////////////////////

void Visitor::_destroyVisitor()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Visit the node.
//
///////////////////////////////////////////////////////////////////////////////

void Visitor::visit ( const GSG::Scene::Nodes::Groups::Group &group, PropertyMap &pm )
{
  group._traverseConst ( *this, pm );
}
void Visitor::visit ( GSG::Scene::Nodes::Groups::Group &group, PropertyMap &pm )
{
  group._traverseModify ( *this, pm );
}
void Visitor::visit ( const GSG::Scene::Nodes::Node &, PropertyMap & )
{
}
void Visitor::visit ( GSG::Scene::Nodes::Node &, PropertyMap & )
{
}
void Visitor::visit ( const GSG::Scene::Nodes::Shapes::Geometry &, PropertyMap & )
{
}
void Visitor::visit ( GSG::Scene::Nodes::Shapes::Geometry &, PropertyMap & )
{
}
void Visitor::visit ( const GSG::Scene::Nodes::Shapes::Shape &, PropertyMap & )
{
}
void Visitor::visit ( GSG::Scene::Nodes::Shapes::Shape &, PropertyMap & )
{
}


} // namespace Visitors
} // namespace Scene
} // namespace GSG
