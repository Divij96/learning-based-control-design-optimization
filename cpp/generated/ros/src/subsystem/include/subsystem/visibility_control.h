#ifndef SUBSYSTEM__VISIBILITY_CONTROL_H_
#define SUBSYSTEM__VISIBILITY_CONTROL_H_
#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define SUBSYSTEM_EXPORT __attribute__ ((dllexport))
    #define SUBSYSTEM_IMPORT __attribute__ ((dllimport))
  #else
    #define SUBSYSTEM_EXPORT __declspec(dllexport)
    #define SUBSYSTEM_IMPORT __declspec(dllimport)
  #endif
  #ifdef SUBSYSTEM_BUILDING_LIBRARY
    #define SUBSYSTEM_PUBLIC SUBSYSTEM_EXPORT
  #else
    #define SUBSYSTEM_PUBLIC SUBSYSTEM_IMPORT
  #endif
  #define SUBSYSTEM_PUBLIC_TYPE SUBSYSTEM_PUBLIC
  #define SUBSYSTEM_LOCAL
#else
  #define SUBSYSTEM_EXPORT __attribute__ ((visibility("default")))
  #define SUBSYSTEM_IMPORT
  #if __GNUC__ >= 4
    #define SUBSYSTEM_PUBLIC __attribute__ ((visibility("default")))
    #define SUBSYSTEM_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define SUBSYSTEM_PUBLIC
    #define SUBSYSTEM_LOCAL
  #endif
  #define SUBSYSTEM_PUBLIC_TYPE
#endif
#endif  // SUBSYSTEM__VISIBILITY_CONTROL_H_
// Generated 24-Nov-2023 17:37:51
// Copyright 2019-2020 The MathWorks, Inc.
