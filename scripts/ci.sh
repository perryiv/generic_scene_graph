
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

# Make sure these environment variables exist.
[ -z "${THIS_JOB_BUILD_GENERATOR}"  ] && echo "Empty environment variable: THIS_JOB_BUILD_GENERATOR"  && exit 1
[ -z "${THIS_JOB_INSTALL_COMMAND}"  ] && echo "Empty environment variable: THIS_JOB_INSTALL_COMMAND"  && exit 1
[ -z "${THIS_JOB_CPP_STANDARD}"     ] && echo "Empty environment variable: THIS_JOB_CPP_STANDARD"     && exit 1
[ -z "${THIS_JOB_VERBOSE_MAKEFILE}" ] && echo "Empty environment variable: THIS_JOB_VERBOSE_MAKEFILE" && exit 1

# Save the source directory.
sourceDir=$(pwd)

# Help cmake find things.
export CMAKE_MODULE_PATH=${CMAKE_MODULE_PATH}:/usr/local/lib/cmake/Catch2:/usr/local/lib/cmake/Immer:/usr/local/lib/cmake/usul

# Useful information.
env | sort
cmake --version
echo "whoami = `whoami`"
pwd

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
