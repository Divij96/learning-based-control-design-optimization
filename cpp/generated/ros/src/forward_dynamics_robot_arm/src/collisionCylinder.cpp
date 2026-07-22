//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: collisionCylinder.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 02-Feb-2024 13:34:01
//

// Include Files
#include "collisionCylinder.h"
#include "rt_nonfinite.h"
#include "collisioncodegen_api.hpp"

// Function Definitions
//
// Arguments    : void
// Return Type  : collisionCylinder
//
namespace coder {
collisionCylinder::collisionCylinder()
{
  matlabCodegenIsDeleted = true;
}

//
// Arguments    : void
// Return Type  : void
//
collisionCylinder::~collisionCylinder()
{
  matlabCodegenDestructor();
}

//
// Arguments    : void
// Return Type  : void
//
void collisionCylinder::matlabCodegenDestructor()
{
  if (!matlabCodegenIsDeleted) {
    matlabCodegenIsDeleted = true;
    collisioncodegen_destructGeometry(&GeometryInternal);
  }
}

} // namespace coder

//
// File trailer for collisionCylinder.cpp
//
// [EOF]
//
