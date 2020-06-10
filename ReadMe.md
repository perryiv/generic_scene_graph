# Generic Scene Graph

An attempt to make a scene graph that is easy to understand and use, and decoupled from the rendering technology (e.g.,
[OpenGL](https://www.khronos.org/opengl/),
[Vulkan](https://www.khronos.org/vulkan/),
[OSMesa](https://www.mesa3d.org/osmesa.html),
etc).

## Building

You will need
[Usul](https://github.com/perryiv/usul),
[Boost](https://www.boost.org/),
and
[CMake](https://cmake.org/)
installed:

    cd /your/path/to/generic_scene_graph
    mkdir build
    cd build
    cmake ..
