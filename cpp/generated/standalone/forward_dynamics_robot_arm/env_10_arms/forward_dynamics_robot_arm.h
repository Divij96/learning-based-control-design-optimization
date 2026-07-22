//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: forward_dynamics_robot_arm.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 02-Feb-2024 13:34:01
//

#ifndef FORWARD_DYNAMICS_ROBOT_ARM_H
#define FORWARD_DYNAMICS_ROBOT_ARM_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
extern void forward_dynamics_robot_arm(
    double rho, double radius, const double arm_length[10],
    const double joint_axes[30], const double joint_angles[10],
    const double config[10], const double vel[10], const double tq[10],
    double acc_data[], int acc_size[1]);

#endif
//
// File trailer for forward_dynamics_robot_arm.h
//
// [EOF]
//
