//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: forward_dynamics_robot_4arm.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 05-Feb-2024 13:57:11
//

// Include Files
#include "forward_dynamics_robot_4arm.h"
#include "CollisionGeometry.h"
#include "CollisionSet.h"
#include "RigidBody.h"
#include "RigidBodyTree1.h"
#include "axang2tform.h"
#include "collisionCylinder.h"
#include "forward_dynamics_robot_4arm_data.h"
#include "forward_dynamics_robot_4arm_initialize.h"
#include "rand.h"
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
          if (switch_expression[loop_ub] != cv[loop_ub]) {
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
    iobj_1._pobj0._pobj0.NameInternal[i] = cv1[i];
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
//                const double arm_length[4]
//                const double joint_axes[12]
//                const double joint_angles[10]
//                const double config[4]
//                const double vel[4]
//                const double tq[4]
//                double acc_data[]
//                int acc_size[1]
// Return Type  : void
//
void forward_dynamics_robot_4arm(double rho, double radius,
                                 const double arm_length[4],
                                 const double joint_axes[12],
                                 const double joint_angles[10],
                                 const double config[4], const double vel[4],
                                 const double tq[4], double acc_data[],
                                 int acc_size[1])
{
  static const char b[8]{'r', 'e', 'v', 'o', 'l', 'u', 't', 'e'};
  static const char b_cv[8]{'r', 'e', 'v', 'o', 'l', 'u', 't', 'e'};
  static const char b_cv1[6]{'l', 'i', 'n', 'k', '0', '1'};
  static const signed char b_iv[6]{0, 0, 1, 0, 0, 0};
  static const signed char b_iv1[6]{0, 0, 0, 0, 0, 1};
  static const char cv2[6]{'l', 'i', 'n', 'k', '0', '2'};
  static const char cv3[6]{'l', 'i', 'n', 'k', '0', '3'};
  static const char cv4[6]{'l', 'i', 'n', 'k', '0', '4'};
  coder::rigidBody lobj_8[4];
  coder::rigidBody *bodies_idx_0;
  coder::rigidBody *bodies_idx_1;
  coder::rigidBody *bodies_idx_2;
  coder::rigidBody *bodies_idx_3;
  coder::rigidBodyJoint lobj_7[12];
  coder::rigidBodyJoint b_joint;
  coder::rigidBodyJoint c_joint;
  coder::rigidBodyJoint d_joint;
  coder::rigidBodyJoint joint;
  coder::rigidBodyTree robot;
  coder::robotics::manip::internal::CollisionSet lobj_5[8];
  coder::robotics::manip::internal::b_RigidBody lobj_6[4];
  double a[16];
  double b_b[16];
  double poslim_data[12];
  double R[9];
  double tempR[9];
  double b_joint_axes[4];
  double b_tempR_tmp;
  double tempR_tmp;
  double v_idx_0;
  double v_idx_1;
  double v_idx_2;
  int exitg1;
  int jcol;
  int kstr;
  signed char msubspace_data[36];
  boolean_T b_bool;
  if (!isInitialized_forward_dynamics_robot_4arm) {
    forward_dynamics_robot_4arm_initialize();
  }
  for (int i{0}; i < 4; i++) {
    lobj_8[i]._pobj1[0].matlabCodegenIsDeleted = true;
    lobj_8[i]._pobj1[1].matlabCodegenIsDeleted = true;
  }
  for (int i{0}; i < 4; i++) {
    lobj_8[i]._pobj0._pobj1[0].matlabCodegenIsDeleted = true;
    lobj_8[i]._pobj0._pobj1[1].matlabCodegenIsDeleted = true;
  }
  lobj_6[0]._pobj0.matlabCodegenIsDeleted = true;
  lobj_6[1]._pobj0.matlabCodegenIsDeleted = true;
  lobj_6[2]._pobj0.matlabCodegenIsDeleted = true;
  lobj_6[3]._pobj0.matlabCodegenIsDeleted = true;
  for (int i{0}; i < 8; i++) {
    lobj_5[i].matlabCodegenIsDeleted = true;
  }
  robot._pobj0.matlabCodegenIsDeleted = true;
  for (int i{0}; i < 5; i++) {
    robot.TreeInternal._pobj2[i]._pobj0.matlabCodegenIsDeleted = true;
  }
  robot.TreeInternal._pobj0[0].matlabCodegenIsDeleted = true;
  robot.TreeInternal._pobj0[1].matlabCodegenIsDeleted = true;
  robot.TreeInternal._pobj0[2].matlabCodegenIsDeleted = true;
  robot.TreeInternal._pobj0[3].matlabCodegenIsDeleted = true;
  robot.TreeInternal.Base._pobj0.matlabCodegenIsDeleted = true;
  lobj_6[0].matlabCodegenIsDeleted = true;
  lobj_6[1].matlabCodegenIsDeleted = true;
  lobj_6[2].matlabCodegenIsDeleted = true;
  lobj_6[3].matlabCodegenIsDeleted = true;
  for (int i{0}; i < 5; i++) {
    robot.TreeInternal._pobj2[i].matlabCodegenIsDeleted = true;
  }
  robot.TreeInternal.Base.matlabCodegenIsDeleted = true;
  robot.TreeInternal.matlabCodegenIsDeleted = true;
  robot.matlabCodegenIsDeleted = true;
  lobj_8[0]._pobj3.matlabCodegenIsDeleted = true;
  lobj_8[1]._pobj3.matlabCodegenIsDeleted = true;
  lobj_8[2]._pobj3.matlabCodegenIsDeleted = true;
  lobj_8[3]._pobj3.matlabCodegenIsDeleted = true;
  lobj_8[0]._pobj0._pobj0.matlabCodegenIsDeleted = true;
  lobj_8[1]._pobj0._pobj0.matlabCodegenIsDeleted = true;
  lobj_8[2]._pobj0._pobj0.matlabCodegenIsDeleted = true;
  lobj_8[3]._pobj0._pobj0.matlabCodegenIsDeleted = true;
  lobj_8[0]._pobj0.Base.matlabCodegenIsDeleted = true;
  lobj_8[1]._pobj0.Base.matlabCodegenIsDeleted = true;
  lobj_8[2]._pobj0.Base.matlabCodegenIsDeleted = true;
  lobj_8[3]._pobj0.Base.matlabCodegenIsDeleted = true;
  lobj_8[0]._pobj0.matlabCodegenIsDeleted = true;
  lobj_8[1]._pobj0.matlabCodegenIsDeleted = true;
  lobj_8[2]._pobj0.matlabCodegenIsDeleted = true;
  lobj_8[3]._pobj0.matlabCodegenIsDeleted = true;
  lobj_8[0].matlabCodegenIsDeleted = true;
  lobj_8[1].matlabCodegenIsDeleted = true;
  lobj_8[2].matlabCodegenIsDeleted = true;
  lobj_8[3].matlabCodegenIsDeleted = true;
  //  Create a robot model
  robot.init();
  //  Pre-allocate rigid bodies
  //  Configure the bodies
  //  Create joint and link
  joint.InTree = false;
  joint.NameInternal.set_size(1, 4);
  joint.NameInternal[0] = 'j';
  joint.NameInternal[1] = 'n';
  joint.NameInternal[2] = 't';
  joint.NameInternal[3] = '1';
  joint.Type.set_size(1, 8);
  for (int i{0}; i < 8; i++) {
    joint.Type[i] = b[i];
  }
  b_bool = false;
  if (joint.Type.size(1) == 8) {
    kstr = 0;
    do {
      exitg1 = 0;
      if (kstr < 8) {
        if (joint.Type[kstr] != b_cv[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  if (b_bool) {
    kstr = 0;
  } else {
    b_bool = false;
    if (joint.Type.size(1) == 9) {
      kstr = 0;
      do {
        exitg1 = 0;
        if (kstr < 9) {
          if (joint.Type[kstr] != cv[kstr]) {
            exitg1 = 1;
          } else {
            kstr++;
          }
        } else {
          b_bool = true;
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }
    if (b_bool) {
      kstr = 1;
    } else {
      kstr = -1;
    }
  }
  switch (kstr) {
  case 0:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = b_iv[i];
    }
    poslim_data[0] = -3.1415926535897931;
    poslim_data[1] = 3.1415926535897931;
    joint.VelocityNumber = 1.0;
    joint.PositionNumber = 1.0;
    joint.JointAxisInternal[0] = 0.0;
    joint.JointAxisInternal[1] = 0.0;
    joint.JointAxisInternal[2] = 1.0;
    break;
  case 1:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = b_iv1[i];
    }
    poslim_data[0] = -0.5;
    poslim_data[1] = 0.5;
    joint.VelocityNumber = 1.0;
    joint.PositionNumber = 1.0;
    joint.JointAxisInternal[0] = 0.0;
    joint.JointAxisInternal[1] = 0.0;
    joint.JointAxisInternal[2] = 1.0;
    break;
  default:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = 0;
    }
    poslim_data[0] = 0.0;
    poslim_data[1] = 0.0;
    joint.VelocityNumber = 0.0;
    joint.PositionNumber = 0.0;
    joint.JointAxisInternal[0] = 0.0;
    joint.JointAxisInternal[1] = 0.0;
    joint.JointAxisInternal[2] = 0.0;
    break;
  }
  joint.MotionSubspace.set_size(6, 1);
  for (int i{0}; i < 6; i++) {
    joint.MotionSubspace[i] = msubspace_data[i];
  }
  joint.PositionLimitsInternal.set_size(1, 2);
  for (int i{0}; i < 2; i++) {
    joint.PositionLimitsInternal[i] = poslim_data[i];
  }
  double c_tempR_tmp;
  double d_tempR_tmp;
  double e_tempR_tmp;
  double f_tempR_tmp;
  double g_tempR_tmp;
  double h_tempR_tmp;
  joint.HomePositionInternal.set_size(1);
  joint.HomePositionInternal[0] = 0.0;
  //  Set the joint's transformation
  v_idx_2 = 1.0 / std::sqrt((joint_axes[0] * joint_axes[0] +
                             joint_axes[4] * joint_axes[4]) +
                            joint_axes[8] * joint_axes[8]);
  v_idx_0 = joint_axes[0] * v_idx_2;
  v_idx_1 = joint_axes[4] * v_idx_2;
  v_idx_2 *= joint_axes[8];
  tempR_tmp = v_idx_0 * v_idx_0 * 0.0 + 1.0;
  tempR[0] = tempR_tmp;
  b_tempR_tmp = v_idx_0 * v_idx_1 * 0.0;
  c_tempR_tmp = b_tempR_tmp - v_idx_2 * 0.0;
  tempR[1] = c_tempR_tmp;
  d_tempR_tmp = v_idx_0 * v_idx_2 * 0.0;
  e_tempR_tmp = d_tempR_tmp + v_idx_1 * 0.0;
  tempR[2] = e_tempR_tmp;
  b_tempR_tmp += v_idx_2 * 0.0;
  tempR[3] = b_tempR_tmp;
  f_tempR_tmp = v_idx_1 * v_idx_1 * 0.0 + 1.0;
  tempR[4] = f_tempR_tmp;
  g_tempR_tmp = v_idx_1 * v_idx_2 * 0.0;
  h_tempR_tmp = g_tempR_tmp - v_idx_0 * 0.0;
  tempR[5] = h_tempR_tmp;
  d_tempR_tmp -= v_idx_1 * 0.0;
  tempR[6] = d_tempR_tmp;
  g_tempR_tmp += v_idx_0 * 0.0;
  tempR[7] = g_tempR_tmp;
  v_idx_2 = v_idx_2 * v_idx_2 * 0.0 + 1.0;
  tempR[8] = v_idx_2;
  R[0] = tempR_tmp;
  R[1] = c_tempR_tmp;
  R[2] = e_tempR_tmp;
  R[3] = b_tempR_tmp;
  R[4] = f_tempR_tmp;
  R[5] = h_tempR_tmp;
  R[6] = d_tempR_tmp;
  R[7] = g_tempR_tmp;
  R[8] = v_idx_2;
  for (kstr = 0; kstr < 3; kstr++) {
    R[kstr] = tempR[3 * kstr];
    R[kstr + 3] = tempR[3 * kstr + 1];
    R[kstr + 6] = tempR[3 * kstr + 2];
  }
  std::memset(&b_b[0], 0, 16U * sizeof(double));
  for (int i{0}; i < 3; i++) {
    kstr = i << 2;
    b_b[kstr] = R[3 * i];
    b_b[kstr + 1] = R[3 * i + 1];
    b_b[kstr + 2] = R[3 * i + 2];
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
      kstr = i5 << 2;
      jcol = i + kstr;
      joint.JointToParentTransform[jcol] = 0.0;
      joint.JointToParentTransform[jcol] += static_cast<double>(i1) * b_b[kstr];
      joint.JointToParentTransform[jcol] +=
          static_cast<double>(i2) * b_b[kstr + 1];
      joint.JointToParentTransform[jcol] +=
          static_cast<double>(i3) * b_b[kstr + 2];
      joint.JointToParentTransform[jcol] +=
          static_cast<double>(i4) * b_b[kstr + 3];
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
  bodies_idx_0 = createBody(b_cv1, joint, radius, arm_length[0], rho, lobj_7[0],
                            lobj_8[0]);
  //  Create joint and link
  b_joint.c_init();
  //  Set the joint's transformation
  std::memset(&b_b[0], 0, 16U * sizeof(double));
  b_b[0] = 1.0;
  b_b[5] = 1.0;
  b_b[10] = 1.0;
  b_b[15] = 1.0;
  for (jcol = 0; jcol < 4; jcol++) {
    kstr = jcol << 2;
    a[kstr] = b_b[kstr];
    a[kstr + 1] = b_b[kstr + 1];
    a[kstr + 2] = b_b[kstr + 2];
    a[kstr + 3] = b_b[kstr + 3];
  }
  a[12] = arm_length[0];
  a[13] = 0.0;
  a[14] = 0.0;
  b_joint_axes[0] = joint_axes[1];
  b_joint_axes[1] = joint_axes[5];
  b_joint_axes[2] = joint_axes[9];
  b_joint_axes[3] = joint_angles[1];
  coder::axang2tform(b_joint_axes, b_b);
  for (int i{0}; i < 4; i++) {
    v_idx_2 = a[i];
    v_idx_0 = a[i + 4];
    v_idx_1 = a[i + 8];
    tempR_tmp = a[i + 12];
    for (int i5{0}; i5 < 4; i5++) {
      kstr = i5 << 2;
      jcol = i + kstr;
      b_joint.JointToParentTransform[jcol] = 0.0;
      b_joint.JointToParentTransform[jcol] += v_idx_2 * b_b[kstr];
      b_joint.JointToParentTransform[jcol] += v_idx_0 * b_b[kstr + 1];
      b_joint.JointToParentTransform[jcol] += v_idx_1 * b_b[kstr + 2];
      b_joint.JointToParentTransform[jcol] += tempR_tmp * b_b[kstr + 3];
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
  bodies_idx_1 = createBody(cv2, b_joint, radius, arm_length[1], rho, lobj_7[1],
                            lobj_8[1]);
  //  Create joint and link
  c_joint.d_init();
  //  Set the joint's transformation
  std::memset(&b_b[0], 0, 16U * sizeof(double));
  b_b[0] = 1.0;
  b_b[5] = 1.0;
  b_b[10] = 1.0;
  b_b[15] = 1.0;
  for (jcol = 0; jcol < 4; jcol++) {
    kstr = jcol << 2;
    a[kstr] = b_b[kstr];
    a[kstr + 1] = b_b[kstr + 1];
    a[kstr + 2] = b_b[kstr + 2];
    a[kstr + 3] = b_b[kstr + 3];
  }
  b_tempR_tmp = arm_length[0] + arm_length[1];
  a[12] = b_tempR_tmp;
  a[13] = 0.0;
  a[14] = 0.0;
  b_joint_axes[0] = joint_axes[2];
  b_joint_axes[1] = joint_axes[6];
  b_joint_axes[2] = joint_axes[10];
  b_joint_axes[3] = joint_angles[2];
  coder::axang2tform(b_joint_axes, b_b);
  for (int i{0}; i < 4; i++) {
    v_idx_2 = a[i];
    v_idx_0 = a[i + 4];
    v_idx_1 = a[i + 8];
    tempR_tmp = a[i + 12];
    for (int i5{0}; i5 < 4; i5++) {
      kstr = i5 << 2;
      jcol = i + kstr;
      c_joint.JointToParentTransform[jcol] = 0.0;
      c_joint.JointToParentTransform[jcol] += v_idx_2 * b_b[kstr];
      c_joint.JointToParentTransform[jcol] += v_idx_0 * b_b[kstr + 1];
      c_joint.JointToParentTransform[jcol] += v_idx_1 * b_b[kstr + 2];
      c_joint.JointToParentTransform[jcol] += tempR_tmp * b_b[kstr + 3];
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
  bodies_idx_2 = createBody(cv3, c_joint, radius, arm_length[2], rho, lobj_7[2],
                            lobj_8[2]);
  //  Create joint and link
  d_joint.e_init();
  //  Set the joint's transformation
  std::memset(&b_b[0], 0, 16U * sizeof(double));
  b_b[0] = 1.0;
  b_b[5] = 1.0;
  b_b[10] = 1.0;
  b_b[15] = 1.0;
  for (jcol = 0; jcol < 4; jcol++) {
    kstr = jcol << 2;
    a[kstr] = b_b[kstr];
    a[kstr + 1] = b_b[kstr + 1];
    a[kstr + 2] = b_b[kstr + 2];
    a[kstr + 3] = b_b[kstr + 3];
  }
  a[12] = b_tempR_tmp + arm_length[2];
  a[13] = 0.0;
  a[14] = 0.0;
  b_joint_axes[0] = joint_axes[3];
  b_joint_axes[1] = joint_axes[7];
  b_joint_axes[2] = joint_axes[11];
  b_joint_axes[3] = joint_angles[3];
  coder::axang2tform(b_joint_axes, b_b);
  for (int i{0}; i < 4; i++) {
    v_idx_2 = a[i];
    v_idx_0 = a[i + 4];
    v_idx_1 = a[i + 8];
    tempR_tmp = a[i + 12];
    for (int i5{0}; i5 < 4; i5++) {
      kstr = i5 << 2;
      jcol = i + kstr;
      d_joint.JointToParentTransform[jcol] = 0.0;
      d_joint.JointToParentTransform[jcol] += v_idx_2 * b_b[kstr];
      d_joint.JointToParentTransform[jcol] += v_idx_0 * b_b[kstr + 1];
      d_joint.JointToParentTransform[jcol] += v_idx_1 * b_b[kstr + 2];
      d_joint.JointToParentTransform[jcol] += tempR_tmp * b_b[kstr + 3];
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
  bodies_idx_3 = createBody(cv4, d_joint, radius, arm_length[3], rho, lobj_7[3],
                            lobj_8[3]);
  //  Add bodies to the robot model
  robot.addBody(bodies_idx_0, lobj_5[0], lobj_7[4], lobj_6[0]);
  //  Pre-allocate with blanks
  robot.addBody(bodies_idx_1, b_cv1, lobj_5[2], lobj_7[6], lobj_6[1]);
  robot.addBody(bodies_idx_2, cv2, lobj_5[4], lobj_7[8], lobj_6[2]);
  robot.addBody(bodies_idx_3, cv3, lobj_5[6], lobj_7[10], lobj_6[3]);
  robot.TreeInternal.Gravity[0] = 0.0;
  robot.TreeInternal.Gravity[1] = 0.0;
  robot.TreeInternal.Gravity[2] = -9.81;
  //  Perform forward dynamics
  acc_size[0] = robot.forwardDynamics(config, vel, tq, acc_data);
  lobj_8[0].matlabCodegenDestructor();
  lobj_8[1].matlabCodegenDestructor();
  lobj_8[2].matlabCodegenDestructor();
  lobj_8[3].matlabCodegenDestructor();
  lobj_8[0]._pobj0.matlabCodegenDestructor();
  lobj_8[1]._pobj0.matlabCodegenDestructor();
  lobj_8[2]._pobj0.matlabCodegenDestructor();
  lobj_8[3]._pobj0.matlabCodegenDestructor();
  lobj_8[0]._pobj0.Base.matlabCodegenDestructor();
  lobj_8[1]._pobj0.Base.matlabCodegenDestructor();
  lobj_8[2]._pobj0.Base.matlabCodegenDestructor();
  lobj_8[3]._pobj0.Base.matlabCodegenDestructor();
  lobj_8[0]._pobj0._pobj0.matlabCodegenDestructor();
  lobj_8[1]._pobj0._pobj0.matlabCodegenDestructor();
  lobj_8[2]._pobj0._pobj0.matlabCodegenDestructor();
  lobj_8[3]._pobj0._pobj0.matlabCodegenDestructor();
  lobj_8[0]._pobj3.matlabCodegenDestructor();
  lobj_8[1]._pobj3.matlabCodegenDestructor();
  lobj_8[2]._pobj3.matlabCodegenDestructor();
  lobj_8[3]._pobj3.matlabCodegenDestructor();
  robot.matlabCodegenDestructor();
  robot.TreeInternal.matlabCodegenDestructor();
  robot.TreeInternal.Base.matlabCodegenDestructor();
  for (int i{0}; i < 5; i++) {
    robot.TreeInternal._pobj2[i].matlabCodegenDestructor();
  }
  lobj_6[0].matlabCodegenDestructor();
  lobj_6[1].matlabCodegenDestructor();
  lobj_6[2].matlabCodegenDestructor();
  lobj_6[3].matlabCodegenDestructor();
  robot.TreeInternal.Base._pobj0.matlabCodegenDestructor();
  robot.TreeInternal._pobj0[0].matlabCodegenDestructor();
  robot.TreeInternal._pobj0[1].matlabCodegenDestructor();
  robot.TreeInternal._pobj0[2].matlabCodegenDestructor();
  robot.TreeInternal._pobj0[3].matlabCodegenDestructor();
  for (int i{0}; i < 5; i++) {
    robot.TreeInternal._pobj2[i]._pobj0.matlabCodegenDestructor();
  }
  robot._pobj0.matlabCodegenDestructor();
  for (int i{0}; i < 8; i++) {
    lobj_5[i].matlabCodegenDestructor();
  }
  lobj_6[0]._pobj0.matlabCodegenDestructor();
  lobj_6[1]._pobj0.matlabCodegenDestructor();
  lobj_6[2]._pobj0.matlabCodegenDestructor();
  lobj_6[3]._pobj0.matlabCodegenDestructor();
  for (int i{0}; i < 4; i++) {
    lobj_8[i]._pobj0._pobj1[0].matlabCodegenDestructor();
    lobj_8[i]._pobj0._pobj1[1].matlabCodegenDestructor();
  }
  for (int i{0}; i < 4; i++) {
    lobj_8[i]._pobj1[0].matlabCodegenDestructor();
    lobj_8[i]._pobj1[1].matlabCodegenDestructor();
  }
}

//
// File trailer for forward_dynamics_robot_4arm.cpp
//
// [EOF]
//
