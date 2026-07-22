//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: forward_dynamics_robot_6arm.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 14-Feb-2024 19:42:36
//

// Include Files
#include "forward_dynamics_robot_6arm.h"
#include "CollisionGeometry.h"
#include "CollisionSet.h"
#include "RigidBody.h"
#include "RigidBodyTree1.h"
#include "axang2tform.h"
#include "cat.h"
#include "collisionCylinder.h"
#include "forward_dynamics_robot_6arm_data.h"
#include "forward_dynamics_robot_6arm_initialize.h"
#include "forward_dynamics_robot_6arm_internal_types.h"
#include "rigidBody1.h"
#include "rigidBodyJoint.h"
#include "rigidBodyTree.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "collisioncodegen_api.hpp"
#include <algorithm>
#include <cmath>
#include <cstring>

// Function Declarations
static coder::rigidBody *
createBody(const char bodyName[6], coder::rigidBodyJoint &joint,
           const double joint_axes[3], double radius, double length, double rho,
           coder::robotics::manip::internal::RigidBodyTree &iobj_0,
           coder::robotics::manip::internal::CollisionSet &iobj_1,
           coder::rigidBodyJoint &iobj_2,
           coder::robotics::manip::internal::RigidBody &iobj_3,
           coder::rigidBody &iobj_4);

