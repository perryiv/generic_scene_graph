
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

#include "GSG/Render/OSMesa/Export.h"
#include "GSG/Scene/Visitors/Visitor.h"
#include "GSG/Scene/Forward.h"

#include "Usul/Math/Vector2.h"

#include "GL/osmesa.h"

#include <vector>


namespace GSG {
namespace Renderers {
namespace OSMesa {


class GSG_RENDERER_OSMESA_EXPORT Renderer : public GSG::Scene::Visitors::Visitor
{
public:

  GSG_DECLARE_VISITOR_CLASS ( Renderer );

  typedef GSG::Scene::Visitors::Visitor BaseClass;
  typedef BaseClass::PropertyMap PropertyMap;
  typedef std::vector < unsigned char > Buffer;
  typedef Usul::Math::Vec2ui Size;

  // Constructor.
  Renderer();

  // Resize the in-memory canvas.
  void resize ( unsigned int width, unsigned int height );

  // Render the scene.
  void render ( GSG::Scene::Nodes::Node * );
  void render ( GSG::Scene::Nodes::Node *, PropertyMap & );

  // Get the buffer.
  const Buffer &getBuffer() const { return _buffer; }

protected:

  // Use reference counting.
  virtual ~Renderer();

  virtual void visit ( GSG::Scene::Nodes::Groups::Transform &, PropertyMap & ) override;
  virtual void visit ( GSG::Scene::Nodes::Groups::Group &, PropertyMap & ) override;
  virtual void visit ( GSG::Scene::Nodes::Node &, PropertyMap & ) override;
  virtual void visit ( GSG::Scene::Nodes::Shapes::Geometry &, PropertyMap & ) override;
  virtual void visit ( GSG::Scene::Nodes::Shapes::Shape &, PropertyMap & ) override;

  void _cull ( GSG::Scene::Nodes::Node *, PropertyMap & );
  void _draw ( PropertyMap & );

  void _processLayers();

private:

  void _destroyRenderer();

  ::OSMesaContext _context;
  Buffer _buffer;
  Size _size;
};


} // namespace OSMesa
} // namespace Renderers
} // namespace GSG


#endif // _GSG_RENDERERS_OSMESA_VISITOR_CLASS_H_
