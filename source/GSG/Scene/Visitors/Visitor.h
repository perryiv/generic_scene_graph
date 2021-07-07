
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2021, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Base class for all scene visitors.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _GSG_VISITORS_VISITOR_CLASS_H_
#define _GSG_VISITORS_VISITOR_CLASS_H_

#include "GSG/Config.h"

#include "GSG/Base/Objects/Object.h"

#include "GSG/Scene/Export.h"
#include "GSG/Scene/Forward.h"

#include "Usul/Properties/Map.h"

#define GSG_DECLARE_VISITOR_CLASS(class_name) \
  GSG_DECLARE_OBJECT_CLASS ( class_name )

#define GSG_IMPLEMENT_VISITOR_CLASS(class_name) \
  GSG_IMPLEMENT_OBJECT_CLASS ( class_name )


namespace GSG {
namespace Scene {
namespace Visitors {


class GSG_SCENE_EXPORT Visitor : public GSG::Base::Objects::Object
{
public:

  GSG_DECLARE_VISITOR_CLASS ( Visitor );

  typedef GSG::Base::Objects::Object BaseClass;
  typedef Usul::Properties::Map PropertyMap;

  virtual void visit ( const GSG::Scene::Nodes::Groups::Transform &, PropertyMap & );
  virtual void visit ( const GSG::Scene::Nodes::Groups::Group &, PropertyMap & );
  virtual void visit ( const GSG::Scene::Nodes::Node &, PropertyMap & );
  virtual void visit ( const GSG::Scene::Nodes::Shapes::Geometry &, PropertyMap & );
  virtual void visit ( const GSG::Scene::Nodes::Shapes::Shape &, PropertyMap & );

  virtual void visit ( GSG::Scene::Nodes::Groups::Transform &, PropertyMap & );
  virtual void visit ( GSG::Scene::Nodes::Groups::Group &, PropertyMap & );
  virtual void visit ( GSG::Scene::Nodes::Node &, PropertyMap & );
  virtual void visit ( GSG::Scene::Nodes::Shapes::Geometry &, PropertyMap & );
  virtual void visit ( GSG::Scene::Nodes::Shapes::Shape &, PropertyMap & );

protected:

  Visitor();
  virtual ~Visitor();

private:

  void _destroyVisitor();
};


} // namespace Visitors
} // namespace Scene
} // namespace GSG


#endif // _GSG_VISITORS_VISITOR_CLASS_H_
