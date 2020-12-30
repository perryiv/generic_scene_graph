
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2020, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Defines what GSG_EXPORT means.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _GENERIC_SCENE_GRAPH_DLL_EXPORT_H_
#define _GENERIC_SCENE_GRAPH_DLL_EXPORT_H_

#ifndef GENERIC_SCENE_GRAPH_STATIC_DEFINE
# ifdef _WIN32
#  ifdef COMPILING_GSG
#   define GSG_EXPORT __declspec ( dllexport ) // We are compiling this library so the classes are exported.
#  else
#   define GSG_EXPORT __declspec ( dllimport ) // The classes will be imported into the client's code.
#  endif
# else
#  ifdef COMPILING_GSG
#   define GSG_EXPORT __attribute__ (( visibility ( "default" ) ))
#  endif
# endif
#endif

#ifndef GSG_EXPORT
# define GSG_EXPORT
#endif

#endif // _GENERIC_SCENE_GRAPH_DLL_EXPORT_H_
