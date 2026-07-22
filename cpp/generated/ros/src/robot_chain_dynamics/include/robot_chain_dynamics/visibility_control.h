#ifndef ROBOT_CHAIN_DYNAMICS__VISIBILITY_CONTROL_H_
#define ROBOT_CHAIN_DYNAMICS__VISIBILITY_CONTROL_H_
#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define ROBOT_CHAIN_DYNAMICS_EXPORT __attribute__ ((dllexport))
    #define ROBOT_CHAIN_DYNAMICS_IMPORT __attribute__ ((dllimport))
  #else
    #define ROBOT_CHAIN_DYNAMICS_EXPORT __declspec(dllexport)
    #define ROBOT_CHAIN_DYNAMICS_IMPORT __declspec(dllimport)
  #endif
  #ifdef ROBOT_CHAIN_DYNAMICS_BUILDING_LIBRARY
    #define ROBOT_CHAIN_DYNAMICS_PUBLIC ROBOT_CHAIN_DYNAMICS_EXPORT
  #else
    #define ROBOT_CHAIN_DYNAMICS_PUBLIC ROBOT_CHAIN_DYNAMICS_IMPORT
  #endif
  #define ROBOT_CHAIN_DYNAMICS_PUBLIC_TYPE ROBOT_CHAIN_DYNAMICS_PUBLIC
  #define ROBOT_CHAIN_DYNAMICS_LOCAL
#else
  #define ROBOT_CHAIN_DYNAMICS_EXPORT __attribute__ ((visibility("default")))
  #define ROBOT_CHAIN_DYNAMICS_IMPORT
  #if __GNUC__ >= 4
    #define ROBOT_CHAIN_DYNAMICS_PUBLIC __attribute__ ((visibility("default")))
    #define ROBOT_CHAIN_DYNAMICS_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define ROBOT_CHAIN_DYNAMICS_PUBLIC
    #define ROBOT_CHAIN_DYNAMICS_LOCAL
  #endif
  #define ROBOT_CHAIN_DYNAMICS_PUBLIC_TYPE
#endif
#endif  // ROBOT_CHAIN_DYNAMICS__VISIBILITY_CONTROL_H_
// Generated 12-Dec-2023 16:05:41
// Copyright 2019-2020 The MathWorks, Inc.
