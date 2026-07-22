//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: scara_robot_2dof_FD.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 02-Dec-2023 17:29:26
//

#ifndef SCARA_ROBOT_2DOF_FD_H
#define SCARA_ROBOT_2DOF_FD_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
extern void scara_robot_2dof_FD(const double q[2], const double dq[2],
                                double rho, double radius,
                                const double arm_length[2],
                                const double torque[2], double joint_acc[2],
                                double pos_tcp[3]);

#endif
//
// File trailer for scara_robot_2dof_FD.h
//
// [EOF]
//
