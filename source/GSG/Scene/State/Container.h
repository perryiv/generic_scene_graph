
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

#ifndef _GSG_STATE_CONTAINER_CLASS_H_
#define _GSG_STATE_CONTAINER_CLASS_H_

#include "GSG/Config.h"

#include "GSG/Base/Objects/Object.h"

#include "GSG/Scene/Export.h"

#include "Usul/Properties/Map.h"
#include "Usul/Strings/Format.h"

#include <functional>


namespace GSG {
namespace Scene {
namespace State {


class GSG_SCENE_EXPORT Container : public GSG::Base::Objects::Object
{
public:

  GSG_DECLARE_OBJECT_CLASS ( Container );

  typedef GSG::Base::Objects::Object BaseClass;
  typedef Usul::Properties::Map PropertyMap;
  typedef std::function < void ( const Container & ) > Callback;

  // Constructors
  Container ( const std::string & );
  Container ( const std::string &, const PropertyMap & );
  Container ( const std::string &, const PropertyMap::Values & );

  // Apply/reset the state.
  void apply();
  void reset();

  // Get the id.
  unsigned long getID() const { return _id; }

  // Get the name.
  const std::string &getName() const { return _name; }

  // Get/set the property map.
  const PropertyMap &getPropertyMap() const { return _props; }
  PropertyMap &      getPropertyMap()       { return _props; }
  void               setPropertyMap ( const PropertyMap & );
  void               setPropertyMap ( const PropertyMap::Values & );

  // Set the apply/reset callbacks.
  void setApplyCallback ( const Callback & );
  void setResetCallback ( const Callback & );

protected:

  virtual ~Container();

private:

  void _destroyContainer();

  const unsigned long _id;
  const std::string _name;
  PropertyMap _props;
  Callback _apply;
  Callback _reset;
};


} // namespace State
} // namespace Scene
} // namespace GSG


// For convenience, pass to the constructor.
#define GSG_STATE_CONTAINER_NAME \
  Usul::Strings::format ( \
    "File: ", __FILE__, \
    ", Line: ", __LINE__ \
  )


#endif // _GSG_STATE_CONTAINER_CLASS_H_
