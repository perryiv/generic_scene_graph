
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

  SECTION ( "Can access a child nodes" )
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
}
