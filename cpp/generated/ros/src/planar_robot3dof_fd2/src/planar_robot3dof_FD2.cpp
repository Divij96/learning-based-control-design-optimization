/*
 * planar_robot3dof_FD2.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "planar_robot3dof_FD2".
 *
 * Model version              : 12.42
 * Simulink Coder version : 9.9 (R2023a) 19-Nov-2022
 * C++ source code generated on : Thu Nov 23 05:03:23 2023
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objective: Debugging
 * Validation result: Not run
 */

#include "planar_robot3dof_FD2.h"
#include "rtwtypes.h"
#include "planar_robot3dof_FD2_private.h"
#include <cstring>
#include <cmath>

extern "C"
{

#include "rt_nonfinite.h"

}

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
void planar_robot3dof_FD2::rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3]{
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3]{
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t { rtsiGetT(si) };

  time_T tnew { rtsiGetSolverStopTime(si) };

  time_T h { rtsiGetStepSize(si) };

  real_T *x { rtsiGetContStates(si) };

  ODE3_IntgData *id { static_cast<ODE3_IntgData *>(rtsiGetSolverData(si)) };

  real_T *y { id->y };

  real_T *f0 { id->f[0] };

  real_T *f1 { id->f[1] };

  real_T *f2 { id->f[2] };

  real_T hB[3];
  int_T i;
  int_T nXc { 6 };

  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) std::memcpy(y, x,
                     static_cast<uint_T>(nXc)*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  planar_robot3dof_FD2_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  this->step();
  planar_robot3dof_FD2_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  this->step();
  planar_robot3dof_FD2_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Function for MATLAB Function: '<S1>/calcSysMatrices' */
void planar_robot3dof_FD2::planar_robot3dof_FD2_eye(real_T b_I[9])
{
  std::memset(&b_I[0], 0, 9U * sizeof(real_T));
  b_I[0] = 1.0;
  b_I[4] = 1.0;
  b_I[8] = 1.0;
}

/* Function for MATLAB Function: '<S1>/calcSysMatrices' */
void planar_robot3dof_FD2::planar_robot3dof_FD2_diag(const real_T v[3], real_T
  d[9])
{
  std::memset(&d[0], 0, 9U * sizeof(real_T));
  d[0] = v[0];
  d[4] = v[1];
  d[8] = v[2];
}

/* Function for MATLAB Function: '<S1>/calcSysMatrices' */
void planar_robot3dof_FD2::planar_robot3dof_FD2_repmat(real_T b[18])
{
  static const int8_T a[6]{ 0, 0, 0, 0, 0, 1 };

  for (int32_T itilerow{0}; itilerow < 3; itilerow++) {
    int32_T ibcol;
    ibcol = itilerow * 6;
    for (int32_T k{0}; k < 6; k++) {
      b[ibcol + k] = a[k];
    }
  }
}

/* Function for MATLAB Function: '<S1>/calcSysMatrices' */
boolean_T planar_robot3dof_FD2::planar_robot3dof_FD2_all(const boolean_T x[3])
{
  int32_T k;
  boolean_T exitg1;
  boolean_T y;
  y = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 3)) {
    if (!x[k]) {
      y = false;
      exitg1 = true;
    } else {
      k++;
    }
  }

  return y;
}

/* Function for MATLAB Function: '<S1>/calcSysMatrices' */
void planar_robot3dof_FD2::planar_robot3dof_FD2_mtimes(const real_T A_data[],
  const int32_T A_size[2], const real_T B[16], real_T C_data[], int32_T C_size[2])
{
  int32_T m;
  m = A_size[0];
  C_size[0] = A_size[0];
  C_size[1] = 4;
  for (int32_T j{0}; j < 4; j++) {
    int32_T boffset;
    int32_T coffset;
    coffset = j * m;
    boffset = j << 2;
    for (int32_T i{0}; i < m; i++) {
      C_data[coffset + i] = ((A_data[A_size[0] + i] * B[boffset + 1] + A_data[i]
        * B[boffset]) + A_data[(A_size[0] << 1) + i] * B[boffset + 2]) + A_data
        [3 * A_size[0] + i] * B[boffset + 3];
    }
  }
}

/* Function for MATLAB Function: '<S1>/calcSysMatrices' */
void planar_robot3dof_FD2::planar_robot3dof_FD2_mtimes_e(const real_T A[36],
  const real_T B_data[], const int32_T B_size[2], real_T C_data[], int32_T
  C_size[2])
{
  int32_T b;
  C_size[0] = 6;
  C_size[1] = B_size[1];
  b = B_size[1];
  for (int32_T j{0}; j < b; j++) {
    int32_T coffset_tmp;
    coffset_tmp = j * 6;
    for (int32_T i{0}; i < 6; i++) {
      real_T s;
      s = 0.0;
      for (int32_T k{0}; k < 6; k++) {
        s += A[k * 6 + i] * B_data[coffset_tmp + k];
      }

      C_data[coffset_tmp + i] = s;
    }
  }
}

