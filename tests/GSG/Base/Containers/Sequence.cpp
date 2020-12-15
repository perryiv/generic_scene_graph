
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

#include <vector>

#define TT static_cast < TestType >


////////////////////////////////////////////////////////////////////////////////
//
//  Test the sequence.
//
////////////////////////////////////////////////////////////////////////////////

TEMPLATE_TEST_CASE ( "Sequence container", "",
  // char,
  // short,
  // int,
  // long,
  // unsigned char,
  // unsigned short,
  // unsigned int,
  // unsigned long,
  // float,
  // double,
  ( long double ) )
{
  typedef GSG::Base::Containers::Sequence < TestType > Sequence;
  typedef typename Sequence::InternalVectorType InternalVectorType;
  typedef typename Sequence::value_type value_type;

  SECTION ( "Default constructor" )
  {
    Sequence s1;
    REQUIRE ( 0 == s1.size() );
    REQUIRE ( true == s1.empty() );
    REQUIRE ( InternalVectorType() == s1.getInternalVector() );
  }

  SECTION ( "Initialize list constructor" )
  {
    Sequence s1 ( { 10, 20, 30, 40 } );
    REQUIRE ( 4 == s1.size() );
    REQUIRE ( false == s1.empty() );
    REQUIRE ( InternalVectorType ( { 10, 20, 30, 40 } ) == s1.getInternalVector() );
  }

  SECTION ( "Copy constructor" )
  {
    Sequence s1 ( { 10, 20, 30, 40 } );
    REQUIRE ( 4 == s1.size() );
    REQUIRE ( false == s1.empty() );
    REQUIRE ( InternalVectorType ( { 10, 20, 30, 40 } ) == s1.getInternalVector() );

    Sequence s2 ( s1 );
    REQUIRE ( 4 == s2.size() );
    REQUIRE ( false == s2.empty() );
    REQUIRE ( InternalVectorType ( { 10, 20, 30, 40 } ) == s2.getInternalVector() );
    REQUIRE ( s1 == s2 );
  }

  SECTION ( "Assignment" )
  {
    Sequence s1 ( { 10, 20, 30, 40 } );
    REQUIRE ( 4 == s1.size() );
    REQUIRE ( false == s1.empty() );
    REQUIRE ( InternalVectorType ( { 10, 20, 30, 40 } ) == s1.getInternalVector() );

    Sequence s2 = s1;
    REQUIRE ( 4 == s2.size() );
    REQUIRE ( false == s2.empty() );
    REQUIRE ( InternalVectorType ( { 10, 20, 30, 40 } ) == s2.getInternalVector() );
    REQUIRE ( s1 == s2 );

    Sequence s3 = { 10, 20, 30, 40 };
    REQUIRE ( 4 == s3.size() );
    REQUIRE ( false == s3.empty() );
    REQUIRE ( InternalVectorType ( { 10, 20, 30, 40 } ) == s3.getInternalVector() );
    REQUIRE ( s1 == s3 );
  }

  SECTION ( "Can push values onto the front and back" )
  {
    Sequence s1;
    REQUIRE ( 0 == s1.size() );
    REQUIRE ( true == s1.empty() );

    s1.push_back ( 30 );
    REQUIRE ( 1 == s1.size() );
    REQUIRE ( false == s1.empty() );

    s1.push_back ( 40 );
    REQUIRE ( 2 == s1.size() );
    REQUIRE ( false == s1.empty() );

    s1.push_front ( 20 );
    REQUIRE ( 3 == s1.size() );
    REQUIRE ( false == s1.empty() );

    s1.push_front ( 10 );
    REQUIRE ( 4 == s1.size() );
    REQUIRE ( false == s1.empty() );

    REQUIRE ( InternalVectorType ( { 10, 20, 30, 40 } ) == s1.getInternalVector() );
  }

  SECTION ( "Can remove values" )
  {
    Sequence s1 ( { 10, 20, 30, 40 } );
    REQUIRE ( InternalVectorType ( { 10, 20, 30, 40 } ) == s1.getInternalVector() );

    s1.erase ( 0 );
    REQUIRE ( InternalVectorType ( { 20, 30, 40 } ) == s1.getInternalVector() );

    s1.erase ( 1 );
    REQUIRE ( InternalVectorType ( { 20, 40 } ) == s1.getInternalVector() );

    s1.erase ( 2 ); // Does nothing.
    REQUIRE ( InternalVectorType ( { 20, 40 } ) == s1.getInternalVector() );

    s1.erase ( 0 );
    REQUIRE ( InternalVectorType ( { 40 } ) == s1.getInternalVector() );
  }

  SECTION ( "Can iterate through the values" )
  {
    const auto input = { TT ( 10 ), TT ( 20 ), TT ( 30 ), TT ( 40 ) };
    const Sequence s1 ( input );

    auto expected = input.begin();
    s1.forEach ( [ &expected ] ( const value_type &value )
    {
      REQUIRE ( *expected == value );
      ++expected;
    } );
  }

  // This does not work correctly.

  // SECTION ( "Can iterate through the values and change them" )
  // {
  //   const auto input = { TT ( 10 ), TT ( 20 ), TT ( 30 ), TT ( 40 ) };
  //   Sequence s1 ( input );
  //
  //   s1.forEach ( [] ( value_type &value )
  //   {
  //     value = value + value;
  //   } );
  //
  //   auto expected = input.begin();
  //   s1.forEach ( [ &expected ] ( const value_type &value )
  //   {
  //     REQUIRE ( ( *expected + *expected ) == value );
  //     ++expected;
  //   } );
  // }
}
