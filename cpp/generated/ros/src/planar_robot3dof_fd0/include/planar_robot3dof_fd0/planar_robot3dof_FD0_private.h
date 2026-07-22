/*
 * planar_robot3dof_FD0_private.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "planar_robot3dof_FD0".
 *
 * Model version              : 12.40
 * Simulink Coder version : 9.9 (R2023a) 19-Nov-2022
 * C++ source code generated on : Thu Nov 23 01:12:48 2023
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objective: Debugging
 * Validation result: Not run
 */

#ifndef RTW_HEADER_planar_robot3dof_FD0_private_h_
#define RTW_HEADER_planar_robot3dof_FD0_private_h_
#include "rtwtypes.h"
#include "builtin_typeid_types.h"
#include "multiword_types.h"
#include "planar_robot3dof_FD0_types.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmSetTFinal
#define rtmSetTFinal(rtm, val)         ((rtm)->Timing.tFinal = (val))
#endif

extern void rt_invd3x3_snf(const real_T u[9], real_T y[9]);

#endif                          /* RTW_HEADER_planar_robot3dof_FD0_private_h_ */
