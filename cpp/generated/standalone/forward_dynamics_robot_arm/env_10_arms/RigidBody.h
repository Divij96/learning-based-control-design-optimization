//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: RigidBody.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 02-Feb-2024 13:34:01
//

#ifndef RIGIDBODY_H
#define RIGIDBODY_H

// Include Files
#include "CollisionSet.h"
#include "rigidBodyJoint.h"
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
namespace coder {
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
namespace robotics {
namespace manip {
namespace internal {
class RigidBody {
public:
  b_RigidBody *copy(CollisionSet &iobj_0, rigidBodyJoint &iobj_1,
                    b_RigidBody &iobj_2);
  void matlabCodegenDestructor();
  ~RigidBody();
  RigidBody();
  boolean_T matlabCodegenIsDeleted;
  double Index;
  array<char, 2U> NameInternal;
  rigidBodyJoint *JointInternal;
  double MassInternal;
  double CenterOfMassInternal[3];
  double InertiaInternal[9];
  double SpatialInertia[36];
  CollisionSet *CollisionsInternal;
};

class b_RigidBody {
public:
  b_RigidBody *init(CollisionSet &iobj_0, rigidBodyJoint &iobj_1);
  b_RigidBody *b_init(CollisionSet &iobj_0, rigidBodyJoint &iobj_1);
  b_RigidBody *c_init(CollisionSet &iobj_0, rigidBodyJoint &iobj_1);
  b_RigidBody *d_init(CollisionSet &iobj_0, rigidBodyJoint &iobj_1);
  b_RigidBody *e_init(CollisionSet &iobj_0, rigidBodyJoint &iobj_1);
  b_RigidBody *f_init(CollisionSet &iobj_0, rigidBodyJoint &iobj_1);
  b_RigidBody *g_init(CollisionSet &iobj_0, rigidBodyJoint &iobj_1);
  b_RigidBody *h_init(CollisionSet &iobj_0, rigidBodyJoint &iobj_1);
  void matlabCodegenDestructor();
  ~b_RigidBody();
  b_RigidBody();
  boolean_T matlabCodegenIsDeleted;
  double Index;
  array<char, 2U> NameInternal;
  rigidBodyJoint *JointInternal;
  double ParentIndex;
  double SpatialInertia[36];
  CollisionSet *CollisionsInternal;
  CollisionSet _pobj0;
  rigidBodyJoint _pobj1;
};

} // namespace internal
} // namespace manip
} // namespace robotics
} // namespace coder

#endif
//
// File trailer for RigidBody.h
//
// [EOF]
//
