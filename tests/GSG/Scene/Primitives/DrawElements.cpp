
////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2020, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//  Test the primitive set for drawing elements.
//
////////////////////////////////////////////////////////////////////////////////

#include "GSG/Scene/Primitives/DrawElements.h"

#include "catch2/catch.hpp"

typedef GSG::Scene::Primitives::DrawElements DrawElements;
typedef GSG::Scene::Primitives::DrawElementsUint8 DrawElementsUint8;
typedef GSG::Scene::Primitives::DrawElementsUint16 DrawElementsUint16;
typedef GSG::Scene::Primitives::DrawElementsUint32 DrawElementsUint32;
typedef GSG::Scene::Primitives::DrawElementsUint64 DrawElementsUint64;


////////////////////////////////////////////////////////////////////////////////
//
//  Test the primitive set for drawing elements.
//
////////////////////////////////////////////////////////////////////////////////

TEMPLATE_TEST_CASE ( "Primitive set for drawing elements", "",
  DrawElementsUint8,
  DrawElementsUint16,
  DrawElementsUint32,
  DrawElementsUint64 )
{
  typedef TestType DrawElementsType;
  typedef typename DrawElementsType::ValidAccessRefPtr DrawElementsPtr;

  SECTION ( "Default constructor" )
  {
    DrawElementsPtr de = new DrawElementsType;
    REQUIRE ( 1 == de->getReferenceCount() );
  }
}
