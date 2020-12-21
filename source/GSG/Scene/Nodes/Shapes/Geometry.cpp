
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

#include "GSG/Scene/Nodes/Shapes/Geometry.h"
#include "GSG/Scene/Visitors/Visitor.h"

#include "Usul/Tools/NoThrow.h"

#include <algorithm>
#include <functional>


namespace GSG {
namespace Scene {
namespace Nodes {
namespace Shapes {


// Add the boilerplate code.
GSG_IMPLEMENT_NODE_CLASS ( Geometry );


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor.
//
///////////////////////////////////////////////////////////////////////////////

Geometry::Geometry() : BaseClass(),
  _points(),
  _normals(),
  _colors(),
  _texCoords(),
  _primitives()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor.
//
///////////////////////////////////////////////////////////////////////////////

Geometry::~Geometry()
{
  USUL_TOOLS_NO_THROW ( 1608015315, std::bind ( &Geometry::_destroyGeometry, this ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destroy this instance.
//
///////////////////////////////////////////////////////////////////////////////

void Geometry::_destroyGeometry()
{
  _points     = Float32ArrayPtr();
  _normals    = Float32ArrayPtr();
  _colors     = Float32ArrayPtr();
  _texCoords  = Float32ArrayPtr();
  _primitives = PrimitiveSets();
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get/set the colors.
//
///////////////////////////////////////////////////////////////////////////////

const Geometry::Float32ArrayPtr Geometry::getColors() const
{
  Guard guard ( this->mutex() );
  return _colors;
}
Geometry::Float32ArrayPtr Geometry::getColors()
{
  Guard guard ( this->mutex() );
  return _colors;
}
void Geometry::setColors ( Float32ArrayPtr colors )
{
  Guard guard ( this->mutex() );
  _colors = colors;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get/set the normals.
//
///////////////////////////////////////////////////////////////////////////////

const Geometry::Float32ArrayPtr Geometry::getNormals() const
{
  Guard guard ( this->mutex() );
  return _normals;
}
Geometry::Float32ArrayPtr Geometry::getNormals()
{
  Guard guard ( this->mutex() );
  return _normals;
}
void Geometry::setNormals ( Float32ArrayPtr normals )
{
  Guard guard ( this->mutex() );
  _normals = normals;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get/set the points.
//
///////////////////////////////////////////////////////////////////////////////

const Geometry::Float32ArrayPtr Geometry::getPoints() const
{
  Guard guard ( this->mutex() );
  return _points;
}
Geometry::Float32ArrayPtr Geometry::getPoints()
{
  Guard guard ( this->mutex() );
  return _points;
}
void Geometry::setPoints ( Float32ArrayPtr points )
{
  Guard guard ( this->mutex() );
  _points = points;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get/set the texture coordinates.
//
///////////////////////////////////////////////////////////////////////////////

const Geometry::Float32ArrayPtr Geometry::getTexCoords() const
{
  Guard guard ( this->mutex() );
  return _texCoords;
}
Geometry::Float32ArrayPtr Geometry::getTexCoords()
{
  Guard guard ( this->mutex() );
  return _texCoords;
}
void Geometry::setTexCoords ( Float32ArrayPtr texCoords )
{
  Guard guard ( this->mutex() );
  _texCoords = texCoords;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Add/remove/get the primitives.
//
///////////////////////////////////////////////////////////////////////////////

void Geometry::addPrimitives ( PrimitiveSetPtr primitives )
{
  if ( true == primitives.valid() )
  {
    Guard guard ( this->mutex() );
    _primitives = _primitives.push_back ( primitives );
  }
}
void Geometry::removePrimitives ( PrimitiveSetPtr primitives )
{
  Guard guard ( this->mutex() );
  PrimitiveSets v;
  for ( auto i = _primitives.begin(); i != _primitives.end(); ++i )
  {
    if ( i->get() != primitives.get() )
    {
      v = v.push_back ( *i );
    }
  }
  _primitives = v;
}
Geometry::PrimitiveSets Geometry::getPrimitives() const
{
  Guard guard ( this->mutex() );
  return _primitives;
}


} // namespace Shapes
} // namespace Nodes
} // namespace Scene
} // namespace GSG
