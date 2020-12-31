
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

echo "----"
echo "whoami = `whoami`"

# Help cmake find things.
echo "----"
export CMAKE_MODULE_PATH=/usr/local/lib/cmake/Catch2:/usr/local/lib/cmake/Immer:/usr/local/lib/cmake/usul
echo "CMAKE_MODULE_PATH = ${CMAKE_MODULE_PATH}"

# Catch2
echo "----"
cd /tmp
curl -L https://github.com/catchorg/Catch2/archive/v2.13.1.tar.gz | tar xz
cd Catch2-2.13.1
rm -rf build && mkdir build && cd build
cmake ../ -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_STANDARD=${CPP_STANDARD} -DCMAKE_VERBOSE_MAKEFILE=ON -DBUILD_TESTING=OFF -DCATCH_INSTALL_DOCS=OFF -DCATCH_INSTALL_HELPERS=OFF
cmake --build .
sudo make install
cd .. && rm -rf build

# Immer
echo "----"
cd /tmp
git clone https://github.com/arximboldi/immer.git
cd immer
rm -rf build && mkdir build && cd build
cmake ../ -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_STANDARD=${CPP_STANDARD} -DCMAKE_VERBOSE_MAKEFILE=ON
cmake --build .
sudo make install
cd .. && rm -rf build

# Boost
echo "----"
cd /tmp
wget https://dl.bintray.com/boostorg/release/1.75.0/source/boost_1_75_0.tar.bz2
bzip2 -d boost_1_75_0.tar.bz2
tar -xf boost_1_75_0.tar
rm boost_1_75_0.tar
cd boost_1_75_0
./bootstrap.sh --with-libraries=filesystem,stacktrace && \
sudo ./b2 install

# Usul
echo "----"
cd /tmp
git clone https://github.com/perryiv/usul.git
cd usul
rm -rf build && mkdir build && cd build
cmake ../ -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_STANDARD=${CPP_STANDARD} -DCMAKE_VERBOSE_MAKEFILE=ON
cmake --build .
sudo make install
cd .. && rm -rf build

# GSG
echo "----"
mkdir -p /tmp/gsg && cd /tmp/gsg
rm -rf build && mkdir build && cd build
cmake ${HOME} -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_STANDARD=${CPP_STANDARD} -DCMAKE_VERBOSE_MAKEFILE=ON -DGSG_BUILD_TESTS=ON
cmake --build .
sudo make install
cd bin && ./gsg_test_d --abort --use-colour=yes --durations=no
cd ..
rm -rf build && mkdir build && cd build
cmake ../ -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_STANDARD=${CPP_STANDARD} -DCMAKE_VERBOSE_MAKEFILE=ON -DGSG_BUILD_TESTS=ON
cmake --build .
sudo make install
cd bin && ./gsg_test --abort --use-colour=yes --durations=no
cd

echo "\n\n---- End of build script ----\n\n"
