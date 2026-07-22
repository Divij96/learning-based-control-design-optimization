#ifndef PLANAR_ROBOT3DOF_FD__VISIBILITY_CONTROL_H_
#define PLANAR_ROBOT3DOF_FD__VISIBILITY_CONTROL_H_
#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define PLANAR_ROBOT3DOF_FD_EXPORT __attribute__ ((dllexport))
    #define PLANAR_ROBOT3DOF_FD_IMPORT __attribute__ ((dllimport))
  #else
    #define PLANAR_ROBOT3DOF_FD_EXPORT __declspec(dllexport)
    #define PLANAR_ROBOT3DOF_FD_IMPORT __declspec(dllimport)
  #endif
  #ifdef PLANAR_ROBOT3DOF_FD_BUILDING_LIBRARY
    #define PLANAR_ROBOT3DOF_FD_PUBLIC PLANAR_ROBOT3DOF_FD_EXPORT
  #else
    #define PLANAR_ROBOT3DOF_FD_PUBLIC PLANAR_ROBOT3DOF_FD_IMPORT
  #endif
  #define PLANAR_ROBOT3DOF_FD_PUBLIC_TYPE PLANAR_ROBOT3DOF_FD_PUBLIC
  #define PLANAR_ROBOT3DOF_FD_LOCAL
#else
  #define PLANAR_ROBOT3DOF_FD_EXPORT __attribute__ ((visibility("default")))
  #define PLANAR_ROBOT3DOF_FD_IMPORT
  #if __GNUC__ >= 4
    #define PLANAR_ROBOT3DOF_FD_PUBLIC __attribute__ ((visibility("default")))
    #define PLANAR_ROBOT3DOF_FD_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define PLANAR_ROBOT3DOF_FD_PUBLIC
    #define PLANAR_ROBOT3DOF_FD_LOCAL
  #endif
  #define PLANAR_ROBOT3DOF_FD_PUBLIC_TYPE
#endif
#endif  // PLANAR_ROBOT3DOF_FD__VISIBILITY_CONTROL_H_
// Generated 22-Nov-2023 18:33:53
// Copyright 2019-2020 The MathWorks, Inc.
