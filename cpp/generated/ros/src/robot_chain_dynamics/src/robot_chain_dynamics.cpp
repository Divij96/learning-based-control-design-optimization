//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: robot_chain_dynamics.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 12-Dec-2023 16:05:32
//

// Include Files
#include "robot_chain_dynamics.h"
#include "mldivide.h"
#include "mtimes.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <algorithm>
#include <cmath>
#include <cstring>

// Type Definitions
struct cell_wrap_0 {
  double f1[36];
};

struct cell_wrap_1 {
  double f1[16];
};

// Function Declarations
static void binary_expand_op(coder::array<double, 2U> &in1,
                             const coder::array<double, 2U> &in3,
                             const coder::array<double, 2U> &in4);

static void binary_expand_op(coder::array<double, 2U> &in1, int in2,
                             const coder::array<double, 2U> &in3);

static void binary_expand_op(coder::array<double, 2U> &in1, int in2,
                             const coder::array<double, 2U> &in3,
                             const coder::array<double, 2U> &in4);

static void binary_expand_op(coder::array<double, 1U> &in1, int in2,
                             const coder::array<double, 1U> &in3);

static void binary_expand_op(coder::array<double, 1U> &in1,
                             const coder::array<double, 1U> &in2,
                             const coder::array<double, 1U> &in3);

