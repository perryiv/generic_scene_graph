
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

# Get ready to install.
sudo apt-get update

# Install boost.
sudo apt-get -y install libboost-stacktrace-dev
