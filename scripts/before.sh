
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

# Install node.
curl -sL https://deb.nodesource.com/setup_14.x | sudo bash -
sudo apt-get -y install nodejs

# Install mode modules.
npm install -g colors platform property-tools shelljs
