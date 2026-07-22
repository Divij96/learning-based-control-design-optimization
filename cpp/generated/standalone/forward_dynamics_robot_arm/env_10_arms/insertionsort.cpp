//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: insertionsort.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 02-Feb-2024 13:34:01
//

// Include Files
#include "insertionsort.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// Arguments    : double x[3]
// Return Type  : void
//
namespace coder {
namespace internal {
void insertionsort(double x[3])
{
  for (int k{2}; k < 4; k++) {
    double xc;
    int idx;
    boolean_T exitg1;
    xc = x[k - 1];
    idx = k - 1;
    exitg1 = false;
    while ((!exitg1) && (idx >= 1)) {
      double d;
      d = x[idx - 1];
      if (xc < d) {
        x[idx] = d;
        idx--;
      } else {
        exitg1 = true;
      }
    }
    x[idx] = xc;
  }
}

} // namespace internal
} // namespace coder

//
// File trailer for insertionsort.cpp
//
// [EOF]
//
