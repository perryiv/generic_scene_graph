
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2021, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Cull visitor.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _GSG_TOOLS_VISITORS_CULL_VISITOR_CLASS_H_
#define _GSG_TOOLS_VISITORS_CULL_VISITOR_CLASS_H_

#include "GSG/Config.h"
#include "GSG/Scene/Forward.h"
#include "GSG/Scene/Visitors/Visitor.h"
#include "GSG/Tools/Export.h"
#include "GSG/Tools/Tree/Root.h"


namespace GSG {
namespace Tools {
namespace Visitors {
namespace Cull {


class GSG_TOOLS_EXPORT Visitor : public GSG::Scene::Visitors::Visitor
{
public:

  GSG_DECLARE_VISITOR_CLASS ( Visitor );

  typedef GSG::Scene::Visitors::Visitor BaseClass;
  typedef BaseClass::PropertyMap PropertyMap;
  typedef GSG::Tools::Tree::Root Root;

  // Constructor.
  Visitor();

  // Cull the scene.
  void cull ( GSG::Scene::Nodes::Node * );
  void cull ( GSG::Scene::Nodes::Node *, PropertyMap & );
  void cull ( GSG::Scene::Nodes::Node *, PropertyMap::Values & );

protected:

  // Use reference counting.
  virtual ~Visitor();

  virtual void visit ( GSG::Scene::Nodes::Groups::Transform &, PropertyMap & ) override;
  virtual void visit ( GSG::Scene::Nodes::Groups::Group &, PropertyMap & ) override;
  virtual void visit ( GSG::Scene::Nodes::Node &, PropertyMap & ) override;
  virtual void visit ( GSG::Scene::Nodes::Shapes::Geometry &, PropertyMap & ) override;
  virtual void visit ( GSG::Scene::Nodes::Shapes::Shape &, PropertyMap & ) override;

private:

  void _destroyVisitor();

  Root::ValidAccessRefPtr _root;
};


} // namespace Cull
} // namespace Visitors
} // namespace Tools
} // namespace GSG


#endif // _GSG_TOOLS_VISITORS_CULL_VISITOR_CLASS_H_
