
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

#include "GSG/Renderers/OSMesa/Renderer.h"
#include "GSG/Scene/Nodes/Node.h"

#include "Usul/Tools/NoThrow.h"

#include <functional>
#include <limits>
#include <type_traits>


namespace GSG {
namespace Renderers {
namespace OSMesa {


// Add the boilerplate code.
GSG_IMPLEMENT_VISITOR_CLASS ( Renderer )


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor.
//
///////////////////////////////////////////////////////////////////////////////

Renderer::Renderer() : BaseClass(),
  _context ( nullptr ),
  _buffer(),
  _size ( 0, 0 )
{
  static_assert ( std::is_same < int, GLsizei > ::value, "GLsizei is not an int" );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor.
//
///////////////////////////////////////////////////////////////////////////////

Renderer::~Renderer()
{
  USUL_TOOLS_NO_THROW ( 1625691959, std::bind ( &Renderer::_destroyRenderer, this ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destroy this instance.
//
///////////////////////////////////////////////////////////////////////////////

void Renderer::_destroyRenderer()
{
  if ( nullptr != _context )
  {
    ::OSMesaDestroyContext ( _context );
    _context = nullptr;
  }

  _buffer.clear();
}


///////////////////////////////////////////////////////////////////////////////
//
//  Resize the in-memory canvas.
//
///////////////////////////////////////////////////////////////////////////////

void Renderer::resize ( unsigned int width, unsigned int height )
{
  typedef std::numeric_limits < GLsizei > Limits;
  constexpr unsigned int mx = static_cast < unsigned int > ( Limits::max() );

  if ( ( width > mx ) || ( height > mx ) )
  {
    return;
  }

  _size.set ( width, height );
  _buffer.resize ( width * height * 4 );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Render the scene.
//
///////////////////////////////////////////////////////////////////////////////

void Renderer::render ( GSG::Scene::Nodes::Node *node )
{
  if ( nullptr == node )
  {
    return;
  }

  if ( nullptr == _context )
  {
    return;
  }

  if ( true == _buffer.empty() )
  {
    return;
  }

  ::OSMesaMakeCurrent ( _context, &_buffer[0], GL_UNSIGNED_BYTE,
    static_cast < GLsizei > ( _size[0] ),
    static_cast < GLsizei > ( _size[1] ) );

  node->accept ( *this );
}


} // namespace OSMesa
} // namespace Renderers
} // namespace GSG
