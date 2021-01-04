
################################################################################
#
#  Copyright (c) 2020, Perry L Miller IV
#  All rights reserved.
#  MIT License: https://opensource.org/licenses/mit-license.html
#
################################################################################

################################################################################
#
#  Install things needed in the continuous integration script.
#
################################################################################

# Exit immediately if one of the following commands does not return zero.
set -e

echo "---- Start of script $0 ----"

# Echo all the commands.
set -x

# # Install conan.
# python -m pip install --upgrade pip
# pip install conan --upgrade
# pip install conan_package_tools
# conan user
#
# # Install boost.
# conan install boost/1.74.0@
# export BOOST_ROOT="/tmp/boost_1_75_0"
# export BOOST_ROOT=${HOME}/.conan/data/boost/1.69.0/conan/stable/package/bbedb5f4230af77e2db8373bcf0ad22d4087edf4

# Install boost.
cd /tmp
rm -rf boost_1_75_0
curl -L https://dl.bintray.com/boostorg/release/1.75.0/source/boost_1_75_0.tar.gz | tar xz
cd boost_1_75_0
./bootstrap.sh --with-libraries=stacktrace
./b2 install
# export BOOST_ROOT="/usr/local/lib/cmake/boost-1_75"
ls /usr/local/lib/cmake/boost-1.75.0

# Install boost.
# This will probably be faster but it hangs when running install_boost.
# cd /tmp
# rm -rf boost
# mkdir boost
# cd boost
# curl -L https://dl.bintray.com/boostorg/release/1.75.0/binaries/boost_1_75_0-msvc-14.2-64.exe > install_boost.exe
# ./install_boost.exe
# cd /tmp
# rm -rf boost

# ls /usr/local/include/boost-1_75
export CMAKE_MODULE_PATH=${CMAKE_MODULE_PATH}:/usr/local/lib/cmake/boost-1.75.0

: "---- End of script $0 ----"
