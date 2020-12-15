
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
#include "GSG/Visitors/Visitor.h"

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
  this->removeAllChildren();
}


///////////////////////////////////////////////////////////////////////////////
//
//  Remove all the child nodes.
//
///////////////////////////////////////////////////////////////////////////////

void Group::removeAllChildren()
{
  // Guard making a copy of the sequence.
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
//  Get the first node. Throws an exception if the group is empty.
//
///////////////////////////////////////////////////////////////////////////////

const NodePtr Group::front() const
{
  Guard guard ( this->mutex() );
  return _children.front();
}
NodePtr Group::front()
{
  Guard guard ( this->mutex() );
  return _children.front();
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the last node. Throws an exception if the group is empty.
//
///////////////////////////////////////////////////////////////////////////////

const NodePtr Group::back() const
{
  Guard guard ( this->mutex() );
  return _children.back();
}
NodePtr Group::back()
{
  Guard guard ( this->mutex() );
  return _children.back();
}


///////////////////////////////////////////////////////////////////////////////
//
//  Iterators. Use with caution in a multi-threaded environment.
//
///////////////////////////////////////////////////////////////////////////////

Group::const_iterator Group::begin() const
{
  Guard guard ( this->mutex() );
  return _children.begin();
}
Group::iterator Group::begin()
{
  Guard guard ( this->mutex() );
  return _children.begin();
}
Group::const_iterator Group::end() const
{
  Guard guard ( this->mutex() );
  return _children.end();
}
Group::iterator Group::end()
{
  Guard guard ( this->mutex() );
  return _children.end();
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
    this->push_back ( node );
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
}


///////////////////////////////////////////////////////////////////////////////
//
//  Add the node to the end of the sequence.
//
///////////////////////////////////////////////////////////////////////////////

void Group::push_back ( NodePtr node )
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
}


///////////////////////////////////////////////////////////////////////////////
//
//  Add the node to the beginning of the sequence.
//
///////////////////////////////////////////////////////////////////////////////

void Group::push_front ( NodePtr node )
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
  children = children.push_front ( node );
  _children = Children ( children.begin(), children.end() );

  // Add this instance to the node's set of parents.
  node->_addParent ( this );
}


} // namespace Groups
} // namespace Nodes
} // namespace Scene
} // namespace GSG
