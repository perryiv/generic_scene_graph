
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2021, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Container of graphics state.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _GENERIC_SCENE_GRAPH_STATE_CONTAINER_CLASS_H_
#define _GENERIC_SCENE_GRAPH_STATE_CONTAINER_CLASS_H_

#include "GSG/Base/Objects/Object.h"

#include "Usul/Properties/Map.h"


namespace GSG {
namespace Scene {
namespace State {


class GSG_EXPORT Container : public GSG::Base::Objects::Object
{
public:

  GSG_DECLARE_OBJECT_CLASS ( Container );

  typedef GSG::Base::Objects::Object BaseClass;
  typedef Usul::Properties::Map PropertyMap;
  typedef std::function < void ( const Container & ) > Callback;

  // Constructor
  Container ( unsigned long );
  Container ( unsigned long, const PropertyMap & );

  // Apply/reset the state.
  void apply();
  void reset();

  // Set the apply/reset callbacks.
  void setApplyCallback ( const Callback & );
  void setResetCallback ( const Callback & );

  // Get the id.
  unsigned long getID() const { return _id; }

  // Get/set the property map.
  const PropertyMap &getPropertyMap() const { return _props; }
  PropertyMap &      getPropertyMap()       { return _props; }
  void               setPropertyMap ( const PropertyMap & );

protected:

  virtual ~Container();

private:

  void _destroyContainer();

  const unsigned long _id;
  PropertyMap _props;
  Callback _apply;
  Callback _reset;
};


} // namespace State
} // namespace Scene
} // namespace GSG


#endif // _GENERIC_SCENE_GRAPH_STATE_CONTAINER_CLASS_H_
