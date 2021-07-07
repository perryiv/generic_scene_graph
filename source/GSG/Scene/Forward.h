
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2021, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Forward declarations.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _GSG_SCENE_FORWARD_DECLARATIONS_H_
#define _GSG_SCENE_FORWARD_DECLARATIONS_H_


namespace GSG
{
  namespace Scene
  {
    namespace Nodes
    {
      namespace Groups
      {
        class Group;
        class Projection;
        class Transform;
      }
      namespace Shapes
      {
        class Geometry;
        class Shape;
      }
      class Node;
    }
    namespace Visitors
    {
      namespace Intersection
      {
        class Intersect;
      }
      class Visitor;
    }
  }
}


#endif // _GSG_SCENE_FORWARD_DECLARATIONS_H_
