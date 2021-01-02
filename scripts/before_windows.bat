
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

:: Install mode modules.
npm install colors platform property-tools shelljs
