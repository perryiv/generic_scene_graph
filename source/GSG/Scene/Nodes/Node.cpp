
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2020, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Base class for all scene-graph nodes.
//
///////////////////////////////////////////////////////////////////////////////

#include "GSG/Scene/Nodes/Node.h"
#include "GSG/Scene/Visitors/Visitor.h"

#include "Usul/Errors/Exceptions.h"
#include "Usul/Tools/NoThrow.h"

#include <atomic>
#include <functional>
#include <stdexcept>


namespace GSG {
namespace Scene {
namespace Nodes {


// Add the boilerplate code.
GSG_IMPLEMENT_NODE_CLASS ( Node );


///////////////////////////////////////////////////////////////////////////////
//
//  Get the next node id. This will also increment the internal counter.
//
///////////////////////////////////////////////////////////////////////////////

namespace Details
{
  std::atomic < unsigned long > _nextID ( 0 );
  unsigned long getNextID()
  {
    return ++_nextID;
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor.
//
///////////////////////////////////////////////////////////////////////////////

Node::Node() : BaseClass(),
  _mutex(),
  _id ( Details::getNextID() ),
  _flags ( VISIBLE | INTERSECTABLE | CONTRIBUTE_TO_BOUNDS ),
  _parents(),
  _bounds()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor.
//
///////////////////////////////////////////////////////////////////////////////

Node::~Node()
{
  USUL_TOOLS_NO_THROW ( 1591770752, std::bind ( &Node::_destroyNode, this ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destroy this instance.
//
///////////////////////////////////////////////////////////////////////////////

void Node::_destroyNode()
{
  if ( false == _parents.empty() )
  {
    throw Usul::Errors::RuntimeError ( "Destroying node with parents" );
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Does this node have the given parent?
//
///////////////////////////////////////////////////////////////////////////////

bool Node::hasParent ( const Parents::mapped_type &parent ) const
{
  // Handle invalid parent.
  if ( false == parent.valid() )
  {
    return false;
  }

  // Need to guard from here down.
  Guard guard ( _mutex );

  // Shortcut.
  const unsigned long id = parent->getID();

  // Returns true if the id is found.
  return ( _parents.end() != _parents.find ( id ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Add the parent.
//
///////////////////////////////////////////////////////////////////////////////

void Node::_addParent ( Node *node )
{
  // Wrap in a smart-pointer.
  Parents::mapped_type parent ( node );

  // Handle invalid parent.
  if ( false == parent.valid() )
  {
    throw Usul::Errors::RuntimeError ( "Adding invalid parent" );
  }

  // Guard before checking for an existing parent.
  Guard guard ( _mutex );

  // Make sure ...
  if ( true == this->hasParent ( parent ) )
  {
    throw Usul::Errors::RuntimeError ( "This node already has the given parent" );
  }

  // Shortcut.
  const unsigned long id = parent->getID();

  // Add the parent to our container.
  _parents[id] = parent;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Remove the parent.
//
///////////////////////////////////////////////////////////////////////////////

void Node::_removeParent ( Node *parent )
{
  // Handle invalid parent.
  if ( nullptr == parent )
  {
    return;
  }

  // Need to guard from here down.
  Guard guard ( _mutex );

  // Shortcut.
  const unsigned long id = parent->getID();

  // Remove the parent at the given id, if it exists.
  _parents.erase ( id );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Dirty the bounds.
//
///////////////////////////////////////////////////////////////////////////////

void Node::dirtyBounds()
{
  // Guard the from here down.
  Guard guard ( _mutex );

  // Set our bounds.
  _bounds = Bounds();

  // Invalidate the bounds of the parents.
  for ( Parents::iterator i = _parents.begin(); i != _parents.end(); ++i )
  {
    i->second->dirtyBounds();
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Set the bounds.
//
///////////////////////////////////////////////////////////////////////////////

void Node::_setBounds ( const Bounds &bounds )
{
  Guard guard ( _mutex );
  _bounds = bounds;
}


} // namespace Nodes
} // namespace Scene
} // namespace GSG
