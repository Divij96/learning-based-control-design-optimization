//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: axang2tform.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 05-Feb-2024 13:57:11
//

// Include Files
#include "axang2tform.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <cstring>

// Function Definitions
//
// Arguments    : const double axang[4]
//                double H[16]
// Return Type  : void
//
namespace coder {
void axang2tform(const double axang[4], double H[16])
{
  double R[9];
  double tempR[9];
  double b_tempR_tmp;
  double c_tempR_tmp;
  double cth;
  double d_tempR_tmp;
  double e_tempR_tmp;
  double f_tempR_tmp;
  double g_tempR_tmp;
  double h_tempR_tmp;
  double sth;
  double tempR_tmp;
  double v_idx_0;
  double v_idx_1;
  double v_idx_2;
  sth = 1.0 / std::sqrt((axang[0] * axang[0] + axang[1] * axang[1]) +
                        axang[2] * axang[2]);
  v_idx_0 = axang[0] * sth;
  v_idx_1 = axang[1] * sth;
  v_idx_2 = axang[2] * sth;
  cth = std::cos(axang[3]);
  sth = std::sin(axang[3]);
  tempR_tmp = v_idx_0 * v_idx_0 * (1.0 - cth) + cth;
  tempR[0] = tempR_tmp;
  b_tempR_tmp = v_idx_0 * v_idx_1 * (1.0 - cth);
  c_tempR_tmp = v_idx_2 * sth;
  d_tempR_tmp = b_tempR_tmp - c_tempR_tmp;
  tempR[1] = d_tempR_tmp;
  e_tempR_tmp = v_idx_0 * v_idx_2 * (1.0 - cth);
  f_tempR_tmp = v_idx_1 * sth;
  g_tempR_tmp = e_tempR_tmp + f_tempR_tmp;
  tempR[2] = g_tempR_tmp;
  b_tempR_tmp += c_tempR_tmp;
  tempR[3] = b_tempR_tmp;
  c_tempR_tmp = v_idx_1 * v_idx_1 * (1.0 - cth) + cth;
  tempR[4] = c_tempR_tmp;
  h_tempR_tmp = v_idx_1 * v_idx_2 * (1.0 - cth);
  sth *= v_idx_0;
  v_idx_1 = h_tempR_tmp - sth;
  tempR[5] = v_idx_1;
  e_tempR_tmp -= f_tempR_tmp;
  tempR[6] = e_tempR_tmp;
  f_tempR_tmp = h_tempR_tmp + sth;
  tempR[7] = f_tempR_tmp;
  h_tempR_tmp = v_idx_2 * v_idx_2 * (1.0 - cth) + cth;
  tempR[8] = h_tempR_tmp;
  R[0] = tempR_tmp;
  R[1] = d_tempR_tmp;
  R[2] = g_tempR_tmp;
  R[3] = b_tempR_tmp;
  R[4] = c_tempR_tmp;
  R[5] = v_idx_1;
  R[6] = e_tempR_tmp;
  R[7] = f_tempR_tmp;
  R[8] = h_tempR_tmp;
  for (int k{0}; k < 3; k++) {
    R[k] = tempR[3 * k];
    R[k + 3] = tempR[3 * k + 1];
    R[k + 6] = tempR[3 * k + 2];
  }
  std::memset(&H[0], 0, 16U * sizeof(double));
  for (int k{0}; k < 3; k++) {
    int H_tmp;
    H_tmp = k << 2;
    H[H_tmp] = R[3 * k];
    H[H_tmp + 1] = R[3 * k + 1];
    H[H_tmp + 2] = R[3 * k + 2];
  }
  H[15] = 1.0;
}

} // namespace coder

//
// File trailer for axang2tform.cpp
//
// [EOF]
//
