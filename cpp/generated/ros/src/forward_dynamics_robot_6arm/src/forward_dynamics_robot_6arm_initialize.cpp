//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: forward_dynamics_robot_6arm_initialize.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 14-Feb-2024 19:42:36
//

// Include Files
#include "forward_dynamics_robot_6arm_initialize.h"
#include "eml_rand_mt19937ar_stateful.h"
#include "forward_dynamics_robot_6arm_data.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
void forward_dynamics_robot_6arm_initialize()
{
  eml_rand_mt19937ar_stateful_init();
  isInitialized_forward_dynamics_robot_6arm = true;
}

//
// File trailer for forward_dynamics_robot_6arm_initialize.cpp
//
// [EOF]
//
