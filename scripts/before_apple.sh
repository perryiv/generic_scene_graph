
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

# Install mode modules.
npm install colors platform property-tools shelljs
