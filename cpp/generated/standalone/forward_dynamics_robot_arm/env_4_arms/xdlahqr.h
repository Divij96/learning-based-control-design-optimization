//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: xdlahqr.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 05-Feb-2024 13:57:11
//

#ifndef XDLAHQR_H
#define XDLAHQR_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
namespace reflapack {
int xdlahqr(int ilo, int ihi, double h[9], double &z, double wr[3],
            double wi[3]);

}
} // namespace internal
} // namespace coder

#endif
//
// File trailer for xdlahqr.h
//
// [EOF]
//
