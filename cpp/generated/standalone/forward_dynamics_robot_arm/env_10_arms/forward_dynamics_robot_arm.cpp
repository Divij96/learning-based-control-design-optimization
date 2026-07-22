//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: forward_dynamics_robot_arm.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 02-Feb-2024 13:34:01
//

// Include Files
#include "forward_dynamics_robot_arm.h"
#include "CollisionGeometry.h"
#include "CollisionSet.h"
#include "RigidBody.h"
#include "RigidBodyTree1.h"
#include "axang2tform.h"
#include "collisionCylinder.h"
#include "forward_dynamics_robot_arm_data.h"
#include "forward_dynamics_robot_arm_initialize.h"
#include "rand.h"
#include "rigidBody1.h"
#include "rigidBodyJoint.h"
#include "rigidBodyTree.h"
#include "rt_nonfinite.h"
#include "trvec2tform.h"
#include "coder_array.h"
#include "collisioncodegen_api.hpp"
#include <algorithm>
#include <cmath>
#include <cstring>

// Function Declarations
static coder::rigidBody *createBody(const char bodyName[6],
                                    coder::rigidBodyJoint &joint, double radius,
                                    double length, double rho,
                                    coder::rigidBodyJoint &iobj_0,
                                    coder::rigidBody &iobj_1);

