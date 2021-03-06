
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2021, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Group node with a transformation matrix.
//
///////////////////////////////////////////////////////////////////////////////

#include "GSG/Scene/Nodes/Groups/Transform.h"
#include "GSG/Scene/Visitors/Visitor.h"

#include "Usul/Tools/NoThrow.h"

#include <functional>


namespace GSG {
namespace Scene {
namespace Nodes {
namespace Groups {


// Add the boilerplate code.
GSG_IMPLEMENT_NODE_CLASS ( Transform )


///////////////////////////////////////////////////////////////////////////////
//
//  Constants.
//
///////////////////////////////////////////////////////////////////////////////

namespace Details
{
  constexpr Transform::Matrix44d identity (
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

Transform::Transform ( const Matrix44d &matrix ) : BaseClass(),
  _matrix ( matrix )
{
}
Transform::Transform() : BaseClass(),
  _matrix()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor.
//
///////////////////////////////////////////////////////////////////////////////

Transform::~Transform()
{
  USUL_TOOLS_NO_THROW ( 1608022445, std::bind ( &Transform::_destroyTransform, this ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destroy this instance.
//
///////////////////////////////////////////////////////////////////////////////

void Transform::_destroyTransform()
{
  this->removeAll();
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get/set the matrix.
//
///////////////////////////////////////////////////////////////////////////////

Transform::Matrix44d Transform::getMatrix() const
{
  Guard guard ( this->mutex() );
  return _matrix;
}
void Transform::setMatrix ( const Matrix44d &matrix )
{
  Guard guard ( this->mutex() );
  _matrix = matrix;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Have the visitor traverse the children.
//
///////////////////////////////////////////////////////////////////////////////

void Transform::_traverseConst ( GSG::Scene::Visitors::Visitor &visitor, PropertyMap &pm ) const
{
  const Matrix44d m1 = pm.get < Matrix44d > ( "viewMatrix", Details::identity );
  pm.update ( "viewMatrix", ( m1 * _matrix ) );
  BaseClass::_traverseConst ( visitor, pm );
  pm.update ( "viewMatrix", m1 );
}
void Transform::_traverseModify ( GSG::Scene::Visitors::Visitor &visitor, PropertyMap &pm )
{
  const Matrix44d m1 = pm.get < Matrix44d > ( "viewMatrix", Details::identity );
  pm.update ( "viewMatrix", ( m1 * _matrix ) );
  BaseClass::_traverseModify ( visitor, pm );
  pm.update ( "viewMatrix", m1 );
}


} // namespace Groups
} // namespace Nodes
} // namespace Scene
} // namespace GSG
