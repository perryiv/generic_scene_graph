
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2020, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Base class for all scene visitors.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _GENERIC_SCENE_GRAPH_VISITORS_VISITOR_CLASS_H_
#define _GENERIC_SCENE_GRAPH_VISITORS_VISITOR_CLASS_H_

#include "GSG/Base/Object.h"
#include "GSG/Forward.h"

#define GSG_DECLARE_VISITOR_CLASS(class_name) \
  GSG_DECLARE_OBJECT_CLASS ( class_name )

#define GSG_IMPLEMENT_VISITOR_CLASS(class_name) \
  GSG_IMPLEMENT_OBJECT_CLASS ( class_name )


namespace GSG {
namespace Visitors {


class GSG_EXPORT Visitor : public GSG::Base::Object
{
public:

  GSG_DECLARE_VISITOR_CLASS ( Visitor );

  typedef GSG::Base::Object BaseClass;

  virtual void visit ( GSG::Scene::Nodes::Groups::Group & );
  virtual void visit ( GSG::Scene::Nodes::Node & );

protected:

  Visitor();
  virtual ~Visitor();

private:

  void _destroyVisitor();
};


} // namespace Visitors
} // namespace GSG


#endif // _GENERIC_SCENE_GRAPH_VISITORS_VISITOR_CLASS_H_
