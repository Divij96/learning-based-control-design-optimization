//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: rigidBodyTree.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 02-Feb-2024 13:34:01
//

// Include Files
#include "rigidBodyTree.h"
#include "CollisionSet.h"
#include "RigidBody.h"
#include "RigidBodyTree1.h"
#include "RigidBodyTreeDynamics.h"
#include "forward_dynamics_robot_arm_data.h"
#include "rand.h"
#include "rigidBody1.h"
#include "rigidBodyJoint.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : rigidBody *bodyin
//                robotics::manip::internal::CollisionSet &iobj_0
//                rigidBodyJoint &iobj_1
//                robotics::manip::internal::b_RigidBody &iobj_2
// Return Type  : void
//
namespace coder {
void rigidBodyTree::addBody(rigidBody *bodyin,
                            robotics::manip::internal::CollisionSet &iobj_0,
                            rigidBodyJoint &iobj_1,
                            robotics::manip::internal::b_RigidBody &iobj_2)
{
  static const char b_cv1[5]{'f', 'i', 'x', 'e', 'd'};
  static const char b_cv[4]{'b', 'a', 's', 'e'};
  rigidBodyJoint *jnt;
  robotics::manip::internal::RigidBody *b_bodyin;
  robotics::manip::internal::b_RigidBody *body;
  array<char, 2U> bname;
  double b_index;
  int exitg1;
  int loop_ub;
  int pid;
  boolean_T b_bool;
  b_bodyin = bodyin->BodyInternal;
  bname.set_size(1, b_bodyin->NameInternal.size(1));
  loop_ub = b_bodyin->NameInternal.size(1);
  for (int i{0}; i < loop_ub; i++) {
    bname[i] = b_bodyin->NameInternal[i];
  }
  TreeInternal.findBodyIndexByName(bname);
  pid = -1;
  bname.set_size(1, TreeInternal.Base.NameInternal.size(1));
  loop_ub = TreeInternal.Base.NameInternal.size(1);
  for (int i{0}; i < loop_ub; i++) {
    bname[i] = TreeInternal.Base.NameInternal[i];
  }
  b_bool = false;
  if (bname.size(1) == 4) {
    loop_ub = 0;
    do {
      exitg1 = 0;
      if (loop_ub < 4) {
        if (bname[loop_ub] != b_cv[loop_ub]) {
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
    pid = 0;
  } else {
    int b_i;
    boolean_T exitg2;
    b_index = TreeInternal.NumBodies;
    b_i = 0;
    exitg2 = false;
    while ((!exitg2) && (b_i <= static_cast<int>(b_index) - 1)) {
      body = TreeInternal.Bodies[b_i];
      bname.set_size(1, body->NameInternal.size(1));
      loop_ub = body->NameInternal.size(1);
      for (int i{0}; i < loop_ub; i++) {
        bname[i] = body->NameInternal[i];
      }
      b_bool = false;
      if (bname.size(1) == 4) {
        loop_ub = 0;
        do {
          exitg1 = 0;
          if (loop_ub < 4) {
            if (bname[loop_ub] != b_cv[loop_ub]) {
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
        pid = b_i + 1;
        exitg2 = true;
      } else {
        b_i++;
      }
    }
  }
  b_index = TreeInternal.NumBodies + 1.0;
  body = b_bodyin->copy((&(&iobj_0)[0])[0], (&(&iobj_1)[0])[0], iobj_2);
  TreeInternal.Bodies[static_cast<int>(b_index) - 1] = body;
  body->Index = b_index;
  body->ParentIndex = pid;
  body->JointInternal->InTree = true;
  TreeInternal.NumBodies++;
  jnt = body->JointInternal;
  bname.set_size(1, jnt->Type.size(1));
  loop_ub = jnt->Type.size(1);
  for (int i{0}; i < loop_ub; i++) {
    bname[i] = jnt->Type[i];
  }
  b_bool = false;
  if (bname.size(1) == 5) {
    loop_ub = 0;
    do {
      exitg1 = 0;
      if (loop_ub < 5) {
        if (bname[loop_ub] != b_cv1[loop_ub]) {
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
  if (!b_bool) {
    TreeInternal.NumNonFixedBodies++;
    jnt = body->JointInternal;
    loop_ub = static_cast<int>(body->Index) - 1;
    TreeInternal.PositionDoFMap[loop_ub] = TreeInternal.PositionNumber + 1.0;
    TreeInternal.PositionDoFMap[loop_ub + 11] =
        TreeInternal.PositionNumber + jnt->PositionNumber;
    jnt = body->JointInternal;
    loop_ub = static_cast<int>(body->Index) - 1;
    TreeInternal.VelocityDoFMap[loop_ub] = TreeInternal.VelocityNumber + 1.0;
    TreeInternal.VelocityDoFMap[loop_ub + 11] =
        TreeInternal.VelocityNumber + jnt->VelocityNumber;
  } else {
    loop_ub = static_cast<int>(body->Index);
    TreeInternal.PositionDoFMap[loop_ub - 1] = 0.0;
    TreeInternal.PositionDoFMap[loop_ub + 10] = -1.0;
    loop_ub = static_cast<int>(body->Index);
    TreeInternal.VelocityDoFMap[loop_ub - 1] = 0.0;
    TreeInternal.VelocityDoFMap[loop_ub + 10] = -1.0;
  }
  jnt = body->JointInternal;
  TreeInternal.PositionNumber += jnt->PositionNumber;
  jnt = body->JointInternal;
  TreeInternal.VelocityNumber += jnt->VelocityNumber;
}

//
// Arguments    : rigidBody *bodyin
//                const char parentName[6]
//                robotics::manip::internal::CollisionSet &iobj_0
//                rigidBodyJoint &iobj_1
//                robotics::manip::internal::b_RigidBody &iobj_2
// Return Type  : void
//
void rigidBodyTree::addBody(rigidBody *bodyin, const char parentName[6],
                            robotics::manip::internal::CollisionSet &iobj_0,
                            rigidBodyJoint &iobj_1,
                            robotics::manip::internal::b_RigidBody &iobj_2)
{
  static const char b_cv[5]{'f', 'i', 'x', 'e', 'd'};
  rigidBodyJoint *jnt;
  robotics::manip::internal::RigidBody *b_bodyin;
  robotics::manip::internal::b_RigidBody *body;
  array<char, 2U> bname;
  double b_index;
  int exitg1;
  int loop_ub;
  int pid;
  boolean_T b_bool;
  b_bodyin = bodyin->BodyInternal;
  bname.set_size(1, b_bodyin->NameInternal.size(1));
  loop_ub = b_bodyin->NameInternal.size(1);
  for (int i{0}; i < loop_ub; i++) {
    bname[i] = b_bodyin->NameInternal[i];
  }
  TreeInternal.findBodyIndexByName(bname);
  pid = -1;
  bname.set_size(1, TreeInternal.Base.NameInternal.size(1));
  loop_ub = TreeInternal.Base.NameInternal.size(1);
  for (int i{0}; i < loop_ub; i++) {
    bname[i] = TreeInternal.Base.NameInternal[i];
  }
  b_bool = false;
  if (bname.size(1) == 6) {
    loop_ub = 0;
    do {
      exitg1 = 0;
      if (loop_ub < 6) {
        if (bname[loop_ub] != parentName[loop_ub]) {
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
    pid = 0;
  } else {
    int b_i;
    boolean_T exitg2;
    b_index = TreeInternal.NumBodies;
    b_i = 0;
    exitg2 = false;
    while ((!exitg2) && (b_i <= static_cast<int>(b_index) - 1)) {
      body = TreeInternal.Bodies[b_i];
      bname.set_size(1, body->NameInternal.size(1));
      loop_ub = body->NameInternal.size(1);
      for (int i{0}; i < loop_ub; i++) {
        bname[i] = body->NameInternal[i];
      }
      b_bool = false;
      if (bname.size(1) == 6) {
        loop_ub = 0;
        do {
          exitg1 = 0;
          if (loop_ub < 6) {
            if (bname[loop_ub] != parentName[loop_ub]) {
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
        pid = b_i + 1;
        exitg2 = true;
      } else {
        b_i++;
      }
    }
  }
  b_index = TreeInternal.NumBodies + 1.0;
  body = b_bodyin->copy((&(&iobj_0)[0])[0], (&(&iobj_1)[0])[0], iobj_2);
  TreeInternal.Bodies[static_cast<int>(b_index) - 1] = body;
  body->Index = b_index;
  body->ParentIndex = pid;
  body->JointInternal->InTree = true;
  TreeInternal.NumBodies++;
  jnt = body->JointInternal;
  bname.set_size(1, jnt->Type.size(1));
  loop_ub = jnt->Type.size(1);
  for (int i{0}; i < loop_ub; i++) {
    bname[i] = jnt->Type[i];
  }
  b_bool = false;
  if (bname.size(1) == 5) {
    loop_ub = 0;
    do {
      exitg1 = 0;
      if (loop_ub < 5) {
        if (bname[loop_ub] != b_cv[loop_ub]) {
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
  if (!b_bool) {
    TreeInternal.NumNonFixedBodies++;
    jnt = body->JointInternal;
    loop_ub = static_cast<int>(body->Index) - 1;
    TreeInternal.PositionDoFMap[loop_ub] = TreeInternal.PositionNumber + 1.0;
    TreeInternal.PositionDoFMap[loop_ub + 11] =
        TreeInternal.PositionNumber + jnt->PositionNumber;
    jnt = body->JointInternal;
    loop_ub = static_cast<int>(body->Index) - 1;
    TreeInternal.VelocityDoFMap[loop_ub] = TreeInternal.VelocityNumber + 1.0;
    TreeInternal.VelocityDoFMap[loop_ub + 11] =
        TreeInternal.VelocityNumber + jnt->VelocityNumber;
  } else {
    loop_ub = static_cast<int>(body->Index);
    TreeInternal.PositionDoFMap[loop_ub - 1] = 0.0;
    TreeInternal.PositionDoFMap[loop_ub + 10] = -1.0;
    loop_ub = static_cast<int>(body->Index);
    TreeInternal.VelocityDoFMap[loop_ub - 1] = 0.0;
    TreeInternal.VelocityDoFMap[loop_ub + 10] = -1.0;
  }
  jnt = body->JointInternal;
  TreeInternal.PositionNumber += jnt->PositionNumber;
  jnt = body->JointInternal;
  TreeInternal.VelocityNumber += jnt->VelocityNumber;
}

//
// Arguments    : void
// Return Type  : rigidBodyTree
//
rigidBodyTree::rigidBodyTree()
{
  matlabCodegenIsDeleted = true;
}

//
// Arguments    : void
// Return Type  : void
//
rigidBodyTree::~rigidBodyTree()
{
  matlabCodegenDestructor();
}

//
// Arguments    : const double varargin_1[10]
//                const double varargin_2[10]
//                const double varargin_3[10]
//                double qddot_data[]
// Return Type  : int
//
int rigidBodyTree::forwardDynamics(const double varargin_1[10],
                                   const double varargin_2[10],
                                   const double varargin_3[10],
                                   double qddot_data[])
{
  array<double, 2U> H;
  array<double, 2U> fext;
  array<double, 2U> lambda;
  double b_j;
  double k;
  double vNum;
  int iend;
  int n;
  int qddot_size;
  fext.set_size(6, static_cast<int>(TreeInternal.NumBodies));
  iend = 6 * static_cast<int>(TreeInternal.NumBodies);
  for (n = 0; n < iend; n++) {
    fext[n] = 0.0;
  }
  robotics::manip::internal::RigidBodyTreeDynamics::massMatrix(
      TreeInternal, varargin_1, H, lambda);
  vNum = TreeInternal.VelocityNumber;
  robotics::manip::internal::RigidBodyTreeDynamics::inverseDynamics(
      TreeInternal, varargin_1, varargin_2, fext, qddot_data);
  qddot_size = 10;
  for (n = 0; n < 10; n++) {
    qddot_data[n] = varargin_3[n] - qddot_data[n];
  }
  if ((H.size(0) == 0) || (H.size(1) == 0)) {
    n = -1;
  } else if (H.size(0) > H.size(1)) {
    n = H.size(0) - 1;
  } else {
    n = H.size(1) - 1;
  }
  for (int i{0}; i <= n; i++) {
    iend = n - i;
    H[iend + H.size(0) * iend] = std::sqrt(H[iend + H.size(0) * iend]);
    k = lambda[iend];
    while (k > 0.0) {
      H[iend + H.size(0) * (static_cast<int>(k) - 1)] =
          H[iend + H.size(0) * (static_cast<int>(k) - 1)] /
          H[iend + H.size(0) * iend];
      k = lambda[static_cast<int>(k) - 1];
    }
    k = lambda[iend];
    while (k > 0.0) {
      b_j = k;
      while (b_j > 0.0) {
        H[(static_cast<int>(k) + H.size(0) * (static_cast<int>(b_j) - 1)) - 1] =
            H[(static_cast<int>(k) + H.size(0) * (static_cast<int>(b_j) - 1)) -
              1] -
            H[iend + H.size(0) * (static_cast<int>(k) - 1)] *
                H[iend + H.size(0) * (static_cast<int>(b_j) - 1)];
        b_j = lambda[static_cast<int>(b_j) - 1];
      }
      k = lambda[static_cast<int>(k) - 1];
    }
  }
  n = H.size(1);
  if ((H.size(0) != 0) && (H.size(1) != 0) && (H.size(1) > 1)) {
    iend = 1;
    for (int j{2}; j <= n; j++) {
      for (int i{0}; i < iend; i++) {
        H[i + H.size(0) * (j - 1)] = 0.0;
      }
      if (iend < H.size(0)) {
        iend++;
      }
    }
  }
  n = static_cast<int>(-((-1.0 - vNum) + 1.0));
  for (int i{0}; i < n; i++) {
    k = vNum - static_cast<double>(i);
    qddot_data[static_cast<int>(k) - 1] /=
        H[(static_cast<int>(k) + H.size(0) * (static_cast<int>(k) - 1)) - 1];
    b_j = lambda[static_cast<int>(k) - 1];
    while (b_j > 0.0) {
      qddot_data[static_cast<int>(b_j) - 1] -=
          qddot_data[static_cast<int>(k) - 1] *
          H[(static_cast<int>(k) + H.size(0) * (static_cast<int>(b_j) - 1)) -
            1];
      b_j = lambda[static_cast<int>(b_j) - 1];
    }
  }
  n = static_cast<int>(vNum);
  for (int i{0}; i < n; i++) {
    b_j = lambda[i];
    while (b_j > 0.0) {
      qddot_data[i] -= H[i + H.size(0) * (static_cast<int>(b_j) - 1)] *
                       qddot_data[static_cast<int>(b_j) - 1];
      b_j = lambda[static_cast<int>(b_j) - 1];
    }
    qddot_data[i] /= H[i + H.size(0) * i];
  }
  return qddot_size;
}

//
// Arguments    : void
// Return Type  : rigidBodyTree *
//
rigidBodyTree *rigidBodyTree::init()
{
  static const signed char iv2[22]{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
                                   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
  static const char b_jname[14]{'d', 'u', 'm', 'm', 'y', 'b', 'o',
                                'd', 'y', '3', '_', 'j', 'n', 't'};
  static const char jname[14]{'d', 'u', 'm', 'm', 'y', 'b', 'o',
                              'd', 'y', '2', '_', 'j', 'n', 't'};
  static const char b_bname[10]{'d', 'u', 'm', 'm', 'y',
                                'b', 'o', 'd', 'y', '3'};
  static const char bname[10]{'d', 'u', 'm', 'm', 'y', 'b', 'o', 'd', 'y', '2'};
  static const char b_cv1[8]{'r', 'e', 'v', 'o', 'l', 'u', 't', 'e'};
  static const signed char b_iv[6]{0, 0, 1, 0, 0, 0};
  static const signed char b_iv1[6]{0, 0, 0, 0, 0, 1};
  static const char b_cv[5]{'f', 'i', 'x', 'e', 'd'};
  rigidBodyTree *obj;
  array<char, 2U> switch_expression;
  double poslim_data[12];
  double unusedExpr[5];
  int exitg1;
  int k;
  signed char msubspace_data[36];
  char jointtype_tmp_data[20];
  boolean_T b_bool;
  obj = this;
  obj->TreeInternal.Base.NameInternal.set_size(1, 4);
  obj->TreeInternal.Base.NameInternal[0] = 'b';
  obj->TreeInternal.Base.NameInternal[1] = 'a';
  obj->TreeInternal.Base.NameInternal[2] = 's';
  obj->TreeInternal.Base.NameInternal[3] = 'e';
  obj->TreeInternal.Base.JointInternal = obj->TreeInternal.Base._pobj1.init();
  obj->TreeInternal.Base.Index = -1.0;
  obj->TreeInternal.Base.ParentIndex = -1.0;
  for (int i{0}; i < 36; i++) {
    msubspace_data[i] = 0;
  }
  for (k = 0; k < 6; k++) {
    msubspace_data[k + 6 * k] = 1;
  }
  for (int i{0}; i < 36; i++) {
    obj->TreeInternal.Base.SpatialInertia[i] = msubspace_data[i];
  }
  obj->TreeInternal.Base.CollisionsInternal =
      obj->TreeInternal.Base._pobj0.init(0.0);
  obj->TreeInternal.Base.matlabCodegenIsDeleted = false;
  obj->TreeInternal.Base.Index = 0.0;
  b_rand(unusedExpr);
  obj->TreeInternal.Gravity[0] = 0.0;
  obj->TreeInternal.Gravity[1] = 0.0;
  obj->TreeInternal.Gravity[2] = 0.0;
  (&(&obj->TreeInternal._pobj2[0])[0])[0].NameInternal.set_size(1, 10);
  for (int i{0}; i < 10; i++) {
    (&(&obj->TreeInternal._pobj2[0])[0])[0].NameInternal[i] = cv[i];
  }
  (&(&obj->TreeInternal._pobj2[0])[0])[0].JointInternal =
      (&(&obj->TreeInternal._pobj2[0])[0])[0]._pobj1.b_init();
  (&(&obj->TreeInternal._pobj2[0])[0])[0].Index = -1.0;
  (&(&obj->TreeInternal._pobj2[0])[0])[0].ParentIndex = -1.0;
  for (int i{0}; i < 36; i++) {
    msubspace_data[i] = 0;
  }
  for (k = 0; k < 6; k++) {
    msubspace_data[k + 6 * k] = 1;
  }
  for (int i{0}; i < 36; i++) {
    (&(&obj->TreeInternal._pobj2[0])[0])[0].SpatialInertia[i] =
        msubspace_data[i];
  }
  (&(&obj->TreeInternal._pobj2[0])[0])[0].CollisionsInternal =
      (&(&obj->TreeInternal._pobj2[0])[0])[0]._pobj0.init(0.0);
  (&(&obj->TreeInternal._pobj2[0])[0])[0].matlabCodegenIsDeleted = false;
  obj->TreeInternal.Bodies[0] = &(&(&obj->TreeInternal._pobj2[0])[0])[0];
  (&(&obj->TreeInternal._pobj2[0])[0])[1].NameInternal.set_size(1, 10);
  for (int i{0}; i < 10; i++) {
    (&(&obj->TreeInternal._pobj2[0])[0])[1].NameInternal[i] = bname[i];
  }
  (&(&obj->TreeInternal._pobj1[0])[0])[0].InTree = false;
  for (int i{0}; i < 16; i++) {
    (&(&obj->TreeInternal._pobj1[0])[0])[0].JointToParentTransform[i] = iv[i];
  }
  for (int i{0}; i < 16; i++) {
    (&(&obj->TreeInternal._pobj1[0])[0])[0].ChildToJointTransform[i] = iv[i];
  }
  (&(&obj->TreeInternal._pobj1[0])[0])[0].NameInternal.set_size(1, 14);
  for (int i{0}; i < 14; i++) {
    (&(&obj->TreeInternal._pobj1[0])[0])[0].NameInternal[i] = jname[i];
  }
  for (int i{0}; i < 5; i++) {
    jointtype_tmp_data[i] = b_cv[i];
  }
  (&(&obj->TreeInternal._pobj1[0])[0])[0].Type.set_size(1, 5);
  for (int i{0}; i < 5; i++) {
    (&(&obj->TreeInternal._pobj1[0])[0])[0].Type[i] = jointtype_tmp_data[i];
  }
  switch_expression.set_size(
      1, (&(&obj->TreeInternal._pobj1[0])[0])[0].Type.size(1));
  k = (&(&obj->TreeInternal._pobj1[0])[0])[0].Type.size(1);
  for (int i{0}; i < k; i++) {
    switch_expression[i] = (&(&obj->TreeInternal._pobj1[0])[0])[0].Type[i];
  }
  b_bool = false;
  if (switch_expression.size(1) == 8) {
    k = 0;
    do {
      exitg1 = 0;
      if (k < 8) {
        if (switch_expression[k] != b_cv1[k]) {
          exitg1 = 1;
        } else {
          k++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  if (b_bool) {
    k = 0;
  } else {
    b_bool = false;
    if (switch_expression.size(1) == 9) {
      k = 0;
      do {
        exitg1 = 0;
        if (k < 9) {
          if (switch_expression[k] != cv1[k]) {
            exitg1 = 1;
          } else {
            k++;
          }
        } else {
          b_bool = true;
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }
    if (b_bool) {
      k = 1;
    } else {
      k = -1;
    }
  }
  switch (k) {
  case 0:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = b_iv[i];
    }
    poslim_data[0] = -3.1415926535897931;
    poslim_data[1] = 3.1415926535897931;
    (&(&obj->TreeInternal._pobj1[0])[0])[0].VelocityNumber = 1.0;
    (&(&obj->TreeInternal._pobj1[0])[0])[0].PositionNumber = 1.0;
    (&(&obj->TreeInternal._pobj1[0])[0])[0].JointAxisInternal[0] = 0.0;
    (&(&obj->TreeInternal._pobj1[0])[0])[0].JointAxisInternal[1] = 0.0;
    (&(&obj->TreeInternal._pobj1[0])[0])[0].JointAxisInternal[2] = 1.0;
    break;
  case 1:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = b_iv1[i];
    }
    poslim_data[0] = -0.5;
    poslim_data[1] = 0.5;
    (&(&obj->TreeInternal._pobj1[0])[0])[0].VelocityNumber = 1.0;
    (&(&obj->TreeInternal._pobj1[0])[0])[0].PositionNumber = 1.0;
    (&(&obj->TreeInternal._pobj1[0])[0])[0].JointAxisInternal[0] = 0.0;
    (&(&obj->TreeInternal._pobj1[0])[0])[0].JointAxisInternal[1] = 0.0;
    (&(&obj->TreeInternal._pobj1[0])[0])[0].JointAxisInternal[2] = 1.0;
    break;
  default:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = 0;
    }
    poslim_data[0] = 0.0;
    poslim_data[1] = 0.0;
    (&(&obj->TreeInternal._pobj1[0])[0])[0].VelocityNumber = 0.0;
    (&(&obj->TreeInternal._pobj1[0])[0])[0].PositionNumber = 0.0;
    (&(&obj->TreeInternal._pobj1[0])[0])[0].JointAxisInternal[0] = 0.0;
    (&(&obj->TreeInternal._pobj1[0])[0])[0].JointAxisInternal[1] = 0.0;
    (&(&obj->TreeInternal._pobj1[0])[0])[0].JointAxisInternal[2] = 0.0;
    break;
  }
  (&(&obj->TreeInternal._pobj1[0])[0])[0].MotionSubspace.set_size(6, 1);
  for (int i{0}; i < 6; i++) {
    (&(&obj->TreeInternal._pobj1[0])[0])[0].MotionSubspace[i] =
        msubspace_data[i];
  }
  (&(&obj->TreeInternal._pobj1[0])[0])[0].PositionLimitsInternal.set_size(1, 2);
  for (int i{0}; i < 2; i++) {
    (&(&obj->TreeInternal._pobj1[0])[0])[0].PositionLimitsInternal[i] =
        poslim_data[i];
  }
  (&(&obj->TreeInternal._pobj1[0])[0])[0].HomePositionInternal.set_size(1);
  (&(&obj->TreeInternal._pobj1[0])[0])[0].HomePositionInternal[0] = 0.0;
  (&(&obj->TreeInternal._pobj2[0])[0])[1].JointInternal =
      &(&(&obj->TreeInternal._pobj1[0])[0])[0];
  (&(&obj->TreeInternal._pobj2[0])[0])[1].Index = -1.0;
  (&(&obj->TreeInternal._pobj2[0])[0])[1].ParentIndex = -1.0;
  for (int i{0}; i < 36; i++) {
    msubspace_data[i] = 0;
  }
  for (k = 0; k < 6; k++) {
    msubspace_data[k + 6 * k] = 1;
  }
  for (int i{0}; i < 36; i++) {
    (&(&obj->TreeInternal._pobj2[0])[0])[1].SpatialInertia[i] =
        msubspace_data[i];
  }
  (&(&obj->TreeInternal._pobj2[0])[0])[1].CollisionsInternal =
      (&(&obj->TreeInternal._pobj0[0])[0])[0].init(0.0);
  (&(&obj->TreeInternal._pobj2[0])[0])[1].matlabCodegenIsDeleted = false;
  obj->TreeInternal.Bodies[1] = &(&(&obj->TreeInternal._pobj2[0])[0])[1];
  (&(&obj->TreeInternal._pobj2[0])[0])[2].NameInternal.set_size(1, 10);
  for (int i{0}; i < 10; i++) {
    (&(&obj->TreeInternal._pobj2[0])[0])[2].NameInternal[i] = b_bname[i];
  }
  (&(&obj->TreeInternal._pobj1[0])[0])[1].InTree = false;
  for (int i{0}; i < 16; i++) {
    (&(&obj->TreeInternal._pobj1[0])[0])[1].JointToParentTransform[i] = iv[i];
  }
  for (int i{0}; i < 16; i++) {
    (&(&obj->TreeInternal._pobj1[0])[0])[1].ChildToJointTransform[i] = iv[i];
  }
  (&(&obj->TreeInternal._pobj1[0])[0])[1].NameInternal.set_size(1, 14);
  for (int i{0}; i < 14; i++) {
    (&(&obj->TreeInternal._pobj1[0])[0])[1].NameInternal[i] = b_jname[i];
  }
  (&(&obj->TreeInternal._pobj1[0])[0])[1].Type.set_size(1, 5);
  for (int i{0}; i < 5; i++) {
    (&(&obj->TreeInternal._pobj1[0])[0])[1].Type[i] = jointtype_tmp_data[i];
  }
  switch_expression.set_size(
      1, (&(&obj->TreeInternal._pobj1[0])[0])[1].Type.size(1));
  k = (&(&obj->TreeInternal._pobj1[0])[0])[1].Type.size(1);
  for (int i{0}; i < k; i++) {
    switch_expression[i] = (&(&obj->TreeInternal._pobj1[0])[0])[1].Type[i];
  }
  b_bool = false;
  if (switch_expression.size(1) == 8) {
    k = 0;
    do {
      exitg1 = 0;
      if (k < 8) {
        if (switch_expression[k] != b_cv1[k]) {
          exitg1 = 1;
        } else {
          k++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  if (b_bool) {
    k = 0;
  } else {
    b_bool = false;
    if (switch_expression.size(1) == 9) {
      k = 0;
      do {
        exitg1 = 0;
        if (k < 9) {
          if (switch_expression[k] != cv1[k]) {
            exitg1 = 1;
          } else {
            k++;
          }
        } else {
          b_bool = true;
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }
    if (b_bool) {
      k = 1;
    } else {
      k = -1;
    }
  }
  switch (k) {
  case 0:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = b_iv[i];
    }
    poslim_data[0] = -3.1415926535897931;
    poslim_data[1] = 3.1415926535897931;
    (&(&obj->TreeInternal._pobj1[0])[0])[1].VelocityNumber = 1.0;
    (&(&obj->TreeInternal._pobj1[0])[0])[1].PositionNumber = 1.0;
    (&(&obj->TreeInternal._pobj1[0])[0])[1].JointAxisInternal[0] = 0.0;
    (&(&obj->TreeInternal._pobj1[0])[0])[1].JointAxisInternal[1] = 0.0;
    (&(&obj->TreeInternal._pobj1[0])[0])[1].JointAxisInternal[2] = 1.0;
    break;
  case 1:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = b_iv1[i];
    }
    poslim_data[0] = -0.5;
    poslim_data[1] = 0.5;
    (&(&obj->TreeInternal._pobj1[0])[0])[1].VelocityNumber = 1.0;
    (&(&obj->TreeInternal._pobj1[0])[0])[1].PositionNumber = 1.0;
    (&(&obj->TreeInternal._pobj1[0])[0])[1].JointAxisInternal[0] = 0.0;
    (&(&obj->TreeInternal._pobj1[0])[0])[1].JointAxisInternal[1] = 0.0;
    (&(&obj->TreeInternal._pobj1[0])[0])[1].JointAxisInternal[2] = 1.0;
    break;
  default:
    for (int i{0}; i < 6; i++) {
      msubspace_data[i] = 0;
    }
    poslim_data[0] = 0.0;
    poslim_data[1] = 0.0;
    (&(&obj->TreeInternal._pobj1[0])[0])[1].VelocityNumber = 0.0;
    (&(&obj->TreeInternal._pobj1[0])[0])[1].PositionNumber = 0.0;
    (&(&obj->TreeInternal._pobj1[0])[0])[1].JointAxisInternal[0] = 0.0;
    (&(&obj->TreeInternal._pobj1[0])[0])[1].JointAxisInternal[1] = 0.0;
    (&(&obj->TreeInternal._pobj1[0])[0])[1].JointAxisInternal[2] = 0.0;
    break;
  }
  (&(&obj->TreeInternal._pobj1[0])[0])[1].MotionSubspace.set_size(6, 1);
  for (int i{0}; i < 6; i++) {
    (&(&obj->TreeInternal._pobj1[0])[0])[1].MotionSubspace[i] =
        msubspace_data[i];
  }
  (&(&obj->TreeInternal._pobj1[0])[0])[1].PositionLimitsInternal.set_size(1, 2);
  for (int i{0}; i < 2; i++) {
    (&(&obj->TreeInternal._pobj1[0])[0])[1].PositionLimitsInternal[i] =
        poslim_data[i];
  }
  (&(&obj->TreeInternal._pobj1[0])[0])[1].HomePositionInternal.set_size(1);
  (&(&obj->TreeInternal._pobj1[0])[0])[1].HomePositionInternal[0] = 0.0;
  (&(&obj->TreeInternal._pobj2[0])[0])[2].JointInternal =
      &(&(&obj->TreeInternal._pobj1[0])[0])[1];
  (&(&obj->TreeInternal._pobj2[0])[0])[2].Index = -1.0;
  (&(&obj->TreeInternal._pobj2[0])[0])[2].ParentIndex = -1.0;
  for (int i{0}; i < 36; i++) {
    msubspace_data[i] = 0;
  }
  for (k = 0; k < 6; k++) {
    msubspace_data[k + 6 * k] = 1;
  }
  for (int i{0}; i < 36; i++) {
    (&(&obj->TreeInternal._pobj2[0])[0])[2].SpatialInertia[i] =
        msubspace_data[i];
  }
  (&(&obj->TreeInternal._pobj2[0])[0])[2].CollisionsInternal =
      (&(&obj->TreeInternal._pobj0[0])[0])[1].init(0.0);
  (&(&obj->TreeInternal._pobj2[0])[0])[2].matlabCodegenIsDeleted = false;
  obj->TreeInternal.Bodies[2] = &(&(&obj->TreeInternal._pobj2[0])[0])[2];
  obj->TreeInternal.Bodies[3] = (&(&obj->TreeInternal._pobj2[0])[0])[3].init(
      (&(&obj->TreeInternal._pobj0[0])[0])[2],
      (&(&obj->TreeInternal._pobj1[0])[0])[2]);
  obj->TreeInternal.Bodies[4] = (&(&obj->TreeInternal._pobj2[0])[0])[4].b_init(
      (&(&obj->TreeInternal._pobj0[0])[0])[3],
      (&(&obj->TreeInternal._pobj1[0])[0])[3]);
  obj->TreeInternal.Bodies[5] = (&(&obj->TreeInternal._pobj2[0])[0])[5].c_init(
      (&(&obj->TreeInternal._pobj0[0])[0])[4],
      (&(&obj->TreeInternal._pobj1[0])[0])[4]);
  obj->TreeInternal.Bodies[6] = (&(&obj->TreeInternal._pobj2[0])[0])[6].d_init(
      (&(&obj->TreeInternal._pobj0[0])[0])[5],
      (&(&obj->TreeInternal._pobj1[0])[0])[5]);
  obj->TreeInternal.Bodies[7] = (&(&obj->TreeInternal._pobj2[0])[0])[7].e_init(
      (&(&obj->TreeInternal._pobj0[0])[0])[6],
      (&(&obj->TreeInternal._pobj1[0])[0])[6]);
  obj->TreeInternal.Bodies[8] = (&(&obj->TreeInternal._pobj2[0])[0])[8].f_init(
      (&(&obj->TreeInternal._pobj0[0])[0])[7],
      (&(&obj->TreeInternal._pobj1[0])[0])[7]);
  obj->TreeInternal.Bodies[9] = (&(&obj->TreeInternal._pobj2[0])[0])[9].g_init(
      (&(&obj->TreeInternal._pobj0[0])[0])[8],
      (&(&obj->TreeInternal._pobj1[0])[0])[8]);
  obj->TreeInternal.Bodies[10] =
      (&(&obj->TreeInternal._pobj2[0])[0])[10].h_init(
          (&(&obj->TreeInternal._pobj0[0])[0])[9],
          (&(&obj->TreeInternal._pobj1[0])[0])[9]);
  obj->TreeInternal.NumBodies = 0.0;
  obj->TreeInternal.NumNonFixedBodies = 0.0;
  obj->TreeInternal.PositionNumber = 0.0;
  obj->TreeInternal.VelocityNumber = 0.0;
  b_rand(unusedExpr);
  for (int i{0}; i < 22; i++) {
    obj->TreeInternal.PositionDoFMap[i] = iv2[i];
  }
  for (int i{0}; i < 22; i++) {
    obj->TreeInternal.VelocityDoFMap[i] = iv2[i];
  }
  obj->TreeInternal.matlabCodegenIsDeleted = false;
  obj->TreeInternal.Base.CollisionsInternal = obj->_pobj0.init(10.0);
  obj->matlabCodegenIsDeleted = false;
  return obj;
}

//
// Arguments    : void
// Return Type  : void
//
void rigidBodyTree::matlabCodegenDestructor()
{
  if (!matlabCodegenIsDeleted) {
    matlabCodegenIsDeleted = true;
  }
}

} // namespace coder

//
// File trailer for rigidBodyTree.cpp
//
// [EOF]
//
