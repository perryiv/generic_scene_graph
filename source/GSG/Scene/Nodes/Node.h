
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2021, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Base class for all scene-graph nodes.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _GSG_NODES_NODE_CLASS_H_
#define _GSG_NODES_NODE_CLASS_H_

#include "GSG/Config.h"

#include "GSG/Base/Objects/Object.h"
#include "GSG/Base/Forward.h"

#include "GSG/Scene/Export.h"
#include "GSG/Scene/Forward.h"

#include "Usul/Bits/Bits.h"
#include "Usul/Math/Box.h"
#include "Usul/Properties/Map.h"

#include <atomic>
#include <map>
#include <mutex>

#define GSG_DECLARE_NODE_CLASS_BASE(class_name) \
  GSG_DECLARE_OBJECT_CLASS ( class_name ); \
  virtual void accept ( GSG::Scene::Visitors::Visitor & ) const; \
  virtual void accept ( GSG::Scene::Visitors::Visitor &, Usul::Properties::Map & ) const; \
  virtual void accept ( GSG::Scene::Visitors::Visitor &, Usul::Properties::Map::Values & ) const; \
  virtual void accept ( GSG::Scene::Visitors::Visitor & ); \
  virtual void accept ( GSG::Scene::Visitors::Visitor &, Usul::Properties::Map & ); \
  virtual void accept ( GSG::Scene::Visitors::Visitor &, Usul::Properties::Map::Values & )

#define GSG_DECLARE_NODE_CLASS(class_name) \
  GSG_DECLARE_OBJECT_CLASS ( class_name ); \
  virtual void accept ( GSG::Scene::Visitors::Visitor & ) const override; \
  virtual void accept ( GSG::Scene::Visitors::Visitor &, Usul::Properties::Map & ) const override; \
  virtual void accept ( GSG::Scene::Visitors::Visitor &, Usul::Properties::Map::Values & ) const override; \
  virtual void accept ( GSG::Scene::Visitors::Visitor & ) override; \
  virtual void accept ( GSG::Scene::Visitors::Visitor &, Usul::Properties::Map & ) override; \
  virtual void accept ( GSG::Scene::Visitors::Visitor &, Usul::Properties::Map::Values & ) override


namespace GSG {
namespace Scene {
namespace Nodes {


class GSG_SCENE_EXPORT Node : public GSG::Base::Objects::Object
{
public:

  GSG_DECLARE_NODE_CLASS_BASE ( Node );

  typedef GSG::Base::Objects::Object BaseClass;
  typedef std::recursive_mutex Mutex;
  typedef std::lock_guard < Mutex > Guard;
  typedef std::map < unsigned long, ValidAccessRefPtr > Parents;
  typedef Usul::Properties::Map PropertyMap;
  typedef Usul::Math::Boxf Bounds;

  // Flags for this class.
  enum : unsigned int
  {
    VISIBLE =              0x00000001,
    INTERSECTABLE =        0x00000002,
    CONTRIBUTE_TO_BOUNDS = 0x00000004,
    RENDER_TREE_DIRTY    = 0x00000008,
  };

  // Dirty/get the bounds.
  void           dirtyBounds();
  virtual Bounds getBounds() const = 0;

  // Get/set the state for contributing to the bounds.
  bool getContributeToBounds() const { return Usul::Bits::has < unsigned int > ( _flags, CONTRIBUTE_TO_BOUNDS ); }
  void setContributeToBounds ( bool state ) { _flags = Usul::Bits::set < unsigned int > ( _flags, CONTRIBUTE_TO_BOUNDS, state ); }

  // Get/set all the flags.
  unsigned int getFlags() const { return _flags; }
  void setFlags ( unsigned int flags ) { _flags = flags; }

  // Get the id.
  unsigned long getID() const { return _id; } // No need to guard.

  // Get/set the intersectable state.
  bool getIntersectable() const { return Usul::Bits::has < unsigned int > ( _flags, INTERSECTABLE ); }
  void setIntersectable ( bool state ) { _flags = Usul::Bits::set < unsigned int > ( _flags, INTERSECTABLE, state ); }

  // Dirty the render-tree, or see if it is.
  bool getRenderTreeDirty() const { return Usul::Bits::has < unsigned int > ( _flags, RENDER_TREE_DIRTY ); }
  void dirtyRenderTree();

  // Get/set the visible state.
  bool getVisible() const { return Usul::Bits::has < unsigned int > ( _flags, VISIBLE ); }
  void setVisible ( bool state ) { _flags = Usul::Bits::set < unsigned int > ( _flags, VISIBLE, state ); }

  // Does this node have the given parent?
  bool hasParent ( const Parents::mapped_type &parent ) const;

  // Direct access to internal mutex. Use with caution.
  Mutex &mutex() const { return _mutex; }

protected:

  friend class GSG::Scene::Nodes::Groups::Group;

  Node();
  virtual ~Node();

  void _addParent ( Node * );

  Bounds &_getBounds() const { return _bounds; } // This is mutable.

  void _removeParent ( Node * );

private:

  void _destroyNode();

  mutable Mutex _mutex;
  const unsigned long _id;
  std::atomic < unsigned int > _flags;
  Parents _parents;
  mutable Bounds _bounds;
};


} // namespace Nodes
} // namespace Scene
} // namespace GSG


#define GSG_IMPLEMENT_NODE_CLASS(class_name) \
  GSG_IMPLEMENT_OBJECT_CLASS ( class_name ) \
  void class_name ::accept ( GSG::Scene::Visitors::Visitor &visitor ) const \
  { \
    Usul::Properties::Map traversalData; \
    visitor.visit ( *this, traversalData ); \
  } \
  void class_name ::accept ( GSG::Scene::Visitors::Visitor &visitor, Usul::Properties::Map &traversalData ) const \
  { \
    visitor.visit ( *this, traversalData ); \
  } \
  void class_name ::accept ( GSG::Scene::Visitors::Visitor &visitor, Usul::Properties::Map::Values &values ) const \
  { \
    Usul::Properties::Map traversalData ( values ); \
    visitor.visit ( *this, traversalData ); \
  } \
  void class_name ::accept ( GSG::Scene::Visitors::Visitor &visitor ) \
  { \
    Usul::Properties::Map traversalData; \
    visitor.visit ( *this, traversalData ); \
  } \
  void class_name ::accept ( GSG::Scene::Visitors::Visitor &visitor, Usul::Properties::Map &traversalData ) \
  { \
    visitor.visit ( *this, traversalData ); \
  } \
  void class_name ::accept ( GSG::Scene::Visitors::Visitor &visitor, Usul::Properties::Map::Values &values ) \
  { \
    Usul::Properties::Map traversalData ( values ); \
    visitor.visit ( *this, traversalData ); \
  }


#endif // _GSG_NODES_NODE_CLASS_H_
