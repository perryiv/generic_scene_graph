
////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2020, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//  Script for continuous integration.
//
////////////////////////////////////////////////////////////////////////////////

const { getProperty, requireProperty } = require ( "property-tools" );

const colors = require ( "colors/safe" );
const os = require ( "os" );
const platform = require ( "platform" );
const shell = require ( "shelljs" );

colors.enable();


////////////////////////////////////////////////////////////////////////////////
//
//  Are we running on one of these platforms?
//
////////////////////////////////////////////////////////////////////////////////

const isLinux = function()
{
  return ( platform.os.family.indexOf ( "Linux" ) >= 0 );
};
const isMac = function()
{
  return ( platform.os.family.indexOf ( "Darwin" ) >= 0 );
};
const isWindows = function()
{
  return ( platform.os.family.indexOf ( "Win32" ) >= 0 );
};


////////////////////////////////////////////////////////////////////////////////
//
//  Print and execute the given command.
//
////////////////////////////////////////////////////////////////////////////////

const execute = function ( command )
{
  console.log ( colors.yellow ( command.replace ( / && /g, "\n" ) ) );
  const code = shell.exec ( command ).code;

  if ( 0 != code )
  {
    throw new Error ( "Command returned " + code + ":\n" + command );
  }
};


////////////////////////////////////////////////////////////////////////////////
//
//  Make the cmake configuration command.
//
////////////////////////////////////////////////////////////////////////////////

const makeConfigCommand = function ( input )
{
  // Shortcuts.
  let env = process.env;

  // Get input.
  const sourceDir = getProperty ( input, "sourceDir", ".." );
  const buildType = requireProperty ( input, "buildType" );

  let s = "";
  s += "cmake " + sourceDir;

  if ( env.THIS_JOB_BUILD_GENERATOR )
  {
    s += " -G " + env.THIS_JOB_BUILD_GENERATOR;
  }
  if ( !isWindows() )
  {
    s += " -DCMAKE_BUILD_TYPE=" + buildType;
  }
  if ( env.THIS_JOB_CPP_STANDARD )
  {
    s += " -DCMAKE_CXX_STANDARD=" + env.THIS_JOB_CPP_STANDARD;
  }
  if ( env.THIS_JOB_VERBOSE_MAKEFILE )
  {
    s += " -DCMAKE_VERBOSE_MAKEFILE=" + env.THIS_JOB_VERBOSE_MAKEFILE;
  }
  if ( env.THIS_JOB_EXTRA_CONFIGURE_ARGUMENTS )
  {
    s += " " + env.THIS_JOB_EXTRA_CONFIGURE_ARGUMENTS;
  }

  return s;
}


////////////////////////////////////////////////////////////////////////////////
//
//  Make the cmake build command.
//
////////////////////////////////////////////////////////////////////////////////

const makeBuildCommand = function ( input )
{
  // Get input.
  const buildType = requireProperty ( input, "buildType" );

  let s = "";
  s += "cmake --build .";
  if ( isWindows() )
  {
    s += " --config " + buildType;
  }
  return s;
};


////////////////////////////////////////////////////////////////////////////////
//
//  Run the steps.
//
////////////////////////////////////////////////////////////////////////////////

