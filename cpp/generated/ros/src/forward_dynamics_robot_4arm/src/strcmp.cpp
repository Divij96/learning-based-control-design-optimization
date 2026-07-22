//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: strcmp.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 05-Feb-2024 13:57:11
//

// Include Files
#include "strcmp.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<char, 2U> &a
//                const ::coder::array<char, 2U> &b
// Return Type  : boolean_T
//
namespace coder {
namespace internal {
boolean_T b_strcmp(const ::coder::array<char, 2U> &a,
                   const ::coder::array<char, 2U> &b)
{
  boolean_T b_b;
  boolean_T b_bool;
  b_bool = false;
  b_b = (a.size(1) == 0);
  if (b_b && (b.size(1) == 0)) {
    b_bool = true;
  } else if (a.size(1) == b.size(1)) {
    int kstr;
    kstr = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (kstr <= b.size(1) - 1) {
        if (a[kstr] != b[kstr]) {
          exitg1 = 1;
        } else {
          kstr++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  return b_bool;
}

} // namespace internal
} // namespace coder

//
// File trailer for strcmp.cpp
//
// [EOF]
//
