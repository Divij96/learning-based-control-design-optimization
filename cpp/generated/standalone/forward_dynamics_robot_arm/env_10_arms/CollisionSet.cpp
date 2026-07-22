//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CollisionSet.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 02-Feb-2024 13:34:01
//

// Include Files
#include "CollisionSet.h"
#include "CollisionGeometry.h"
#include "forward_dynamics_robot_arm_data.h"
#include "rt_nonfinite.h"
#include "string1.h"
#include "coder_array.h"
#include "collisioncodegen_api.hpp"

// Function Definitions
//
// Arguments    : void
// Return Type  : CollisionSet
//
namespace coder {
namespace robotics {
namespace manip {
namespace internal {
CollisionSet::CollisionSet()
{
  matlabCodegenIsDeleted = true;
}

//
// Arguments    : void
// Return Type  : void
//
CollisionSet::~CollisionSet()
{
  matlabCodegenDestructor();
}

//
// Arguments    : double maxElements
// Return Type  : CollisionSet *
//
CollisionSet *CollisionSet::init(double maxElements)
{
  void *defaultCollisionObj_GeometryInternal;
  CollisionGeometry defaultGeometry;
  CollisionSet *obj;
  rtString r;
  int i;
  int size_tmp_idx_1;
  obj = this;
  obj->Size = 0.0;
  obj->MaxElements = maxElements;
  size_tmp_idx_1 = static_cast<int>(obj->MaxElements);
  obj->CollisionGeometries.set_size(1, size_tmp_idx_1);
  obj->Tags = r;
  defaultCollisionObj_GeometryInternal = nullptr;
  defaultGeometry.CollisionPrimitive = defaultCollisionObj_GeometryInternal;
  for (i = 0; i < 16; i++) {
    size_tmp_idx_1 = iv[i];
    defaultGeometry.LocalPose[i] = size_tmp_idx_1;
    defaultGeometry.WorldPose[i] = size_tmp_idx_1;
  }
  double d;
  d = obj->MaxElements;
  i = static_cast<int>(d);
  for (size_tmp_idx_1 = 0; size_tmp_idx_1 < i; size_tmp_idx_1++) {
    obj->CollisionGeometries[size_tmp_idx_1] = defaultGeometry;
  }
  obj->matlabCodegenIsDeleted = false;
  return obj;
}

//
// Arguments    : void
// Return Type  : void
//
void CollisionSet::matlabCodegenDestructor()
{
  if (!matlabCodegenIsDeleted) {
    int i;
    matlabCodegenIsDeleted = true;
    i = static_cast<int>(Size);
    for (int b_i{0}; b_i < i; b_i++) {
      collisioncodegen_destructGeometry(
          &CollisionGeometries[b_i].CollisionPrimitive);
    }
  }
}

} // namespace internal
} // namespace manip
} // namespace robotics
} // namespace coder

//
// File trailer for CollisionSet.cpp
//
// [EOF]
//
