//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: RigidBody.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 02-Feb-2024 13:34:01
//

// Include Files
#include "RigidBody.h"
#include "CollisionGeometry.h"
#include "CollisionSet.h"
#include "forward_dynamics_robot_arm_data.h"
#include "rigidBodyJoint.h"
#include "rt_nonfinite.h"
#include "string1.h"
#include "coder_array.h"
#include "collisioncodegen_api.hpp"
#include <algorithm>

// Function Definitions
//
// Arguments    : CollisionSet &iobj_0
//                rigidBodyJoint &iobj_1
// Return Type  : b_RigidBody *
//
namespace coder {
namespace robotics {
namespace manip {
namespace internal {
b_RigidBody *b_RigidBody::b_init(CollisionSet &iobj_0, rigidBodyJoint &iobj_1)
{
  static const char jname[14]{'d', 'u', 'm', 'm', 'y', 'b', 'o',
                              'd', 'y', '5', '_', 'j', 'n', 't'};
  static const char bname[10]{'d', 'u', 'm', 'm', 'y', 'b', 'o', 'd', 'y', '5'};
  static const char b_cv1[8]{'r', 'e', 'v', 'o', 'l', 'u', 't', 'e'};
  static const signed char b_iv[6]{0, 0, 1, 0, 0, 0};
  static const signed char b_iv1[6]{0, 0, 0, 0, 0, 1};
  static const char b_cv[5]{'f', 'i', 'x', 'e', 'd'};
  b_RigidBody *obj;
  array<char, 2U> switch_expression;
  double poslim_data[12];
  int exitg1;
  int loop_ub;
  signed char msubspace_data[36];
  boolean_T b_bool;
  obj = this;
  obj->NameInternal.set_size(1, 10);
  for (int i{0}; i < 10; i++) {
    obj->NameInternal[i] = bname[i];
  }
  iobj_1.InTree = false;
  for (int i{0}; i < 16; i++) {
    iobj_1.JointToParentTransform[i] = iv[i];
  }
  for (int i{0}; i < 16; i++) {
    iobj_1.ChildToJointTransform[i] = iv[i];
  }
  iobj_1.NameInternal.set_size(1, 14);
  for (int i{0}; i < 14; i++) {
    iobj_1.NameInternal[i] = jname[i];
  }
  iobj_1.Type.set_size(1, 5);
  for (int i{0}; i < 5; i++) {
    iobj_1.Type[i] = b_cv[i];
  }
  switch_expression.set_size(1, iobj_1.Type.size(1));
  loop_ub = iobj_1.Type.size(1);
  for (int i{0}; i < loop_ub; i++) {
    switch_expression[i] = iobj_1.Type[i];
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
    iobj_1.VelocityNumber = 1.0;
    iobj_1.PositionNumber = 1.0;
    iobj_1.JointAxisInternal[0] = 0.0;
    iobj_1.JointAxisInternal[1] = 0.0;
    iobj_1.JointAxisInternal[2] = 1.0;
    break;
  case 1:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = b_iv1[i];
    }
    poslim_data[0] = -0.5;
    poslim_data[1] = 0.5;
    iobj_1.VelocityNumber = 1.0;
    iobj_1.PositionNumber = 1.0;
    iobj_1.JointAxisInternal[0] = 0.0;
    iobj_1.JointAxisInternal[1] = 0.0;
    iobj_1.JointAxisInternal[2] = 1.0;
    break;
  default:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = 0;
    }
    poslim_data[0] = 0.0;
    poslim_data[1] = 0.0;
    iobj_1.VelocityNumber = 0.0;
    iobj_1.PositionNumber = 0.0;
    iobj_1.JointAxisInternal[0] = 0.0;
    iobj_1.JointAxisInternal[1] = 0.0;
    iobj_1.JointAxisInternal[2] = 0.0;
    break;
  }
  iobj_1.MotionSubspace.set_size(6, 1);
  for (int i{0}; i < 6; i++) {
    iobj_1.MotionSubspace[i] = msubspace_data[i];
  }
  iobj_1.PositionLimitsInternal.set_size(1, 2);
  for (int i{0}; i < 2; i++) {
    iobj_1.PositionLimitsInternal[i] = poslim_data[i];
  }
  iobj_1.HomePositionInternal.set_size(1);
  iobj_1.HomePositionInternal[0] = 0.0;
  obj->JointInternal = &iobj_1;
  obj->Index = -1.0;
  obj->ParentIndex = -1.0;
  for (int i{0}; i < 36; i++) {
    msubspace_data[i] = 0;
  }
  for (loop_ub = 0; loop_ub < 6; loop_ub++) {
    msubspace_data[loop_ub + 6 * loop_ub] = 1;
  }
  for (int i{0}; i < 36; i++) {
    obj->SpatialInertia[i] = msubspace_data[i];
  }
  obj->CollisionsInternal = iobj_0.init(0.0);
  obj->matlabCodegenIsDeleted = false;
  return obj;
}

//
// Arguments    : CollisionSet &iobj_0
//                rigidBodyJoint &iobj_1
// Return Type  : b_RigidBody *
//
b_RigidBody *b_RigidBody::c_init(CollisionSet &iobj_0, rigidBodyJoint &iobj_1)
{
  static const char jname[14]{'d', 'u', 'm', 'm', 'y', 'b', 'o',
                              'd', 'y', '6', '_', 'j', 'n', 't'};
  static const char bname[10]{'d', 'u', 'm', 'm', 'y', 'b', 'o', 'd', 'y', '6'};
  static const char b_cv1[8]{'r', 'e', 'v', 'o', 'l', 'u', 't', 'e'};
  static const signed char b_iv[6]{0, 0, 1, 0, 0, 0};
  static const signed char b_iv1[6]{0, 0, 0, 0, 0, 1};
  static const char b_cv[5]{'f', 'i', 'x', 'e', 'd'};
  b_RigidBody *obj;
  array<char, 2U> switch_expression;
  double poslim_data[12];
  int exitg1;
  int loop_ub;
  signed char msubspace_data[36];
  boolean_T b_bool;
  obj = this;
  obj->NameInternal.set_size(1, 10);
  for (int i{0}; i < 10; i++) {
    obj->NameInternal[i] = bname[i];
  }
  iobj_1.InTree = false;
  for (int i{0}; i < 16; i++) {
    iobj_1.JointToParentTransform[i] = iv[i];
  }
  for (int i{0}; i < 16; i++) {
    iobj_1.ChildToJointTransform[i] = iv[i];
  }
  iobj_1.NameInternal.set_size(1, 14);
  for (int i{0}; i < 14; i++) {
    iobj_1.NameInternal[i] = jname[i];
  }
  iobj_1.Type.set_size(1, 5);
  for (int i{0}; i < 5; i++) {
    iobj_1.Type[i] = b_cv[i];
  }
  switch_expression.set_size(1, iobj_1.Type.size(1));
  loop_ub = iobj_1.Type.size(1);
  for (int i{0}; i < loop_ub; i++) {
    switch_expression[i] = iobj_1.Type[i];
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
    iobj_1.VelocityNumber = 1.0;
    iobj_1.PositionNumber = 1.0;
    iobj_1.JointAxisInternal[0] = 0.0;
    iobj_1.JointAxisInternal[1] = 0.0;
    iobj_1.JointAxisInternal[2] = 1.0;
    break;
  case 1:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = b_iv1[i];
    }
    poslim_data[0] = -0.5;
    poslim_data[1] = 0.5;
    iobj_1.VelocityNumber = 1.0;
    iobj_1.PositionNumber = 1.0;
    iobj_1.JointAxisInternal[0] = 0.0;
    iobj_1.JointAxisInternal[1] = 0.0;
    iobj_1.JointAxisInternal[2] = 1.0;
    break;
  default:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = 0;
    }
    poslim_data[0] = 0.0;
    poslim_data[1] = 0.0;
    iobj_1.VelocityNumber = 0.0;
    iobj_1.PositionNumber = 0.0;
    iobj_1.JointAxisInternal[0] = 0.0;
    iobj_1.JointAxisInternal[1] = 0.0;
    iobj_1.JointAxisInternal[2] = 0.0;
    break;
  }
  iobj_1.MotionSubspace.set_size(6, 1);
  for (int i{0}; i < 6; i++) {
    iobj_1.MotionSubspace[i] = msubspace_data[i];
  }
  iobj_1.PositionLimitsInternal.set_size(1, 2);
  for (int i{0}; i < 2; i++) {
    iobj_1.PositionLimitsInternal[i] = poslim_data[i];
  }
  iobj_1.HomePositionInternal.set_size(1);
  iobj_1.HomePositionInternal[0] = 0.0;
  obj->JointInternal = &iobj_1;
  obj->Index = -1.0;
  obj->ParentIndex = -1.0;
  for (int i{0}; i < 36; i++) {
    msubspace_data[i] = 0;
  }
  for (loop_ub = 0; loop_ub < 6; loop_ub++) {
    msubspace_data[loop_ub + 6 * loop_ub] = 1;
  }
  for (int i{0}; i < 36; i++) {
    obj->SpatialInertia[i] = msubspace_data[i];
  }
  obj->CollisionsInternal = iobj_0.init(0.0);
  obj->matlabCodegenIsDeleted = false;
  return obj;
}

