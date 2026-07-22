//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: rigidBody1.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 14-Feb-2024 19:42:36
//

#ifndef RIGIDBODY1_H
#define RIGIDBODY1_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
namespace coder {
namespace robotics {
namespace manip {
namespace internal {
class RigidBody;

class RigidBodyTree;

class CollisionSet;

} // namespace internal
} // namespace manip
} // namespace robotics
class rigidBodyJoint;

} // namespace coder

// Type Definitions
namespace coder {
class rigidBody {
public:
  void set_Inertia(const double b_value[6]);
  rigidBody *init(robotics::manip::internal::RigidBodyTree &iobj_0,
                  robotics::manip::internal::CollisionSet &iobj_1,
                  rigidBodyJoint &iobj_2,
                  robotics::manip::internal::RigidBody &iobj_3);
  void matlabCodegenDestructor();
  ~rigidBody();
  rigidBody();
  boolean_T matlabCodegenIsDeleted;
  robotics::manip::internal::RigidBody *BodyInternal;
  robotics::manip::internal::RigidBodyTree *TreeInternal;
};

} // namespace coder

#endif
//
// File trailer for rigidBody1.h
//
// [EOF]
//
