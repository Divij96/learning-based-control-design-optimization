//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: svd.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 14-Feb-2024 19:42:36
//

// Include Files
#include "svd.h"
#include "rt_nonfinite.h"
#include "xnrm2.h"
#include "xrotg.h"
#include <algorithm>
#include <cmath>

// Function Definitions
//
// Arguments    : const double A[9]
//                double U[3]
// Return Type  : void
//
namespace coder {
namespace internal {
void svd(const double A[9], double U[3])
{
  double b_A[9];
  double e[3];
  double s[3];
  double work[3];
  double absxk;
  double nrm;
  double scale;
  double snorm;
  double sqds;
  double t;
  int ii;
  int iter;
  int m;
  int nmqp1_tmp;
  int qp1;
  int qq;
  int qs;
  ::std::copy(&A[0], &A[9], &b_A[0]);
  s[0] = 0.0;
  e[0] = 0.0;
  work[0] = 0.0;
  s[1] = 0.0;
  e[1] = 0.0;
  work[1] = 0.0;
  s[2] = 0.0;
  e[2] = 0.0;
  work[2] = 0.0;
  for (int q{0}; q < 2; q++) {
    boolean_T apply_transform;
    qp1 = q + 2;
    iter = q + 3 * q;
    qq = iter + 1;
    nmqp1_tmp = 2 - q;
    apply_transform = false;
    nrm = blas::xnrm2(3 - q, b_A, iter + 1);
    if (nrm > 0.0) {
      apply_transform = true;
      if (b_A[iter] < 0.0) {
        t = -nrm;
      } else {
        t = nrm;
      }
      s[q] = t;
      if (std::abs(t) >= 1.0020841800044864E-292) {
        nrm = 1.0 / t;
        qs = (iter - q) + 3;
        for (int k{qq}; k <= qs; k++) {
          b_A[k - 1] *= nrm;
        }
      } else {
        qs = (iter - q) + 3;
        for (int k{qq}; k <= qs; k++) {
          b_A[k - 1] /= s[q];
        }
      }
      b_A[iter]++;
      s[q] = -s[q];
    } else {
      s[q] = 0.0;
    }
    for (m = qp1; m < 4; m++) {
      qq = q + 3 * (m - 1);
      if (apply_transform) {
        t = 0.0;
        for (int k{0}; k <= nmqp1_tmp; k++) {
          t += b_A[iter + k] * b_A[qq + k];
        }
        nrm = -(t / b_A[iter]);
        if (!(nrm == 0.0)) {
          for (int k{0}; k <= nmqp1_tmp; k++) {
            qs = qq + k;
            b_A[qs] += nrm * b_A[iter + k];
          }
        }
      }
      e[m - 1] = b_A[qq];
    }
    if (q + 1 <= 1) {
      scale = 3.3121686421112381E-170;
      absxk = std::abs(e[1]);
      if (absxk > 3.3121686421112381E-170) {
        nrm = 1.0;
        scale = absxk;
      } else {
        t = absxk / 3.3121686421112381E-170;
        nrm = t * t;
      }
      absxk = std::abs(e[2]);
      if (absxk > scale) {
        t = scale / absxk;
        nrm = nrm * t * t + 1.0;
        scale = absxk;
      } else {
        t = absxk / scale;
        nrm += t * t;
      }
      nrm = scale * std::sqrt(nrm);
      if (nrm == 0.0) {
        e[0] = 0.0;
      } else {
        if (e[1] < 0.0) {
          nrm = -nrm;
        }
        e[0] = nrm;
        if (std::abs(nrm) >= 1.0020841800044864E-292) {
          nrm = 1.0 / nrm;
          for (int k{qp1}; k < 4; k++) {
            e[k - 1] *= nrm;
          }
        } else {
          for (int k{qp1}; k < 4; k++) {
            e[k - 1] /= nrm;
          }
        }
        e[1]++;
        e[0] = -e[0];
        for (ii = qp1; ii < 4; ii++) {
          work[ii - 1] = 0.0;
        }
        for (m = qp1; m < 4; m++) {
          t = e[m - 1];
          if (!(t == 0.0)) {
            qq = 3 * (m - 1) + 1;
            work[1] += t * b_A[qq];
            work[2] += t * b_A[qq + 1];
          }
        }
        for (m = qp1; m < 4; m++) {
          nrm = -e[m - 1] / e[1];
          if (!(nrm == 0.0)) {
            qq = (q + 3 * (m - 1)) + 1;
            b_A[qq] += nrm * work[q + 1];
            b_A[qq + 1] += nrm * work[q + 2];
          }
        }
      }
    }
  }
  m = 1;
  s[2] = b_A[8];
  e[1] = b_A[7];
  e[2] = 0.0;
  iter = 0;
  t = s[0];
  if (s[0] != 0.0) {
    nrm = std::abs(s[0]);
    absxk = s[0] / nrm;
    t = nrm;
    s[0] = nrm;
    e[0] /= absxk;
  }
  if (e[0] != 0.0) {
    nrm = std::abs(e[0]);
    absxk = nrm / e[0];
    e[0] = nrm;
    s[1] *= absxk;
  }
  snorm = std::fmax(std::abs(t), e[0]);
  t = s[1];
  if (s[1] != 0.0) {
    nrm = std::abs(s[1]);
    absxk = s[1] / nrm;
    t = nrm;
    s[1] = nrm;
    e[1] = b_A[7] / absxk;
  }
  if (e[1] != 0.0) {
    nrm = std::abs(e[1]);
    absxk = nrm / e[1];
    e[1] = nrm;
    s[2] = b_A[8] * absxk;
  }
  snorm = std::fmax(snorm, std::fmax(std::abs(t), e[1]));
  t = s[2];
  if (s[2] != 0.0) {
    nrm = std::abs(s[2]);
    t = nrm;
    s[2] = nrm;
  }
  snorm = std::fmax(snorm, std::fmax(std::abs(t), 0.0));
  while ((m + 2 > 0) && (iter < 75)) {
    boolean_T exitg1;
    nmqp1_tmp = m + 1;
    ii = m + 1;
    exitg1 = false;
    while (!(exitg1 || (ii == 0))) {
      nrm = std::abs(e[ii - 1]);
      if ((nrm <=
           2.2204460492503131E-16 * (std::abs(s[ii - 1]) + std::abs(s[ii]))) ||
          (nrm <= 1.0020841800044864E-292) ||
          ((iter > 20) && (nrm <= 2.2204460492503131E-16 * snorm))) {
        e[ii - 1] = 0.0;
        exitg1 = true;
      } else {
        ii--;
      }
    }
    if (ii == m + 1) {
      qq = 4;
    } else {
      qs = m + 2;
      qq = m + 2;
      exitg1 = false;
      while ((!exitg1) && (qq >= ii)) {
        qs = qq;
        if (qq == ii) {
          exitg1 = true;
        } else {
          nrm = 0.0;
          if (qq < m + 2) {
            nrm = std::abs(e[qq - 1]);
          }
          if (qq > ii + 1) {
            nrm += std::abs(e[qq - 2]);
          }
          t = std::abs(s[qq - 1]);
          if ((t <= 2.2204460492503131E-16 * nrm) ||
              (t <= 1.0020841800044864E-292)) {
            s[qq - 1] = 0.0;
            exitg1 = true;
          } else {
            qq--;
          }
        }
      }
      if (qs == ii) {
        qq = 3;
      } else if (qs == m + 2) {
        qq = 1;
      } else {
        qq = 2;
        ii = qs;
      }
    }
    switch (qq) {
    case 1: {
      t = e[m];
      e[m] = 0.0;
      for (int k{nmqp1_tmp}; k >= ii + 1; k--) {
        double sm;
        sm = blas::xrotg(s[k - 1], t, sqds);
        if (k > ii + 1) {
          t = -sqds * e[0];
          e[0] *= sm;
        }
      }
    } break;
    case 2: {
      t = e[ii - 1];
      e[ii - 1] = 0.0;
      for (int k{ii + 1}; k <= m + 2; k++) {
        double sm;
        sm = blas::xrotg(s[k - 1], t, sqds);
        absxk = e[k - 1];
        t = -sqds * absxk;
        e[k - 1] = absxk * sm;
      }
    } break;
    case 3: {
      double sm;
      nrm = s[m + 1];
      scale = std::fmax(
          std::fmax(std::fmax(std::fmax(std::abs(nrm), std::abs(s[m])),
                              std::abs(e[m])),
                    std::abs(s[ii])),
          std::abs(e[ii]));
      sm = nrm / scale;
      nrm = s[m] / scale;
      t = e[m] / scale;
      sqds = s[ii] / scale;
      absxk = ((nrm + sm) * (nrm - sm) + t * t) / 2.0;
      nrm = sm * t;
      nrm *= nrm;
      if ((absxk != 0.0) || (nrm != 0.0)) {
        t = std::sqrt(absxk * absxk + nrm);
        if (absxk < 0.0) {
          t = -t;
        }
        t = nrm / (absxk + t);
      } else {
        t = 0.0;
      }
      t += (sqds + sm) * (sqds - sm);
      nrm = sqds * (e[ii] / scale);
      for (int k{ii + 1}; k <= nmqp1_tmp; k++) {
        sm = blas::xrotg(t, nrm, sqds);
        if (k > ii + 1) {
          e[0] = t;
        }
        nrm = e[k - 1];
        absxk = s[k - 1];
        e[k - 1] = sm * nrm - sqds * absxk;
        t = sqds * s[k];
        s[k] *= sm;
        s[k - 1] = sm * absxk + sqds * nrm;
        sm = blas::xrotg(s[k - 1], t, sqds);
        absxk = e[k - 1];
        t = sm * absxk + sqds * s[k];
        s[k] = -sqds * absxk + sm * s[k];
        nrm = sqds * e[k];
        e[k] *= sm;
      }
      e[m] = t;
      iter++;
    } break;
    default:
      if (s[ii] < 0.0) {
        s[ii] = -s[ii];
      }
      qp1 = ii + 1;
      while ((ii + 1 < 3) && (s[ii] < s[qp1])) {
        nrm = s[ii];
        s[ii] = s[qp1];
        s[qp1] = nrm;
        ii = qp1;
        qp1++;
      }
      iter = 0;
      m--;
      break;
    }
  }
  U[0] = s[0];
  U[1] = s[1];
  U[2] = s[2];
}

} // namespace internal
} // namespace coder

//
// File trailer for svd.cpp
//
// [EOF]
//
