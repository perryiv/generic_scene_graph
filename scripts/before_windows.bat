
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

:: Print environment variables.
set

:: Sanity check.
REM whoami
REM cd
REM dir
REM cd ..
REM dir
REM node --version
REM echo "hi 1"
REM echo "hi 2"

:: Install mode modules.
npm install colors platform property-tools shelljs
