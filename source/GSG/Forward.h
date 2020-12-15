
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2020, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Forward declarations.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _GENERIC_SCENE_GRAPH_FORWARD_DECLARATIONS_H_
#define _GENERIC_SCENE_GRAPH_FORWARD_DECLARATIONS_H_


namespace GSG
{
  namespace Base
  {
    namespace Objects
    {
      class Object;
    }
  }
  namespace Scene
  {
    namespace Buffers
    {
      class Buffer;
    }
    namespace Nodes
    {
      namespace Groups
      {
        class Group;
      }
      namespace Shapes
      {
        class Geometry;
        class Shape;
      }
      class Node;
    }
  }
  namespace Visitors
  {
    class Visitor;
  }
}


#endif // _GENERIC_SCENE_GRAPH_FORWARD_DECLARATIONS_H_