//
// Arguments    : void
// Return Type  : b_RigidBody
//
b_RigidBody::b_RigidBody()
{
  matlabCodegenIsDeleted = true;
}

//
// Arguments    : void
// Return Type  : RigidBody
//
RigidBody::RigidBody()
{
  matlabCodegenIsDeleted = true;
}

//
// Arguments    : CollisionSet &iobj_0
//                rigidBodyJoint &iobj_1
//                b_RigidBody &iobj_2
// Return Type  : b_RigidBody *
//
b_RigidBody *RigidBody::copy(CollisionSet &iobj_0, rigidBodyJoint &iobj_1,
                             b_RigidBody &iobj_2)
{
  static const char b_cv1[8]{'r', 'e', 'v', 'o', 'l', 'u', 't', 'e'};
  static const signed char b_iv[6]{0, 0, 1, 0, 0, 0};
  static const signed char b_iv1[6]{0, 0, 0, 0, 0, 1};
  static const char b_cv[5]{'f', 'i', 'x', 'e', 'd'};
  CollisionGeometry b_newObj;
  CollisionGeometry c_obj;
  CollisionSet *b_obj;
  CollisionSet *newObj;
  b_RigidBody *newbody;
  array<char, 2U> bodyInput;
  double obj[36];
  double poslim_data[12];
  int exitg1;
  int i;
  int loop_ub;
  signed char msubspace_data[36];
  boolean_T b_bool;
  bodyInput.set_size(1, NameInternal.size(1));
  loop_ub = NameInternal.size(1);
  for (i = 0; i < loop_ub; i++) {
    bodyInput[i] = NameInternal[i];
  }
  newbody = &iobj_2;
  iobj_2.NameInternal.set_size(1, bodyInput.size(1));
  loop_ub = bodyInput.size(1);
  for (i = 0; i < loop_ub; i++) {
    iobj_2.NameInternal[i] = bodyInput[i];
  }
  (&iobj_1)[0].InTree = false;
  for (i = 0; i < 16; i++) {
    (&iobj_1)[0].JointToParentTransform[i] = iv[i];
  }
  for (i = 0; i < 16; i++) {
    (&iobj_1)[0].ChildToJointTransform[i] = iv[i];
  }
  (&iobj_1)[0].NameInternal.set_size(1, bodyInput.size(1) + 4);
  loop_ub = bodyInput.size(1);
  for (i = 0; i < loop_ub; i++) {
    (&iobj_1)[0].NameInternal[i] = bodyInput[i];
  }
  (&iobj_1)[0].NameInternal[bodyInput.size(1)] = '_';
  (&iobj_1)[0].NameInternal[bodyInput.size(1) + 1] = 'j';
  (&iobj_1)[0].NameInternal[bodyInput.size(1) + 2] = 'n';
  (&iobj_1)[0].NameInternal[bodyInput.size(1) + 3] = 't';
  (&iobj_1)[0].Type.set_size(1, 5);
  for (i = 0; i < 5; i++) {
    (&iobj_1)[0].Type[i] = b_cv[i];
  }
  bodyInput.set_size(1, (&iobj_1)[0].Type.size(1));
  loop_ub = (&iobj_1)[0].Type.size(1);
  for (i = 0; i < loop_ub; i++) {
    bodyInput[i] = (&iobj_1)[0].Type[i];
  }
  b_bool = false;
  if (bodyInput.size(1) == 8) {
    loop_ub = 0;
    do {
      exitg1 = 0;
      if (loop_ub < 8) {
        if (bodyInput[loop_ub] != b_cv1[loop_ub]) {
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
    if (bodyInput.size(1) == 9) {
      loop_ub = 0;
      do {
        exitg1 = 0;
        if (loop_ub < 9) {
          if (bodyInput[loop_ub] != cv1[loop_ub]) {
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
    (&iobj_1)[0].VelocityNumber = 1.0;
    (&iobj_1)[0].PositionNumber = 1.0;
    (&iobj_1)[0].JointAxisInternal[0] = 0.0;
    (&iobj_1)[0].JointAxisInternal[1] = 0.0;
    (&iobj_1)[0].JointAxisInternal[2] = 1.0;
    break;
  case 1:
    for (i = 0; i < 6; i++) {
      msubspace_data[i] = b_iv1[i];
    }
    poslim_data[0] = -0.5;
    poslim_data[1] = 0.5;
    (&iobj_1)[0].VelocityNumber = 1.0;
    (&iobj_1)[0].PositionNumber = 1.0;
    (&iobj_1)[0].JointAxisInternal[0] = 0.0;
    (&iobj_1)[0].JointAxisInternal[1] = 0.0;
    (&iobj_1)[0].JointAxisInternal[2] = 1.0;
    break;
  default:
    for (i = 0; i < 6; i++) {
      msubspace_data[i] = 0;
    }
    poslim_data[0] = 0.0;
    poslim_data[1] = 0.0;
    (&iobj_1)[0].VelocityNumber = 0.0;
    (&iobj_1)[0].PositionNumber = 0.0;
    (&iobj_1)[0].JointAxisInternal[0] = 0.0;
    (&iobj_1)[0].JointAxisInternal[1] = 0.0;
    (&iobj_1)[0].JointAxisInternal[2] = 0.0;
    break;
  }
  (&iobj_1)[0].MotionSubspace.set_size(6, 1);
  for (i = 0; i < 6; i++) {
    (&iobj_1)[0].MotionSubspace[i] = msubspace_data[i];
  }
  (&iobj_1)[0].PositionLimitsInternal.set_size(1, 2);
  for (i = 0; i < 2; i++) {
    (&iobj_1)[0].PositionLimitsInternal[i] = poslim_data[i];
  }
  (&iobj_1)[0].HomePositionInternal.set_size(1);
  (&iobj_1)[0].HomePositionInternal[0] = 0.0;
  iobj_2.JointInternal = &(&iobj_1)[0];
  iobj_2.Index = -1.0;
  iobj_2.ParentIndex = -1.0;
  for (i = 0; i < 36; i++) {
    msubspace_data[i] = 0;
  }
  for (loop_ub = 0; loop_ub < 6; loop_ub++) {
    msubspace_data[loop_ub + 6 * loop_ub] = 1;
  }
  for (i = 0; i < 36; i++) {
    iobj_2.SpatialInertia[i] = msubspace_data[i];
  }
  iobj_2.CollisionsInternal = (&iobj_0)[0].init(0.0);
  iobj_2.matlabCodegenIsDeleted = false;
  iobj_2.JointInternal = JointInternal->copy((&iobj_1)[1]);
  for (i = 0; i < 36; i++) {
    obj[i] = SpatialInertia[i];
  }
  for (i = 0; i < 36; i++) {
    iobj_2.SpatialInertia[i] = obj[i];
  }
  double d;
  b_obj = CollisionsInternal;
  newObj = (&iobj_0)[1].init(b_obj->MaxElements);
  newObj->Size = b_obj->Size;
  newObj->Tags = b_obj->Tags;
  d = b_obj->Size;
  i = static_cast<int>(d);
  for (loop_ub = 0; loop_ub < i; loop_ub++) {
    void *primitive_GeometryInternal;
    c_obj = b_obj->CollisionGeometries[loop_ub];
    primitive_GeometryInternal =
        collisioncodegen_copyGeometry(c_obj.CollisionPrimitive);
    b_newObj.CollisionPrimitive = primitive_GeometryInternal;
    ::std::copy(&c_obj.LocalPose[0], &c_obj.LocalPose[16],
                &b_newObj.LocalPose[0]);
    ::std::copy(&c_obj.WorldPose[0], &c_obj.WorldPose[16],
                &b_newObj.WorldPose[0]);
    newObj->CollisionGeometries[loop_ub] = b_newObj;
  }
  iobj_2.CollisionsInternal = newObj;
  return newbody;
}

//
// Arguments    : CollisionSet &iobj_0
//                rigidBodyJoint &iobj_1
// Return Type  : b_RigidBody *
//
b_RigidBody *b_RigidBody::d_init(CollisionSet &iobj_0, rigidBodyJoint &iobj_1)
{
  static const char jname[14]{'d', 'u', 'm', 'm', 'y', 'b', 'o',
                              'd', 'y', '7', '_', 'j', 'n', 't'};
  static const char bname[10]{'d', 'u', 'm', 'm', 'y', 'b', 'o', 'd', 'y', '7'};
  static const char b_cv1[8]{'r', 'e', 'v', 'o', 'l', 'u', 't', 'e'};
  static const signed char b_iv[6]{0, 0, 1, 0, 0, 0};
  static const signed char b_iv1[6]{0, 0, 0, 0, 0, 1};
  static const char b_cv[5]{'f', 'i', 'x', 'e', 'd'};
  b_RigidBody *obj;
  array<char, 2U> switch_expression;
  double poslim_data[12];
  int exitg1;
  int loop_ub;
  signed char msubspace_data[36];
  boolean_T b_bool;
  obj = this;
  obj->NameInternal.set_size(1, 10);
  for (int i{0}; i < 10; i++) {
    obj->NameInternal[i] = bname[i];
  }
  iobj_1.InTree = false;
  for (int i{0}; i < 16; i++) {
    iobj_1.JointToParentTransform[i] = iv[i];
  }
  for (int i{0}; i < 16; i++) {
    iobj_1.ChildToJointTransform[i] = iv[i];
  }
  iobj_1.NameInternal.set_size(1, 14);
  for (int i{0}; i < 14; i++) {
    iobj_1.NameInternal[i] = jname[i];
  }
  iobj_1.Type.set_size(1, 5);
  for (int i{0}; i < 5; i++) {
    iobj_1.Type[i] = b_cv[i];
  }
  switch_expression.set_size(1, iobj_1.Type.size(1));
  loop_ub = iobj_1.Type.size(1);
  for (int i{0}; i < loop_ub; i++) {
    switch_expression[i] = iobj_1.Type[i];
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
    iobj_1.VelocityNumber = 1.0;
    iobj_1.PositionNumber = 1.0;
    iobj_1.JointAxisInternal[0] = 0.0;
    iobj_1.JointAxisInternal[1] = 0.0;
    iobj_1.JointAxisInternal[2] = 1.0;
    break;
  case 1:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = b_iv1[i];
    }
    poslim_data[0] = -0.5;
    poslim_data[1] = 0.5;
    iobj_1.VelocityNumber = 1.0;
    iobj_1.PositionNumber = 1.0;
    iobj_1.JointAxisInternal[0] = 0.0;
    iobj_1.JointAxisInternal[1] = 0.0;
    iobj_1.JointAxisInternal[2] = 1.0;
    break;
  default:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = 0;
    }
    poslim_data[0] = 0.0;
    poslim_data[1] = 0.0;
    iobj_1.VelocityNumber = 0.0;
    iobj_1.PositionNumber = 0.0;
    iobj_1.JointAxisInternal[0] = 0.0;
    iobj_1.JointAxisInternal[1] = 0.0;
    iobj_1.JointAxisInternal[2] = 0.0;
    break;
  }
  iobj_1.MotionSubspace.set_size(6, 1);
  for (int i{0}; i < 6; i++) {
    iobj_1.MotionSubspace[i] = msubspace_data[i];
  }
  iobj_1.PositionLimitsInternal.set_size(1, 2);
  for (int i{0}; i < 2; i++) {
    iobj_1.PositionLimitsInternal[i] = poslim_data[i];
  }
  iobj_1.HomePositionInternal.set_size(1);
  iobj_1.HomePositionInternal[0] = 0.0;
  obj->JointInternal = &iobj_1;
  obj->Index = -1.0;
  obj->ParentIndex = -1.0;
  for (int i{0}; i < 36; i++) {
    msubspace_data[i] = 0;
  }
  for (loop_ub = 0; loop_ub < 6; loop_ub++) {
    msubspace_data[loop_ub + 6 * loop_ub] = 1;
  }
  for (int i{0}; i < 36; i++) {
    obj->SpatialInertia[i] = msubspace_data[i];
  }
  obj->CollisionsInternal = iobj_0.init(0.0);
  obj->matlabCodegenIsDeleted = false;
  return obj;
}

//
// Arguments    : void
// Return Type  : void
//
b_RigidBody::~b_RigidBody()
{
  matlabCodegenDestructor();
}

//
// Arguments    : void
// Return Type  : void
//
RigidBody::~RigidBody()
{
  matlabCodegenDestructor();
}

//
// Arguments    : CollisionSet &iobj_0
//                rigidBodyJoint &iobj_1
// Return Type  : b_RigidBody *
//
b_RigidBody *b_RigidBody::e_init(CollisionSet &iobj_0, rigidBodyJoint &iobj_1)
{
  static const char jname[14]{'d', 'u', 'm', 'm', 'y', 'b', 'o',
                              'd', 'y', '8', '_', 'j', 'n', 't'};
  static const char bname[10]{'d', 'u', 'm', 'm', 'y', 'b', 'o', 'd', 'y', '8'};
  static const char b_cv1[8]{'r', 'e', 'v', 'o', 'l', 'u', 't', 'e'};
  static const signed char b_iv[6]{0, 0, 1, 0, 0, 0};
  static const signed char b_iv1[6]{0, 0, 0, 0, 0, 1};
  static const char b_cv[5]{'f', 'i', 'x', 'e', 'd'};
  b_RigidBody *obj;
  array<char, 2U> switch_expression;
  double poslim_data[12];
  int exitg1;
  int loop_ub;
  signed char msubspace_data[36];
  boolean_T b_bool;
  obj = this;
  obj->NameInternal.set_size(1, 10);
  for (int i{0}; i < 10; i++) {
    obj->NameInternal[i] = bname[i];
  }
  iobj_1.InTree = false;
  for (int i{0}; i < 16; i++) {
    iobj_1.JointToParentTransform[i] = iv[i];
  }
  for (int i{0}; i < 16; i++) {
    iobj_1.ChildToJointTransform[i] = iv[i];
  }
  iobj_1.NameInternal.set_size(1, 14);
  for (int i{0}; i < 14; i++) {
    iobj_1.NameInternal[i] = jname[i];
  }
  iobj_1.Type.set_size(1, 5);
  for (int i{0}; i < 5; i++) {
    iobj_1.Type[i] = b_cv[i];
  }
  switch_expression.set_size(1, iobj_1.Type.size(1));
  loop_ub = iobj_1.Type.size(1);
  for (int i{0}; i < loop_ub; i++) {
    switch_expression[i] = iobj_1.Type[i];
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
    iobj_1.VelocityNumber = 1.0;
    iobj_1.PositionNumber = 1.0;
    iobj_1.JointAxisInternal[0] = 0.0;
    iobj_1.JointAxisInternal[1] = 0.0;
    iobj_1.JointAxisInternal[2] = 1.0;
    break;
  case 1:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = b_iv1[i];
    }
    poslim_data[0] = -0.5;
    poslim_data[1] = 0.5;
    iobj_1.VelocityNumber = 1.0;
    iobj_1.PositionNumber = 1.0;
    iobj_1.JointAxisInternal[0] = 0.0;
    iobj_1.JointAxisInternal[1] = 0.0;
    iobj_1.JointAxisInternal[2] = 1.0;
    break;
  default:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = 0;
    }
    poslim_data[0] = 0.0;
    poslim_data[1] = 0.0;
    iobj_1.VelocityNumber = 0.0;
    iobj_1.PositionNumber = 0.0;
    iobj_1.JointAxisInternal[0] = 0.0;
    iobj_1.JointAxisInternal[1] = 0.0;
    iobj_1.JointAxisInternal[2] = 0.0;
    break;
  }
  iobj_1.MotionSubspace.set_size(6, 1);
  for (int i{0}; i < 6; i++) {
    iobj_1.MotionSubspace[i] = msubspace_data[i];
  }
  iobj_1.PositionLimitsInternal.set_size(1, 2);
  for (int i{0}; i < 2; i++) {
    iobj_1.PositionLimitsInternal[i] = poslim_data[i];
  }
  iobj_1.HomePositionInternal.set_size(1);
  iobj_1.HomePositionInternal[0] = 0.0;
  obj->JointInternal = &iobj_1;
  obj->Index = -1.0;
  obj->ParentIndex = -1.0;
  for (int i{0}; i < 36; i++) {
    msubspace_data[i] = 0;
  }
  for (loop_ub = 0; loop_ub < 6; loop_ub++) {
    msubspace_data[loop_ub + 6 * loop_ub] = 1;
  }
  for (int i{0}; i < 36; i++) {
    obj->SpatialInertia[i] = msubspace_data[i];
  }
  obj->CollisionsInternal = iobj_0.init(0.0);
  obj->matlabCodegenIsDeleted = false;
  return obj;
}

//
// Arguments    : CollisionSet &iobj_0
//                rigidBodyJoint &iobj_1
// Return Type  : b_RigidBody *
//
b_RigidBody *b_RigidBody::f_init(CollisionSet &iobj_0, rigidBodyJoint &iobj_1)
{
  static const char jname[14]{'d', 'u', 'm', 'm', 'y', 'b', 'o',
                              'd', 'y', '9', '_', 'j', 'n', 't'};
  static const char bname[10]{'d', 'u', 'm', 'm', 'y', 'b', 'o', 'd', 'y', '9'};
  static const char b_cv1[8]{'r', 'e', 'v', 'o', 'l', 'u', 't', 'e'};
  static const signed char b_iv[6]{0, 0, 1, 0, 0, 0};
  static const signed char b_iv1[6]{0, 0, 0, 0, 0, 1};
  static const char b_cv[5]{'f', 'i', 'x', 'e', 'd'};
  b_RigidBody *obj;
  array<char, 2U> switch_expression;
  double poslim_data[12];
  int exitg1;
  int loop_ub;
  signed char msubspace_data[36];
  boolean_T b_bool;
  obj = this;
  obj->NameInternal.set_size(1, 10);
  for (int i{0}; i < 10; i++) {
    obj->NameInternal[i] = bname[i];
  }
  iobj_1.InTree = false;
  for (int i{0}; i < 16; i++) {
    iobj_1.JointToParentTransform[i] = iv[i];
  }
  for (int i{0}; i < 16; i++) {
    iobj_1.ChildToJointTransform[i] = iv[i];
  }
  iobj_1.NameInternal.set_size(1, 14);
  for (int i{0}; i < 14; i++) {
    iobj_1.NameInternal[i] = jname[i];
  }
  iobj_1.Type.set_size(1, 5);
  for (int i{0}; i < 5; i++) {
    iobj_1.Type[i] = b_cv[i];
  }
  switch_expression.set_size(1, iobj_1.Type.size(1));
  loop_ub = iobj_1.Type.size(1);
  for (int i{0}; i < loop_ub; i++) {
    switch_expression[i] = iobj_1.Type[i];
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
    iobj_1.VelocityNumber = 1.0;
    iobj_1.PositionNumber = 1.0;
    iobj_1.JointAxisInternal[0] = 0.0;
    iobj_1.JointAxisInternal[1] = 0.0;
    iobj_1.JointAxisInternal[2] = 1.0;
    break;
  case 1:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = b_iv1[i];
    }
    poslim_data[0] = -0.5;
    poslim_data[1] = 0.5;
    iobj_1.VelocityNumber = 1.0;
    iobj_1.PositionNumber = 1.0;
    iobj_1.JointAxisInternal[0] = 0.0;
    iobj_1.JointAxisInternal[1] = 0.0;
    iobj_1.JointAxisInternal[2] = 1.0;
    break;
  default:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = 0;
    }
    poslim_data[0] = 0.0;
    poslim_data[1] = 0.0;
    iobj_1.VelocityNumber = 0.0;
    iobj_1.PositionNumber = 0.0;
    iobj_1.JointAxisInternal[0] = 0.0;
    iobj_1.JointAxisInternal[1] = 0.0;
    iobj_1.JointAxisInternal[2] = 0.0;
    break;
  }
  iobj_1.MotionSubspace.set_size(6, 1);
  for (int i{0}; i < 6; i++) {
    iobj_1.MotionSubspace[i] = msubspace_data[i];
  }
  iobj_1.PositionLimitsInternal.set_size(1, 2);
  for (int i{0}; i < 2; i++) {
    iobj_1.PositionLimitsInternal[i] = poslim_data[i];
  }
  iobj_1.HomePositionInternal.set_size(1);
  iobj_1.HomePositionInternal[0] = 0.0;
  obj->JointInternal = &iobj_1;
  obj->Index = -1.0;
  obj->ParentIndex = -1.0;
  for (int i{0}; i < 36; i++) {
    msubspace_data[i] = 0;
  }
  for (loop_ub = 0; loop_ub < 6; loop_ub++) {
    msubspace_data[loop_ub + 6 * loop_ub] = 1;
  }
  for (int i{0}; i < 36; i++) {
    obj->SpatialInertia[i] = msubspace_data[i];
  }
  obj->CollisionsInternal = iobj_0.init(0.0);
  obj->matlabCodegenIsDeleted = false;
  return obj;
}

//
// Arguments    : CollisionSet &iobj_0
//                rigidBodyJoint &iobj_1
// Return Type  : b_RigidBody *
//
b_RigidBody *b_RigidBody::g_init(CollisionSet &iobj_0, rigidBodyJoint &iobj_1)
{
  static const char jname[15]{'d', 'u', 'm', 'm', 'y', 'b', 'o', 'd',
                              'y', '1', '0', '_', 'j', 'n', 't'};
  static const char bname[11]{'d', 'u', 'm', 'm', 'y', 'b',
                              'o', 'd', 'y', '1', '0'};
  static const char b_cv1[8]{'r', 'e', 'v', 'o', 'l', 'u', 't', 'e'};
  static const signed char b_iv[6]{0, 0, 1, 0, 0, 0};
  static const signed char b_iv1[6]{0, 0, 0, 0, 0, 1};
  static const char b_cv[5]{'f', 'i', 'x', 'e', 'd'};
  b_RigidBody *obj;
  array<char, 2U> switch_expression;
  double poslim_data[12];
  int exitg1;
  int loop_ub;
  signed char msubspace_data[36];
  boolean_T b_bool;
  obj = this;
  obj->NameInternal.set_size(1, 11);
  for (int i{0}; i < 11; i++) {
    obj->NameInternal[i] = bname[i];
  }
  iobj_1.InTree = false;
  for (int i{0}; i < 16; i++) {
    iobj_1.JointToParentTransform[i] = iv[i];
  }
  for (int i{0}; i < 16; i++) {
    iobj_1.ChildToJointTransform[i] = iv[i];
  }
  iobj_1.NameInternal.set_size(1, 15);
  for (int i{0}; i < 15; i++) {
    iobj_1.NameInternal[i] = jname[i];
  }
  iobj_1.Type.set_size(1, 5);
  for (int i{0}; i < 5; i++) {
    iobj_1.Type[i] = b_cv[i];
  }
  switch_expression.set_size(1, iobj_1.Type.size(1));
  loop_ub = iobj_1.Type.size(1);
  for (int i{0}; i < loop_ub; i++) {
    switch_expression[i] = iobj_1.Type[i];
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
    iobj_1.VelocityNumber = 1.0;
    iobj_1.PositionNumber = 1.0;
    iobj_1.JointAxisInternal[0] = 0.0;
    iobj_1.JointAxisInternal[1] = 0.0;
    iobj_1.JointAxisInternal[2] = 1.0;
    break;
  case 1:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = b_iv1[i];
    }
    poslim_data[0] = -0.5;
    poslim_data[1] = 0.5;
    iobj_1.VelocityNumber = 1.0;
    iobj_1.PositionNumber = 1.0;
    iobj_1.JointAxisInternal[0] = 0.0;
    iobj_1.JointAxisInternal[1] = 0.0;
    iobj_1.JointAxisInternal[2] = 1.0;
    break;
  default:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = 0;
    }
    poslim_data[0] = 0.0;
    poslim_data[1] = 0.0;
    iobj_1.VelocityNumber = 0.0;
    iobj_1.PositionNumber = 0.0;
    iobj_1.JointAxisInternal[0] = 0.0;
    iobj_1.JointAxisInternal[1] = 0.0;
    iobj_1.JointAxisInternal[2] = 0.0;
    break;
  }
  iobj_1.MotionSubspace.set_size(6, 1);
  for (int i{0}; i < 6; i++) {
    iobj_1.MotionSubspace[i] = msubspace_data[i];
  }
  iobj_1.PositionLimitsInternal.set_size(1, 2);
  for (int i{0}; i < 2; i++) {
    iobj_1.PositionLimitsInternal[i] = poslim_data[i];
  }
  iobj_1.HomePositionInternal.set_size(1);
  iobj_1.HomePositionInternal[0] = 0.0;
  obj->JointInternal = &iobj_1;
  obj->Index = -1.0;
  obj->ParentIndex = -1.0;
  for (int i{0}; i < 36; i++) {
    msubspace_data[i] = 0;
  }
  for (loop_ub = 0; loop_ub < 6; loop_ub++) {
    msubspace_data[loop_ub + 6 * loop_ub] = 1;
  }
  for (int i{0}; i < 36; i++) {
    obj->SpatialInertia[i] = msubspace_data[i];
  }
  obj->CollisionsInternal = iobj_0.init(0.0);
  obj->matlabCodegenIsDeleted = false;
  return obj;
}

