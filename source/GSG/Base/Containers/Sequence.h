
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2020, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Sequence container class.
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


namespace GSG {
namespace Base {
namespace Containers {


template < class T > class Sequence
{
public:

  typedef Sequence < T > ThisType;
  #ifdef GSG_USE_IMMER_CONTAINERS
  typedef typename immer::vector < T > InternalVectorType;
  #else
  typedef typename std::vector < T > InternalVectorType;
  #endif
  typedef typename InternalVectorType::value_type value_type;
  typedef typename InternalVectorType::size_type size_type;

  Sequence();
  Sequence ( const Sequence &s );
  ~Sequence();

  Sequence &operator = ( const Sequence & );

  bool empty() const { return _v.empty(); }

  const InternalVectorType &getInternalVector() const { return _v; }
  InternalVectorType &      getInternalVector()       { return _v; }

  void push_front ( const T &v );
  void push_back  ( const T &v );

  size_type size() const { return _v.size(); }

private:

  InternalVectorType _v;
};


///////////////////////////////////////////////////////////////////////////////
//
//  Constructors.
//
///////////////////////////////////////////////////////////////////////////////

template < class T > inline Sequence<T>::Sequence() : _v()
{
}
template < class T > inline Sequence<T>::Sequence ( const Sequence &s ) : _v ( s._v )
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
   _v = s._v;
   return *this;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Push to the front and back.
//
///////////////////////////////////////////////////////////////////////////////

template < class T > inline void Sequence<T>::push_front ( const T &v )
{
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
  #ifdef GSG_USE_IMMER_CONTAINERS
  {
    _v = _v.push_back  ( v );
  }
  #else
  {
    _v.push_front ( v );
  }
  #endif
}


} // namespace Containers
} // namespace Base
} // namespace GSG


#endif // _GENERIC_SCENE_GRAPH_BASE_CONTAINERS_SEQUENCE_CLASS_H_
