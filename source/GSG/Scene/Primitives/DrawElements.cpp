
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2021, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Primitive set that draws the arrays using indices.
//
///////////////////////////////////////////////////////////////////////////////

#include "GSG/Scene/Primitives/DrawElements.h"

#include "Usul/Tools/NoThrow.h"

#include <functional>


namespace GSG {
namespace Scene {
namespace Primitives {


// Add the boilerplate code.
GSG_IMPLEMENT_PRIMITIVE_CLASS ( DrawElements )


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor.
//
///////////////////////////////////////////////////////////////////////////////

DrawElements::DrawElements ( unsigned int mode ) : BaseClass ( mode )
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor.
//
///////////////////////////////////////////////////////////////////////////////

DrawElements::~DrawElements()
{
  USUL_TOOLS_NO_THROW ( 1608543505, std::bind ( &DrawElements::_destroyDrawElements, this ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destroy this instance.
//
///////////////////////////////////////////////////////////////////////////////

void DrawElements::_destroyDrawElements()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Implement the concrete classes.
//
///////////////////////////////////////////////////////////////////////////////

GSG_IMPLEMENT_DRAW_ELEMENTS_CLASS ( DrawElementsUint8,  1608611520 )
GSG_IMPLEMENT_DRAW_ELEMENTS_CLASS ( DrawElementsUint16, 1608611521 )
GSG_IMPLEMENT_DRAW_ELEMENTS_CLASS ( DrawElementsUint32, 1608611522 )
GSG_IMPLEMENT_DRAW_ELEMENTS_CLASS ( DrawElementsUint64, 1608611523 )


} // namespace Primitives
} // namespace Scene
} // namespace GSG
