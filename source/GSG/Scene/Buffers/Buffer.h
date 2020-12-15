
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
#include "GSG/Forward.h"

#include <mutex>


namespace GSG {
namespace Scene {
namespace Buffers {


class GSG_EXPORT Buffer : public GSG::Base::Objects::Object
{
public:

  typedef GSG::Base::Objects::Object BaseClass;
  typedef std::recursive_mutex Mutex;
  typedef std::lock_guard < Mutex > Guard;

  GSG_DECLARE_OBJECT_CLASS ( Buffer );

  // Constructor
  Buffer();

protected:

  virtual ~Buffer();

private:

  void _destroyBuffer();
};


} // namespace Buffers
} // namespace Scene
} // namespace GSG


#endif // _GENERIC_SCENE_GRAPH_NODES_BUFFERS_BUFFER_CLASS_H_
