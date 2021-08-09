
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2021, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Update visitor.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _GSG_TOOLS_VISITORS_UPDATE_VISITOR_CLASS_H_
#define _GSG_TOOLS_VISITORS_UPDATE_VISITOR_CLASS_H_

#include "GSG/Config.h"
#include "GSG/Scene/Forward.h"
#include "GSG/Scene/Visitors/Visitor.h"
#include "GSG/Tools/Export.h"


namespace GSG {
namespace Tools {
namespace Visitors {
namespace Update {


class GSG_TOOLS_EXPORT Visitor : public GSG::Scene::Visitors::Visitor
{
public:

  GSG_DECLARE_VISITOR_CLASS ( Visitor );

  typedef GSG::Scene::Visitors::Visitor BaseClass;
  typedef BaseClass::PropertyMap PropertyMap;

  // Constructor.
  Visitor();

  // Update the scene.
  void update ( GSG::Scene::Nodes::Node * );
  void update ( GSG::Scene::Nodes::Node *, PropertyMap & );
  void update ( GSG::Scene::Nodes::Node *, PropertyMap::Values & );

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
};


} // namespace Update
} // namespace Visitors
} // namespace Tools
} // namespace GSG


#endif // _GSG_TOOLS_VISITORS_UPDATE_VISITOR_CLASS_H_
