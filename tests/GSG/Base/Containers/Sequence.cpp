
////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2020, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//  Test the sequence.
//
////////////////////////////////////////////////////////////////////////////////

#include "GSG/Base/Containers/Sequence.h"

#include "catch2/catch.hpp"


////////////////////////////////////////////////////////////////////////////////
//
//  Test the sequence.
//
////////////////////////////////////////////////////////////////////////////////

TEMPLATE_TEST_CASE ( "Sequence container", "",
  char, short, int, long,
  unsigned char, unsigned short, unsigned int, unsigned long,
  float, double, ( long double ) )
{
  typedef GSG::Base::Containers::Sequence < TestType > Sequence;
  typedef typename Sequence::InternalVectorType InternalVectorType;

  SECTION ( "Can push values onto the front and back" )
  {
    Sequence s1;
    REQUIRE ( 0 == s1.size() );

    s1.push_back ( 30 );
    REQUIRE ( 1 == s1.size() );

    s1.push_back ( 40 );
    REQUIRE ( 2 == s1.size() );

    s1.push_front ( 20 );
    REQUIRE ( 3 == s1.size() );

    s1.push_front ( 10 );
    REQUIRE ( 4 == s1.size() );

    REQUIRE ( InternalVectorType ( { 10, 20, 30, 40 } ) == s1.getInternalVector() );
  }
}
