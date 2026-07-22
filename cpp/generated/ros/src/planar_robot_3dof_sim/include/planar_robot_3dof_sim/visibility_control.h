#ifndef PLANAR_ROBOT_3DOF_SIM__VISIBILITY_CONTROL_H_
#define PLANAR_ROBOT_3DOF_SIM__VISIBILITY_CONTROL_H_
#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define PLANAR_ROBOT_3DOF_SIM_EXPORT __attribute__ ((dllexport))
    #define PLANAR_ROBOT_3DOF_SIM_IMPORT __attribute__ ((dllimport))
  #else
    #define PLANAR_ROBOT_3DOF_SIM_EXPORT __declspec(dllexport)
    #define PLANAR_ROBOT_3DOF_SIM_IMPORT __declspec(dllimport)
  #endif
  #ifdef PLANAR_ROBOT_3DOF_SIM_BUILDING_LIBRARY
    #define PLANAR_ROBOT_3DOF_SIM_PUBLIC PLANAR_ROBOT_3DOF_SIM_EXPORT
  #else
    #define PLANAR_ROBOT_3DOF_SIM_PUBLIC PLANAR_ROBOT_3DOF_SIM_IMPORT
  #endif
  #define PLANAR_ROBOT_3DOF_SIM_PUBLIC_TYPE PLANAR_ROBOT_3DOF_SIM_PUBLIC
  #define PLANAR_ROBOT_3DOF_SIM_LOCAL
#else
  #define PLANAR_ROBOT_3DOF_SIM_EXPORT __attribute__ ((visibility("default")))
  #define PLANAR_ROBOT_3DOF_SIM_IMPORT
  #if __GNUC__ >= 4
    #define PLANAR_ROBOT_3DOF_SIM_PUBLIC __attribute__ ((visibility("default")))
    #define PLANAR_ROBOT_3DOF_SIM_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define PLANAR_ROBOT_3DOF_SIM_PUBLIC
    #define PLANAR_ROBOT_3DOF_SIM_LOCAL
  #endif
  #define PLANAR_ROBOT_3DOF_SIM_PUBLIC_TYPE
#endif
#endif  // PLANAR_ROBOT_3DOF_SIM__VISIBILITY_CONTROL_H_
// Generated 23-Nov-2023 04:14:49
// Copyright 2019-2020 The MathWorks, Inc.
