//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: RigidBodyTree1.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 14-Feb-2024 19:42:36
//

// Include Files
#include "RigidBodyTree1.h"
#include "CollisionSet.h"
#include "RigidBody.h"
#include "forward_dynamics_robot_6arm_data.h"
#include "forward_dynamics_robot_6arm_internal_types.h"
#include "rand.h"
#include "rigidBodyJoint.h"
#include "rt_nonfinite.h"
#include "strcmp.h"
#include "coder_array.h"
#include <algorithm>

// Function Definitions
//
// Arguments    : void
// Return Type  : b_RigidBodyTree
//
namespace coder {
namespace robotics {
namespace manip {
namespace internal {
b_RigidBodyTree::b_RigidBodyTree()
{
  matlabCodegenIsDeleted = true;
}

//
// Arguments    : void
// Return Type  : RigidBodyTree
//
RigidBodyTree::RigidBodyTree()
{
  matlabCodegenIsDeleted = true;
}

//
// Arguments    : void
// Return Type  : void
//
b_RigidBodyTree::~b_RigidBodyTree()
{
  matlabCodegenDestructor();
}

//
// Arguments    : void
// Return Type  : void
//
RigidBodyTree::~RigidBodyTree()
{
  matlabCodegenDestructor();
}

//
// Arguments    : const ::coder::array<char, 2U> &bodyname
// Return Type  : double
//
double
b_RigidBodyTree::findBodyIndexByName(const ::coder::array<char, 2U> &bodyname)
{
  b_RigidBody *obj;
  array<char, 2U> bname;
  double bid;
  int loop_ub;
  bid = -1.0;
  bname.set_size(1, Base.NameInternal.size(1));
  loop_ub = Base.NameInternal.size(1);
  for (int i{0}; i < loop_ub; i++) {
    bname[i] = Base.NameInternal[i];
  }
  if (::coder::internal::b_strcmp(bname, bodyname)) {
    bid = 0.0;
  } else {
    double d;
    int b_i;
    boolean_T exitg1;
    d = NumBodies;
    b_i = 0;
    exitg1 = false;
    while ((!exitg1) && (b_i <= static_cast<int>(d) - 1)) {
      obj = Bodies[b_i];
      bname.set_size(1, obj->NameInternal.size(1));
      loop_ub = obj->NameInternal.size(1);
      for (int i{0}; i < loop_ub; i++) {
        bname[i] = obj->NameInternal[i];
      }
      if (::coder::internal::b_strcmp(bname, bodyname)) {
        bid = static_cast<double>(b_i) + 1.0;
        exitg1 = true;
      } else {
        b_i++;
      }
    }
  }
  return bid;
}

//
// Arguments    : const double qvec[6]
//                ::coder::array<cell_wrap_33, 2U> &Ttree
// Return Type  : void
//
void b_RigidBodyTree::forwardKinematics(const double qvec[6],
                                        ::coder::array<cell_wrap_33, 2U> &Ttree)
{
  b_RigidBody *body;
  double a[16];
  double k;
  double n;
  int i;
  int i1;
  int jtilecol;
  n = NumBodies;
  i = static_cast<int>(n);
  Ttree.set_size(1, i);
  if (static_cast<int>(n) != 0) {
    for (jtilecol = 0; jtilecol < i; jtilecol++) {
      for (i1 = 0; i1 < 16; i1++) {
        Ttree[jtilecol].f1[i1] = iv[i1];
      }
    }
  }
  k = 1.0;
  for (int b_i{0}; b_i < i; b_i++) {
    double qvec_data[6];
    int i2;
    body = Bodies[b_i];
    n = body->JointInternal->PositionNumber;
    n += k;
    if (k > n - 1.0) {
      i1 = 0;
      i2 = 0;
    } else {
      i1 = static_cast<int>(k) - 1;
      i2 = static_cast<int>(n - 1.0);
    }
    jtilecol = i2 - i1;
    for (i2 = 0; i2 < jtilecol; i2++) {
      qvec_data[i2] = qvec[i1 + i2];
    }
    body->JointInternal->transformBodyToParent(qvec_data, jtilecol, a);
    ::std::copy(&a[0], &a[16], &Ttree[b_i].f1[0]);
    k = n;
    if (body->ParentIndex > 0.0) {
      double b_a[16];
      for (i1 = 0; i1 < 16; i1++) {
        a[i1] = Ttree[static_cast<int>(body->ParentIndex) - 1].f1[i1];
      }
      for (i1 = 0; i1 < 4; i1++) {
        double d;
        double d1;
        double d2;
        n = a[i1];
        d = a[i1 + 4];
        d1 = a[i1 + 8];
        d2 = a[i1 + 12];
        for (i2 = 0; i2 < 4; i2++) {
          jtilecol = i2 << 2;
          b_a[i1 + jtilecol] =
              ((n * Ttree[b_i].f1[jtilecol] + d * Ttree[b_i].f1[jtilecol + 1]) +
               d1 * Ttree[b_i].f1[jtilecol + 2]) +
              d2 * Ttree[b_i].f1[jtilecol + 3];
        }
      }
      for (i1 = 0; i1 < 16; i1++) {
        Ttree[b_i].f1[i1] = b_a[i1];
      }
    }
  }
}

//
// Arguments    : void
// Return Type  : RigidBodyTree *
//
RigidBodyTree *RigidBodyTree::init()
{
  RigidBodyTree *obj;
  double unusedExpr[5];
  signed char c_I[36];
  signed char b_I[9];
  obj = this;
  obj->Base.NameInternal.set_size(1, 4);
  obj->Base.NameInternal[0] = 'b';
  obj->Base.NameInternal[1] = 'a';
  obj->Base.NameInternal[2] = 's';
  obj->Base.NameInternal[3] = 'e';
  obj->Base.JointInternal = obj->_pobj2[0].init();
  obj->Base.Index = -1.0;
  obj->Base.MassInternal = 1.0;
  obj->Base.CenterOfMassInternal[0] = 0.0;
  obj->Base.CenterOfMassInternal[1] = 0.0;
  obj->Base.CenterOfMassInternal[2] = 0.0;
  for (int k{0}; k < 9; k++) {
    b_I[k] = 0;
  }
  b_I[0] = 1;
  b_I[4] = 1;
  b_I[8] = 1;
  for (int k{0}; k < 9; k++) {
    obj->Base.InertiaInternal[k] = b_I[k];
  }
  for (int k{0}; k < 36; k++) {
    c_I[k] = 0;
  }
  for (int k{0}; k < 6; k++) {
    c_I[k + 6 * k] = 1;
  }
  for (int k{0}; k < 36; k++) {
    obj->Base.SpatialInertia[k] = c_I[k];
  }
  obj->Base.CollisionsInternal = obj->_pobj1[0].init(0.0);
  obj->Base.matlabCodegenIsDeleted = false;
  obj->Base.Index = 0.0;
  b_rand(unusedExpr);
  obj->_pobj0.NameInternal.set_size(1, 10);
  for (int k{0}; k < 10; k++) {
    obj->_pobj0.NameInternal[k] = cv[k];
  }
  obj->_pobj0.JointInternal = obj->_pobj2[1].b_init();
  obj->_pobj0.Index = -1.0;
  obj->_pobj0.MassInternal = 1.0;
  obj->_pobj0.CenterOfMassInternal[0] = 0.0;
  obj->_pobj0.CenterOfMassInternal[1] = 0.0;
  obj->_pobj0.CenterOfMassInternal[2] = 0.0;
  for (int k{0}; k < 9; k++) {
    b_I[k] = 0;
  }
  b_I[0] = 1;
  b_I[4] = 1;
  b_I[8] = 1;
  for (int k{0}; k < 9; k++) {
    obj->_pobj0.InertiaInternal[k] = b_I[k];
  }
  for (int k{0}; k < 36; k++) {
    c_I[k] = 0;
  }
  for (int k{0}; k < 6; k++) {
    c_I[k + 6 * k] = 1;
  }
  for (int k{0}; k < 36; k++) {
    obj->_pobj0.SpatialInertia[k] = c_I[k];
  }
  obj->_pobj0.CollisionsInternal = obj->_pobj1[1].init(0.0);
  obj->_pobj0.matlabCodegenIsDeleted = false;
  obj->Bodies[0] = &obj->_pobj0;
  b_rand(unusedExpr);
  obj->matlabCodegenIsDeleted = false;
  return obj;
}

//
// Arguments    : void
// Return Type  : void
//
void b_RigidBodyTree::matlabCodegenDestructor()
{
  if (!matlabCodegenIsDeleted) {
    matlabCodegenIsDeleted = true;
  }
}

//
// Arguments    : void
// Return Type  : void
//
void RigidBodyTree::matlabCodegenDestructor()
{
  if (!matlabCodegenIsDeleted) {
    matlabCodegenIsDeleted = true;
  }
}

//
// Arguments    : const char bodyname[6]
// Return Type  : double
//
double b_RigidBodyTree::validateInputBodyName(const char bodyname[6])
{
  b_RigidBody *obj;
  array<char, 2U> bname;
  double bid;
  int exitg1;
  int loop_ub;
  boolean_T b_bool;
  bid = -1.0;
  bname.set_size(1, Base.NameInternal.size(1));
  loop_ub = Base.NameInternal.size(1);
  for (int i{0}; i < loop_ub; i++) {
    bname[i] = Base.NameInternal[i];
  }
  b_bool = false;
  if (bname.size(1) == 6) {
    loop_ub = 0;
    do {
      exitg1 = 0;
      if (loop_ub < 6) {
        if (bname[loop_ub] != bodyname[loop_ub]) {
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
    bid = 0.0;
  } else {
    double d;
    int b_i;
    boolean_T exitg2;
    d = NumBodies;
    b_i = 0;
    exitg2 = false;
    while ((!exitg2) && (b_i <= static_cast<int>(d) - 1)) {
      obj = Bodies[b_i];
      bname.set_size(1, obj->NameInternal.size(1));
      loop_ub = obj->NameInternal.size(1);
      for (int i{0}; i < loop_ub; i++) {
        bname[i] = obj->NameInternal[i];
      }
      b_bool = false;
      if (bname.size(1) == 6) {
        loop_ub = 0;
        do {
          exitg1 = 0;
          if (loop_ub < 6) {
            if (bname[loop_ub] != bodyname[loop_ub]) {
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
        bid = static_cast<double>(b_i) + 1.0;
        exitg2 = true;
      } else {
        b_i++;
      }
    }
  }
  return bid;
}

} // namespace internal
} // namespace manip
} // namespace robotics
} // namespace coder

//
// File trailer for RigidBodyTree1.cpp
//
// [EOF]
//
