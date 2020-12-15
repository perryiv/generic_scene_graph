
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

#ifndef _GENERIC_SCENE_GRAPH_NODES_GROUPS_GROUP_CLASS_H_
#define _GENERIC_SCENE_GRAPH_NODES_GROUPS_GROUP_CLASS_H_

#include "GSG/Scene/Nodes/Node.h"

#include <immer/vector.hpp>


namespace GSG {
namespace Scene {
namespace Nodes {
namespace Groups {


class GSG_EXPORT Group : public GSG::Scene::Nodes::Node
{
public:

  typedef GSG::Scene::Nodes::Node Node;
  typedef Node BaseClass;
  typedef BaseClass::Mutex Mutex;
  typedef BaseClass::Guard Guard;
  typedef Node::ValidAccessRefPtr NodePtr;
  typedef immer::vector < NodePtr > Children;
  typedef Children::const_iterator const_iterator;
  typedef Children::iterator iterator;
  typedef Children::size_type size_type;

  GSG_DECLARE_NODE_CLASS ( Group );

  // Constructor
  Group();

  // Add the child node.
  void addChild ( NodePtr child ) { this->push_back ( child ); }

  // Access the child. Throws an exception if the index is out of range.
  const NodePtr at ( size_type ) const;
  NodePtr       at ( size_type );

  // Get the last node. Throws an exception if the group is empty.
  const NodePtr back() const;
  NodePtr       back();

  // Iterators. Use with caution in a multi-threaded environment.
  const_iterator begin() const;
  iterator       begin();
  const_iterator end() const;
  iterator       end();

  // Clear the group.
  void clear() { this->removeAllChildren(); }

  // Is the group empty?
  bool empty() const;

  // Get the first node. Throws an exception if the group is empty.
  const NodePtr front() const;
  NodePtr       front();

  // Get the number of child nodes.
  size_type getNumChildren() const { return this->size(); }

  // Insert the node before the given position iterator.
  template< class Itr >
  void insert ( size_type pos, Itr first, Itr last);
  void insert ( size_type pos, NodePtr );

  // Access the child.
  const NodePtr operator[] ( size_type index ) const { return this->at ( index ); }
  NodePtr       operator[] ( size_type index )       { return this->at ( index ); }

  // Add the node to the end or beginning of the sequence.
  void push_back  ( NodePtr );
  void push_front ( NodePtr );

  // Remove all the child nodes.
  void removeAllChildren();

  // Get the size of the group, which is the number of child nodes.
  size_type size() const;

protected:

  friend class GSG::Visitors::Visitor;

  virtual ~Group();

  // Have the visitor traverse the children.
  void _traverseConst ( GSG::Visitors::Visitor & ) const;
  void _traverseModify ( GSG::Visitors::Visitor & );

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


#endif // _GENERIC_SCENE_GRAPH_NODES_GROUPS_GROUP_CLASS_H_
