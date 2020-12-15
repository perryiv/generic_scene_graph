
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2020, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Shape node based on vertex buffers.
//
///////////////////////////////////////////////////////////////////////////////

#include "GSG/Scene/Nodes/Shapes/Geometry.h"
#include "GSG/Visitors/Visitor.h"

#include "Usul/Tools/NoThrow.h"

#include <functional>


namespace GSG {
namespace Scene {
namespace Nodes {
namespace Shapes {


// Add the boilerplate code.
GSG_IMPLEMENT_NODE_CLASS ( Geometry );


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor.
//
///////////////////////////////////////////////////////////////////////////////

Geometry::Geometry() : BaseClass()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor.
//
///////////////////////////////////////////////////////////////////////////////

Geometry::~Geometry()
{
  USUL_TOOLS_NO_THROW ( 1608015315, std::bind ( &Geometry::_destroyGeometry, this ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destroy this instance.
//
///////////////////////////////////////////////////////////////////////////////

void Geometry::_destroyGeometry()
{
}


} // namespace Shapes
} // namespace Nodes
} // namespace Scene
} // namespace GSG
