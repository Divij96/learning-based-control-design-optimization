//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: RigidBodyTree1.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 02-Feb-2024 13:34:01
//

// Include Files
#include "RigidBodyTree1.h"
#include "RigidBody.h"
#include "rt_nonfinite.h"
#include "strcmp.h"
#include "coder_array.h"

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

} // namespace internal
} // namespace manip
} // namespace robotics
} // namespace coder

//
// File trailer for RigidBodyTree1.cpp
//
// [EOF]
//
