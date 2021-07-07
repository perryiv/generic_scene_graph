
################################################################################
#
#  Copyright (c) 2021, Perry L Miller IV
#  All rights reserved.
#  MIT License: https://opensource.org/licenses/mit-license.html
#
################################################################################

# Exit immediately if one of the following commands does not return zero.
set -e

echo "---- Start of script $0 ----"

# Make sure these environment variables exist.
[ -z "${THIS_JOB_BUILD_GENERATOR}"  ] && env | sort && echo "Missing environment variable: THIS_JOB_BUILD_GENERATOR"  && exit 1
[ -z "${THIS_JOB_INSTALL_COMMAND}"  ] && env | sort && echo "Missing environment variable: THIS_JOB_INSTALL_COMMAND"  && exit 1
[ -z "${THIS_JOB_CPP_STANDARD}"     ] && env | sort && echo "Missing environment variable: THIS_JOB_CPP_STANDARD"     && exit 1
[ -z "${THIS_JOB_VERBOSE_MAKEFILE}" ] && env | sort && echo "Missing environment variable: THIS_JOB_VERBOSE_MAKEFILE" && exit 1

# Save the source directory.
export SOURCE_DIR=$(pwd)

# Help cmake find things.
export CMAKE_MODULE_PATH=${CMAKE_MODULE_PATH}:/usr/local/lib/cmake/Catch2:/usr/local/lib/cmake/Immer:/usr/local/lib/cmake/usul

# Echo all the commands.
set -x

# Useful information.
: "---- Start of environment variables ----"
env | sort
: "---- End of environment variables ----"
cmake --version
whoami
pwd

: "---- Start of Catch2 ----"
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
: "---- End of Catch2 ----"

: "---- Start of Immer ----"
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
: "---- End of Immer ----"

: "---- Start of Usul ----"
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
: "---- End of Usul ----"

: "---- Start of GSG ----"
cd /tmp
rm -rf gsg && mkdir -p gsg && cd gsg
rm -rf build && mkdir build && cd build
cmake ${SOURCE_DIR} \
  -G "${THIS_JOB_BUILD_GENERATOR}" \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_CXX_STANDARD=${THIS_JOB_CPP_STANDARD} \
  -DCMAKE_VERBOSE_MAKEFILE=${THIS_JOB_VERBOSE_MAKEFILE} \
  -DGSG_BUILD_TESTS=ON \
  ${THIS_JOB_EXTRA_CONFIGURE_ARGUMENTS}
cmake --build . --config Debug
${THIS_JOB_INSTALL_COMMAND}
cd bin && \
  ./gsg_base_test_d  --abort --use-colour=yes --durations=no \
  ./gsg_scene_test_d --abort --use-colour=yes --durations=no
cd ../..
rm -rf build && mkdir build && cd build
cmake ${SOURCE_DIR} \
  -G "${THIS_JOB_BUILD_GENERATOR}" \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_CXX_STANDARD=${THIS_JOB_CPP_STANDARD} \
  -DCMAKE_VERBOSE_MAKEFILE=${THIS_JOB_VERBOSE_MAKEFILE} \
  -DGSG_BUILD_TESTS=ON \
  ${THIS_JOB_EXTRA_CONFIGURE_ARGUMENTS}
cmake --build . --config Release
${THIS_JOB_INSTALL_COMMAND}
cd bin && \
  ./gsg_base_test  --abort --use-colour=yes --durations=no \
  ./gsg_scene_test --abort --use-colour=yes --durations=no \
cd
: "---- End of GSG ----"

: "---- End of script $0 ----"
