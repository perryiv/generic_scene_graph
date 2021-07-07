
////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2021, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//  Test the container of graphics state.
//
////////////////////////////////////////////////////////////////////////////////

#include "GSG/Scene/State/Container.h"

#include "catch2/catch.hpp"

#include <map>

USUL_DEFINE_MAKE_PROPERTY_FUNCTION_SHORTCUT // mp


////////////////////////////////////////////////////////////////////////////////
//
//  Test the container of graphics state.
//
////////////////////////////////////////////////////////////////////////////////

TEST_CASE ( "Primitive set for drawing elements" )
{
  typedef GSG::Scene::State::Container StateContainer;
  std::map < std::string, bool > names;
  std::map < unsigned long, bool > ids;

  auto checkUniqueNameAndID = [ &names, &ids ] ( const StateContainer::RefPtr &state )
  {
    REQUIRE ( false == names[state->getName()] );
    names[state->getName()] = true; // For next time.

    REQUIRE ( false == ids[state->getID()] );
    ids[state->getID()] = true; // For next time.
  };

  SECTION ( "Constructors" )
  {
    {
      StateContainer::RefPtr state = new StateContainer ( GSG_STATE_CONTAINER_NAME );
      REQUIRE ( std::string::npos != state->getName().find ( "Line: 49" ) );
      REQUIRE ( std::string::npos != state->getName().find ( "File:" ) );
      REQUIRE ( std::string::npos != state->getName().find ( "GSG/Scene/State/Container.cpp" ) );
      checkUniqueNameAndID ( state );
      REQUIRE ( true == state->getPropertyMap().empty() );
    }
    {
      StateContainer::RefPtr state = new StateContainer ( GSG_STATE_CONTAINER_NAME, {
        { "name1", mp ( "prop1" ) }
      } );
      REQUIRE ( std::string::npos != state->getName().find ( "Line: 57" ) );
      REQUIRE ( std::string::npos != state->getName().find ( "File:" ) );
      REQUIRE ( std::string::npos != state->getName().find ( "GSG/Scene/State/Container.cpp" ) );
      checkUniqueNameAndID ( state );
      REQUIRE ( false == state->getPropertyMap().empty() );
      REQUIRE ( "prop1" == state->getPropertyMap().require < std::string > ( "name1" ) );
    }
    {
      StateContainer::RefPtr state = new StateContainer ( "some name" );
      REQUIRE ( "some name" == state->getName() );
      checkUniqueNameAndID ( state );
      REQUIRE ( true == state->getPropertyMap().empty() );
    }
    {
      StateContainer::RefPtr state = new StateContainer ( "some other name", {
        { "name2", mp ( "prop2" ) }
      } );
      REQUIRE ( "some other name" == state->getName() );
      checkUniqueNameAndID ( state );
      REQUIRE ( false == state->getPropertyMap().empty() );
      REQUIRE ( "prop2" == state->getPropertyMap().require < std::string > ( "name2" ) );
    }
  }
}
