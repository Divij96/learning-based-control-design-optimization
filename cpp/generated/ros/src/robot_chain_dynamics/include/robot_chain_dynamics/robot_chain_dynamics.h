//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: robot_chain_dynamics.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 12-Dec-2023 16:05:32
//

#ifndef ROBOT_CHAIN_DYNAMICS_H
#define ROBOT_CHAIN_DYNAMICS_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
extern void robot_chain_dynamics(coder::array<double, 1U> &q,
                                 coder::array<double, 1U> &dq, double rho,
                                 double num_links, double radius,
                                 const coder::array<double, 1U> &arm_length,
                                 const coder::array<double, 1U> &torque,
                                 coder::array<double, 1U> &joint_acc,
                                 double pos_tcp[3]);

#endif
//
// File trailer for robot_chain_dynamics.h
//
// [EOF]
//
