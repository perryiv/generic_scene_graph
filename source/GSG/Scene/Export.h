
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2021, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Defines what GSG_SCENE_EXPORT means.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _GSG_SCENE_DLL_EXPORT_H_
#define _GSG_SCENE_DLL_EXPORT_H_

#ifndef GSG_BASE_STATIC_DEFINE
# ifdef _WIN32
#  ifdef COMPILING_GSG_SCENE
#   define GSG_SCENE_EXPORT __declspec ( dllexport ) // We are compiling this library so the classes are exported.
#  else
#   define GSG_SCENE_EXPORT __declspec ( dllimport ) // The classes will be imported into the client's code.
#  endif
# else
#  ifdef COMPILING_GSG_SCENE
#   define GSG_SCENE_EXPORT __attribute__ (( visibility ( "default" ) ))
#  endif
# endif
#endif

#ifndef GSG_SCENE_EXPORT
# define GSG_SCENE_EXPORT
#endif

#endif // _GSG_SCENE_DLL_EXPORT_H_