// Function Definitions
//
// Create a rigid body with the specified parameters
//
// Arguments    : const char bodyName[6]
//                coder::rigidBodyJoint &joint
//                double radius
//                double length
//                double rho
//                coder::rigidBodyJoint &iobj_0
//                coder::rigidBody &iobj_1
// Return Type  : coder::rigidBody *
//
static coder::rigidBody *createBody(const char bodyName[6],
                                    coder::rigidBodyJoint &joint, double radius,
                                    double length, double rho,
                                    coder::rigidBodyJoint &iobj_0,
                                    coder::rigidBody &iobj_1)
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
  coder::robotics::manip::internal::CollisionGeometry collisionGeometry;
  coder::robotics::manip::internal::CollisionSet *b_obj;
  coder::robotics::manip::internal::RigidBody *obj;
  coder::array<char, 2U> switch_expression;
  double y[16];
  double poslim_data[12];
  double b_I[9];
  double sc[9];
  double unusedExpr[5];
  double Iz;
  double com_idx_0;
  double com_idx_1;
  double com_idx_2;
  double m;
  double m_tmp;
  double mass;
  int exitg1;
  int i1;
  int loop_ub;
  signed char msubspace_data[36];
  boolean_T b_bool;
  body = &iobj_1;
  iobj_1._pobj3.NameInternal.set_size(1, 6);
  for (int i{0}; i < 6; i++) {
    iobj_1._pobj3.NameInternal[i] = bodyName[i];
  }
  iobj_1._pobj2.InTree = false;
  for (int i{0}; i < 16; i++) {
    iobj_1._pobj2.JointToParentTransform[i] = iv[i];
  }
  for (int i{0}; i < 16; i++) {
    iobj_1._pobj2.ChildToJointTransform[i] = iv[i];
  }
  iobj_1._pobj2.NameInternal.set_size(1, 10);
  for (int i{0}; i < 6; i++) {
    iobj_1._pobj2.NameInternal[i] = bodyName[i];
  }
  iobj_1._pobj2.NameInternal[6] = '_';
  iobj_1._pobj2.NameInternal[7] = 'j';
  iobj_1._pobj2.NameInternal[8] = 'n';
  iobj_1._pobj2.NameInternal[9] = 't';
  iobj_1._pobj2.Type.set_size(1, 5);
  for (int i{0}; i < 5; i++) {
    iobj_1._pobj2.Type[i] = b_cv[i];
  }
  switch_expression.set_size(1, iobj_1._pobj2.Type.size(1));
  loop_ub = iobj_1._pobj2.Type.size(1);
  for (int i{0}; i < loop_ub; i++) {
    switch_expression[i] = iobj_1._pobj2.Type[i];
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
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = b_iv[i];
    }
    poslim_data[0] = -3.1415926535897931;
    poslim_data[1] = 3.1415926535897931;
    iobj_1._pobj2.VelocityNumber = 1.0;
    iobj_1._pobj2.PositionNumber = 1.0;
    iobj_1._pobj2.JointAxisInternal[0] = 0.0;
    iobj_1._pobj2.JointAxisInternal[1] = 0.0;
    iobj_1._pobj2.JointAxisInternal[2] = 1.0;
    break;
  case 1:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = b_iv1[i];
    }
    poslim_data[0] = -0.5;
    poslim_data[1] = 0.5;
    iobj_1._pobj2.VelocityNumber = 1.0;
    iobj_1._pobj2.PositionNumber = 1.0;
    iobj_1._pobj2.JointAxisInternal[0] = 0.0;
    iobj_1._pobj2.JointAxisInternal[1] = 0.0;
    iobj_1._pobj2.JointAxisInternal[2] = 1.0;
    break;
  default:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = 0;
    }
    poslim_data[0] = 0.0;
    poslim_data[1] = 0.0;
    iobj_1._pobj2.VelocityNumber = 0.0;
    iobj_1._pobj2.PositionNumber = 0.0;
    iobj_1._pobj2.JointAxisInternal[0] = 0.0;
    iobj_1._pobj2.JointAxisInternal[1] = 0.0;
    iobj_1._pobj2.JointAxisInternal[2] = 0.0;
    break;
  }
  iobj_1._pobj2.MotionSubspace.set_size(6, 1);
  for (int i{0}; i < 6; i++) {
    iobj_1._pobj2.MotionSubspace[i] = msubspace_data[i];
  }
  iobj_1._pobj2.PositionLimitsInternal.set_size(1, 2);
  for (int i{0}; i < 2; i++) {
    iobj_1._pobj2.PositionLimitsInternal[i] = poslim_data[i];
  }
  iobj_1._pobj2.HomePositionInternal.set_size(1);
  iobj_1._pobj2.HomePositionInternal[0] = 0.0;
  iobj_1._pobj3.JointInternal = &iobj_1._pobj2;
  iobj_1._pobj3.Index = -1.0;
  iobj_1._pobj3.MassInternal = 1.0;
  iobj_1._pobj3.CenterOfMassInternal[0] = 0.0;
  iobj_1._pobj3.CenterOfMassInternal[1] = 0.0;
  iobj_1._pobj3.CenterOfMassInternal[2] = 0.0;
  std::memset(&b_I[0], 0, 9U * sizeof(double));
  b_I[0] = 1.0;
  b_I[4] = 1.0;
  b_I[8] = 1.0;
  for (int i{0}; i < 9; i++) {
    iobj_1._pobj3.InertiaInternal[i] = b_I[i];
  }
  for (int i{0}; i < 36; i++) {
    msubspace_data[i] = 0;
  }
  for (loop_ub = 0; loop_ub < 6; loop_ub++) {
    msubspace_data[loop_ub + 6 * loop_ub] = 1;
  }
  for (int i{0}; i < 36; i++) {
    iobj_1._pobj3.SpatialInertia[i] = msubspace_data[i];
  }
  iobj_1._pobj3.CollisionsInternal = iobj_1._pobj1[0].init(0.0);
  iobj_1._pobj3.matlabCodegenIsDeleted = false;
  iobj_1._pobj0.Base.NameInternal.set_size(1, 4);
  iobj_1._pobj0.Base.NameInternal[0] = 'b';
  iobj_1._pobj0.Base.NameInternal[1] = 'a';
  iobj_1._pobj0.Base.NameInternal[2] = 's';
  iobj_1._pobj0.Base.NameInternal[3] = 'e';
  iobj_1._pobj0.Base.JointInternal = iobj_1._pobj0._pobj2[0].init();
  iobj_1._pobj0.Base.Index = -1.0;
  iobj_1._pobj0.Base.MassInternal = 1.0;
  iobj_1._pobj0.Base.CenterOfMassInternal[0] = 0.0;
  iobj_1._pobj0.Base.CenterOfMassInternal[1] = 0.0;
  iobj_1._pobj0.Base.CenterOfMassInternal[2] = 0.0;
  std::memset(&b_I[0], 0, 9U * sizeof(double));
  b_I[0] = 1.0;
  b_I[4] = 1.0;
  b_I[8] = 1.0;
  for (int i{0}; i < 9; i++) {
    iobj_1._pobj0.Base.InertiaInternal[i] = b_I[i];
  }
  for (int i{0}; i < 36; i++) {
    msubspace_data[i] = 0;
  }
  for (loop_ub = 0; loop_ub < 6; loop_ub++) {
    msubspace_data[loop_ub + 6 * loop_ub] = 1;
  }
  for (int i{0}; i < 36; i++) {
    iobj_1._pobj0.Base.SpatialInertia[i] = msubspace_data[i];
  }
  iobj_1._pobj0.Base.CollisionsInternal = iobj_1._pobj0._pobj1[0].init(0.0);
  iobj_1._pobj0.Base.matlabCodegenIsDeleted = false;
  iobj_1._pobj0.Base.Index = 0.0;
  coder::b_rand(unusedExpr);
  iobj_1._pobj0._pobj0.NameInternal.set_size(1, 10);
  for (int i{0}; i < 10; i++) {
    iobj_1._pobj0._pobj0.NameInternal[i] = cv[i];
  }
  iobj_1._pobj0._pobj0.JointInternal = iobj_1._pobj0._pobj2[1].b_init();
  iobj_1._pobj0._pobj0.Index = -1.0;
  iobj_1._pobj0._pobj0.MassInternal = 1.0;
  iobj_1._pobj0._pobj0.CenterOfMassInternal[0] = 0.0;
  iobj_1._pobj0._pobj0.CenterOfMassInternal[1] = 0.0;
  iobj_1._pobj0._pobj0.CenterOfMassInternal[2] = 0.0;
  std::memset(&b_I[0], 0, 9U * sizeof(double));
  b_I[0] = 1.0;
  b_I[4] = 1.0;
  b_I[8] = 1.0;
  for (int i{0}; i < 9; i++) {
    iobj_1._pobj0._pobj0.InertiaInternal[i] = b_I[i];
  }
  for (int i{0}; i < 36; i++) {
    msubspace_data[i] = 0;
  }
  for (loop_ub = 0; loop_ub < 6; loop_ub++) {
    msubspace_data[loop_ub + 6 * loop_ub] = 1;
  }
  for (int i{0}; i < 36; i++) {
    iobj_1._pobj0._pobj0.SpatialInertia[i] = msubspace_data[i];
  }
  iobj_1._pobj0._pobj0.CollisionsInternal = iobj_1._pobj0._pobj1[1].init(0.0);
  iobj_1._pobj0._pobj0.matlabCodegenIsDeleted = false;
  iobj_1._pobj0.Bodies[0] = &iobj_1._pobj0._pobj0;
  coder::b_rand(unusedExpr);
  iobj_1._pobj0.matlabCodegenIsDeleted = false;
  iobj_1._pobj3.CollisionsInternal = iobj_1._pobj1[1].init(10.0);
  iobj_1.BodyInternal = &iobj_1._pobj3;
  iobj_1.TreeInternal = &iobj_1._pobj0;
  iobj_1.matlabCodegenIsDeleted = false;
  obj = iobj_1.BodyInternal;
  obj->JointInternal = joint.copy(iobj_0);
  //  Set collision geometry
  collisionObj.RadiusInternal = radius;
  collisionObj.LengthInternal = length;
  collisionObj.GeometryInternal = collisioncodegen_makeCylinder(radius, length);
  collisionObj.matlabCodegenIsDeleted = false;
  for (int i{0}; i < 3; i++) {
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
  obj = iobj_1.BodyInternal;
  for (int i{0}; i < 4; i++) {
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
      y[i + loop_ub] =
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
  std::copy(&y[0], &y[16], &collisionGeometry.LocalPose[0]);
  std::copy(&y[0], &y[16], &collisionGeometry.WorldPose[0]);
  b_obj = obj->CollisionsInternal;
  if (b_obj->Size < b_obj->MaxElements) {
    b_obj->Size++;
    b_obj->CollisionGeometries[static_cast<int>(b_obj->Size) - 1] =
        collisionGeometry;
  }
  lobj_0.matlabCodegenDestructor();
  //  Compute dynamics based on cylindrical geometry
  m_tmp = radius * radius;
  m = 3.1415926535897931 * m_tmp * length * rho;
  //  Mass
  //  Center of mass
  //  Inertia around x-axis
  //  Inertia around x and y axis
  Iz = length / 2.0;
  Iz = (0.25 * m * m_tmp + 0.083333333333333329 * m * (length * length)) +
       m * (Iz * Iz);
  //  Adjust inertia for the frame origin
  obj = iobj_1.BodyInternal;
  obj->MassInternal = m;
  mass = obj->MassInternal;
  com_idx_0 = obj->CenterOfMassInternal[0];
  com_idx_1 = obj->CenterOfMassInternal[1];
  com_idx_2 = obj->CenterOfMassInternal[2];
  for (int i{0}; i < 9; i++) {
    b_I[i] = obj->InertiaInternal[i];
  }
  sc[0] = 0.0;
  sc[3] = -com_idx_2;
  sc[6] = com_idx_1;
  sc[1] = com_idx_2;
  sc[4] = 0.0;
  sc[7] = -com_idx_0;
  sc[2] = -com_idx_1;
  sc[5] = com_idx_0;
  sc[8] = 0.0;
  for (int i{0}; i < 3; i++) {
    obj->SpatialInertia[6 * i] = b_I[3 * i];
    obj->SpatialInertia[6 * i + 1] = b_I[3 * i + 1];
    obj->SpatialInertia[6 * i + 2] = b_I[3 * i + 2];
  }
  for (int i{0}; i < 3; i++) {
    i1 = 6 * (i + 3);
    obj->SpatialInertia[i1] = mass * sc[3 * i];
    obj->SpatialInertia[i1 + 1] = mass * sc[3 * i + 1];
    obj->SpatialInertia[i1 + 2] = mass * sc[3 * i + 2];
  }
  for (int i{0}; i < 3; i++) {
    obj->SpatialInertia[6 * i + 3] = mass * sc[i];
    obj->SpatialInertia[6 * i + 4] = mass * sc[i + 3];
    obj->SpatialInertia[6 * i + 5] = mass * sc[i + 6];
  }
  for (int i{0}; i < 3; i++) {
    i1 = 6 * (i + 3);
    obj->SpatialInertia[i1 + 3] = mass * static_cast<double>(iv1[3 * i]);
    obj->SpatialInertia[i1 + 4] = mass * static_cast<double>(iv1[3 * i + 1]);
    obj->SpatialInertia[i1 + 5] = mass * static_cast<double>(iv1[3 * i + 2]);
  }
  obj = iobj_1.BodyInternal;
  obj->CenterOfMassInternal[0] = length / 2.0;
  obj->CenterOfMassInternal[1] = 0.0;
  obj->CenterOfMassInternal[2] = 0.0;
  mass = obj->MassInternal;
  com_idx_0 = obj->CenterOfMassInternal[0];
  com_idx_1 = obj->CenterOfMassInternal[1];
  com_idx_2 = obj->CenterOfMassInternal[2];
  for (int i{0}; i < 9; i++) {
    b_I[i] = obj->InertiaInternal[i];
  }
  sc[0] = 0.0;
  sc[3] = -com_idx_2;
  sc[6] = com_idx_1;
  sc[1] = com_idx_2;
  sc[4] = 0.0;
  sc[7] = -com_idx_0;
  sc[2] = -com_idx_1;
  sc[5] = com_idx_0;
  sc[8] = 0.0;
  for (int i{0}; i < 3; i++) {
    obj->SpatialInertia[6 * i] = b_I[3 * i];
    obj->SpatialInertia[6 * i + 1] = b_I[3 * i + 1];
    obj->SpatialInertia[6 * i + 2] = b_I[3 * i + 2];
  }
  for (int i{0}; i < 3; i++) {
    i1 = 6 * (i + 3);
    obj->SpatialInertia[i1] = mass * sc[3 * i];
    obj->SpatialInertia[i1 + 1] = mass * sc[3 * i + 1];
    obj->SpatialInertia[i1 + 2] = mass * sc[3 * i + 2];
  }
  for (int i{0}; i < 3; i++) {
    obj->SpatialInertia[6 * i + 3] = mass * sc[i];
    obj->SpatialInertia[6 * i + 4] = mass * sc[i + 3];
    obj->SpatialInertia[6 * i + 5] = mass * sc[i + 6];
  }
  for (int i{0}; i < 3; i++) {
    i1 = 6 * (i + 3);
    obj->SpatialInertia[i1 + 3] = mass * static_cast<double>(iv1[3 * i]);
    obj->SpatialInertia[i1 + 4] = mass * static_cast<double>(iv1[3 * i + 1]);
    obj->SpatialInertia[i1 + 5] = mass * static_cast<double>(iv1[3 * i + 2]);
  }
  double dv1[6];
  dv1[0] = 0.5 * m * m_tmp;
  dv1[1] = Iz;
  dv1[2] = Iz;
  dv1[3] = 0.0;
  dv1[4] = 0.0;
  dv1[5] = 0.0;
  iobj_1.set_Inertia(dv1);
  return body;
}

//
// Validate inputs
//
// Arguments    : double rho
//                double radius
//                const double arm_length[10]
//                const double joint_axes[30]
//                const double joint_angles[10]
//                const double config[10]
//                const double vel[10]
//                const double tq[10]
//                double acc_data[]
//                int acc_size[1]
// Return Type  : void
//
void forward_dynamics_robot_arm(double rho, double radius,
                                const double arm_length[10],
                                const double joint_axes[30],
                                const double joint_angles[10],
                                const double config[10], const double vel[10],
                                const double tq[10], double acc_data[],
                                int acc_size[1])
{
  static const char b_cv[6]{'l', 'i', 'n', 'k', '0', '1'};
  static const char b_cv1[6]{'l', 'i', 'n', 'k', '0', '2'};
  static const char cv2[6]{'l', 'i', 'n', 'k', '0', '3'};
  static const char cv3[6]{'l', 'i', 'n', 'k', '0', '4'};
  static const char cv4[6]{'l', 'i', 'n', 'k', '0', '5'};
  static const char cv5[6]{'l', 'i', 'n', 'k', '0', '6'};
  static const char cv6[6]{'l', 'i', 'n', 'k', '0', '7'};
  static const char cv7[6]{'l', 'i', 'n', 'k', '0', '8'};
  static const char cv8[6]{'l', 'i', 'n', 'k', '0', '9'};
  static const char cv9[6]{'l', 'i', 'n', 'k', '1', '0'};
  coder::rigidBody lobj_14[10];
  coder::rigidBody *bodies_idx_0;
  coder::rigidBody *bodies_idx_1;
  coder::rigidBody *bodies_idx_2;
  coder::rigidBody *bodies_idx_3;
  coder::rigidBody *bodies_idx_4;
  coder::rigidBody *bodies_idx_5;
  coder::rigidBody *bodies_idx_6;
  coder::rigidBody *bodies_idx_7;
  coder::rigidBody *bodies_idx_8;
  coder::rigidBody *bodies_idx_9;
  coder::rigidBodyJoint lobj_13[30];
  coder::rigidBodyJoint b_joint;
  coder::rigidBodyJoint c_joint;
  coder::rigidBodyJoint d_joint;
  coder::rigidBodyJoint e_joint;
  coder::rigidBodyJoint f_joint;
  coder::rigidBodyJoint g_joint;
  coder::rigidBodyJoint h_joint;
  coder::rigidBodyJoint i_joint;
  coder::rigidBodyJoint j_joint;
  coder::rigidBodyJoint joint;
  coder::rigidBodyTree robot;
  coder::robotics::manip::internal::CollisionSet lobj_11[20];
  coder::robotics::manip::internal::b_RigidBody lobj_12[10];
  double b_b[16];
  double dv[16];
  double R[9];
  double tempR[9];
  double b_joint_axes[4];
  double v[3];
  double b;
  double b_tempR_tmp;
  double c_tempR_tmp;
  double d_tempR_tmp;
  double tempR_tmp;
  int i6;
  int k;
  if (!isInitialized_forward_dynamics_robot_arm) {
    forward_dynamics_robot_arm_initialize();
  }
  for (int i{0}; i < 10; i++) {
    lobj_14[i]._pobj1[0].matlabCodegenIsDeleted = true;
    lobj_14[i]._pobj1[1].matlabCodegenIsDeleted = true;
  }
  for (int i{0}; i < 10; i++) {
    lobj_14[i]._pobj0._pobj1[0].matlabCodegenIsDeleted = true;
    lobj_14[i]._pobj0._pobj1[1].matlabCodegenIsDeleted = true;
  }
  for (int i{0}; i < 10; i++) {
    lobj_12[i]._pobj0.matlabCodegenIsDeleted = true;
  }
  for (int i{0}; i < 20; i++) {
    lobj_11[i].matlabCodegenIsDeleted = true;
  }
  robot._pobj0.matlabCodegenIsDeleted = true;
  for (int i{0}; i < 11; i++) {
    robot.TreeInternal._pobj2[i]._pobj0.matlabCodegenIsDeleted = true;
  }
  for (int i{0}; i < 10; i++) {
    robot.TreeInternal._pobj0[i].matlabCodegenIsDeleted = true;
  }
  robot.TreeInternal.Base._pobj0.matlabCodegenIsDeleted = true;
  for (int i{0}; i < 10; i++) {
    lobj_12[i].matlabCodegenIsDeleted = true;
  }
  for (int i{0}; i < 11; i++) {
    robot.TreeInternal._pobj2[i].matlabCodegenIsDeleted = true;
  }
  robot.TreeInternal.Base.matlabCodegenIsDeleted = true;
  robot.TreeInternal.matlabCodegenIsDeleted = true;
  robot.matlabCodegenIsDeleted = true;
  for (int i{0}; i < 10; i++) {
    lobj_14[i]._pobj3.matlabCodegenIsDeleted = true;
  }
  for (int i{0}; i < 10; i++) {
    lobj_14[i]._pobj0._pobj0.matlabCodegenIsDeleted = true;
  }
  for (int i{0}; i < 10; i++) {
    lobj_14[i]._pobj0.Base.matlabCodegenIsDeleted = true;
  }
  for (int i{0}; i < 10; i++) {
    lobj_14[i]._pobj0.matlabCodegenIsDeleted = true;
  }
  for (int i{0}; i < 10; i++) {
    lobj_14[i].matlabCodegenIsDeleted = true;
  }
  double e_tempR_tmp;
  double f_tempR_tmp;
  double g_tempR_tmp;
  double h_tempR_tmp;
  //  Create a robot model
  robot.init();
  //  Pre-allocate rigid bodies
  //  Configure the bodies
  //  Create joint and link
  joint.c_init();
  //  Set the joint's transformation
  b = 1.0 / std::sqrt((joint_axes[0] * joint_axes[0] +
                       joint_axes[10] * joint_axes[10]) +
                      joint_axes[20] * joint_axes[20]);
  v[0] = joint_axes[0] * b;
  v[1] = joint_axes[10] * b;
  v[2] = joint_axes[20] * b;
  b = v[0] * v[0] * 0.0 + 1.0;
  tempR[0] = b;
  tempR_tmp = v[0] * v[1] * 0.0;
  b_tempR_tmp = tempR_tmp - v[2] * 0.0;
  tempR[1] = b_tempR_tmp;
  c_tempR_tmp = v[0] * v[2] * 0.0;
  d_tempR_tmp = c_tempR_tmp + v[1] * 0.0;
  tempR[2] = d_tempR_tmp;
  tempR_tmp += v[2] * 0.0;
  tempR[3] = tempR_tmp;
  e_tempR_tmp = v[1] * v[1] * 0.0 + 1.0;
  tempR[4] = e_tempR_tmp;
  f_tempR_tmp = v[1] * v[2] * 0.0;
  g_tempR_tmp = f_tempR_tmp - v[0] * 0.0;
  tempR[5] = g_tempR_tmp;
  c_tempR_tmp -= v[1] * 0.0;
  tempR[6] = c_tempR_tmp;
  f_tempR_tmp += v[0] * 0.0;
  tempR[7] = f_tempR_tmp;
  h_tempR_tmp = v[2] * v[2] * 0.0 + 1.0;
  tempR[8] = h_tempR_tmp;
  R[0] = b;
  R[1] = b_tempR_tmp;
  R[2] = d_tempR_tmp;
  R[3] = tempR_tmp;
  R[4] = e_tempR_tmp;
  R[5] = g_tempR_tmp;
  R[6] = c_tempR_tmp;
  R[7] = f_tempR_tmp;
  R[8] = h_tempR_tmp;
  for (k = 0; k < 3; k++) {
    R[k] = tempR[3 * k];
    R[k + 3] = tempR[3 * k + 1];
    R[k + 6] = tempR[3 * k + 2];
  }
  std::memset(&b_b[0], 0, 16U * sizeof(double));
  for (int i{0}; i < 3; i++) {
    k = i << 2;
    b_b[k] = R[3 * i];
    b_b[k + 1] = R[3 * i + 1];
    b_b[k + 2] = R[3 * i + 2];
  }
  b_b[15] = 1.0;
  for (int i{0}; i < 4; i++) {
    signed char i1;
    signed char i2;
    signed char i3;
    signed char i4;
    i1 = iv[i];
    i2 = iv[i + 4];
    i3 = iv[i + 8];
    i4 = iv[i + 12];
    for (int i5{0}; i5 < 4; i5++) {
      k = i5 << 2;
      i6 = i + k;
      joint.JointToParentTransform[i6] = 0.0;
      joint.JointToParentTransform[i6] += static_cast<double>(i1) * b_b[k];
      joint.JointToParentTransform[i6] += static_cast<double>(i2) * b_b[k + 1];
      joint.JointToParentTransform[i6] += static_cast<double>(i3) * b_b[k + 2];
      joint.JointToParentTransform[i6] += static_cast<double>(i4) * b_b[k + 3];
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
  bodies_idx_0 = createBody(b_cv, joint, radius, arm_length[0], rho, lobj_13[0],
                            lobj_14[0]);
  //  Create joint and link
  b_joint.d_init();
  //  Set the joint's transformation
  v[0] = arm_length[0];
  v[1] = 0.0;
  v[2] = 0.0;
  coder::trvec2tform(v, b_b);
  b_joint_axes[0] = joint_axes[1];
  b_joint_axes[1] = joint_axes[11];
  b_joint_axes[2] = joint_axes[21];
  b_joint_axes[3] = joint_angles[1];
  coder::axang2tform(b_joint_axes, dv);
  for (int i{0}; i < 4; i++) {
    tempR_tmp = b_b[i];
    b_tempR_tmp = b_b[i + 4];
    c_tempR_tmp = b_b[i + 8];
    d_tempR_tmp = b_b[i + 12];
    for (int i5{0}; i5 < 4; i5++) {
      k = i5 << 2;
      i6 = i + k;
      b_joint.JointToParentTransform[i6] = 0.0;
      b_joint.JointToParentTransform[i6] += tempR_tmp * dv[k];
      b_joint.JointToParentTransform[i6] += b_tempR_tmp * dv[k + 1];
      b_joint.JointToParentTransform[i6] += c_tempR_tmp * dv[k + 2];
      b_joint.JointToParentTransform[i6] += d_tempR_tmp * dv[k + 3];
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
  bodies_idx_1 = createBody(b_cv1, b_joint, radius, arm_length[1], rho,
                            lobj_13[1], lobj_14[1]);
  //  Create joint and link
  c_joint.e_init();
  //  Set the joint's transformation
  b = arm_length[0] + arm_length[1];
  v[0] = b;
  v[1] = 0.0;
  v[2] = 0.0;
  coder::trvec2tform(v, b_b);
  b_joint_axes[0] = joint_axes[2];
  b_joint_axes[1] = joint_axes[12];
  b_joint_axes[2] = joint_axes[22];
  b_joint_axes[3] = joint_angles[2];
  coder::axang2tform(b_joint_axes, dv);
  for (int i{0}; i < 4; i++) {
    tempR_tmp = b_b[i];
    b_tempR_tmp = b_b[i + 4];
    c_tempR_tmp = b_b[i + 8];
    d_tempR_tmp = b_b[i + 12];
    for (int i5{0}; i5 < 4; i5++) {
      k = i5 << 2;
      i6 = i + k;
      c_joint.JointToParentTransform[i6] = 0.0;
      c_joint.JointToParentTransform[i6] += tempR_tmp * dv[k];
      c_joint.JointToParentTransform[i6] += b_tempR_tmp * dv[k + 1];
      c_joint.JointToParentTransform[i6] += c_tempR_tmp * dv[k + 2];
      c_joint.JointToParentTransform[i6] += d_tempR_tmp * dv[k + 3];
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
  bodies_idx_2 = createBody(cv2, c_joint, radius, arm_length[2], rho,
                            lobj_13[2], lobj_14[2]);
  //  Create joint and link
  d_joint.f_init();
  //  Set the joint's transformation
  b += arm_length[2];
  v[0] = b;
  v[1] = 0.0;
  v[2] = 0.0;
  coder::trvec2tform(v, b_b);
  b_joint_axes[0] = joint_axes[3];
  b_joint_axes[1] = joint_axes[13];
  b_joint_axes[2] = joint_axes[23];
  b_joint_axes[3] = joint_angles[3];
  coder::axang2tform(b_joint_axes, dv);
  for (int i{0}; i < 4; i++) {
    tempR_tmp = b_b[i];
    b_tempR_tmp = b_b[i + 4];
    c_tempR_tmp = b_b[i + 8];
    d_tempR_tmp = b_b[i + 12];
    for (int i5{0}; i5 < 4; i5++) {
      k = i5 << 2;
      i6 = i + k;
      d_joint.JointToParentTransform[i6] = 0.0;
      d_joint.JointToParentTransform[i6] += tempR_tmp * dv[k];
      d_joint.JointToParentTransform[i6] += b_tempR_tmp * dv[k + 1];
      d_joint.JointToParentTransform[i6] += c_tempR_tmp * dv[k + 2];
      d_joint.JointToParentTransform[i6] += d_tempR_tmp * dv[k + 3];
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
  bodies_idx_3 = createBody(cv3, d_joint, radius, arm_length[3], rho,
                            lobj_13[3], lobj_14[3]);
  //  Create joint and link
  e_joint.g_init();
  //  Set the joint's transformation
  b += arm_length[3];
  v[0] = b;
  v[1] = 0.0;
  v[2] = 0.0;
  coder::trvec2tform(v, b_b);
  b_joint_axes[0] = joint_axes[4];
  b_joint_axes[1] = joint_axes[14];
  b_joint_axes[2] = joint_axes[24];
  b_joint_axes[3] = joint_angles[4];
  coder::axang2tform(b_joint_axes, dv);
  for (int i{0}; i < 4; i++) {
    tempR_tmp = b_b[i];
    b_tempR_tmp = b_b[i + 4];
    c_tempR_tmp = b_b[i + 8];
    d_tempR_tmp = b_b[i + 12];
    for (int i5{0}; i5 < 4; i5++) {
      k = i5 << 2;
      i6 = i + k;
      e_joint.JointToParentTransform[i6] = 0.0;
      e_joint.JointToParentTransform[i6] += tempR_tmp * dv[k];
      e_joint.JointToParentTransform[i6] += b_tempR_tmp * dv[k + 1];
      e_joint.JointToParentTransform[i6] += c_tempR_tmp * dv[k + 2];
      e_joint.JointToParentTransform[i6] += d_tempR_tmp * dv[k + 3];
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
  bodies_idx_4 = createBody(cv4, e_joint, radius, arm_length[4], rho,
                            lobj_13[4], lobj_14[4]);
  //  Create joint and link
  f_joint.h_init();
  //  Set the joint's transformation
  v[0] = b + arm_length[4];
  v[1] = 0.0;
  v[2] = 0.0;
  coder::trvec2tform(v, b_b);
  b_joint_axes[0] = joint_axes[5];
  b_joint_axes[1] = joint_axes[15];
  b_joint_axes[2] = joint_axes[25];
  b_joint_axes[3] = joint_angles[5];
  coder::axang2tform(b_joint_axes, dv);
  for (int i{0}; i < 4; i++) {
    tempR_tmp = b_b[i];
    b_tempR_tmp = b_b[i + 4];
    c_tempR_tmp = b_b[i + 8];
    d_tempR_tmp = b_b[i + 12];
    for (int i5{0}; i5 < 4; i5++) {
      k = i5 << 2;
      i6 = i + k;
      f_joint.JointToParentTransform[i6] = 0.0;
      f_joint.JointToParentTransform[i6] += tempR_tmp * dv[k];
      f_joint.JointToParentTransform[i6] += b_tempR_tmp * dv[k + 1];
      f_joint.JointToParentTransform[i6] += c_tempR_tmp * dv[k + 2];
      f_joint.JointToParentTransform[i6] += d_tempR_tmp * dv[k + 3];
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
  bodies_idx_5 = createBody(cv5, f_joint, radius, arm_length[5], rho,
                            lobj_13[5], lobj_14[5]);
  //  Create joint and link
  g_joint.i_init();
  //  Set the joint's transformation
  b = arm_length[0];
  for (k = 0; k < 5; k++) {
    b += arm_length[k + 1];
  }
  v[0] = b;
  v[1] = 0.0;
  v[2] = 0.0;
  coder::trvec2tform(v, b_b);
  b_joint_axes[0] = joint_axes[6];
  b_joint_axes[1] = joint_axes[16];
  b_joint_axes[2] = joint_axes[26];
  b_joint_axes[3] = joint_angles[6];
  coder::axang2tform(b_joint_axes, dv);
  for (int i{0}; i < 4; i++) {
    tempR_tmp = b_b[i];
    b_tempR_tmp = b_b[i + 4];
    c_tempR_tmp = b_b[i + 8];
    d_tempR_tmp = b_b[i + 12];
    for (int i5{0}; i5 < 4; i5++) {
      k = i5 << 2;
      i6 = i + k;
      g_joint.JointToParentTransform[i6] = 0.0;
      g_joint.JointToParentTransform[i6] += tempR_tmp * dv[k];
      g_joint.JointToParentTransform[i6] += b_tempR_tmp * dv[k + 1];
      g_joint.JointToParentTransform[i6] += c_tempR_tmp * dv[k + 2];
      g_joint.JointToParentTransform[i6] += d_tempR_tmp * dv[k + 3];
    }
  }
  std::memset(&g_joint.ChildToJointTransform[0], 0, 16U * sizeof(double));
  g_joint.ChildToJointTransform[0] = 1.0;
  g_joint.ChildToJointTransform[5] = 1.0;
  g_joint.ChildToJointTransform[10] = 1.0;
  g_joint.ChildToJointTransform[15] = 1.0;
  //  Generate body name
  //  Pre-allocate with blanks
  //  Create and configure body
  bodies_idx_6 = createBody(cv6, g_joint, radius, arm_length[6], rho,
                            lobj_13[6], lobj_14[6]);
  //  Create joint and link
  h_joint.j_init();
  //  Set the joint's transformation
  b = arm_length[0];
  for (k = 0; k < 6; k++) {
    b += arm_length[k + 1];
  }
  v[0] = b;
  v[1] = 0.0;
  v[2] = 0.0;
  coder::trvec2tform(v, b_b);
  b_joint_axes[0] = joint_axes[7];
  b_joint_axes[1] = joint_axes[17];
  b_joint_axes[2] = joint_axes[27];
  b_joint_axes[3] = joint_angles[7];
  coder::axang2tform(b_joint_axes, dv);
  for (int i{0}; i < 4; i++) {
    tempR_tmp = b_b[i];
    b_tempR_tmp = b_b[i + 4];
    c_tempR_tmp = b_b[i + 8];
    d_tempR_tmp = b_b[i + 12];
    for (int i5{0}; i5 < 4; i5++) {
      k = i5 << 2;
      i6 = i + k;
      h_joint.JointToParentTransform[i6] = 0.0;
      h_joint.JointToParentTransform[i6] += tempR_tmp * dv[k];
      h_joint.JointToParentTransform[i6] += b_tempR_tmp * dv[k + 1];
      h_joint.JointToParentTransform[i6] += c_tempR_tmp * dv[k + 2];
      h_joint.JointToParentTransform[i6] += d_tempR_tmp * dv[k + 3];
    }
  }
  std::memset(&h_joint.ChildToJointTransform[0], 0, 16U * sizeof(double));
  h_joint.ChildToJointTransform[0] = 1.0;
  h_joint.ChildToJointTransform[5] = 1.0;
  h_joint.ChildToJointTransform[10] = 1.0;
  h_joint.ChildToJointTransform[15] = 1.0;
  //  Generate body name
  //  Pre-allocate with blanks
  //  Create and configure body
  bodies_idx_7 = createBody(cv7, h_joint, radius, arm_length[7], rho,
                            lobj_13[7], lobj_14[7]);
  //  Create joint and link
  i_joint.k_init();
  //  Set the joint's transformation
  b = arm_length[0];
  for (k = 0; k < 7; k++) {
    b += arm_length[k + 1];
  }
  v[0] = b;
  v[1] = 0.0;
  v[2] = 0.0;
  coder::trvec2tform(v, b_b);
  b_joint_axes[0] = joint_axes[8];
  b_joint_axes[1] = joint_axes[18];
  b_joint_axes[2] = joint_axes[28];
  b_joint_axes[3] = joint_angles[8];
  coder::axang2tform(b_joint_axes, dv);
  for (int i{0}; i < 4; i++) {
    tempR_tmp = b_b[i];
    b_tempR_tmp = b_b[i + 4];
    c_tempR_tmp = b_b[i + 8];
    d_tempR_tmp = b_b[i + 12];
    for (int i5{0}; i5 < 4; i5++) {
      k = i5 << 2;
      i6 = i + k;
      i_joint.JointToParentTransform[i6] = 0.0;
      i_joint.JointToParentTransform[i6] += tempR_tmp * dv[k];
      i_joint.JointToParentTransform[i6] += b_tempR_tmp * dv[k + 1];
      i_joint.JointToParentTransform[i6] += c_tempR_tmp * dv[k + 2];
      i_joint.JointToParentTransform[i6] += d_tempR_tmp * dv[k + 3];
    }
  }
  std::memset(&i_joint.ChildToJointTransform[0], 0, 16U * sizeof(double));
  i_joint.ChildToJointTransform[0] = 1.0;
  i_joint.ChildToJointTransform[5] = 1.0;
  i_joint.ChildToJointTransform[10] = 1.0;
  i_joint.ChildToJointTransform[15] = 1.0;
  //  Generate body name
  //  Pre-allocate with blanks
  //  Create and configure body
  bodies_idx_8 = createBody(cv8, i_joint, radius, arm_length[8], rho,
                            lobj_13[8], lobj_14[8]);
  //  Create joint and link
  j_joint.l_init();
  //  Set the joint's transformation
  b = arm_length[0];
  for (k = 0; k < 8; k++) {
    b += arm_length[k + 1];
  }
  v[0] = b;
  v[1] = 0.0;
  v[2] = 0.0;
  coder::trvec2tform(v, b_b);
  b_joint_axes[0] = joint_axes[9];
  b_joint_axes[1] = joint_axes[19];
  b_joint_axes[2] = joint_axes[29];
  b_joint_axes[3] = joint_angles[9];
  coder::axang2tform(b_joint_axes, dv);
  for (int i{0}; i < 4; i++) {
    tempR_tmp = b_b[i];
    b_tempR_tmp = b_b[i + 4];
    c_tempR_tmp = b_b[i + 8];
    d_tempR_tmp = b_b[i + 12];
    for (int i5{0}; i5 < 4; i5++) {
      k = i5 << 2;
      i6 = i + k;
      j_joint.JointToParentTransform[i6] = 0.0;
      j_joint.JointToParentTransform[i6] += tempR_tmp * dv[k];
      j_joint.JointToParentTransform[i6] += b_tempR_tmp * dv[k + 1];
      j_joint.JointToParentTransform[i6] += c_tempR_tmp * dv[k + 2];
      j_joint.JointToParentTransform[i6] += d_tempR_tmp * dv[k + 3];
    }
  }
  std::memset(&j_joint.ChildToJointTransform[0], 0, 16U * sizeof(double));
  j_joint.ChildToJointTransform[0] = 1.0;
  j_joint.ChildToJointTransform[5] = 1.0;
  j_joint.ChildToJointTransform[10] = 1.0;
  j_joint.ChildToJointTransform[15] = 1.0;
  //  Generate body name
  //  Pre-allocate with blanks
  //  Create and configure body
  bodies_idx_9 = createBody(cv9, j_joint, radius, arm_length[9], rho,
                            lobj_13[9], lobj_14[9]);
  //  Add bodies to the robot model
  robot.addBody(bodies_idx_0, lobj_11[0], lobj_13[10], lobj_12[0]);
  //  Pre-allocate with blanks
  robot.addBody(bodies_idx_1, b_cv, lobj_11[2], lobj_13[12], lobj_12[1]);
  robot.addBody(bodies_idx_2, b_cv1, lobj_11[4], lobj_13[14], lobj_12[2]);
  robot.addBody(bodies_idx_3, cv2, lobj_11[6], lobj_13[16], lobj_12[3]);
  robot.addBody(bodies_idx_4, cv3, lobj_11[8], lobj_13[18], lobj_12[4]);
  robot.addBody(bodies_idx_5, cv4, lobj_11[10], lobj_13[20], lobj_12[5]);
  robot.addBody(bodies_idx_6, cv5, lobj_11[12], lobj_13[22], lobj_12[6]);
  robot.addBody(bodies_idx_7, cv6, lobj_11[14], lobj_13[24], lobj_12[7]);
  robot.addBody(bodies_idx_8, cv7, lobj_11[16], lobj_13[26], lobj_12[8]);
  robot.addBody(bodies_idx_9, cv8, lobj_11[18], lobj_13[28], lobj_12[9]);
  robot.TreeInternal.Gravity[0] = 0.0;
  robot.TreeInternal.Gravity[1] = 0.0;
  robot.TreeInternal.Gravity[2] = -9.81;
  //  Perform forward dynamics
  acc_size[0] = robot.forwardDynamics(config, vel, tq, acc_data);
  for (int i{0}; i < 10; i++) {
    lobj_14[i].matlabCodegenDestructor();
  }
  for (int i{0}; i < 10; i++) {
    lobj_14[i]._pobj0.matlabCodegenDestructor();
  }
  for (int i{0}; i < 10; i++) {
    lobj_14[i]._pobj0.Base.matlabCodegenDestructor();
  }
  for (int i{0}; i < 10; i++) {
    lobj_14[i]._pobj0._pobj0.matlabCodegenDestructor();
  }
  for (int i{0}; i < 10; i++) {
    lobj_14[i]._pobj3.matlabCodegenDestructor();
  }
  robot.matlabCodegenDestructor();
  robot.TreeInternal.matlabCodegenDestructor();
  robot.TreeInternal.Base.matlabCodegenDestructor();
  for (int i{0}; i < 11; i++) {
    robot.TreeInternal._pobj2[i].matlabCodegenDestructor();
  }
  for (int i{0}; i < 10; i++) {
    lobj_12[i].matlabCodegenDestructor();
  }
  robot.TreeInternal.Base._pobj0.matlabCodegenDestructor();
  for (int i{0}; i < 10; i++) {
    robot.TreeInternal._pobj0[i].matlabCodegenDestructor();
  }
  for (int i{0}; i < 11; i++) {
    robot.TreeInternal._pobj2[i]._pobj0.matlabCodegenDestructor();
  }
  robot._pobj0.matlabCodegenDestructor();
  for (int i{0}; i < 20; i++) {
    lobj_11[i].matlabCodegenDestructor();
  }
  for (int i{0}; i < 10; i++) {
    lobj_12[i]._pobj0.matlabCodegenDestructor();
  }
  for (int i{0}; i < 10; i++) {
    lobj_14[i]._pobj0._pobj1[0].matlabCodegenDestructor();
    lobj_14[i]._pobj0._pobj1[1].matlabCodegenDestructor();
  }
  for (int i{0}; i < 10; i++) {
    lobj_14[i]._pobj1[0].matlabCodegenDestructor();
    lobj_14[i]._pobj1[1].matlabCodegenDestructor();
  }
}

//
// File trailer for forward_dynamics_robot_arm.cpp
//
// [EOF]
//
