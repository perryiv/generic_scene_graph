
################################################################################
#
#  Copyright (c) 2020, Perry L Miller IV
#  All rights reserved.
#  MIT License: https://opensource.org/licenses/mit-license.html
#
################################################################################

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
git clone https://github.com/perryiv/usul.git
cd usul

pushd .
rm -rf build && mkdir build && cd build
cmake ../ \
  -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_CXX_STANDARD=${CPP_STANDARD} \
  -DCMAKE_VERBOSE_MAKEFILE=ON \
  -DFORCE_COLORED_OUTPUT=ON
cmake --build .
cd bin && ./gsg_test_d --abort --use-colour=yes --durations=no
popd

pushd .
rm -rf build && mkdir build && cd build
cmake ../../ \
  -G Ninja \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_CXX_STANDARD=${CPP_STANDARD} \
  -DCMAKE_VERBOSE_MAKEFILE=ON \
  -DFORCE_COLORED_OUTPUT=ON
cmake --build .
cd bin && ./gsg_test --abort --use-colour=yes --durations=no
popd

echo "\n\n---- End of build script ----\n\n"
