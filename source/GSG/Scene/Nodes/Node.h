
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

#include "GSG/Config.h"
#include "GSG/Export.h"

#include "Usul/Base/Referenced.h"
#include "Usul/Bits/Bits.h"
#include "Usul/Pointers/Pointers.h"
#include "Usul/Tools/NoCopying.h"

#include <atomic>
#include <mutex>
#include <set>

namespace GSG { namespace Scene { namespace Nodes { namespace Groups { class Group; } } } };

#define GSG_DECLARE_NODE_CLASS(class_name) \
  USUL_REFERENCED_CLASS ( class_name )


namespace GSG {
namespace Scene {
namespace Nodes {


class GSG_EXPORT Node : public Usul::Base::Referenced,
  public Usul::Tools::NoCopying
{
public:

  GSG_DECLARE_NODE_CLASS ( Node );

  typedef Usul::Base::Referenced BaseClass;
  typedef std::recursive_mutex Mutex;
  typedef std::lock_guard < Mutex > Guard;
  typedef std::atomic < unsigned int > Flags;
  typedef std::set < RefPtr > Parents;

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

  // Get/set the intersectable state.
  bool isIntersectable() const { return Usul::Bits::has < unsigned int > ( _flags, INTERSECTABLE ); }
  void setIntersectable ( bool state ) { _flags = Usul::Bits::set < unsigned int > ( _flags, INTERSECTABLE, state ); }

  // Get/set the visible state.
  bool isVisible() const { return Usul::Bits::has < unsigned int > ( _flags, VISIBLE ); }
  void setVisible ( bool state ) { _flags = Usul::Bits::set < unsigned int > ( _flags, VISIBLE, state ); }

  // Does this node have the given parent?
  bool hasParent ( RefPtr ) const;

  // Direct access to internal mutex. Use with caution.
  Mutex &mutex() { return _mutex; }

protected:

  friend class GSG::Scene::Nodes::Groups::Group;

  Node();
  virtual ~Node();

  void _addParent ( RefPtr );
  void _removeParent ( RefPtr );

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