const run = function()
{
  console.log ( colors.green ( "\n---- Start of build script ----" ) );

  // Shortcuts.
  let env = process.env;

  // Help cmake find things.
  {
    let mp = "";
    mp += "/usr/local/lib/cmake/Catch2";
    mp += ":/usr/local/lib/cmake/Immer";
    mp += ":/usr/local/lib/cmake/usul";
    env.CMAKE_MODULE_PATH = mp;
  }

  // Set defaults.
  if ( !env.THIS_JOB_BUILD_GENERATOR )
  {
    env.THIS_JOB_BUILD_GENERATOR = "Ninja";
  }
  if ( !env.THIS_JOB_BUILD_COMMAND )
  {
    env.THIS_JOB_BUILD_COMMAND = "ninja";
  }
  if ( !env.THIS_JOB_CPP_STANDARD )
  {
    env.THIS_JOB_CPP_STANDARD = 17;
  }
  if ( !env.THIS_JOB_VERBOSE_MAKEFILE )
  {
    env.THIS_JOB_VERBOSE_MAKEFILE = "ON";
  }
  if ( !env.THIS_JOB_SUDO_COMMAND )
  {
    env.THIS_JOB_SUDO_COMMAND = "sudo";
  }

  // Print some things.
  console.log ( "environment variables:", env );
  console.log ( "user info:", os.userInfo() );
  execute ( "cmake --version" );

  // Catch2
  {
    const buildType = "Release";
    const dir = "Catch2-2.13.1";
    let s = "";
    s += "cd /tmp";
    s += " && rm -rf " + dir;
    s += " && curl -L https://github.com/catchorg/Catch2/archive/v2.13.1.tar.gz | tar xz";
    s += " && cd " + dir;
    s += " && mkdir build";
    s += " && cd build";
    s += " && pwd";
    s += " && " + makeConfigCommand ( { buildType: buildType } );
    s += " -DBUILD_TESTING=OFF";
    s += " -DCATCH_INSTALL_DOCS=OFF";
    s += " -DCATCH_INSTALL_HELPERS=OFF";
    s += " && " + makeBuildCommand ( { buildType: buildType } );
    s += " && " + env.THIS_JOB_SUDO_COMMAND + " " + env.THIS_JOB_BUILD_COMMAND + " install";
    s += " && cd /tmp";
    s += " && rm -rf " + dir;
    execute ( s );
  }

  // Immer
  {
    const buildType = "Release";
    const dir = "immer";
    let s = "";
    s += "cd /tmp";
    s += " && rm -rf " + dir;
    s += " && git clone https://github.com/arximboldi/immer.git";
    s += " && cd " + dir;
    s += " && mkdir build";
    s += " && cd build";
    s += " && pwd";
    s += " && " + makeConfigCommand ( { buildType: buildType } );
    s += " && " + makeBuildCommand ( { buildType: buildType } );
    s += " && " + env.THIS_JOB_SUDO_COMMAND + " " + env.THIS_JOB_BUILD_COMMAND + " install";
    s += " && cd /tmp";
    s += " && rm -rf " + dir;
    execute ( s );
  }

  // Boost
  {
    if ( isLinux() )
    {
      execute ( env.THIS_JOB_SUDO_COMMAND + " apt-get -y install libboost-stacktrace-dev" );
    }
    else
    {
      const dir = "boost_1_75_0";
      let s = "";
      s += "cd /tmp";
      s += " && rm -rf " + dir;
      s += " && curl -L https://dl.bintray.com/boostorg/release/1.75.0/source/boost_1_75_0.tar.gz | tar xz";
      s += " && cd " + dir;
      s += " && ./bootstrap.sh --with-libraries=filesystem,stacktrace";
      s += " && " + env.THIS_JOB_SUDO_COMMAND + " ./b2 install";
      execute ( s );
    }
  }

  // Usul
  {
    const buildType = "Release";
    const dir = "usul";
    let s = "";
    s += "cd /tmp";
    s += " && rm -rf " + dir;
    s += " && git clone https://github.com/perryiv/usul.git";
    s += " && cd " + dir;
    s += " && mkdir build";
    s += " && cd build";
    s += " && pwd";
    s += " && " + makeConfigCommand ( { buildType: buildType } );
    s += " && " + makeBuildCommand ( { buildType: buildType } );
    s += " && " + env.THIS_JOB_SUDO_COMMAND + " " + env.THIS_JOB_BUILD_COMMAND + " install";
    s += " && cd /tmp";
    s += " && rm -rf " + dir;
    execute ( s );
  }

  // GSG
  {
    const makeThisProject = function ( buildType )
    {
      let postfix = ( ( "Debug" == buildType ) ? "_d" : "" );
      const dir = "gsg";
      let s = "";
      s += "cd /tmp";
      s += " && rm -rf " + dir;
      s += " && mkdir " + dir;
      s += " && cd " + dir;
      s += " && mkdir build";
      s += " && cd build";
      s += " && pwd";
      s += " && " + makeConfigCommand ( { buildType: buildType, sourceDir: env.HOME } ) + " -DGSG_BUILD_TESTS=ON";
      s += " && " + makeBuildCommand ( { buildType: buildType } );
      s += " && " + env.THIS_JOB_SUDO_COMMAND + " " + env.THIS_JOB_BUILD_COMMAND + " install";
      s += " && cd bin";
      s += " && ./gsg_test" + postfix + " --abort --use-colour=yes --durations=no";
      s += " && cd /tmp";
      s += " && rm -rf " + dir;
      execute ( s );
    }
    makeThisProject ( "Debug" );
    makeThisProject ( "Release" );
  }

  console.log ( colors.green ( "\n---- End of build script ----" ) );
};


////////////////////////////////////////////////////////////////////////////////
//
//  The main function.
//
////////////////////////////////////////////////////////////////////////////////

const main = function()
{
  try
  {
    run();
  }

  catch ( error )
  {
    console.log ( error );
    process.exitCode = 1;
  }
};
main();