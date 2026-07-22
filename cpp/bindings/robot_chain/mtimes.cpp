//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: mtimes.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 12-Dec-2023 16:05:32
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
void b_mtimes(const ::coder::array<double, 2U> &A,
              const ::coder::array<double, 2U> &B,
              ::coder::array<double, 2U> &C)
{
  int m;
  int n;
  m = A.size(0);
  n = B.size(1);
  C.set_size(A.size(0), B.size(1));
  for (int j{0}; j < n; j++) {
    int boffset;
    int coffset;
    coffset = j * m;
    boffset = j * 6;
    for (int i{0}; i < m; i++) {
      double s;
      s = 0.0;
      for (int k{0}; k < 6; k++) {
        s += A[k * A.size(0) + i] * B[boffset + k];
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
      s = 0.0;
      for (int k{0}; k < 6; k++) {
        s += A[k * 6 + i] * B[coffset_tmp + k];
      }
      C[coffset_tmp + i] = s;
    }
  }
}

//
// Arguments    : const ::coder::array<double, 2U> &A
//                const ::coder::array<double, 2U> &B
//                ::coder::array<double, 2U> &C
// Return Type  : void
//
void mtimes(const ::coder::array<double, 2U> &A,
            const ::coder::array<double, 2U> &B, ::coder::array<double, 2U> &C)
{
  int m;
  m = A.size(1);
  C.set_size(A.size(1), 6);
  for (int j{0}; j < 6; j++) {
    int boffset;
    int coffset;
    coffset = j * m;
    boffset = j * B.size(0);
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
// Arguments    : const ::coder::array<double, 2U> &A
//                const double B[36]
//                ::coder::array<double, 2U> &C
// Return Type  : void
//
void mtimes(const ::coder::array<double, 2U> &A, const double B[36],
            ::coder::array<double, 2U> &C)
{
  int m;
  m = A.size(1);
  C.set_size(A.size(1), 6);
  for (int j{0}; j < 6; j++) {
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
// Arguments    : const ::coder::array<double, 2U> &A
//                const ::coder::array<double, 1U> &B
//                ::coder::array<double, 1U> &C
// Return Type  : void
//
void mtimes(const ::coder::array<double, 2U> &A,
            const ::coder::array<double, 1U> &B, ::coder::array<double, 1U> &C)
{
  int inner;
  int mc;
  mc = A.size(0) - 1;
  inner = A.size(1);
  C.set_size(A.size(0));
  for (int i{0}; i <= mc; i++) {
    C[i] = 0.0;
  }
  for (int k{0}; k < inner; k++) {
    int aoffset;
    aoffset = k * A.size(0);
    for (int i{0}; i <= mc; i++) {
      C[i] = C[i] + A[aoffset + i] * B[k];
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
