
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2020, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Thread-safe sequence container class.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _GENERIC_SCENE_GRAPH_BASE_CONTAINERS_SEQUENCE_CLASS_H_
#define _GENERIC_SCENE_GRAPH_BASE_CONTAINERS_SEQUENCE_CLASS_H_

#include "GSG/Config.h"

#ifdef GSG_USE_IMMER_CONTAINERS
#include <immer/flex_vector.hpp>
#include <immer/vector.hpp>
#else
#include <vector>
#endif

#include <functional>
#include <initializer_list>
#include <mutex>


namespace GSG {
namespace Base {
namespace Containers {


template < class T > class Sequence
{
public:

  #ifdef GSG_USE_IMMER_CONTAINERS
  typedef typename immer::vector < T > InternalVectorType;
  #else
  typedef typename std::vector < T > InternalVectorType;
  #endif

  typedef Sequence < T > ThisType;
  typedef std::mutex Mutex;
  typedef std::lock_guard < Mutex > Guard;
  typedef typename InternalVectorType::value_type value_type;
  typedef typename InternalVectorType::size_type size_type;
  typedef typename InternalVectorType::iterator iterator;
  typedef typename InternalVectorType::const_iterator const_iterator;

  typedef std::function < void ( const T & ) > ConstCallback;
  typedef std::function < void ( T & ) > Callback;

  Sequence();
  Sequence ( const std::initializer_list < T > values );
  Sequence ( const Sequence &s );
  ~Sequence();

  Sequence &operator = ( const Sequence & );

  bool operator == ( const Sequence &rhs ) const { return (  true == this->equal ( rhs ) ); }
  bool operator != ( const Sequence &rhs ) const { return ( false == this->equal ( rhs ) ); }

  bool empty() const { return _v.empty(); }
  bool equal ( const Sequence &s ) const;
  void erase ( size_type );

  void forEach ( ConstCallback ) const;
  void forEach ( Callback );

  // Use with caution.
  const InternalVectorType &getInternalVector() const { return _v; }
  InternalVectorType &      getInternalVector()       { return _v; }

  void push_front ( const T &v );
  void push_back  ( const T &v );

  size_type size() const { return _v.size(); }

private:

  InternalVectorType _v;
  mutable Mutex _mutex;
};


///////////////////////////////////////////////////////////////////////////////
//
//  Constructors.
//
///////////////////////////////////////////////////////////////////////////////

template < class T > inline Sequence<T>::Sequence() :
  _v(),
  _mutex()
{
}
template < class T > inline Sequence<T>::Sequence ( const std::initializer_list < T > values ) :
  _v ( values ),
  _mutex()
{
}
template < class T > inline Sequence<T>::Sequence ( const Sequence &s ) :
  _v ( s._v ),
  _mutex()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor.
//
///////////////////////////////////////////////////////////////////////////////

template < class T > inline Sequence<T>::~Sequence()
{
  _v = InternalVectorType();
}


///////////////////////////////////////////////////////////////////////////////
//
//  Assignment.
//
///////////////////////////////////////////////////////////////////////////////

template < class T > inline Sequence<T> &Sequence<T>::operator = ( const Sequence &s )
{
  Guard guard ( _mutex );
  _v = s._v;
  return *this;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Are they equal?
//
///////////////////////////////////////////////////////////////////////////////

template < class T > inline bool Sequence<T>::equal ( const Sequence &s ) const
{
  Guard guard1 ( _mutex );
  Guard guard2 ( s._mutex );
  return ( _v == s._v );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Erase at the position.
//
///////////////////////////////////////////////////////////////////////////////

template < class T > inline void Sequence<T>::erase ( size_type index )
{
  Guard guard ( _mutex );
  #ifdef GSG_USE_IMMER_CONTAINERS
  {
    typedef immer::flex_vector < T > FlexVector;
    FlexVector f ( _v );
    f = f.erase ( index );
    _v = InternalVectorType ( f.begin(), f.end() );
  }
  #else
  {
    _v.erase ( index );
  }
  #endif
}


///////////////////////////////////////////////////////////////////////////////
//
//  Iterate through the values.
//
///////////////////////////////////////////////////////////////////////////////

template < class T > inline void Sequence<T>::forEach ( ConstCallback fun ) const
{
  // Guard the copying of the internal vector.
  // If we are using immer then this will be fast.
  InternalVectorType v;
  {
    Guard guard ( _mutex );
    v = _v;
  }

  // Now loop through the copy.
  for ( const_iterator i = v.begin(); i != v.end(); ++i )
  {
    fun ( *i );
  }
}
template < class T > inline void Sequence<T>::forEach ( Callback fun )
{
  // Guard the copying of the internal vector.
  // If we are using immer then this will be fast.
  InternalVectorType v;
  {
    Guard guard ( _mutex );
    v = _v;
  }

  // Now loop through the copy.
  for ( iterator i = v.begin(); i != v.end(); ++i )
  {
    #ifdef GSG_USE_IMMER_CONTAINERS

    // Need a copy to lose the const if using immer.
    T temp = *i;
    fun ( temp );

    // Did the value change?
    // if ( temp != *i )
    // {
    //   *i = temp; // Does not compile because all iterators are const.
    // }

    #else

    fun ( *i );

    #endif
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Push to the front and back.
//
///////////////////////////////////////////////////////////////////////////////

template < class T > inline void Sequence<T>::push_front ( const T &v )
{
  Guard guard ( _mutex );
  #ifdef GSG_USE_IMMER_CONTAINERS
  {
    typedef immer::flex_vector < T > FlexVector;
    FlexVector f ( _v );
    f = f.push_front ( v );
    _v = InternalVectorType ( f.begin(), f.end() );
  }
  #else
  {
    _v.push_front ( v );
  }
  #endif
}
template < class T > inline void Sequence<T>::push_back ( const T &v )
{
  Guard guard ( _mutex );
  #ifdef GSG_USE_IMMER_CONTAINERS
  {
    _v = _v.push_back  ( v );
  }
  #else
  {
    _v.push_back ( v );
  }
  #endif
}


} // namespace Containers
} // namespace Base
} // namespace GSG


#endif // _GENERIC_SCENE_GRAPH_BASE_CONTAINERS_SEQUENCE_CLASS_H_
