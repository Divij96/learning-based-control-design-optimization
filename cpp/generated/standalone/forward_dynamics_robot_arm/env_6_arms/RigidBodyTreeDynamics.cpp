//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: RigidBodyTreeDynamics.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 14-Feb-2024 19:42:36
//

// Include Files
#include "RigidBodyTreeDynamics.h"
#include "RigidBody.h"
#include "RigidBodyTree1.h"
#include "find.h"
#include "mtimes.h"
#include "rigidBodyJoint.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <algorithm>
#include <cmath>
#include <cstring>

// Type Definitions
struct cell_wrap_31 {
  double f1[36];
};

// Function Declarations
static void binary_expand_op(coder::array<double, 2U> &in1, int in2,
                             const coder::array<double, 2U> &in4,
                             const coder::array<signed char, 2U> &in5);

// Function Definitions
//
// Arguments    : coder::array<double, 2U> &in1
//                int in2
//                const coder::array<double, 2U> &in4
//                const coder::array<signed char, 2U> &in5
// Return Type  : void
//
static void binary_expand_op(coder::array<double, 2U> &in1, int in2,
                             const coder::array<double, 2U> &in4,
                             const coder::array<signed char, 2U> &in5)
{
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  stride_0_1 = (in4.size(1) != 1);
  stride_1_1 = (in5.size(1) != 1);
  if (in5.size(1) == 1) {
    loop_ub = in4.size(1);
  } else {
    loop_ub = in5.size(1);
  }
  for (int i{0}; i < loop_ub; i++) {
    in1[in2 + i] =
        in4[i * stride_0_1] - static_cast<double>(in5[i * stride_1_1]);
  }
}

