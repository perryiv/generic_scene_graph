
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

# Useful information.
env | sort

# Make sure these environment variables exist.
[ -z "${THIS_JOB_DOCKER_IMAGE_NAME}"  ] && echo "Empty environment variable: THIS_JOB_DOCKER_IMAGE_NAME" && exit 1

# Run the docker command.
# docker run --rm -v `pwd`:/home/conan ${THIS_JOB_DOCKER_IMAGE_NAME} /bin/bash -c "sh scripts/before_ubuntu.sh && sh scripts/ci.sh"
