#ifndef AEROFOIL__VISIBILITY_CONTROL_H_
#define AEROFOIL__VISIBILITY_CONTROL_H_
#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define AEROFOIL_EXPORT __attribute__ ((dllexport))
    #define AEROFOIL_IMPORT __attribute__ ((dllimport))
  #else
    #define AEROFOIL_EXPORT __declspec(dllexport)
    #define AEROFOIL_IMPORT __declspec(dllimport)
  #endif
  #ifdef AEROFOIL_BUILDING_LIBRARY
    #define AEROFOIL_PUBLIC AEROFOIL_EXPORT
  #else
    #define AEROFOIL_PUBLIC AEROFOIL_IMPORT
  #endif
  #define AEROFOIL_PUBLIC_TYPE AEROFOIL_PUBLIC
  #define AEROFOIL_LOCAL
#else
  #define AEROFOIL_EXPORT __attribute__ ((visibility("default")))
  #define AEROFOIL_IMPORT
  #if __GNUC__ >= 4
    #define AEROFOIL_PUBLIC __attribute__ ((visibility("default")))
    #define AEROFOIL_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define AEROFOIL_PUBLIC
    #define AEROFOIL_LOCAL
  #endif
  #define AEROFOIL_PUBLIC_TYPE
#endif
#endif  // AEROFOIL__VISIBILITY_CONTROL_H_
// Generated 26-Nov-2023 17:30:49
// Copyright 2019-2020 The MathWorks, Inc.
