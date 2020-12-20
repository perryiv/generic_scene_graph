
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2020, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Base class for all scene-graph buffer objects.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _GENERIC_SCENE_GRAPH_NODES_BUFFERS_BUFFER_CLASS_H_
#define _GENERIC_SCENE_GRAPH_NODES_BUFFERS_BUFFER_CLASS_H_

#include "GSG/Base/Objects/Object.h"
#include "GSG/Base/Containers/Array.h"
#include "GSG/Forward.h"

#include <mutex>
#include <cstdint>


namespace GSG {
namespace Scene {
namespace Buffers {


class GSG_EXPORT Buffer : public GSG::Base::Objects::Object
{
public:

  typedef GSG::Base::Objects::Object BaseClass;

  GSG_DECLARE_OBJECT_CLASS ( Buffer );

  Buffer();

protected:

  virtual ~Buffer();

private:

  void _destroyBuffer();
};


#define GSG_DECLARE_BUFFER_TYPE(class_name,value_type) \
  class GSG_EXPORT class_name : public Buffer \
  { \
  public: \
    typedef Buffer BaseClass; \
    typedef BaseClass::Mutex Mutex; \
    typedef BaseClass::Guard Guard; \
    typedef GSG::Base::Containers::Array < value_type > Values; \
    GSG_DECLARE_OBJECT_CLASS ( class_name ); \
    class_name() : BaseClass(), _array() {} \
    class_name ( const Array &a ) : BaseClass(), _array ( a ) {} \
    template < class Itr > class_name ( Itr begin, Itr end ) : BaseClass(), _array ( begin, end ) {} \
    void clear() { _array.clear(); } \
    const Values &getValues() const { return _array.getValues(); } \
    Values &      getValues()       { return _array.getValues(); } \
    void getValues ( Values &v )           { _array.getValues ( v ); } \
    void setValues ( const Values &v )     { _array.setValues ( v ); } \
  protected: \
    virtual ~class_name(); \
  private: \
    Array _array; \
  }


#define GSG_DEFINE_BUFFER_TYPE(class_name) \
  GSG_IMPLEMENT_OBJECT_CLASS ( class_name ); \
  class_name::~class_name() { _array.clear(); }


// GSG_DECLARE_BUFFER_TYPE ( Int8Array,    std::int8_t   );
// GSG_DECLARE_BUFFER_TYPE ( Uint8Array,   std::uint8_t  );
// GSG_DECLARE_BUFFER_TYPE ( Int16Array,   std::int16_t  );
// GSG_DECLARE_BUFFER_TYPE ( Uint16Array,  std::uint16_t );
// GSG_DECLARE_BUFFER_TYPE ( Int32Array,   std::int32_t  );
// GSG_DECLARE_BUFFER_TYPE ( Uint32Array,  std::uint32_t );
// GSG_DECLARE_BUFFER_TYPE ( Int64Array,   std::int64_t  );
// GSG_DECLARE_BUFFER_TYPE ( Uint64Array,  std::uint64_t );
// GSG_DECLARE_BUFFER_TYPE ( Float32Array, float  );
// GSG_DECLARE_BUFFER_TYPE ( Float64Array, double );


} // namespace Buffers
} // namespace Scene
} // namespace GSG


#endif // _GENERIC_SCENE_GRAPH_NODES_BUFFERS_BUFFER_CLASS_H_
