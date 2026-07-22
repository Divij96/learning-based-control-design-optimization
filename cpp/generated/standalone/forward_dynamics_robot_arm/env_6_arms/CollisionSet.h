//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CollisionSet.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 14-Feb-2024 19:42:36
//

#ifndef COLLISIONSET_H
#define COLLISIONSET_H

// Include Files
#include "CollisionGeometry.h"
#include "rtwtypes.h"
#include "string1.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder {
namespace robotics {
namespace manip {
namespace internal {
class CollisionSet {
public:
  CollisionSet *init(double maxElements);
  void matlabCodegenDestructor();
  ~CollisionSet();
  CollisionSet();
  boolean_T matlabCodegenIsDeleted;
  array<CollisionGeometry, 2U> CollisionGeometries;
  double MaxElements;
  double Size;
  rtString Tags;
};

} // namespace internal
} // namespace manip
} // namespace robotics
} // namespace coder

#endif
//
// File trailer for CollisionSet.h
//
// [EOF]
//
