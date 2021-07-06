
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

#ifndef _GSG_VISITORS_INTERSECTION_VISITOR_CLASS_H_
#define _GSG_VISITORS_INTERSECTION_VISITOR_CLASS_H_

#include "GSG/Scene/Visitors/Visitor.h"


namespace GSG {
namespace Scene {
namespace Visitors {
namespace Intersection {


class GSG_SCENE_EXPORT Intersect : public GSG::Scene::Visitors::Visitor
{
public:

  GSG_DECLARE_VISITOR_CLASS ( Intersect );

  typedef GSG::Scene::Visitors::Visitor BaseClass;
  typedef BaseClass::PropertyMap PropertyMap;

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


#endif // _GSG_VISITORS_INTERSECTION_VISITOR_CLASS_H_
