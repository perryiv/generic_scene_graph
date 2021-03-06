
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2021, Perry L Miller IV
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

#include <initializer_list>
#include <vector>


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
  typedef std::vector < PrimitiveSetPtr > PrimitiveSets;

  GSG_DECLARE_NODE_CLASS ( Geometry );

  Geometry();

  // Get the bounds.
  virtual Bounds getBounds() const override;

  // Get/set the colors.
  const Float32ArrayPtr getColors() const;
  Float32ArrayPtr       getColors();
  void                  setColors ( Float32Array * );
  void                  setColors ( Float32ArrayPtr );
  void                  setColors ( const std::initializer_list < float > & );

  // Get/set the normals.
  const Float32ArrayPtr getNormals() const;
  Float32ArrayPtr       getNormals();
  void                  setNormals ( Float32Array * );
  void                  setNormals ( Float32ArrayPtr );
  void                  setNormals ( const std::initializer_list < float > & );

  // Get/set the points.
  const Float32ArrayPtr getPoints() const;
  Float32ArrayPtr       getPoints();
  void                  setPoints ( Float32Array * );
  void                  setPoints ( Float32ArrayPtr );
  void                  setPoints ( const std::initializer_list < float > & );

  // Get/set the texture coordinates.
  const Float32ArrayPtr getTexCoords() const;
  Float32ArrayPtr       getTexCoords();
  void                  setTexCoords ( Float32Array * );
  void                  setTexCoords ( Float32ArrayPtr );
  void                  setTexCoords ( const std::initializer_list < float > & );

  // Add/remove/get the primitives.
  void          addPrimitives    ( PrimitiveSet * );
  void          addPrimitives    ( PrimitiveSetPtr );
  void          removePrimitives ( PrimitiveSet * );
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
