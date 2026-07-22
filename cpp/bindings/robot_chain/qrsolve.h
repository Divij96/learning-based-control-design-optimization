//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: qrsolve.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 12-Dec-2023 16:05:32
//

#ifndef QRSOLVE_H
#define QRSOLVE_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
void qrsolve(const ::coder::array<double, 2U> &A,
             const ::coder::array<double, 1U> &B,
             ::coder::array<double, 1U> &Y);

}
} // namespace coder

#endif
//
// File trailer for qrsolve.h
//
// [EOF]
//
