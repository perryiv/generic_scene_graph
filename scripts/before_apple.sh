
################################################################################
#
#  Copyright (c) 2021, Perry L Miller IV
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

# Install boost.
brew install boost

# cd /tmp
# rm -rf boost_1_75_0
# curl -L https://dl.bintray.com/boostorg/release/1.75.0/source/boost_1_75_0.tar.gz | tar xz
# cd boost_1_75_0
# ./bootstrap.sh --with-libraries=filesystem,stacktrace
# sudo ./b2 install

# Install OSMesa.
# https://github.com/vizlab-kobe/KVS.osmesa
brew install --cask xquartz

: "---- End of script $0 ----"
