
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

# Run the docker command.
docker run --rm -v `pwd`:/home/conan conanio/gcc9 /bin/bash -c "sh scripts/before_ubuntu.sh && sh scripts/ci.sh"
