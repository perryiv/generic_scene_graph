
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2020, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Primitive set that draws the arrays using indices.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _GENERIC_SCENE_GRAPH_PRIMITIVES_DRAW_ELEMENTS_CLASS_H_
#define _GENERIC_SCENE_GRAPH_PRIMITIVES_DRAW_ELEMENTS_CLASS_H_

#include "GSG/Scene/Primitives/PrimitiveSet.h"
#include "GSG/Base/Containers/TypedArrays.h"


#define GSG_DECLARE_DRAW_ELEMENTS_CLASS(class_name,indices_type) \
  class GSG_EXPORT class_name : public DrawElements \
  { \
  public: \
    typedef DrawElements BaseClass; \
    typedef indices_type IndicesType; \
    typedef IndicesType::ValidAccessRefPtr IndicesTypePtr; \
    GSG_DECLARE_PRIMITIVE_CLASS ( class_name ); \
    class_name() : BaseClass(), _indices() {} \
  protected: \
    virtual ~class_name(); \
  private: \
    void _destroy##class_name(); \
    IndicesTypePtr _indices; \
  }


#define GSG_IMPLEMENT_DRAW_ELEMENTS_CLASS(class_name,id) \
  GSG_IMPLEMENT_PRIMITIVE_CLASS ( class_name ) \
  class_name::~class_name() \
  { \
    USUL_TOOLS_NO_THROW ( id, std::bind ( &class_name::_destroy##class_name, this ) ); \
  } \
  void class_name::_destroy##class_name() \
  { \
    _indices = IndicesTypePtr(); \
  }


namespace GSG {
namespace Scene {
namespace Primitives {


class GSG_EXPORT DrawElements : public PrimitiveSet
{
public:

  typedef PrimitiveSet BaseClass;

  GSG_DECLARE_PRIMITIVE_CLASS ( DrawElements );

protected:

  DrawElements();
  virtual ~DrawElements();

private:

  void _destroyDrawElements();
};


GSG_DECLARE_DRAW_ELEMENTS_CLASS ( DrawElementsUint8,  GSG::Base::Containers::Uint8Array  );
GSG_DECLARE_DRAW_ELEMENTS_CLASS ( DrawElementsUint16, GSG::Base::Containers::Uint16Array );
GSG_DECLARE_DRAW_ELEMENTS_CLASS ( DrawElementsUint32, GSG::Base::Containers::Uint32Array );
GSG_DECLARE_DRAW_ELEMENTS_CLASS ( DrawElementsUint64, GSG::Base::Containers::Uint64Array );


} // namespace Primitives
} // namespace Scene
} // namespace GSG


#endif // _GENERIC_SCENE_GRAPH_PRIMITIVES_DRAW_ELEMENTS_CLASS_H_
