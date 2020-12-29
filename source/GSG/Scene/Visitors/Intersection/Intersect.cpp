
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

#include "GSG/Scene/Visitors/Intersection/Intersect.h"

#include "Usul/Tools/NoThrow.h"

#include <functional>


namespace GSG {
namespace Scene {
namespace Visitors {
namespace Intersection {


// Add the boilerplate code.
GSG_IMPLEMENT_VISITOR_CLASS ( Intersect );


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor.
//
///////////////////////////////////////////////////////////////////////////////

Intersect::Intersect() : BaseClass()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor.
//
///////////////////////////////////////////////////////////////////////////////

Intersect::~Intersect()
{
  USUL_TOOLS_NO_THROW ( 1608769716, std::bind ( &Intersect::_destroyIntersect, this ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destroy this instance.
//
///////////////////////////////////////////////////////////////////////////////

void Intersect::_destroyIntersect()
{
}


} // namespace Intersection
} // namespace Visitors
} // namespace Scene
} // namespace GSG
