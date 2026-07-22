#ifndef PLANAR_ROBOT3DOF_FD0__VISIBILITY_CONTROL_H_
#define PLANAR_ROBOT3DOF_FD0__VISIBILITY_CONTROL_H_
#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define PLANAR_ROBOT3DOF_FD0_EXPORT __attribute__ ((dllexport))
    #define PLANAR_ROBOT3DOF_FD0_IMPORT __attribute__ ((dllimport))
  #else
    #define PLANAR_ROBOT3DOF_FD0_EXPORT __declspec(dllexport)
    #define PLANAR_ROBOT3DOF_FD0_IMPORT __declspec(dllimport)
  #endif
  #ifdef PLANAR_ROBOT3DOF_FD0_BUILDING_LIBRARY
    #define PLANAR_ROBOT3DOF_FD0_PUBLIC PLANAR_ROBOT3DOF_FD0_EXPORT
  #else
    #define PLANAR_ROBOT3DOF_FD0_PUBLIC PLANAR_ROBOT3DOF_FD0_IMPORT
  #endif
  #define PLANAR_ROBOT3DOF_FD0_PUBLIC_TYPE PLANAR_ROBOT3DOF_FD0_PUBLIC
  #define PLANAR_ROBOT3DOF_FD0_LOCAL
#else
  #define PLANAR_ROBOT3DOF_FD0_EXPORT __attribute__ ((visibility("default")))
  #define PLANAR_ROBOT3DOF_FD0_IMPORT
  #if __GNUC__ >= 4
    #define PLANAR_ROBOT3DOF_FD0_PUBLIC __attribute__ ((visibility("default")))
    #define PLANAR_ROBOT3DOF_FD0_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define PLANAR_ROBOT3DOF_FD0_PUBLIC
    #define PLANAR_ROBOT3DOF_FD0_LOCAL
  #endif
  #define PLANAR_ROBOT3DOF_FD0_PUBLIC_TYPE
#endif
#endif  // PLANAR_ROBOT3DOF_FD0__VISIBILITY_CONTROL_H_
// Generated 23-Nov-2023 01:12:53
// Copyright 2019-2020 The MathWorks, Inc.
