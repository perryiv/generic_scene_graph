
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

#include "GSG/Nodes/Node.h"

#include <vector>


namespace GSG {
namespace Nodes {
namespace Groups {


class GSG_EXPORT Group : public Node
{
public:

  typedef Node BaseClass;
  typedef Node::RefPtr NodePtr;
  typedef std::vector < NodePtr > Children;
  typedef Children::const_iterator const_iterator;
  typedef Children::iterator iterator;
  typedef Children::const_reference const_reference;
  typedef Children::reference reference;
  typedef Children::size_type size_type;

  GSG_DECLARE_NODE_CLASS ( Group );

  // Constructor
  Group();

  // Add the child node.
  void addChild ( NodePtr child ) { this->push_back ( child ); }

  // Access the child.
  const_reference at ( size_type ) const;
  reference       at ( size_type );

  // Get the last node. Throws an exception if the group is empty.
  const_reference back() const;
  reference       back();

  // Iterators.
  const_iterator begin() const { return _children.begin(); }
  iterator       begin()       { return _children.begin(); }
  const_iterator end() const   { return _children.end(); }
  iterator       end()         { return _children.end(); }

  // Clear the group.
  void clear() { this->removeAllChildren(); }

  // Is the group empty?
  bool empty() const { return _children.empty(); }

  // Get the first node. Throws an exception if the group is empty.
  const_reference front() const;
  reference       front();

  // Insert the node before the given position iterator.
  // Throws an exception if the given position iterator is invalid.
  iterator insert ( iterator pos, NodePtr );
  iterator insert ( const_iterator pos, NodePtr );
  template< class Itr > iterator insert ( iterator pos, Itr first, Itr last);
  template< class Itr > iterator insert ( const_iterator pos, Itr first, Itr last );

  // Access the child.
  reference       operator[] ( size_type index )       { return this->at ( index ); }
  const_reference operator[] ( size_type index ) const { return this->at ( index ); }

  // Add the node to the end of the sequence.
  void push_back ( NodePtr );

  // Add the node to the beginning of the sequence.
  void push_front ( NodePtr );

  // Remove all the child nodes.
  void removeAllChildren();

  // Get the size of the group, which is the number of child nodes.
  bool size() const { return _children.size(); }

protected:

  virtual ~Group();

private:

  void _destroyGroup();

  Children _children;
};


} // namespace Groups
} // namespace Nodes
} // namespace GSG


#endif // _GENERIC_SCENE_GRAPH_NODES_GROUPS_GROUP_CLASS_H_