void planar_robot3dof_FD2::planar_rob_binary_expand_op_lmf(real_T in1[18],
  int32_T in2, const real_T in3[36], const real_T in4[18], const real_T in5[9],
  const real_T in6[6], const real_T in7[18])
{
  real_T in5_0[36];
  real_T in4_data[12];
  real_T tmp_data[12];
  real_T tmp_data_0[12];
  real_T in5_1;
  int32_T in4_size[2];
  int32_T tmp_size[2];
  int32_T tmp_size_0[2];
  int32_T aux_0_1;
  int32_T aux_1_1;
  int32_T i;
  int32_T in5_tmp;
  int32_T loop_ub;
  int32_T stride_0_1;
  int32_T stride_1_1;

  /* Outputs for Atomic SubSystem: '<Root>/planar_robot3dof_FD' */
  /* MATLAB Function: '<S1>/calcSysMatrices' */
  in4_size[0] = 6;
  in4_size[1] = in2;
  for (i = 0; i < in2; i++) {
    for (in5_tmp = 0; in5_tmp < 6; in5_tmp++) {
      in4_data[in5_tmp + 6 * i] = in4[6 * i + in5_tmp];
    }
  }

  planar_robot3dof_FD2_mtimes_e(in3, in4_data, in4_size, tmp_data, tmp_size);
  in5_0[18] = 0.0;
  in5_0[24] = -in6[2];
  in5_0[30] = in6[1];
  in5_0[19] = in6[2];
  in5_0[25] = 0.0;
  in5_0[31] = -in6[0];
  in5_0[20] = -in6[1];
  in5_0[26] = in6[0];
  in5_0[32] = 0.0;
  for (i = 0; i < 3; i++) {
    in5_1 = in5[3 * i];
    in5_0[6 * i] = in5_1;
    in5_0[6 * i + 3] = 0.0;
    in5_tmp = (i + 3) * 6;
    in5_0[in5_tmp + 3] = in5_1;
    in5_1 = in5[3 * i + 1];
    in5_0[6 * i + 1] = in5_1;
    in5_0[6 * i + 4] = 0.0;
    in5_0[in5_tmp + 4] = in5_1;
    in5_1 = in5[3 * i + 2];
    in5_0[6 * i + 2] = in5_1;
    in5_0[6 * i + 5] = 0.0;
    in5_0[in5_tmp + 5] = in5_1;
  }

  in4_size[0] = 6;
  in4_size[1] = in2;
  for (i = 0; i < in2; i++) {
    for (in5_tmp = 0; in5_tmp < 6; in5_tmp++) {
      in4_data[in5_tmp + 6 * i] = in7[6 * i + in5_tmp];
    }
  }

  planar_robot3dof_FD2_mtimes_e(in5_0, in4_data, in4_size, tmp_data_0,
    tmp_size_0);
  stride_0_1 = (tmp_size[1] != 1);
  stride_1_1 = (tmp_size_0[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  loop_ub = tmp_size_0[1] == 1 ? tmp_size[1] : tmp_size_0[1];
  for (i = 0; i < loop_ub; i++) {
    for (in5_tmp = 0; in5_tmp < 6; in5_tmp++) {
      in1[in5_tmp + 6 * i] = tmp_data[6 * aux_0_1 + in5_tmp] - tmp_data_0[6 *
        aux_1_1 + in5_tmp];
    }

    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }

  /* End of MATLAB Function: '<S1>/calcSysMatrices' */
  /* End of Outputs for SubSystem: '<Root>/planar_robot3dof_FD' */
}

/* Function for MATLAB Function: '<S1>/calcSysMatrices' */
void planar_robot3dof_FD2::planar_robot3dof_FD2_mtimes_ev(const real_T A_data[],
  const int32_T A_size[2], const real_T B_data[], const int32_T B_size[2],
  real_T C_data[], int32_T C_size[2])
{
  int32_T m;
  m = A_size[1];
  C_size[0] = A_size[1];
  C_size[1] = 6;
  for (int32_T j{0}; j < 6; j++) {
    int32_T boffset;
    int32_T coffset;
    coffset = j * m;
    boffset = j * B_size[0];
    for (int32_T i{0}; i < m; i++) {
      real_T s;
      int32_T aoffset;
      aoffset = i * 6;
      s = 0.0;
      for (int32_T k{0}; k < 6; k++) {
        s += A_data[aoffset + k] * B_data[boffset + k];
      }

      C_data[coffset + i] = s;
    }
  }
}

/* Function for MATLAB Function: '<S1>/calcSysMatrices' */
void planar_robot3dof_FD2::planar_robot3dof_FD2_mtimes_evj(const real_T A_data[],
  const int32_T A_size[2], const real_T B_data[], const int32_T B_size[2],
  real_T C_data[], int32_T C_size[2])
{
  int32_T b;
  int32_T m;
  m = A_size[0];
  C_size[0] = A_size[0];
  C_size[1] = B_size[1];
  b = B_size[1];
  for (int32_T j{0}; j < b; j++) {
    int32_T boffset;
    int32_T coffset;
    coffset = j * m;
    boffset = j * 6;
    for (int32_T i{0}; i < m; i++) {
      real_T s;
      s = 0.0;
      for (int32_T k{0}; k < 6; k++) {
        s += A_data[k * A_size[0] + i] * B_data[boffset + k];
      }

      C_data[coffset + i] = s;
    }
  }
}

void planar_robot3dof_FD2::planar_robo_binary_expand_op_lm(real_T in1[9],
  int32_T in2, const real_T in3_data[], const int32_T in3_size[2], const real_T
  in4[18])
{
  real_T in4_data[18];
  real_T in1_data[9];
  real_T tmp_data[9];
  int32_T in4_size[2];
  int32_T tmp_size[2];
  int32_T aux_0_1;
  int32_T aux_1_1;
  int32_T i;
  int32_T i_0;
  int32_T loop_ub;
  int32_T loop_ub_0;
  int32_T stride_0_0_tmp;
  int32_T stride_1_0;
  int32_T stride_1_1;

  /* Outputs for Atomic SubSystem: '<Root>/planar_robot3dof_FD' */
  /* MATLAB Function: '<S1>/calcSysMatrices' */
  in4_size[0] = 6;
  in4_size[1] = in2 + 1;
  for (i_0 = 0; i_0 <= in2; i_0++) {
    for (i = 0; i < 6; i++) {
      in4_data[i + 6 * i_0] = in4[6 * i_0 + i];
    }
  }

  planar_robot3dof_FD2_mtimes_evj(in3_data, in3_size, in4_data, in4_size,
    tmp_data, tmp_size);
  loop_ub_0 = tmp_size[0] == 1 ? in2 + 1 : tmp_size[0];
  loop_ub = tmp_size[1] == 1 ? in2 + 1 : tmp_size[1];
  stride_0_0_tmp = (in2 + 1 != 1);
  stride_1_0 = (tmp_size[0] != 1);
  stride_1_1 = (tmp_size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (i_0 = 0; i_0 < loop_ub; i_0++) {
    for (i = 0; i < loop_ub_0; i++) {
      in1_data[i + loop_ub_0 * i_0] = in1[i * stride_0_0_tmp + 3 * aux_0_1] +
        tmp_data[i * stride_1_0 + tmp_size[0] * aux_1_1];
    }

    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_0_tmp;
  }

  for (i_0 = 0; i_0 < loop_ub; i_0++) {
    for (i = 0; i < loop_ub_0; i++) {
      in1[i + 3 * i_0] = in1_data[loop_ub_0 * i_0 + i];
    }
  }

  /* End of MATLAB Function: '<S1>/calcSysMatrices' */
  /* End of Outputs for SubSystem: '<Root>/planar_robot3dof_FD' */
}

/* Function for MATLAB Function: '<S1>/calcSysMatrices' */
void planar_robot3dof_FD2::planar_robot3dof_FD_mtimes_evjz(const real_T A_data[],
  const int32_T A_size[2], const real_T B[36], real_T C_data[], int32_T C_size[2])
{
  int32_T m;
  m = A_size[1];
  C_size[0] = A_size[1];
  C_size[1] = 6;
  for (int32_T j{0}; j < 6; j++) {
    int32_T boffset;
    int32_T coffset;
    coffset = j * m;
    boffset = j * 6;
    for (int32_T i{0}; i < m; i++) {
      real_T s;
      int32_T aoffset;
      aoffset = i * 6;
      s = 0.0;
      for (int32_T k{0}; k < 6; k++) {
        s += A_data[aoffset + k] * B[boffset + k];
      }

      C_data[coffset + i] = s;
    }
  }
}

void planar_robot3dof_FD2::planar_robot_binary_expand_op_l(real_T in1[9],
  int32_T in2, const real_T in3[18], real_T in4, const real_T in5[9], const
  real_T in6[9], const real_T in7[9], const real_T in8_data[], const int32_T
  in8_size[2], const real_T in9[18])
{
  real_T in4_0[36];
  real_T in3_data[18];
  real_T in3_data_0[18];
  real_T tmp_data_1[18];
  real_T in1_data[9];
  real_T tmp_data[9];
  real_T tmp_data_0[9];
  int32_T in3_size[2];
  int32_T in3_size_0[2];
  int32_T tmp_size[2];
  int32_T tmp_size_0[2];
  int32_T aux_0_1;
  int32_T aux_1_1;
  int32_T aux_2_1;
  int32_T i;
  int32_T in4_tmp;
  int32_T in4_tmp_0;
  int32_T loop_ub;
  int32_T stride_0_0_tmp;
  int32_T stride_1_0;
  int32_T stride_1_1;
  int32_T stride_2_0;
  int32_T stride_2_1;

  /* Outputs for Atomic SubSystem: '<Root>/planar_robot3dof_FD' */
  /* MATLAB Function: '<S1>/calcSysMatrices' */
  in3_size[0] = 6;
  in3_size[1] = in2 + 1;
  for (i = 0; i <= in2; i++) {
    for (in4_tmp = 0; in4_tmp < 6; in4_tmp++) {
      in3_data[in4_tmp + 6 * i] = in3[6 * i + in4_tmp];
    }
  }

  for (i = 0; i < 3; i++) {
    in4_0[6 * i] = in5[3 * i] * in4;
    in4_tmp = (i + 3) * 6;
    in4_0[in4_tmp] = -in6[i];
    in4_0[6 * i + 3] = in6[3 * i];
    in4_0[in4_tmp + 3] = in7[3 * i] - in7[i];
    in4_tmp_0 = 3 * i + 1;
    in4_0[6 * i + 1] = in5[in4_tmp_0] * in4;
    in4_0[in4_tmp + 1] = -in6[i + 3];
    in4_0[6 * i + 4] = in6[in4_tmp_0];
    in4_0[in4_tmp + 4] = in7[in4_tmp_0] - in7[i + 3];
    in4_tmp_0 = 3 * i + 2;
    in4_0[6 * i + 2] = in5[in4_tmp_0] * in4;
    in4_0[in4_tmp + 2] = -in6[i + 6];
    in4_0[6 * i + 5] = in6[in4_tmp_0];
    in4_0[in4_tmp + 5] = in7[in4_tmp_0] - in7[i + 6];
  }

  in3_size_0[0] = 6;
  in3_size_0[1] = in2 + 1;
  for (i = 0; i <= in2; i++) {
    for (in4_tmp = 0; in4_tmp < 6; in4_tmp++) {
      in3_data_0[in4_tmp + 6 * i] = in3[6 * i + in4_tmp];
    }
  }

  planar_robot3dof_FD_mtimes_evjz(in3_data, in3_size, in4_0, tmp_data_1,
    tmp_size_0);
  planar_robot3dof_FD2_mtimes_evj(tmp_data_1, tmp_size_0, in3_data_0, in3_size_0,
    tmp_data, tmp_size);
  in3_size[0] = 6;
  in3_size[1] = in2 + 1;
  for (i = 0; i <= in2; i++) {
    for (in4_tmp = 0; in4_tmp < 6; in4_tmp++) {
      in3_data[in4_tmp + 6 * i] = in9[6 * i + in4_tmp];
    }
  }

  planar_robot3dof_FD2_mtimes_evj(in8_data, in8_size, in3_data, in3_size,
    tmp_data_0, tmp_size_0);
  in4_tmp_0 = tmp_size_0[0] == 1 ? tmp_size[0] == 1 ? in2 + 1 : tmp_size[0] :
    tmp_size_0[0];
  loop_ub = tmp_size_0[1] == 1 ? tmp_size[1] == 1 ? in2 + 1 : tmp_size[1] :
    tmp_size_0[1];
  stride_0_0_tmp = (in2 + 1 != 1);
  stride_1_0 = (tmp_size[0] != 1);
  stride_1_1 = (tmp_size[1] != 1);
  stride_2_0 = (tmp_size_0[0] != 1);
  stride_2_1 = (tmp_size_0[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  aux_2_1 = 0;
  for (i = 0; i < loop_ub; i++) {
    for (in4_tmp = 0; in4_tmp < in4_tmp_0; in4_tmp++) {
      in1_data[in4_tmp + in4_tmp_0 * i] = (in1[in4_tmp * stride_0_0_tmp + 3 *
        aux_0_1] + tmp_data[in4_tmp * stride_1_0 + tmp_size[0] * aux_1_1]) +
        tmp_data_0[in4_tmp * stride_2_0 + tmp_size_0[0] * aux_2_1];
    }

    aux_2_1 += stride_2_1;
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_0_tmp;
  }

  for (i = 0; i < loop_ub; i++) {
    for (in4_tmp = 0; in4_tmp < in4_tmp_0; in4_tmp++) {
      in1[in4_tmp + 3 * i] = in1_data[in4_tmp_0 * i + in4_tmp];
    }
  }

  /* End of MATLAB Function: '<S1>/calcSysMatrices' */
  /* End of Outputs for SubSystem: '<Root>/planar_robot3dof_FD' */
}

/* Function for MATLAB Function: '<S1>/calcSysMatrices' */
void planar_robot3dof_FD2::planar_robot3dof_F_mtimes_evjzc(const real_T A_data[],
  const int32_T A_size[2], const real_T B[9], real_T C_data[], int32_T C_size[2])
{
  int32_T m;
  m = A_size[0];
  C_size[0] = A_size[0];
  C_size[1] = 3;
  for (int32_T j{0}; j < 3; j++) {
    int32_T coffset;
    coffset = j * m;
    for (int32_T i{0}; i < m; i++) {
      C_data[coffset + i] = (A_data[A_size[0] + i] * B[j + 3] + A_data[i] * B[j])
        + A_data[(A_size[0] << 1) + i] * B[j + 6];
    }
  }
}

/* Function for MATLAB Function: '<S1>/calcSysMatrices' */
void planar_robot3dof_FD2::planar_robot3dof__mtimes_evjzci(const real_T A_data[],
  const int32_T A_size[2], real_T C_data[], int32_T *C_size)
{
  int32_T b;
  *C_size = A_size[0];
  b = A_size[0];
  for (int32_T i{0}; i < b; i++) {
    C_data[i] = (A_data[A_size[0] + i] * 0.0 + A_data[i] * 0.0) + A_data
      [(A_size[0] << 1) + i] * 0.0;
  }
}

void planar_robot3dof_FD2::planar_robot3d_binary_expand_op(real_T in1[3],
  int32_T in2, const real_T in3_data[], const int32_T in3_size[2], const real_T
  in4[16])
{
  real_T in3_data_0[9];
  real_T in4_0[9];
  real_T tmp_data_0[9];
  real_T in1_data[3];
  real_T tmp_data[3];
  int32_T in3_size_0[2];
  int32_T tmp_size_0[2];
  int32_T in4_tmp;
  int32_T stride_0_1;
  int32_T stride_1_1;
  int32_T tmp_size;

  /* Outputs for Atomic SubSystem: '<Root>/planar_robot3dof_FD' */
  /* MATLAB Function: '<S1>/calcSysMatrices' */
  in3_size_0[0] = in2 + 1;
  in3_size_0[1] = 3;
  for (tmp_size = 0; tmp_size < 3; tmp_size++) {
    for (in4_tmp = 0; in4_tmp <= in2; in4_tmp++) {
      in3_data_0[in4_tmp + (in2 + 1) * tmp_size] = in3_data[in3_size[0] *
        tmp_size + in4_tmp];
    }

    in4_tmp = tmp_size << 2;
    in4_0[3 * tmp_size] = in4[in4_tmp];
    in4_0[3 * tmp_size + 1] = in4[in4_tmp + 1];
    in4_0[3 * tmp_size + 2] = in4[in4_tmp + 2];
  }

  planar_robot3dof_F_mtimes_evjzc(in3_data_0, in3_size_0, in4_0, tmp_data_0,
    tmp_size_0);
  planar_robot3dof__mtimes_evjzci(tmp_data_0, tmp_size_0, tmp_data, &tmp_size);
  in4_tmp = in2 + 1;
  stride_0_1 = (in2 + 1 != 1);
  stride_1_1 = (tmp_size != 1);
  for (tmp_size = 0; tmp_size < in4_tmp; tmp_size++) {
    in1_data[tmp_size] = in1[tmp_size * stride_0_1] + tmp_data[tmp_size *
      stride_1_1];
  }

  if ((in2 + 1) - 1 >= 0) {
    std::memcpy(&in1[0], &in1_data[0], static_cast<uint32_T>(in2 + 1) * sizeof
                (real_T));
  }

  /* End of MATLAB Function: '<S1>/calcSysMatrices' */
  /* End of Outputs for SubSystem: '<Root>/planar_robot3dof_FD' */
}

void rt_invd3x3_snf(const real_T u[9], real_T y[9])
{
  real_T x[9];
  real_T absx11;
  real_T absx21;
  real_T absx31;
  int32_T p1;
  int32_T p2;
  int32_T p3;
  std::memcpy(&x[0], &u[0], 9U * sizeof(real_T));
  p1 = 1;
  p2 = 3;
  p3 = 6;
  absx11 = std::abs(u[0]);
  absx21 = std::abs(u[1]);
  absx31 = std::abs(u[2]);
  if ((absx21 > absx11) && (absx21 > absx31)) {
    p1 = 4;
    p2 = 0;
    x[0] = u[1];
    x[1] = u[0];
    x[3] = u[4];
    x[4] = u[3];
    x[6] = u[7];
    x[7] = u[6];
  } else if (absx31 > absx11) {
    p1 = 7;
    p3 = 0;
    x[2] = x[0];
    x[0] = u[2];
    x[5] = x[3];
    x[3] = u[5];
    x[8] = x[6];
    x[6] = u[8];
  }

  absx31 = x[1] / x[0];
  x[1] = absx31;
  absx11 = x[2] / x[0];
  x[2] = absx11;
  x[4] -= absx31 * x[3];
  x[5] -= absx11 * x[3];
  x[7] -= absx31 * x[6];
  x[8] -= absx11 * x[6];
  if (std::abs(x[5]) > std::abs(x[4])) {
    int32_T itmp;
    itmp = p2;
    p2 = p3;
    p3 = itmp;
    x[1] = absx11;
    x[2] = absx31;
    absx11 = x[4];
    x[4] = x[5];
    x[5] = absx11;
    absx11 = x[7];
    x[7] = x[8];
    x[8] = absx11;
  }

  absx31 = x[5] / x[4];
  x[8] -= absx31 * x[7];
  absx11 = (x[1] * absx31 - x[2]) / x[8];
  absx21 = -(x[7] * absx11 + x[1]) / x[4];
  y[p1 - 1] = ((1.0 - x[3] * absx21) - x[6] * absx11) / x[0];
  y[p1] = absx21;
  y[p1 + 1] = absx11;
  absx11 = -absx31 / x[8];
  absx21 = (1.0 - x[7] * absx11) / x[4];
  y[p2] = -(x[3] * absx21 + x[6] * absx11) / x[0];
  y[p2 + 1] = absx21;
  y[p2 + 2] = absx11;
  absx11 = 1.0 / x[8];
  absx21 = -x[7] * absx11 / x[4];
  y[p3] = -(x[3] * absx21 + x[6] * absx11) / x[0];
  y[p3 + 1] = absx21;
  y[p3 + 2] = absx11;
}

/* Model step function */
void planar_robot3dof_FD2::step()
{
  if (rtmIsMajorTimeStep((&planar_robot3dof_FD2_M))) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&(&planar_robot3dof_FD2_M)->solverInfo,
                          (((&planar_robot3dof_FD2_M)->Timing.clockTick0+1)*
      (&planar_robot3dof_FD2_M)->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep((&planar_robot3dof_FD2_M))) {
    (&planar_robot3dof_FD2_M)->Timing.t[0] = rtsiGetT(&(&planar_robot3dof_FD2_M
      )->solverInfo);
  }

  {
    static const int8_T c_b[9]{ 1, 0, 0, 0, 1, 0, 0, 0, 1 };

    real_T ROBOT_Mass[108];
    real_T ROBOT_Mass_data[108];
    real_T Htm_data[48];
    real_T ROBOT_g0[48];
    real_T ROBOT_g0_data[48];
    real_T invAd[36];
    real_T m_0[36];
    real_T m_1[36];
    real_T m_2[36];
    real_T J[18];
    real_T J_data[18];
    real_T J_data_0[18];
    real_T J_data_1[18];
    real_T J_data_2[18];
    real_T J_data_3[18];
    real_T J_data_4[18];
    real_T J_data_5[18];
    real_T J_pre[18];
    real_T ROBOT_csi[18];
    real_T dJ[18];
    real_T dJ_data[18];
    real_T dJ_data_0[18];
    real_T dJ_pre[18];
    real_T tmp_data_2[18];
    real_T O_Htm[16];
    real_T O_Htm_0[16];
    real_T O_Htm_pre[16];
    real_T J_pre_data[12];
    real_T dJ_pre_data[12];
    real_T tmp_data[12];
    real_T E_tmp[9];
    real_T S[9];
    real_T b_I[9];
    real_T b_I_0[9];
    real_T b_S[9];
    real_T b_y[9];
    real_T c_S[9];
    real_T c_y[9];
    real_T d_y[9];
    real_T jointOrigins[9];
    real_T tmp[9];
    real_T tmp2[9];
    real_T tmp2_0[9];
    real_T tmp_0[9];
    real_T y[9];
    real_T inertialTwist[6];
    real_T inertialTwist_pre[6];
    real_T relTwist[6];
    real_T rtb_ZeroOrderHold[3];
    real_T tmp_data_0[3];
    real_T tmp_data_1[3];
    real_T (*lastU)[3];
    real_T Iz;
    real_T S_0;
    real_T b_m;
    real_T body_CenterOfMass_idx_0;
    real_T c_m;
    real_T m;
    real_T m_tmp;
    real_T m_tmp_0;
    real_T rtb_ZeroOrderHold1_idx_0;
    real_T rtb_ZeroOrderHold1_idx_1;
    real_T rtb_ZeroOrderHold1_idx_2;
    real_T tmp2_1;
    int32_T Htm_size[2];
    int32_T J_pre_size[2];
    int32_T J_size[2];
    int32_T J_size_0[2];
    int32_T J_size_1[2];
    int32_T J_size_2[2];
    int32_T J_size_3[2];
    int32_T J_size_4[2];
    int32_T J_size_5[2];
    int32_T J_size_6[2];
    int32_T ROBOT_Mass_size[2];
    int32_T ROBOT_g0_size[2];
    int32_T dJ_pre_size[2];
    int32_T dJ_size[2];
    int32_T dJ_size_0[2];
    int32_T tmp_size[2];
    int32_T tmp_size_0[2];
    int32_T tmp_size_1[2];
    int32_T tmp_size_2[2];
    int32_T tmp_size_3[2];
    int32_T tmp_size_4[2];
    int32_T tmp_size_5[2];
    int32_T O_Htm_tmp;
    int32_T O_Htm_tmp_0;
    int32_T i;
    int32_T idxStart_4Row;
    int32_T idxStart_6Row;
    int32_T y_tmp_0;
    int8_T y_tmp[9];
    boolean_T ROBOT_csi_0[3];

    /* Outputs for Atomic SubSystem: '<Root>/planar_robot3dof_FD' */
    /* Integrator: '<S1>/Integrator1' */
    planar_robot3dof_FD2_B.q[0] = planar_robot3dof_FD2_X.Integrator1_CSTATE[0];
    planar_robot3dof_FD2_B.q[1] = planar_robot3dof_FD2_X.Integrator1_CSTATE[1];
    planar_robot3dof_FD2_B.q[2] = planar_robot3dof_FD2_X.Integrator1_CSTATE[2];

    /* Integrator: '<S1>/Integrator' */
    planar_robot3dof_FD2_B.dq[0] = planar_robot3dof_FD2_X.Integrator_CSTATE[0];
    planar_robot3dof_FD2_B.dq[1] = planar_robot3dof_FD2_X.Integrator_CSTATE[1];
    planar_robot3dof_FD2_B.dq[2] = planar_robot3dof_FD2_X.Integrator_CSTATE[2];
    if (rtmIsMajorTimeStep((&planar_robot3dof_FD2_M))) {
      /* ZeroOrderHold: '<S1>/Zero-Order Hold' */
      rtb_ZeroOrderHold[0] = planar_robot3dof_FD2_B.q[0];
      rtb_ZeroOrderHold[1] = planar_robot3dof_FD2_B.q[1];
      rtb_ZeroOrderHold[2] = planar_robot3dof_FD2_B.q[2];

      /* MATLAB Function: '<S1>/calcSysMatrices' incorporates:
       *  Inport: '<Root>/arm_length'
       *  Inport: '<Root>/arm_link_radius'
       *  Inport: '<Root>/rho'
       */
      planar_robot3dof_FD2_eye(E_tmp);
      jointOrigins[0] = 0.0;
      jointOrigins[3] = planar_robot3dof_FD2_U.arm_length[0];
      jointOrigins[6] = planar_robot3dof_FD2_U.arm_length[1];
      m_tmp = planar_robot3dof_FD2_U.arm_link_radius *
        planar_robot3dof_FD2_U.arm_link_radius;
      m_tmp_0 = m_tmp * 3.1415926535897931;
      m = m_tmp_0 * planar_robot3dof_FD2_U.arm_length[0] *
        planar_robot3dof_FD2_U.rho;
      body_CenterOfMass_idx_0 = planar_robot3dof_FD2_U.arm_length[0] / 2.0;
      Iz = 0.25 * m * m_tmp + 0.083333333333333329 * m *
        (planar_robot3dof_FD2_U.arm_length[0] *
         planar_robot3dof_FD2_U.arm_length[0]);
      b_m = m;
      inertialTwist_pre[0] = 0.5 * m * m_tmp;
      inertialTwist_pre[1] = Iz;
      inertialTwist_pre[2] = Iz;
      inertialTwist_pre[3] = 0.0;
      inertialTwist_pre[4] = 0.0;
      inertialTwist_pre[5] = 0.0;
      planar_robot3dof_FD2_diag(&inertialTwist_pre[0], tmp2);

      /* ZeroOrderHold: '<S1>/Zero-Order Hold1' */
      rtb_ZeroOrderHold1_idx_0 = planar_robot3dof_FD2_B.dq[0];

      /* MATLAB Function: '<S1>/calcSysMatrices' */
      jointOrigins[1] = 0.0;
      jointOrigins[2] = 0.0;
      S[0] = 0.0;

      /* ZeroOrderHold: '<S1>/Zero-Order Hold1' */
      rtb_ZeroOrderHold1_idx_1 = planar_robot3dof_FD2_B.dq[1];

      /* MATLAB Function: '<S1>/calcSysMatrices' */
      jointOrigins[4] = 0.0;
      jointOrigins[5] = 0.0;
      S[3] = 0.0;

      /* ZeroOrderHold: '<S1>/Zero-Order Hold1' */
      rtb_ZeroOrderHold1_idx_2 = planar_robot3dof_FD2_B.dq[2];

      /* MATLAB Function: '<S1>/calcSysMatrices' incorporates:
       *  Derivative: '<S1>/Derivative1'
       *  Inport: '<Root>/arm_length'
       *  Inport: '<Root>/rho'
       *  ZeroOrderHold: '<S1>/Zero-Order Hold1'
       */
      jointOrigins[7] = 0.0;
      jointOrigins[8] = 0.0;
      S[6] = 0.0;
      S[1] = 0.0;
      S[4] = 0.0;
      S[7] = -body_CenterOfMass_idx_0;
      S[2] = -0.0;
      S[5] = body_CenterOfMass_idx_0;
      S[8] = 0.0;
      for (i = 0; i < 9; i++) {
        y_tmp_0 = c_b[i];
        y_tmp[i] = static_cast<int8_T>(y_tmp_0);
        y[i] = m * static_cast<real_T>(y_tmp_0);
        b_y[i] = m * S[i];
      }

      m = m_tmp_0 * planar_robot3dof_FD2_U.arm_length[1] *
        planar_robot3dof_FD2_U.rho;
      body_CenterOfMass_idx_0 = planar_robot3dof_FD2_U.arm_length[1] / 2.0;
      Iz = 0.25 * m * m_tmp + 0.083333333333333329 * m *
        (planar_robot3dof_FD2_U.arm_length[1] *
         planar_robot3dof_FD2_U.arm_length[1]);
      c_m = m;
      inertialTwist_pre[0] = 0.5 * m * m_tmp;
      inertialTwist_pre[1] = Iz;
      inertialTwist_pre[2] = Iz;
      inertialTwist_pre[3] = 0.0;
      inertialTwist_pre[4] = 0.0;
      inertialTwist_pre[5] = 0.0;
      planar_robot3dof_FD2_diag(&inertialTwist_pre[0], b_I);
      b_S[0] = 0.0;
      b_S[3] = 0.0;
      b_S[6] = 0.0;
      b_S[1] = 0.0;
      b_S[4] = 0.0;
      b_S[7] = -body_CenterOfMass_idx_0;
      b_S[2] = -0.0;
      b_S[5] = body_CenterOfMass_idx_0;
      b_S[8] = 0.0;
      for (i = 0; i < 9; i++) {
        c_y[i] = m * static_cast<real_T>(y_tmp[i]);
        d_y[i] = m * b_S[i];
      }

      m = m_tmp_0 * planar_robot3dof_FD2_U.arm_length[2] *
        planar_robot3dof_FD2_U.rho;
      body_CenterOfMass_idx_0 = planar_robot3dof_FD2_U.arm_length[2] / 2.0;
      Iz = 0.25 * m * m_tmp + 0.083333333333333329 * m *
        (planar_robot3dof_FD2_U.arm_length[2] *
         planar_robot3dof_FD2_U.arm_length[2]);
      c_S[0] = 0.0;
      c_S[3] = 0.0;
      c_S[6] = 0.0;
      c_S[1] = 0.0;
      c_S[4] = 0.0;
      c_S[7] = -body_CenterOfMass_idx_0;
      c_S[2] = -0.0;
      c_S[5] = body_CenterOfMass_idx_0;
      c_S[8] = 0.0;
      planar_robot3dof_FD2_repmat(ROBOT_csi);
      for (i = 0; i < 3; i++) {
        ROBOT_g0[12 * i] = E_tmp[3 * i];
        ROBOT_g0[12 * i + 1] = E_tmp[3 * i + 1];
        ROBOT_g0[12 * i + 2] = E_tmp[3 * i + 2];
        ROBOT_g0[i + 36] = 0.0;
      }

      ROBOT_g0[3] = 0.0;
      ROBOT_g0[15] = 0.0;
      ROBOT_g0[27] = 0.0;
      ROBOT_g0[39] = 1.0;
      for (i = 0; i < 3; i++) {
        ROBOT_g0[12 * i + 4] = E_tmp[3 * i];
        ROBOT_g0[12 * i + 5] = E_tmp[3 * i + 1];
        ROBOT_g0[12 * i + 6] = E_tmp[3 * i + 2];
        ROBOT_g0[i + 40] = jointOrigins[i + 3];
      }

      ROBOT_g0[7] = 0.0;
      ROBOT_g0[19] = 0.0;
      ROBOT_g0[31] = 0.0;
      ROBOT_g0[43] = 1.0;
      for (i = 0; i < 3; i++) {
        ROBOT_g0[12 * i + 8] = E_tmp[3 * i];
        ROBOT_g0[12 * i + 9] = E_tmp[3 * i + 1];
        ROBOT_g0[12 * i + 10] = E_tmp[3 * i + 2];
        ROBOT_g0[i + 44] = jointOrigins[i + 6];
      }

      ROBOT_g0[11] = 0.0;
      ROBOT_g0[23] = 0.0;
      ROBOT_g0[35] = 0.0;
      ROBOT_g0[47] = 1.0;
      for (i = 0; i < 9; i++) {
        jointOrigins[i] = m * c_S[i];
      }

      inertialTwist_pre[0] = 0.5 * m * m_tmp;
      inertialTwist_pre[1] = Iz;
      inertialTwist_pre[2] = Iz;
      inertialTwist_pre[3] = 0.0;
      inertialTwist_pre[4] = 0.0;
      inertialTwist_pre[5] = 0.0;
      planar_robot3dof_FD2_diag(&inertialTwist_pre[0], tmp);
      for (i = 0; i < 3; i++) {
        m_tmp = jointOrigins[i + 3];
        m_tmp_0 = jointOrigins[i];
        body_CenterOfMass_idx_0 = jointOrigins[i + 6];
        for (O_Htm_tmp = 0; O_Htm_tmp < 3; O_Htm_tmp++) {
          idxStart_4Row = 3 * O_Htm_tmp + i;
          y_tmp_0 = 3 * O_Htm_tmp + 1;
          idxStart_6Row = 3 * O_Htm_tmp + 2;
          tmp2_0[idxStart_4Row] = tmp2[idxStart_4Row] - ((S[i + 3] * b_m *
            S[y_tmp_0] + b_m * S[i] * S[3 * O_Htm_tmp]) + S[i + 6] * b_m *
            S[idxStart_6Row]);
          b_I_0[idxStart_4Row] = b_I[idxStart_4Row] - ((b_S[i + 3] * c_m *
            b_S[y_tmp_0] + c_m * b_S[i] * b_S[3 * O_Htm_tmp]) + b_S[i + 6] * c_m
            * b_S[idxStart_6Row]);
          tmp_0[idxStart_4Row] = tmp[idxStart_4Row] - ((c_S[3 * O_Htm_tmp] *
            m_tmp_0 + c_S[y_tmp_0] * m_tmp) + c_S[idxStart_6Row] *
            body_CenterOfMass_idx_0);
          idxStart_4Row = 3 * i + O_Htm_tmp;
          y_tmp_0 = 18 * i + O_Htm_tmp;
          ROBOT_Mass[y_tmp_0] = y[idxStart_4Row];
          ROBOT_Mass[O_Htm_tmp + 18 * (i + 3)] = S[idxStart_4Row] * -b_m;
          ROBOT_Mass[y_tmp_0 + 3] = b_y[idxStart_4Row];
        }
      }

      for (i = 0; i < 3; i++) {
        idxStart_4Row = (i + 3) * 18;
        ROBOT_Mass[idxStart_4Row + 3] = tmp2_0[3 * i];
        ROBOT_Mass[18 * i + 6] = c_y[3 * i];
        ROBOT_Mass[idxStart_4Row + 6] = b_S[3 * i] * -c_m;
        ROBOT_Mass[18 * i + 9] = d_y[3 * i];
        ROBOT_Mass[idxStart_4Row + 9] = b_I_0[3 * i];
        ROBOT_Mass[18 * i + 12] = static_cast<real_T>(y_tmp[3 * i]) * m;
        ROBOT_Mass[idxStart_4Row + 12] = c_S[3 * i] * -m;
        ROBOT_Mass[18 * i + 15] = jointOrigins[3 * i];
        ROBOT_Mass[idxStart_4Row + 15] = tmp_0[3 * i];
        y_tmp_0 = 3 * i + 1;
        ROBOT_Mass[idxStart_4Row + 4] = tmp2_0[y_tmp_0];
        ROBOT_Mass[18 * i + 7] = c_y[y_tmp_0];
        ROBOT_Mass[idxStart_4Row + 7] = b_S[y_tmp_0] * -c_m;
        ROBOT_Mass[18 * i + 10] = d_y[y_tmp_0];
        ROBOT_Mass[idxStart_4Row + 10] = b_I_0[y_tmp_0];
        ROBOT_Mass[18 * i + 13] = static_cast<real_T>(y_tmp[y_tmp_0]) * m;
        ROBOT_Mass[idxStart_4Row + 13] = c_S[y_tmp_0] * -m;
        ROBOT_Mass[18 * i + 16] = jointOrigins[y_tmp_0];
        ROBOT_Mass[idxStart_4Row + 16] = tmp_0[y_tmp_0];
        y_tmp_0 = 3 * i + 2;
        ROBOT_Mass[idxStart_4Row + 5] = tmp2_0[y_tmp_0];
        ROBOT_Mass[18 * i + 8] = c_y[y_tmp_0];
        ROBOT_Mass[idxStart_4Row + 8] = b_S[y_tmp_0] * -c_m;
        ROBOT_Mass[18 * i + 11] = d_y[y_tmp_0];
        ROBOT_Mass[idxStart_4Row + 11] = b_I_0[y_tmp_0];
        ROBOT_Mass[18 * i + 14] = static_cast<real_T>(y_tmp[y_tmp_0]) * m;
        ROBOT_Mass[idxStart_4Row + 14] = c_S[y_tmp_0] * -m;
        ROBOT_Mass[18 * i + 17] = jointOrigins[y_tmp_0];
        ROBOT_Mass[idxStart_4Row + 17] = tmp_0[y_tmp_0];
      }

      std::memset(&planar_robot3dof_FD2_B.M[0], 0, 9U * sizeof(real_T));
      std::memset(&planar_robot3dof_FD2_B.CC[0], 0, 9U * sizeof(real_T));
      planar_robot3dof_FD2_B.g[0] = 0.0;
      planar_robot3dof_FD2_B.g[1] = 0.0;
      planar_robot3dof_FD2_B.g[2] = 0.0;
      std::memset(&J_pre[0], 0, 18U * sizeof(real_T));
      std::memset(&dJ_pre[0], 0, 18U * sizeof(real_T));
      for (i = 0; i < 6; i++) {
        inertialTwist_pre[i] = 0.0;
      }

      std::memset(&O_Htm_pre[0], 0, sizeof(real_T) << 4U);
      O_Htm_pre[0] = 1.0;
      O_Htm_pre[5] = 1.0;
      O_Htm_pre[10] = 1.0;
      O_Htm_pre[15] = 1.0;
      tmp[0] = 0.0;
      tmp[4] = 0.0;
      tmp[8] = 0.0;
      for (y_tmp_0 = 0; y_tmp_0 < 3; y_tmp_0++) {
        idxStart_4Row = y_tmp_0 << 2;
        idxStart_6Row = 6 * y_tmp_0;
        m_tmp = planar_robot3dof_FD2_B.dq[y_tmp_0];
        for (i = 0; i < 6; i++) {
          relTwist[i] = ROBOT_csi[idxStart_6Row + i] * m_tmp;
        }

        m_tmp = ROBOT_csi[idxStart_6Row + 3];
        ROBOT_csi_0[0] = (m_tmp == 0.0);
        m = ROBOT_csi[idxStart_6Row + 4];
        ROBOT_csi_0[1] = (m == 0.0);
        b_m = ROBOT_csi[idxStart_6Row + 5];
        ROBOT_csi_0[2] = (b_m == 0.0);
        if (planar_robot3dof_FD2_all(ROBOT_csi_0)) {
          m_tmp = rtb_ZeroOrderHold[y_tmp_0];
          for (i = 0; i < 3; i++) {
            O_Htm_tmp_0 = i << 2;
            O_Htm[O_Htm_tmp_0] = E_tmp[3 * i];
            O_Htm[O_Htm_tmp_0 + 1] = E_tmp[3 * i + 1];
            O_Htm[O_Htm_tmp_0 + 2] = E_tmp[3 * i + 2];
            O_Htm[i + 12] = ROBOT_csi[idxStart_6Row + i] * m_tmp;
          }

          O_Htm[3] = 0.0;
          O_Htm[7] = 0.0;
          O_Htm[11] = 0.0;
          O_Htm[15] = 1.0;
        } else {
          jointOrigins[0] = 0.0;
          jointOrigins[3] = -b_m;
          jointOrigins[6] = m;
          jointOrigins[1] = b_m;
          jointOrigins[4] = 0.0;
          jointOrigins[7] = -m_tmp;
          jointOrigins[2] = -m;
          jointOrigins[5] = m_tmp;
          jointOrigins[8] = 0.0;
          m_tmp = rtb_ZeroOrderHold[y_tmp_0];
          m = std::sin(m_tmp);
          Iz = std::cos(m_tmp);
          for (i = 0; i < 3; i++) {
            for (O_Htm_tmp = 0; O_Htm_tmp < 3; O_Htm_tmp++) {
              tmp2[i + 3 * O_Htm_tmp] = (jointOrigins[3 * O_Htm_tmp + 1] *
                jointOrigins[i + 3] + jointOrigins[3 * O_Htm_tmp] *
                jointOrigins[i]) + jointOrigins[3 * O_Htm_tmp + 2] *
                jointOrigins[i + 6];
            }
          }

          for (i = 0; i < 3; i++) {
            O_Htm_tmp_0 = i << 2;
            O_Htm[O_Htm_tmp_0] = (jointOrigins[3 * i] * m + tmp2[3 * i] * (1.0 -
              Iz)) + E_tmp[3 * i];
            O_Htm_tmp = 3 * i + 1;
            O_Htm[O_Htm_tmp_0 + 1] = ((1.0 - Iz) * tmp2[O_Htm_tmp] +
              jointOrigins[O_Htm_tmp] * m) + E_tmp[O_Htm_tmp];
            O_Htm_tmp = 3 * i + 2;
            O_Htm[O_Htm_tmp_0 + 2] = ((1.0 - Iz) * tmp2[O_Htm_tmp] +
              jointOrigins[O_Htm_tmp] * m) + E_tmp[O_Htm_tmp];
            O_Htm[i + 12] = 0.0;
          }

          O_Htm[3] = 0.0;
          O_Htm[7] = 0.0;
          O_Htm[11] = 0.0;
          O_Htm[15] = 1.0;
        }

        ROBOT_g0_size[0] = 4;
        ROBOT_g0_size[1] = 4;
        for (i = 0; i < 4; i++) {
          for (O_Htm_tmp = 0; O_Htm_tmp < 4; O_Htm_tmp++) {
            ROBOT_g0_data[O_Htm_tmp + (i << 2)] = ROBOT_g0[(idxStart_4Row +
              O_Htm_tmp) + 12 * i];
          }
        }

        planar_robot3dof_FD2_mtimes(ROBOT_g0_data, ROBOT_g0_size, O_Htm,
          Htm_data, Htm_size);
        for (i = 0; i < 4; i++) {
          m_tmp = O_Htm_pre[i + 4];
          m = O_Htm_pre[i];
          b_m = O_Htm_pre[i + 8];
          c_m = O_Htm_pre[i + 12];
          for (O_Htm_tmp = 0; O_Htm_tmp < 4; O_Htm_tmp++) {
            O_Htm_tmp_0 = O_Htm_tmp << 2;
            O_Htm[i + O_Htm_tmp_0] = ((Htm_data[O_Htm_tmp_0 + 1] * m_tmp +
              Htm_data[O_Htm_tmp_0] * m) + Htm_data[O_Htm_tmp_0 + 2] * b_m) +
              Htm_data[O_Htm_tmp_0 + 3] * c_m;
          }
        }

        for (i = 0; i < 6; i++) {
          inertialTwist[i] = relTwist[i];
        }

        for (i = 0; i < 3; i++) {
          jointOrigins[3 * i] = Htm_data[i];
          jointOrigins[3 * i + 1] = Htm_data[i + Htm_size[0]];
          jointOrigins[3 * i + 2] = Htm_data[(Htm_size[0] << 1) + i];
        }

        for (i = 0; i < 9; i++) {
          tmp2[i] = -jointOrigins[i];
        }

        m_tmp = Htm_data[Htm_size[0] * 3 + 2];
        tmp[3] = -m_tmp;
        m_tmp_0 = Htm_data[Htm_size[0] * 3 + 1];
        tmp[6] = m_tmp_0;
        tmp[1] = m_tmp;
        m_tmp = Htm_data[Htm_size[0] * 3];
        tmp[7] = -m_tmp;
        tmp[2] = -m_tmp_0;
        tmp[5] = m_tmp;
        for (i = 0; i < 3; i++) {
          m_tmp = tmp2[i + 3];
          m_tmp_0 = tmp2[i];
          body_CenterOfMass_idx_0 = tmp2[i + 6];
          for (O_Htm_tmp = 0; O_Htm_tmp < 3; O_Htm_tmp++) {
            S[i + 3 * O_Htm_tmp] = (tmp[3 * O_Htm_tmp + 1] * m_tmp + tmp[3 *
              O_Htm_tmp] * m_tmp_0) + tmp[3 * O_Htm_tmp + 2] *
              body_CenterOfMass_idx_0;
            invAd[O_Htm_tmp + 6 * i] = jointOrigins[3 * i + O_Htm_tmp];
          }
        }

        for (i = 0; i < 3; i++) {
          O_Htm_tmp = (i + 3) * 6;
          invAd[O_Htm_tmp] = S[3 * i];
          invAd[6 * i + 3] = 0.0;
          invAd[O_Htm_tmp + 3] = jointOrigins[3 * i];
          idxStart_4Row = 3 * i + 1;
          invAd[O_Htm_tmp + 1] = S[idxStart_4Row];
          invAd[6 * i + 4] = 0.0;
          invAd[O_Htm_tmp + 4] = jointOrigins[idxStart_4Row];
          idxStart_4Row = 3 * i + 2;
          invAd[O_Htm_tmp + 2] = S[idxStart_4Row];
          invAd[6 * i + 5] = 0.0;
          invAd[O_Htm_tmp + 5] = jointOrigins[idxStart_4Row];
        }

        std::memset(&J[0], 0, 18U * sizeof(real_T));
        std::memset(&dJ[0], 0, 18U * sizeof(real_T));
        if (y_tmp_0 + 1 > 1) {
          for (i = 0; i < 6; i++) {
            m_tmp = 0.0;
            for (O_Htm_tmp = 0; O_Htm_tmp < 6; O_Htm_tmp++) {
              m_tmp += invAd[6 * O_Htm_tmp + i] * inertialTwist_pre[O_Htm_tmp];
            }

            inertialTwist[i] = relTwist[i] + m_tmp;
          }

          J_pre_size[0] = 6;
          J_pre_size[1] = y_tmp_0;
          for (i = 0; i < y_tmp_0; i++) {
            for (O_Htm_tmp = 0; O_Htm_tmp < 6; O_Htm_tmp++) {
              J_pre_data[O_Htm_tmp + 6 * i] = J_pre[6 * i + O_Htm_tmp];
            }
          }

          planar_robot3dof_FD2_mtimes_e(invAd, J_pre_data, J_pre_size, tmp_data,
            Htm_size);
          idxStart_4Row = Htm_size[1];
          for (i = 0; i < idxStart_4Row; i++) {
            for (O_Htm_tmp = 0; O_Htm_tmp < 6; O_Htm_tmp++) {
              J[O_Htm_tmp + 6 * i] = tmp_data[6 * i + O_Htm_tmp];
            }
          }

          jointOrigins[0] = 0.0;
          jointOrigins[3] = -relTwist[5];
          jointOrigins[6] = relTwist[4];
          jointOrigins[1] = relTwist[5];
          jointOrigins[4] = 0.0;
          jointOrigins[7] = -relTwist[3];
          jointOrigins[2] = -relTwist[4];
          jointOrigins[5] = relTwist[3];
          jointOrigins[8] = 0.0;
          dJ_pre_size[0] = 6;
          dJ_pre_size[1] = y_tmp_0;
          for (i = 0; i < y_tmp_0; i++) {
            for (O_Htm_tmp = 0; O_Htm_tmp < 6; O_Htm_tmp++) {
              dJ_pre_data[O_Htm_tmp + 6 * i] = dJ_pre[6 * i + O_Htm_tmp];
            }
          }

          m_0[18] = 0.0;
          m_0[24] = -relTwist[2];
          m_0[30] = relTwist[1];
          m_0[19] = relTwist[2];
          m_0[25] = 0.0;
          m_0[31] = -relTwist[0];
          m_0[20] = -relTwist[1];
          m_0[26] = relTwist[0];
          m_0[32] = 0.0;
          for (i = 0; i < 3; i++) {
            m_tmp = jointOrigins[3 * i];
            m_0[6 * i] = m_tmp;
            m_0[6 * i + 3] = 0.0;
            O_Htm_tmp = (i + 3) * 6;
            m_0[O_Htm_tmp + 3] = m_tmp;
            m_tmp = jointOrigins[3 * i + 1];
            m_0[6 * i + 1] = m_tmp;
            m_0[6 * i + 4] = 0.0;
            m_0[O_Htm_tmp + 4] = m_tmp;
            m_tmp = jointOrigins[3 * i + 2];
            m_0[6 * i + 2] = m_tmp;
            m_0[6 * i + 5] = 0.0;
            m_0[O_Htm_tmp + 5] = m_tmp;
          }

          J_pre_size[0] = 6;
          J_pre_size[1] = y_tmp_0;
          for (i = 0; i < y_tmp_0; i++) {
            for (O_Htm_tmp = 0; O_Htm_tmp < 6; O_Htm_tmp++) {
              J_pre_data[O_Htm_tmp + 6 * i] = J[6 * i + O_Htm_tmp];
            }
          }

          planar_robot3dof_FD2_mtimes_e(invAd, dJ_pre_data, dJ_pre_size,
            tmp_data, Htm_size);
          planar_robot3dof_FD2_mtimes_e(m_0, J_pre_data, J_pre_size, tmp_data,
            tmp_size_5);
          if (Htm_size[1] == tmp_size_5[1]) {
            dJ_pre_size[0] = 6;
            dJ_pre_size[1] = y_tmp_0;
            for (i = 0; i < y_tmp_0; i++) {
              for (O_Htm_tmp = 0; O_Htm_tmp < 6; O_Htm_tmp++) {
                dJ_pre_data[O_Htm_tmp + 6 * i] = dJ_pre[6 * i + O_Htm_tmp];
              }
            }

            planar_robot3dof_FD2_mtimes_e(invAd, dJ_pre_data, dJ_pre_size,
              tmp_data, Htm_size);
            m_0[18] = 0.0;
            m_0[24] = -relTwist[2];
            m_0[30] = relTwist[1];
            m_0[19] = relTwist[2];
            m_0[25] = 0.0;
            m_0[31] = -relTwist[0];
            m_0[20] = -relTwist[1];
            m_0[26] = relTwist[0];
            m_0[32] = 0.0;
            for (i = 0; i < 3; i++) {
              m_tmp = jointOrigins[3 * i];
              m_0[6 * i] = m_tmp;
              m_0[6 * i + 3] = 0.0;
              O_Htm_tmp = (i + 3) * 6;
              m_0[O_Htm_tmp + 3] = m_tmp;
              m_tmp = jointOrigins[3 * i + 1];
              m_0[6 * i + 1] = m_tmp;
              m_0[6 * i + 4] = 0.0;
              m_0[O_Htm_tmp + 4] = m_tmp;
              m_tmp = jointOrigins[3 * i + 2];
              m_0[6 * i + 2] = m_tmp;
              m_0[6 * i + 5] = 0.0;
              m_0[O_Htm_tmp + 5] = m_tmp;
            }

            J_pre_size[0] = 6;
            J_pre_size[1] = y_tmp_0;
            for (i = 0; i < y_tmp_0; i++) {
              for (O_Htm_tmp = 0; O_Htm_tmp < 6; O_Htm_tmp++) {
                J_pre_data[O_Htm_tmp + 6 * i] = J[6 * i + O_Htm_tmp];
              }
            }

            planar_robot3dof_FD2_mtimes_e(m_0, J_pre_data, J_pre_size,
              dJ_pre_data, dJ_pre_size);
            idxStart_4Row = Htm_size[1];
            for (i = 0; i < idxStart_4Row; i++) {
              for (O_Htm_tmp = 0; O_Htm_tmp < 6; O_Htm_tmp++) {
                O_Htm_tmp_0 = 6 * i + O_Htm_tmp;
                dJ[O_Htm_tmp_0] = tmp_data[O_Htm_tmp_0] -
                  dJ_pre_data[O_Htm_tmp_0];
              }
            }
          } else {
            planar_rob_binary_expand_op_lmf(dJ, y_tmp_0, invAd, dJ_pre,
              jointOrigins, relTwist, J);
          }
        }

        for (i = 0; i < 6; i++) {
          J[i + 6 * y_tmp_0] = ROBOT_csi[idxStart_6Row + i];
        }

        J_size[0] = 6;
        J_size[1] = y_tmp_0 + 1;
        for (i = 0; i <= y_tmp_0; i++) {
          for (O_Htm_tmp = 0; O_Htm_tmp < 6; O_Htm_tmp++) {
            J_pre[O_Htm_tmp + 6 * i] = J[6 * i + O_Htm_tmp];
          }
        }

        ROBOT_Mass_size[0] = 6;
        ROBOT_Mass_size[1] = 6;
        for (i = 0; i < 6; i++) {
          for (O_Htm_tmp = 0; O_Htm_tmp < 6; O_Htm_tmp++) {
            ROBOT_Mass_data[O_Htm_tmp + 6 * i] = ROBOT_Mass[(idxStart_6Row +
              O_Htm_tmp) + 18 * i];
          }
        }

        planar_robot3dof_FD2_mtimes_ev(J_pre, J_size, ROBOT_Mass_data,
          ROBOT_Mass_size, dJ_pre, Htm_size);
        J_size[0] = 6;
        J_size[1] = y_tmp_0 + 1;
        J_size_0[0] = 6;
        J_size_0[1] = y_tmp_0 + 1;
        for (i = 0; i <= y_tmp_0; i++) {
          for (O_Htm_tmp = 0; O_Htm_tmp < 6; O_Htm_tmp++) {
            idxStart_4Row = 6 * i + O_Htm_tmp;
            m_tmp = J[idxStart_4Row];
            J_pre[idxStart_4Row] = m_tmp;
            J_data[idxStart_4Row] = m_tmp;
          }
        }

        planar_robot3dof_FD2_mtimes_evj(dJ_pre, Htm_size, J_pre, J_size, y,
          tmp_size_5);
        planar_robot3dof_FD2_mtimes_evj(dJ_pre, Htm_size, J_data, J_size_0, y,
          tmp_size_4);
        if ((y_tmp_0 + 1 == tmp_size_5[0]) && (y_tmp_0 + 1 == tmp_size_4[1])) {
          J_size[0] = 6;
          J_size[1] = y_tmp_0 + 1;
          for (i = 0; i <= y_tmp_0; i++) {
            for (O_Htm_tmp = 0; O_Htm_tmp < 6; O_Htm_tmp++) {
              J_pre[O_Htm_tmp + 6 * i] = J[6 * i + O_Htm_tmp];
            }
          }

          planar_robot3dof_FD2_mtimes_evj(dJ_pre, Htm_size, J_pre, J_size, y,
            tmp_size_5);
          for (i = 0; i <= y_tmp_0; i++) {
            for (O_Htm_tmp = 0; O_Htm_tmp <= y_tmp_0; O_Htm_tmp++) {
              tmp2[O_Htm_tmp + (y_tmp_0 + 1) * i] = planar_robot3dof_FD2_B.M[3 *
                i + O_Htm_tmp] + y[tmp_size_5[0] * i + O_Htm_tmp];
            }
          }

          idxStart_4Row = y_tmp_0 + 1;
          O_Htm_tmp_0 = y_tmp_0 + 1;
          for (i = 0; i < idxStart_4Row; i++) {
            for (O_Htm_tmp = 0; O_Htm_tmp < O_Htm_tmp_0; O_Htm_tmp++) {
              planar_robot3dof_FD2_B.M[O_Htm_tmp + 3 * i] = tmp2[(y_tmp_0 + 1) *
                i + O_Htm_tmp];
            }
          }
        } else {
          planar_robo_binary_expand_op_lm(planar_robot3dof_FD2_B.M, y_tmp_0,
            dJ_pre, Htm_size, J);
        }

        jointOrigins[0] = 0.0;
        jointOrigins[3] = -inertialTwist[5];
        jointOrigins[6] = inertialTwist[4];
        jointOrigins[1] = inertialTwist[5];
        jointOrigins[4] = 0.0;
        jointOrigins[7] = -inertialTwist[3];
        jointOrigins[2] = -inertialTwist[4];
        jointOrigins[5] = inertialTwist[3];
        jointOrigins[8] = 0.0;
        for (i = 0; i < 3; i++) {
          idxStart_4Row = idxStart_6Row + i;
          m = ROBOT_Mass[idxStart_4Row + 3];
          b_m = ROBOT_Mass[idxStart_4Row + 57];
          c_m = ROBOT_Mass[idxStart_4Row + 21];
          m_tmp_0 = ROBOT_Mass[idxStart_4Row + 75];
          body_CenterOfMass_idx_0 = ROBOT_Mass[idxStart_4Row + 93];
          Iz = ROBOT_Mass[idxStart_4Row + 39];
          for (O_Htm_tmp = 0; O_Htm_tmp < 3; O_Htm_tmp++) {
            m_tmp = jointOrigins[3 * O_Htm_tmp];
            S_0 = m * m_tmp;
            tmp2_1 = b_m * m_tmp;
            m_tmp = jointOrigins[3 * O_Htm_tmp + 1];
            S_0 += c_m * m_tmp;
            tmp2_1 += m_tmp_0 * m_tmp;
            m_tmp = jointOrigins[3 * O_Htm_tmp + 2];
            idxStart_4Row = 3 * O_Htm_tmp + i;
            tmp2[idxStart_4Row] = body_CenterOfMass_idx_0 * m_tmp + tmp2_1;
            S[idxStart_4Row] = Iz * m_tmp + S_0;
          }
        }

        m = ROBOT_Mass[idxStart_6Row];
        J_size[0] = 6;
        J_size[1] = y_tmp_0 + 1;
        for (i = 0; i <= y_tmp_0; i++) {
          for (O_Htm_tmp = 0; O_Htm_tmp < 6; O_Htm_tmp++) {
            J_pre[O_Htm_tmp + 6 * i] = J[6 * i + O_Htm_tmp];
          }
        }

        for (i = 0; i < 3; i++) {
          invAd[6 * i] = jointOrigins[3 * i] * m;
          O_Htm_tmp = (i + 3) * 6;
          invAd[O_Htm_tmp] = -S[i];
          invAd[6 * i + 3] = S[3 * i];
          invAd[O_Htm_tmp + 3] = tmp2[3 * i] - tmp2[i];
          idxStart_6Row = 3 * i + 1;
          invAd[6 * i + 1] = jointOrigins[idxStart_6Row] * m;
          invAd[O_Htm_tmp + 1] = -S[i + 3];
          invAd[6 * i + 4] = S[idxStart_6Row];
          invAd[O_Htm_tmp + 4] = tmp2[idxStart_6Row] - tmp2[i + 3];
          idxStart_6Row = 3 * i + 2;
          invAd[6 * i + 2] = jointOrigins[idxStart_6Row] * m;
          invAd[O_Htm_tmp + 2] = -S[i + 6];
          invAd[6 * i + 5] = S[idxStart_6Row];
          invAd[O_Htm_tmp + 5] = tmp2[idxStart_6Row] - tmp2[i + 6];
        }

        J_size_0[0] = 6;
        J_size_0[1] = y_tmp_0 + 1;
        J_size_1[0] = 6;
        J_size_1[1] = y_tmp_0 + 1;
        for (i = 0; i <= y_tmp_0; i++) {
          for (O_Htm_tmp = 0; O_Htm_tmp < 6; O_Htm_tmp++) {
            idxStart_4Row = 6 * i + O_Htm_tmp;
            m_tmp = J[idxStart_4Row];
            J_data[idxStart_4Row] = m_tmp;
            J_data_0[O_Htm_tmp + 6 * i] = m_tmp;
          }
        }

        for (i = 0; i < 3; i++) {
          m_0[6 * i] = jointOrigins[3 * i] * m;
          O_Htm_tmp = (i + 3) * 6;
          m_0[O_Htm_tmp] = -S[i];
          m_0[6 * i + 3] = S[3 * i];
          m_0[O_Htm_tmp + 3] = tmp2[3 * i] - tmp2[i];
          idxStart_6Row = 3 * i + 1;
          m_0[6 * i + 1] = jointOrigins[idxStart_6Row] * m;
          m_0[O_Htm_tmp + 1] = -S[i + 3];
          m_0[6 * i + 4] = S[idxStart_6Row];
          m_0[O_Htm_tmp + 4] = tmp2[idxStart_6Row] - tmp2[i + 3];
          idxStart_6Row = 3 * i + 2;
          m_0[6 * i + 2] = jointOrigins[idxStart_6Row] * m;
          m_0[O_Htm_tmp + 2] = -S[i + 6];
          m_0[6 * i + 5] = S[idxStart_6Row];
          m_0[O_Htm_tmp + 5] = tmp2[idxStart_6Row] - tmp2[i + 6];
        }

        J_size_2[0] = 6;
        J_size_2[1] = y_tmp_0 + 1;
        J_size_3[0] = 6;
        J_size_3[1] = y_tmp_0 + 1;
        for (i = 0; i <= y_tmp_0; i++) {
          for (O_Htm_tmp = 0; O_Htm_tmp < 6; O_Htm_tmp++) {
            idxStart_4Row = 6 * i + O_Htm_tmp;
            m_tmp = J[idxStart_4Row];
            J_data_1[idxStart_4Row] = m_tmp;
            J_data_2[O_Htm_tmp + 6 * i] = m_tmp;
          }
        }

        for (i = 0; i < 3; i++) {
          m_1[6 * i] = jointOrigins[3 * i] * m;
          O_Htm_tmp = (i + 3) * 6;
          m_1[O_Htm_tmp] = -S[i];
          m_1[6 * i + 3] = S[3 * i];
          m_1[O_Htm_tmp + 3] = tmp2[3 * i] - tmp2[i];
          idxStart_6Row = 3 * i + 1;
          m_1[6 * i + 1] = jointOrigins[idxStart_6Row] * m;
          m_1[O_Htm_tmp + 1] = -S[i + 3];
          m_1[6 * i + 4] = S[idxStart_6Row];
          m_1[O_Htm_tmp + 4] = tmp2[idxStart_6Row] - tmp2[i + 3];
          idxStart_6Row = 3 * i + 2;
          m_1[6 * i + 2] = jointOrigins[idxStart_6Row] * m;
          m_1[O_Htm_tmp + 2] = -S[i + 6];
          m_1[6 * i + 5] = S[idxStart_6Row];
          m_1[O_Htm_tmp + 5] = tmp2[idxStart_6Row] - tmp2[i + 6];
        }

        J_size_4[0] = 6;
        J_size_4[1] = y_tmp_0 + 1;
        dJ_size[0] = 6;
        dJ_size[1] = y_tmp_0 + 1;
        J_size_5[0] = 6;
        J_size_5[1] = y_tmp_0 + 1;
        for (i = 0; i <= y_tmp_0; i++) {
          for (O_Htm_tmp = 0; O_Htm_tmp < 6; O_Htm_tmp++) {
            idxStart_6Row = 6 * i + O_Htm_tmp;
            m_tmp = J[idxStart_6Row];
            idxStart_4Row = 6 * i + O_Htm_tmp;
            J_data_3[idxStart_4Row] = m_tmp;
            dJ_data[idxStart_4Row] = dJ[idxStart_6Row];
            J_data_4[idxStart_4Row] = m_tmp;
          }
        }

        for (i = 0; i < 3; i++) {
          m_2[6 * i] = jointOrigins[3 * i] * m;
          O_Htm_tmp = (i + 3) * 6;
          m_2[O_Htm_tmp] = -S[i];
          m_2[6 * i + 3] = S[3 * i];
          m_2[O_Htm_tmp + 3] = tmp2[3 * i] - tmp2[i];
          idxStart_6Row = 3 * i + 1;
          m_2[6 * i + 1] = jointOrigins[idxStart_6Row] * m;
          m_2[O_Htm_tmp + 1] = -S[i + 3];
          m_2[6 * i + 4] = S[idxStart_6Row];
          m_2[O_Htm_tmp + 4] = tmp2[idxStart_6Row] - tmp2[i + 3];
          idxStart_6Row = 3 * i + 2;
          m_2[6 * i + 2] = jointOrigins[idxStart_6Row] * m;
          m_2[O_Htm_tmp + 2] = -S[i + 6];
          m_2[6 * i + 5] = S[idxStart_6Row];
          m_2[O_Htm_tmp + 5] = tmp2[idxStart_6Row] - tmp2[i + 6];
        }

        J_size_6[0] = 6;
        J_size_6[1] = y_tmp_0 + 1;
        dJ_size_0[0] = 6;
        dJ_size_0[1] = y_tmp_0 + 1;
        for (i = 0; i <= y_tmp_0; i++) {
          for (O_Htm_tmp = 0; O_Htm_tmp < 6; O_Htm_tmp++) {
            idxStart_6Row = 6 * i + O_Htm_tmp;
            J_data_5[idxStart_6Row] = J[idxStart_6Row];
            dJ_data_0[idxStart_6Row] = dJ[idxStart_6Row];
          }
        }

        planar_robot3dof_FD_mtimes_evjz(J_pre, J_size, invAd, tmp_data_2,
          tmp_size_5);
        planar_robot3dof_FD2_mtimes_evj(tmp_data_2, tmp_size_5, J_data, J_size_0,
          y, tmp_size_4);
        planar_robot3dof_FD_mtimes_evjz(J_data_0, J_size_1, m_0, tmp_data_2,
          tmp_size_5);
        planar_robot3dof_FD2_mtimes_evj(tmp_data_2, tmp_size_5, J_data_1,
          J_size_2, y, tmp_size_0);
        planar_robot3dof_FD_mtimes_evjz(J_data_2, J_size_3, m_1, tmp_data_2,
          tmp_size_5);
        planar_robot3dof_FD2_mtimes_evj(tmp_data_2, tmp_size_5, J_data_3,
          J_size_4, y, tmp_size_1);
        planar_robot3dof_FD2_mtimes_evj(dJ_pre, Htm_size, dJ_data, dJ_size, y,
          tmp_size_5);
        planar_robot3dof_FD_mtimes_evjz(J_data_4, J_size_5, m_2, tmp_data_2,
          tmp_size_2);
        planar_robot3dof_FD2_mtimes_evj(tmp_data_2, tmp_size_2, J_data_5,
          J_size_6, y, tmp_size_3);
        planar_robot3dof_FD2_mtimes_evj(dJ_pre, Htm_size, dJ_data_0, dJ_size_0,
          y, tmp_size_2);
        if ((y_tmp_0 + 1 == tmp_size_4[0]) && (y_tmp_0 + 1 == tmp_size_0[1]) &&
            ((y_tmp_0 + 1 == 1 ? tmp_size_1[0] : y_tmp_0 + 1) == tmp_size_5[0]) &&
            ((y_tmp_0 + 1 == 1 ? tmp_size_3[1] : y_tmp_0 + 1) == tmp_size_2[1]))
        {
          J_size[0] = 6;
          J_size[1] = y_tmp_0 + 1;
          for (i = 0; i <= y_tmp_0; i++) {
            for (O_Htm_tmp = 0; O_Htm_tmp < 6; O_Htm_tmp++) {
              J_pre[O_Htm_tmp + 6 * i] = J[6 * i + O_Htm_tmp];
            }
          }

          for (i = 0; i < 3; i++) {
            invAd[6 * i] = jointOrigins[3 * i] * m;
            O_Htm_tmp = (i + 3) * 6;
            invAd[O_Htm_tmp] = -S[i];
            invAd[6 * i + 3] = S[3 * i];
            invAd[O_Htm_tmp + 3] = tmp2[3 * i] - tmp2[i];
            idxStart_6Row = 3 * i + 1;
            invAd[6 * i + 1] = jointOrigins[idxStart_6Row] * m;
            invAd[O_Htm_tmp + 1] = -S[i + 3];
            invAd[6 * i + 4] = S[idxStart_6Row];
            invAd[O_Htm_tmp + 4] = tmp2[idxStart_6Row] - tmp2[i + 3];
            idxStart_6Row = 3 * i + 2;
            invAd[6 * i + 2] = jointOrigins[idxStart_6Row] * m;
            invAd[O_Htm_tmp + 2] = -S[i + 6];
            invAd[6 * i + 5] = S[idxStart_6Row];
            invAd[O_Htm_tmp + 5] = tmp2[idxStart_6Row] - tmp2[i + 6];
          }

          J_size_0[0] = 6;
          J_size_0[1] = y_tmp_0 + 1;
          for (i = 0; i <= y_tmp_0; i++) {
            for (O_Htm_tmp = 0; O_Htm_tmp < 6; O_Htm_tmp++) {
              J_data[O_Htm_tmp + 6 * i] = J[6 * i + O_Htm_tmp];
            }
          }

          planar_robot3dof_FD_mtimes_evjz(J_pre, J_size, invAd, tmp_data_2,
            tmp_size_4);
          planar_robot3dof_FD2_mtimes_evj(tmp_data_2, tmp_size_4, J_data,
            J_size_0, y, tmp_size_5);
          dJ_size[0] = 6;
          dJ_size[1] = y_tmp_0 + 1;
          for (i = 0; i <= y_tmp_0; i++) {
            for (O_Htm_tmp = 0; O_Htm_tmp < 6; O_Htm_tmp++) {
              dJ_data[O_Htm_tmp + 6 * i] = dJ[6 * i + O_Htm_tmp];
            }
          }

          planar_robot3dof_FD2_mtimes_evj(dJ_pre, Htm_size, dJ_data, dJ_size,
            tmp2, tmp_size_4);
          idxStart_6Row = y_tmp_0 + 1;
          idxStart_4Row = y_tmp_0 + 1;
          for (i = 0; i <= y_tmp_0; i++) {
            for (O_Htm_tmp = 0; O_Htm_tmp <= y_tmp_0; O_Htm_tmp++) {
              jointOrigins[O_Htm_tmp + (y_tmp_0 + 1) * i] =
                (planar_robot3dof_FD2_B.CC[3 * i + O_Htm_tmp] + y[tmp_size_5[0] *
                 i + O_Htm_tmp]) + tmp2[tmp_size_4[0] * i + O_Htm_tmp];
            }
          }

          for (i = 0; i < idxStart_4Row; i++) {
            for (O_Htm_tmp = 0; O_Htm_tmp < idxStart_6Row; O_Htm_tmp++) {
              planar_robot3dof_FD2_B.CC[O_Htm_tmp + 3 * i] = jointOrigins
                [(y_tmp_0 + 1) * i + O_Htm_tmp];
            }
          }
        } else {
          planar_robot_binary_expand_op_l(planar_robot3dof_FD2_B.CC, y_tmp_0, J,
            m, jointOrigins, S, tmp2, dJ_pre, Htm_size, dJ);
        }

        tmp_size[0] = y_tmp_0 + 1;
        tmp_size[1] = 3;
        for (i = 0; i < 3; i++) {
          for (O_Htm_tmp = 0; O_Htm_tmp <= y_tmp_0; O_Htm_tmp++) {
            y[O_Htm_tmp + (y_tmp_0 + 1) * i] = dJ_pre[Htm_size[0] * i +
              O_Htm_tmp];
          }

          O_Htm_tmp_0 = i << 2;
          jointOrigins[3 * i] = O_Htm[O_Htm_tmp_0];
          jointOrigins[3 * i + 1] = O_Htm[O_Htm_tmp_0 + 1];
          jointOrigins[3 * i + 2] = O_Htm[O_Htm_tmp_0 + 2];
        }

        planar_robot3dof_F_mtimes_evjzc(y, tmp_size, jointOrigins, tmp2,
          tmp_size_5);
        planar_robot3dof__mtimes_evjzci(tmp2, tmp_size_5, tmp_data_1, &i);
        if (y_tmp_0 + 1 == i) {
          tmp_size[0] = y_tmp_0 + 1;
          tmp_size[1] = 3;
          for (i = 0; i < 3; i++) {
            for (O_Htm_tmp = 0; O_Htm_tmp <= y_tmp_0; O_Htm_tmp++) {
              y[O_Htm_tmp + (y_tmp_0 + 1) * i] = dJ_pre[Htm_size[0] * i +
                O_Htm_tmp];
            }

            O_Htm_tmp_0 = i << 2;
            jointOrigins[3 * i] = O_Htm[O_Htm_tmp_0];
            jointOrigins[3 * i + 1] = O_Htm[O_Htm_tmp_0 + 1];
            jointOrigins[3 * i + 2] = O_Htm[O_Htm_tmp_0 + 2];
          }

          planar_robot3dof_F_mtimes_evjzc(y, tmp_size, jointOrigins, tmp2,
            Htm_size);
          planar_robot3dof__mtimes_evjzci(tmp2, Htm_size, tmp_data_1, &i);
          O_Htm_tmp = y_tmp_0 + 1;
          for (i = 0; i < O_Htm_tmp; i++) {
            tmp_data_0[i] = planar_robot3dof_FD2_B.g[i] + tmp_data_1[i];
          }

          std::memcpy(&planar_robot3dof_FD2_B.g[0], &tmp_data_0[0],
                      static_cast<uint32_T>(y_tmp_0 + 1) * sizeof(real_T));
        } else {
          planar_robot3d_binary_expand_op(planar_robot3dof_FD2_B.g, y_tmp_0,
            dJ_pre, Htm_size, O_Htm);
        }

        std::memcpy(&J_pre[0], &J[0], 18U * sizeof(real_T));
        std::memcpy(&dJ_pre[0], &dJ[0], 18U * sizeof(real_T));
        for (i = 0; i < 6; i++) {
          inertialTwist_pre[i] = inertialTwist[i];
        }

        std::memcpy(&O_Htm_pre[0], &O_Htm[0], sizeof(real_T) << 4U);
      }

      for (i = 0; i < 3; i++) {
        y_tmp_0 = i << 2;
        O_Htm_pre[y_tmp_0] = E_tmp[3 * i];
        O_Htm_pre[y_tmp_0 + 1] = E_tmp[3 * i + 1];
        O_Htm_pre[y_tmp_0 + 2] = E_tmp[3 * i + 2];
      }

      O_Htm_pre[12] = planar_robot3dof_FD2_U.arm_length[2];
      O_Htm_pre[13] = 0.0;
      O_Htm_pre[14] = 0.0;
      O_Htm_pre[3] = 0.0;
      O_Htm_pre[7] = 0.0;
      O_Htm_pre[11] = 0.0;
      O_Htm_pre[15] = 1.0;
      for (i = 0; i < 4; i++) {
        y_tmp_0 = i << 2;
        m_tmp = O_Htm_pre[y_tmp_0 + 1];
        m = O_Htm_pre[y_tmp_0];
        b_m = O_Htm_pre[y_tmp_0 + 2];
        c_m = O_Htm_pre[y_tmp_0 + 3];
        for (O_Htm_tmp = 0; O_Htm_tmp < 4; O_Htm_tmp++) {
          O_Htm_0[O_Htm_tmp + y_tmp_0] = ((O_Htm[O_Htm_tmp + 4] * m_tmp + m *
            O_Htm[O_Htm_tmp]) + O_Htm[O_Htm_tmp + 8] * b_m) + O_Htm[O_Htm_tmp +
            12] * c_m;
        }
      }

      /* Outport: '<Root>/TCP_pos' incorporates:
       *  MATLAB Function: '<S1>/calcSysMatrices'
       */
      planar_robot3dof_FD2_Y.TCP_pos[0] = O_Htm_0[12];
      planar_robot3dof_FD2_Y.TCP_pos[1] = O_Htm_0[13];
      planar_robot3dof_FD2_Y.TCP_pos[2] = O_Htm_0[14];
    }

    /* Derivative: '<S1>/Derivative1' incorporates:
     *  Derivative: '<S1>/Derivative'
     */
    m = (&planar_robot3dof_FD2_M)->Timing.t[0];
    if ((planar_robot3dof_FD2_DW.TimeStampA >= m) &&
        (planar_robot3dof_FD2_DW.TimeStampB >= m)) {
      /* Derivative: '<S1>/Derivative1' */
      planar_robot3dof_FD2_B.Derivative1[0] = 0.0;
      planar_robot3dof_FD2_B.Derivative1[1] = 0.0;
      planar_robot3dof_FD2_B.Derivative1[2] = 0.0;
    } else {
      Iz = planar_robot3dof_FD2_DW.TimeStampA;
      lastU = &planar_robot3dof_FD2_DW.LastUAtTimeA;
      if (planar_robot3dof_FD2_DW.TimeStampA <
          planar_robot3dof_FD2_DW.TimeStampB) {
        if (planar_robot3dof_FD2_DW.TimeStampB < m) {
          Iz = planar_robot3dof_FD2_DW.TimeStampB;
          lastU = &planar_robot3dof_FD2_DW.LastUAtTimeB;
        }
      } else if (planar_robot3dof_FD2_DW.TimeStampA >= m) {
        Iz = planar_robot3dof_FD2_DW.TimeStampB;
        lastU = &planar_robot3dof_FD2_DW.LastUAtTimeB;
      }

      Iz = m - Iz;

      /* Derivative: '<S1>/Derivative1' incorporates:
       *  Outport: '<Root>/TCP_pos'
       */
      planar_robot3dof_FD2_B.Derivative1[0] = (planar_robot3dof_FD2_Y.TCP_pos[0]
        - (*lastU)[0]) / Iz;
      planar_robot3dof_FD2_B.Derivative1[1] = (planar_robot3dof_FD2_Y.TCP_pos[1]
        - (*lastU)[1]) / Iz;
      planar_robot3dof_FD2_B.Derivative1[2] = (planar_robot3dof_FD2_Y.TCP_pos[2]
        - (*lastU)[2]) / Iz;
    }

    /* Derivative: '<S1>/Derivative' */
    if ((planar_robot3dof_FD2_DW.TimeStampA_b >= m) &&
        (planar_robot3dof_FD2_DW.TimeStampB_n >= m)) {
      /* Outport: '<Root>/TCP_acc' */
      planar_robot3dof_FD2_Y.TCP_acc[0] = 0.0;
      planar_robot3dof_FD2_Y.TCP_acc[1] = 0.0;
      planar_robot3dof_FD2_Y.TCP_acc[2] = 0.0;
    } else {
      Iz = planar_robot3dof_FD2_DW.TimeStampA_b;
      lastU = &planar_robot3dof_FD2_DW.LastUAtTimeA_l;
      if (planar_robot3dof_FD2_DW.TimeStampA_b <
          planar_robot3dof_FD2_DW.TimeStampB_n) {
        if (planar_robot3dof_FD2_DW.TimeStampB_n < m) {
          Iz = planar_robot3dof_FD2_DW.TimeStampB_n;
          lastU = &planar_robot3dof_FD2_DW.LastUAtTimeB_m;
        }
      } else if (planar_robot3dof_FD2_DW.TimeStampA_b >= m) {
        Iz = planar_robot3dof_FD2_DW.TimeStampB_n;
        lastU = &planar_robot3dof_FD2_DW.LastUAtTimeB_m;
      }

      Iz = m - Iz;

      /* Outport: '<Root>/TCP_acc' */
      planar_robot3dof_FD2_Y.TCP_acc[0] = (planar_robot3dof_FD2_B.Derivative1[0]
        - (*lastU)[0]) / Iz;
      planar_robot3dof_FD2_Y.TCP_acc[1] = (planar_robot3dof_FD2_B.Derivative1[1]
        - (*lastU)[1]) / Iz;
      planar_robot3dof_FD2_Y.TCP_acc[2] = (planar_robot3dof_FD2_B.Derivative1[2]
        - (*lastU)[2]) / Iz;
    }

    if (rtmIsMajorTimeStep((&planar_robot3dof_FD2_M))) {
      /* Product: '<S1>/Product5' */
      rt_invd3x3_snf(planar_robot3dof_FD2_B.M, planar_robot3dof_FD2_B.Product5);
      for (i = 0; i < 3; i++) {
        /* Product: '<S1>/Product3' */
        planar_robot3dof_FD2_B.Product3[i] = (planar_robot3dof_FD2_B.CC[i + 3] *
          rtb_ZeroOrderHold1_idx_1 + planar_robot3dof_FD2_B.CC[i] *
          rtb_ZeroOrderHold1_idx_0) + planar_robot3dof_FD2_B.CC[i + 6] *
          rtb_ZeroOrderHold1_idx_2;
      }
    }

    /* Sum: '<S1>/Sum4' incorporates:
     *  Inport: '<Root>/joint_torque'
     */
    rtb_ZeroOrderHold1_idx_0 = (planar_robot3dof_FD2_U.joint_torque[0] -
      planar_robot3dof_FD2_B.Product3[0]) - planar_robot3dof_FD2_B.g[0];
    rtb_ZeroOrderHold1_idx_1 = (planar_robot3dof_FD2_U.joint_torque[1] -
      planar_robot3dof_FD2_B.Product3[1]) - planar_robot3dof_FD2_B.g[1];
    rtb_ZeroOrderHold1_idx_2 = (planar_robot3dof_FD2_U.joint_torque[2] -
      planar_robot3dof_FD2_B.Product3[2]) - planar_robot3dof_FD2_B.g[2];
    for (i = 0; i < 3; i++) {
      /* Product: '<S1>/Product1' incorporates:
       *  Product: '<S1>/Product5'
       */
      m_tmp = (planar_robot3dof_FD2_B.Product5[i + 3] * rtb_ZeroOrderHold1_idx_1
               + planar_robot3dof_FD2_B.Product5[i] * rtb_ZeroOrderHold1_idx_0)
        + planar_robot3dof_FD2_B.Product5[i + 6] * rtb_ZeroOrderHold1_idx_2;
      planar_robot3dof_FD2_B.Product1[i] = m_tmp;

      /* Outport: '<Root>/joint_pos' */
      planar_robot3dof_FD2_Y.joint_pos[i] = planar_robot3dof_FD2_B.q[i];

      /* Outport: '<Root>/joint_vel' */
      planar_robot3dof_FD2_Y.joint_vel[i] = planar_robot3dof_FD2_B.dq[i];

      /* Outport: '<Root>/joint_acc' incorporates:
       *  Product: '<S1>/Product1'
       */
      planar_robot3dof_FD2_Y.joint_acc[i] = m_tmp;

      /* Outport: '<Root>/TCP_vel' */
      planar_robot3dof_FD2_Y.TCP_vel[i] = planar_robot3dof_FD2_B.Derivative1[i];
    }

    /* End of Outputs for SubSystem: '<Root>/planar_robot3dof_FD' */
  }

  if (rtmIsMajorTimeStep((&planar_robot3dof_FD2_M))) {
    real_T (*lastU)[3];

    /* Update for Atomic SubSystem: '<Root>/planar_robot3dof_FD' */
    /* Update for Derivative: '<S1>/Derivative1' incorporates:
     *  Outport: '<Root>/TCP_pos'
     */
    if (planar_robot3dof_FD2_DW.TimeStampA == (rtInf)) {
      planar_robot3dof_FD2_DW.TimeStampA = (&planar_robot3dof_FD2_M)->Timing.t[0];
      lastU = &planar_robot3dof_FD2_DW.LastUAtTimeA;
    } else if (planar_robot3dof_FD2_DW.TimeStampB == (rtInf)) {
      planar_robot3dof_FD2_DW.TimeStampB = (&planar_robot3dof_FD2_M)->Timing.t[0];
      lastU = &planar_robot3dof_FD2_DW.LastUAtTimeB;
    } else if (planar_robot3dof_FD2_DW.TimeStampA <
               planar_robot3dof_FD2_DW.TimeStampB) {
      planar_robot3dof_FD2_DW.TimeStampA = (&planar_robot3dof_FD2_M)->Timing.t[0];
      lastU = &planar_robot3dof_FD2_DW.LastUAtTimeA;
    } else {
      planar_robot3dof_FD2_DW.TimeStampB = (&planar_robot3dof_FD2_M)->Timing.t[0];
      lastU = &planar_robot3dof_FD2_DW.LastUAtTimeB;
    }

    (*lastU)[0] = planar_robot3dof_FD2_Y.TCP_pos[0];
    (*lastU)[1] = planar_robot3dof_FD2_Y.TCP_pos[1];
    (*lastU)[2] = planar_robot3dof_FD2_Y.TCP_pos[2];

    /* End of Update for Derivative: '<S1>/Derivative1' */

    /* Update for Derivative: '<S1>/Derivative' */
    if (planar_robot3dof_FD2_DW.TimeStampA_b == (rtInf)) {
      planar_robot3dof_FD2_DW.TimeStampA_b = (&planar_robot3dof_FD2_M)->
        Timing.t[0];
      lastU = &planar_robot3dof_FD2_DW.LastUAtTimeA_l;
    } else if (planar_robot3dof_FD2_DW.TimeStampB_n == (rtInf)) {
      planar_robot3dof_FD2_DW.TimeStampB_n = (&planar_robot3dof_FD2_M)->
        Timing.t[0];
      lastU = &planar_robot3dof_FD2_DW.LastUAtTimeB_m;
    } else if (planar_robot3dof_FD2_DW.TimeStampA_b <
               planar_robot3dof_FD2_DW.TimeStampB_n) {
      planar_robot3dof_FD2_DW.TimeStampA_b = (&planar_robot3dof_FD2_M)->
        Timing.t[0];
      lastU = &planar_robot3dof_FD2_DW.LastUAtTimeA_l;
    } else {
      planar_robot3dof_FD2_DW.TimeStampB_n = (&planar_robot3dof_FD2_M)->
        Timing.t[0];
      lastU = &planar_robot3dof_FD2_DW.LastUAtTimeB_m;
    }

    (*lastU)[0] = planar_robot3dof_FD2_B.Derivative1[0];
    (*lastU)[1] = planar_robot3dof_FD2_B.Derivative1[1];
    (*lastU)[2] = planar_robot3dof_FD2_B.Derivative1[2];

    /* End of Update for Derivative: '<S1>/Derivative' */
    /* End of Update for SubSystem: '<Root>/planar_robot3dof_FD' */
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep((&planar_robot3dof_FD2_M))) {
    rt_ertODEUpdateContinuousStates(&(&planar_robot3dof_FD2_M)->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++(&planar_robot3dof_FD2_M)->Timing.clockTick0;
    (&planar_robot3dof_FD2_M)->Timing.t[0] = rtsiGetSolverStopTime
      (&(&planar_robot3dof_FD2_M)->solverInfo);

    {
      /* Update absolute timer for sample time: [0.001s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.001, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      (&planar_robot3dof_FD2_M)->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void planar_robot3dof_FD2::planar_robot3dof_FD2_derivatives()
{
  XDot_planar_robot3dof_FD2_T *_rtXdot;
  _rtXdot = ((XDot_planar_robot3dof_FD2_T *) (&planar_robot3dof_FD2_M)->derivs);

  /* Derivatives for Atomic SubSystem: '<Root>/planar_robot3dof_FD' */
  /* Derivatives for Integrator: '<S1>/Integrator1' */
  _rtXdot->Integrator1_CSTATE[0] = planar_robot3dof_FD2_B.dq[0];

  /* Derivatives for Integrator: '<S1>/Integrator' */
  _rtXdot->Integrator_CSTATE[0] = planar_robot3dof_FD2_B.Product1[0];

  /* Derivatives for Integrator: '<S1>/Integrator1' */
  _rtXdot->Integrator1_CSTATE[1] = planar_robot3dof_FD2_B.dq[1];

  /* Derivatives for Integrator: '<S1>/Integrator' */
  _rtXdot->Integrator_CSTATE[1] = planar_robot3dof_FD2_B.Product1[1];

  /* Derivatives for Integrator: '<S1>/Integrator1' */
  _rtXdot->Integrator1_CSTATE[2] = planar_robot3dof_FD2_B.dq[2];

  /* Derivatives for Integrator: '<S1>/Integrator' */
  _rtXdot->Integrator_CSTATE[2] = planar_robot3dof_FD2_B.Product1[2];

  /* End of Derivatives for SubSystem: '<Root>/planar_robot3dof_FD' */
}

/* Model initialize function */
void planar_robot3dof_FD2::initialize()
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&(&planar_robot3dof_FD2_M)->solverInfo,
                          &(&planar_robot3dof_FD2_M)->Timing.simTimeStep);
    rtsiSetTPtr(&(&planar_robot3dof_FD2_M)->solverInfo, &rtmGetTPtr
                ((&planar_robot3dof_FD2_M)));
    rtsiSetStepSizePtr(&(&planar_robot3dof_FD2_M)->solverInfo,
                       &(&planar_robot3dof_FD2_M)->Timing.stepSize0);
    rtsiSetdXPtr(&(&planar_robot3dof_FD2_M)->solverInfo,
                 &(&planar_robot3dof_FD2_M)->derivs);
    rtsiSetContStatesPtr(&(&planar_robot3dof_FD2_M)->solverInfo, (real_T **)
                         &(&planar_robot3dof_FD2_M)->contStates);
    rtsiSetNumContStatesPtr(&(&planar_robot3dof_FD2_M)->solverInfo,
      &(&planar_robot3dof_FD2_M)->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&(&planar_robot3dof_FD2_M)->solverInfo,
      &(&planar_robot3dof_FD2_M)->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&(&planar_robot3dof_FD2_M)->solverInfo,
      &(&planar_robot3dof_FD2_M)->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&(&planar_robot3dof_FD2_M)->solverInfo, &(
      &planar_robot3dof_FD2_M)->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&(&planar_robot3dof_FD2_M)->solverInfo,
                          (&rtmGetErrorStatus((&planar_robot3dof_FD2_M))));
    rtsiSetRTModelPtr(&(&planar_robot3dof_FD2_M)->solverInfo,
                      (&planar_robot3dof_FD2_M));
  }

  rtsiSetSimTimeStep(&(&planar_robot3dof_FD2_M)->solverInfo, MAJOR_TIME_STEP);
  (&planar_robot3dof_FD2_M)->intgData.y = (&planar_robot3dof_FD2_M)->odeY;
  (&planar_robot3dof_FD2_M)->intgData.f[0] = (&planar_robot3dof_FD2_M)->odeF[0];
  (&planar_robot3dof_FD2_M)->intgData.f[1] = (&planar_robot3dof_FD2_M)->odeF[1];
  (&planar_robot3dof_FD2_M)->intgData.f[2] = (&planar_robot3dof_FD2_M)->odeF[2];
  (&planar_robot3dof_FD2_M)->contStates = ((X_planar_robot3dof_FD2_T *)
    &planar_robot3dof_FD2_X);
  rtsiSetSolverData(&(&planar_robot3dof_FD2_M)->solverInfo, static_cast<void *>(
    &(&planar_robot3dof_FD2_M)->intgData));
  rtsiSetIsMinorTimeStepWithModeChange(&(&planar_robot3dof_FD2_M)->solverInfo,
    false);
  rtsiSetSolverName(&(&planar_robot3dof_FD2_M)->solverInfo,"ode3");
  rtmSetTPtr((&planar_robot3dof_FD2_M), &(&planar_robot3dof_FD2_M)
             ->Timing.tArray[0]);
  (&planar_robot3dof_FD2_M)->Timing.stepSize0 = 0.001;

  /* SystemInitialize for Atomic SubSystem: '<Root>/planar_robot3dof_FD' */
  /* InitializeConditions for Integrator: '<S1>/Integrator1' */
  planar_robot3dof_FD2_X.Integrator1_CSTATE[0] = 0.0;

  /* InitializeConditions for Integrator: '<S1>/Integrator' */
  planar_robot3dof_FD2_X.Integrator_CSTATE[0] = 0.0;

  /* InitializeConditions for Integrator: '<S1>/Integrator1' */
  planar_robot3dof_FD2_X.Integrator1_CSTATE[1] = 0.0;

  /* InitializeConditions for Integrator: '<S1>/Integrator' */
  planar_robot3dof_FD2_X.Integrator_CSTATE[1] = 0.0;

  /* InitializeConditions for Integrator: '<S1>/Integrator1' */
  planar_robot3dof_FD2_X.Integrator1_CSTATE[2] = 0.0;

  /* InitializeConditions for Integrator: '<S1>/Integrator' */
  planar_robot3dof_FD2_X.Integrator_CSTATE[2] = 0.0;

  /* InitializeConditions for Derivative: '<S1>/Derivative1' */
  planar_robot3dof_FD2_DW.TimeStampA = (rtInf);
  planar_robot3dof_FD2_DW.TimeStampB = (rtInf);

  /* InitializeConditions for Derivative: '<S1>/Derivative' */
  planar_robot3dof_FD2_DW.TimeStampA_b = (rtInf);
  planar_robot3dof_FD2_DW.TimeStampB_n = (rtInf);

  /* End of SystemInitialize for SubSystem: '<Root>/planar_robot3dof_FD' */
}

/* Model terminate function */
void planar_robot3dof_FD2::terminate()
{
  /* (no terminate code required) */
}

/* Constructor */
planar_robot3dof_FD2::planar_robot3dof_FD2() :
  planar_robot3dof_FD2_U(),
  planar_robot3dof_FD2_Y(),
  planar_robot3dof_FD2_B(),
  planar_robot3dof_FD2_DW(),
  planar_robot3dof_FD2_X(),
  planar_robot3dof_FD2_M()
{
  /* Currently there is no constructor body generated.*/
}

/* Destructor */
/* Currently there is no destructor body generated.*/
planar_robot3dof_FD2::~planar_robot3dof_FD2() = default;

/* Real-Time Model get method */
RT_MODEL_planar_robot3dof_FD2_T * planar_robot3dof_FD2::getRTM()
{
  return (&planar_robot3dof_FD2_M);
}
