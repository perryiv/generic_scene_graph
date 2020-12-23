
////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2020, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//  Test the transform group node.
//
////////////////////////////////////////////////////////////////////////////////

#include "GSG/Scene/Nodes/Groups/Transform.h"

#include "catch2/catch.hpp"

typedef GSG::Scene::Nodes::Groups::Transform Transform;
typedef Transform::Matrix44d Matrix44d;


////////////////////////////////////////////////////////////////////////////////
//
//  Helper function that adds children.
//
////////////////////////////////////////////////////////////////////////////////

namespace Details
{
  inline void addChildren ( Transform::Ptr &trans, unsigned int depth )
  {
    const Matrix44d m ( {
      2, 0, 0, 0,
      0, 2, 0, 0,
      0, 0, 2, 0,
      0, 0, 0, 2
    } );
    Transform::Ptr child1 ( new Transform ( m ) );
    Transform::Ptr child2 ( new Transform ( m ) );
    Transform::Ptr child3 ( new Transform ( m ) );
    Transform::Ptr child4 ( new Transform ( m ) );

    trans->addChild ( child1 );
    trans->addChild ( child2 );
    trans->addChild ( child3 );
    trans->addChild ( child4 );

    if ( 0 == depth )
    {
      return;
    }

    Details::addChildren ( child1, depth - 1 );
    Details::addChildren ( child2, depth - 1 );
    Details::addChildren ( child3, depth - 1 );
    Details::addChildren ( child4, depth - 1 );
  }
}


////////////////////////////////////////////////////////////////////////////////
//
//  Test the group node.
//
////////////////////////////////////////////////////////////////////////////////

TEST_CASE ( "Scene transform group node" )
{
  SECTION ( "Can traverse and modify the graph" )
  {
    Transform::Ptr root ( new Transform() );
    Details::addChildren ( root, 4 );

  }
}
