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

As of now, you will need
[Usul](https://github.com/perryiv/usul),
[immer](https://github.com/arximboldi/immer),
[Boost](https://www.boost.org/), and
[CMake](https://cmake.org/)
installed.

Eventually, in order to compile the renderers you will need
[OpenGL](https://www.khronos.org/opengl/)
and/or
[Vulkan](https://vulkan.lunarg.com/sdk/home),
but that's not working yet.

Configuring and building looks like this:

    cd /your/path/to/generic_scene_graph
    mkdir build
    cd build
    cmake .. \
      -DCMAKE_VERBOSE_MAKEFILE=ON \
      -DGSG_BUILD_TESTS=ON \
      -DGSG_ENABLE_CODE_COVERAGE=ON \
      -DCMAKE_BUILD_TYPE=Debug",
    cmake --build .

Or, if you have node, you can do this:

    npm run config-debug
    npm run build-debug

## Testing

You can do this:

    cd build/bin
    gsg_test_d --abort --use-colour=yes --durations=no

Or, again, if you have node, you can do this instead:

    npm run test-debug

## Developing

To build and test every time a change is made to the source code:

    npm run watch-debug
