
////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2021, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//  Test the array class.
//
////////////////////////////////////////////////////////////////////////////////

#include "GSG/Base/Containers/Array.h"

#include "catch2/catch.hpp"

#include <cstdint>

#define TT static_cast < TestType >


////////////////////////////////////////////////////////////////////////////////
//
//  Test the array.
//
////////////////////////////////////////////////////////////////////////////////

TEMPLATE_TEST_CASE ( "Array container", "",
  std::int8_t,
  std::int16_t,
  std::int32_t,
  std::int64_t,
  std::uint8_t,
  std::uint16_t,
  std::uint32_t,
  std::uint64_t,
  float,
  double,
  ( long double ) )
{
  typedef GSG::Base::Containers::Array < TestType > Array;
  typedef typename Array::InternalVectorType InternalVectorType;
  typedef typename Array::value_type value_type;

  SECTION ( "Default constructor" )
  {
    Array *a = new Array;
    REQUIRE ( 0 == a->size() );
    REQUIRE ( true == a->empty() );
    REQUIRE ( InternalVectorType() == a->getInternalVector() );
  }

  SECTION ( "Initialize list constructor" )
  {
    Array *a = new Array ( { 10, 20, 30, 40 } );
    REQUIRE ( 4 == a->size() );
    REQUIRE ( false == a->empty() );
    REQUIRE ( InternalVectorType ( { 10, 20, 30, 40 } ) == a->getInternalVector() );
  }

  SECTION ( "Internal vector constructor" )
  {
    const InternalVectorType input ( { 10, 20, 30, 40 } );
    Array *a = new Array ( input );
    REQUIRE ( 4 == a->size() );
    REQUIRE ( false == a->empty() );
    REQUIRE ( input == a->getInternalVector() );
  }

  SECTION ( "Swap contents" )
  {
    Array *a1 = new Array ( { 10, 20, 30, 40 } );
    REQUIRE ( 4 == a1->size() );
    REQUIRE ( false == a1->empty() );
    REQUIRE ( InternalVectorType ( { 10, 20, 30, 40 } ) == a1->getInternalVector() );

    Array *a2 = new Array;
    REQUIRE ( 0 == a2->size() );
    REQUIRE ( true == a2->empty() );
    REQUIRE ( InternalVectorType() == a2->getInternalVector() );

    a1->swap ( *a2 );

    REQUIRE ( 0 == a1->size() );
    REQUIRE ( true == a1->empty() );
    REQUIRE ( InternalVectorType() == a1->getInternalVector() );

    REQUIRE ( 4 == a2->size() );
    REQUIRE ( false == a2->empty() );
    REQUIRE ( InternalVectorType ( { 10, 20, 30, 40 } ) == a2->getInternalVector() );
  }

  SECTION ( "Can push values onto the front and back" )
  {
    Array *a = new Array;
    REQUIRE ( 0 == a->size() );
    REQUIRE ( true == a->empty() );

    a->push_back ( 30 );
    REQUIRE ( 1 == a->size() );
    REQUIRE ( false == a->empty() );

    a->push_back ( 40 );
    REQUIRE ( 2 == a->size() );
    REQUIRE ( false == a->empty() );

    a->push_front ( 20 );
    REQUIRE ( 3 == a->size() );
    REQUIRE ( false == a->empty() );

    a->push_front ( 10 );
    REQUIRE ( 4 == a->size() );
    REQUIRE ( false == a->empty() );

    REQUIRE ( InternalVectorType ( { 10, 20, 30, 40 } ) == a->getInternalVector() );
  }

  SECTION ( "Can remove values" )
  {
    Array *a = new Array ( { 10, 20, 30, 40 } );
    REQUIRE ( InternalVectorType ( { 10, 20, 30, 40 } ) == a->getInternalVector() );

    a->erase ( 0 );
    REQUIRE ( InternalVectorType ( { 20, 30, 40 } ) == a->getInternalVector() );

    a->erase ( 1 );
    REQUIRE ( InternalVectorType ( { 20, 40 } ) == a->getInternalVector() );

    a->erase ( 8 ); // Gets clamped to last position.
    REQUIRE ( InternalVectorType ( { 20 } ) == a->getInternalVector() );

    a->erase ( 0 );
    REQUIRE ( InternalVectorType() == a->getInternalVector() );
  }

  SECTION ( "Can iterate through the values" )
  {
    const InternalVectorType input = { TT ( 10 ), TT ( 20 ), TT ( 30 ), TT ( 40 ) };
    const Array *a = new Array ( input );

    auto expected = input.begin();
    a->forEach ( [ &expected ] ( const value_type &value )
    {
      REQUIRE ( *expected == value );
      ++expected;
    } );
  }

  SECTION ( "Can iterate through the values and change them" )
  {
    const InternalVectorType input = { TT ( 10 ), TT ( 20 ), TT ( 30 ), TT ( 40 ) };
    Array *a = new Array ( input );

    a->forEach ( [] ( value_type &value )
    {
      // The static_cast keeps gcc 9 and earlier happy.
      value = static_cast < value_type > ( value + value );
    } );

    auto expected = input.begin();
    a->forEach ( [ &expected ] ( const value_type &value )
    {
      REQUIRE ( ( *expected + *expected ) == value );
      ++expected;
    } );
  }
}
