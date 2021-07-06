
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

#ifndef _GSG_NODES_SHAPES_GEOMETRY_CLASS_H_
#define _GSG_NODES_SHAPES_GEOMETRY_CLASS_H_

#include "GSG/Scene/Nodes/Shapes/Shape.h"
#include "GSG/Base/Containers/TypedArrays.h"
#include "GSG/Scene/Primitives/PrimitiveSet.h"

#include <immer/vector.hpp>


namespace GSG {
namespace Scene {
namespace Nodes {
namespace Shapes {


class GSG_SCENE_EXPORT Geometry : public GSG::Scene::Nodes::Shapes::Shape
{
public:

  typedef GSG::Scene::Nodes::Shapes::Shape BaseClass;
  typedef BaseClass::Mutex Mutex;
  typedef BaseClass::Guard Guard;
  typedef GSG::Base::Containers::Float32Array Float32Array;
  typedef Float32Array::ValidAccessRefPtr Float32ArrayPtr;
  typedef GSG::Scene::Primitives::PrimitiveSet PrimitiveSet;
  typedef PrimitiveSet::ValidAccessRefPtr PrimitiveSetPtr;
  typedef immer::vector < PrimitiveSetPtr > PrimitiveSets;

  GSG_DECLARE_NODE_CLASS ( Geometry );

  Geometry();

  // Get the bounds.
  virtual Bounds getBounds() const override;

  // Get/set the colors.
  const Float32ArrayPtr getColors() const;
  Float32ArrayPtr       getColors();
  void                  setColors ( Float32ArrayPtr );

  // Get/set the normals.
  const Float32ArrayPtr getNormals() const;
  Float32ArrayPtr       getNormals();
  void                  setNormals ( Float32ArrayPtr );

  // Get/set the points.
  const Float32ArrayPtr getPoints() const;
  Float32ArrayPtr       getPoints();
  void                  setPoints ( Float32ArrayPtr );

  // Get/set the texture coordinates.
  const Float32ArrayPtr getTexCoords() const;
  Float32ArrayPtr       getTexCoords();
  void                  setTexCoords ( Float32ArrayPtr );

  // Add/remove/get the primitives.
  void          addPrimitives    ( PrimitiveSetPtr );
  void          removePrimitives ( PrimitiveSetPtr );
  PrimitiveSets getPrimitives() const;

protected:

  virtual ~Geometry();

private:

  void _destroyGeometry();

  Float32ArrayPtr _points;
  Float32ArrayPtr _normals;
  Float32ArrayPtr _colors;
  Float32ArrayPtr _texCoords;
  PrimitiveSets _primitives;
};


} // namespace Shapes
} // namespace Nodes
} // namespace Scene
} // namespace GSG


#endif // _GSG_NODES_SHAPES_GEOMETRY_CLASS_H_
