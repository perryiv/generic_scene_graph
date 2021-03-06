
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2021, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Defines what GSG_RENDERER_OSMESA_EXPORT means.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _GSG_RENDERER_OSMESA_DLL_EXPORT_H_
#define _GSG_RENDERER_OSMESA_DLL_EXPORT_H_

#ifndef GSG_BASE_STATIC_DEFINE
# ifdef _WIN32
#  ifdef COMPILING_GSG_RENDERER_OSMESA
#   define GSG_RENDERER_OSMESA_EXPORT __declspec ( dllexport ) // We are compiling this library so the classes are exported.
#  else
#   define GSG_RENDERER_OSMESA_EXPORT __declspec ( dllimport ) // The classes will be imported into the client's code.
#  endif
# else
#  ifdef COMPILING_GSG_RENDERER_OSMESA
#   define GSG_RENDERER_OSMESA_EXPORT __attribute__ (( visibility ( "default" ) ))
#  endif
# endif
#endif

#ifndef GSG_RENDERER_OSMESA_EXPORT
# define GSG_RENDERER_OSMESA_EXPORT
#endif

#endif // _GSG_RENDERER_OSMESA_DLL_EXPORT_H_
