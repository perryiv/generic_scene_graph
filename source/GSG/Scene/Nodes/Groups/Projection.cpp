
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2021, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Group node with a projection matrix.
//
///////////////////////////////////////////////////////////////////////////////

#include "GSG/Scene/Nodes/Groups/Projection.h"
#include "GSG/Scene/Visitors/Visitor.h"

#include "Usul/Tools/NoThrow.h"

#include <functional>


namespace GSG {
namespace Scene {
namespace Nodes {
namespace Groups {


// Add the boilerplate code.
GSG_IMPLEMENT_NODE_CLASS ( Projection )


///////////////////////////////////////////////////////////////////////////////
//
//  Constants.
//
///////////////////////////////////////////////////////////////////////////////

namespace Details
{
  constexpr Projection::Matrix44d identity (
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
  );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Constructors.
//
///////////////////////////////////////////////////////////////////////////////

Projection::Projection ( const Matrix44d &matrix ) : BaseClass(),
  _matrix ( matrix )
{
}
Projection::Projection() : BaseClass(),
  _matrix()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor.
//
///////////////////////////////////////////////////////////////////////////////

Projection::~Projection()
{
  USUL_TOOLS_NO_THROW ( 1624159548, std::bind ( &Projection::_destroyProjection, this ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destroy this instance.
//
///////////////////////////////////////////////////////////////////////////////

void Projection::_destroyProjection()
{
  this->removeAll();
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get/set the matrix.
//
///////////////////////////////////////////////////////////////////////////////

Projection::Matrix44d Projection::getMatrix() const
{
  Guard guard ( this->mutex() );
  return _matrix;
}
void Projection::setMatrix ( const Matrix44d &matrix )
{
  Guard guard ( this->mutex() );
  _matrix = matrix;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Have the visitor traverse the children.
//
///////////////////////////////////////////////////////////////////////////////

void Projection::_traverseConst ( GSG::Scene::Visitors::Visitor &visitor, PropertyMap &pm ) const
{
  const Matrix44d m1 = pm.get < Matrix44d > ( "projMatrix", Details::identity );
  pm.update ( "projMatrix", ( m1 * _matrix ) );
  BaseClass::_traverseConst ( visitor, pm );
  pm.update ( "projMatrix", m1 );
}
void Projection::_traverseModify ( GSG::Scene::Visitors::Visitor &visitor, PropertyMap &pm )
{
  const Matrix44d m1 = pm.get < Matrix44d > ( "projMatrix", Details::identity );
  pm.update ( "projMatrix", ( m1 * _matrix ) );
  BaseClass::_traverseModify ( visitor, pm );
  pm.update ( "projMatrix", m1 );
}


} // namespace Groups
} // namespace Nodes
} // namespace Scene
} // namespace GSG
