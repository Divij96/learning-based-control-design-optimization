//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: rigidBody1.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 02-Feb-2024 13:34:01
//

// Include Files
#include "rigidBody1.h"
#include "RigidBody.h"
#include "eigStandard.h"
#include "forward_dynamics_robot_arm_data.h"
#include "forward_dynamics_robot_arm_rtwutil.h"
#include "relop.h"
#include "rt_nonfinite.h"
#include "svd.h"
#include "xdlahqr.h"
#include "xdsterf.h"
#include "xzgehrd.h"
#include "xzlarfg.h"
#include "xzlascl.h"
#include <algorithm>
#include <cmath>

// Function Definitions
//
// Arguments    : void
// Return Type  : rigidBody
//
namespace coder {
rigidBody::rigidBody()
{
  matlabCodegenIsDeleted = true;
}

//
// Arguments    : void
// Return Type  : void
//
rigidBody::~rigidBody()
{
  matlabCodegenDestructor();
}

//
// Arguments    : void
// Return Type  : void
//
void rigidBody::matlabCodegenDestructor()
{
  if (!matlabCodegenIsDeleted) {
    matlabCodegenIsDeleted = true;
  }
}

//
// Arguments    : const double b_value[6]
// Return Type  : void
//
void rigidBody::set_Inertia(const double b_value[6])
{
  robotics::manip::internal::RigidBody *obj;
  creal_T eigVals[3];
  creal_T largestEigVal;
  creal_T smallestEigVal;
  double A[9];
  double inertiaInternal[9];
  double s[3];
  double absx;
  double tau_tmp;
  int b_exponent;
  int b_i;
  int exponent;
  int i1;
  int k;
  boolean_T b;
  boolean_T iscale;
  obj = BodyInternal;
  inertiaInternal[0] = b_value[0];
  inertiaInternal[3] = 0.0;
  inertiaInternal[6] = 0.0;
  inertiaInternal[1] = 0.0;
  inertiaInternal[4] = b_value[1];
  inertiaInternal[7] = 0.0;
  inertiaInternal[2] = 0.0;
  inertiaInternal[5] = 0.0;
  inertiaInternal[8] = b_value[2];
  iscale = true;
  for (k = 0; k < 9; k++) {
    if (iscale) {
      absx = inertiaInternal[k];
      if (std::isinf(absx) || std::isnan(absx)) {
        iscale = false;
      }
    } else {
      iscale = false;
    }
  }
  if (!iscale) {
    eigVals[0].re = rtNaN;
    eigVals[0].im = 0.0;
    eigVals[1].re = rtNaN;
    eigVals[1].im = 0.0;
    eigVals[2].re = rtNaN;
    eigVals[2].im = 0.0;
  } else {
    int exitg1;
    int i;
    boolean_T exitg2;
    iscale = true;
    k = 0;
    exitg2 = false;
    while ((!exitg2) && (k < 3)) {
      i = 0;
      do {
        exitg1 = 0;
        if (i <= k) {
          if (!(inertiaInternal[i + 3 * k] == inertiaInternal[k + 3 * i])) {
            iscale = false;
            exitg1 = 1;
          } else {
            i++;
          }
        } else {
          k++;
          exitg1 = 2;
        }
      } while (exitg1 == 0);
      if (exitg1 == 1) {
        exitg2 = true;
      }
    }
    if (iscale) {
      double anrm;
      ::std::copy(&inertiaInternal[0], &inertiaInternal[9], &A[0]);
      anrm = 0.0;
      k = 0;
      exitg2 = false;
      while ((!exitg2) && (k < 3)) {
        i = 0;
        do {
          exitg1 = 0;
          if (i <= k) {
            absx = std::abs(inertiaInternal[i + 3 * k]);
            if (std::isnan(absx)) {
              anrm = rtNaN;
              exitg1 = 1;
            } else {
              if (absx > anrm) {
                anrm = absx;
              }
              i++;
            }
          } else {
            k++;
            exitg1 = 2;
          }
        } while (exitg1 == 0);
        if (exitg1 == 1) {
          exitg2 = true;
        }
      }
      if (std::isinf(anrm) || std::isnan(anrm)) {
        s[0] = rtNaN;
        s[1] = rtNaN;
        s[2] = rtNaN;
      } else {
        double e[2];
        double tau[2];
        iscale = false;
        if ((anrm > 0.0) && (anrm < 1.0010415475915505E-146)) {
          iscale = true;
          anrm = 1.0010415475915505E-146 / anrm;
          internal::reflapack::xzlascl(1.0, anrm, A);
        } else if (anrm > 9.9895953610111751E+145) {
          iscale = true;
          anrm = 9.9895953610111751E+145 / anrm;
          internal::reflapack::xzlascl(1.0, anrm, A);
        }
        for (i = 0; i < 2; i++) {
          double taui;
          int e_tmp_tmp;
          e_tmp_tmp = i + 3 * i;
          e[i] = A[e_tmp_tmp + 1];
          taui = internal::reflapack::xzlarfg(2 - i, e[i], A, i * 3 + 3);
          if (taui != 0.0) {
            double temp1;
            int b_tau_tmp;
            int i2;
            A[e_tmp_tmp + 1] = 1.0;
            for (k = i + 1; k < 3; k++) {
              tau[k - 1] = 0.0;
            }
            b_i = 1 - i;
            i1 = 2 - i;
            for (int jj{0}; jj <= b_i; jj++) {
              k = i + jj;
              temp1 = taui * A[(k + 3 * i) + 1];
              absx = 0.0;
              b_tau_tmp = 3 * (k + 1);
              tau[k] += temp1 * A[(k + b_tau_tmp) + 1];
              i2 = jj + 2;
              for (int ii{i2}; ii <= i1; ii++) {
                tau_tmp = A[b_tau_tmp + 2];
                tau[1] += temp1 * tau_tmp;
                absx += tau_tmp * A[3 * i + 2];
              }
              tau[k] += taui * absx;
            }
            absx = 0.0;
            for (k = 0; k <= b_i; k++) {
              absx += tau[i + k] * A[(e_tmp_tmp + k) + 1];
            }
            absx *= -0.5 * taui;
            if (!(absx == 0.0)) {
              for (k = 0; k <= b_i; k++) {
                b_tau_tmp = i + k;
                tau[b_tau_tmp] += absx * A[(e_tmp_tmp + k) + 1];
              }
            }
            for (int jj{0}; jj <= b_i; jj++) {
              k = i + jj;
              temp1 = A[(k + 3 * i) + 1];
              absx = tau[k];
              tau_tmp = absx * temp1;
              b_tau_tmp = 3 * (k + 1);
              k = (k + b_tau_tmp) + 1;
              A[k] = (A[k] - tau_tmp) - tau_tmp;
              i2 = jj + 2;
              for (int ii{i2}; ii <= i1; ii++) {
                A[b_tau_tmp + 2] =
                    (A[b_tau_tmp + 2] - tau[1] * temp1) - A[3 * i + 2] * absx;
              }
            }
          }
          A[e_tmp_tmp + 1] = e[i];
          s[i] = A[e_tmp_tmp];
          tau[i] = taui;
        }
        s[2] = A[8];
        k = internal::reflapack::xdsterf(s, e);
        if (k != 0) {
          s[0] = rtNaN;
          s[1] = rtNaN;
          s[2] = rtNaN;
        } else if (iscale) {
          absx = 1.0 / anrm;
          s[0] *= absx;
          s[1] *= absx;
          s[2] *= absx;
        }
      }
      eigVals[0].re = s[0];
      eigVals[0].im = 0.0;
      eigVals[1].re = s[1];
      eigVals[1].im = 0.0;
      eigVals[2].re = s[2];
      eigVals[2].im = 0.0;
    } else {
      iscale = true;
      k = 0;
      exitg2 = false;
      while ((!exitg2) && (k < 3)) {
        i = 0;
        do {
          exitg1 = 0;
          if (i <= k) {
            if (!(inertiaInternal[i + 3 * k] == -inertiaInternal[k + 3 * i])) {
              iscale = false;
              exitg1 = 1;
            } else {
              i++;
            }
          } else {
            k++;
            exitg1 = 2;
          }
        } while (exitg1 == 0);
        if (exitg1 == 1) {
          exitg2 = true;
        }
      }
      if (iscale) {
        double wi[3];
        ::std::copy(&inertiaInternal[0], &inertiaInternal[9], &A[0]);
        internal::reflapack::xzgehrd(A, 1, 3);
        k = internal::reflapack::xdlahqr(1, 3, A, absx, s, wi);
        b_i = static_cast<unsigned char>(k);
        for (i = 0; i < b_i; i++) {
          eigVals[i].re = rtNaN;
          eigVals[i].im = 0.0;
        }
        b_i = k + 1;
        for (i = b_i; i < 4; i++) {
          eigVals[i - 1].re = 0.0;
          eigVals[i - 1].im = wi[i - 1];
        }
      } else {
        eigStandard(inertiaInternal, eigVals);
      }
    }
  }
  smallestEigVal = eigVals[0];
  largestEigVal = eigVals[0];
  b = (std::isnan(eigVals[1].re) || std::isnan(eigVals[1].im));
  if (b) {
    iscale = false;
  } else if (std::isnan(eigVals[0].re) || std::isnan(eigVals[0].im)) {
    iscale = true;
  } else {
    absx = internal::absRelopProxies(eigVals[0], eigVals[1], tau_tmp);
    iscale = (absx > tau_tmp);
  }
  if (iscale) {
    smallestEigVal = eigVals[1];
  }
  if (b) {
    iscale = false;
  } else if (std::isnan(eigVals[0].re) || std::isnan(eigVals[0].im)) {
    iscale = true;
  } else {
    absx = internal::absRelopProxies(eigVals[0], eigVals[1], tau_tmp);
    iscale = (absx < tau_tmp);
  }
  if (iscale) {
    largestEigVal = eigVals[1];
  }
  b = (std::isnan(eigVals[2].re) || std::isnan(eigVals[2].im));
  if (b) {
    iscale = false;
  } else if (std::isnan(smallestEigVal.re) || std::isnan(smallestEigVal.im)) {
    iscale = true;
  } else {
    absx = internal::absRelopProxies(smallestEigVal, eigVals[2], tau_tmp);
    iscale = (absx > tau_tmp);
  }
  if (iscale) {
    smallestEigVal = eigVals[2];
  }
  if (b) {
    iscale = false;
  } else if (std::isnan(largestEigVal.re) || std::isnan(largestEigVal.im)) {
    iscale = true;
  } else {
    absx = internal::absRelopProxies(largestEigVal, eigVals[2], tau_tmp);
    iscale = (absx < tau_tmp);
  }
  if (iscale) {
    largestEigVal = eigVals[2];
  }
  absx = rt_hypotd_snf(largestEigVal.re, largestEigVal.im);
  if (std::isinf(absx) || std::isnan(absx)) {
    absx = rtNaN;
  } else if (absx < 4.4501477170144028E-308) {
    absx = 4.94065645841247E-324;
  } else {
    std::frexp(absx, &exponent);
    absx = std::ldexp(1.0, exponent - 53);
  }
  absx *= 3.0;
  if (((!(smallestEigVal.re < 0.0)) ||
       (!(rt_hypotd_snf(smallestEigVal.re, smallestEigVal.im) > absx))) &&
      (eigVals[0].re < absx)) {
    iscale = true;
    for (k = 0; k < 9; k++) {
      if (iscale) {
        absx = inertiaInternal[k];
        if (std::isinf(absx) || std::isnan(absx)) {
          iscale = false;
        }
      } else {
        iscale = false;
      }
    }
    if (iscale) {
      internal::svd(inertiaInternal, s);
    } else {
      s[0] = rtNaN;
    }
    absx = std::abs(s[0]);
    if ((!std::isinf(absx)) && (!std::isnan(absx)) &&
        (!(absx < 4.4501477170144028E-308))) {
      std::frexp(absx, &b_exponent);
    }
  }
  for (b_i = 0; b_i < 9; b_i++) {
    obj->InertiaInternal[b_i] = inertiaInternal[b_i];
  }
  absx = obj->MassInternal;
  s[0] = obj->CenterOfMassInternal[0];
  s[1] = obj->CenterOfMassInternal[1];
  s[2] = obj->CenterOfMassInternal[2];
  for (b_i = 0; b_i < 9; b_i++) {
    A[b_i] = obj->InertiaInternal[b_i];
  }
  inertiaInternal[0] = 0.0;
  inertiaInternal[3] = -s[2];
  inertiaInternal[6] = s[1];
  inertiaInternal[1] = s[2];
  inertiaInternal[4] = 0.0;
  inertiaInternal[7] = -s[0];
  inertiaInternal[2] = -s[1];
  inertiaInternal[5] = s[0];
  inertiaInternal[8] = 0.0;
  for (b_i = 0; b_i < 3; b_i++) {
    obj->SpatialInertia[6 * b_i] = A[3 * b_i];
    obj->SpatialInertia[6 * b_i + 1] = A[3 * b_i + 1];
    obj->SpatialInertia[6 * b_i + 2] = A[3 * b_i + 2];
  }
  for (b_i = 0; b_i < 3; b_i++) {
    i1 = 6 * (b_i + 3);
    obj->SpatialInertia[i1] = absx * inertiaInternal[3 * b_i];
    obj->SpatialInertia[i1 + 1] = absx * inertiaInternal[3 * b_i + 1];
    obj->SpatialInertia[i1 + 2] = absx * inertiaInternal[3 * b_i + 2];
  }
  for (b_i = 0; b_i < 3; b_i++) {
    obj->SpatialInertia[6 * b_i + 3] = absx * inertiaInternal[b_i];
    obj->SpatialInertia[6 * b_i + 4] = absx * inertiaInternal[b_i + 3];
    obj->SpatialInertia[6 * b_i + 5] = absx * inertiaInternal[b_i + 6];
  }
  for (b_i = 0; b_i < 3; b_i++) {
    i1 = 6 * (b_i + 3);
    obj->SpatialInertia[i1 + 3] = absx * static_cast<double>(iv1[3 * b_i]);
    obj->SpatialInertia[i1 + 4] = absx * static_cast<double>(iv1[3 * b_i + 1]);
    obj->SpatialInertia[i1 + 5] = absx * static_cast<double>(iv1[3 * b_i + 2]);
  }
}

} // namespace coder

//
// File trailer for rigidBody1.cpp
//
// [EOF]
//
