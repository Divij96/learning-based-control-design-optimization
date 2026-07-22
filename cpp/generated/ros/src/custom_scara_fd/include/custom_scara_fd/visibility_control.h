#ifndef CUSTOM_SCARA_FD__VISIBILITY_CONTROL_H_
#define CUSTOM_SCARA_FD__VISIBILITY_CONTROL_H_
#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define CUSTOM_SCARA_FD_EXPORT __attribute__ ((dllexport))
    #define CUSTOM_SCARA_FD_IMPORT __attribute__ ((dllimport))
  #else
    #define CUSTOM_SCARA_FD_EXPORT __declspec(dllexport)
    #define CUSTOM_SCARA_FD_IMPORT __declspec(dllimport)
  #endif
  #ifdef CUSTOM_SCARA_FD_BUILDING_LIBRARY
    #define CUSTOM_SCARA_FD_PUBLIC CUSTOM_SCARA_FD_EXPORT
  #else
    #define CUSTOM_SCARA_FD_PUBLIC CUSTOM_SCARA_FD_IMPORT
  #endif
  #define CUSTOM_SCARA_FD_PUBLIC_TYPE CUSTOM_SCARA_FD_PUBLIC
  #define CUSTOM_SCARA_FD_LOCAL
#else
  #define CUSTOM_SCARA_FD_EXPORT __attribute__ ((visibility("default")))
  #define CUSTOM_SCARA_FD_IMPORT
  #if __GNUC__ >= 4
    #define CUSTOM_SCARA_FD_PUBLIC __attribute__ ((visibility("default")))
    #define CUSTOM_SCARA_FD_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define CUSTOM_SCARA_FD_PUBLIC
    #define CUSTOM_SCARA_FD_LOCAL
  #endif
  #define CUSTOM_SCARA_FD_PUBLIC_TYPE
#endif
#endif  // CUSTOM_SCARA_FD__VISIBILITY_CONTROL_H_
// Generated 23-Nov-2023 05:15:26
// Copyright 2019-2020 The MathWorks, Inc.
