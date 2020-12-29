
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2020, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Base class for all scene intersection visitors.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _GENERIC_SCENE_GRAPH_VISITORS_INTERSECTION_VISITOR_CLASS_H_
#define _GENERIC_SCENE_GRAPH_VISITORS_INTERSECTION_VISITOR_CLASS_H_

#include "GSG/Scene/Visitors/Visitor.h"


namespace GSG {
namespace Scene {
namespace Visitors {
namespace Intersection {


class GSG_EXPORT Intersect : public GSG::Scene::Visitors::Visitor
{
public:

  GSG_DECLARE_VISITOR_CLASS ( Intersect );

  typedef GSG::Scene::Visitors::Visitor BaseClass;

protected:

  Intersect();
  virtual ~Intersect();

private:

  void _destroyIntersect();
};


} // namespace Intersection
} // namespace Visitors
} // namespace Scene
} // namespace GSG


#endif // _GENERIC_SCENE_GRAPH_VISITORS_INTERSECTION_VISITOR_CLASS_H_
