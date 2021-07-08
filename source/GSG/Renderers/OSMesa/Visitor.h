
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2021, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Renderer visitor.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _GSG_RENDERERS_OSMESA_VISITOR_CLASS_H_
#define _GSG_RENDERERS_OSMESA_VISITOR_CLASS_H_

#include "GSG/Scene/Visitors/Visitor.h"


namespace GSG {
namespace Renderers {
namespace OSMesa {


class GSG_SCENE_EXPORT Visitor : public GSG::Scene::Visitors::Visitor
{
public:

  GSG_DECLARE_VISITOR_CLASS ( Visitor );

  typedef GSG::Scene::Visitors::Visitor BaseClass;
  typedef BaseClass::PropertyMap PropertyMap;

protected:

  Visitor();
  virtual ~Visitor();

private:

  void _destroyVisitor();
};


} // namespace OSMesa
} // namespace Renderers
} // namespace GSG


#endif // _GSG_RENDERERS_OSMESA_VISITOR_CLASS_H_
