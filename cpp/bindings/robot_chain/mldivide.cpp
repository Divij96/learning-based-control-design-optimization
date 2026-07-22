//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: mldivide.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 12-Dec-2023 16:05:32
//

// Include Files
#include "mldivide.h"
#include "qrsolve.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &A
//                ::coder::array<double, 1U> &B
// Return Type  : void
//
namespace coder {
void mldivide(const ::coder::array<double, 2U> &A,
              ::coder::array<double, 1U> &B)
{
  array<double, 2U> b_A;
  array<double, 1U> b_B;
  array<int, 2U> ipiv;
  if (A.size(0) == A.size(1)) {
    double smax;
    int LDA;
    int i;
    int n;
    int temp_tmp;
    int u0;
    int yk;
    u0 = A.size(0);
    n = A.size(1);
    if (u0 <= n) {
      n = u0;
    }
    u0 = B.size(0);
    if (u0 <= n) {
      n = u0;
    }
    LDA = A.size(0);
    b_A.set_size(A.size(0), A.size(1));
    yk = A.size(0) * A.size(1);
    for (i = 0; i < yk; i++) {
      b_A[i] = A[i];
    }
    ipiv.set_size(1, n);
    ipiv[0] = 1;
    yk = 1;
    for (int k{2}; k <= n; k++) {
      yk++;
      ipiv[k - 1] = yk;
    }
    u0 = n - 1;
    if (u0 > n) {
      u0 = n;
    }
    for (int j{0}; j < u0; j++) {
      int b_tmp;
      int jA;
      int jp1j;
      int mmj_tmp;
      mmj_tmp = n - j;
      b_tmp = j * (LDA + 1);
      jp1j = b_tmp + 2;
      if (mmj_tmp < 1) {
        yk = -1;
      } else {
        yk = 0;
        if (mmj_tmp > 1) {
          smax = std::abs(b_A[b_tmp]);
          for (int k{2}; k <= mmj_tmp; k++) {
            double s;
            s = std::abs(b_A[(b_tmp + k) - 1]);
            if (s > smax) {
              yk = k - 1;
              smax = s;
            }
          }
        }
      }
      if (b_A[b_tmp + yk] != 0.0) {
        if (yk != 0) {
          jA = j + yk;
          ipiv[j] = jA + 1;
          for (int k{0}; k < n; k++) {
            yk = k * LDA;
            temp_tmp = j + yk;
            smax = b_A[temp_tmp];
            i = jA + yk;
            b_A[temp_tmp] = b_A[i];
            b_A[i] = smax;
          }
        }
        i = b_tmp + mmj_tmp;
        for (temp_tmp = jp1j; temp_tmp <= i; temp_tmp++) {
          b_A[temp_tmp - 1] = b_A[temp_tmp - 1] / b_A[b_tmp];
        }
      }
      yk = b_tmp + LDA;
      jA = yk;
      for (jp1j = 0; jp1j <= mmj_tmp - 2; jp1j++) {
        smax = b_A[yk + jp1j * LDA];
        if (smax != 0.0) {
          i = jA + 2;
          temp_tmp = mmj_tmp + jA;
          for (int k{i}; k <= temp_tmp; k++) {
            b_A[k - 1] = b_A[k - 1] + b_A[((b_tmp + k) - jA) - 1] * -smax;
          }
        }
        jA += LDA;
      }
    }
    LDA = b_A.size(0);
    for (temp_tmp = 0; temp_tmp <= n - 2; temp_tmp++) {
      i = ipiv[temp_tmp];
      if (i != temp_tmp + 1) {
        smax = B[temp_tmp];
        B[temp_tmp] = B[i - 1];
        B[i - 1] = smax;
      }
    }
    for (int k{0}; k < n; k++) {
      yk = LDA * k;
      if (B[k] != 0.0) {
        i = k + 2;
        for (temp_tmp = i; temp_tmp <= n; temp_tmp++) {
          B[temp_tmp - 1] = B[temp_tmp - 1] - B[k] * b_A[(temp_tmp + yk) - 1];
        }
      }
    }
    for (int k{n}; k >= 1; k--) {
      yk = LDA * (k - 1);
      smax = B[k - 1];
      if (smax != 0.0) {
        smax /= b_A[(k + yk) - 1];
        B[k - 1] = smax;
        for (temp_tmp = 0; temp_tmp <= k - 2; temp_tmp++) {
          B[temp_tmp] = B[temp_tmp] - B[k - 1] * b_A[temp_tmp + yk];
        }
      }
    }
  } else {
    int yk;
    b_B.set_size(B.size(0));
    yk = B.size(0) - 1;
    for (int i{0}; i <= yk; i++) {
      b_B[i] = B[i];
    }
    internal::qrsolve(A, b_B, B);
  }
}

} // namespace coder

//
// File trailer for mldivide.cpp
//
// [EOF]
//
