
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

:: Echo all the commands.
@echo on

:: Sanity check.
whoami
cd
dir
cd ..
dir
node --version
echo "hi 1"
echo "hi 2"

:: Install mode modules.
npm install colors platform property-tools shelljs