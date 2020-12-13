
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

#include <functional>


namespace GSG {
namespace Scene {
namespace Nodes {
namespace Groups {


// Add the boilerplate code.
GSG_IMPLEMENT_NODE_CLASS ( Group );


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
  this->clear();
}


///////////////////////////////////////////////////////////////////////////////
//
//  Remove all the child nodes.
//
///////////////////////////////////////////////////////////////////////////////

void Group::removeAllChildren()
{
  Children children;
  {
    Guard guard ( this->mutex() );
    children = _children;
    _children.clear();
  }

  for ( auto i = children.begin(); i != children.end(); ++i )
  {
    NodePtr &child = *i;
    child->_removeParent ( this );
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Add the node to the end of the sequence.
//
///////////////////////////////////////////////////////////////////////////////

void Group::push_back ( NodePtr node )
{
  if ( true == node.valid() )
  {
    #if 0
    #ifdef _DEBUG
    std::cout << "child node = " << node->getReferenceCount() << ", this = " << this->getReferenceCount() << std::endl;
    #endif
    #endif

    Guard guard ( this->mutex() );
    _children.push_back ( node );
    node->_addParent ( this );
  }
}


} // namespace Groups
} // namespace Nodes
} // namespace Scene
} // namespace GSG