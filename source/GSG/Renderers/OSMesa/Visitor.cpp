
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

#include "GSG/Renderers/OSMesa/Visitor.h"

#include "Usul/Tools/NoThrow.h"

#include <functional>


namespace GSG {
namespace Renderers {
namespace OSMesa {


// Add the boilerplate code.
GSG_IMPLEMENT_VISITOR_CLASS ( Visitor )


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor.
//
///////////////////////////////////////////////////////////////////////////////

Visitor::Visitor() : BaseClass()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor.
//
///////////////////////////////////////////////////////////////////////////////

Visitor::~Visitor()
{
  USUL_TOOLS_NO_THROW ( 1625691959, std::bind ( &Visitor::_destroyVisitor, this ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destroy this instance.
//
///////////////////////////////////////////////////////////////////////////////

void Visitor::_destroyVisitor()
{
}


} // namespace OSMesa
} // namespace Renderers
} // namespace GSG