// Function Definitions
//
// Create a rigid body with the specified parameters
//
// Arguments    : const char bodyName[6]
//                coder::rigidBodyJoint &joint
//                const double joint_axes[3]
//                double radius
//                double length
//                double rho
//                coder::robotics::manip::internal::RigidBodyTree &iobj_0
//                coder::robotics::manip::internal::CollisionSet &iobj_1
//                coder::rigidBodyJoint &iobj_2
//                coder::robotics::manip::internal::RigidBody &iobj_3
//                coder::rigidBody &iobj_4
// Return Type  : coder::rigidBody *
//
static coder::rigidBody *
createBody(const char bodyName[6], coder::rigidBodyJoint &joint,
           const double joint_axes[3], double radius, double length, double rho,
           coder::robotics::manip::internal::RigidBodyTree &iobj_0,
           coder::robotics::manip::internal::CollisionSet &iobj_1,
           coder::rigidBodyJoint &iobj_2,
           coder::robotics::manip::internal::RigidBody &iobj_3,
           coder::rigidBody &iobj_4)
{
  static const double dv[9]{
      6.123233995736766E-17, 0.0, -1.0, 0.0, 1.0, 0.0, 1.0, 0.0,
      6.123233995736766E-17};
  static const char b_cv1[8]{'r', 'e', 'v', 'o', 'l', 'u', 't', 'e'};
  static const signed char b_iv[6]{0, 0, 1, 0, 0, 0};
  static const signed char b_iv1[6]{0, 0, 0, 0, 0, 1};
  static const char b_cv[5]{'f', 'i', 'x', 'e', 'd'};
  coder::collisionCylinder collisionObj;
  coder::collisionCylinder lobj_0;
  coder::rigidBody *body;
  coder::rigidBodyJoint *b_obj;
  coder::robotics::manip::internal::CollisionGeometry collisionGeometry;
  coder::robotics::manip::internal::CollisionSet *c_obj;
  coder::robotics::manip::internal::RigidBody *obj;
  coder::robotics::manip::internal::RigidBodyTree *b_default;
  coder::array<char, 2U> switch_expression;
  double b_y[16];
  double poslim_data[12];
  double b_I[9];
  double sc[9];
  double ax[6];
  double absxk;
  double ax_idx_0;
  double ax_idx_1;
  double ax_idx_2;
  double m;
  double scale;
  double t;
  double y;
  int exitg1;
  int i;
  int i1;
  int loop_ub;
  signed char msubspace_data[36];
  boolean_T b_bool;
  body = &iobj_4;
  iobj_3.NameInternal.set_size(1, 6);
  for (i = 0; i < 6; i++) {
    iobj_3.NameInternal[i] = bodyName[i];
  }
  (&iobj_2)[0].InTree = false;
  for (i = 0; i < 16; i++) {
    (&iobj_2)[0].JointToParentTransform[i] = iv[i];
  }
  for (i = 0; i < 16; i++) {
    (&iobj_2)[0].ChildToJointTransform[i] = iv[i];
  }
  (&iobj_2)[0].NameInternal.set_size(1, 10);
  for (i = 0; i < 6; i++) {
    (&iobj_2)[0].NameInternal[i] = bodyName[i];
  }
  (&iobj_2)[0].NameInternal[6] = '_';
  (&iobj_2)[0].NameInternal[7] = 'j';
  (&iobj_2)[0].NameInternal[8] = 'n';
  (&iobj_2)[0].NameInternal[9] = 't';
  (&iobj_2)[0].Type.set_size(1, 5);
  for (i = 0; i < 5; i++) {
    (&iobj_2)[0].Type[i] = b_cv[i];
  }
  switch_expression.set_size(1, (&iobj_2)[0].Type.size(1));
  loop_ub = (&iobj_2)[0].Type.size(1);
  for (i = 0; i < loop_ub; i++) {
    switch_expression[i] = (&iobj_2)[0].Type[i];
  }
  b_bool = false;
  if (switch_expression.size(1) == 8) {
    loop_ub = 0;
    do {
      exitg1 = 0;
      if (loop_ub < 8) {
        if (switch_expression[loop_ub] != b_cv1[loop_ub]) {
          exitg1 = 1;
        } else {
          loop_ub++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  if (b_bool) {
    loop_ub = 0;
  } else {
    b_bool = false;
    if (switch_expression.size(1) == 9) {
      loop_ub = 0;
      do {
        exitg1 = 0;
        if (loop_ub < 9) {
          if (switch_expression[loop_ub] != cv1[loop_ub]) {
            exitg1 = 1;
          } else {
            loop_ub++;
          }
        } else {
          b_bool = true;
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }
    if (b_bool) {
      loop_ub = 1;
    } else {
      loop_ub = -1;
    }
  }
  switch (loop_ub) {
  case 0:
    for (i = 0; i < 6; i++) {
      msubspace_data[i] = b_iv[i];
    }
    poslim_data[0] = -3.1415926535897931;
    poslim_data[1] = 3.1415926535897931;
    (&iobj_2)[0].VelocityNumber = 1.0;
    (&iobj_2)[0].PositionNumber = 1.0;
    (&iobj_2)[0].JointAxisInternal[0] = 0.0;
    (&iobj_2)[0].JointAxisInternal[1] = 0.0;
    (&iobj_2)[0].JointAxisInternal[2] = 1.0;
    break;
  case 1:
    for (i = 0; i < 6; i++) {
      msubspace_data[i] = b_iv1[i];
    }
    poslim_data[0] = -0.5;
    poslim_data[1] = 0.5;
    (&iobj_2)[0].VelocityNumber = 1.0;
    (&iobj_2)[0].PositionNumber = 1.0;
    (&iobj_2)[0].JointAxisInternal[0] = 0.0;
    (&iobj_2)[0].JointAxisInternal[1] = 0.0;
    (&iobj_2)[0].JointAxisInternal[2] = 1.0;
    break;
  default:
    for (i = 0; i < 6; i++) {
      msubspace_data[i] = 0;
    }
    poslim_data[0] = 0.0;
    poslim_data[1] = 0.0;
    (&iobj_2)[0].VelocityNumber = 0.0;
    (&iobj_2)[0].PositionNumber = 0.0;
    (&iobj_2)[0].JointAxisInternal[0] = 0.0;
    (&iobj_2)[0].JointAxisInternal[1] = 0.0;
    (&iobj_2)[0].JointAxisInternal[2] = 0.0;
    break;
  }
  (&iobj_2)[0].MotionSubspace.set_size(6, 1);
  for (i = 0; i < 6; i++) {
    (&iobj_2)[0].MotionSubspace[i] = msubspace_data[i];
  }
  (&iobj_2)[0].PositionLimitsInternal.set_size(1, 2);
  for (i = 0; i < 2; i++) {
    (&iobj_2)[0].PositionLimitsInternal[i] = poslim_data[i];
  }
  (&iobj_2)[0].HomePositionInternal.set_size(1);
  (&iobj_2)[0].HomePositionInternal[0] = 0.0;
  iobj_3.JointInternal = &(&iobj_2)[0];
  iobj_3.Index = -1.0;
  iobj_3.MassInternal = 1.0;
  iobj_3.CenterOfMassInternal[0] = 0.0;
  iobj_3.CenterOfMassInternal[1] = 0.0;
  iobj_3.CenterOfMassInternal[2] = 0.0;
  std::memset(&b_I[0], 0, 9U * sizeof(double));
  b_I[0] = 1.0;
  b_I[4] = 1.0;
  b_I[8] = 1.0;
  for (i = 0; i < 9; i++) {
    iobj_3.InertiaInternal[i] = b_I[i];
  }
  for (i = 0; i < 36; i++) {
    msubspace_data[i] = 0;
  }
  for (loop_ub = 0; loop_ub < 6; loop_ub++) {
    msubspace_data[loop_ub + 6 * loop_ub] = 1;
  }
  for (i = 0; i < 36; i++) {
    iobj_3.SpatialInertia[i] = msubspace_data[i];
  }
  iobj_3.CollisionsInternal = (&(&iobj_1)[0])[0].init(0.0);
  iobj_3.matlabCodegenIsDeleted = false;
  b_default = iobj_0.init();
  iobj_3.CollisionsInternal = (&(&iobj_1)[0])[1].init(10.0);
  iobj_4.BodyInternal = &iobj_3;
  iobj_4.TreeInternal = b_default;
  iobj_4.matlabCodegenIsDeleted = false;
  obj = iobj_4.BodyInternal;
  obj->JointInternal = joint.copy(&(&iobj_2)[1]);
  obj = iobj_4.BodyInternal;
  b_obj = obj->JointInternal;
  scale = 3.3121686421112381E-170;
  absxk = std::abs(joint_axes[0]);
  if (absxk > 3.3121686421112381E-170) {
    m = 1.0;
    scale = absxk;
  } else {
    t = absxk / 3.3121686421112381E-170;
    m = t * t;
  }
  absxk = std::abs(joint_axes[1]);
  if (absxk > scale) {
    t = scale / absxk;
    m = m * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    m += t * t;
  }
  absxk = std::abs(joint_axes[2]);
  if (absxk > scale) {
    t = scale / absxk;
    m = m * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    m += t * t;
  }
  m = scale * std::sqrt(m);
  scale = 3.3121686421112381E-170;
  ax_idx_2 = joint_axes[0] / m;
  ax_idx_0 = ax_idx_2;
  absxk = std::abs(ax_idx_2);
  if (absxk > 3.3121686421112381E-170) {
    y = 1.0;
    scale = absxk;
  } else {
    t = absxk / 3.3121686421112381E-170;
    y = t * t;
  }
  ax_idx_2 = joint_axes[1] / m;
  ax_idx_1 = ax_idx_2;
  absxk = std::abs(ax_idx_2);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }
  ax_idx_2 = joint_axes[2] / m;
  absxk = std::abs(ax_idx_2);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }
  y = scale * std::sqrt(y);
  if (y - 1.0 < 1.4901161193847656E-8) {
    b_obj->JointAxisInternal[0] = ax_idx_0;
    b_obj->JointAxisInternal[1] = ax_idx_1;
    b_obj->JointAxisInternal[2] = ax_idx_2;
    switch_expression.set_size(1, b_obj->Type.size(1));
    loop_ub = b_obj->Type.size(1);
    for (i = 0; i < loop_ub; i++) {
      switch_expression[i] = b_obj->Type[i];
    }
    b_bool = false;
    if (switch_expression.size(1) == 8) {
      loop_ub = 0;
      do {
        exitg1 = 0;
        if (loop_ub < 8) {
          if (switch_expression[loop_ub] != b_cv1[loop_ub]) {
            exitg1 = 1;
          } else {
            loop_ub++;
          }
        } else {
          b_bool = true;
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }
    if (b_bool) {
      i = 0;
    } else {
      i = -1;
    }
    if (i == 0) {
      ax[0] = ax_idx_0;
      ax[1] = ax_idx_1;
      ax[2] = ax_idx_2;
      ax[3] = 0.0;
      ax[4] = 0.0;
      ax[5] = 0.0;
      b_obj->MotionSubspace.set_size(6, 1);
      for (i = 0; i < 6; i++) {
        b_obj->MotionSubspace[i] = ax[i];
      }
    } else {
      ax[0] = 0.0;
      ax[1] = 0.0;
      ax[2] = 0.0;
      ax[3] = ax_idx_0;
      ax[4] = ax_idx_1;
      ax[5] = ax_idx_2;
      b_obj->MotionSubspace.set_size(6, 1);
      for (i = 0; i < 6; i++) {
        b_obj->MotionSubspace[i] = ax[i];
      }
    }
  }
  obj = iobj_4.BodyInternal;
  obj->JointInternal = b_obj->copy(&(&iobj_2)[2]);
  //  Set collision geometry
  collisionObj.RadiusInternal = radius;
  collisionObj.LengthInternal = length;
  collisionObj.GeometryInternal = collisioncodegen_makeCylinder(radius, length);
  collisionObj.matlabCodegenIsDeleted = false;
  for (i = 0; i < 3; i++) {
    i1 = i << 2;
    collisionObj.PoseInternal[i1] = dv[3 * i];
    collisionObj.PoseInternal[i1 + 1] = dv[3 * i + 1];
    collisionObj.PoseInternal[i1 + 2] = dv[3 * i + 2];
  }
  collisionObj.PoseInternal[12] = length / 2.0;
  collisionObj.PoseInternal[13] = 0.0;
  collisionObj.PoseInternal[14] = 0.0;
  collisionObj.PoseInternal[3] = 0.0;
  collisionObj.PoseInternal[7] = 0.0;
  collisionObj.PoseInternal[11] = 0.0;
  collisionObj.PoseInternal[15] = 1.0;
  obj = iobj_4.BodyInternal;
  for (i = 0; i < 4; i++) {
    signed char i2;
    signed char i3;
    signed char i4;
    signed char i5;
    i2 = iv[i];
    i3 = iv[i + 4];
    i4 = iv[i + 8];
    i5 = iv[i + 12];
    for (i1 = 0; i1 < 4; i1++) {
      loop_ub = i1 << 2;
      b_y[i + loop_ub] =
          ((static_cast<double>(i2) * collisionObj.PoseInternal[loop_ub] +
            static_cast<double>(i3) * collisionObj.PoseInternal[loop_ub + 1]) +
           static_cast<double>(i4) * collisionObj.PoseInternal[loop_ub + 2]) +
          static_cast<double>(i5) * collisionObj.PoseInternal[loop_ub + 3];
    }
  }
  void *collisionObj_GeometryInternal;
  lobj_0.RadiusInternal = radius;
  lobj_0.LengthInternal = length;
  lobj_0.GeometryInternal = collisioncodegen_makeCylinder(radius, length);
  lobj_0.matlabCodegenIsDeleted = false;
  std::copy(&collisionObj.PoseInternal[0], &collisionObj.PoseInternal[16],
            &lobj_0.PoseInternal[0]);
  collisionObj_GeometryInternal = collisioncodegen_makeCylinder(radius, length);
  collisionGeometry.CollisionPrimitive = collisionObj_GeometryInternal;
  std::copy(&b_y[0], &b_y[16], &collisionGeometry.LocalPose[0]);
  std::copy(&b_y[0], &b_y[16], &collisionGeometry.WorldPose[0]);
  c_obj = obj->CollisionsInternal;
  if (c_obj->Size < c_obj->MaxElements) {
    c_obj->Size++;
    c_obj->CollisionGeometries[static_cast<int>(c_obj->Size) - 1] =
        collisionGeometry;
  }
  lobj_0.matlabCodegenDestructor();
  //  Compute dynamics based on cylindrical geometry
  t = radius * radius;
  m = 3.1415926535897931 * t * length * rho;
  //  Mass
  //  Center of mass
  //  Inertia around x-axis
  //  Inertia around x and y axis
  scale = length / 2.0;
  scale = (0.25 * m * t + 0.083333333333333329 * m * (length * length)) +
          m * (scale * scale);
  //  Adjust inertia for the frame origin
  obj = iobj_4.BodyInternal;
  obj->MassInternal = m;
  absxk = obj->MassInternal;
  ax_idx_0 = obj->CenterOfMassInternal[0];
  ax_idx_1 = obj->CenterOfMassInternal[1];
  ax_idx_2 = obj->CenterOfMassInternal[2];
  for (i = 0; i < 9; i++) {
    b_I[i] = obj->InertiaInternal[i];
  }
  sc[0] = 0.0;
  sc[3] = -ax_idx_2;
  sc[6] = ax_idx_1;
  sc[1] = ax_idx_2;
  sc[4] = 0.0;
  sc[7] = -ax_idx_0;
  sc[2] = -ax_idx_1;
  sc[5] = ax_idx_0;
  sc[8] = 0.0;
  for (i = 0; i < 3; i++) {
    obj->SpatialInertia[6 * i] = b_I[3 * i];
    obj->SpatialInertia[6 * i + 1] = b_I[3 * i + 1];
    obj->SpatialInertia[6 * i + 2] = b_I[3 * i + 2];
  }
  for (i = 0; i < 3; i++) {
    i1 = 6 * (i + 3);
    obj->SpatialInertia[i1] = absxk * sc[3 * i];
    obj->SpatialInertia[i1 + 1] = absxk * sc[3 * i + 1];
    obj->SpatialInertia[i1 + 2] = absxk * sc[3 * i + 2];
  }
  for (i = 0; i < 3; i++) {
    obj->SpatialInertia[6 * i + 3] = absxk * sc[i];
    obj->SpatialInertia[6 * i + 4] = absxk * sc[i + 3];
    obj->SpatialInertia[6 * i + 5] = absxk * sc[i + 6];
  }
  for (i = 0; i < 3; i++) {
    i1 = 6 * (i + 3);
    obj->SpatialInertia[i1 + 3] = absxk * static_cast<double>(iv1[3 * i]);
    obj->SpatialInertia[i1 + 4] = absxk * static_cast<double>(iv1[3 * i + 1]);
    obj->SpatialInertia[i1 + 5] = absxk * static_cast<double>(iv1[3 * i + 2]);
  }
  obj = iobj_4.BodyInternal;
  obj->CenterOfMassInternal[0] = length / 2.0;
  obj->CenterOfMassInternal[1] = 0.0;
  obj->CenterOfMassInternal[2] = 0.0;
  absxk = obj->MassInternal;
  ax_idx_0 = obj->CenterOfMassInternal[0];
  ax_idx_1 = obj->CenterOfMassInternal[1];
  ax_idx_2 = obj->CenterOfMassInternal[2];
  for (i = 0; i < 9; i++) {
    b_I[i] = obj->InertiaInternal[i];
  }
  sc[0] = 0.0;
  sc[3] = -ax_idx_2;
  sc[6] = ax_idx_1;
  sc[1] = ax_idx_2;
  sc[4] = 0.0;
  sc[7] = -ax_idx_0;
  sc[2] = -ax_idx_1;
  sc[5] = ax_idx_0;
  sc[8] = 0.0;
  for (i = 0; i < 3; i++) {
    obj->SpatialInertia[6 * i] = b_I[3 * i];
    obj->SpatialInertia[6 * i + 1] = b_I[3 * i + 1];
    obj->SpatialInertia[6 * i + 2] = b_I[3 * i + 2];
  }
  for (i = 0; i < 3; i++) {
    i1 = 6 * (i + 3);
    obj->SpatialInertia[i1] = absxk * sc[3 * i];
    obj->SpatialInertia[i1 + 1] = absxk * sc[3 * i + 1];
    obj->SpatialInertia[i1 + 2] = absxk * sc[3 * i + 2];
  }
  for (i = 0; i < 3; i++) {
    obj->SpatialInertia[6 * i + 3] = absxk * sc[i];
    obj->SpatialInertia[6 * i + 4] = absxk * sc[i + 3];
    obj->SpatialInertia[6 * i + 5] = absxk * sc[i + 6];
  }
  for (i = 0; i < 3; i++) {
    i1 = 6 * (i + 3);
    obj->SpatialInertia[i1 + 3] = absxk * static_cast<double>(iv1[3 * i]);
    obj->SpatialInertia[i1 + 4] = absxk * static_cast<double>(iv1[3 * i + 1]);
    obj->SpatialInertia[i1 + 5] = absxk * static_cast<double>(iv1[3 * i + 2]);
  }
  ax[0] = 0.5 * m * t;
  ax[1] = scale;
  ax[2] = scale;
  ax[3] = 0.0;
  ax[4] = 0.0;
  ax[5] = 0.0;
  iobj_4.set_Inertia(ax);
  return body;
}

//
// Validate inputs
//
// Arguments    : double rho
//                double radius
//                const double arm_length[6]
//                const double joint_axes[18]
//                const double joint_angles[6]
//                const double config[6]
//                const double vel[6]
//                const double tq[6]
//                double acc_data[]
//                int acc_size[1]
//                double linkPositionsArray[18]
// Return Type  : void
//
void forward_dynamics_robot_6arm(double rho, double radius,
                                 const double arm_length[6],
                                 const double joint_axes[18],
                                 const double joint_angles[6],
                                 const double config[6], const double vel[6],
                                 const double tq[6], double acc_data[],
                                 int acc_size[1], double linkPositionsArray[18])
{
  static const char b_cv[6]{'l', 'i', 'n', 'k', '0', '1'};
  static const char b_cv1[6]{'l', 'i', 'n', 'k', '0', '2'};
  static const char b_cv2[6]{'l', 'i', 'n', 'k', '0', '3'};
  static const char cv3[6]{'l', 'i', 'n', 'k', '0', '4'};
  static const char cv4[6]{'l', 'i', 'n', 'k', '0', '5'};
  static const char cv5[6]{'l', 'i', 'n', 'k', '0', '6'};
  coder::rigidBody lobj_14[6];
  coder::rigidBody body_EE;
  coder::rigidBody *bodies_idx_0;
  coder::rigidBody *bodies_idx_1;
  coder::rigidBody *bodies_idx_2;
  coder::rigidBody *bodies_idx_3;
  coder::rigidBody *bodies_idx_4;
  coder::rigidBody *bodies_idx_5;
  coder::rigidBodyJoint lobj_12[34];
  coder::rigidBodyJoint b_joint;
  coder::rigidBodyJoint c_joint;
  coder::rigidBodyJoint d_joint;
  coder::rigidBodyJoint e_joint;
  coder::rigidBodyJoint f_joint;
  coder::rigidBodyJoint joint;
  coder::rigidBodyJoint joint_EE;
  coder::rigidBodyJoint *iobj_0;
  coder::rigidBodyTree robot;
  coder::robotics::manip::internal::CollisionSet lobj_11[27];
  coder::robotics::manip::internal::RigidBody lobj_13[7];
  coder::robotics::manip::internal::RigidBody *obj;
  coder::robotics::manip::internal::RigidBodyTree lobj_10[7];
  coder::robotics::manip::internal::b_RigidBody lobj_9[7];
  coder::array<cell_wrap_33, 2U> Ttree;
  double T1[16];
  double a[16];
  double R[9];
  double tempR[9];
  double c_joint_axes[4];
  double b_joint_axes[3];
  double tempR_tmp;
  double v_idx_0;
  double v_idx_1;
  double v_idx_2;
  int jcol;
  int k;
  signed char b_I[16];
  signed char i1;
  signed char i2;
  signed char i3;
  signed char i4;
  if (!isInitialized_forward_dynamics_robot_6arm) {
    forward_dynamics_robot_6arm_initialize();
  }
  for (int i{0}; i < 27; i++) {
    lobj_11[i].matlabCodegenIsDeleted = true;
  }
  for (int i{0}; i < 7; i++) {
    lobj_10[i]._pobj1[0].matlabCodegenIsDeleted = true;
    lobj_10[i]._pobj1[1].matlabCodegenIsDeleted = true;
  }
  for (int i{0}; i < 7; i++) {
    lobj_9[i]._pobj0.matlabCodegenIsDeleted = true;
  }
  robot._pobj0.matlabCodegenIsDeleted = true;
  for (int i{0}; i < 7; i++) {
    robot.TreeInternal._pobj2[i]._pobj0.matlabCodegenIsDeleted = true;
  }
  for (int i{0}; i < 6; i++) {
    robot.TreeInternal._pobj0[i].matlabCodegenIsDeleted = true;
  }
  robot.TreeInternal.Base._pobj0.matlabCodegenIsDeleted = true;
  for (int i{0}; i < 7; i++) {
    lobj_9[i].matlabCodegenIsDeleted = true;
  }
  for (int i{0}; i < 7; i++) {
    robot.TreeInternal._pobj2[i].matlabCodegenIsDeleted = true;
  }
  robot.TreeInternal.Base.matlabCodegenIsDeleted = true;
  robot.TreeInternal.matlabCodegenIsDeleted = true;
  robot.matlabCodegenIsDeleted = true;
  for (int i{0}; i < 7; i++) {
    lobj_13[i].matlabCodegenIsDeleted = true;
  }
  for (int i{0}; i < 7; i++) {
    lobj_10[i]._pobj0.matlabCodegenIsDeleted = true;
  }
  for (int i{0}; i < 7; i++) {
    lobj_10[i].Base.matlabCodegenIsDeleted = true;
  }
  for (int i{0}; i < 7; i++) {
    lobj_10[i].matlabCodegenIsDeleted = true;
  }
  for (int i{0}; i < 6; i++) {
    lobj_14[i].matlabCodegenIsDeleted = true;
  }
  double b_tempR_tmp;
  double c_tempR_tmp;
  double d_tempR_tmp;
  double e_tempR_tmp;
  double f_tempR_tmp;
  double g_tempR_tmp;
  double h_tempR_tmp;
  body_EE.matlabCodegenIsDeleted = true;
  //  Create a robot model
  robot.init();
  //  Pre-allocate rigid bodies
  //  Configure the bodies
  //  Create joint and link
  joint.c_init();
  //  Set the joint's transformation
  v_idx_2 = 1.0 / std::sqrt((joint_axes[0] * joint_axes[0] +
                             joint_axes[6] * joint_axes[6]) +
                            joint_axes[12] * joint_axes[12]);
  v_idx_0 = joint_axes[0] * v_idx_2;
  v_idx_1 = joint_axes[6] * v_idx_2;
  v_idx_2 *= joint_axes[12];
  tempR_tmp = v_idx_0 * v_idx_1 * 0.0;
  b_tempR_tmp = v_idx_0 * v_idx_2 * 0.0;
  c_tempR_tmp = v_idx_1 * v_idx_2 * 0.0;
  d_tempR_tmp = v_idx_0 * v_idx_0 * 0.0 + 1.0;
  e_tempR_tmp = tempR_tmp - v_idx_2 * 0.0;
  f_tempR_tmp = b_tempR_tmp + v_idx_1 * 0.0;
  tempR_tmp += v_idx_2 * 0.0;
  g_tempR_tmp = v_idx_1 * v_idx_1 * 0.0 + 1.0;
  h_tempR_tmp = c_tempR_tmp - v_idx_0 * 0.0;
  b_tempR_tmp -= v_idx_1 * 0.0;
  c_tempR_tmp += v_idx_0 * 0.0;
  v_idx_2 = v_idx_2 * v_idx_2 * 0.0 + 1.0;
  coder::cat(d_tempR_tmp, e_tempR_tmp, f_tempR_tmp, tempR_tmp, g_tempR_tmp,
             h_tempR_tmp, b_tempR_tmp, c_tempR_tmp, v_idx_2, tempR);
  coder::cat(d_tempR_tmp, e_tempR_tmp, f_tempR_tmp, tempR_tmp, g_tempR_tmp,
             h_tempR_tmp, b_tempR_tmp, c_tempR_tmp, v_idx_2, R);
  for (k = 0; k < 3; k++) {
    R[k] = tempR[3 * k];
    R[k + 3] = tempR[3 * k + 1];
    R[k + 6] = tempR[3 * k + 2];
  }
  std::memset(&T1[0], 0, 16U * sizeof(double));
  for (int i{0}; i < 3; i++) {
    k = i << 2;
    T1[k] = R[3 * i];
    T1[k + 1] = R[3 * i + 1];
    T1[k + 2] = R[3 * i + 2];
  }
  T1[15] = 1.0;
  for (int i{0}; i < 4; i++) {
    i1 = iv[i];
    i2 = iv[i + 4];
    i3 = iv[i + 8];
    i4 = iv[i + 12];
    for (int i5{0}; i5 < 4; i5++) {
      k = i5 << 2;
      jcol = i + k;
      joint.JointToParentTransform[jcol] = 0.0;
      joint.JointToParentTransform[jcol] += static_cast<double>(i1) * T1[k];
      joint.JointToParentTransform[jcol] += static_cast<double>(i2) * T1[k + 1];
      joint.JointToParentTransform[jcol] += static_cast<double>(i3) * T1[k + 2];
      joint.JointToParentTransform[jcol] += static_cast<double>(i4) * T1[k + 3];
    }
  }
  std::memset(&joint.ChildToJointTransform[0], 0, 16U * sizeof(double));
  joint.ChildToJointTransform[0] = 1.0;
  joint.ChildToJointTransform[5] = 1.0;
  joint.ChildToJointTransform[10] = 1.0;
  joint.ChildToJointTransform[15] = 1.0;
  //  Generate body name
  //  Pre-allocate with blanks
  //  Create and configure body
  b_joint_axes[0] = joint_axes[0];
  b_joint_axes[1] = joint_axes[6];
  b_joint_axes[2] = joint_axes[12];
  bodies_idx_0 =
      createBody(b_cv, joint, b_joint_axes, radius, arm_length[0], rho,
                 lobj_10[0], lobj_11[0], lobj_12[0], lobj_13[0], lobj_14[0]);
  //  Create joint and link
  b_joint.d_init();
  //  Set the joint's transformation
  for (int i{0}; i < 16; i++) {
    b_I[i] = 0;
  }
  b_I[0] = 1;
  b_I[5] = 1;
  b_I[10] = 1;
  b_I[15] = 1;
  for (jcol = 0; jcol < 4; jcol++) {
    k = jcol << 2;
    a[k] = b_I[k];
    a[k + 1] = b_I[k + 1];
    a[k + 2] = b_I[k + 2];
    a[k + 3] = b_I[k + 3];
  }
  a[12] = arm_length[1];
  a[13] = 0.0;
  a[14] = 0.0;
  c_joint_axes[0] = joint_axes[1];
  c_joint_axes[1] = joint_axes[7];
  c_joint_axes[2] = joint_axes[13];
  c_joint_axes[3] = joint_angles[1];
  coder::axang2tform(c_joint_axes, T1);
  for (int i{0}; i < 4; i++) {
    v_idx_2 = a[i];
    v_idx_0 = a[i + 4];
    v_idx_1 = a[i + 8];
    tempR_tmp = a[i + 12];
    for (int i5{0}; i5 < 4; i5++) {
      k = i5 << 2;
      jcol = i + k;
      b_joint.JointToParentTransform[jcol] = 0.0;
      b_joint.JointToParentTransform[jcol] += v_idx_2 * T1[k];
      b_joint.JointToParentTransform[jcol] += v_idx_0 * T1[k + 1];
      b_joint.JointToParentTransform[jcol] += v_idx_1 * T1[k + 2];
      b_joint.JointToParentTransform[jcol] += tempR_tmp * T1[k + 3];
    }
  }
  std::memset(&b_joint.ChildToJointTransform[0], 0, 16U * sizeof(double));
  b_joint.ChildToJointTransform[0] = 1.0;
  b_joint.ChildToJointTransform[5] = 1.0;
  b_joint.ChildToJointTransform[10] = 1.0;
  b_joint.ChildToJointTransform[15] = 1.0;
  //  Generate body name
  //  Pre-allocate with blanks
  //  Create and configure body
  b_joint_axes[0] = joint_axes[1];
  b_joint_axes[1] = joint_axes[7];
  b_joint_axes[2] = joint_axes[13];
  bodies_idx_1 =
      createBody(b_cv1, b_joint, b_joint_axes, radius, arm_length[1], rho,
                 lobj_10[1], lobj_11[2], lobj_12[3], lobj_13[1], lobj_14[1]);
  //  Create joint and link
  c_joint.e_init();
  //  Set the joint's transformation
  for (int i{0}; i < 16; i++) {
    b_I[i] = 0;
  }
  b_I[0] = 1;
  b_I[5] = 1;
  b_I[10] = 1;
  b_I[15] = 1;
  for (jcol = 0; jcol < 4; jcol++) {
    k = jcol << 2;
    a[k] = b_I[k];
    a[k + 1] = b_I[k + 1];
    a[k + 2] = b_I[k + 2];
    a[k + 3] = b_I[k + 3];
  }
  a[12] = arm_length[2];
  a[13] = 0.0;
  a[14] = 0.0;
  c_joint_axes[0] = joint_axes[2];
  c_joint_axes[1] = joint_axes[8];
  c_joint_axes[2] = joint_axes[14];
  c_joint_axes[3] = joint_angles[2];
  coder::axang2tform(c_joint_axes, T1);
  for (int i{0}; i < 4; i++) {
    v_idx_2 = a[i];
    v_idx_0 = a[i + 4];
    v_idx_1 = a[i + 8];
    tempR_tmp = a[i + 12];
    for (int i5{0}; i5 < 4; i5++) {
      k = i5 << 2;
      jcol = i + k;
      c_joint.JointToParentTransform[jcol] = 0.0;
      c_joint.JointToParentTransform[jcol] += v_idx_2 * T1[k];
      c_joint.JointToParentTransform[jcol] += v_idx_0 * T1[k + 1];
      c_joint.JointToParentTransform[jcol] += v_idx_1 * T1[k + 2];
      c_joint.JointToParentTransform[jcol] += tempR_tmp * T1[k + 3];
    }
  }
  std::memset(&c_joint.ChildToJointTransform[0], 0, 16U * sizeof(double));
  c_joint.ChildToJointTransform[0] = 1.0;
  c_joint.ChildToJointTransform[5] = 1.0;
  c_joint.ChildToJointTransform[10] = 1.0;
  c_joint.ChildToJointTransform[15] = 1.0;
  //  Generate body name
  //  Pre-allocate with blanks
  //  Create and configure body
  b_joint_axes[0] = joint_axes[2];
  b_joint_axes[1] = joint_axes[8];
  b_joint_axes[2] = joint_axes[14];
  bodies_idx_2 =
      createBody(b_cv2, c_joint, b_joint_axes, radius, arm_length[2], rho,
                 lobj_10[2], lobj_11[4], lobj_12[6], lobj_13[2], lobj_14[2]);
  //  Create joint and link
  d_joint.f_init();
  //  Set the joint's transformation
  for (int i{0}; i < 16; i++) {
    b_I[i] = 0;
  }
  b_I[0] = 1;
  b_I[5] = 1;
  b_I[10] = 1;
  b_I[15] = 1;
  for (jcol = 0; jcol < 4; jcol++) {
    k = jcol << 2;
    a[k] = b_I[k];
    a[k + 1] = b_I[k + 1];
    a[k + 2] = b_I[k + 2];
    a[k + 3] = b_I[k + 3];
  }
  a[12] = arm_length[3];
  a[13] = 0.0;
  a[14] = 0.0;
  c_joint_axes[0] = joint_axes[3];
  c_joint_axes[1] = joint_axes[9];
  c_joint_axes[2] = joint_axes[15];
  c_joint_axes[3] = joint_angles[3];
  coder::axang2tform(c_joint_axes, T1);
  for (int i{0}; i < 4; i++) {
    v_idx_2 = a[i];
    v_idx_0 = a[i + 4];
    v_idx_1 = a[i + 8];
    tempR_tmp = a[i + 12];
    for (int i5{0}; i5 < 4; i5++) {
      k = i5 << 2;
      jcol = i + k;
      d_joint.JointToParentTransform[jcol] = 0.0;
      d_joint.JointToParentTransform[jcol] += v_idx_2 * T1[k];
      d_joint.JointToParentTransform[jcol] += v_idx_0 * T1[k + 1];
      d_joint.JointToParentTransform[jcol] += v_idx_1 * T1[k + 2];
      d_joint.JointToParentTransform[jcol] += tempR_tmp * T1[k + 3];
    }
  }
  std::memset(&d_joint.ChildToJointTransform[0], 0, 16U * sizeof(double));
  d_joint.ChildToJointTransform[0] = 1.0;
  d_joint.ChildToJointTransform[5] = 1.0;
  d_joint.ChildToJointTransform[10] = 1.0;
  d_joint.ChildToJointTransform[15] = 1.0;
  //  Generate body name
  //  Pre-allocate with blanks
  //  Create and configure body
  b_joint_axes[0] = joint_axes[3];
  b_joint_axes[1] = joint_axes[9];
  b_joint_axes[2] = joint_axes[15];
  bodies_idx_3 =
      createBody(cv3, d_joint, b_joint_axes, radius, arm_length[3], rho,
                 lobj_10[3], lobj_11[6], lobj_12[9], lobj_13[3], lobj_14[3]);
  //  Create joint and link
  e_joint.g_init();
  //  Set the joint's transformation
  for (int i{0}; i < 16; i++) {
    b_I[i] = 0;
  }
  b_I[0] = 1;
  b_I[5] = 1;
  b_I[10] = 1;
  b_I[15] = 1;
  for (jcol = 0; jcol < 4; jcol++) {
    k = jcol << 2;
    a[k] = b_I[k];
    a[k + 1] = b_I[k + 1];
    a[k + 2] = b_I[k + 2];
    a[k + 3] = b_I[k + 3];
  }
  a[12] = arm_length[4];
  a[13] = 0.0;
  a[14] = 0.0;
  c_joint_axes[0] = joint_axes[4];
  c_joint_axes[1] = joint_axes[10];
  c_joint_axes[2] = joint_axes[16];
  c_joint_axes[3] = joint_angles[4];
  coder::axang2tform(c_joint_axes, T1);
  for (int i{0}; i < 4; i++) {
    v_idx_2 = a[i];
    v_idx_0 = a[i + 4];
    v_idx_1 = a[i + 8];
    tempR_tmp = a[i + 12];
    for (int i5{0}; i5 < 4; i5++) {
      k = i5 << 2;
      jcol = i + k;
      e_joint.JointToParentTransform[jcol] = 0.0;
      e_joint.JointToParentTransform[jcol] += v_idx_2 * T1[k];
      e_joint.JointToParentTransform[jcol] += v_idx_0 * T1[k + 1];
      e_joint.JointToParentTransform[jcol] += v_idx_1 * T1[k + 2];
      e_joint.JointToParentTransform[jcol] += tempR_tmp * T1[k + 3];
    }
  }
  std::memset(&e_joint.ChildToJointTransform[0], 0, 16U * sizeof(double));
  e_joint.ChildToJointTransform[0] = 1.0;
  e_joint.ChildToJointTransform[5] = 1.0;
  e_joint.ChildToJointTransform[10] = 1.0;
  e_joint.ChildToJointTransform[15] = 1.0;
  //  Generate body name
  //  Pre-allocate with blanks
  //  Create and configure body
  b_joint_axes[0] = joint_axes[4];
  b_joint_axes[1] = joint_axes[10];
  b_joint_axes[2] = joint_axes[16];
  bodies_idx_4 =
      createBody(cv4, e_joint, b_joint_axes, radius, arm_length[4], rho,
                 lobj_10[4], lobj_11[8], lobj_12[12], lobj_13[4], lobj_14[4]);
  //  Create joint and link
  f_joint.h_init();
  //  Set the joint's transformation
  for (int i{0}; i < 16; i++) {
    b_I[i] = 0;
  }
  b_I[0] = 1;
  b_I[5] = 1;
  b_I[10] = 1;
  b_I[15] = 1;
  for (jcol = 0; jcol < 4; jcol++) {
    k = jcol << 2;
    a[k] = b_I[k];
    a[k + 1] = b_I[k + 1];
    a[k + 2] = b_I[k + 2];
    a[k + 3] = b_I[k + 3];
  }
  a[12] = arm_length[5];
  c_joint_axes[0] = joint_axes[5];
  a[13] = 0.0;
  c_joint_axes[1] = joint_axes[11];
  a[14] = 0.0;
  c_joint_axes[2] = joint_axes[17];
  c_joint_axes[3] = joint_angles[5];
  coder::axang2tform(c_joint_axes, T1);
  for (int i{0}; i < 4; i++) {
    v_idx_2 = a[i];
    v_idx_0 = a[i + 4];
    v_idx_1 = a[i + 8];
    tempR_tmp = a[i + 12];
    for (int i5{0}; i5 < 4; i5++) {
      k = i5 << 2;
      jcol = i + k;
      f_joint.JointToParentTransform[jcol] = 0.0;
      f_joint.JointToParentTransform[jcol] += v_idx_2 * T1[k];
      f_joint.JointToParentTransform[jcol] += v_idx_0 * T1[k + 1];
      f_joint.JointToParentTransform[jcol] += v_idx_1 * T1[k + 2];
      f_joint.JointToParentTransform[jcol] += tempR_tmp * T1[k + 3];
    }
  }
  std::memset(&f_joint.ChildToJointTransform[0], 0, 16U * sizeof(double));
  f_joint.ChildToJointTransform[0] = 1.0;
  f_joint.ChildToJointTransform[5] = 1.0;
  f_joint.ChildToJointTransform[10] = 1.0;
  f_joint.ChildToJointTransform[15] = 1.0;
  //  Generate body name
  //  Pre-allocate with blanks
  //  Create and configure body
  b_joint_axes[0] = joint_axes[5];
  b_joint_axes[1] = joint_axes[11];
  b_joint_axes[2] = joint_axes[17];
  bodies_idx_5 =
      createBody(cv5, f_joint, b_joint_axes, radius, arm_length[5], rho,
                 lobj_10[5], lobj_11[10], lobj_12[15], lobj_13[5], lobj_14[5]);
  //  Add bodies to the robot model
  robot.addBody(bodies_idx_0, lobj_11[12], lobj_12[18], lobj_9[0]);
  //  Pre-allocate with blanks
  robot.addBody(bodies_idx_1, b_cv, lobj_11[14], lobj_12[20], lobj_9[1]);
  robot.addBody(bodies_idx_2, b_cv1, lobj_11[16], lobj_12[22], lobj_9[2]);
  robot.addBody(bodies_idx_3, b_cv2, lobj_11[18], lobj_12[24], lobj_9[3]);
  robot.addBody(bodies_idx_4, cv3, lobj_11[20], lobj_12[26], lobj_9[4]);
  robot.addBody(bodies_idx_5, cv4, lobj_11[22], lobj_12[28], lobj_9[5]);
  //  Assuming 'robot' is your RigidBodyTree object and bodies{6} is the last
  //  link Create the end effector as a rigid body
  body_EE.init(lobj_10[6], lobj_11[24], lobj_12[30], lobj_13[6]);
  //  Create a fixed joint to attach the end effector to the last link
  joint_EE.i_init();
  //  Define the transformation from the last link to the end effector
  //  This transformation positions the end effector relative to the last link.
  //  Adjust [0, 0, 0] to position the end effector as needed.
  for (int i{0}; i < 16; i++) {
    b_I[i] = 0;
  }
  b_I[0] = 1;
  b_I[5] = 1;
  b_I[10] = 1;
  b_I[15] = 1;
  for (jcol = 0; jcol < 4; jcol++) {
    k = jcol << 2;
    T1[k] = b_I[k];
    T1[k + 1] = b_I[k + 1];
    T1[k + 2] = b_I[k + 2];
    T1[k + 3] = b_I[k + 3];
  }
  T1[12] = arm_length[5];
  T1[13] = 0.0;
  T1[14] = 0.0;
  std::copy(&T1[0], &T1[16], &joint_EE.JointToParentTransform[0]);
  std::memset(&joint_EE.ChildToJointTransform[0], 0, 16U * sizeof(double));
  joint_EE.ChildToJointTransform[0] = 1.0;
  joint_EE.ChildToJointTransform[5] = 1.0;
  joint_EE.ChildToJointTransform[10] = 1.0;
  joint_EE.ChildToJointTransform[15] = 1.0;
  //  Example transformation
  //  Associate the joint with the end effector
  iobj_0 = &lobj_12[31];
  obj = body_EE.BodyInternal;
  obj->JointInternal = joint_EE.copy(iobj_0);
  //  Add the end effector to the robot, attaching it to the last link
  robot.addBody(&body_EE, cv5, lobj_11[25], lobj_12[32], lobj_9[6]);
  robot.TreeInternal.Gravity[0] = 0.0;
  robot.TreeInternal.Gravity[1] = 0.0;
  robot.TreeInternal.Gravity[2] = -9.81;
  //  Perform forward dynamics
  acc_size[0] = robot.forwardDynamics(config, vel, tq, acc_data);
  //  Initialize link positions array
  //  Each row: [startX, startY, startZ, endX, endY, endZ]
  robot.TreeInternal.forwardKinematics(config, Ttree);
  v_idx_2 = robot.TreeInternal.validateInputBodyName(b_cv1);
  if (v_idx_2 == 0.0) {
    std::memset(&T1[0], 0, 16U * sizeof(double));
    T1[0] = 1.0;
    T1[5] = 1.0;
    T1[10] = 1.0;
    T1[15] = 1.0;
  } else {
    for (int i{0}; i < 16; i++) {
      T1[i] = Ttree[static_cast<int>(v_idx_2) - 1].f1[i];
    }
  }
  for (int i{0}; i < 4; i++) {
    i1 = iv[i];
    i2 = iv[i + 4];
    i3 = iv[i + 8];
    i4 = iv[i + 12];
    for (int i5{0}; i5 < 4; i5++) {
      k = i5 << 2;
      a[i + k] = ((static_cast<double>(i1) * T1[k] +
                   static_cast<double>(i2) * T1[k + 1]) +
                  static_cast<double>(i3) * T1[k + 2]) +
                 static_cast<double>(i4) * T1[k + 3];
    }
  }
  linkPositionsArray[0] = a[12];
  linkPositionsArray[6] = a[13];
  linkPositionsArray[12] = a[14];
  robot.TreeInternal.forwardKinematics(config, Ttree);
  v_idx_2 = robot.TreeInternal.validateInputBodyName(b_cv2);
  if (v_idx_2 == 0.0) {
    std::memset(&T1[0], 0, 16U * sizeof(double));
    T1[0] = 1.0;
    T1[5] = 1.0;
    T1[10] = 1.0;
    T1[15] = 1.0;
  } else {
    for (int i{0}; i < 16; i++) {
      T1[i] = Ttree[static_cast<int>(v_idx_2) - 1].f1[i];
    }
  }
  for (int i{0}; i < 4; i++) {
    i1 = iv[i];
    i2 = iv[i + 4];
    i3 = iv[i + 8];
    i4 = iv[i + 12];
    for (int i5{0}; i5 < 4; i5++) {
      k = i5 << 2;
      a[i + k] = ((static_cast<double>(i1) * T1[k] +
                   static_cast<double>(i2) * T1[k + 1]) +
                  static_cast<double>(i3) * T1[k + 2]) +
                 static_cast<double>(i4) * T1[k + 3];
    }
  }
  linkPositionsArray[1] = a[12];
  linkPositionsArray[7] = a[13];
  linkPositionsArray[13] = a[14];
  robot.TreeInternal.forwardKinematics(config, Ttree);
  v_idx_2 = robot.TreeInternal.validateInputBodyName(cv3);
  if (v_idx_2 == 0.0) {
    std::memset(&T1[0], 0, 16U * sizeof(double));
    T1[0] = 1.0;
    T1[5] = 1.0;
    T1[10] = 1.0;
    T1[15] = 1.0;
  } else {
    for (int i{0}; i < 16; i++) {
      T1[i] = Ttree[static_cast<int>(v_idx_2) - 1].f1[i];
    }
  }
  for (int i{0}; i < 4; i++) {
    i1 = iv[i];
    i2 = iv[i + 4];
    i3 = iv[i + 8];
    i4 = iv[i + 12];
    for (int i5{0}; i5 < 4; i5++) {
      k = i5 << 2;
      a[i + k] = ((static_cast<double>(i1) * T1[k] +
                   static_cast<double>(i2) * T1[k + 1]) +
                  static_cast<double>(i3) * T1[k + 2]) +
                 static_cast<double>(i4) * T1[k + 3];
    }
  }
  linkPositionsArray[2] = a[12];
  linkPositionsArray[8] = a[13];
  linkPositionsArray[14] = a[14];
  robot.getTransform(config, T1);
  linkPositionsArray[3] = T1[12];
  linkPositionsArray[9] = T1[13];
  linkPositionsArray[15] = T1[14];
  robot.b_getTransform(config, T1);
  linkPositionsArray[4] = T1[12];
  linkPositionsArray[10] = T1[13];
  linkPositionsArray[16] = T1[14];
  robot.c_getTransform(config, T1);
  linkPositionsArray[5] = T1[12];
  linkPositionsArray[11] = T1[13];
  linkPositionsArray[17] = T1[14];
  body_EE.matlabCodegenDestructor();
  for (int i{0}; i < 6; i++) {
    lobj_14[i].matlabCodegenDestructor();
  }
  for (int i{0}; i < 7; i++) {
    lobj_10[i].matlabCodegenDestructor();
  }
  for (int i{0}; i < 7; i++) {
    lobj_10[i].Base.matlabCodegenDestructor();
  }
  for (int i{0}; i < 7; i++) {
    lobj_10[i]._pobj0.matlabCodegenDestructor();
  }
  for (int i{0}; i < 7; i++) {
    lobj_13[i].matlabCodegenDestructor();
  }
  robot.matlabCodegenDestructor();
  robot.TreeInternal.matlabCodegenDestructor();
  robot.TreeInternal.Base.matlabCodegenDestructor();
  for (int i{0}; i < 7; i++) {
    robot.TreeInternal._pobj2[i].matlabCodegenDestructor();
  }
  for (int i{0}; i < 7; i++) {
    lobj_9[i].matlabCodegenDestructor();
  }
  robot.TreeInternal.Base._pobj0.matlabCodegenDestructor();
  for (int i{0}; i < 6; i++) {
    robot.TreeInternal._pobj0[i].matlabCodegenDestructor();
  }
  for (int i{0}; i < 7; i++) {
    robot.TreeInternal._pobj2[i]._pobj0.matlabCodegenDestructor();
  }
  robot._pobj0.matlabCodegenDestructor();
  for (int i{0}; i < 7; i++) {
    lobj_9[i]._pobj0.matlabCodegenDestructor();
  }
  for (int i{0}; i < 7; i++) {
    lobj_10[i]._pobj1[0].matlabCodegenDestructor();
    lobj_10[i]._pobj1[1].matlabCodegenDestructor();
  }
  for (int i{0}; i < 27; i++) {
    lobj_11[i].matlabCodegenDestructor();
  }
}

//
// File trailer for forward_dynamics_robot_6arm.cpp
//
// [EOF]
//