// Function Definitions
//
// Arguments    : coder::array<double, 2U> &in1
//                const coder::array<double, 2U> &in3
//                const coder::array<double, 2U> &in4
// Return Type  : void
//
static void binary_expand_op(coder::array<double, 2U> &in1,
                             const coder::array<double, 2U> &in3,
                             const coder::array<double, 2U> &in4)
{
  int aux_0_1;
  int aux_1_1;
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  stride_0_1 = (in3.size(1) != 1);
  stride_1_1 = (in4.size(1) != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  if (in4.size(1) == 1) {
    loop_ub = in3.size(1);
  } else {
    loop_ub = in4.size(1);
  }
  for (int i{0}; i < loop_ub; i++) {
    for (int i1{0}; i1 < 6; i1++) {
      in1[i1 + 6 * i] = in3[i1 + 6 * aux_0_1] - in4[i1 + 6 * aux_1_1];
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
}

//
// Arguments    : coder::array<double, 2U> &in1
//                int in2
//                const coder::array<double, 2U> &in3
// Return Type  : void
//
static void binary_expand_op(coder::array<double, 2U> &in1, int in2,
                             const coder::array<double, 2U> &in3)
{
  coder::array<double, 2U> b_in1;
  int aux_0_1;
  int aux_1_1;
  int b_loop_ub;
  int loop_ub;
  int stride_0_0_tmp;
  int stride_1_0;
  int stride_1_1;
  if (in3.size(0) == 1) {
    loop_ub = in2 + 1;
  } else {
    loop_ub = in3.size(0);
  }
  if (in3.size(1) == 1) {
    b_loop_ub = in2 + 1;
  } else {
    b_loop_ub = in3.size(1);
  }
  b_in1.set_size(loop_ub, b_loop_ub);
  stride_0_0_tmp = (in2 + 1 != 1);
  stride_1_0 = (in3.size(0) != 1);
  stride_1_1 = (in3.size(1) != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (int i{0}; i < b_loop_ub; i++) {
    for (int i1{0}; i1 < loop_ub; i1++) {
      b_in1[i1 + b_in1.size(0) * i] =
          in1[i1 * stride_0_0_tmp + in1.size(0) * aux_0_1] +
          in3[i1 * stride_1_0 + in3.size(0) * aux_1_1];
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_0_tmp;
  }
  loop_ub = b_in1.size(1);
  for (int i{0}; i < loop_ub; i++) {
    b_loop_ub = b_in1.size(0);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
      in1[i1 + in1.size(0) * i] = b_in1[i1 + b_in1.size(0) * i];
    }
  }
}

//
// Arguments    : coder::array<double, 2U> &in1
//                int in2
//                const coder::array<double, 2U> &in3
//                const coder::array<double, 2U> &in4
// Return Type  : void
//
static void binary_expand_op(coder::array<double, 2U> &in1, int in2,
                             const coder::array<double, 2U> &in3,
                             const coder::array<double, 2U> &in4)
{
  coder::array<double, 2U> b_in1;
  int aux_0_1;
  int aux_1_1;
  int aux_2_1;
  int b_loop_ub;
  int loop_ub;
  int stride_0_0_tmp;
  int stride_1_0;
  int stride_1_1;
  int stride_2_0;
  int stride_2_1;
  if (in4.size(0) == 1) {
    if (in3.size(0) == 1) {
      loop_ub = in2 + 1;
    } else {
      loop_ub = in3.size(0);
    }
  } else {
    loop_ub = in4.size(0);
  }
  if (in4.size(1) == 1) {
    if (in3.size(1) == 1) {
      b_loop_ub = in2 + 1;
    } else {
      b_loop_ub = in3.size(1);
    }
  } else {
    b_loop_ub = in4.size(1);
  }
  b_in1.set_size(loop_ub, b_loop_ub);
  stride_0_0_tmp = (in2 + 1 != 1);
  stride_1_0 = (in3.size(0) != 1);
  stride_1_1 = (in3.size(1) != 1);
  stride_2_0 = (in4.size(0) != 1);
  stride_2_1 = (in4.size(1) != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  aux_2_1 = 0;
  for (int i{0}; i < b_loop_ub; i++) {
    for (int i1{0}; i1 < loop_ub; i1++) {
      b_in1[i1 + b_in1.size(0) * i] =
          (in1[i1 * stride_0_0_tmp + in1.size(0) * aux_0_1] +
           in3[i1 * stride_1_0 + in3.size(0) * aux_1_1]) +
          in4[i1 * stride_2_0 + in4.size(0) * aux_2_1];
    }
    aux_2_1 += stride_2_1;
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_0_tmp;
  }
  loop_ub = b_in1.size(1);
  for (int i{0}; i < loop_ub; i++) {
    b_loop_ub = b_in1.size(0);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
      in1[i1 + in1.size(0) * i] = b_in1[i1 + b_in1.size(0) * i];
    }
  }
}

//
// Arguments    : coder::array<double, 1U> &in1
//                int in2
//                const coder::array<double, 1U> &in3
// Return Type  : void
//
static void binary_expand_op(coder::array<double, 1U> &in1, int in2,
                             const coder::array<double, 1U> &in3)
{
  coder::array<double, 2U> b_in1;
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  b_in1.set_size(1, in2 + 1);
  stride_0_1 = (in2 + 1 != 1);
  stride_1_1 = (in3.size(0) != 1);
  loop_ub = in2 + 1;
  for (int i{0}; i < loop_ub; i++) {
    b_in1[i] = in1[i * stride_0_1] + in3[i * stride_1_1];
  }
  loop_ub = b_in1.size(1);
  for (int i{0}; i < loop_ub; i++) {
    in1[i] = b_in1[i];
  }
}

//
// Arguments    : coder::array<double, 1U> &in1
//                const coder::array<double, 1U> &in2
//                const coder::array<double, 1U> &in3
// Return Type  : void
//
static void binary_expand_op(coder::array<double, 1U> &in1,
                             const coder::array<double, 1U> &in2,
                             const coder::array<double, 1U> &in3)
{
  coder::array<double, 1U> b_in1;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  int stride_2_0;
  if (in3.size(0) == 1) {
    if (in2.size(0) == 1) {
      loop_ub = in1.size(0);
    } else {
      loop_ub = in2.size(0);
    }
  } else {
    loop_ub = in3.size(0);
  }
  b_in1.set_size(loop_ub);
  stride_0_0 = (in1.size(0) != 1);
  stride_1_0 = (in2.size(0) != 1);
  stride_2_0 = (in3.size(0) != 1);
  for (int i{0}; i < loop_ub; i++) {
    b_in1[i] =
        (in1[i * stride_0_0] + in2[i * stride_1_0]) - in3[i * stride_2_0];
  }
  in1.set_size(b_in1.size(0));
  loop_ub = b_in1.size(0);
  for (int i{0}; i < loop_ub; i++) {
    in1[i] = b_in1[i];
  }
}

//
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// Arguments    : coder::array<double, 1U> &q
//                coder::array<double, 1U> &dq
//                double rho
//                double num_links
//                double radius
//                const coder::array<double, 1U> &arm_length
//                const coder::array<double, 1U> &torque
//                coder::array<double, 1U> &joint_acc
//                double pos_tcp[3]
// Return Type  : void
//
void robot_chain_dynamics(coder::array<double, 1U> &q,
                          coder::array<double, 1U> &dq, double rho,
                          double num_links, double radius,
                          const coder::array<double, 1U> &arm_length,
                          const coder::array<double, 1U> &torque,
                          coder::array<double, 1U> &joint_acc,
                          double pos_tcp[3])
{
  static const signed char b[9]{1, 0, 0, 0, 1, 0, 0, 0, 1};
  static const signed char a[6]{0, 0, 0, 0, 0, 1};
  coder::array<cell_wrap_0, 1U> Mass;
  coder::array<cell_wrap_1, 1U> g0;
  coder::array<double, 2U> C;
  coder::array<double, 2U> CC;
  coder::array<double, 2U> Htm;
  coder::array<double, 2U> J;
  coder::array<double, 2U> J_pre;
  coder::array<double, 2U> M;
  coder::array<double, 2U> ROBOT_Mass;
  coder::array<double, 2U> ROBOT_g0;
  coder::array<double, 2U> b_ROBOT_Mass;
  coder::array<double, 2U> b_g;
  coder::array<double, 2U> dJ;
  coder::array<double, 2U> dJ_pre;
  coder::array<double, 2U> jointOrigins;
  coder::array<double, 2U> r;
  coder::array<double, 2U> r1;
  coder::array<double, 2U> tmp;
  coder::array<double, 2U> tmptmp;
  coder::array<double, 1U> b_C;
  coder::array<double, 1U> g;
  coder::array<signed char, 1U> ROBOT_csi;
  double O_Htm[16];
  double O_Htm_pre[16];
  double ROBOT_tcp_t_ee[16];
  double E[9];
  double S[9];
  double b_I[9];
  double c_I[9];
  double tmp2[9];
  double inertialTwist_pre[6];
  double Iz;
  double body_CenterOfMass_idx_0;
  double currentG0Index;
  double m;
  int b_loop_ub_tmp;
  int boffset;
  int coffset;
  int i;
  int i1;
  int ibcol;
  int loop_ub_tmp;
  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  //  Calculation of system matrices
  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  //
  //  Calculates the dynamic and kinematic matrices by using the iterative
  //  algorithm proposed in [1]. Kinematic and inertia parameters of the robot
  //  can be given in a compact way. Additionally, this algorithm can ensure
  //  the skew-symmetric property of dM - 2C.
  //
  //  Inputs:
  //  q:        Current joint positions, n-by-1 vector
  //  dq:       Current joint velocities, n-by-1 vector
  //  ROBOT:    Robot parameters, MATLAB structure with three
  //            fields:
  //            g0:       4n-by-4 matrix stacking vertically the homogeneous
  //                      transformation matrices from parent to link in the
  //                      zero-configuration
  //            csi:      6n-by-1 vector stacking vertically the 6-by-1
  //                      relative body jacobian (twist)
  //            Mass:     6n-by-6 matrix stacking vertically the 6-by-6
  //                      constant body inertia matrix from parent to link
  //            g_vec:    3-by-1 gravitational acceleration constant
  //            tcp_t_ee: 4-by-4 homogeneous transformation matrix from
  //                      end-effector to tcp
  //
  //  Outputs
  //  M:        n-by-n joint space inertia matrix
  //  CC:       n-by-n joint space Cor./centrifugal matrix
  //  g:        n-by-1 gravity torque vector
  //  O_J_TCP:  6-by-n hybrid jacobian of tcp
  //  B_J_TCP:  6-by-n body jacobian of tcp
  //  Htm_TCP:  4-by-4 homogeneous transformation matrix from tcp to base
  //
  //  References
  //  [1] Garofalo, Gianluca, Christian Ott and Alin Albu-Schäffer. "On the
  //  closed form computation of the dynamic matrices and their
  //  differentiations." 2013 IEEE/RSJ International Conference on Intelligent
  //  Robots and Systems (2013): 2364-2359.
  //
  //  Implemented by Xuwei Wu.
  //  Planar_n_DoF Description.
  //    Planar manipulator with 2 DoF.
  //    ...
  //  Origin of the frames and axis
  std::memset(&E[0], 0, 9U * sizeof(double));
  E[0] = 1.0;
  E[4] = 1.0;
  E[8] = 1.0;
  //  Initial origins of joint coordinate systems represented in global
  //  coordinate system (one for each column)
  i = static_cast<int>(num_links);
  jointOrigins.set_size(3, i);
  coffset = 3 * static_cast<int>(num_links);
  for (i1 = 0; i1 < coffset; i1++) {
    jointOrigins[i1] = 0.0;
  }
  i1 = static_cast<int>(num_links - 1.0);
  for (int b_i{0}; b_i < i1; b_i++) {
    jointOrigins[3 * (b_i + 1)] = arm_length[b_i];
    jointOrigins[3 * (b_i + 1) + 1] = 0.0;
    jointOrigins[3 * (b_i + 1) + 2] = 0.0;
  }
  //  Parameter of end-effector
  //  homogeneous transformation of tcp
  //  Mass, Center of Mass, and Inertia calculations for each link
  Mass.set_size(i);
  g0.set_size(i);
  currentG0Index = radius * radius;
  S[0] = 0.0;
  S[3] = 0.0;
  S[6] = 0.0;
  S[1] = 0.0;
  S[4] = 0.0;
  S[2] = -0.0;
  S[8] = 0.0;
  for (int iLink{0}; iLink < i; iLink++) {
    //  Compute dynamics based on cylindrical geometry
    m = 3.1415926535897931 * currentG0Index * arm_length[iLink] * rho;
    //  Mass
    body_CenterOfMass_idx_0 = arm_length[iLink] / 2.0;
    //  Center of mass
    //  Inertia around z-axis
    Iz = 0.25 * m * currentG0Index +
         0.083333333333333329 * m * (arm_length[iLink] * arm_length[iLink]);
    //  Inertia around x and y axis
    //  Assign computed values to body
    //  Spatial inertia matrix
    std::memset(&b_I[0], 0, 9U * sizeof(double));
    //  Inertia  Spatial rigid-body inertia from mass, CoM, and rotational
    //  inertia.
    //  ...
    //  utility functions
    //  -------------------------------------------------------% Skew symmetric
    //  matrix.
    //  ...
    b_I[0] = 0.5 * m * currentG0Index;
    b_I[4] = Iz;
    b_I[8] = Iz;
    S[7] = -body_CenterOfMass_idx_0;
    S[5] = body_CenterOfMass_idx_0;
    for (i1 = 0; i1 < 9; i1++) {
      tmp2[i1] = m * S[i1];
    }
    for (i1 = 0; i1 < 3; i1++) {
      for (boffset = 0; boffset < 3; boffset++) {
        ibcol = i1 + 3 * boffset;
        c_I[ibcol] =
            b_I[ibcol] -
            ((tmp2[i1] * S[3 * boffset] + tmp2[i1 + 3] * S[3 * boffset + 1]) +
             tmp2[i1 + 6] * S[3 * boffset + 2]);
        coffset = boffset + 3 * i1;
        ibcol = boffset + 6 * i1;
        Mass[iLink].f1[ibcol] = m * static_cast<double>(b[coffset]);
        Mass[iLink].f1[boffset + 6 * (i1 + 3)] = -m * S[coffset];
        Mass[iLink].f1[ibcol + 3] = tmp2[coffset];
      }
    }
    //  Initial relative homogeneous transformation matrix
    for (i1 = 0; i1 < 3; i1++) {
      boffset = 6 * (i1 + 3);
      Mass[iLink].f1[boffset + 3] = c_I[3 * i1];
      coffset = i1 << 2;
      g0[iLink].f1[coffset] = E[3 * i1];
      ibcol = 3 * i1 + 1;
      Mass[iLink].f1[boffset + 4] = c_I[ibcol];
      g0[iLink].f1[coffset + 1] = E[ibcol];
      ibcol = 3 * i1 + 2;
      Mass[iLink].f1[boffset + 5] = c_I[ibcol];
      g0[iLink].f1[coffset + 2] = E[ibcol];
      g0[iLink].f1[i1 + 12] = jointOrigins[i1 + 3 * iLink];
    }
    g0[iLink].f1[3] = 0.0;
    g0[iLink].f1[7] = 0.0;
    g0[iLink].f1[11] = 0.0;
    g0[iLink].f1[15] = 1.0;
  }
  //  Relative body jacobians adjusted for n DOF planar robot (rotation around
  //  z-axis)
  ROBOT_csi.set_size(6 * static_cast<int>(num_links));
  for (coffset = 0; coffset < i; coffset++) {
    ibcol = coffset * 6;
    for (boffset = 0; boffset < 6; boffset++) {
      ROBOT_csi[ibcol + boffset] = a[boffset];
    }
  }
  //  Gravitational acceleration constant
  //  Pack into ROBOT structure
  //  Concatenate all elements of g0 vertically
  //  Pre-allocate ROBOT.g0 and ROBOT.Mass based on num_links
  i1 = static_cast<int>(4.0 * num_links);
  ROBOT_g0.set_size(i1, 4);
  coffset = i1 << 2;
  for (i1 = 0; i1 < coffset; i1++) {
    ROBOT_g0[i1] = 0.0;
  }
  i1 = static_cast<int>(6.0 * num_links);
  ROBOT_Mass.set_size(i1, 6);
  coffset = i1 * 6;
  for (i1 = 0; i1 < coffset; i1++) {
    ROBOT_Mass[i1] = 0.0;
  }
  //  Variables to keep track of the current index
  currentG0Index = 1.0;
  m = 1.0;
  for (int b_i{0}; b_i < i; b_i++) {
    //  Calculate the size of the current g0{i} and Mass{i}
    //  Fill the pre-allocated arrays
    if (currentG0Index > (currentG0Index + 4.0) - 1.0) {
      i1 = 0;
      boffset = 0;
    } else {
      i1 = static_cast<int>(currentG0Index) - 1;
      boffset =
          static_cast<int>(static_cast<unsigned int>(currentG0Index) + 3U);
    }
    ibcol = boffset - i1;
    for (boffset = 0; boffset < 4; boffset++) {
      for (coffset = 0; coffset < ibcol; coffset++) {
        ROBOT_g0[(i1 + coffset) + ROBOT_g0.size(0) * boffset] =
            g0[b_i].f1[coffset + ibcol * boffset];
      }
    }
    if (m > (m + 6.0) - 1.0) {
      i1 = 0;
      boffset = 0;
    } else {
      i1 = static_cast<int>(m) - 1;
      boffset = static_cast<int>(static_cast<unsigned int>(m) + 5U);
    }
    ibcol = boffset - i1;
    for (boffset = 0; boffset < 6; boffset++) {
      for (coffset = 0; coffset < ibcol; coffset++) {
        ROBOT_Mass[(i1 + coffset) + ROBOT_Mass.size(0) * boffset] =
            Mass[b_i].f1[coffset + ibcol * boffset];
      }
    }
    //  Update the indices
    currentG0Index += 4.0;
    m += 6.0;
  }
  for (i = 0; i < 3; i++) {
    ibcol = i << 2;
    ROBOT_tcp_t_ee[ibcol] = E[3 * i];
    ROBOT_tcp_t_ee[ibcol + 1] = E[3 * i + 1];
    ROBOT_tcp_t_ee[ibcol + 2] = E[3 * i + 2];
  }
  ROBOT_tcp_t_ee[12] = arm_length[static_cast<int>(num_links) - 1];
  ROBOT_tcp_t_ee[13] = 0.0;
  ROBOT_tcp_t_ee[14] = 0.0;
  ROBOT_tcp_t_ee[3] = 0.0;
  ROBOT_tcp_t_ee[7] = 0.0;
  ROBOT_tcp_t_ee[11] = 0.0;
  ROBOT_tcp_t_ee[15] = 1.0;
  //  reshape signals
  currentG0Index = static_cast<double>(ROBOT_g0.size(0)) / 4.0;
  loop_ub_tmp = static_cast<int>(currentG0Index);
  q.set_size(loop_ub_tmp);
  dq.set_size(loop_ub_tmp);
  //  pre-allocate memory for variables
  M.set_size(loop_ub_tmp, loop_ub_tmp);
  b_loop_ub_tmp =
      static_cast<int>(currentG0Index) * static_cast<int>(currentG0Index);
  CC.set_size(loop_ub_tmp, loop_ub_tmp);
  for (i = 0; i < b_loop_ub_tmp; i++) {
    M[i] = 0.0;
    CC[i] = 0.0;
  }
  g.set_size(loop_ub_tmp);
  for (i = 0; i < loop_ub_tmp; i++) {
    g[i] = 0.0;
  }
  J_pre.set_size(6, loop_ub_tmp);
  b_loop_ub_tmp = 6 * static_cast<int>(currentG0Index);
  dJ_pre.set_size(6, loop_ub_tmp);
  for (i = 0; i < b_loop_ub_tmp; i++) {
    J_pre[i] = 0.0;
    dJ_pre[i] = 0.0;
  }
  for (int b_i{0}; b_i < 6; b_i++) {
    inertialTwist_pre[b_i] = 0.0;
  }
  std::memset(&O_Htm_pre[0], 0, 16U * sizeof(double));
  O_Htm_pre[0] = 1.0;
  O_Htm_pre[5] = 1.0;
  O_Htm_pre[10] = 1.0;
  O_Htm_pre[15] = 1.0;
  //  iterate from the root to the end-effector of the serial manipulator
  for (int iLink{0}; iLink < loop_ub_tmp; iLink++) {
    double invAd[36];
    double inertialTwist[6];
    double relTwist[6];
    int idxStart_4Row;
    unsigned int idxStart_6Row;
    signed char x_tmp;
    signed char x_tmp_tmp;
    boolean_T x[3];
    boolean_T exitg1;
    boolean_T y;
    //  initialize indices of the current iteration
    idxStart_4Row = iLink << 2;
    idxStart_6Row = 6U * static_cast<unsigned int>(iLink) + 6U;
    //  compute relative body twist
    if (idxStart_6Row - 5U > idxStart_6Row) {
      i = 3;
    } else {
      i = static_cast<int>(idxStart_6Row) - 3;
    }
    for (i1 = 0; i1 < 6; i1++) {
      relTwist[i1] = static_cast<double>(ROBOT_csi[(i + i1) - 3]) * dq[iLink];
    }
    //  compute relative homogeneous transformation matrix between link and
    //  its parent
    if (idxStart_4Row + 1 > idxStart_4Row + 4) {
      idxStart_4Row = 0;
      i1 = 0;
    } else {
      i1 = idxStart_4Row + 4;
    }
    //  Twist exponential of the relative body jacobian
    //  Implemented by Gianluca Garofalo.
    std::memset(&b_I[0], 0, 9U * sizeof(double));
    b_I[0] = 1.0;
    x[0] = (ROBOT_csi[i] == 0);
    b_I[4] = 1.0;
    x_tmp = ROBOT_csi[i + 1];
    x[1] = (x_tmp == 0);
    b_I[8] = 1.0;
    x_tmp_tmp = ROBOT_csi[i + 2];
    x[2] = (x_tmp_tmp == 0);
    y = true;
    boffset = 0;
    exitg1 = false;
    while ((!exitg1) && (boffset < 3)) {
      if (!x[boffset]) {
        y = false;
        exitg1 = true;
      } else {
        boffset++;
      }
    }
    if (y) {
      for (boffset = 0; boffset < 3; boffset++) {
        ibcol = boffset << 2;
        O_Htm[ibcol] = b_I[3 * boffset];
        O_Htm[ibcol + 1] = b_I[3 * boffset + 1];
        O_Htm[ibcol + 2] = b_I[3 * boffset + 2];
        O_Htm[boffset + 12] =
            static_cast<double>(ROBOT_csi[(i + boffset) - 3]) * q[iLink];
      }
      O_Htm[3] = 0.0;
      O_Htm[7] = 0.0;
      O_Htm[11] = 0.0;
      O_Htm[15] = 1.0;
    } else {
      //  Skew operator
      //  Implemented by Gianluca Garofalo.
      E[0] = 0.0;
      E[3] = -static_cast<double>(x_tmp_tmp);
      E[6] = x_tmp;
      E[1] = x_tmp_tmp;
      E[4] = 0.0;
      E[7] = -static_cast<double>(ROBOT_csi[i]);
      E[2] = -static_cast<double>(x_tmp);
      E[5] = ROBOT_csi[i];
      E[8] = 0.0;
      currentG0Index = std::sin(q[iLink]);
      m = std::cos(q[iLink]);
      for (boffset = 0; boffset < 3; boffset++) {
        for (coffset = 0; coffset < 3; coffset++) {
          c_I[boffset + 3 * coffset] = (E[boffset] * E[3 * coffset] +
                                        E[boffset + 3] * E[3 * coffset + 1]) +
                                       E[boffset + 6] * E[3 * coffset + 2];
        }
      }
      for (boffset = 0; boffset < 3; boffset++) {
        ibcol = boffset << 2;
        O_Htm[ibcol] = b_I[3 * boffset] + (E[3 * boffset] * currentG0Index +
                                           c_I[3 * boffset] * (1.0 - m));
        coffset = 3 * boffset + 1;
        O_Htm[ibcol + 1] = b_I[coffset] + (E[coffset] * currentG0Index +
                                           c_I[coffset] * (1.0 - m));
        coffset = 3 * boffset + 2;
        O_Htm[ibcol + 2] = b_I[coffset] + (E[coffset] * currentG0Index +
                                           c_I[coffset] * (1.0 - m));
        O_Htm[boffset + 12] = 0.0;
      }
      O_Htm[3] = 0.0;
      O_Htm[7] = 0.0;
      O_Htm[11] = 0.0;
      O_Htm[15] = 1.0;
    }
    ibcol = i1 - idxStart_4Row;
    Htm.set_size(ibcol, 4);
    for (int j{0}; j < 4; j++) {
      coffset = j * ibcol;
      boffset = j << 2;
      for (int b_i{0}; b_i < ibcol; b_i++) {
        i1 = ibcol + b_i;
        currentG0Index = ROBOT_g0[(idxStart_4Row + b_i % ibcol) +
                                  ROBOT_g0.size(0) * (b_i / ibcol)] *
                             O_Htm[boffset] +
                         ROBOT_g0[(idxStart_4Row + i1 % ibcol) +
                                  ROBOT_g0.size(0) * (i1 / ibcol)] *
                             O_Htm[boffset + 1];
        i1 = (ibcol << 1) + b_i;
        currentG0Index += ROBOT_g0[(idxStart_4Row + i1 % ibcol) +
                                   ROBOT_g0.size(0) * (i1 / ibcol)] *
                          O_Htm[boffset + 2];
        i1 = 3 * ibcol + b_i;
        currentG0Index += ROBOT_g0[(idxStart_4Row + i1 % ibcol) +
                                   ROBOT_g0.size(0) * (i1 / ibcol)] *
                          O_Htm[boffset + 3];
        Htm[coffset + b_i] = currentG0Index;
      }
    }
    //  propagate rotation matrix, body twists, body jacobians and
    //  derivatives of body jacobians
    for (i1 = 0; i1 < 4; i1++) {
      currentG0Index = O_Htm_pre[i1];
      m = O_Htm_pre[i1 + 4];
      body_CenterOfMass_idx_0 = O_Htm_pre[i1 + 8];
      Iz = O_Htm_pre[i1 + 12];
      for (boffset = 0; boffset < 4; boffset++) {
        coffset = boffset << 2;
        O_Htm[i1 + coffset] =
            ((currentG0Index * Htm[coffset] + m * Htm[coffset + 1]) +
             body_CenterOfMass_idx_0 * Htm[coffset + 2]) +
            Iz * Htm[coffset + 3];
      }
    }
    for (int b_i{0}; b_i < 6; b_i++) {
      inertialTwist[b_i] = relTwist[b_i];
    }
    //  Inverse of the adjoint transformation
    //  Implemented by Gianluca Garofalo.
    for (i1 = 0; i1 < 3; i1++) {
      E[3 * i1] = Htm[i1];
      E[3 * i1 + 1] = Htm[i1 + Htm.size(0)];
      E[3 * i1 + 2] = Htm[i1 + Htm.size(0) * 2];
    }
    //  Skew operator
    //  Implemented by Gianluca Garofalo.
    for (i1 = 0; i1 < 9; i1++) {
      c_I[i1] = -E[i1];
    }
    S[0] = 0.0;
    S[3] = -Htm[Htm.size(0) * 3 + 2];
    S[6] = Htm[Htm.size(0) * 3 + 1];
    S[1] = Htm[Htm.size(0) * 3 + 2];
    S[4] = 0.0;
    S[7] = -Htm[Htm.size(0) * 3];
    S[2] = -Htm[Htm.size(0) * 3 + 1];
    S[5] = Htm[Htm.size(0) * 3];
    S[8] = 0.0;
    for (i1 = 0; i1 < 3; i1++) {
      currentG0Index = c_I[i1];
      m = c_I[i1 + 3];
      body_CenterOfMass_idx_0 = c_I[i1 + 6];
      for (boffset = 0; boffset < 3; boffset++) {
        tmp2[i1 + 3 * boffset] =
            (currentG0Index * S[3 * boffset] + m * S[3 * boffset + 1]) +
            body_CenterOfMass_idx_0 * S[3 * boffset + 2];
        invAd[boffset + 6 * i1] = E[boffset + 3 * i1];
      }
    }
    for (i1 = 0; i1 < 3; i1++) {
      ibcol = 6 * (i1 + 3);
      invAd[ibcol] = tmp2[3 * i1];
      invAd[6 * i1 + 3] = 0.0;
      invAd[ibcol + 3] = E[3 * i1];
      coffset = 3 * i1 + 1;
      invAd[ibcol + 1] = tmp2[coffset];
      invAd[6 * i1 + 4] = 0.0;
      invAd[ibcol + 4] = E[coffset];
      coffset = 3 * i1 + 2;
      invAd[ibcol + 2] = tmp2[coffset];
      invAd[6 * i1 + 5] = 0.0;
      invAd[ibcol + 5] = E[coffset];
    }
    J.set_size(6, loop_ub_tmp);
    dJ.set_size(6, loop_ub_tmp);
    for (i1 = 0; i1 < b_loop_ub_tmp; i1++) {
      J[i1] = 0.0;
      dJ[i1] = 0.0;
    }
    if (iLink + 1 > 1) {
      for (i1 = 0; i1 < 6; i1++) {
        currentG0Index = 0.0;
        for (boffset = 0; boffset < 6; boffset++) {
          currentG0Index +=
              invAd[i1 + 6 * boffset] * inertialTwist_pre[boffset];
        }
        inertialTwist[i1] = relTwist[i1] + currentG0Index;
      }
      J_pre.set_size(6, iLink);
      coder::internal::blas::mtimes(invAd, J_pre, r);
      coffset = r.size(1);
      for (i1 = 0; i1 < coffset; i1++) {
        for (boffset = 0; boffset < 6; boffset++) {
          J[boffset + 6 * i1] = r[boffset + 6 * i1];
        }
      }
      //  Lie bracket of the body twist
      //  Implemented by Gianluca Garofalo.
      //  Skew operator
      //  Implemented by Gianluca Garofalo.
      //  Skew operator
      //  Implemented by Gianluca Garofalo.
      E[0] = 0.0;
      E[3] = -relTwist[5];
      E[6] = relTwist[4];
      E[1] = relTwist[5];
      E[4] = 0.0;
      E[7] = -relTwist[3];
      E[2] = -relTwist[4];
      E[5] = relTwist[3];
      E[8] = 0.0;
      dJ_pre.set_size(6, iLink);
      coder::internal::blas::mtimes(invAd, dJ_pre, r);
      invAd[18] = 0.0;
      invAd[24] = -relTwist[2];
      invAd[30] = relTwist[1];
      invAd[19] = relTwist[2];
      invAd[25] = 0.0;
      invAd[31] = -relTwist[0];
      invAd[20] = -relTwist[1];
      invAd[26] = relTwist[0];
      invAd[32] = 0.0;
      for (i1 = 0; i1 < 3; i1++) {
        currentG0Index = E[3 * i1];
        invAd[6 * i1] = currentG0Index;
        invAd[6 * i1 + 3] = 0.0;
        ibcol = 6 * (i1 + 3);
        invAd[ibcol + 3] = currentG0Index;
        currentG0Index = E[3 * i1 + 1];
        invAd[6 * i1 + 1] = currentG0Index;
        invAd[6 * i1 + 4] = 0.0;
        invAd[ibcol + 4] = currentG0Index;
        currentG0Index = E[3 * i1 + 2];
        invAd[6 * i1 + 2] = currentG0Index;
        invAd[6 * i1 + 5] = 0.0;
        invAd[ibcol + 5] = currentG0Index;
      }
      dJ_pre.set_size(6, iLink);
      for (i1 = 0; i1 < iLink; i1++) {
        for (boffset = 0; boffset < 6; boffset++) {
          dJ_pre[boffset + 6 * i1] = J[boffset + 6 * i1];
        }
      }
      coder::internal::blas::mtimes(invAd, dJ_pre, J_pre);
      if (r.size(1) == J_pre.size(1)) {
        coffset = r.size(1);
        for (i1 = 0; i1 < coffset; i1++) {
          for (boffset = 0; boffset < 6; boffset++) {
            dJ[boffset + 6 * i1] =
                r[boffset + 6 * i1] - J_pre[boffset + 6 * i1];
          }
        }
      } else {
        binary_expand_op(dJ, r, J_pre);
      }
    }
    for (i1 = 0; i1 < 6; i1++) {
      J[i1 + 6 * iLink] = ROBOT_csi[(i + i1) - 3];
    }
    //  update inertia matrix
    if (idxStart_6Row - 5U > idxStart_6Row) {
      i = 0;
      i1 = 0;
    } else {
      i = static_cast<int>(idxStart_6Row) - 6;
      i1 = static_cast<int>(idxStart_6Row);
    }
    dJ_pre.set_size(6, iLink + 1);
    for (boffset = 0; boffset <= iLink; boffset++) {
      for (coffset = 0; coffset < 6; coffset++) {
        dJ_pre[coffset + 6 * boffset] = J[coffset + 6 * boffset];
      }
    }
    coffset = i1 - i;
    b_ROBOT_Mass.set_size(coffset, 6);
    for (i1 = 0; i1 < 6; i1++) {
      for (boffset = 0; boffset < coffset; boffset++) {
        b_ROBOT_Mass[boffset + b_ROBOT_Mass.size(0) * i1] =
            ROBOT_Mass[(i + boffset) + ROBOT_Mass.size(0) * i1];
      }
    }
    coder::internal::blas::mtimes(dJ_pre, b_ROBOT_Mass, tmp);
    dJ_pre.set_size(6, iLink + 1);
    for (i = 0; i <= iLink; i++) {
      for (i1 = 0; i1 < 6; i1++) {
        dJ_pre[i1 + 6 * i] = J[i1 + 6 * i];
      }
    }
    coder::internal::blas::b_mtimes(tmp, dJ_pre, tmptmp);
    if ((iLink + 1 == tmptmp.size(0)) && (iLink + 1 == tmptmp.size(1))) {
      tmptmp.set_size(iLink + 1, iLink + 1);
      for (i = 0; i <= iLink; i++) {
        for (i1 = 0; i1 <= iLink; i1++) {
          tmptmp[i1 + tmptmp.size(0) * i] =
              M[i1 + M.size(0) * i] + tmptmp[i1 + tmptmp.size(0) * i];
        }
      }
      coffset = tmptmp.size(1);
      ibcol = tmptmp.size(0);
      for (i = 0; i < coffset; i++) {
        for (i1 = 0; i1 < ibcol; i1++) {
          M[i1 + M.size(0) * i] = tmptmp[i1 + tmptmp.size(0) * i];
        }
      }
    } else {
      binary_expand_op(M, iLink, tmptmp);
    }
    //  update Cor.\centrifugal matrix
    //  Method 1: Original version from [1]
    //  Mass_x_ad_tmp = ROBOT.Mass(idxStart_6Row:idxEnd_6Row, 1:6) *
    //  LieBracket(inertialTwist); Mass_x_ad_tmp = Mass_x_ad_tmp -
    //  Mass_x_ad_tmp';
    if (idxStart_6Row - 5U > idxStart_6Row) {
      i = 3;
    } else {
      i = static_cast<int>(idxStart_6Row) - 3;
    }
    //  Skew operator
    //  Implemented by Gianluca Garofalo.
    E[0] = 0.0;
    E[3] = -inertialTwist[5];
    E[6] = inertialTwist[4];
    E[1] = inertialTwist[5];
    E[4] = 0.0;
    E[7] = -inertialTwist[3];
    E[2] = -inertialTwist[4];
    E[5] = inertialTwist[3];
    E[8] = 0.0;
    for (i1 = 0; i1 < 3; i1++) {
      boffset = i + i1;
      for (coffset = 0; coffset < 3; coffset++) {
        currentG0Index = E[3 * coffset];
        m = ROBOT_Mass[boffset] * currentG0Index;
        body_CenterOfMass_idx_0 =
            ROBOT_Mass[boffset + ROBOT_Mass.size(0) * 3] * currentG0Index;
        currentG0Index = E[3 * coffset + 1];
        m += ROBOT_Mass[boffset + ROBOT_Mass.size(0)] * currentG0Index;
        body_CenterOfMass_idx_0 +=
            ROBOT_Mass[boffset + ROBOT_Mass.size(0) * 4] * currentG0Index;
        currentG0Index = E[3 * coffset + 2];
        m += ROBOT_Mass[boffset + ROBOT_Mass.size(0) * 2] * currentG0Index;
        body_CenterOfMass_idx_0 +=
            ROBOT_Mass[boffset + ROBOT_Mass.size(0) * 5] * currentG0Index;
        ibcol = i1 + 3 * coffset;
        tmp2[ibcol] = body_CenterOfMass_idx_0;
        S[ibcol] = m;
      }
    }
    currentG0Index = ROBOT_Mass[i - 3];
    dJ_pre.set_size(6, iLink + 1);
    for (i = 0; i <= iLink; i++) {
      for (i1 = 0; i1 < 6; i1++) {
        dJ_pre[i1 + 6 * i] = J[i1 + 6 * i];
      }
    }
    for (i = 0; i < 3; i++) {
      invAd[6 * i] = currentG0Index * E[3 * i];
      ibcol = 6 * (i + 3);
      invAd[ibcol] = -S[i];
      invAd[6 * i + 3] = S[3 * i];
      invAd[ibcol + 3] = tmp2[3 * i] - tmp2[i];
      coffset = 3 * i + 1;
      invAd[6 * i + 1] = currentG0Index * E[coffset];
      invAd[ibcol + 1] = -S[i + 3];
      invAd[6 * i + 4] = S[coffset];
      invAd[ibcol + 4] = tmp2[coffset] - tmp2[i + 3];
      coffset = 3 * i + 2;
      invAd[6 * i + 2] = currentG0Index * E[coffset];
      invAd[ibcol + 2] = -S[i + 6];
      invAd[6 * i + 5] = S[coffset];
      invAd[ibcol + 5] = tmp2[coffset] - tmp2[i + 6];
    }
    coder::internal::blas::mtimes(dJ_pre, invAd, b_ROBOT_Mass);
    dJ_pre.set_size(6, iLink + 1);
    for (i = 0; i <= iLink; i++) {
      for (i1 = 0; i1 < 6; i1++) {
        dJ_pre[i1 + 6 * i] = J[i1 + 6 * i];
      }
    }
    coder::internal::blas::b_mtimes(b_ROBOT_Mass, dJ_pre, tmptmp);
    dJ_pre.set_size(6, iLink + 1);
    for (i = 0; i <= iLink; i++) {
      for (i1 = 0; i1 < 6; i1++) {
        dJ_pre[i1 + 6 * i] = dJ[i1 + 6 * i];
      }
    }
    coder::internal::blas::b_mtimes(tmp, dJ_pre, r1);
    if (iLink + 1 == 1) {
      i = tmptmp.size(0);
      i1 = tmptmp.size(1);
    } else {
      i = iLink + 1;
      i1 = iLink + 1;
    }
    if ((iLink + 1 == tmptmp.size(0)) && (iLink + 1 == tmptmp.size(1)) &&
        (i == r1.size(0)) && (i1 == r1.size(1))) {
      tmptmp.set_size(iLink + 1, iLink + 1);
      for (i = 0; i <= iLink; i++) {
        for (i1 = 0; i1 <= iLink; i1++) {
          tmptmp[i1 + tmptmp.size(0) * i] =
              (CC[i1 + CC.size(0) * i] + tmptmp[i1 + tmptmp.size(0) * i]) +
              r1[i1 + r1.size(0) * i];
        }
      }
      coffset = tmptmp.size(1);
      ibcol = tmptmp.size(0);
      for (i = 0; i < coffset; i++) {
        for (i1 = 0; i1 < ibcol; i1++) {
          CC[i1 + CC.size(0) * i] = tmptmp[i1 + tmptmp.size(0) * i];
        }
      }
    } else {
      binary_expand_op(CC, iLink, tmptmp, r1);
    }
    //  update gravity torque vector
    C.set_size(iLink + 1, 3);
    for (int j{0}; j < 3; j++) {
      coffset = j * (iLink + 1);
      for (int b_i{0}; b_i <= iLink; b_i++) {
        i = (iLink + b_i) + 1;
        currentG0Index =
            tmp[b_i % (iLink + 1) + tmp.size(0) * (b_i / (iLink + 1))] *
                O_Htm[j % 3] +
            tmp[i % (iLink + 1) + tmp.size(0) * (i / (iLink + 1))] *
                O_Htm[(j + 3) % 3 + 4];
        i = ((iLink + 1) << 1) + b_i;
        currentG0Index +=
            tmp[i % (iLink + 1) + tmp.size(0) * (i / (iLink + 1))] *
            O_Htm[(j + 6) % 3 + 8];
        C[coffset + b_i] = currentG0Index;
      }
    }
    ibcol = C.size(0);
    b_C.set_size(C.size(0));
    for (int b_i{0}; b_i < ibcol; b_i++) {
      b_C[b_i] = (C[b_i] * 0.0 + C[C.size(0) + b_i] * 0.0) +
                 C[(C.size(0) << 1) + b_i] * 0.0;
    }
    if (iLink + 1 == b_C.size(0)) {
      b_g.set_size(1, iLink + 1);
      coffset = iLink + 1;
      for (i = 0; i < coffset; i++) {
        b_g[i] = g[i] + b_C[i];
      }
      coffset = b_g.size(1);
      for (i = 0; i < coffset; i++) {
        g[i] = b_g[i];
      }
    } else {
      binary_expand_op(g, iLink, b_C);
    }
    //  update variables of parent link
    J_pre.set_size(6, J.size(1));
    for (i = 0; i < b_loop_ub_tmp; i++) {
      J_pre[i] = J[i];
    }
    dJ_pre.set_size(6, dJ.size(1));
    coffset = 6 * dJ.size(1);
    for (i = 0; i < coffset; i++) {
      dJ_pre[i] = dJ[i];
    }
    for (int b_i{0}; b_i < 6; b_i++) {
      inertialTwist_pre[b_i] = inertialTwist[b_i];
    }
    std::copy(&O_Htm[0], &O_Htm[16], &O_Htm_pre[0]);
  }
  for (i = 0; i < 4; i++) {
    currentG0Index = O_Htm[i];
    m = O_Htm[i + 4];
    body_CenterOfMass_idx_0 = O_Htm[i + 8];
    Iz = O_Htm[i + 12];
    for (i1 = 0; i1 < 4; i1++) {
      boffset = i1 << 2;
      O_Htm_pre[i + boffset] =
          ((currentG0Index * ROBOT_tcp_t_ee[boffset] +
            m * ROBOT_tcp_t_ee[boffset + 1]) +
           body_CenterOfMass_idx_0 * ROBOT_tcp_t_ee[boffset + 2]) +
          Iz * ROBOT_tcp_t_ee[boffset + 3];
    }
  }
  pos_tcp[0] = O_Htm_pre[12];
  pos_tcp[1] = O_Htm_pre[13];
  pos_tcp[2] = O_Htm_pre[14];
  //  Inverse of the adjoint transformation
  //  Implemented by Gianluca Garofalo.
  //  Skew operator
  //  Implemented by Gianluca Garofalo.
  tmptmp.set_size(CC.size(0), CC.size(1));
  coffset = CC.size(0) * CC.size(1);
  for (i = 0; i < coffset; i++) {
    tmptmp[i] = -CC[i];
  }
  coder::internal::blas::mtimes(tmptmp, dq, joint_acc);
  if (joint_acc.size(0) == 1) {
    i = torque.size(0);
  } else {
    i = joint_acc.size(0);
  }
  if ((joint_acc.size(0) == torque.size(0)) && (i == g.size(0))) {
    coffset = joint_acc.size(0);
    for (i = 0; i < coffset; i++) {
      joint_acc[i] = (joint_acc[i] + torque[i]) - g[i];
    }
  } else {
    binary_expand_op(joint_acc, torque, g);
  }
  coder::mldivide(M, joint_acc);
}

//
// File trailer for robot_chain_dynamics.cpp
//
// [EOF]
//
