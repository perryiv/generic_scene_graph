
################################################################################
#
#  Copyright (c) 2020, Perry L Miller IV
#  All rights reserved.
#  MIT License: https://opensource.org/licenses/mit-license.html
#
################################################################################

# Exit immediately if one of the following commands does not return zero.
set -e

# Echo all the commands.
set -x

: "---- Start of build script ----"

# Useful information.
env
cmake --version
echo "whoami = `whoami`"
pwd

# Save the source directory.
sourceDir=$(pwd)

# Help cmake find things.
export CMAKE_MODULE_PATH=/usr/local/lib/cmake/Catch2:/usr/local/lib/cmake/Immer:/usr/local/lib/cmake/usul

: "---- Catch2 ----"
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

: "---- Immer ----"
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

# : "---- Boost ----"
# cd /tmp
# rm -rf boost_1_75_0
# wget https://dl.bintray.com/boostorg/release/1.75.0/source/boost_1_75_0.tar.bz2
# bzip2 -d boost_1_75_0.tar.bz2
# tar -xf boost_1_75_0.tar
# rm boost_1_75_0.tar
# cd boost_1_75_0
# ./bootstrap.sh --with-libraries=filesystem,stacktrace && \
# ./b2 install

: "---- Usul ----"
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

: "---- GSG ----"
cd /tmp
rm -rf gsg && mkdir -p gsg && cd gsg
rm -rf build && mkdir build && cd build
cmake ${sourceDir} \
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
cmake ${sourceDir} \
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

: "---- End of build script ----"
