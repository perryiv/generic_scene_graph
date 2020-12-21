
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2020, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Shape node based on vertex arrays.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _GENERIC_SCENE_GRAPH_NODES_SHAPES_GEOMETRY_CLASS_H_
#define _GENERIC_SCENE_GRAPH_NODES_SHAPES_GEOMETRY_CLASS_H_

#include "GSG/Scene/Nodes/Shapes/Shape.h"
#include "GSG/Base/Containers/TypedArrays.h"
#include "GSG/Scene/Primitives/Primitive.h"


namespace GSG {
namespace Scene {
namespace Nodes {
namespace Shapes {


class GSG_EXPORT Geometry : public GSG::Scene::Nodes::Shapes::Shape
{
public:

  typedef GSG::Scene::Nodes::Shapes::Shape BaseClass;
  typedef GSG::Base::Containers::Float32Array Float32Array;
  typedef Float32Array::ValidAccessRefPtr Float32ArrayPtr;
  typedef GSG::Scene::Primitives::Primitive Primitive;
  typedef Primitive::ValidAccessRefPtr PrimitivePtr;

  GSG_DECLARE_NODE_CLASS ( Geometry );

  Geometry();

  // Get/set the points.
  const Float32ArrayPtr getPoints() const    { return _points; }
  Float32ArrayPtr       getPoints()          { return _points; }
  void                  setPoints ( Float32ArrayPtr );

  // Get/set the normals.
  const Float32ArrayPtr getNormals() const   { return _normals; }
  Float32ArrayPtr       getNormals()         { return _normals; }
  void                  setNormals ( Float32ArrayPtr );

  // Get/set the colors.
  const Float32ArrayPtr getColors() const    { return _colors; }
  Float32ArrayPtr       getColors()          { return _colors; }
  void                  setColors ( Float32ArrayPtr );

  // Get/set the texture coordinates.
  const Float32ArrayPtr getTexCoords() const { return _texCoords; }
  Float32ArrayPtr       getTexCoords()       { return _texCoords; }
  void                  setTexCoords ( Float32ArrayPtr );


protected:

  virtual ~Geometry();

private:

  void _destroyGeometry();

  Float32ArrayPtr _points;
  Float32ArrayPtr _normals;
  Float32ArrayPtr _colors;
  Float32ArrayPtr _texCoords;
};


} // namespace Shapes
} // namespace Nodes
} // namespace Scene
} // namespace GSG


#endif // _GENERIC_SCENE_GRAPH_NODES_SHAPES_GEOMETRY_CLASS_H_
