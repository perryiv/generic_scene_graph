
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2020, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Specializations of the template array class.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _GENERIC_SCENE_GRAPH_BASE_CONTAINERS_TYPED_ARRAYS_H_
#define _GENERIC_SCENE_GRAPH_BASE_CONTAINERS_TYPED_ARRAYS_H_

#include "GSG/Base/Containers/Array.h"
#include "GSG/Export.h"


#define GSG_DECLARE_ARRAY_TYPE(class_name,number_type) \
  class GSG_EXPORT class_name : public Array < number_type > \
  { \
  public: \
    typedef Array < number_type > BaseClass; \
    typedef BaseClass::initializer_list initializer_list; \
    typedef BaseClass::InternalVectorType InternalVectorType; \
    GSG_DECLARE_OBJECT_CLASS ( class_name ); \
    class_name() : BaseClass() {} \
    class_name ( const initializer_list values ) : BaseClass ( values ) {} \
    class_name ( const InternalVectorType &values ) : BaseClass ( values ) {} \
  protected: \
    virtual ~class_name(); \
  }

#define GSG_DEFINE_ARRAY_TYPE(class_name) \
  GSG_IMPLEMENT_OBJECT_CLASS ( class_name ) \
  class_name::~class_name() { this->clear(); }


namespace GSG {
namespace Base {
namespace Containers {


GSG_DECLARE_ARRAY_TYPE ( Int8Array,    std::int8_t   );
GSG_DECLARE_ARRAY_TYPE ( Uint8Array,   std::uint8_t  );
GSG_DECLARE_ARRAY_TYPE ( Int16Array,   std::int16_t  );
GSG_DECLARE_ARRAY_TYPE ( Uint16Array,  std::uint16_t );
GSG_DECLARE_ARRAY_TYPE ( Int32Array,   std::int32_t  );
GSG_DECLARE_ARRAY_TYPE ( Uint32Array,  std::uint32_t );
GSG_DECLARE_ARRAY_TYPE ( Int64Array,   std::int64_t  );
GSG_DECLARE_ARRAY_TYPE ( Uint64Array,  std::uint64_t );
GSG_DECLARE_ARRAY_TYPE ( Float32Array, float  );
GSG_DECLARE_ARRAY_TYPE ( Float64Array, double );


} // namespace Containers
} // namespace Base
} // namespace GSG


#endif // _GENERIC_SCENE_GRAPH_BASE_CONTAINERS_TYPED_ARRAYS_H_
