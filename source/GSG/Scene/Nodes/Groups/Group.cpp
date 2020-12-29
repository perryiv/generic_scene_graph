
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2020, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Base class for all scene-graph group nodes.
//
///////////////////////////////////////////////////////////////////////////////

#include "GSG/Scene/Nodes/Groups/Group.h"
#include "GSG/Scene/Visitors/Visitor.h"

#include "Usul/Tools/NoThrow.h"

#include <immer/flex_vector.hpp>

#include <functional>
#include <type_traits>


namespace GSG {
namespace Scene {
namespace Nodes {
namespace Groups {


// Add the boilerplate code.
GSG_IMPLEMENT_NODE_CLASS ( Group );


///////////////////////////////////////////////////////////////////////////////
//
//  Shortcuts.
//
///////////////////////////////////////////////////////////////////////////////

typedef Group::NodePtr NodePtr;
typedef immer::flex_vector < NodePtr > FlexVector;


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor.
//
///////////////////////////////////////////////////////////////////////////////

Group::Group() : BaseClass(),
  _children()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor.
//
///////////////////////////////////////////////////////////////////////////////

Group::~Group()
{
  USUL_TOOLS_NO_THROW ( 1591773842, std::bind ( &Group::_destroyGroup, this ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destroy this instance.
//
///////////////////////////////////////////////////////////////////////////////

void Group::_destroyGroup()
{
  this->removeAll();
}


///////////////////////////////////////////////////////////////////////////////
//
//  Have the visitor traverse the children.
//
///////////////////////////////////////////////////////////////////////////////

void Group::_traverseConst ( GSG::Scene::Visitors::Visitor &visitor, PropertyMap &pm ) const
{
  // Guard making a copy of the children.
  Children children;
  {
    Guard guard ( this->mutex() );
    children = _children;
  }

  // Loop through the copy of children.
  for ( auto i = children.begin(); i != children.end(); ++i )
  {
    (*i)->accept ( visitor, pm );
  }
}
void Group::_traverseModify ( GSG::Scene::Visitors::Visitor &visitor, PropertyMap &pm )
{
  // Guard making a copy of the children.
  Children children;
  {
    Guard guard ( this->mutex() );
    children = _children;
  }

  // Loop through the copy of children.
  for ( auto i = children.begin(); i != children.end(); ++i )
  {
    NodePtr child = *i;
    child->accept ( visitor, pm );
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Remove all the child nodes.
//
///////////////////////////////////////////////////////////////////////////////

void Group::removeAll()
{
  // Guard making a copy of the children.
  Children children;
  {
    Guard guard ( this->mutex() );
    children = _children;
    _children = Children(); // We're done with this.
  }

  // Loop through the copy of children and remove us as a parent.
  for ( auto i = children.begin(); i != children.end(); ++i )
  {
    NodePtr child = *i;
    child->_removeParent ( this );
  }

  // Unless we were already empty, our bounds is now invalid.
  if ( false == children.empty() )
  {
    this->dirtyBounds();
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Access the child. Throws an exception if the index is out of range.
//
///////////////////////////////////////////////////////////////////////////////

const NodePtr Group::at ( size_type index ) const
{
  Guard guard ( this->mutex() );
  return _children.at ( index );
}
NodePtr Group::at ( size_type index )
{
  Guard guard ( this->mutex() );
  return _children.at ( index );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the size of the group, which is the number of child nodes.
//
///////////////////////////////////////////////////////////////////////////////

Group::size_type Group::size() const
{
  Guard guard ( this->mutex() );
  return _children.size();
}


///////////////////////////////////////////////////////////////////////////////
//
//  Is the group empty?
//
///////////////////////////////////////////////////////////////////////////////

bool Group::empty() const
{
  Guard guard ( this->mutex() );
  return _children.empty();
}


///////////////////////////////////////////////////////////////////////////////
//
//  Insert the node before the given position.
//
///////////////////////////////////////////////////////////////////////////////

void Group::insert ( size_type pos, NodePtr node )
{
  static_assert ( ( true == ( std::is_integral < size_type > ::value ) ), "Size type is not an integer" );
  static_assert ( ( true == ( std::is_unsigned < size_type > ::value ) ), "Size type is not unsigned" );

  // Handle invalid node.
  if ( false == node.valid() )
  {
    return;
  }

  // Handle position out of range.
  if ( pos >= this->size() )
  {
    this->append ( node );
    return;
  }

  // If we get to here then insert the node.
  Guard guard ( this->mutex() );

  // We have to convert to a flex-vector, insert, and convert back.
  FlexVector children ( _children );
  children = children.insert ( pos, node );
  _children = Children ( children.begin(), children.end() );

  // Add this instance to the node's set of parents.
  node->_addParent ( this );

  // Our bounds is now invalid.
  this->dirtyBounds();
}


///////////////////////////////////////////////////////////////////////////////
//
//  Append the node to the end of the sequence.
//
///////////////////////////////////////////////////////////////////////////////

void Group::append ( NodePtr node )
{
  // Handle invalid node.
  if ( false == node.valid() )
  {
    return;
  }

  // If we get to here then append the node.
  Guard guard ( this->mutex() );

  // We have to convert to a flex-vector, push, and convert back.
  FlexVector children ( _children );
  children = children.push_back ( node );
  _children = Children ( children.begin(), children.end() );

  // Add this instance to the node's set of parents.
  node->_addParent ( this );

  // Our bounds is now invalid.
  this->dirtyBounds();
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the bound.
//
///////////////////////////////////////////////////////////////////////////////

Group::Bounds Group::getBounds() const
{
  // For now, guard the whole thing. Optimize later.
  Guard guard ( this->mutex() );

  // Are we supposed to contribute to the bounds?
  if ( false == this->getContributeToBounds() )
  {
    return Bounds(); // Return an invalid bounds.
  }

  // Shortcuts.
  Bounds &bounds = this->_getBounds();

  // If the bounds is valid then return it.
  if ( true == bounds.valid() )
  {
    return bounds;
  }

  // Loop through the copy of the children and grow the bounds.
  for ( auto i = _children.begin(); i != _children.end(); ++i )
  {
    // TODO: Do we need to make sure it is valid?
    bounds.grow ( (*i)->getBounds() );
  }

  // Return what we have.
  return bounds;
}


} // namespace Groups
} // namespace Nodes
} // namespace Scene
} // namespace GSG
