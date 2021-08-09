
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2021, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Update visitor.
//
///////////////////////////////////////////////////////////////////////////////

#include "GSG/Tools/Visitors/Update/Visitor.h"
#include "GSG/Scene/Nodes/Shapes/Geometry.h"

#include "Usul/Tools/NoThrow.h"

#include <functional>


namespace GSG {
namespace Tools {
namespace Visitors {
namespace Update {


// Add the boilerplate code.
GSG_IMPLEMENT_VISITOR_CLASS ( Visitor )

// Shortcuts.
typedef GSG::Scene::Nodes::Groups::Group Group;
typedef GSG::Scene::Nodes::Groups::Transform Transform;
typedef GSG::Scene::Nodes::Shapes::Geometry Geometry;
typedef GSG::Scene::Nodes::Shapes::Shape Shape;
typedef GSG::Scene::Nodes::Node Node;


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
  USUL_TOOLS_NO_THROW ( 1628481406, std::bind ( &Visitor::_destroyVisitor, this ) );
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
//  Update the scene and build the render-tree.
//
///////////////////////////////////////////////////////////////////////////////

void Visitor::update ( Node *node, PropertyMap &pm )
{
  // Handle invalid node.
  if ( nullptr == node )
  {
    return;
  }

  // Traverse the scene.
  node->accept ( *this, pm );
}
void Visitor::update ( Node *node, PropertyMap::Values &values )
{
  PropertyMap pm ( values );
  this->update ( node, pm );
}
void Visitor::update ( Node *node )
{
  PropertyMap pm;
  this->update ( node, pm );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Visit the node.
//
///////////////////////////////////////////////////////////////////////////////

void Visitor::visit ( Transform &node, PropertyMap &pm )
{
  BaseClass::visit ( node, pm );
}
void Visitor::visit ( Group &node, PropertyMap &pm )
{
  BaseClass::visit ( node, pm );
}
void Visitor::visit ( Geometry &node, PropertyMap &pm )
{
  BaseClass::visit ( node, pm );
}
void Visitor::visit ( Shape &node, PropertyMap &pm )
{
  BaseClass::visit ( node, pm );
}
void Visitor::visit ( Node &node, PropertyMap &pm )
{
  BaseClass::visit ( node, pm );
}


} // namespace Update
} // namespace Visitors
} // namespace Tools
} // namespace GSG
