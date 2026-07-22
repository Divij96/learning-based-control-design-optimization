//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: forward_dynamics_robot_6arm.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 14-Feb-2024 19:42:36
//

#ifndef FORWARD_DYNAMICS_ROBOT_6ARM_H
#define FORWARD_DYNAMICS_ROBOT_6ARM_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
extern void forward_dynamics_robot_6arm(
    double rho, double radius, const double arm_length[6],
    const double joint_axes[18], const double joint_angles[6],
    const double config[6], const double vel[6], const double tq[6],
    double acc_data[], int acc_size[1], double linkPositionsArray[18]);

#endif
//
// File trailer for forward_dynamics_robot_6arm.h
//
// [EOF]
//