//
// Arguments    : CollisionSet &iobj_0
//                rigidBodyJoint &iobj_1
// Return Type  : b_RigidBody *
//
b_RigidBody *b_RigidBody::h_init(CollisionSet &iobj_0, rigidBodyJoint &iobj_1)
{
  static const char jname[15]{'d', 'u', 'm', 'm', 'y', 'b', 'o', 'd',
                              'y', '1', '1', '_', 'j', 'n', 't'};
  static const char bname[11]{'d', 'u', 'm', 'm', 'y', 'b',
                              'o', 'd', 'y', '1', '1'};
  static const char b_cv1[8]{'r', 'e', 'v', 'o', 'l', 'u', 't', 'e'};
  static const signed char b_iv[6]{0, 0, 1, 0, 0, 0};
  static const signed char b_iv1[6]{0, 0, 0, 0, 0, 1};
  static const char b_cv[5]{'f', 'i', 'x', 'e', 'd'};
  b_RigidBody *obj;
  array<char, 2U> switch_expression;
  double poslim_data[12];
  int exitg1;
  int loop_ub;
  signed char msubspace_data[36];
  boolean_T b_bool;
  obj = this;
  obj->NameInternal.set_size(1, 11);
  for (int i{0}; i < 11; i++) {
    obj->NameInternal[i] = bname[i];
  }
  iobj_1.InTree = false;
  for (int i{0}; i < 16; i++) {
    iobj_1.JointToParentTransform[i] = iv[i];
  }
  for (int i{0}; i < 16; i++) {
    iobj_1.ChildToJointTransform[i] = iv[i];
  }
  iobj_1.NameInternal.set_size(1, 15);
  for (int i{0}; i < 15; i++) {
    iobj_1.NameInternal[i] = jname[i];
  }
  iobj_1.Type.set_size(1, 5);
  for (int i{0}; i < 5; i++) {
    iobj_1.Type[i] = b_cv[i];
  }
  switch_expression.set_size(1, iobj_1.Type.size(1));
  loop_ub = iobj_1.Type.size(1);
  for (int i{0}; i < loop_ub; i++) {
    switch_expression[i] = iobj_1.Type[i];
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
    iobj_1.VelocityNumber = 1.0;
    iobj_1.PositionNumber = 1.0;
    iobj_1.JointAxisInternal[0] = 0.0;
    iobj_1.JointAxisInternal[1] = 0.0;
    iobj_1.JointAxisInternal[2] = 1.0;
    break;
  case 1:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = b_iv1[i];
    }
    poslim_data[0] = -0.5;
    poslim_data[1] = 0.5;
    iobj_1.VelocityNumber = 1.0;
    iobj_1.PositionNumber = 1.0;
    iobj_1.JointAxisInternal[0] = 0.0;
    iobj_1.JointAxisInternal[1] = 0.0;
    iobj_1.JointAxisInternal[2] = 1.0;
    break;
  default:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = 0;
    }
    poslim_data[0] = 0.0;
    poslim_data[1] = 0.0;
    iobj_1.VelocityNumber = 0.0;
    iobj_1.PositionNumber = 0.0;
    iobj_1.JointAxisInternal[0] = 0.0;
    iobj_1.JointAxisInternal[1] = 0.0;
    iobj_1.JointAxisInternal[2] = 0.0;
    break;
  }
  iobj_1.MotionSubspace.set_size(6, 1);
  for (int i{0}; i < 6; i++) {
    iobj_1.MotionSubspace[i] = msubspace_data[i];
  }
  iobj_1.PositionLimitsInternal.set_size(1, 2);
  for (int i{0}; i < 2; i++) {
    iobj_1.PositionLimitsInternal[i] = poslim_data[i];
  }
  iobj_1.HomePositionInternal.set_size(1);
  iobj_1.HomePositionInternal[0] = 0.0;
  obj->JointInternal = &iobj_1;
  obj->Index = -1.0;
  obj->ParentIndex = -1.0;
  for (int i{0}; i < 36; i++) {
    msubspace_data[i] = 0;
  }
  for (loop_ub = 0; loop_ub < 6; loop_ub++) {
    msubspace_data[loop_ub + 6 * loop_ub] = 1;
  }
  for (int i{0}; i < 36; i++) {
    obj->SpatialInertia[i] = msubspace_data[i];
  }
  obj->CollisionsInternal = iobj_0.init(0.0);
  obj->matlabCodegenIsDeleted = false;
  return obj;
}

