
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2020, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Group node with a transformation matrix.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _GSG_NODES_GROUPS_TRANSFORM_CLASS_H_
#define _GSG_NODES_GROUPS_TRANSFORM_CLASS_H_

#include "GSG/Scene/Nodes/Groups/Group.h"

#include "Usul/Math/Matrix44.h"


namespace GSG {
namespace Scene {
namespace Nodes {
namespace Groups {


class GSG_SCENE_EXPORT Transform : public GSG::Scene::Nodes::Groups::Group
{
public:

  typedef GSG::Scene::Nodes::Groups::Group BaseClass;
  typedef BaseClass::Mutex Mutex;
  typedef BaseClass::Guard Guard;
  typedef Usul::Math::Matrix44d Matrix44d;

  GSG_DECLARE_NODE_CLASS ( Transform );

  // Constructor
  Transform();
  Transform ( const Matrix44d & );

  // Get/set the matrix.
  Matrix44d getMatrix() const;
  void      setMatrix ( const Matrix44d & );

protected:

  friend class GSG::Scene::Visitors::Visitor;

  virtual ~Transform();

  // Have the visitor traverse the children.
  virtual void _traverseConst  ( GSG::Scene::Visitors::Visitor &, PropertyMap & ) const override;
  virtual void _traverseModify ( GSG::Scene::Visitors::Visitor &, PropertyMap & ) override;

private:

  void _destroyTransform();

  Matrix44d _matrix;
};


} // namespace Groups
} // namespace Nodes
} // namespace Scene
} // namespace GSG


#endif // _GSG_NODES_GROUPS_TRANSFORM_CLASS_H_
