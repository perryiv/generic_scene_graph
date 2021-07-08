
////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2021, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//  Test the OSMesa renderer visitor class.
//
////////////////////////////////////////////////////////////////////////////////

#include "GSG/Renderers/OSMesa/Renderer.h"
#include "GSG/Scene/Nodes/Groups/Transform.h"
#include "GSG/Scene/Nodes/Shapes/Geometry.h"

#include "catch2/catch.hpp"

typedef GSG::Scene::Nodes::Groups::Group Group;
typedef GSG::Scene::Nodes::Groups::Transform Transform;
typedef GSG::Scene::Nodes::Node Node;
typedef GSG::Scene::Nodes::Shapes::Geometry Geometry;


////////////////////////////////////////////////////////////////////////////////
//
//  Build the scene for testing.
//
////////////////////////////////////////////////////////////////////////////////

namespace Details
{
  inline Node::RefPtr buildScene()
  {
    Group::RefPtr root = new Group;
    {
      Transform::RefPtr trans = new Transform;
      root->append ( trans );
      {
        Group::RefPtr group = new Group;
        trans->append ( group );
        {
          group->append ( new Geometry );
          group->append ( new Geometry );
          group->append ( new Geometry );
          group->append ( new Geometry );
        }
      }
    }
    {
      Transform::RefPtr trans = new Transform;
      root->append ( trans );
      {
        Group::RefPtr group = new Group;
        trans->append ( group );
        {
          group->append ( new Geometry );
          group->append ( new Geometry );
        }
      }
      {
        Group::RefPtr group = new Group;
        trans->append ( group );
        {
          group->append ( new Geometry );
          group->append ( new Geometry );
        }
      }
    }
    return root;
  }
}


////////////////////////////////////////////////////////////////////////////////
//
//  Test the array.
//
////////////////////////////////////////////////////////////////////////////////

TEST_CASE ( "OSGMesa Renderer" )
{
  typedef GSG::Renderers::OSMesa::Renderer Renderer;

  Node::Ptr scene = Details::buildScene();

  SECTION ( "Can make a renderer and render the scene" )
  {
    Renderer::Ptr renderer = new Renderer;
    renderer->resize ( 400, 200 );
    renderer->render ( scene.get() );
  }
}
