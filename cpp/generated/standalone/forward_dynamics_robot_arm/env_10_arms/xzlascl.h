//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: xzlascl.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 02-Feb-2024 13:34:01
//

#ifndef XZLASCL_H
#define XZLASCL_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
namespace reflapack {
void b_xzlascl(double cfrom, double cto, int m, double A[2], int iA0);

void xzlascl(double cfrom, double cto, int m, double A[3], int iA0);

void xzlascl(double cfrom, double cto, double A[9]);

} // namespace reflapack
} // namespace internal
} // namespace coder

#endif
//
// File trailer for xzlascl.h
//
// [EOF]
//
