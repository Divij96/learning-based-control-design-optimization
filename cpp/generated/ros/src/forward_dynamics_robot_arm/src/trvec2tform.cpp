//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: trvec2tform.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 02-Feb-2024 13:34:01
//

// Include Files
#include "trvec2tform.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// Arguments    : const double t[3]
//                double H[16]
// Return Type  : void
//
namespace coder {
void trvec2tform(const double t[3], double H[16])
{
  signed char b_I[16];
  for (int jcol{0}; jcol < 16; jcol++) {
    b_I[jcol] = 0;
  }
  b_I[0] = 1;
  b_I[5] = 1;
  b_I[10] = 1;
  b_I[15] = 1;
  for (int jcol{0}; jcol < 4; jcol++) {
    int iacol_tmp;
    iacol_tmp = jcol << 2;
    H[iacol_tmp] = b_I[iacol_tmp];
    H[iacol_tmp + 1] = b_I[iacol_tmp + 1];
    H[iacol_tmp + 2] = b_I[iacol_tmp + 2];
    H[iacol_tmp + 3] = b_I[iacol_tmp + 3];
  }
  H[12] = t[0];
  H[13] = t[1];
  H[14] = t[2];
}

} // namespace coder

//
// File trailer for trvec2tform.cpp
//
// [EOF]
//
