//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: RigidBodyTreeDynamics.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 05-Feb-2024 13:57:11
//

#ifndef RIGIDBODYTREEDYNAMICS_H
#define RIGIDBODYTREEDYNAMICS_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <algorithm>
#include <cstddef>
#include <cstdlib>

// Type Declarations
namespace coder {
namespace robotics {
namespace manip {
namespace internal {
class RigidBodyTree;

}
} // namespace manip
} // namespace robotics
} // namespace coder

// Type Definitions
namespace coder {
namespace robotics {
namespace manip {
namespace internal {
class RigidBodyTreeDynamics {
public:
  static void massMatrix(RigidBodyTree &robot, const double q_data[],
                         ::coder::array<double, 2U> &H,
                         ::coder::array<double, 2U> &lambda);
  static int inverseDynamics(RigidBodyTree &robot, const double q_data[],
                             const double qdot_data[],
                             const ::coder::array<double, 2U> &fext,
                             double tau_data[]);
};

} // namespace internal
} // namespace manip
} // namespace robotics
} // namespace coder

#endif
//
// File trailer for RigidBodyTreeDynamics.h
//
// [EOF]
//
