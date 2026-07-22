//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CollisionGeometry.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 14-Feb-2024 19:42:36
//

#ifndef COLLISIONGEOMETRY_H
#define COLLISIONGEOMETRY_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder {
namespace robotics {
namespace manip {
namespace internal {
class CollisionGeometry {
public:
  void *CollisionPrimitive;
  double LocalPose[16];
  double WorldPose[16];
};

} // namespace internal
} // namespace manip
} // namespace robotics
} // namespace coder

#endif
//
// File trailer for CollisionGeometry.h
//
// [EOF]
//
