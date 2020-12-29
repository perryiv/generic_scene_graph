# Generic Scene Graph

An attempt to make a scene graph that is easy to understand and use, and decoupled from the rendering technology (e.g.,
[OpenGL](https://www.khronos.org/opengl/),
[Vulkan](https://www.khronos.org/vulkan/),
[OSMesa](https://www.mesa3d.org/osmesa.html),
etc).

## Thread Safety

You should be able to add and remove nodes in one thread while another thread is traversing the graph (e.g., rendering).

This is because the group node makes a light-weight copy of its children (using
[immer](https://github.com/arximboldi/immer)) before iterating over them.

However, modifying existing nodes (that are already part of the graph) in one thread while traversing the graph in another thread will probably not work properly.

## Building

You will need
[Usul](https://github.com/perryiv/usul),
[immer](https://github.com/arximboldi/immer),
[Vulkan](https://vulkan.lunarg.com/sdk/home), and
[CMake](https://cmake.org/)
installed:

    cd /your/path/to/generic_scene_graph
    mkdir build
    cd build
    cmake ..
