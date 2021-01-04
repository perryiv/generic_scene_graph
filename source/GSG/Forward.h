
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
    namespace Containers
    {
      class Int8Array;
      class Uint8Array;
      class Int16Array;
      class Uint16Array;
      class Int32Array;
      class Uint32Array;
      class Int64Array;
      class Uint64Array;
      class Float32Array;
      class Float64Array;
    }
    namespace Objects
    {
      class Object;
    }
  }
  namespace Scene
  {
    namespace Nodes
    {
      namespace Groups
      {
        class Group;
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


#endif // _GENERIC_SCENE_GRAPH_FORWARD_DECLARATIONS_H_
