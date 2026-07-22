#ifndef SCARA_ROBOT_2DOF_FD__VISIBILITY_CONTROL_H_
#define SCARA_ROBOT_2DOF_FD__VISIBILITY_CONTROL_H_
#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define SCARA_ROBOT_2DOF_FD_EXPORT __attribute__ ((dllexport))
    #define SCARA_ROBOT_2DOF_FD_IMPORT __attribute__ ((dllimport))
  #else
    #define SCARA_ROBOT_2DOF_FD_EXPORT __declspec(dllexport)
    #define SCARA_ROBOT_2DOF_FD_IMPORT __declspec(dllimport)
  #endif
  #ifdef SCARA_ROBOT_2DOF_FD_BUILDING_LIBRARY
    #define SCARA_ROBOT_2DOF_FD_PUBLIC SCARA_ROBOT_2DOF_FD_EXPORT
  #else
    #define SCARA_ROBOT_2DOF_FD_PUBLIC SCARA_ROBOT_2DOF_FD_IMPORT
  #endif
  #define SCARA_ROBOT_2DOF_FD_PUBLIC_TYPE SCARA_ROBOT_2DOF_FD_PUBLIC
  #define SCARA_ROBOT_2DOF_FD_LOCAL
#else
  #define SCARA_ROBOT_2DOF_FD_EXPORT __attribute__ ((visibility("default")))
  #define SCARA_ROBOT_2DOF_FD_IMPORT
  #if __GNUC__ >= 4
    #define SCARA_ROBOT_2DOF_FD_PUBLIC __attribute__ ((visibility("default")))
    #define SCARA_ROBOT_2DOF_FD_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define SCARA_ROBOT_2DOF_FD_PUBLIC
    #define SCARA_ROBOT_2DOF_FD_LOCAL
  #endif
  #define SCARA_ROBOT_2DOF_FD_PUBLIC_TYPE
#endif
#endif  // SCARA_ROBOT_2DOF_FD__VISIBILITY_CONTROL_H_
// Generated 02-Dec-2023 17:29:32
// Copyright 2019-2020 The MathWorks, Inc.
