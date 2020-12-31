
################################################################################
#
#  Copyright (c) 2020, Perry L Miller IV
#  All rights reserved.
#  MIT License: https://opensource.org/licenses/mit-license.html
#
################################################################################

# Exit when any command fails.
# https://intoli.com/blog/exit-on-errors-in-bash-scripts/
set -e

echo "\n\n---- Start of build script ----\n\n"

echo "----"
env

echo "----"
cmake --version

echo "----"
$CC --version

echo "----"
$CXX --version


# Catch2
echo "----"
cd
curl -L https://github.com/catchorg/Catch2/archive/v2.13.1.tar.gz | tar xz
cd Catch2-2.13.1
rm -rf build && mkdir build && cd build
cmake ../ -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_STANDARD=${CPP_STANDARD} -DCMAKE_VERBOSE_MAKEFILE=ON -DBUILD_TESTING=OFF -DCATCH_INSTALL_DOCS=OFF -DCATCH_INSTALL_HELPERS=OFF
cmake --build .
sudo ninja install
cd .. && rm -rf build
cd


# immer
echo "----"
cd
git clone https://github.com/arximboldi/immer.git
cd immer
rm -rf build && mkdir build && cd build
cmake ../ -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_STANDARD=${CPP_STANDARD} -DCMAKE_VERBOSE_MAKEFILE=ON
cmake --build .
sudo ninja install
cd .. && rm -rf build
cd


# Usul
echo "----"
cd
git clone https://github.com/perryiv/usul.git
cd usul
rm -rf build && mkdir build && cd build
cmake ../ -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_STANDARD=${CPP_STANDARD} -DCMAKE_VERBOSE_MAKEFILE=ON
cmake --build .
sudo ninja install
cd .. && rm -rf build
cd


# GSG
echo "----"
cd
git clone https://github.com/perryiv/generic_scene_graph.git
cd generic_scene_graph
rm -rf build && mkdir build && cd build
cmake ../ -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_STANDARD=${CPP_STANDARD} -DCMAKE_VERBOSE_MAKEFILE=ON -DGSG_BUILD_TESTS=ON
cmake --build .
cd bin && ./gsg_test_d --abort --use-colour=yes --durations=no
cd
cd generic_scene_graph
rm -rf build && mkdir build && cd build
cmake ../ -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_STANDARD=${CPP_STANDARD} -DCMAKE_VERBOSE_MAKEFILE=ON -DGSG_BUILD_TESTS=ON
cmake --build .
cd bin && ./gsg_test --abort --use-colour=yes --durations=no
cd


echo "\n\n---- End of build script ----\n\n"
