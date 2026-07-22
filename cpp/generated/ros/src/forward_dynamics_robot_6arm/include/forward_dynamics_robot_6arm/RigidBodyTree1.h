//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: RigidBodyTree1.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 14-Feb-2024 19:42:36
//

#ifndef RIGIDBODYTREE1_H
#define RIGIDBODYTREE1_H

// Include Files
#include "CollisionSet.h"
#include "FastVisualizationHelper.h"
#include "RigidBody.h"
#include "rigidBodyJoint.h"
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
struct cell_wrap_33;

// Type Definitions
namespace coder {
namespace robotics {
namespace manip {
namespace internal {
class RigidBodyTree {
public:
  RigidBodyTree *init();
  void matlabCodegenDestructor();
  ~RigidBodyTree();
  RigidBodyTree();
  boolean_T matlabCodegenIsDeleted;
  RigidBody Base;
  FastVisualizationHelper b_FastVisualizationHelper;
  RigidBody *Bodies[1];
  RigidBody _pobj0;
  CollisionSet _pobj1[2];
  rigidBodyJoint _pobj2[2];
};

class b_RigidBodyTree {
public:
  double findBodyIndexByName(const ::coder::array<char, 2U> &bodyname);
  double validateInputBodyName(const char bodyname[6]);
  void forwardKinematics(const double qvec[6],
                         ::coder::array<cell_wrap_33, 2U> &Ttree);
  void matlabCodegenDestructor();
  ~b_RigidBodyTree();
  b_RigidBodyTree();
  boolean_T matlabCodegenIsDeleted;
  double NumBodies;
  b_RigidBody Base;
  FastVisualizationHelper b_FastVisualizationHelper;
  double Gravity[3];
  b_RigidBody *Bodies[7];
  double NumNonFixedBodies;
  double PositionNumber;
  double VelocityNumber;
  double PositionDoFMap[14];
  double VelocityDoFMap[14];
  CollisionSet _pobj0[6];
  rigidBodyJoint _pobj1[6];
  b_RigidBody _pobj2[7];
};

} // namespace internal
} // namespace manip
} // namespace robotics
} // namespace coder

#endif
//
// File trailer for RigidBodyTree1.h
//
// [EOF]
//
