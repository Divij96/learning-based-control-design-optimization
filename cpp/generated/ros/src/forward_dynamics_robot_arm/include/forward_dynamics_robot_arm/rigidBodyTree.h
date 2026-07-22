//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: rigidBodyTree.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 02-Feb-2024 13:34:01
//

#ifndef RIGIDBODYTREE_H
#define RIGIDBODYTREE_H

// Include Files
#include "CollisionSet.h"
#include "RigidBodyTree1.h"
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
namespace coder {
class rigidBody;

class rigidBodyJoint;

namespace robotics {
namespace manip {
namespace internal {
class b_RigidBody;

}
} // namespace manip
} // namespace robotics
} // namespace coder

// Type Definitions
namespace coder {
class rigidBodyTree {
public:
  rigidBodyTree *init();
  void addBody(rigidBody *bodyin,
               robotics::manip::internal::CollisionSet &iobj_0,
               rigidBodyJoint &iobj_1,
               robotics::manip::internal::b_RigidBody &iobj_2);
  void addBody(rigidBody *bodyin, const char parentName[6],
               robotics::manip::internal::CollisionSet &iobj_0,
               rigidBodyJoint &iobj_1,
               robotics::manip::internal::b_RigidBody &iobj_2);
  int forwardDynamics(const double varargin_1[10], const double varargin_2[10],
                      const double varargin_3[10], double qddot_data[]);
  void matlabCodegenDestructor();
  ~rigidBodyTree();
  rigidBodyTree();
  boolean_T matlabCodegenIsDeleted;
  robotics::manip::internal::b_RigidBodyTree TreeInternal;
  robotics::manip::internal::CollisionSet _pobj0;
};

} // namespace coder

#endif
//
// File trailer for rigidBodyTree.h
//
// [EOF]
//
