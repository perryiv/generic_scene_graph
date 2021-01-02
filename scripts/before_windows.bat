
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::
::  Copyright (c) 2020, Perry L Miller IV
::  All rights reserved.
::  MIT License: https://opensource.org/licenses/mit-license.html
::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::
::  Install things needed in the continuous integration script.
::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

:: Sanity check.
echo "whoami = `whoami`"
echo "pwd = `pwd`"
echo "dir = `dir`"
cmake --version
node --version

REM :: Get ready to install.
REM sudo apt-get update
REM
REM :: Install node.
REM curl -sL https://deb.nodesource.com/setup_14.x | sudo bash -
REM sudo apt-get -y install nodejs
REM
REM :: Make sure we own everything.
REM sudo chown -R `whoami` "/home/`whoami`/"
REM
REM :: Install mode modules.
REM npm install colors platform property-tools shelljs
REM
REM :: Install boost.
REM sudo apt-get -y install libboost-stacktrace-dev