//
// Arguments    : b_RigidBodyTree &robot
//                const double q_data[]
//                const double qdot_data[]
//                const ::coder::array<double, 2U> &fext
//                double tau_data[]
// Return Type  : int
//
namespace coder {
namespace robotics {
namespace manip {
namespace internal {
int RigidBodyTreeDynamics::inverseDynamics(
    b_RigidBodyTree &robot, const double q_data[], const double qdot_data[],
    const ::coder::array<double, 2U> &fext, double tau_data[])
{
  static const char b_cv[5]{'f', 'i', 'x', 'e', 'd'};
  b_RigidBody *obj;
  rigidBodyJoint *jnt;
  array<cell_wrap_31, 2U> X;
  array<cell_wrap_31, 2U> Xtree;
  array<double, 2U> S;
  array<double, 2U> aB;
  array<double, 2U> f;
  array<double, 2U> vB;
  array<double, 2U> vJ;
  array<double, 2U> y;
  array<double, 1U> taui;
  array<char, 2U> a;
  double XDHOffset[36];
  double TDHOffset[16];
  double R[9];
  double b_R[9];
  double a0[6];
  double b_q_data[6];
  double c_R[3];
  double a_idx_0;
  double a_idx_1;
  double b_idx_0;
  double b_idx_1;
  double nb;
  int aoffset;
  int i;
  int i1;
  int j;
  int loop_ub_tmp;
  int tau_size;
  a0[0] = 0.0;
  a0[1] = 0.0;
  a0[2] = 0.0;
  a0[3] = -robot.Gravity[0];
  a0[4] = -robot.Gravity[1];
  a0[5] = -robot.Gravity[2];
  nb = robot.NumBodies;
  i = static_cast<int>(nb);
  X.set_size(1, i);
  Xtree.set_size(1, i);
  vJ.set_size(6, i);
  loop_ub_tmp = 6 * static_cast<int>(nb);
  vB.set_size(6, i);
  aB.set_size(6, i);
  for (j = 0; j < loop_ub_tmp; j++) {
    vJ[j] = 0.0;
    vB[j] = 0.0;
    aB[j] = 0.0;
  }
  f.set_size(6, i);
  tau_size = 6;
  for (j = 0; j < 6; j++) {
    tau_data[j] = 0.0;
  }
  for (int k{0}; k < i; k++) {
    std::memset(&XDHOffset[0], 0, 36U * sizeof(double));
    for (loop_ub_tmp = 0; loop_ub_tmp < 6; loop_ub_tmp++) {
      XDHOffset[loop_ub_tmp + 6 * loop_ub_tmp] = 1.0;
    }
    for (j = 0; j < 36; j++) {
      Xtree[k].f1[j] = XDHOffset[j];
      X[k].f1[j] = XDHOffset[j];
    }
  }
  for (int b_i{0}; b_i < i; b_i++) {
    double d_R[36];
    double T[16];
    double b_X[6];
    obj = robot.Bodies[b_i];
    jnt = obj->JointInternal;
    S.set_size(6, jnt->MotionSubspace.size(1));
    loop_ub_tmp = 6 * jnt->MotionSubspace.size(1);
    for (j = 0; j < loop_ub_tmp; j++) {
      S[j] = jnt->MotionSubspace[j];
    }
    a_idx_0 = robot.PositionDoFMap[b_i];
    a_idx_1 = robot.PositionDoFMap[b_i + 7];
    b_idx_0 = robot.VelocityDoFMap[b_i];
    b_idx_1 = robot.VelocityDoFMap[b_i + 7];
    std::memset(&XDHOffset[0], 0, 36U * sizeof(double));
    for (int k{0}; k < 6; k++) {
      XDHOffset[k + 6 * k] = 1.0;
    }
    if (a_idx_1 < a_idx_0) {
      obj = robot.Bodies[b_i];
      jnt = obj->JointInternal;
      jnt->transformBodyToParent(T);
      for (j = 0; j < 6; j++) {
        vJ[j + 6 * b_i] = 0.0;
      }
    } else {
      if (a_idx_0 > a_idx_1) {
        j = 0;
        aoffset = 0;
      } else {
        j = static_cast<int>(a_idx_0) - 1;
        aoffset = static_cast<int>(a_idx_1);
      }
      if (b_idx_0 > b_idx_1) {
        i1 = 0;
      } else {
        i1 = static_cast<int>(b_idx_0) - 1;
      }
      obj = robot.Bodies[b_i];
      jnt = obj->JointInternal;
      loop_ub_tmp = aoffset - j;
      for (aoffset = 0; aoffset < loop_ub_tmp; aoffset++) {
        b_q_data[aoffset] = q_data[j + aoffset];
      }
      jnt->transformBodyToParent(b_q_data, loop_ub_tmp, T);
      obj = robot.Bodies[b_i];
      jnt = obj->JointInternal;
      for (j = 0; j < 16; j++) {
        TDHOffset[j] = jnt->ChildToJointTransform[j];
      }
      for (j = 0; j < 3; j++) {
        R[3 * j] = TDHOffset[j];
        R[3 * j + 1] = TDHOffset[j + 4];
        R[3 * j + 2] = TDHOffset[j + 8];
      }
      for (j = 0; j < 9; j++) {
        b_R[j] = -R[j];
      }
      for (j = 0; j < 3; j++) {
        a_idx_0 = b_R[j] * TDHOffset[12];
        loop_ub_tmp = j << 2;
        TDHOffset[loop_ub_tmp] = R[3 * j];
        a_idx_0 += b_R[j + 3] * TDHOffset[13];
        TDHOffset[loop_ub_tmp + 1] = R[3 * j + 1];
        a_idx_0 += b_R[j + 6] * TDHOffset[14];
        TDHOffset[loop_ub_tmp + 2] = R[3 * j + 2];
        c_R[j] = a_idx_0;
      }
      TDHOffset[12] = c_R[0];
      TDHOffset[13] = c_R[1];
      TDHOffset[14] = c_R[2];
      TDHOffset[3] = 0.0;
      TDHOffset[7] = 0.0;
      TDHOffset[11] = 0.0;
      TDHOffset[15] = 1.0;
      R[0] = 0.0;
      R[3] = -c_R[2];
      R[6] = c_R[1];
      R[1] = c_R[2];
      R[4] = 0.0;
      R[7] = -c_R[0];
      R[2] = -c_R[1];
      R[5] = c_R[0];
      R[8] = 0.0;
      for (j = 0; j < 3; j++) {
        a_idx_0 = R[j];
        a_idx_1 = R[j + 3];
        b_idx_0 = R[j + 6];
        for (aoffset = 0; aoffset < 3; aoffset++) {
          loop_ub_tmp = aoffset << 2;
          b_R[j + 3 * aoffset] = (a_idx_0 * TDHOffset[loop_ub_tmp] +
                                  a_idx_1 * TDHOffset[loop_ub_tmp + 1]) +
                                 b_idx_0 * TDHOffset[loop_ub_tmp + 2];
          XDHOffset[aoffset + 6 * j] = TDHOffset[aoffset + (j << 2)];
          XDHOffset[aoffset + 6 * (j + 3)] = 0.0;
        }
      }
      for (j = 0; j < 3; j++) {
        XDHOffset[6 * j + 3] = b_R[3 * j];
        loop_ub_tmp = j << 2;
        aoffset = 6 * (j + 3);
        XDHOffset[aoffset + 3] = TDHOffset[loop_ub_tmp];
        XDHOffset[6 * j + 4] = b_R[3 * j + 1];
        XDHOffset[aoffset + 4] = TDHOffset[loop_ub_tmp + 1];
        XDHOffset[6 * j + 5] = b_R[3 * j + 2];
        XDHOffset[aoffset + 5] = TDHOffset[loop_ub_tmp + 2];
      }
      loop_ub_tmp = S.size(1);
      y.set_size(6, S.size(1));
      for (j = 0; j < loop_ub_tmp; j++) {
        aoffset = j * 6;
        for (int d_i{0}; d_i < 6; d_i++) {
          a_idx_0 = 0.0;
          for (int k{0}; k < 6; k++) {
            a_idx_0 += XDHOffset[k * 6 + d_i] * S[aoffset + k];
          }
          y[aoffset + d_i] = a_idx_0;
        }
      }
      loop_ub_tmp = y.size(1);
      for (int d_i{0}; d_i < 6; d_i++) {
        vJ[d_i + 6 * b_i] = 0.0;
      }
      for (int k{0}; k < loop_ub_tmp; k++) {
        aoffset = k * 6;
        for (int d_i{0}; d_i < 6; d_i++) {
          vJ[d_i + 6 * b_i] =
              vJ[d_i + 6 * b_i] + y[aoffset + d_i] * qdot_data[i1 + k];
        }
      }
    }
    for (j = 0; j < 3; j++) {
      R[3 * j] = T[j];
      R[3 * j + 1] = T[j + 4];
      R[3 * j + 2] = T[j + 8];
    }
    for (j = 0; j < 9; j++) {
      b_R[j] = -R[j];
    }
    a_idx_0 = T[12];
    a_idx_1 = T[13];
    b_idx_0 = T[14];
    for (j = 0; j < 3; j++) {
      loop_ub_tmp = j << 2;
      TDHOffset[loop_ub_tmp] = R[3 * j];
      TDHOffset[loop_ub_tmp + 1] = R[3 * j + 1];
      TDHOffset[loop_ub_tmp + 2] = R[3 * j + 2];
      TDHOffset[j + 12] =
          (b_R[j] * a_idx_0 + b_R[j + 3] * a_idx_1) + b_R[j + 6] * b_idx_0;
    }
    TDHOffset[3] = 0.0;
    TDHOffset[7] = 0.0;
    TDHOffset[11] = 0.0;
    TDHOffset[15] = 1.0;
    R[0] = 0.0;
    R[3] = -TDHOffset[14];
    R[6] = TDHOffset[13];
    R[1] = TDHOffset[14];
    R[4] = 0.0;
    R[7] = -TDHOffset[12];
    R[2] = -TDHOffset[13];
    R[5] = TDHOffset[12];
    R[8] = 0.0;
    for (j = 0; j < 3; j++) {
      a_idx_0 = R[j];
      a_idx_1 = R[j + 3];
      b_idx_0 = R[j + 6];
      for (aoffset = 0; aoffset < 3; aoffset++) {
        i1 = aoffset << 2;
        b_R[j + 3 * aoffset] =
            (a_idx_0 * TDHOffset[i1] + a_idx_1 * TDHOffset[i1 + 1]) +
            b_idx_0 * TDHOffset[i1 + 2];
        X[b_i].f1[aoffset + 6 * j] = TDHOffset[aoffset + (j << 2)];
        X[b_i].f1[aoffset + 6 * (j + 3)] = 0.0;
      }
    }
    for (j = 0; j < 3; j++) {
      X[b_i].f1[6 * j + 3] = b_R[3 * j];
      aoffset = j << 2;
      i1 = 6 * (j + 3);
      X[b_i].f1[i1 + 3] = TDHOffset[aoffset];
      X[b_i].f1[6 * j + 4] = b_R[3 * j + 1];
      X[b_i].f1[i1 + 4] = TDHOffset[aoffset + 1];
      X[b_i].f1[6 * j + 5] = b_R[3 * j + 2];
      X[b_i].f1[i1 + 5] = TDHOffset[aoffset + 2];
    }
    b_idx_1 = robot.Bodies[b_i]->ParentIndex;
    if (b_idx_1 > 0.0) {
      double e_R[6];
      for (j = 0; j < 6; j++) {
        a_idx_0 = 0.0;
        for (aoffset = 0; aoffset < 6; aoffset++) {
          a_idx_0 += X[b_i].f1[j + 6 * aoffset] *
                     vB[aoffset + 6 * (static_cast<int>(b_idx_1) - 1)];
        }
        b_q_data[j] = vJ[j + 6 * b_i] + a_idx_0;
      }
      for (j = 0; j < 6; j++) {
        vB[j + 6 * b_i] = b_q_data[j];
      }
      loop_ub_tmp = S.size(1);
      y.set_size(6, S.size(1));
      for (j = 0; j < loop_ub_tmp; j++) {
        aoffset = j * 6;
        for (int d_i{0}; d_i < 6; d_i++) {
          a_idx_0 = 0.0;
          for (int k{0}; k < 6; k++) {
            a_idx_0 += XDHOffset[k * 6 + d_i] * S[aoffset + k];
          }
          y[aoffset + d_i] = a_idx_0;
        }
      }
      loop_ub_tmp = y.size(1);
      for (int d_i{0}; d_i < 6; d_i++) {
        b_q_data[d_i] = 0.0;
      }
      for (int k{0}; k < loop_ub_tmp; k++) {
        aoffset = k * 6;
        for (int d_i{0}; d_i < 6; d_i++) {
          b_q_data[d_i] += y[aoffset + d_i] * 0.0;
        }
      }
      R[0] = 0.0;
      a_idx_0 = vB[6 * b_i + 2];
      R[3] = -a_idx_0;
      a_idx_1 = vB[6 * b_i + 1];
      R[6] = a_idx_1;
      R[1] = a_idx_0;
      R[4] = 0.0;
      a_idx_0 = vB[6 * b_i];
      R[7] = -a_idx_0;
      R[2] = -a_idx_1;
      R[5] = a_idx_0;
      R[8] = 0.0;
      d_R[3] = 0.0;
      a_idx_0 = vB[6 * b_i + 5];
      d_R[9] = -a_idx_0;
      a_idx_1 = vB[6 * b_i + 4];
      d_R[15] = a_idx_1;
      d_R[4] = a_idx_0;
      d_R[10] = 0.0;
      a_idx_0 = vB[6 * b_i + 3];
      d_R[16] = -a_idx_0;
      d_R[5] = -a_idx_1;
      d_R[11] = a_idx_0;
      d_R[17] = 0.0;
      for (j = 0; j < 3; j++) {
        a_idx_0 = R[3 * j];
        d_R[6 * j] = a_idx_0;
        loop_ub_tmp = 6 * (j + 3);
        d_R[loop_ub_tmp] = 0.0;
        d_R[loop_ub_tmp + 3] = a_idx_0;
        a_idx_0 = R[3 * j + 1];
        d_R[6 * j + 1] = a_idx_0;
        d_R[loop_ub_tmp + 1] = 0.0;
        d_R[loop_ub_tmp + 4] = a_idx_0;
        a_idx_0 = R[3 * j + 2];
        d_R[6 * j + 2] = a_idx_0;
        d_R[loop_ub_tmp + 2] = 0.0;
        d_R[loop_ub_tmp + 5] = a_idx_0;
      }
      for (j = 0; j < 6; j++) {
        a_idx_0 = 0.0;
        a_idx_1 = 0.0;
        for (aoffset = 0; aoffset < 6; aoffset++) {
          i1 = j + 6 * aoffset;
          a_idx_0 +=
              X[b_i].f1[i1] * aB[aoffset + 6 * (static_cast<int>(b_idx_1) - 1)];
          a_idx_1 += d_R[i1] * vJ[aoffset + 6 * b_i];
        }
        e_R[j] = a_idx_1;
        b_X[j] = a_idx_0 + b_q_data[j];
      }
      for (j = 0; j < 6; j++) {
        aB[j + 6 * b_i] = b_X[j] + e_R[j];
      }
      R[0] = 0.0;
      R[3] = -T[14];
      R[6] = T[13];
      R[1] = T[14];
      R[4] = 0.0;
      R[7] = -T[12];
      R[2] = -T[13];
      R[5] = T[12];
      R[8] = 0.0;
      for (j = 0; j < 3; j++) {
        a_idx_0 = R[j];
        a_idx_1 = R[j + 3];
        b_idx_0 = R[j + 6];
        for (aoffset = 0; aoffset < 3; aoffset++) {
          i1 = aoffset << 2;
          b_R[j + 3 * aoffset] =
              (a_idx_0 * T[i1] + a_idx_1 * T[i1 + 1]) + b_idx_0 * T[i1 + 2];
          XDHOffset[aoffset + 6 * j] = T[aoffset + (j << 2)];
          XDHOffset[aoffset + 6 * (j + 3)] = 0.0;
        }
      }
      for (j = 0; j < 3; j++) {
        XDHOffset[6 * j + 3] = b_R[3 * j];
        loop_ub_tmp = j << 2;
        aoffset = 6 * (j + 3);
        XDHOffset[aoffset + 3] = T[loop_ub_tmp];
        XDHOffset[6 * j + 4] = b_R[3 * j + 1];
        XDHOffset[aoffset + 4] = T[loop_ub_tmp + 1];
        XDHOffset[6 * j + 5] = b_R[3 * j + 2];
        XDHOffset[aoffset + 5] = T[loop_ub_tmp + 2];
      }
      for (j = 0; j < 6; j++) {
        for (aoffset = 0; aoffset < 6; aoffset++) {
          a_idx_0 = 0.0;
          for (i1 = 0; i1 < 6; i1++) {
            a_idx_0 += Xtree[static_cast<int>(b_idx_1) - 1].f1[j + 6 * i1] *
                       XDHOffset[i1 + 6 * aoffset];
          }
          d_R[j + 6 * aoffset] = a_idx_0;
        }
      }
      for (j = 0; j < 36; j++) {
        Xtree[b_i].f1[j] = d_R[j];
      }
    } else {
      for (j = 0; j < 6; j++) {
        vB[j + 6 * b_i] = vJ[j + 6 * b_i];
      }
      loop_ub_tmp = S.size(1);
      y.set_size(6, S.size(1));
      for (j = 0; j < loop_ub_tmp; j++) {
        aoffset = j * 6;
        for (int d_i{0}; d_i < 6; d_i++) {
          a_idx_0 = 0.0;
          for (int k{0}; k < 6; k++) {
            a_idx_0 += XDHOffset[k * 6 + d_i] * S[aoffset + k];
          }
          y[aoffset + d_i] = a_idx_0;
        }
      }
      loop_ub_tmp = y.size(1);
      for (int d_i{0}; d_i < 6; d_i++) {
        b_q_data[d_i] = 0.0;
      }
      for (int k{0}; k < loop_ub_tmp; k++) {
        aoffset = k * 6;
        for (int d_i{0}; d_i < 6; d_i++) {
          b_q_data[d_i] += y[aoffset + d_i] * 0.0;
        }
      }
      for (j = 0; j < 6; j++) {
        a_idx_0 = 0.0;
        for (aoffset = 0; aoffset < 6; aoffset++) {
          a_idx_0 += X[b_i].f1[j + 6 * aoffset] * a0[aoffset];
        }
        aB[j + 6 * b_i] = a_idx_0 + b_q_data[j];
      }
      R[0] = 0.0;
      R[3] = -T[14];
      R[6] = T[13];
      R[1] = T[14];
      R[4] = 0.0;
      R[7] = -T[12];
      R[2] = -T[13];
      R[5] = T[12];
      R[8] = 0.0;
      for (j = 0; j < 3; j++) {
        a_idx_0 = R[j];
        a_idx_1 = R[j + 3];
        b_idx_0 = R[j + 6];
        for (aoffset = 0; aoffset < 3; aoffset++) {
          i1 = aoffset << 2;
          b_R[j + 3 * aoffset] =
              (a_idx_0 * T[i1] + a_idx_1 * T[i1 + 1]) + b_idx_0 * T[i1 + 2];
          Xtree[b_i].f1[aoffset + 6 * j] = T[aoffset + (j << 2)];
          Xtree[b_i].f1[aoffset + 6 * (j + 3)] = 0.0;
        }
      }
      for (j = 0; j < 3; j++) {
        Xtree[b_i].f1[6 * j + 3] = b_R[3 * j];
        aoffset = j << 2;
        i1 = 6 * (j + 3);
        Xtree[b_i].f1[i1 + 3] = T[aoffset];
        Xtree[b_i].f1[6 * j + 4] = b_R[3 * j + 1];
        Xtree[b_i].f1[i1 + 4] = T[aoffset + 1];
        Xtree[b_i].f1[6 * j + 5] = b_R[3 * j + 2];
        Xtree[b_i].f1[i1 + 5] = T[aoffset + 2];
      }
    }
    for (j = 0; j < 36; j++) {
      XDHOffset[j] = robot.Bodies[b_i]->SpatialInertia[j];
    }
    R[0] = 0.0;
    a_idx_0 = vB[6 * b_i + 2];
    R[3] = -a_idx_0;
    a_idx_1 = vB[6 * b_i + 1];
    R[6] = a_idx_1;
    R[1] = a_idx_0;
    R[4] = 0.0;
    a_idx_0 = vB[6 * b_i];
    R[7] = -a_idx_0;
    R[2] = -a_idx_1;
    R[5] = a_idx_0;
    R[8] = 0.0;
    d_R[18] = 0.0;
    a_idx_0 = vB[6 * b_i + 5];
    d_R[24] = -a_idx_0;
    a_idx_1 = vB[6 * b_i + 4];
    d_R[30] = a_idx_1;
    d_R[19] = a_idx_0;
    d_R[25] = 0.0;
    a_idx_0 = vB[6 * b_i + 3];
    d_R[31] = -a_idx_0;
    d_R[20] = -a_idx_1;
    d_R[26] = a_idx_0;
    d_R[32] = 0.0;
    for (j = 0; j < 3; j++) {
      a_idx_0 = R[3 * j];
      d_R[6 * j] = a_idx_0;
      d_R[6 * j + 3] = 0.0;
      loop_ub_tmp = 6 * (j + 3);
      d_R[loop_ub_tmp + 3] = a_idx_0;
      a_idx_0 = R[3 * j + 1];
      d_R[6 * j + 1] = a_idx_0;
      d_R[6 * j + 4] = 0.0;
      d_R[loop_ub_tmp + 4] = a_idx_0;
      a_idx_0 = R[3 * j + 2];
      d_R[6 * j + 2] = a_idx_0;
      d_R[6 * j + 5] = 0.0;
      d_R[loop_ub_tmp + 5] = a_idx_0;
    }
    for (j = 0; j < 6; j++) {
      a_idx_0 = 0.0;
      a_idx_1 = 0.0;
      for (aoffset = 0; aoffset < 6; aoffset++) {
        b_idx_0 = XDHOffset[j + 6 * aoffset];
        a_idx_0 += b_idx_0 * vB[aoffset + 6 * b_i];
        a_idx_1 += b_idx_0 * aB[aoffset + 6 * b_i];
      }
      b_X[j] = a_idx_1;
      b_q_data[j] = a_idx_0;
    }
    for (j = 0; j < 6; j++) {
      a_idx_0 = 0.0;
      a_idx_1 = 0.0;
      for (aoffset = 0; aoffset < 6; aoffset++) {
        a_idx_1 += d_R[j + 6 * aoffset] * b_q_data[aoffset];
        a_idx_0 += Xtree[b_i].f1[aoffset + 6 * j] * fext[aoffset + 6 * b_i];
      }
      f[j + 6 * b_i] = (b_X[j] + a_idx_1) - a_idx_0;
    }
  }
  i = static_cast<int>(-((-1.0 - nb) + 1.0));
  for (int b_i{0}; b_i < i; b_i++) {
    double c_i;
    boolean_T b_bool;
    c_i = nb - static_cast<double>(b_i);
    obj = robot.Bodies[static_cast<int>(c_i) - 1];
    jnt = obj->JointInternal;
    a.set_size(1, jnt->Type.size(1));
    loop_ub_tmp = jnt->Type.size(1);
    for (j = 0; j < loop_ub_tmp; j++) {
      a[j] = jnt->Type[j];
    }
    b_bool = false;
    if (a.size(1) == 5) {
      loop_ub_tmp = 0;
      int exitg1;
      do {
        exitg1 = 0;
        if (loop_ub_tmp < 5) {
          if (a[loop_ub_tmp] != b_cv[loop_ub_tmp]) {
            exitg1 = 1;
          } else {
            loop_ub_tmp++;
          }
        } else {
          b_bool = true;
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }
    if (!b_bool) {
      obj = robot.Bodies[static_cast<int>(c_i) - 1];
      jnt = obj->JointInternal;
      for (j = 0; j < 16; j++) {
        TDHOffset[j] = jnt->ChildToJointTransform[j];
      }
      for (j = 0; j < 3; j++) {
        R[3 * j] = TDHOffset[j];
        R[3 * j + 1] = TDHOffset[j + 4];
        R[3 * j + 2] = TDHOffset[j + 8];
      }
      for (j = 0; j < 9; j++) {
        b_R[j] = -R[j];
      }
      for (j = 0; j < 3; j++) {
        a_idx_0 = b_R[j] * TDHOffset[12];
        loop_ub_tmp = j << 2;
        TDHOffset[loop_ub_tmp] = R[3 * j];
        a_idx_0 += b_R[j + 3] * TDHOffset[13];
        TDHOffset[loop_ub_tmp + 1] = R[3 * j + 1];
        a_idx_0 += b_R[j + 6] * TDHOffset[14];
        TDHOffset[loop_ub_tmp + 2] = R[3 * j + 2];
        c_R[j] = a_idx_0;
      }
      TDHOffset[12] = c_R[0];
      TDHOffset[13] = c_R[1];
      TDHOffset[14] = c_R[2];
      TDHOffset[3] = 0.0;
      TDHOffset[7] = 0.0;
      TDHOffset[11] = 0.0;
      TDHOffset[15] = 1.0;
      obj = robot.Bodies[static_cast<int>(c_i) - 1];
      jnt = obj->JointInternal;
      vJ.set_size(6, jnt->MotionSubspace.size(1));
      loop_ub_tmp = 6 * jnt->MotionSubspace.size(1);
      for (j = 0; j < loop_ub_tmp; j++) {
        vJ[j] = jnt->MotionSubspace[j];
      }
      R[0] = 0.0;
      R[3] = -c_R[2];
      R[6] = c_R[1];
      R[1] = c_R[2];
      R[4] = 0.0;
      R[7] = -c_R[0];
      R[2] = -c_R[1];
      R[5] = c_R[0];
      R[8] = 0.0;
      for (j = 0; j < 3; j++) {
        a_idx_0 = R[j];
        a_idx_1 = R[j + 3];
        b_idx_0 = R[j + 6];
        for (aoffset = 0; aoffset < 3; aoffset++) {
          i1 = aoffset << 2;
          b_R[j + 3 * aoffset] =
              (a_idx_0 * TDHOffset[i1] + a_idx_1 * TDHOffset[i1 + 1]) +
              b_idx_0 * TDHOffset[i1 + 2];
          XDHOffset[aoffset + 6 * j] = TDHOffset[aoffset + (j << 2)];
          XDHOffset[aoffset + 6 * (j + 3)] = 0.0;
        }
      }
      for (j = 0; j < 3; j++) {
        XDHOffset[6 * j + 3] = b_R[3 * j];
        loop_ub_tmp = j << 2;
        aoffset = 6 * (j + 3);
        XDHOffset[aoffset + 3] = TDHOffset[loop_ub_tmp];
        XDHOffset[6 * j + 4] = b_R[3 * j + 1];
        XDHOffset[aoffset + 4] = TDHOffset[loop_ub_tmp + 1];
        XDHOffset[6 * j + 5] = b_R[3 * j + 2];
        XDHOffset[aoffset + 5] = TDHOffset[loop_ub_tmp + 2];
      }
      loop_ub_tmp = vJ.size(1);
      S.set_size(6, vJ.size(1));
      for (j = 0; j < loop_ub_tmp; j++) {
        aoffset = j * 6;
        for (int d_i{0}; d_i < 6; d_i++) {
          a_idx_0 = 0.0;
          for (int k{0}; k < 6; k++) {
            a_idx_0 += XDHOffset[k * 6 + d_i] * vJ[aoffset + k];
          }
          S[aoffset + d_i] = a_idx_0;
        }
      }
      loop_ub_tmp = S.size(1);
      taui.set_size(S.size(1));
      for (int d_i{0}; d_i < loop_ub_tmp; d_i++) {
        aoffset = d_i * 6;
        a_idx_0 = 0.0;
        for (int k{0}; k < 6; k++) {
          a_idx_0 += S[aoffset + k] * f[k + 6 * (static_cast<int>(c_i) - 1)];
        }
        taui[d_i] = a_idx_0;
      }
      b_idx_0 = robot.VelocityDoFMap[static_cast<int>(c_i) - 1];
      b_idx_1 = robot.VelocityDoFMap[static_cast<int>(c_i) + 6];
      if (b_idx_0 > b_idx_1) {
        j = 0;
        aoffset = 0;
      } else {
        j = static_cast<int>(b_idx_0) - 1;
        aoffset = static_cast<int>(b_idx_1);
      }
      loop_ub_tmp = aoffset - j;
      for (aoffset = 0; aoffset < loop_ub_tmp; aoffset++) {
        tau_data[j + aoffset] = taui[aoffset];
      }
    }
    b_idx_1 = robot.Bodies[static_cast<int>(c_i) - 1]->ParentIndex;
    if (b_idx_1 > 0.0) {
      for (j = 0; j < 6; j++) {
        a_idx_0 = 0.0;
        for (aoffset = 0; aoffset < 6; aoffset++) {
          a_idx_0 += X[static_cast<int>(c_i) - 1].f1[aoffset + 6 * j] *
                     f[aoffset + 6 * (static_cast<int>(c_i) - 1)];
        }
        b_q_data[j] = f[j + 6 * (static_cast<int>(b_idx_1) - 1)] + a_idx_0;
      }
      for (j = 0; j < 6; j++) {
        f[j + 6 * (static_cast<int>(b_idx_1) - 1)] = b_q_data[j];
      }
    }
  }
  return tau_size;
}

//
// Arguments    : b_RigidBodyTree &robot
//                const double q_data[]
//                ::coder::array<double, 2U> &H
//                ::coder::array<double, 2U> &lambda
// Return Type  : void
//
void RigidBodyTreeDynamics::massMatrix(b_RigidBodyTree &robot,
                                       const double q_data[],
                                       ::coder::array<double, 2U> &H,
                                       ::coder::array<double, 2U> &lambda)
{
  static const char b_cv[5]{'f', 'i', 'x', 'e', 'd'};
  b_RigidBody *obj;
  rigidBodyJoint *jnt;
  array<cell_wrap_31, 2U> Ic;
  array<cell_wrap_31, 2U> X;
  array<double, 2U> Fi;
  array<double, 2U> Hji;
  array<double, 2U> Si;
  array<double, 2U> b;
  array<double, 2U> lambda_;
  array<double, 2U> r;
  array<char, 2U> a;
  array<signed char, 2U> r1;
  double b_X[36];
  double T[16];
  double R[9];
  double b_R[9];
  double c_R[3];
  double apnd;
  double b_idx_1;
  double cdiff;
  double nb;
  double p_idx_0;
  double p_idx_1;
  double vNum;
  int nonFixedIndices_data[7];
  int tmp_data[7];
  int i;
  int i1;
  int k;
  int loop_ub;
  int loop_ub_tmp;
  int nm1d2;
  boolean_T mask[7];
  nb = robot.NumBodies;
  loop_ub_tmp = static_cast<int>(nb);
  Ic.set_size(1, loop_ub_tmp);
  X.set_size(1, loop_ub_tmp);
  vNum = robot.VelocityNumber;
  nm1d2 = static_cast<int>(vNum);
  H.set_size(nm1d2, nm1d2);
  loop_ub = static_cast<int>(vNum) * static_cast<int>(vNum);
  for (i = 0; i < loop_ub; i++) {
    H[i] = 0.0;
  }
  lambda_.set_size(1, loop_ub_tmp);
  for (i = 0; i < loop_ub_tmp; i++) {
    lambda_[i] = 0.0;
  }
  lambda.set_size(1, nm1d2);
  for (i = 0; i < nm1d2; i++) {
    lambda[i] = 0.0;
  }
  for (int b_i{0}; b_i < loop_ub_tmp; b_i++) {
    for (i = 0; i < 36; i++) {
      Ic[b_i].f1[i] = robot.Bodies[b_i]->SpatialInertia[i];
    }
    p_idx_0 = robot.PositionDoFMap[b_i];
    p_idx_1 = robot.PositionDoFMap[b_i + 7];
    if (p_idx_1 < p_idx_0) {
      obj = robot.Bodies[b_i];
      jnt = obj->JointInternal;
      jnt->transformBodyToParent(T);
    } else {
      double b_q_data[6];
      if (p_idx_0 > p_idx_1) {
        i = 0;
        i1 = 0;
      } else {
        i = static_cast<int>(p_idx_0) - 1;
        i1 = static_cast<int>(p_idx_1);
      }
      obj = robot.Bodies[b_i];
      jnt = obj->JointInternal;
      loop_ub = i1 - i;
      for (i1 = 0; i1 < loop_ub; i1++) {
        b_q_data[i1] = q_data[i + i1];
      }
      jnt->transformBodyToParent(b_q_data, loop_ub, T);
    }
    for (i = 0; i < 3; i++) {
      R[3 * i] = T[i];
      R[3 * i + 1] = T[i + 4];
      R[3 * i + 2] = T[i + 8];
    }
    for (i = 0; i < 9; i++) {
      b_R[i] = -R[i];
    }
    for (i = 0; i < 3; i++) {
      vNum = b_R[i] * T[12];
      nm1d2 = i << 2;
      T[nm1d2] = R[3 * i];
      vNum += b_R[i + 3] * T[13];
      T[nm1d2 + 1] = R[3 * i + 1];
      vNum += b_R[i + 6] * T[14];
      T[nm1d2 + 2] = R[3 * i + 2];
      c_R[i] = vNum;
    }
    T[12] = c_R[0];
    T[13] = c_R[1];
    T[14] = c_R[2];
    T[3] = 0.0;
    T[7] = 0.0;
    T[11] = 0.0;
    T[15] = 1.0;
    R[0] = 0.0;
    R[3] = -c_R[2];
    R[6] = c_R[1];
    R[1] = c_R[2];
    R[4] = 0.0;
    R[7] = -c_R[0];
    R[2] = -c_R[1];
    R[5] = c_R[0];
    R[8] = 0.0;
    for (i = 0; i < 3; i++) {
      vNum = R[i];
      apnd = R[i + 3];
      cdiff = R[i + 6];
      for (i1 = 0; i1 < 3; i1++) {
        k = i1 << 2;
        b_R[i + 3 * i1] = (vNum * T[k] + apnd * T[k + 1]) + cdiff * T[k + 2];
        X[b_i].f1[i1 + 6 * i] = T[i1 + (i << 2)];
        X[b_i].f1[i1 + 6 * (i + 3)] = 0.0;
      }
    }
    for (i = 0; i < 3; i++) {
      X[b_i].f1[6 * i + 3] = b_R[3 * i];
      i1 = i << 2;
      k = 6 * (i + 3);
      X[b_i].f1[k + 3] = T[i1];
      X[b_i].f1[6 * i + 4] = b_R[3 * i + 1];
      X[b_i].f1[k + 4] = T[i1 + 1];
      X[b_i].f1[6 * i + 5] = b_R[3 * i + 2];
      X[b_i].f1[k + 5] = T[i1 + 2];
    }
  }
  i = static_cast<int>(-((-1.0 - nb) + 1.0));
  for (int b_i{0}; b_i < i; b_i++) {
    double b_idx_0;
    double c_i;
    double pid;
    c_i = nb - static_cast<double>(b_i);
    pid = robot.Bodies[static_cast<int>(c_i) - 1]->ParentIndex;
    p_idx_0 = robot.VelocityDoFMap[static_cast<int>(c_i) - 1];
    p_idx_1 = robot.VelocityDoFMap[static_cast<int>(c_i) + 6];
    if (pid > 0.0) {
      for (i1 = 0; i1 < 6; i1++) {
        for (k = 0; k < 6; k++) {
          vNum = 0.0;
          for (loop_ub_tmp = 0; loop_ub_tmp < 6; loop_ub_tmp++) {
            vNum += X[static_cast<int>(c_i) - 1].f1[loop_ub_tmp + 6 * i1] *
                    Ic[static_cast<int>(c_i) - 1].f1[loop_ub_tmp + 6 * k];
          }
          b_X[i1 + 6 * k] = vNum;
        }
      }
      for (i1 = 0; i1 < 6; i1++) {
        for (k = 0; k < 6; k++) {
          vNum = 0.0;
          for (loop_ub_tmp = 0; loop_ub_tmp < 6; loop_ub_tmp++) {
            vNum += b_X[i1 + 6 * loop_ub_tmp] *
                    X[static_cast<int>(c_i) - 1].f1[loop_ub_tmp + 6 * k];
          }
          loop_ub_tmp = i1 + 6 * k;
          Ic[static_cast<int>(pid) - 1].f1[loop_ub_tmp] =
              Ic[static_cast<int>(pid) - 1].f1[loop_ub_tmp] + vNum;
        }
      }
      lambda_[static_cast<int>(c_i) - 1] = pid;
      int exitg1;
      do {
        exitg1 = 0;
        vNum = lambda_[static_cast<int>(c_i) - 1];
        if (vNum > 0.0) {
          boolean_T b_bool;
          obj = robot.Bodies[static_cast<int>(vNum) - 1];
          jnt = obj->JointInternal;
          a.set_size(1, jnt->Type.size(1));
          loop_ub = jnt->Type.size(1);
          for (i1 = 0; i1 < loop_ub; i1++) {
            a[i1] = jnt->Type[i1];
          }
          b_bool = false;
          if (a.size(1) == 5) {
            nm1d2 = 0;
            int exitg2;
            do {
              exitg2 = 0;
              if (nm1d2 < 5) {
                if (a[nm1d2] != b_cv[nm1d2]) {
                  exitg2 = 1;
                } else {
                  nm1d2++;
                }
              } else {
                b_bool = true;
                exitg2 = 1;
              }
            } while (exitg2 == 0);
          }
          if (b_bool) {
            lambda_[static_cast<int>(c_i) - 1] =
                robot
                    .Bodies[static_cast<int>(
                                lambda_[static_cast<int>(c_i) - 1]) -
                            1]
                    ->ParentIndex;
          } else {
            exitg1 = 1;
          }
        } else {
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }
    b_idx_0 = robot.VelocityDoFMap[static_cast<int>(c_i) - 1];
    b_idx_1 = robot.VelocityDoFMap[static_cast<int>(c_i) + 6];
    if (b_idx_0 <= b_idx_1) {
      obj = robot.Bodies[static_cast<int>(c_i) - 1];
      jnt = obj->JointInternal;
      for (i1 = 0; i1 < 16; i1++) {
        T[i1] = jnt->ChildToJointTransform[i1];
      }
      for (i1 = 0; i1 < 3; i1++) {
        R[3 * i1] = T[i1];
        R[3 * i1 + 1] = T[i1 + 4];
        R[3 * i1 + 2] = T[i1 + 8];
      }
      for (i1 = 0; i1 < 9; i1++) {
        b_R[i1] = -R[i1];
      }
      for (i1 = 0; i1 < 3; i1++) {
        vNum = b_R[i1] * T[12];
        nm1d2 = i1 << 2;
        T[nm1d2] = R[3 * i1];
        vNum += b_R[i1 + 3] * T[13];
        T[nm1d2 + 1] = R[3 * i1 + 1];
        vNum += b_R[i1 + 6] * T[14];
        T[nm1d2 + 2] = R[3 * i1 + 2];
        c_R[i1] = vNum;
      }
      T[12] = c_R[0];
      T[13] = c_R[1];
      T[14] = c_R[2];
      T[3] = 0.0;
      T[7] = 0.0;
      T[11] = 0.0;
      T[15] = 1.0;
      obj = robot.Bodies[static_cast<int>(c_i) - 1];
      jnt = obj->JointInternal;
      b.set_size(6, jnt->MotionSubspace.size(1));
      loop_ub = 6 * jnt->MotionSubspace.size(1);
      for (i1 = 0; i1 < loop_ub; i1++) {
        b[i1] = jnt->MotionSubspace[i1];
      }
      R[0] = 0.0;
      R[3] = -c_R[2];
      R[6] = c_R[1];
      R[1] = c_R[2];
      R[4] = 0.0;
      R[7] = -c_R[0];
      R[2] = -c_R[1];
      R[5] = c_R[0];
      R[8] = 0.0;
      for (i1 = 0; i1 < 3; i1++) {
        vNum = R[i1];
        apnd = R[i1 + 3];
        cdiff = R[i1 + 6];
        for (k = 0; k < 3; k++) {
          loop_ub_tmp = k << 2;
          b_R[i1 + 3 * k] =
              (vNum * T[loop_ub_tmp] + apnd * T[loop_ub_tmp + 1]) +
              cdiff * T[loop_ub_tmp + 2];
          b_X[k + 6 * i1] = T[k + (i1 << 2)];
          b_X[k + 6 * (i1 + 3)] = 0.0;
        }
      }
      for (i1 = 0; i1 < 3; i1++) {
        b_X[6 * i1 + 3] = b_R[3 * i1];
        nm1d2 = i1 << 2;
        loop_ub_tmp = 6 * (i1 + 3);
        b_X[loop_ub_tmp + 3] = T[nm1d2];
        b_X[6 * i1 + 4] = b_R[3 * i1 + 1];
        b_X[loop_ub_tmp + 4] = T[nm1d2 + 1];
        b_X[6 * i1 + 5] = b_R[3 * i1 + 2];
        b_X[loop_ub_tmp + 5] = T[nm1d2 + 2];
      }
      loop_ub = b.size(1);
      Si.set_size(6, b.size(1));
      for (nm1d2 = 0; nm1d2 < loop_ub; nm1d2++) {
        loop_ub_tmp = nm1d2 * 6;
        for (int d_i{0}; d_i < 6; d_i++) {
          vNum = 0.0;
          for (k = 0; k < 6; k++) {
            vNum += b_X[k * 6 + d_i] * b[loop_ub_tmp + k];
          }
          Si[loop_ub_tmp + d_i] = vNum;
        }
      }
      loop_ub = Si.size(1);
      Fi.set_size(6, Si.size(1));
      for (nm1d2 = 0; nm1d2 < loop_ub; nm1d2++) {
        loop_ub_tmp = nm1d2 * 6;
        for (int d_i{0}; d_i < 6; d_i++) {
          vNum = 0.0;
          for (k = 0; k < 6; k++) {
            vNum += Ic[static_cast<int>(c_i) - 1].f1[k * 6 + d_i] *
                    Si[loop_ub_tmp + k];
          }
          Fi[loop_ub_tmp + d_i] = vNum;
        }
      }
      if (p_idx_0 > p_idx_1) {
        i1 = 1;
        k = 1;
      } else {
        i1 = static_cast<int>(p_idx_0);
        k = static_cast<int>(p_idx_0);
      }
      ::coder::internal::blas::mtimes(Si, Fi, Hji);
      loop_ub = Hji.size(1);
      for (loop_ub_tmp = 0; loop_ub_tmp < loop_ub; loop_ub_tmp++) {
        nm1d2 = Hji.size(0);
        for (int d_i{0}; d_i < nm1d2; d_i++) {
          H[((i1 + d_i) + H.size(0) * ((k + loop_ub_tmp) - 1)) - 1] =
              Hji[d_i + Hji.size(0) * loop_ub_tmp];
        }
      }
      b.set_size(6, Fi.size(1));
      loop_ub = Fi.size(0) * Fi.size(1) - 1;
      for (i1 = 0; i1 <= loop_ub; i1++) {
        b[i1] = Fi[i1];
      }
      ::std::copy(&X[static_cast<int>(c_i) - 1].f1[0],
                  &X[static_cast<int>(c_i) - 1].f1[36], &b_X[0]);
      ::coder::internal::blas::mtimes(b_X, b, Fi);
      while (pid > 0.0) {
        obj = robot.Bodies[static_cast<int>(pid) - 1];
        jnt = obj->JointInternal;
        for (i1 = 0; i1 < 16; i1++) {
          T[i1] = jnt->ChildToJointTransform[i1];
        }
        for (i1 = 0; i1 < 3; i1++) {
          R[3 * i1] = T[i1];
          R[3 * i1 + 1] = T[i1 + 4];
          R[3 * i1 + 2] = T[i1 + 8];
        }
        for (i1 = 0; i1 < 9; i1++) {
          b_R[i1] = -R[i1];
        }
        for (i1 = 0; i1 < 3; i1++) {
          vNum = b_R[i1] * T[12];
          nm1d2 = i1 << 2;
          T[nm1d2] = R[3 * i1];
          vNum += b_R[i1 + 3] * T[13];
          T[nm1d2 + 1] = R[3 * i1 + 1];
          vNum += b_R[i1 + 6] * T[14];
          T[nm1d2 + 2] = R[3 * i1 + 2];
          c_R[i1] = vNum;
        }
        T[12] = c_R[0];
        T[13] = c_R[1];
        T[14] = c_R[2];
        T[3] = 0.0;
        T[7] = 0.0;
        T[11] = 0.0;
        T[15] = 1.0;
        obj = robot.Bodies[static_cast<int>(pid) - 1];
        jnt = obj->JointInternal;
        b.set_size(6, jnt->MotionSubspace.size(1));
        loop_ub = 6 * jnt->MotionSubspace.size(1);
        for (i1 = 0; i1 < loop_ub; i1++) {
          b[i1] = jnt->MotionSubspace[i1];
        }
        b_idx_0 = robot.VelocityDoFMap[static_cast<int>(pid) - 1];
        b_idx_1 = robot.VelocityDoFMap[static_cast<int>(pid) + 6];
        if (b_idx_0 <= b_idx_1) {
          R[0] = 0.0;
          R[3] = -c_R[2];
          R[6] = c_R[1];
          R[1] = c_R[2];
          R[4] = 0.0;
          R[7] = -c_R[0];
          R[2] = -c_R[1];
          R[5] = c_R[0];
          R[8] = 0.0;
          for (i1 = 0; i1 < 3; i1++) {
            vNum = R[i1];
            apnd = R[i1 + 3];
            cdiff = R[i1 + 6];
            for (k = 0; k < 3; k++) {
              loop_ub_tmp = k << 2;
              b_R[i1 + 3 * k] =
                  (vNum * T[loop_ub_tmp] + apnd * T[loop_ub_tmp + 1]) +
                  cdiff * T[loop_ub_tmp + 2];
              b_X[k + 6 * i1] = T[k + (i1 << 2)];
              b_X[k + 6 * (i1 + 3)] = 0.0;
            }
          }
          for (i1 = 0; i1 < 3; i1++) {
            b_X[6 * i1 + 3] = b_R[3 * i1];
            nm1d2 = i1 << 2;
            loop_ub_tmp = 6 * (i1 + 3);
            b_X[loop_ub_tmp + 3] = T[nm1d2];
            b_X[6 * i1 + 4] = b_R[3 * i1 + 1];
            b_X[loop_ub_tmp + 4] = T[nm1d2 + 1];
            b_X[6 * i1 + 5] = b_R[3 * i1 + 2];
            b_X[loop_ub_tmp + 5] = T[nm1d2 + 2];
          }
          loop_ub = b.size(1);
          Si.set_size(6, b.size(1));
          for (nm1d2 = 0; nm1d2 < loop_ub; nm1d2++) {
            loop_ub_tmp = nm1d2 * 6;
            for (int d_i{0}; d_i < 6; d_i++) {
              vNum = 0.0;
              for (k = 0; k < 6; k++) {
                vNum += b_X[k * 6 + d_i] * b[loop_ub_tmp + k];
              }
              Si[loop_ub_tmp + d_i] = vNum;
            }
          }
          ::coder::internal::blas::mtimes(Si, Fi, Hji);
          if (b_idx_0 > b_idx_1) {
            i1 = 1;
          } else {
            i1 = static_cast<int>(b_idx_0);
          }
          if (p_idx_0 > p_idx_1) {
            k = 1;
          } else {
            k = static_cast<int>(p_idx_0);
          }
          loop_ub = Hji.size(1);
          for (loop_ub_tmp = 0; loop_ub_tmp < loop_ub; loop_ub_tmp++) {
            nm1d2 = Hji.size(0);
            for (int d_i{0}; d_i < nm1d2; d_i++) {
              H[((i1 + d_i) + H.size(0) * ((k + loop_ub_tmp) - 1)) - 1] =
                  Hji[d_i + Hji.size(0) * loop_ub_tmp];
            }
          }
          if (p_idx_0 > p_idx_1) {
            i1 = 1;
          } else {
            i1 = static_cast<int>(p_idx_0);
          }
          if (b_idx_0 > b_idx_1) {
            k = 1;
          } else {
            k = static_cast<int>(b_idx_0);
          }
          loop_ub = Hji.size(0);
          for (loop_ub_tmp = 0; loop_ub_tmp < loop_ub; loop_ub_tmp++) {
            nm1d2 = Hji.size(1);
            for (int d_i{0}; d_i < nm1d2; d_i++) {
              H[((i1 + d_i) + H.size(0) * ((k + loop_ub_tmp) - 1)) - 1] =
                  Hji[loop_ub_tmp + Hji.size(0) * d_i];
            }
          }
        }
        b.set_size(6, Fi.size(1));
        loop_ub = Fi.size(0) * Fi.size(1) - 1;
        for (i1 = 0; i1 <= loop_ub; i1++) {
          b[i1] = Fi[i1];
        }
        ::std::copy(&X[static_cast<int>(pid) - 1].f1[0],
                    &X[static_cast<int>(pid) - 1].f1[36], &b_X[0]);
        ::coder::internal::blas::mtimes(b_X, b, Fi);
        pid = robot.Bodies[static_cast<int>(pid) - 1]->ParentIndex;
      }
    }
  }
  for (i = 0; i < 7; i++) {
    mask[i] = (robot.VelocityDoFMap[i] <= robot.VelocityDoFMap[i + 7]);
  }
  loop_ub_tmp = eml_find(mask, tmp_data);
  if (loop_ub_tmp - 1 >= 0) {
    ::std::copy(&tmp_data[0], &tmp_data[loop_ub_tmp], &nonFixedIndices_data[0]);
  }
  for (k = 0; k < loop_ub_tmp; k++) {
    nm1d2 = nonFixedIndices_data[k];
    p_idx_0 = robot.VelocityDoFMap[nm1d2 - 1];
    p_idx_1 = robot.VelocityDoFMap[nm1d2 + 6];
    if (std::isnan(p_idx_0) || std::isnan(p_idx_1)) {
      r.set_size(1, 1);
      r[0] = rtNaN;
    } else if (p_idx_1 < p_idx_0) {
      r.set_size(1, 0);
    } else if ((std::isinf(p_idx_0) || std::isinf(p_idx_1)) &&
               (p_idx_0 == p_idx_1)) {
      r.set_size(1, 1);
      r[0] = rtNaN;
    } else if (std::floor(p_idx_0) == p_idx_0) {
      loop_ub = static_cast<int>(p_idx_1 - p_idx_0);
      r.set_size(1, loop_ub + 1);
      for (i = 0; i <= loop_ub; i++) {
        r[i] = p_idx_0 + static_cast<double>(i);
      }
    } else {
      vNum = std::floor((p_idx_1 - p_idx_0) + 0.5);
      apnd = p_idx_0 + vNum;
      cdiff = apnd - p_idx_1;
      if (std::abs(cdiff) <
          4.4408920985006262E-16 *
              std::fmax(std::abs(p_idx_0), std::abs(p_idx_1))) {
        vNum++;
        apnd = p_idx_1;
      } else if (cdiff > 0.0) {
        apnd = p_idx_0 + (vNum - 1.0);
      } else {
        vNum++;
      }
      if (vNum >= 0.0) {
        loop_ub = static_cast<int>(vNum);
      } else {
        loop_ub = 0;
      }
      r.set_size(1, loop_ub);
      if (loop_ub > 0) {
        r[0] = p_idx_0;
        if (loop_ub > 1) {
          r[loop_ub - 1] = apnd;
          nm1d2 = (loop_ub - 1) / 2;
          for (int d_i{0}; d_i <= nm1d2 - 2; d_i++) {
            r[d_i + 1] = p_idx_0 + (static_cast<double>(d_i) + 1.0);
            r[(loop_ub - d_i) - 2] = apnd - (static_cast<double>(d_i) + 1.0);
          }
          if (nm1d2 << 1 == loop_ub - 1) {
            r[nm1d2] = (p_idx_0 + apnd) / 2.0;
          } else {
            r[nm1d2] = p_idx_0 + static_cast<double>(nm1d2);
            r[nm1d2 + 1] = apnd - static_cast<double>(nm1d2);
          }
        }
      }
    }
    loop_ub = static_cast<int>((p_idx_1 - p_idx_0) + 1.0);
    r1.set_size(1, loop_ub);
    for (i = 0; i < loop_ub; i++) {
      r1[i] = 1;
    }
    if (p_idx_0 > p_idx_1) {
      i = 0;
    } else {
      i = static_cast<int>(p_idx_0) - 1;
    }
    if (r.size(1) == r1.size(1)) {
      loop_ub = r.size(1);
      for (i1 = 0; i1 < loop_ub; i1++) {
        lambda[i + i1] = r[i1] - 1.0;
      }
    } else {
      binary_expand_op(lambda, i, r, r1);
    }
    vNum = lambda_[nonFixedIndices_data[k] - 1];
    if (vNum == 0.0) {
      lambda[static_cast<int>(p_idx_0) - 1] = 0.0;
    } else {
      b_idx_1 = robot.VelocityDoFMap[static_cast<int>(vNum) + 6];
      lambda[static_cast<int>(p_idx_0) - 1] = b_idx_1;
    }
  }
}

} // namespace internal
} // namespace manip
} // namespace robotics
} // namespace coder

//
// File trailer for RigidBodyTreeDynamics.cpp
//
// [EOF]
//
