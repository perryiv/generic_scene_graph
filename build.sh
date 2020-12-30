
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


# immer
echo "----"
cd
git clone https://github.com/arximboldi/immer.git
cd immer && rm -rf build && mkdir build && cd build
cmake ../ -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_STANDARD=${CPP_STANDARD} -DCMAKE_VERBOSE_MAKEFILE=ON
cmake --build .
sudo cmake --target install
cd


# Usul
echo "----"
cd
git clone https://github.com/perryiv/usul.git
cd usul && rm -rf build && mkdir build && cd build
cmake ../ -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_STANDARD=${CPP_STANDARD} -DCMAKE_VERBOSE_MAKEFILE=ON
cmake --build .
sudo cmake --target install
cd


echo "\n\n---- End of build script ----\n\n"
