
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
echo "whoami = `whoami`"

# Help cmake find things.
echo "----"
export CMAKE_MODULE_PATH=/usr/local/lib/cmake/Catch2:/usr/local/lib/cmake/Immer:/usr/local/lib/cmake/usul
echo "CMAKE_MODULE_PATH = ${CMAKE_MODULE_PATH}"

# Catch2
echo "----"
cd /tmp
rm -rf Catch2-2.13.1
curl -L https://github.com/catchorg/Catch2/archive/v2.13.1.tar.gz | tar xz
cd Catch2-2.13.1
rm -rf build && mkdir build && cd build
cmake ../ \
  -G "${THIS_JOB_BUILD_GENERATOR}" \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_CXX_STANDARD=${THIS_JOB_CPP_STANDARD} \
  -DCMAKE_VERBOSE_MAKEFILE=${THIS_JOB_VERBOSE_MAKEFILE} \
  -DBUILD_TESTING=OFF \
  -DCATCH_INSTALL_DOCS=OFF \
  -DCATCH_INSTALL_HELPERS=OFF \
  ${THIS_JOB_EXTRA_CONFIGURE_ARGUMENTS}
cmake --build .
${THIS_JOB_INSTALL_COMMAND}
cd .. && rm -rf build

# Immer
echo "----"
cd /tmp
rm -rf immer
git clone https://github.com/arximboldi/immer.git
cd immer
rm -rf build && mkdir build && cd build
cmake ../ \
  -G "${THIS_JOB_BUILD_GENERATOR}" \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_CXX_STANDARD=${THIS_JOB_CPP_STANDARD} \
  -DCMAKE_VERBOSE_MAKEFILE=${THIS_JOB_VERBOSE_MAKEFILE} \
  ${THIS_JOB_EXTRA_CONFIGURE_ARGUMENTS}
cmake --build .
${THIS_JOB_INSTALL_COMMAND}
cd .. && rm -rf build

# Boost
# echo "----"
# cd /tmp
# rm -rf boost_1_75_0
# wget https://dl.bintray.com/boostorg/release/1.75.0/source/boost_1_75_0.tar.bz2
# bzip2 -d boost_1_75_0.tar.bz2
# tar -xf boost_1_75_0.tar
# rm boost_1_75_0.tar
# cd boost_1_75_0
# ./bootstrap.sh --with-libraries=filesystem,stacktrace && \
# ./b2 install

# Usul
echo "----"
cd /tmp
rm -rf usul
git clone https://github.com/perryiv/usul.git
cd usul && rm -rf build && mkdir build && cd build
cmake ../ \
  -G "${THIS_JOB_BUILD_GENERATOR}" \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_CXX_STANDARD=${THIS_JOB_CPP_STANDARD} \
  -DCMAKE_VERBOSE_MAKEFILE=${THIS_JOB_VERBOSE_MAKEFILE} \
  ${THIS_JOB_EXTRA_CONFIGURE_ARGUMENTS}
cmake --build .
${THIS_JOB_INSTALL_COMMAND}
cd .. && rm -rf build

# GSG
echo "----"
cd /tmp
rm -rf gsg && mkdir -p gsg && cd gsg
rm -rf build && mkdir build && cd build
cmake ${HOME} \
  -G "${THIS_JOB_BUILD_GENERATOR}" \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_CXX_STANDARD=${THIS_JOB_CPP_STANDARD} \
  -DCMAKE_VERBOSE_MAKEFILE=${THIS_JOB_VERBOSE_MAKEFILE} \
  -DGSG_BUILD_TESTS=ON \
  ${THIS_JOB_EXTRA_CONFIGURE_ARGUMENTS}
cmake --build . --config Debug
${THIS_JOB_INSTALL_COMMAND}
cd bin && ./gsg_test_d --abort --use-colour=yes --durations=no
cd ../..
rm -rf build && mkdir build && cd build
cmake ${HOME} \
  -G "${THIS_JOB_BUILD_GENERATOR}" \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_CXX_STANDARD=${THIS_JOB_CPP_STANDARD} \
  -DCMAKE_VERBOSE_MAKEFILE=${THIS_JOB_VERBOSE_MAKEFILE} \
  -DGSG_BUILD_TESTS=ON \
  ${THIS_JOB_EXTRA_CONFIGURE_ARGUMENTS}
cmake --build . --config Release
${THIS_JOB_INSTALL_COMMAND}
cd bin && ./gsg_test --abort --use-colour=yes --durations=no
cd

echo "\n\n---- End of build script ----\n\n"
