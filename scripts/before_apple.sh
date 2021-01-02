
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

# Sanity check.
echo "whoami = `whoami`"
echo "pwd = `pwd`"
echo "ls = `ls`"
cmake --version
node --version

# Get ready to install.
# sudo apt-get update

# Install node.
# curl -sL https://deb.nodesource.com/setup_14.x | sudo bash -
# sudo apt-get -y install nodejs

# Make sure we own everything.
# sudo chown -R `whoami` "/home/`whoami`/"

# Install mode modules.
npm install colors platform property-tools shelljs

# Install boost.
# sudo apt-get -y install libboost-stacktrace-dev
