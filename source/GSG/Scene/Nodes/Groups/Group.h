
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2021, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Base class for all scene-graph group nodes.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _GSG_NODES_GROUPS_GROUP_CLASS_H_
#define _GSG_NODES_GROUPS_GROUP_CLASS_H_

#include "GSG/Scene/Nodes/Node.h"

#include <immer/vector.hpp>


namespace GSG {
namespace Scene {
namespace Nodes {
namespace Groups {


class GSG_SCENE_EXPORT Group : public GSG::Scene::Nodes::Node
{
public:

  typedef GSG::Scene::Nodes::Node Node;
  typedef Node BaseClass;
  typedef BaseClass::Mutex Mutex;
  typedef BaseClass::Guard Guard;
  typedef BaseClass::Bounds Bounds;
  typedef Node::ValidAccessRefPtr NodePtr;
  typedef immer::vector < NodePtr > Children;
  typedef Children::size_type size_type;

  GSG_DECLARE_NODE_CLASS ( Group );

  // Constructor
  Group();

  // Append or insert the child node before the given position.
  void append ( NodePtr child );
  template< class Itr >
  void insert ( size_type pos, Itr first, Itr last);
  void insert ( size_type pos, NodePtr );

  // Access the child. Throws an exception if the index is out of range.
  const NodePtr at ( size_type ) const;
  NodePtr       at ( size_type );

  // Is the group empty?
  bool empty() const;

  // Get the bounds.
  virtual Bounds getBounds() const override;

  // Get the children.
  Children getChildren();

  // Access the child.
  const NodePtr operator[] ( size_type index ) const { return this->at ( index ); }
  NodePtr       operator[] ( size_type index )       { return this->at ( index ); }

  // Remove the given child node, or all the child nodes.
  void removeAll();
  void remove ( size_type pos );
  void remove ( NodePtr child );

  // Get the size of the group, which is the number of child nodes.
  size_type size() const;

protected:

  friend class GSG::Scene::Visitors::Visitor;

  virtual ~Group();

  // Have the visitor traverse the children.
  virtual void _traverseConst  ( GSG::Scene::Visitors::Visitor &, PropertyMap & ) const;
  virtual void _traverseModify ( GSG::Scene::Visitors::Visitor &, PropertyMap & );

private:

  void _destroyGroup();

  Children _children;
};


///////////////////////////////////////////////////////////////////////////////
//
//  Insert the node before the given position.
//
///////////////////////////////////////////////////////////////////////////////

template< class Itr >
void Group::insert ( size_type pos, Itr first, Itr last)
{
  for ( auto i = first; i != last; ++i )
  {
    this->insert ( pos++, *i );
  }
}


} // namespace Groups
} // namespace Nodes
} // namespace Scene
} // namespace GSG


#endif // _GSG_NODES_GROUPS_GROUP_CLASS_H_
