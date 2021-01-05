
////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2020, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//  Test the scene visitors that call registered functions.
//
////////////////////////////////////////////////////////////////////////////////

#include "GSG/Scene/Visitors/Callbacks/Const.h"
#include "GSG/Scene/Visitors/Callbacks/Modify.h"
#include "GSG/Scene/Nodes/Groups/Transform.h"
#include "GSG/Scene/Nodes/Shapes/Geometry.h"

#include "catch2/catch.hpp"

#include <map>
#include <sstream>

USUL_DEFINE_MAKE_PROPERTY_FUNCTION_SHORTCUT // mp

typedef GSG::Scene::Nodes::Groups::Group Group;
typedef GSG::Scene::Nodes::Groups::Transform Transform;
typedef GSG::Scene::Nodes::Node Node;
typedef GSG::Scene::Nodes::Shapes::Geometry Geometry;
typedef GSG::Scene::Visitors::Callbacks::Const ConstVisitor;
typedef GSG::Scene::Visitors::Callbacks::Modify ModifyVisitor;
typedef std::map < unsigned long, Node::RefPtr > IDS;


////////////////////////////////////////////////////////////////////////////////
//
//  This is what should print during the traversal.
//
////////////////////////////////////////////////////////////////////////////////

namespace Details
{
  const char *SCENE_TREE = R"=====(
  Group start
    Transform start
      Group start
        Geometry
        Geometry
        Geometry
        Geometry
      Group end
    Transform end
    Transform start
      Group start
        Geometry
        Geometry
      Group end
      Group start
        Geometry
        Geometry
      Group end
    Transform end
  Group end
)=====";
}


////////////////////////////////////////////////////////////////////////////////
//
//  Store the id and return the node.
//
////////////////////////////////////////////////////////////////////////////////

namespace Details
{
  template < class NodeType >
  inline NodeType *storeID ( IDS &ids, NodeType *node )
  {
    typedef typename NodeType::RefPtr NodePtr;
    const unsigned long id = node->getID();
    REQUIRE ( 0 == ids.count ( id ) );
    ids.insert ( IDS::value_type ( id, NodePtr ( node ) ) );
    return node;
  }
}


////////////////////////////////////////////////////////////////////////////////
//
//  Remove the id.
//
////////////////////////////////////////////////////////////////////////////////

namespace Details
{
  template < class NodeType >
  inline void removeID ( IDS &ids, NodeType *node )
  {
    const unsigned long id = node->getID();
    REQUIRE ( 1 == ids.count ( id ) );
    REQUIRE ( node == ids[id].get() );
    ids.erase ( id );
  }
}


////////////////////////////////////////////////////////////////////////////////
//
//  Build the scene for testing.
//
////////////////////////////////////////////////////////////////////////////////

namespace Details
{
  inline Group::RefPtr buildScene ( IDS &ids )
  {
    Group::RefPtr root = Details::storeID ( ids, new Group );
    {
      Transform::RefPtr trans = Details::storeID ( ids, new Transform );
      root->append ( trans );
      {
        Group::RefPtr group = Details::storeID ( ids, new Group );
        trans->append ( group );
        {
          group->append ( Details::storeID ( ids, new Geometry ) );
          group->append ( Details::storeID ( ids, new Geometry ) );
          group->append ( Details::storeID ( ids, new Geometry ) );
          group->append ( Details::storeID ( ids, new Geometry ) );
        }
      }
    }
    {
      Transform::RefPtr trans = Details::storeID ( ids, new Transform );
      root->append ( trans );
      {
        Group::RefPtr group = Details::storeID ( ids, new Group );
        trans->append ( group );
        {
          group->append ( Details::storeID ( ids, new Geometry ) );
          group->append ( Details::storeID ( ids, new Geometry ) );
        }
      }
      {
        Group::RefPtr group = Details::storeID ( ids, new Group );
        trans->append ( group );
        {
          group->append ( Details::storeID ( ids, new Geometry ) );
          group->append ( Details::storeID ( ids, new Geometry ) );
        }
      }
    }
    return root;
  }
}


////////////////////////////////////////////////////////////////////////////////
//
//  Test the scene visitor.
//
////////////////////////////////////////////////////////////////////////////////

TEST_CASE ( "Scene visitor with modify callbacks" )
{
  typedef ModifyVisitor VisitorType;
  typedef VisitorType::PropertyMap PropertyMap;

  IDS ids;
  Group::RefPtr scene = Details::buildScene ( ids );
  std::ostringstream out; out << '\n';

  SECTION ( "Can traverse and visit nodes" )
  {
    VisitorType::RefPtr visitor = new VisitorType();
    std::string indent = "  ";

    visitor->setTransformCallback ( [ &out, &indent ] ( GSG::Scene::Nodes::Groups::Transform &, PropertyMap & )
    {
      out << indent << "Transform start" << std::endl;
      indent += "  ";
    }, VisitorType::BEFORE_TRAVERSAL );

    visitor->setTransformCallback ( [ &out, &ids, &indent ] ( GSG::Scene::Nodes::Groups::Transform &node, PropertyMap & )
    {
      indent.resize ( indent.size() - 2 );
      out << indent << "Transform end" << std::endl;
      Details::removeID ( ids, &node );
    }, VisitorType::AFTER_TRAVERSAL );

    visitor->setGroupCallback ( [ &out, &indent ] ( GSG::Scene::Nodes::Groups::Group &, PropertyMap & )
    {
      out << indent << "Group start" << std::endl;
      indent += "  ";
    }, VisitorType::BEFORE_TRAVERSAL );

    visitor->setGroupCallback ( [ &out, &ids, &indent ] ( GSG::Scene::Nodes::Groups::Group &node, PropertyMap & )
    {
      indent.resize ( indent.size() - 2 );
      out << indent << "Group end" << std::endl;
      Details::removeID ( ids, &node );
    }, VisitorType::AFTER_TRAVERSAL );

    visitor->setGeometryCallback ( [ &out, &ids, &indent ] ( GSG::Scene::Nodes::Shapes::Geometry &node, PropertyMap & )
    {
      out << indent << "Geometry" << std::endl;
      Details::removeID ( ids, &node );
    } );

    scene->accept ( *visitor );

    REQUIRE ( true == ids.empty() );
    REQUIRE ( out.str() == Details::SCENE_TREE );
  }
}
