
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2020, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Thread-safe dynamic array container class.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _GENERIC_SCENE_GRAPH_BASE_CONTAINERS_ARRAY_CLASS_H_
#define _GENERIC_SCENE_GRAPH_BASE_CONTAINERS_ARRAY_CLASS_H_

#include "GSG/Base/Objects/Object.h"

#include "Usul/Math/Base.h"

#include <functional>
#include <initializer_list>
#include <mutex>
#include <vector>


namespace GSG {
namespace Base {
namespace Containers {


template < class T > class Array : public GSG::Base::Objects::Object
{
public:

  typedef GSG::Base::Objects::Object BaseClass;
  typedef Array < T > ThisType;
  typedef std::mutex Mutex;
  typedef std::lock_guard < Mutex > Guard;
  typedef typename std::vector < T > InternalVectorType;
  typedef typename InternalVectorType::value_type value_type;
  typedef typename InternalVectorType::size_type size_type;
  typedef typename InternalVectorType::difference_type difference_type;
  typedef typename InternalVectorType::iterator iterator;
  typedef typename InternalVectorType::const_iterator const_iterator;
  typedef std::function < void ( const T & ) > ConstCallback;
  typedef std::function < void ( T & ) > Callback;

  Array();
  Array ( const std::initializer_list < T > values );
  Array ( const InternalVectorType & );

  bool operator == ( const Array &rhs ) const { return (  true == this->equal ( rhs ) ); }
  bool operator != ( const Array &rhs ) const { return ( false == this->equal ( rhs ) ); }

  void append  ( const T &v ) { this->push_back  ( v ); }
  void prepend ( const T &v ) { this->push_front ( v ); }

  size_type capacity() const;

  bool empty() const;
  bool equal ( const Array &s ) const;
  void erase ( size_type );

  void forEach ( ConstCallback ) const;
  void forEach ( Callback );

  // Use with caution. Not thread-safe!
  const InternalVectorType &getInternalVector() const { return _v; }
  InternalVectorType &      getInternalVector()       { return _v; }

  void insert ( size_type, const T & );

  // Use with caution.
  Mutex &mutex() { return _mutex; }

  void push_front ( const T &v );
  void push_back  ( const T &v );

  void reserve ( size_type );
  void resize ( size_type );

  size_type size() const;

  void swap ( Array & );
  void swap ( InternalVectorType & );

protected:

  virtual ~Array();

private:

  InternalVectorType _v;
  mutable Mutex _mutex;
};


///////////////////////////////////////////////////////////////////////////////
//
//  Constructors.
//
///////////////////////////////////////////////////////////////////////////////

template < class T > inline Array<T>::Array() : BaseClass(),
  _v(),
  _mutex()
{
}
template < class T > inline Array<T>::Array ( const std::initializer_list < T > values ) : BaseClass(),
  _v ( values ),
  _mutex()
{
}
template < class T > inline Array<T>::Array ( const InternalVectorType &v ) : BaseClass(),
  _v ( v ),
  _mutex()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor.
//
///////////////////////////////////////////////////////////////////////////////

template < class T > inline Array<T>::~Array()
{
  _v = InternalVectorType();
}


///////////////////////////////////////////////////////////////////////////////
//
//  Is it empty?
//
///////////////////////////////////////////////////////////////////////////////

template < class T > inline bool Array<T>::empty() const
{
  Guard guard ( _mutex );
  return _v.empty();
}


///////////////////////////////////////////////////////////////////////////////
//
//  Are they equal?
//
///////////////////////////////////////////////////////////////////////////////

template < class T > inline bool Array<T>::equal ( const Array &s ) const
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

template < class T > inline void Array<T>::erase ( size_type position )
{
  Guard guard ( _mutex );

  if ( true == _v.empty() )
  {
    return;
  }

  position = Usul::Math::clamp < size_type > ( position, 0, _v.size() - 1 );
  iterator itr = _v.begin() + ( static_cast < difference_type > ( position ) );
  _v.erase ( itr );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Iterate through the values.
//
///////////////////////////////////////////////////////////////////////////////

template < class T > inline void Array<T>::forEach ( ConstCallback fun ) const
{
  // Guard the copying of the internal vector.
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
template < class T > inline void Array<T>::forEach ( Callback fun )
{
  // Guard the loop because the callback can modify the value.
  Guard guard ( _mutex );

  // Loop through the container.
  for ( iterator i = _v.begin(); i != _v.end(); ++i )
  {
    fun ( *i );
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Insert before the given position.
//
///////////////////////////////////////////////////////////////////////////////

template < class T > inline void Array<T>::insert ( size_type position, const T &v )
{
  Guard guard ( _mutex );

  if ( true == _v.empty() )
  {
    _v.push_back ( v );
    return;
  }

  position = Usul::Math::clamp < size_type > ( position, 0, _v.size() - 1 );
  iterator itr = _v.begin() + ( static_cast < difference_type > ( position ) );
  _v.insert ( itr, v );
}

///////////////////////////////////////////////////////////////////////////////
//
//  Push to the back or front.
//
///////////////////////////////////////////////////////////////////////////////

template < class T > inline void Array<T>::push_back ( const T &v )
{
  Guard guard ( _mutex );
  _v.push_back ( v );
}
template < class T > inline void Array<T>::push_front ( const T &v )
{
  this->insert ( 0, v );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Return the size.
//
///////////////////////////////////////////////////////////////////////////////

template < class T > inline typename Array<T>::size_type Array<T>::size() const
{
  Guard guard ( _mutex );
  return _v.size();
}


///////////////////////////////////////////////////////////////////////////////
//
//  Swap the contents of the two containers.
//
///////////////////////////////////////////////////////////////////////////////

template < class T > inline void Array<T>::swap ( InternalVectorType &other )
{
  Guard guard ( _mutex );
  _v.swap ( other );
}
template < class T > inline void Array<T>::swap ( Array &other )
{
  Guard guard1 ( _mutex );
  Guard guard2 ( other._mutex );
  _v.swap ( other._v );
}


} // namespace Containers
} // namespace Base
} // namespace GSG


#endif // _GENERIC_SCENE_GRAPH_BASE_CONTAINERS_ARRAY_CLASS_H_
