
////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2021, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//  Test the visitor that culls the scene and builds the render-tree.
//
////////////////////////////////////////////////////////////////////////////////

#include "GSG/Tools/Visitors/Cull/Visitor.h"
#include "GSG/Scene/Nodes/Groups/Transform.h"
#include "GSG/Scene/Nodes/Shapes/Geometry.h"
#include "GSG/Scene/Primitives/DrawElements.h"

#include "catch2/catch.hpp"

USUL_DEFINE_MAKE_PROPERTY_FUNCTION_SHORTCUT // mp

typedef GSG::Scene::Nodes::Groups::Group Group;
typedef GSG::Scene::Nodes::Groups::Transform Transform;
typedef GSG::Scene::Nodes::Node Node;
typedef GSG::Scene::Nodes::Shapes::Geometry Geometry;
typedef GSG::Scene::Primitives::DrawElementsUint8 DrawElementsUint8;
typedef GSG::Tools::Visitors::Cull::Visitor CullVisitor;
typedef Transform::Matrix44d Matrix44d;


////////////////////////////////////////////////////////////////////////////////
//
//  Build the scene for testing.
//
////////////////////////////////////////////////////////////////////////////////

namespace Details
{
  inline Node::RefPtr buildScene()
  {
    Geometry::RefPtr geom = new Geometry;
    {
      geom->setPoints  ( { 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0 } );
      geom->setNormals ( { 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0 } );
      geom->addPrimitives ( new DrawElementsUint8 ( GSG::Constants::Mode::TRIANGLES, { 0, 1, 2, 1, 3, 2 } ) );
    }

    Group::RefPtr root = new Group;
    {
      Transform::RefPtr trans = new Transform;
      trans->setMatrix ( Usul::Math::translate ( Matrix44d(), 2.0, 0.0, 0.0 ) );
      trans->append ( geom );
      root->append ( trans );
    }
    {
      Transform::RefPtr trans = new Transform;
      trans->setMatrix ( Usul::Math::translate ( Matrix44d(), -2.0, 0.0, 0.0 ) );
      trans->append ( geom );
      root->append ( trans );
    }
    return root;
  }
}


////////////////////////////////////////////////////////////////////////////////
//
//  Test the scene visitor.
//
////////////////////////////////////////////////////////////////////////////////

TEST_CASE ( "Cull visitor" )
{
  // typedef CullVisitor::PropertyMap PropertyMap;

  Node::RefPtr scene = Details::buildScene();

  SECTION ( "Can visit nodes and build render-tree" )
  {
    CullVisitor::RefPtr cv = new CullVisitor();
    cv->cull ( scene.get() );
  }
}
