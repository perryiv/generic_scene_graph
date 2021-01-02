
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

# Echo all the commands.
set -x

# Install boost.
cd /tmp
rm -rf boost_1_75_0
wget https://dl.bintray.com/boostorg/release/1.75.0/source/boost_1_75_0.tar.bz2
bzip2 -d boost_1_75_0.tar.bz2
tar -xf boost_1_75_0.tar
rm boost_1_75_0.tar
cd boost_1_75_0
./bootstrap.sh --with-libraries=filesystem,stacktrace
./b2 install
