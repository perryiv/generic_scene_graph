
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
[ -z "${THIS_JOB_DOCKER_IMAGE_NAME}" ] && env | sort && echo "Missing environment variable: THIS_JOB_DOCKER_IMAGE_NAME" && exit 1
[ -z "${THIS_JOB_BEFORE_SCRIPT}"     ] && env | sort && echo "Missing environment variable: THIS_JOB_BEFORE_SCRIPT"     && exit 1
[ -z "${THIS_JOB_BUILD_GENERATOR}"   ] && env | sort && echo "Missing environment variable: THIS_JOB_BUILD_GENERATOR"   && exit 1
[ -z "${THIS_JOB_INSTALL_COMMAND}"   ] && env | sort && echo "Missing environment variable: THIS_JOB_INSTALL_COMMAND"   && exit 1
[ -z "${THIS_JOB_CPP_STANDARD}"      ] && env | sort && echo "Missing environment variable: THIS_JOB_CPP_STANDARD"      && exit 1
[ -z "${THIS_JOB_VERBOSE_MAKEFILE}"  ] && env | sort && echo "Missing environment variable: THIS_JOB_VERBOSE_MAKEFILE"  && exit 1

# Echo all the commands.
set -x

# Run the docker command.
docker run --rm \
  -v `pwd`:/home/conan \
  --env THIS_JOB_BUILD_GENERATOR="${THIS_JOB_BUILD_GENERATOR}" \
  --env THIS_JOB_INSTALL_COMMAND="${THIS_JOB_INSTALL_COMMAND}" \
  --env THIS_JOB_CPP_STANDARD="${THIS_JOB_CPP_STANDARD}" \
  --env THIS_JOB_VERBOSE_MAKEFILE="${THIS_JOB_VERBOSE_MAKEFILE}" \
  ${THIS_JOB_DOCKER_IMAGE_NAME} \
  /bin/bash -c "sh ${THIS_JOB_BEFORE_SCRIPT} && sh scripts/ci.sh"

: "---- End of script $0 ----"
