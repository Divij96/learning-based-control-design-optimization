//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: rigidBodyJoint.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 02-Feb-2024 13:34:01
//

#ifndef RIGIDBODYJOINT_H
#define RIGIDBODYJOINT_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder {
class rigidBodyJoint {
public:
  rigidBodyJoint *init();
  rigidBodyJoint *b_init();
  rigidBodyJoint *c_init();
  rigidBodyJoint *copy(rigidBodyJoint &iobj_0) const;
  rigidBodyJoint *d_init();
  rigidBodyJoint *e_init();
  rigidBodyJoint *f_init();
  rigidBodyJoint *g_init();
  rigidBodyJoint *h_init();
  rigidBodyJoint *i_init();
  rigidBodyJoint *j_init();
  rigidBodyJoint *k_init();
  rigidBodyJoint *l_init();
  void get_JointAxis(double ax[3]) const;
  void transformBodyToParent(const double q_data[], int q_size,
                             double T[16]) const;
  void transformBodyToParent(double T[16]) const;
  array<char, 2U> Type;
  double VelocityNumber;
  double PositionNumber;
  array<double, 2U> MotionSubspace;
  boolean_T InTree;
  double JointToParentTransform[16];
  double ChildToJointTransform[16];
  array<char, 2U> NameInternal;
  array<double, 2U> PositionLimitsInternal;
  array<double, 1U> HomePositionInternal;
  double JointAxisInternal[3];
};

} // namespace coder

#endif
//
// File trailer for rigidBodyJoint.h
//
// [EOF]
//
