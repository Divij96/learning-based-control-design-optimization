//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: rigidBody1.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 05-Feb-2024 13:57:11
//

#ifndef RIGIDBODY1_H
#define RIGIDBODY1_H

// Include Files
#include "CollisionSet.h"
#include "RigidBody.h"
#include "RigidBodyTree1.h"
#include "rigidBodyJoint.h"
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder {
class rigidBody {
public:
  void set_Inertia(const double b_value[6]);
  void matlabCodegenDestructor();
  ~rigidBody();
  rigidBody();
  boolean_T matlabCodegenIsDeleted;
  robotics::manip::internal::RigidBody *BodyInternal;
  robotics::manip::internal::b_RigidBodyTree *TreeInternal;
  robotics::manip::internal::b_RigidBodyTree _pobj0;
  robotics::manip::internal::CollisionSet _pobj1[2];
  rigidBodyJoint _pobj2;
  robotics::manip::internal::RigidBody _pobj3;
};

} // namespace coder

#endif
//
// File trailer for rigidBody1.h
//
// [EOF]
//
