
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2021, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Cull visitor.
//
///////////////////////////////////////////////////////////////////////////////

#include "GSG/Tools/Visitors/Cull/Visitor.h"
#include "GSG/Scene/Nodes/Shapes/Geometry.h"

#include "Usul/Tools/NoThrow.h"

#include <functional>


namespace GSG {
namespace Tools {
namespace Visitors {
namespace Cull {


// Add the boilerplate code.
GSG_IMPLEMENT_VISITOR_CLASS ( Visitor )

// Shortcuts.
typedef GSG::Scene::Nodes::Groups::Group Group;
typedef GSG::Scene::Nodes::Groups::Transform Transform;
typedef GSG::Scene::Nodes::Shapes::Geometry Geometry;
typedef GSG::Scene::Nodes::Shapes::Shape Shape;
typedef GSG::Scene::Nodes::Node Node;
typedef GSG::Tools::Tree::Layer Layer;


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor.
//
///////////////////////////////////////////////////////////////////////////////

Visitor::Visitor() : BaseClass(),
  _root()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor.
//
///////////////////////////////////////////////////////////////////////////////

Visitor::~Visitor()
{
  USUL_TOOLS_NO_THROW ( 1626067463, std::bind ( &Visitor::_destroyVisitor, this ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destroy this instance.
//
///////////////////////////////////////////////////////////////////////////////

void Visitor::_destroyVisitor()
{
  _root = nullptr;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Cull the scene and build the render-tree.
//
///////////////////////////////////////////////////////////////////////////////

void Visitor::cull ( Node *node, PropertyMap &pm )
{
  // Handle invalid node.
  if ( nullptr == node )
  {
    return;
  }

  // Make sure we have a root.
  if ( false == _root.valid() )
  {
    _root = new Root;
  }

  // Make sure the root is empty.
  _root->clear();

  // Traverse the scene.
  node->accept ( *this, pm );
}
void Visitor::cull ( Node *node, PropertyMap::Values &values )
{
  PropertyMap pm ( values );
  this->cull ( node, pm );
}
void Visitor::cull ( Node *node )
{
  PropertyMap pm;
  this->cull ( node, pm );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Process the shape node.
//
///////////////////////////////////////////////////////////////////////////////

namespace Details
{
  inline void processShape ( Shape &shape, Visitor::PropertyMap &, Visitor::Root &root )
  {
    // Layer &layer =
    root.getLayer ( shape.getLayer() );
  }
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
  Details::processShape ( node, pm, *_root );
  BaseClass::visit ( node, pm );
}
void Visitor::visit ( Shape &node, PropertyMap &pm )
{
  Details::processShape ( node, pm, *_root );
  BaseClass::visit ( node, pm );
}
void Visitor::visit ( Node &node, PropertyMap &pm )
{
  BaseClass::visit ( node, pm );
}


} // namespace Cull
} // namespace Visitors
} // namespace Tools
} // namespace GSG
