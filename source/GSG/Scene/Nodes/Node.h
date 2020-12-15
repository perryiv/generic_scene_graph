
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

#ifndef _GENERIC_SCENE_GRAPH_NODES_NODE_CLASS_H_
#define _GENERIC_SCENE_GRAPH_NODES_NODE_CLASS_H_

#include "GSG/Base/Objects/Object.h"
#include "GSG/Forward.h"

#include "Usul/Bits/Bits.h"

#include <atomic>
#include <mutex>
#include <set>

#define GSG_DECLARE_NODE_CLASS(class_name) \
  GSG_DECLARE_OBJECT_CLASS ( class_name ); \
  virtual void accept ( GSG::Visitors::Visitor & ) const; \
  virtual void accept ( GSG::Visitors::Visitor & )

#define GSG_IMPLEMENT_NODE_CLASS(class_name) \
  GSG_IMPLEMENT_OBJECT_CLASS ( class_name ) \
  void class_name ::accept ( GSG::Visitors::Visitor &visitor ) const { visitor.visit ( *this ); } \
  void class_name ::accept ( GSG::Visitors::Visitor &visitor ) { visitor.visit ( *this ); }


namespace GSG {
namespace Scene {
namespace Nodes {


class GSG_EXPORT Node : public GSG::Base::Objects::Object
{
public:

  GSG_DECLARE_NODE_CLASS ( Node );

  typedef GSG::Base::Objects::Object BaseClass;
  typedef std::recursive_mutex Mutex;
  typedef std::lock_guard < Mutex > Guard;
  typedef std::atomic < unsigned int > Flags;
  typedef std::set < ValidAccessRefPtr > Parents;

  // Flags for this class.
  enum : unsigned int
  {
    VISIBLE =              0x00000001,
    INTERSECTABLE =        0x00000002,
    CONTRIBUTE_TO_BOUNDS = 0x00000004,
  };

  // Get/set all the flags.
  unsigned int getFlags() const { return _flags; }
  void setFlags ( unsigned int flags ) { _flags = flags; }

  // Get/set the state for contributing to the bounds.
  bool getContributeToBounds() const { return Usul::Bits::has < unsigned int > ( _flags, CONTRIBUTE_TO_BOUNDS ); }
  void setContributeToBounds ( bool state ) { _flags = Usul::Bits::set < unsigned int > ( _flags, CONTRIBUTE_TO_BOUNDS, state ); }

  // Get/set the intersectable state.
  bool getIntersectable() const { return Usul::Bits::has < unsigned int > ( _flags, INTERSECTABLE ); }
  void setIntersectable ( bool state ) { _flags = Usul::Bits::set < unsigned int > ( _flags, INTERSECTABLE, state ); }

  // Get/set the visible state.
  bool getVisible() const { return Usul::Bits::has < unsigned int > ( _flags, VISIBLE ); }
  void setVisible ( bool state ) { _flags = Usul::Bits::set < unsigned int > ( _flags, VISIBLE, state ); }

  // Does this node have the given parent?
  bool hasParent ( const Parents::value_type &parent ) const;

  // Direct access to internal mutex. Use with caution.
  Mutex &mutex() const { return _mutex; }

protected:

  friend class GSG::Scene::Nodes::Groups::Group;

  Node();
  virtual ~Node();

  void _addParent ( Node * );

  void _removeParent ( Node * );

private:

  void _destroyNode();

  mutable Mutex _mutex;
  Flags _flags;
  Parents _parents;
};


} // namespace Nodes
} // namespace Scene
} // namespace GSG


#endif // _GENERIC_SCENE_GRAPH_NODES_NODE_CLASS_H_
