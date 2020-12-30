
////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2020, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//  Test the group node.
//
////////////////////////////////////////////////////////////////////////////////

#include "GSG/Scene/Nodes/Groups/Group.h"

#include "Usul/Errors/Exceptions.h"

#include "catch2/catch.hpp"


////////////////////////////////////////////////////////////////////////////////
//
//  Test the group node.
//
////////////////////////////////////////////////////////////////////////////////

TEST_CASE ( "Scene group node" )
{
  typedef GSG::Scene::Nodes::Groups::Group Group;
  typedef Group::RefPtr OtherPtr;

  static_assert ( ( false == ( std::is_same < Group::Ptr, OtherPtr > ::value ) ),
    "Need to use different pointer types when testing" );

  SECTION ( "Can add child nodes" )
  {
    Group::Ptr root ( new Group() );

    Group::Ptr child1 ( new Group() );
    Group::Ptr child2 ( new Group() );
    Group::Ptr child3 ( new Group() );
    Group::Ptr child4 ( new Group() );

    REQUIRE ( 1 ==   root->getReferenceCount() );
    REQUIRE ( 1 == child1->getReferenceCount() );
    REQUIRE ( 1 == child2->getReferenceCount() );
    REQUIRE ( 1 == child3->getReferenceCount() );
    REQUIRE ( 1 == child4->getReferenceCount() );

    root->append ( child1 );
    root->append ( child2 );
    root->append ( child3 );
    root->append ( child4 );

    REQUIRE ( 4 == root->size() );

    REQUIRE ( true == child1->hasParent ( root ) );
    REQUIRE ( true == child2->hasParent ( root ) );
    REQUIRE ( true == child3->hasParent ( root ) );
    REQUIRE ( true == child4->hasParent ( root ) );

    REQUIRE ( true == child1->hasParent ( OtherPtr ( root ) ) );
    REQUIRE ( true == child2->hasParent ( OtherPtr ( root ) ) );
    REQUIRE ( true == child3->hasParent ( OtherPtr ( root ) ) );
    REQUIRE ( true == child4->hasParent ( OtherPtr ( root ) ) );

    Group::Ptr child5 ( new Group() );
    REQUIRE ( false == root->hasParent ( child5 ) );
    REQUIRE ( false == root->hasParent ( Group::Ptr() ) );
  }

  SECTION ( "Can access child nodes" )
  {
    Group::Ptr root ( new Group() );

    Group::Ptr child0 ( new Group() );
    Group::Ptr child1 ( new Group() );

    root->append ( child0 );
    root->append ( child1 );

    REQUIRE ( child0.get() == root->at ( 0 ).get() );
    REQUIRE ( child1.get() == root->at ( 1 ).get() );

    REQUIRE ( child0.get() == (*root)[0].get() );
    REQUIRE ( child1.get() == (*root)[1].get() );
  }

  SECTION ( "Can not add node to group twice" )
  {
    Group::Ptr root ( new Group() );

    Group::Ptr child0 ( new Group() );
    Group::Ptr child1 ( new Group() );

    root->append ( child0 );
    root->append ( child1 );

    REQUIRE_THROWS_AS   ( root->append ( child0 ), Usul::Errors::RuntimeError );
    REQUIRE_THROWS_AS   ( root->append ( child0 ), std::exception );
    REQUIRE_THROWS_WITH ( root->append ( child0 ), "This node already has the given parent" );

    REQUIRE ( 2 == root->size() );

    REQUIRE ( child0.get() == root->at ( 0 ).get() );
    REQUIRE ( child1.get() == root->at ( 1 ).get() );
  }

  SECTION ( "Can insert child nodes" )
  {
    Group::Ptr root ( new Group() );

    Group::Ptr child0 ( new Group() );
    Group::Ptr child1 ( new Group() );
    Group::Ptr child2 ( new Group() );
    Group::Ptr child3 ( new Group() );
    Group::Ptr child4 ( new Group() );

    root->append ( child0 );
    root->insert ( 0, child1 );
    root->insert ( 0, child2 );
    root->insert ( 1, child3 );
    root->insert ( 100, child4 ); // Should append.

    REQUIRE ( 5 == root->size() );

    REQUIRE ( child2.get() == root->at ( 0 ).get() );
    REQUIRE ( child3.get() == root->at ( 1 ).get() );
    REQUIRE ( child1.get() == root->at ( 2 ).get() );
    REQUIRE ( child0.get() == root->at ( 3 ).get() );
    REQUIRE ( child4.get() == root->at ( 4 ).get() );
  }

  SECTION ( "Can get the children" )
  {
  }
}