//
// Arguments    : CollisionSet &iobj_0
//                rigidBodyJoint &iobj_1
// Return Type  : b_RigidBody *
//
b_RigidBody *b_RigidBody::init(CollisionSet &iobj_0, rigidBodyJoint &iobj_1)
{
  static const char jname[14]{'d', 'u', 'm', 'm', 'y', 'b', 'o',
                              'd', 'y', '4', '_', 'j', 'n', 't'};
  static const char bname[10]{'d', 'u', 'm', 'm', 'y', 'b', 'o', 'd', 'y', '4'};
  static const char b_cv1[8]{'r', 'e', 'v', 'o', 'l', 'u', 't', 'e'};
  static const signed char b_iv[6]{0, 0, 1, 0, 0, 0};
  static const signed char b_iv1[6]{0, 0, 0, 0, 0, 1};
  static const char b_cv[5]{'f', 'i', 'x', 'e', 'd'};
  b_RigidBody *obj;
  array<char, 2U> switch_expression;
  double poslim_data[12];
  int exitg1;
  int loop_ub;
  signed char msubspace_data[36];
  boolean_T b_bool;
  obj = this;
  obj->NameInternal.set_size(1, 10);
  for (int i{0}; i < 10; i++) {
    obj->NameInternal[i] = bname[i];
  }
  iobj_1.InTree = false;
  for (int i{0}; i < 16; i++) {
    iobj_1.JointToParentTransform[i] = iv[i];
  }
  for (int i{0}; i < 16; i++) {
    iobj_1.ChildToJointTransform[i] = iv[i];
  }
  iobj_1.NameInternal.set_size(1, 14);
  for (int i{0}; i < 14; i++) {
    iobj_1.NameInternal[i] = jname[i];
  }
  iobj_1.Type.set_size(1, 5);
  for (int i{0}; i < 5; i++) {
    iobj_1.Type[i] = b_cv[i];
  }
  switch_expression.set_size(1, iobj_1.Type.size(1));
  loop_ub = iobj_1.Type.size(1);
  for (int i{0}; i < loop_ub; i++) {
    switch_expression[i] = iobj_1.Type[i];
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
    iobj_1.VelocityNumber = 1.0;
    iobj_1.PositionNumber = 1.0;
    iobj_1.JointAxisInternal[0] = 0.0;
    iobj_1.JointAxisInternal[1] = 0.0;
    iobj_1.JointAxisInternal[2] = 1.0;
    break;
  case 1:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = b_iv1[i];
    }
    poslim_data[0] = -0.5;
    poslim_data[1] = 0.5;
    iobj_1.VelocityNumber = 1.0;
    iobj_1.PositionNumber = 1.0;
    iobj_1.JointAxisInternal[0] = 0.0;
    iobj_1.JointAxisInternal[1] = 0.0;
    iobj_1.JointAxisInternal[2] = 1.0;
    break;
  default:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = 0;
    }
    poslim_data[0] = 0.0;
    poslim_data[1] = 0.0;
    iobj_1.VelocityNumber = 0.0;
    iobj_1.PositionNumber = 0.0;
    iobj_1.JointAxisInternal[0] = 0.0;
    iobj_1.JointAxisInternal[1] = 0.0;
    iobj_1.JointAxisInternal[2] = 0.0;
    break;
  }
  iobj_1.MotionSubspace.set_size(6, 1);
  for (int i{0}; i < 6; i++) {
    iobj_1.MotionSubspace[i] = msubspace_data[i];
  }
  iobj_1.PositionLimitsInternal.set_size(1, 2);
  for (int i{0}; i < 2; i++) {
    iobj_1.PositionLimitsInternal[i] = poslim_data[i];
  }
  iobj_1.HomePositionInternal.set_size(1);
  iobj_1.HomePositionInternal[0] = 0.0;
  obj->JointInternal = &iobj_1;
  obj->Index = -1.0;
  obj->ParentIndex = -1.0;
  for (int i{0}; i < 36; i++) {
    msubspace_data[i] = 0;
  }
  for (loop_ub = 0; loop_ub < 6; loop_ub++) {
    msubspace_data[loop_ub + 6 * loop_ub] = 1;
  }
  for (int i{0}; i < 36; i++) {
    obj->SpatialInertia[i] = msubspace_data[i];
  }
  obj->CollisionsInternal = iobj_0.init(0.0);
  obj->matlabCodegenIsDeleted = false;
  return obj;
}

//
// Arguments    : void
// Return Type  : void
//
void b_RigidBody::matlabCodegenDestructor()
{
  if (!matlabCodegenIsDeleted) {
    matlabCodegenIsDeleted = true;
  }
}

//
// Arguments    : void
// Return Type  : void
//
void RigidBody::matlabCodegenDestructor()
{
  if (!matlabCodegenIsDeleted) {
    matlabCodegenIsDeleted = true;
  }
}

} // namespace internal
} // namespace manip
} // namespace robotics
} // namespace coder

//
// File trailer for RigidBody.cpp
//
// [EOF]
//
