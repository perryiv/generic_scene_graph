
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2020, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Base class for all scene-graph shape nodes.
//
///////////////////////////////////////////////////////////////////////////////

#include "GSG/Scene/Nodes/Shapes/Shape.h"
#include "GSG/Visitors/Visitor.h"

#include "Usul/Tools/NoThrow.h"

#include <functional>


namespace GSG {
namespace Scene {
namespace Nodes {
namespace Shapes {


// Add the boilerplate code.
GSG_IMPLEMENT_NODE_CLASS ( Shape );


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor.
//
///////////////////////////////////////////////////////////////////////////////

Shape::Shape() : BaseClass()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor.
//
///////////////////////////////////////////////////////////////////////////////

Shape::~Shape()
{
  USUL_TOOLS_NO_THROW ( 1608015018, std::bind ( &Shape::_destroyShape, this ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destroy this instance.
//
///////////////////////////////////////////////////////////////////////////////

void Shape::_destroyShape()
{
}


} // namespace Shapes
} // namespace Nodes
} // namespace Scene
} // namespace GSG
