//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: mtimes.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 14-Feb-2024 19:42:36
//

// Include Files
#include "mtimes.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &A
//                const ::coder::array<double, 2U> &B
//                ::coder::array<double, 2U> &C
// Return Type  : void
//
namespace coder {
namespace internal {
namespace blas {
void mtimes(const ::coder::array<double, 2U> &A,
            const ::coder::array<double, 2U> &B, ::coder::array<double, 2U> &C)
{
  int m;
  int n;
  m = A.size(1);
  n = B.size(1);
  C.set_size(A.size(1), B.size(1));
  for (int j{0}; j < n; j++) {
    int boffset;
    int coffset;
    coffset = j * m;
    boffset = j * 6;
    for (int i{0}; i < m; i++) {
      double s;
      int aoffset;
      aoffset = i * 6;
      s = 0.0;
      for (int k{0}; k < 6; k++) {
        s += A[aoffset + k] * B[boffset + k];
      }
      C[coffset + i] = s;
    }
  }
}

//
// Arguments    : const double A[36]
//                const ::coder::array<double, 2U> &B
//                ::coder::array<double, 2U> &C
// Return Type  : void
//
void mtimes(const double A[36], const ::coder::array<double, 2U> &B,
            ::coder::array<double, 2U> &C)
{
  int n;
  n = B.size(1);
  C.set_size(6, B.size(1));
  for (int j{0}; j < n; j++) {
    int coffset_tmp;
    coffset_tmp = j * 6;
    for (int i{0}; i < 6; i++) {
      double s;
      int aoffset;
      aoffset = i * 6;
      s = 0.0;
      for (int k{0}; k < 6; k++) {
        s += A[aoffset + k] * B[coffset_tmp + k];
      }
      C[coffset_tmp + i] = s;
    }
  }
}

} // namespace blas
} // namespace internal
} // namespace coder

//
// File trailer for mtimes.cpp
//
// [EOF]
//
