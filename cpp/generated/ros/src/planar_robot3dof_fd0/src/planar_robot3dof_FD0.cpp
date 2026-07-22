/*
 * planar_robot3dof_FD0.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "planar_robot3dof_FD0".
 *
 * Model version              : 12.40
 * Simulink Coder version : 9.9 (R2023a) 19-Nov-2022
 * C++ source code generated on : Thu Nov 23 01:12:48 2023
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objective: Debugging
 * Validation result: Not run
 */

#include "planar_robot3dof_FD0.h"
#include "rtwtypes.h"
#include <cstring>
#include <cmath>
#include "planar_robot3dof_FD0_private.h"

extern "C"
{

#include "rt_nonfinite.h"

}

/* Function for MATLAB Function: '<S1>/calcSysMatrices' */
void planar_robot3dof_FD0::planar_robot3dof_FD0_eye(real_T b_I[9])
{
  std::memset(&b_I[0], 0, 9U * sizeof(real_T));
  b_I[0] = 1.0;
  b_I[4] = 1.0;
  b_I[8] = 1.0;
}

/* Function for MATLAB Function: '<S1>/calcSysMatrices' */
void planar_robot3dof_FD0::planar_robot3dof_FD0_diag(const real_T v[3], real_T
  d[9])
{
  std::memset(&d[0], 0, 9U * sizeof(real_T));
  d[0] = v[0];
  d[4] = v[1];
  d[8] = v[2];
}

/* Function for MATLAB Function: '<S1>/calcSysMatrices' */
void planar_robot3dof_FD0::planar_robot3dof_FD0_repmat(real_T b[18])
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
boolean_T planar_robot3dof_FD0::planar_robot3dof_FD0_all(const boolean_T x[3])
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
void planar_robot3dof_FD0::planar_robot3dof_FD0_mtimes(const real_T A_data[],
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
      real_T s;
      s = A_data[i] * B[boffset];
      s += A_data[A_size[0] + i] * B[boffset + 1];
      s += A_data[(A_size[0] << 1) + i] * B[boffset + 2];
      s += A_data[3 * A_size[0] + i] * B[boffset + 3];
      C_data[coffset + i] = s;
    }
  }
}

/* Function for MATLAB Function: '<S1>/calcSysMatrices' */
void planar_robot3dof_FD0::planar_robot3dof_FD0_mtimes_j(const real_T A[36],
  const real_T B_data[], const int32_T B_size[2], real_T C_data[], int32_T
  C_size[2])
{
  int32_T b;
  C_size[0] = 6;
  C_size[1] = B_size[1];
  b = B_size[1];
  for (int32_T j{0}; j < b; j++) {
    int32_T coffset;
    coffset = j * 6;
    for (int32_T i{0}; i < 6; i++) {
      real_T s;
      s = 0.0;
      for (int32_T k{0}; k < 6; k++) {
        s += A[k * 6 + i] * B_data[coffset + k];
      }

      C_data[coffset + i] = s;
    }
  }
}

void planar_robot3dof_FD0::planar_rob_binary_expand_op_hym(real_T in1[18],
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

  planar_robot3dof_FD0_mtimes_j(in3, in4_data, in4_size, tmp_data, tmp_size);
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

  planar_robot3dof_FD0_mtimes_j(in5_0, in4_data, in4_size, tmp_data_0,
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
void planar_robot3dof_FD0::planar_robot3dof_FD0_mtimes_jf(const real_T A_data[],
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
void planar_robot3dof_FD0::planar_robot3dof_FD0_mtimes_jfu(const real_T A_data[],
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

void planar_robot3dof_FD0::planar_robo_binary_expand_op_hy(real_T in1[9],
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

  planar_robot3dof_FD0_mtimes_jfu(in3_data, in3_size, in4_data, in4_size,
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
void planar_robot3dof_FD0::planar_robot3dof_FD_mtimes_jfux(const real_T A_data[],
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

void planar_robot3dof_FD0::planar_robot_binary_expand_op_h(real_T in1[9],
  int32_T in2, const real_T in3[18], real_T in4, const real_T in5[9], const
  real_T in6[9], const real_T in7[9], const real_T in8_data[], const int32_T
  in8_size[2], const real_T in9[18])
{
  real_T in4_0[36];
  real_T in3_data[18];
  real_T tmp_data[18];
  real_T in1_data[9];
  real_T tmp_data_0[9];
  real_T tmp_data_1[9];
  int32_T in3_size[2];
  int32_T tmp_size[2];
  int32_T tmp_size_0[2];
  int32_T aux_0_1;
  int32_T aux_1_1;
  int32_T aux_2_1;
  int32_T i;
  int32_T in4_tmp;
  int32_T in4_tmp_0;
  int32_T loop_ub;
  int32_T loop_ub_0;
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

  planar_robot3dof_FD_mtimes_jfux(in3_data, in3_size, in4_0, tmp_data, tmp_size);
  in3_size[0] = 6;
  in3_size[1] = in2 + 1;
  for (i = 0; i <= in2; i++) {
    for (in4_tmp = 0; in4_tmp < 6; in4_tmp++) {
      in3_data[in4_tmp + 6 * i] = in3[6 * i + in4_tmp];
    }
  }

  planar_robot3dof_FD0_mtimes_jfu(tmp_data, tmp_size, in3_data, in3_size,
    tmp_data_0, tmp_size_0);
  in3_size[0] = 6;
  in3_size[1] = in2 + 1;
  for (i = 0; i <= in2; i++) {
    for (in4_tmp = 0; in4_tmp < 6; in4_tmp++) {
      in3_data[in4_tmp + 6 * i] = in9[6 * i + in4_tmp];
    }
  }

  planar_robot3dof_FD0_mtimes_jfu(in8_data, in8_size, in3_data, in3_size,
    tmp_data_1, tmp_size);
  loop_ub_0 = tmp_size[0] == 1 ? tmp_size_0[0] == 1 ? in2 + 1 : tmp_size_0[0] :
    tmp_size[0];
  loop_ub = tmp_size[1] == 1 ? tmp_size_0[1] == 1 ? in2 + 1 : tmp_size_0[1] :
    tmp_size[1];
  in4_tmp_0 = (in2 + 1 != 1);
  stride_1_0 = (tmp_size_0[0] != 1);
  stride_1_1 = (tmp_size_0[1] != 1);
  stride_2_0 = (tmp_size[0] != 1);
  stride_2_1 = (tmp_size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  aux_2_1 = 0;
  for (i = 0; i < loop_ub; i++) {
    for (in4_tmp = 0; in4_tmp < loop_ub_0; in4_tmp++) {
      in1_data[in4_tmp + loop_ub_0 * i] = (in1[in4_tmp * in4_tmp_0 + 3 * aux_0_1]
        + tmp_data_0[in4_tmp * stride_1_0 + tmp_size_0[0] * aux_1_1]) +
        tmp_data_1[in4_tmp * stride_2_0 + tmp_size[0] * aux_2_1];
    }

    aux_2_1 += stride_2_1;
    aux_1_1 += stride_1_1;
    aux_0_1 += in4_tmp_0;
  }

  for (i = 0; i < loop_ub; i++) {
    for (in4_tmp = 0; in4_tmp < loop_ub_0; in4_tmp++) {
      in1[in4_tmp + 3 * i] = in1_data[loop_ub_0 * i + in4_tmp];
    }
  }

  /* End of MATLAB Function: '<S1>/calcSysMatrices' */
  /* End of Outputs for SubSystem: '<Root>/planar_robot3dof_FD' */
}

/* Function for MATLAB Function: '<S1>/calcSysMatrices' */
void planar_robot3dof_FD0::planar_robot3dof_F_mtimes_jfuxr(const real_T A_data[],
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
      real_T s;
      s = A_data[i] * B[j];
      s += A_data[A_size[0] + i] * B[j + 3];
      s += A_data[(A_size[0] << 1) + i] * B[j + 6];
      C_data[coffset + i] = s;
    }
  }
}

/* Function for MATLAB Function: '<S1>/calcSysMatrices' */
void planar_robot3dof_FD0::planar_robot3dof__mtimes_jfuxri(const real_T A_data[],
  const int32_T A_size[2], real_T C_data[], int32_T *C_size)
{
  int32_T b;
  *C_size = A_size[0];
  b = A_size[0];
  for (int32_T i{0}; i < b; i++) {
    real_T s;
    s = A_data[i] * 0.0;
    s += A_data[A_size[0] + i] * 0.0;
    s += A_data[(A_size[0] << 1) + i] * 0.0;
    C_data[i] = s;
  }
}

void planar_robot3dof_FD0::planar_robot3d_binary_expand_op(real_T in1[3],
  int32_T in2, const real_T in3_data[], const int32_T in3_size[2], const real_T
  in4[16])
{
  real_T in3_data_0[9];
  real_T in4_0[9];
  real_T tmp_data[9];
  real_T in1_data[3];
  real_T tmp_data_0[3];
  int32_T in3_size_0[2];
  int32_T tmp_size[2];
  int32_T in4_tmp;
  int32_T stride_0_1;
  int32_T stride_1_1;
  int32_T tmp_size_0;

  /* Outputs for Atomic SubSystem: '<Root>/planar_robot3dof_FD' */
  /* MATLAB Function: '<S1>/calcSysMatrices' */
  in3_size_0[0] = in2 + 1;
  in3_size_0[1] = 3;
  for (tmp_size_0 = 0; tmp_size_0 < 3; tmp_size_0++) {
    for (in4_tmp = 0; in4_tmp <= in2; in4_tmp++) {
      in3_data_0[in4_tmp + in3_size_0[0] * tmp_size_0] = in3_data[in3_size[0] *
        tmp_size_0 + in4_tmp];
    }

    in4_tmp = tmp_size_0 << 2;
    in4_0[3 * tmp_size_0] = in4[in4_tmp];
    in4_0[3 * tmp_size_0 + 1] = in4[in4_tmp + 1];
    in4_0[3 * tmp_size_0 + 2] = in4[in4_tmp + 2];
  }

  planar_robot3dof_F_mtimes_jfuxr(in3_data_0, in3_size_0, in4_0, tmp_data,
    tmp_size);
  planar_robot3dof__mtimes_jfuxri(tmp_data, tmp_size, tmp_data_0, &tmp_size_0);
  in4_tmp = in2 + 1;
  stride_0_1 = (in2 + 1 != 1);
  stride_1_1 = (tmp_size_0 != 1);
  for (tmp_size_0 = 0; tmp_size_0 < in4_tmp; tmp_size_0++) {
    in1_data[tmp_size_0] = in1[tmp_size_0 * stride_0_1] + tmp_data_0[tmp_size_0 *
      stride_1_1];
  }

  if (in4_tmp - 1 >= 0) {
    std::memcpy(&in1[0], &in1_data[0], static_cast<uint32_T>(in4_tmp) * sizeof
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
  real_T y_0;
  int32_T p1;
  int32_T six;
  int32_T three;
  int32_T zero;
  std::memcpy(&x[0], &u[0], 9U * sizeof(real_T));
  three = 3;
  six = 6;
  p1 = 0;
  absx31 = x[0];
  absx11 = std::abs(absx31);
  absx31 = x[1];
  absx21 = std::abs(absx31);
  absx31 = x[2];
  absx31 = std::abs(absx31);
  if ((absx21 > absx11) && (absx21 > absx31)) {
    p1 = 3;
    three = 0;
    absx21 = x[0];
    x[0] = x[1];
    x[1] = absx21;
    absx21 = x[3];
    x[3] = x[4];
    x[4] = absx21;
    absx21 = x[6];
    x[6] = x[7];
    x[7] = absx21;
  } else if (absx31 > absx11) {
    p1 = 6;
    six = 0;
    absx21 = x[0];
    x[0] = x[2];
    x[2] = absx21;
    absx21 = x[3];
    x[3] = x[5];
    x[5] = absx21;
    absx21 = x[6];
    x[6] = x[8];
    x[8] = absx21;
  }

  absx31 = x[1];
  y_0 = x[0];
  absx31 /= y_0;
  x[1] = absx31;
  absx31 = x[2];
  y_0 = x[0];
  absx31 /= y_0;
  x[2] = absx31;
  x[4] -= x[1] * x[3];
  x[5] -= x[2] * x[3];
  x[7] -= x[1] * x[6];
  x[8] -= x[2] * x[6];
  absx31 = x[5];
  y_0 = std::abs(absx31);
  absx31 = x[4];
  absx31 = std::abs(absx31);
  if (y_0 > absx31) {
    zero = three;
    three = six;
    six = zero;
    absx21 = x[1];
    x[1] = x[2];
    x[2] = absx21;
    absx21 = x[4];
    x[4] = x[5];
    x[5] = absx21;
    absx21 = x[7];
    x[7] = x[8];
    x[8] = absx21;
  }

  absx31 = x[5];
  y_0 = x[4];
  absx31 /= y_0;
  x[5] = absx31;
  x[8] -= x[5] * x[7];
  absx31 = x[1] * x[5] - x[2];
  y_0 = x[8];
  absx11 = absx31 / y_0;
  absx31 = -(x[7] * absx11 + x[1]);
  y_0 = x[4];
  absx21 = absx31 / y_0;
  zero = p1;
  absx31 = (1.0 - x[3] * absx21) - x[6] * absx11;
  y_0 = x[0];
  absx31 /= y_0;
  y[zero] = absx31;
  zero = p1 + 1;
  y[zero] = absx21;
  zero = p1 + 2;
  y[zero] = absx11;
  absx31 = -x[5];
  y_0 = x[8];
  absx11 = absx31 / y_0;
  absx31 = 1.0 - x[7] * absx11;
  y_0 = x[4];
  absx21 = absx31 / y_0;
  zero = three;
  absx31 = -(x[3] * absx21 + x[6] * absx11);
  y_0 = x[0];
  absx31 /= y_0;
  y[zero] = absx31;
  zero = three + 1;
  y[zero] = absx21;
  zero = three + 2;
  y[zero] = absx11;
  y_0 = x[8];
  absx11 = 1.0 / y_0;
  absx31 = -x[7] * absx11;
  y_0 = x[4];
  absx21 = absx31 / y_0;
  zero = six;
  absx31 = -(x[3] * absx21 + x[6] * absx11);
  y_0 = x[0];
  absx31 /= y_0;
  y[zero] = absx31;
  zero = six + 1;
  y[zero] = absx21;
  zero = six + 2;
  y[zero] = absx11;
}

/* Model step function */
void planar_robot3dof_FD0::step()
{
  static const int8_T c_b[9]{ 1, 0, 0, 0, 1, 0, 0, 0, 1 };

  real_T ROBOT_Mass[108];
  real_T ROBOT_Mass_data[108];
  real_T Htm_data[48];
  real_T ROBOT_g0[48];
  real_T ROBOT_g0_data[48];
  real_T invAd[36];
  real_T jointOrigins_0[36];
  real_T J[18];
  real_T J_data[18];
  real_T J_pre[18];
  real_T ROBOT_csi[18];
  real_T dJ[18];
  real_T dJ_pre[18];
  real_T tmp_data_2[18];
  real_T O_Htm[16];
  real_T O_Htm_0[16];
  real_T O_Htm_pre[16];
  real_T J_pre_data[12];
  real_T tmp_data[12];
  real_T tmp_data_1[12];
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
  real_T tmp_0[9];
  real_T y[9];
  real_T inertialTwist[6];
  real_T inertialTwist_pre[6];
  real_T relTwist[6];
  real_T tmp_data_0[3];
  real_T tmp_data_3[3];
  real_T Iz;
  real_T b_m;
  real_T b_m_0;
  real_T body_CenterOfMass_idx_0;
  real_T c_m;
  real_T m;
  real_T m_tmp;
  real_T m_tmp_0;
  real_T tmp2_0;
  int32_T Htm_size[2];
  int32_T J_pre_size[2];
  int32_T J_size[2];
  int32_T J_size_0[2];
  int32_T ROBOT_Mass_size[2];
  int32_T ROBOT_g0_size[2];
  int32_T tmp_size[2];
  int32_T tmp_size_0[2];
  int32_T tmp_size_1[2];
  int32_T tmp_size_2[2];
  int32_T tmp_size_3[2];
  int32_T tmp_size_4[2];
  int32_T tmp_size_5[2];
  int32_T O_Htm_tmp;
  int32_T O_Htm_tmp_0;
  int32_T ROBOT_Mass_tmp;
  int32_T i;
  int32_T idxStart_4Row;
  int32_T idxStart_6Row;
  boolean_T ROBOT_csi_0[3];

  /* Outputs for Atomic SubSystem: '<Root>/planar_robot3dof_FD' */
  /* DiscreteIntegrator: '<S1>/Discrete-Time Integrator1' incorporates:
   *  Inport: '<Root>/init_pos'
   */
  if (planar_robot3dof_FD0_DW.DiscreteTimeIntegrator1_IC_LOAD != 0) {
    planar_robot3dof_FD0_DW.DiscreteTimeIntegrator1_DSTATE[0] =
      planar_robot3dof_FD0_U.init_pos[0];
    planar_robot3dof_FD0_DW.DiscreteTimeIntegrator1_DSTATE[1] =
      planar_robot3dof_FD0_U.init_pos[1];
    planar_robot3dof_FD0_DW.DiscreteTimeIntegrator1_DSTATE[2] =
      planar_robot3dof_FD0_U.init_pos[2];
  }

  /* MATLAB Function: '<S1>/calcSysMatrices' incorporates:
   *  Inport: '<Root>/arm_length'
   *  Inport: '<Root>/arm_link_radius'
   *  Inport: '<Root>/rho'
   */
  /* :  ROBOT = Planar3DoF(rho, radius, arm_length); */
  /* :  E = eye(3); */
  planar_robot3dof_FD0_eye(E_tmp);

  /* :  o = [0 0 0].'; */
  /* :  wz = [0 0 1].'; */
  /* :  jointOrigins = [ */
  /* :      0, arm_length(1), arm_length(2) */
  /* :      0, 0, 0 */
  /* :      0, 0, 0]; */
  jointOrigins[0] = 0.0;
  jointOrigins[3] = planar_robot3dof_FD0_U.arm_length[0];
  jointOrigins[6] = planar_robot3dof_FD0_U.arm_length[1];

  /* :  TCP_T_EE = [E, [arm_length(3) 0 0]'; o.', 1]; */
  /* :  Mass = cell(3,1); */
  /* :  g0 = cell(3,1); */
  /* :  for iLink = 1:3 */
  /* :  m = pi * radius^2 * arm_length(iLink) * rho; */
  m_tmp = planar_robot3dof_FD0_U.arm_link_radius *
    planar_robot3dof_FD0_U.arm_link_radius;
  m_tmp_0 = m_tmp * 3.1415926535897931;
  m = m_tmp_0 * planar_robot3dof_FD0_U.arm_length[0] *
    planar_robot3dof_FD0_U.rho;

  /* :  com = [arm_length(iLink)/2, 0, 0]; */
  body_CenterOfMass_idx_0 = planar_robot3dof_FD0_U.arm_length[0] / 2.0;

  /* :  Ix = 0.5 * m * radius^2; */
  /* :  Iz = (1/4) * m * radius^2 + (1/12) * m * arm_length(iLink)^2; */
  Iz = 0.25 * m * m_tmp + 0.083333333333333329 * m *
    (planar_robot3dof_FD0_U.arm_length[0] * planar_robot3dof_FD0_U.arm_length[0]);

  /* :  body.Mass = m; */
  /* :  body.CenterOfMass = com; */
  /* :  body.Inertia = [Ix, Iz, Iz, 0, 0, 0]; */
  /* :  Mass{iLink} = Inertia(body.Mass, body.CenterOfMass, diag(body.Inertia(1:3))); */
  b_m = m;
  inertialTwist_pre[0] = 0.5 * m * m_tmp;
  inertialTwist_pre[1] = Iz;
  inertialTwist_pre[2] = Iz;
  inertialTwist_pre[3] = 0.0;
  inertialTwist_pre[4] = 0.0;
  inertialTwist_pre[5] = 0.0;
  planar_robot3dof_FD0_diag(&inertialTwist_pre[0], tmp2);

  /* Outport: '<Root>/joint_pos' incorporates:
   *  DiscreteIntegrator: '<S1>/Discrete-Time Integrator1'
   */
  /* :  S = Skew(c); */
  /* :  out = [ */
  /* :          0,         -vec(3),   vec(2) */
  /* :          vec(3),    0,         -vec(1) */
  /* :          -vec(2),   vec(1),    0 */
  /* :      ]; */
  planar_robot3dof_FD0_Y.joint_pos[0] =
    planar_robot3dof_FD0_DW.DiscreteTimeIntegrator1_DSTATE[0];

  /* Outport: '<Root>/joint_vel' incorporates:
   *  DiscreteIntegrator: '<S1>/Discrete-Time Integrator'
   */
  planar_robot3dof_FD0_Y.joint_vel[0] =
    planar_robot3dof_FD0_DW.DiscreteTimeIntegrator_DSTATE[0];

  /* MATLAB Function: '<S1>/calcSysMatrices' */
  jointOrigins[1] = 0.0;
  jointOrigins[2] = 0.0;
  S[0] = 0.0;

  /* Outport: '<Root>/joint_pos' incorporates:
   *  DiscreteIntegrator: '<S1>/Discrete-Time Integrator1'
   */
  planar_robot3dof_FD0_Y.joint_pos[1] =
    planar_robot3dof_FD0_DW.DiscreteTimeIntegrator1_DSTATE[1];

  /* Outport: '<Root>/joint_vel' incorporates:
   *  DiscreteIntegrator: '<S1>/Discrete-Time Integrator'
   */
  planar_robot3dof_FD0_Y.joint_vel[1] =
    planar_robot3dof_FD0_DW.DiscreteTimeIntegrator_DSTATE[1];

  /* MATLAB Function: '<S1>/calcSysMatrices' */
  jointOrigins[4] = 0.0;
  jointOrigins[5] = 0.0;
  S[3] = 0.0;

  /* Outport: '<Root>/joint_pos' incorporates:
   *  DiscreteIntegrator: '<S1>/Discrete-Time Integrator1'
   */
  planar_robot3dof_FD0_Y.joint_pos[2] =
    planar_robot3dof_FD0_DW.DiscreteTimeIntegrator1_DSTATE[2];

  /* Outport: '<Root>/joint_vel' incorporates:
   *  DiscreteIntegrator: '<S1>/Discrete-Time Integrator'
   */
  planar_robot3dof_FD0_Y.joint_vel[2] =
    planar_robot3dof_FD0_DW.DiscreteTimeIntegrator_DSTATE[2];

  /* MATLAB Function: '<S1>/calcSysMatrices' incorporates:
   *  Inport: '<Root>/arm_length'
   *  Inport: '<Root>/rho'
   *  Outport: '<Root>/joint_pos'
   *  Outport: '<Root>/joint_vel'
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

  /* :  out = [ */
  /* :          m*eye(3),   -m*S */
  /* :          m*S,        I - m*S*S */
  /* :      ]; */
  for (i = 0; i < 9; i++) {
    y[i] = m * static_cast<real_T>(c_b[i]);
    b_y[i] = m * S[i];
  }

  /* :  g0{iLink} = [E, jointOrigins(:,iLink); o.', 1]; */
  /* :  m = pi * radius^2 * arm_length(iLink) * rho; */
  m = m_tmp_0 * planar_robot3dof_FD0_U.arm_length[1] *
    planar_robot3dof_FD0_U.rho;

  /* :  com = [arm_length(iLink)/2, 0, 0]; */
  body_CenterOfMass_idx_0 = planar_robot3dof_FD0_U.arm_length[1] / 2.0;

  /* :  Ix = 0.5 * m * radius^2; */
  /* :  Iz = (1/4) * m * radius^2 + (1/12) * m * arm_length(iLink)^2; */
  Iz = 0.25 * m * m_tmp + 0.083333333333333329 * m *
    (planar_robot3dof_FD0_U.arm_length[1] * planar_robot3dof_FD0_U.arm_length[1]);

  /* :  body.Mass = m; */
  /* :  body.CenterOfMass = com; */
  /* :  body.Inertia = [Ix, Iz, Iz, 0, 0, 0]; */
  /* :  Mass{iLink} = Inertia(body.Mass, body.CenterOfMass, diag(body.Inertia(1:3))); */
  c_m = m;
  inertialTwist_pre[0] = 0.5 * m * m_tmp;
  inertialTwist_pre[1] = Iz;
  inertialTwist_pre[2] = Iz;
  inertialTwist_pre[3] = 0.0;
  inertialTwist_pre[4] = 0.0;
  inertialTwist_pre[5] = 0.0;
  planar_robot3dof_FD0_diag(&inertialTwist_pre[0], b_I);

  /* :  S = Skew(c); */
  /* :  out = [ */
  /* :          0,         -vec(3),   vec(2) */
  /* :          vec(3),    0,         -vec(1) */
  /* :          -vec(2),   vec(1),    0 */
  /* :      ]; */
  b_S[0] = 0.0;
  b_S[3] = 0.0;
  b_S[6] = 0.0;
  b_S[1] = 0.0;
  b_S[4] = 0.0;
  b_S[7] = -body_CenterOfMass_idx_0;
  b_S[2] = -0.0;
  b_S[5] = body_CenterOfMass_idx_0;
  b_S[8] = 0.0;

  /* :  out = [ */
  /* :          m*eye(3),   -m*S */
  /* :          m*S,        I - m*S*S */
  /* :      ]; */
  for (i = 0; i < 9; i++) {
    c_y[i] = m * static_cast<real_T>(c_b[i]);
    d_y[i] = m * b_S[i];
  }

  /* :  g0{iLink} = [E, jointOrigins(:,iLink); o.', 1]; */
  /* :  m = pi * radius^2 * arm_length(iLink) * rho; */
  m = m_tmp_0 * planar_robot3dof_FD0_U.arm_length[2] *
    planar_robot3dof_FD0_U.rho;

  /* :  com = [arm_length(iLink)/2, 0, 0]; */
  body_CenterOfMass_idx_0 = planar_robot3dof_FD0_U.arm_length[2] / 2.0;

  /* :  Ix = 0.5 * m * radius^2; */
  /* :  Iz = (1/4) * m * radius^2 + (1/12) * m * arm_length(iLink)^2; */
  Iz = 0.25 * m * m_tmp + 0.083333333333333329 * m *
    (planar_robot3dof_FD0_U.arm_length[2] * planar_robot3dof_FD0_U.arm_length[2]);

  /* :  body.Mass = m; */
  /* :  body.CenterOfMass = com; */
  /* :  body.Inertia = [Ix, Iz, Iz, 0, 0, 0]; */
  /* :  Mass{iLink} = Inertia(body.Mass, body.CenterOfMass, diag(body.Inertia(1:3))); */
  /* :  S = Skew(c); */
  /* :  out = [ */
  /* :          0,         -vec(3),   vec(2) */
  /* :          vec(3),    0,         -vec(1) */
  /* :          -vec(2),   vec(1),    0 */
  /* :      ]; */
  c_S[1] = 0.0;
  c_S[4] = 0.0;
  c_S[7] = -body_CenterOfMass_idx_0;
  c_S[2] = -0.0;
  c_S[5] = body_CenterOfMass_idx_0;
  c_S[8] = 0.0;

  /* :  out = [ */
  /* :          m*eye(3),   -m*S */
  /* :          m*S,        I - m*S*S */
  /* :      ]; */
  /* :  g0{iLink} = [E, jointOrigins(:,iLink); o.', 1]; */
  /* :  ROBOT.csi = repmat([o; wz], 3, 1); */
  planar_robot3dof_FD0_repmat(ROBOT_csi);

  /* :  ROBOT.g_vec = [0 0 0]'; */
  /* :  ROBOT.g0 = [g0{1}; g0{2}; g0{3}]; */
  for (i = 0; i < 3; i++) {
    c_S[3 * i] = 0.0;
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

  /* :  ROBOT.Mass = [Mass{1}; Mass{2}; Mass{3}]; */
  b_m_0 = -b_m;
  body_CenterOfMass_idx_0 = -c_m;
  m_tmp_0 = -m;
  inertialTwist_pre[0] = 0.5 * m * m_tmp;
  inertialTwist_pre[1] = Iz;
  inertialTwist_pre[2] = Iz;
  inertialTwist_pre[3] = 0.0;
  inertialTwist_pre[4] = 0.0;
  inertialTwist_pre[5] = 0.0;
  planar_robot3dof_FD0_diag(&inertialTwist_pre[0], tmp);
  for (i = 0; i < 3; i++) {
    for (O_Htm_tmp = 0; O_Htm_tmp < 3; O_Htm_tmp++) {
      m_tmp = b_m * S[i] * S[3 * O_Htm_tmp];
      Iz = c_m * b_S[i] * b_S[3 * O_Htm_tmp];
      tmp2_0 = m * c_S[i] * c_S[3 * O_Htm_tmp];
      ROBOT_Mass_tmp = 3 * O_Htm_tmp + 1;
      m_tmp += S[i + 3] * b_m * S[ROBOT_Mass_tmp];
      Iz += b_S[i + 3] * c_m * b_S[ROBOT_Mass_tmp];
      tmp2_0 += c_S[i + 3] * m * c_S[ROBOT_Mass_tmp];
      ROBOT_Mass_tmp = 3 * O_Htm_tmp + 2;
      m_tmp += S[i + 6] * b_m * S[ROBOT_Mass_tmp];
      Iz += b_S[i + 6] * c_m * b_S[ROBOT_Mass_tmp];
      tmp2_0 += c_S[i + 6] * m * c_S[ROBOT_Mass_tmp];
      idxStart_4Row = 3 * O_Htm_tmp + i;
      jointOrigins[idxStart_4Row] = tmp2[idxStart_4Row] - m_tmp;
      b_I_0[idxStart_4Row] = b_I[idxStart_4Row] - Iz;
      tmp_0[idxStart_4Row] = tmp[idxStart_4Row] - tmp2_0;
      idxStart_4Row = 3 * i + O_Htm_tmp;
      ROBOT_Mass_tmp = 18 * i + O_Htm_tmp;
      ROBOT_Mass[ROBOT_Mass_tmp] = y[idxStart_4Row];
      ROBOT_Mass[O_Htm_tmp + 18 * (i + 3)] = S[idxStart_4Row] * b_m_0;
      ROBOT_Mass[ROBOT_Mass_tmp + 3] = b_y[idxStart_4Row];
    }
  }

  for (i = 0; i < 3; i++) {
    idxStart_4Row = (i + 3) * 18;
    ROBOT_Mass[idxStart_4Row + 3] = jointOrigins[3 * i];
    ROBOT_Mass[18 * i + 6] = c_y[3 * i];
    ROBOT_Mass[idxStart_4Row + 6] = b_S[3 * i] * body_CenterOfMass_idx_0;
    ROBOT_Mass[18 * i + 9] = d_y[3 * i];
    ROBOT_Mass[idxStart_4Row + 9] = b_I_0[3 * i];
    ROBOT_Mass[18 * i + 12] = static_cast<real_T>(c_b[3 * i]) * m;
    b_m = c_S[3 * i];
    ROBOT_Mass[idxStart_4Row + 12] = m_tmp_0 * b_m;
    ROBOT_Mass[18 * i + 15] = m * b_m;
    ROBOT_Mass[idxStart_4Row + 15] = tmp_0[3 * i];
    ROBOT_Mass_tmp = 3 * i + 1;
    ROBOT_Mass[idxStart_4Row + 4] = jointOrigins[ROBOT_Mass_tmp];
    ROBOT_Mass[18 * i + 7] = c_y[ROBOT_Mass_tmp];
    ROBOT_Mass[idxStart_4Row + 7] = b_S[ROBOT_Mass_tmp] *
      body_CenterOfMass_idx_0;
    ROBOT_Mass[18 * i + 10] = d_y[ROBOT_Mass_tmp];
    ROBOT_Mass[idxStart_4Row + 10] = b_I_0[ROBOT_Mass_tmp];
    ROBOT_Mass[18 * i + 13] = static_cast<real_T>(c_b[ROBOT_Mass_tmp]) * m;
    b_m = c_S[ROBOT_Mass_tmp];
    ROBOT_Mass[idxStart_4Row + 13] = m_tmp_0 * b_m;
    ROBOT_Mass[18 * i + 16] = m * b_m;
    ROBOT_Mass[idxStart_4Row + 16] = tmp_0[ROBOT_Mass_tmp];
    ROBOT_Mass_tmp = 3 * i + 2;
    ROBOT_Mass[idxStart_4Row + 5] = jointOrigins[ROBOT_Mass_tmp];
    ROBOT_Mass[18 * i + 8] = c_y[ROBOT_Mass_tmp];
    ROBOT_Mass[idxStart_4Row + 8] = b_S[ROBOT_Mass_tmp] *
      body_CenterOfMass_idx_0;
    ROBOT_Mass[18 * i + 11] = d_y[ROBOT_Mass_tmp];
    ROBOT_Mass[idxStart_4Row + 11] = b_I_0[ROBOT_Mass_tmp];
    ROBOT_Mass[18 * i + 14] = static_cast<real_T>(c_b[ROBOT_Mass_tmp]) * m;
    b_m = c_S[ROBOT_Mass_tmp];
    ROBOT_Mass[idxStart_4Row + 14] = m_tmp_0 * b_m;
    ROBOT_Mass[18 * i + 17] = m * b_m;
    ROBOT_Mass[idxStart_4Row + 17] = tmp_0[ROBOT_Mass_tmp];
  }

  /* :  ROBOT.tcp_t_ee = TCP_T_EE; */
  /* :  ndof = size(ROBOT.g0, 1)/4; */
  /* :  q = reshape(q, ndof, 1); */
  /* :  dq = reshape(dq, ndof, 1); */
  /* :  M = zeros(ndof, ndof); */
  /* :  dM = zeros(ndof, ndof); */
  /* :  CC = zeros(ndof, ndof); */
  std::memset(&planar_robot3dof_FD0_B.M[0], 0, 9U * sizeof(real_T));
  std::memset(&planar_robot3dof_FD0_B.CC[0], 0, 9U * sizeof(real_T));

  /* :  g = zeros(ndof, 1); */
  planar_robot3dof_FD0_B.g[0] = 0.0;
  planar_robot3dof_FD0_B.g[1] = 0.0;
  planar_robot3dof_FD0_B.g[2] = 0.0;

  /* :  J_pre = zeros(6, ndof); */
  /* :  dJ_pre = zeros(6, ndof); */
  std::memset(&J_pre[0], 0, 18U * sizeof(real_T));
  std::memset(&dJ_pre[0], 0, 18U * sizeof(real_T));

  /* :  inertialTwist_pre = zeros(6,1); */
  for (i = 0; i < 6; i++) {
    inertialTwist_pre[i] = 0.0;
  }

  /* :  O_Htm_pre = eye(4); */
  std::memset(&O_Htm_pre[0], 0, sizeof(real_T) << 4U);
  O_Htm_pre[0] = 1.0;
  O_Htm_pre[5] = 1.0;
  O_Htm_pre[10] = 1.0;
  O_Htm_pre[15] = 1.0;

  /* :  for iLink = 1:ndof */
  tmp[0] = 0.0;
  tmp[4] = 0.0;
  tmp[8] = 0.0;
  for (ROBOT_Mass_tmp = 0; ROBOT_Mass_tmp < 3; ROBOT_Mass_tmp++) {
    /* :  idxStart_4Row = 4*(iLink-1) + 1; */
    idxStart_4Row = ROBOT_Mass_tmp << 2;

    /* :  idxEnd_4Row = idxStart_4Row + 3; */
    /* :  idxStart_6Row = 6*(iLink-1) + 1; */
    idxStart_6Row = 6 * ROBOT_Mass_tmp;

    /* :  idxEnd_6Row = idxStart_6Row + 5; */
    /* :  relBodyJac = ROBOT.csi(idxStart_6Row:idxEnd_6Row); */
    /* :  relBodyJac = reshape(relBodyJac, 6, 1); */
    /* :  relTwist = relBodyJac * dq(iLink); */
    m_tmp = planar_robot3dof_FD0_Y.joint_vel[ROBOT_Mass_tmp];
    for (i = 0; i < 6; i++) {
      relTwist[i] = ROBOT_csi[idxStart_6Row + i] * m_tmp;
    }

    /* :  Htm = ROBOT.g0(idxStart_4Row:idxEnd_4Row, 1:4); */
    /* :  Htm = Htm * Exponential(relBodyJac, q(iLink)); */
    /* :  o = [0 0 0].'; */
    /* :  I = eye( 3 ); */
    /* :  v = csi(1:3); */
    /* :  w = csi(4:6); */
    /* :  if all( w == o ) */
    m = ROBOT_csi[idxStart_6Row + 3];
    ROBOT_csi_0[0] = (m == 0.0);
    b_m = ROBOT_csi[idxStart_6Row + 4];
    ROBOT_csi_0[1] = (b_m == 0.0);
    c_m = ROBOT_csi[idxStart_6Row + 5];
    ROBOT_csi_0[2] = (c_m == 0.0);
    if (planar_robot3dof_FD0_all(ROBOT_csi_0)) {
      /* :  out = [I v*theta; zeros(1,3) 1]; */
      m_tmp = planar_robot3dof_FD0_Y.joint_pos[ROBOT_Mass_tmp];
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
      /* :  else */
      /* :  w_hat = Skew( w ); */
      /* :  out = [ */
      /* :      0         -vec(3)   vec(2) */
      /* :      vec(3)    0         -vec(1) */
      /* :      -vec(2)   vec(1)    0 */
      /* :      ]; */
      jointOrigins[0] = 0.0;
      jointOrigins[3] = -c_m;
      jointOrigins[6] = b_m;
      jointOrigins[1] = c_m;
      jointOrigins[4] = 0.0;
      jointOrigins[7] = -m;
      jointOrigins[2] = -b_m;
      jointOrigins[5] = m;
      jointOrigins[8] = 0.0;

      /* :  R_minus_I = w_hat * sin( theta ) + w_hat * w_hat * ( 1 - cos(theta) ); */
      m = std::sin(planar_robot3dof_FD0_Y.joint_pos[ROBOT_Mass_tmp]);
      Iz = std::cos(planar_robot3dof_FD0_Y.joint_pos[ROBOT_Mass_tmp]);

      /* :  out = [I+R_minus_I zeros(3,1); zeros(1,3) 1]; */
      m_tmp = 1.0 - Iz;
      for (i = 0; i < 3; i++) {
        for (O_Htm_tmp = 0; O_Htm_tmp < 3; O_Htm_tmp++) {
          b_m = jointOrigins[3 * O_Htm_tmp] * jointOrigins[i];
          b_m += jointOrigins[3 * O_Htm_tmp + 1] * jointOrigins[i + 3];
          b_m += jointOrigins[3 * O_Htm_tmp + 2] * jointOrigins[i + 6];
          tmp2[i + 3 * O_Htm_tmp] = b_m;
        }
      }

      for (i = 0; i < 3; i++) {
        O_Htm_tmp_0 = i << 2;
        O_Htm[O_Htm_tmp_0] = (jointOrigins[3 * i] * m + tmp2[3 * i] * m_tmp) +
          E_tmp[3 * i];
        O_Htm_tmp = 3 * i + 1;
        O_Htm[O_Htm_tmp_0 + 1] = (jointOrigins[O_Htm_tmp] * m + tmp2[O_Htm_tmp] *
          m_tmp) + E_tmp[O_Htm_tmp];
        O_Htm_tmp = 3 * i + 2;
        O_Htm[O_Htm_tmp_0 + 2] = (jointOrigins[O_Htm_tmp] * m + tmp2[O_Htm_tmp] *
          m_tmp) + E_tmp[O_Htm_tmp];
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
        ROBOT_g0_data[O_Htm_tmp + ROBOT_g0_size[0] * i] = ROBOT_g0
          [(idxStart_4Row + O_Htm_tmp) + 12 * i];
      }
    }

    planar_robot3dof_FD0_mtimes(ROBOT_g0_data, ROBOT_g0_size, O_Htm, Htm_data,
      Htm_size);

    /* :  O_Htm = O_Htm_pre * Htm; */
    for (i = 0; i < 4; i++) {
      b_m = O_Htm_pre[i];
      c_m = O_Htm_pre[i + 4];
      body_CenterOfMass_idx_0 = O_Htm_pre[i + 8];
      m_tmp_0 = O_Htm_pre[i + 12];
      for (O_Htm_tmp = 0; O_Htm_tmp < 4; O_Htm_tmp++) {
        O_Htm_tmp_0 = O_Htm_tmp << 2;
        m = Htm_data[O_Htm_tmp_0] * b_m;
        m += Htm_data[O_Htm_tmp_0 + 1] * c_m;
        m += Htm_data[O_Htm_tmp_0 + 2] * body_CenterOfMass_idx_0;
        m += Htm_data[O_Htm_tmp_0 + 3] * m_tmp_0;
        O_Htm[i + O_Htm_tmp_0] = m;
      }
    }

    /* :  inertialTwist = relTwist; */
    for (i = 0; i < 6; i++) {
      inertialTwist[i] = relTwist[i];
    }

    /* :  invAd = InvAdjoint(Htm); */
    /* :  R_tra = Htm(1:3,1:3).'; */
    for (i = 0; i < 3; i++) {
      jointOrigins[3 * i] = Htm_data[i];
      jointOrigins[3 * i + 1] = Htm_data[i + Htm_size[0]];
      jointOrigins[3 * i + 2] = Htm_data[(Htm_size[0] << 1) + i];
    }

    /* :  p_hat = Skew( Htm(1:3,4) ); */
    /* :  out = [ */
    /* :      0         -vec(3)   vec(2) */
    /* :      vec(3)    0         -vec(1) */
    /* :      -vec(2)   vec(1)    0 */
    /* :      ]; */
    /* :  out = [R_tra -R_tra*p_hat; zeros(3) R_tra]; */
    for (i = 0; i < 9; i++) {
      tmp2[i] = -jointOrigins[i];
    }

    tmp[3] = -Htm_data[Htm_size[0] * 3 + 2];
    tmp[6] = Htm_data[Htm_size[0] * 3 + 1];
    tmp[1] = Htm_data[Htm_size[0] * 3 + 2];
    tmp[7] = -Htm_data[Htm_size[0] * 3];
    tmp[2] = -Htm_data[Htm_size[0] * 3 + 1];
    tmp[5] = Htm_data[Htm_size[0] * 3];
    for (i = 0; i < 3; i++) {
      b_m = tmp2[i];
      m = tmp2[i + 3];
      c_m = tmp2[i + 6];
      for (O_Htm_tmp = 0; O_Htm_tmp < 3; O_Htm_tmp++) {
        body_CenterOfMass_idx_0 = tmp[3 * O_Htm_tmp] * b_m;
        body_CenterOfMass_idx_0 += tmp[3 * O_Htm_tmp + 1] * m;
        body_CenterOfMass_idx_0 += tmp[3 * O_Htm_tmp + 2] * c_m;
        S[i + 3 * O_Htm_tmp] = body_CenterOfMass_idx_0;
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

    /* :  J = zeros(6, ndof); */
    /* :  dJ = zeros(6, ndof); */
    std::memset(&J[0], 0, 18U * sizeof(real_T));
    std::memset(&dJ[0], 0, 18U * sizeof(real_T));

    /* :  if iLink > 1 */
    if (ROBOT_Mass_tmp + 1 > 1) {
      /* :  inertialTwist = inertialTwist + invAd * inertialTwist_pre; */
      for (i = 0; i < 6; i++) {
        m_tmp = 0.0;
        for (O_Htm_tmp = 0; O_Htm_tmp < 6; O_Htm_tmp++) {
          m_tmp += invAd[6 * O_Htm_tmp + i] * inertialTwist_pre[O_Htm_tmp];
        }

        inertialTwist[i] = relTwist[i] + m_tmp;
      }

      /* :  J(1:6, 1:iLink-1) = invAd * J_pre(1:6, 1:iLink-1); */
      J_pre_size[0] = 6;
      J_pre_size[1] = ROBOT_Mass_tmp;
      for (i = 0; i < ROBOT_Mass_tmp; i++) {
        for (O_Htm_tmp = 0; O_Htm_tmp < 6; O_Htm_tmp++) {
          J_pre_data[O_Htm_tmp + 6 * i] = J_pre[6 * i + O_Htm_tmp];
        }
      }

      planar_robot3dof_FD0_mtimes_j(invAd, J_pre_data, J_pre_size, tmp_data_1,
        Htm_size);
      O_Htm_tmp_0 = Htm_size[1];
      for (i = 0; i < O_Htm_tmp_0; i++) {
        for (O_Htm_tmp = 0; O_Htm_tmp < 6; O_Htm_tmp++) {
          J[O_Htm_tmp + 6 * i] = tmp_data_1[6 * i + O_Htm_tmp];
        }
      }

      /* :  dJ(1:6, 1:iLink-1) = invAd * dJ_pre(1:6, 1:iLink-1)- LieBracket(relTwist) * J(1:6, 1:iLink-1); */
      /* :  Sv = Skew( twist(1:3) ); */
      /* :  out = [ */
      /* :      0         -vec(3)   vec(2) */
      /* :      vec(3)    0         -vec(1) */
      /* :      -vec(2)   vec(1)    0 */
      /* :      ]; */
      /* :  Sw = Skew( twist(4:6) ); */
      /* :  out = [ */
      /* :      0         -vec(3)   vec(2) */
      /* :      vec(3)    0         -vec(1) */
      /* :      -vec(2)   vec(1)    0 */
      /* :      ]; */
      jointOrigins[0] = 0.0;
      jointOrigins[3] = -relTwist[5];
      jointOrigins[6] = relTwist[4];
      jointOrigins[1] = relTwist[5];
      jointOrigins[4] = 0.0;
      jointOrigins[7] = -relTwist[3];
      jointOrigins[2] = -relTwist[4];
      jointOrigins[5] = relTwist[3];
      jointOrigins[8] = 0.0;

      /* :  ad = [Sw Sv; zeros(3) Sw]; */
      J_pre_size[0] = 6;
      J_pre_size[1] = ROBOT_Mass_tmp;
      for (i = 0; i < ROBOT_Mass_tmp; i++) {
        for (O_Htm_tmp = 0; O_Htm_tmp < 6; O_Htm_tmp++) {
          J_pre_data[O_Htm_tmp + 6 * i] = dJ_pre[6 * i + O_Htm_tmp];
        }
      }

      planar_robot3dof_FD0_mtimes_j(invAd, J_pre_data, J_pre_size, tmp_data_1,
        Htm_size);
      jointOrigins_0[18] = 0.0;
      jointOrigins_0[24] = -relTwist[2];
      jointOrigins_0[30] = relTwist[1];
      jointOrigins_0[19] = relTwist[2];
      jointOrigins_0[25] = 0.0;
      jointOrigins_0[31] = -relTwist[0];
      jointOrigins_0[20] = -relTwist[1];
      jointOrigins_0[26] = relTwist[0];
      jointOrigins_0[32] = 0.0;
      for (i = 0; i < 3; i++) {
        b_m = jointOrigins[3 * i];
        jointOrigins_0[6 * i] = b_m;
        jointOrigins_0[6 * i + 3] = 0.0;
        O_Htm_tmp = (i + 3) * 6;
        jointOrigins_0[O_Htm_tmp + 3] = b_m;
        b_m = jointOrigins[3 * i + 1];
        jointOrigins_0[6 * i + 1] = b_m;
        jointOrigins_0[6 * i + 4] = 0.0;
        jointOrigins_0[O_Htm_tmp + 4] = b_m;
        b_m = jointOrigins[3 * i + 2];
        jointOrigins_0[6 * i + 2] = b_m;
        jointOrigins_0[6 * i + 5] = 0.0;
        jointOrigins_0[O_Htm_tmp + 5] = b_m;
      }

      J_pre_size[0] = 6;
      J_pre_size[1] = ROBOT_Mass_tmp;
      for (i = 0; i < ROBOT_Mass_tmp; i++) {
        for (O_Htm_tmp = 0; O_Htm_tmp < 6; O_Htm_tmp++) {
          J_pre_data[O_Htm_tmp + 6 * i] = J[6 * i + O_Htm_tmp];
        }
      }

      planar_robot3dof_FD0_mtimes_j(jointOrigins_0, J_pre_data, J_pre_size,
        tmp_data, tmp_size);
      if (Htm_size[1] == tmp_size[1]) {
        J_pre_size[0] = 6;
        J_pre_size[1] = ROBOT_Mass_tmp;
        for (i = 0; i < ROBOT_Mass_tmp; i++) {
          for (O_Htm_tmp = 0; O_Htm_tmp < 6; O_Htm_tmp++) {
            J_pre_data[O_Htm_tmp + 6 * i] = dJ_pre[6 * i + O_Htm_tmp];
          }
        }

        planar_robot3dof_FD0_mtimes_j(invAd, J_pre_data, J_pre_size, tmp_data_1,
          Htm_size);
        jointOrigins_0[18] = 0.0;
        jointOrigins_0[24] = -relTwist[2];
        jointOrigins_0[30] = relTwist[1];
        jointOrigins_0[19] = relTwist[2];
        jointOrigins_0[25] = 0.0;
        jointOrigins_0[31] = -relTwist[0];
        jointOrigins_0[20] = -relTwist[1];
        jointOrigins_0[26] = relTwist[0];
        jointOrigins_0[32] = 0.0;
        for (i = 0; i < 3; i++) {
          b_m = jointOrigins[3 * i];
          jointOrigins_0[6 * i] = b_m;
          jointOrigins_0[6 * i + 3] = 0.0;
          O_Htm_tmp = (i + 3) * 6;
          jointOrigins_0[O_Htm_tmp + 3] = b_m;
          b_m = jointOrigins[3 * i + 1];
          jointOrigins_0[6 * i + 1] = b_m;
          jointOrigins_0[6 * i + 4] = 0.0;
          jointOrigins_0[O_Htm_tmp + 4] = b_m;
          b_m = jointOrigins[3 * i + 2];
          jointOrigins_0[6 * i + 2] = b_m;
          jointOrigins_0[6 * i + 5] = 0.0;
          jointOrigins_0[O_Htm_tmp + 5] = b_m;
        }

        J_pre_size[0] = 6;
        J_pre_size[1] = ROBOT_Mass_tmp;
        for (i = 0; i < ROBOT_Mass_tmp; i++) {
          for (O_Htm_tmp = 0; O_Htm_tmp < 6; O_Htm_tmp++) {
            J_pre_data[O_Htm_tmp + 6 * i] = J[6 * i + O_Htm_tmp];
          }
        }

        planar_robot3dof_FD0_mtimes_j(jointOrigins_0, J_pre_data, J_pre_size,
          tmp_data, tmp_size);
        O_Htm_tmp_0 = Htm_size[1];
        for (i = 0; i < O_Htm_tmp_0; i++) {
          for (O_Htm_tmp = 0; O_Htm_tmp < 6; O_Htm_tmp++) {
            dJ[O_Htm_tmp + 6 * i] = tmp_data_1[6 * i + O_Htm_tmp] - tmp_data[6 *
              i + O_Htm_tmp];
          }
        }
      } else {
        planar_rob_binary_expand_op_hym(dJ, ROBOT_Mass_tmp, invAd, dJ_pre,
          jointOrigins, relTwist, J);
      }
    }

    /* :  J(1:6, iLink) = relBodyJac; */
    for (i = 0; i < 6; i++) {
      J[i + 6 * ROBOT_Mass_tmp] = ROBOT_csi[idxStart_6Row + i];
    }

    /* :  tmp = J(1:6, 1:iLink)' * ROBOT.Mass(idxStart_6Row:idxEnd_6Row, 1:6); */
    J_size[0] = 6;
    J_size[1] = ROBOT_Mass_tmp + 1;
    for (i = 0; i <= ROBOT_Mass_tmp; i++) {
      for (O_Htm_tmp = 0; O_Htm_tmp < 6; O_Htm_tmp++) {
        J_pre[O_Htm_tmp + 6 * i] = J[6 * i + O_Htm_tmp];
      }
    }

    ROBOT_Mass_size[0] = 6;
    ROBOT_Mass_size[1] = 6;
    for (i = 0; i < 6; i++) {
      for (O_Htm_tmp = 0; O_Htm_tmp < 6; O_Htm_tmp++) {
        ROBOT_Mass_data[O_Htm_tmp + ROBOT_Mass_size[0] * i] = ROBOT_Mass
          [(idxStart_6Row + O_Htm_tmp) + 18 * i];
      }
    }

    planar_robot3dof_FD0_mtimes_jf(J_pre, J_size, ROBOT_Mass_data,
      ROBOT_Mass_size, dJ_pre, Htm_size);

    /* :  M(1:iLink, 1:iLink) = M(1:iLink, 1:iLink) + tmp * J(1:6, 1:iLink); */
    J_size[0] = 6;
    J_size[1] = ROBOT_Mass_tmp + 1;
    J_size_0[0] = 6;
    J_size_0[1] = ROBOT_Mass_tmp + 1;
    for (i = 0; i <= ROBOT_Mass_tmp; i++) {
      for (O_Htm_tmp = 0; O_Htm_tmp < 6; O_Htm_tmp++) {
        b_m = J[6 * i + O_Htm_tmp];
        J_pre[O_Htm_tmp + 6 * i] = b_m;
        J_data[O_Htm_tmp + 6 * i] = b_m;
      }
    }

    planar_robot3dof_FD0_mtimes_jfu(dJ_pre, Htm_size, J_pre, J_size, y, tmp_size);
    planar_robot3dof_FD0_mtimes_jfu(dJ_pre, Htm_size, J_data, J_size_0, b_y,
      tmp_size_0);
    if ((ROBOT_Mass_tmp + 1 == tmp_size[0]) && (ROBOT_Mass_tmp + 1 ==
         tmp_size_0[1])) {
      J_size[0] = 6;
      J_size[1] = ROBOT_Mass_tmp + 1;
      for (i = 0; i <= ROBOT_Mass_tmp; i++) {
        for (O_Htm_tmp = 0; O_Htm_tmp < 6; O_Htm_tmp++) {
          J_pre[O_Htm_tmp + 6 * i] = J[6 * i + O_Htm_tmp];
        }
      }

      planar_robot3dof_FD0_mtimes_jfu(dJ_pre, Htm_size, J_pre, J_size, y,
        tmp_size);
      tmp_size_0[0] = ROBOT_Mass_tmp + 1;
      tmp_size_0[1] = ROBOT_Mass_tmp + 1;
      for (i = 0; i <= ROBOT_Mass_tmp; i++) {
        for (O_Htm_tmp = 0; O_Htm_tmp <= ROBOT_Mass_tmp; O_Htm_tmp++) {
          b_y[O_Htm_tmp + tmp_size_0[0] * i] = planar_robot3dof_FD0_B.M[3 * i +
            O_Htm_tmp] + y[tmp_size[0] * i + O_Htm_tmp];
        }
      }

      O_Htm_tmp_0 = tmp_size_0[1];
      idxStart_4Row = tmp_size_0[0];
      for (i = 0; i < O_Htm_tmp_0; i++) {
        for (O_Htm_tmp = 0; O_Htm_tmp < idxStart_4Row; O_Htm_tmp++) {
          planar_robot3dof_FD0_B.M[O_Htm_tmp + 3 * i] = b_y[tmp_size_0[0] * i +
            O_Htm_tmp];
        }
      }
    } else {
      planar_robo_binary_expand_op_hy(planar_robot3dof_FD0_B.M, ROBOT_Mass_tmp,
        dJ_pre, Htm_size, J);
    }

    /* :  tmptmp = tmp * dJ(1:6, 1:iLink); */
    /* :  dM(1:iLink, 1:iLink) = dM(1:iLink, 1:iLink) + tmptmp + tmptmp'; */
    /* :  Mass_x_ad_tmp = SkewCoriolis(ROBOT.Mass(idxStart_6Row:idxEnd_6Row, 1:6), inertialTwist(4:6)); */
    idxStart_6Row += 3;

    /* :  Sw = Skew(w); */
    /* :  out = [ */
    /* :      0         -vec(3)   vec(2) */
    /* :      vec(3)    0         -vec(1) */
    /* :      -vec(2)   vec(1)    0 */
    /* :      ]; */
    jointOrigins[0] = 0.0;
    jointOrigins[3] = -inertialTwist[5];
    jointOrigins[6] = inertialTwist[4];
    jointOrigins[1] = inertialTwist[5];
    jointOrigins[4] = 0.0;
    jointOrigins[7] = -inertialTwist[3];
    jointOrigins[2] = -inertialTwist[4];
    jointOrigins[5] = inertialTwist[3];
    jointOrigins[8] = 0.0;

    /* :  tmp = Mass(4:6, 1:3)*Sw; */
    /* :  tmp2 = Mass(4:6, 4:6)*Sw; */
    for (i = 0; i < 3; i++) {
      idxStart_4Row = idxStart_6Row + i;
      m = ROBOT_Mass[idxStart_4Row];
      c_m = ROBOT_Mass[idxStart_4Row + 54];
      body_CenterOfMass_idx_0 = ROBOT_Mass[idxStart_4Row + 18];
      m_tmp_0 = ROBOT_Mass[idxStart_4Row + 72];
      b_m_0 = ROBOT_Mass[idxStart_4Row + 36];
      m_tmp = ROBOT_Mass[idxStart_4Row + 90];
      for (O_Htm_tmp = 0; O_Htm_tmp < 3; O_Htm_tmp++) {
        b_m = jointOrigins[3 * O_Htm_tmp];
        Iz = m * b_m;
        tmp2_0 = c_m * b_m;
        b_m = jointOrigins[3 * O_Htm_tmp + 1];
        Iz += body_CenterOfMass_idx_0 * b_m;
        tmp2_0 += m_tmp_0 * b_m;
        b_m = jointOrigins[3 * O_Htm_tmp + 2];
        Iz += b_m_0 * b_m;
        tmp2_0 += m_tmp * b_m;
        idxStart_4Row = 3 * O_Htm_tmp + i;
        tmp2[idxStart_4Row] = tmp2_0;
        S[idxStart_4Row] = Iz;
      }
    }

    /* :  out = [Mass(1,1)*Sw -tmp'; tmp tmp2 - tmp2']; */
    m = ROBOT_Mass[idxStart_6Row - 3];

    /* :  CC(1:iLink, 1:iLink) = CC(1:iLink, 1:iLink) + J(1:6, 1:iLink)' * Mass_x_ad_tmp * J(1:6, 1:iLink) + tmp * dJ(1:6, 1:iLink); */
    J_size[0] = 6;
    J_size[1] = ROBOT_Mass_tmp + 1;
    for (i = 0; i <= ROBOT_Mass_tmp; i++) {
      for (O_Htm_tmp = 0; O_Htm_tmp < 6; O_Htm_tmp++) {
        J_pre[O_Htm_tmp + 6 * i] = J[6 * i + O_Htm_tmp];
      }
    }

    for (i = 0; i < 3; i++) {
      invAd[6 * i] = jointOrigins[3 * i] * m;
      idxStart_6Row = (i + 3) * 6;
      invAd[idxStart_6Row] = -S[i];
      invAd[6 * i + 3] = S[3 * i];
      invAd[idxStart_6Row + 3] = tmp2[3 * i] - tmp2[i];
      O_Htm_tmp = 3 * i + 1;
      invAd[6 * i + 1] = jointOrigins[O_Htm_tmp] * m;
      invAd[idxStart_6Row + 1] = -S[i + 3];
      invAd[6 * i + 4] = S[O_Htm_tmp];
      invAd[idxStart_6Row + 4] = tmp2[O_Htm_tmp] - tmp2[i + 3];
      O_Htm_tmp = 3 * i + 2;
      invAd[6 * i + 2] = jointOrigins[O_Htm_tmp] * m;
      invAd[idxStart_6Row + 2] = -S[i + 6];
      invAd[6 * i + 5] = S[O_Htm_tmp];
      invAd[idxStart_6Row + 5] = tmp2[O_Htm_tmp] - tmp2[i + 6];
    }

    planar_robot3dof_FD_mtimes_jfux(J_pre, J_size, invAd, tmp_data_2, tmp_size_4);
    J_size[0] = 6;
    J_size[1] = ROBOT_Mass_tmp + 1;
    J_size_0[0] = 6;
    J_size_0[1] = ROBOT_Mass_tmp + 1;
    for (i = 0; i <= ROBOT_Mass_tmp; i++) {
      for (O_Htm_tmp = 0; O_Htm_tmp < 6; O_Htm_tmp++) {
        b_m = J[6 * i + O_Htm_tmp];
        J_pre[O_Htm_tmp + 6 * i] = b_m;
        J_data[O_Htm_tmp + 6 * i] = b_m;
      }
    }

    planar_robot3dof_FD0_mtimes_jfu(tmp_data_2, tmp_size_4, J_pre, J_size, y,
      tmp_size);
    for (i = 0; i < 3; i++) {
      invAd[6 * i] = jointOrigins[3 * i] * m;
      idxStart_6Row = (i + 3) * 6;
      invAd[idxStart_6Row] = -S[i];
      invAd[6 * i + 3] = S[3 * i];
      invAd[idxStart_6Row + 3] = tmp2[3 * i] - tmp2[i];
      O_Htm_tmp = 3 * i + 1;
      invAd[6 * i + 1] = jointOrigins[O_Htm_tmp] * m;
      invAd[idxStart_6Row + 1] = -S[i + 3];
      invAd[6 * i + 4] = S[O_Htm_tmp];
      invAd[idxStart_6Row + 4] = tmp2[O_Htm_tmp] - tmp2[i + 3];
      O_Htm_tmp = 3 * i + 2;
      invAd[6 * i + 2] = jointOrigins[O_Htm_tmp] * m;
      invAd[idxStart_6Row + 2] = -S[i + 6];
      invAd[6 * i + 5] = S[O_Htm_tmp];
      invAd[idxStart_6Row + 5] = tmp2[O_Htm_tmp] - tmp2[i + 6];
    }

    planar_robot3dof_FD_mtimes_jfux(J_data, J_size_0, invAd, tmp_data_2,
      tmp_size_4);
    J_size[0] = 6;
    J_size[1] = ROBOT_Mass_tmp + 1;
    J_size_0[0] = 6;
    J_size_0[1] = ROBOT_Mass_tmp + 1;
    for (i = 0; i <= ROBOT_Mass_tmp; i++) {
      for (O_Htm_tmp = 0; O_Htm_tmp < 6; O_Htm_tmp++) {
        b_m = J[6 * i + O_Htm_tmp];
        J_pre[O_Htm_tmp + 6 * i] = b_m;
        J_data[O_Htm_tmp + 6 * i] = b_m;
      }
    }

    planar_robot3dof_FD0_mtimes_jfu(tmp_data_2, tmp_size_4, J_pre, J_size, b_y,
      tmp_size_0);
    for (i = 0; i < 3; i++) {
      invAd[6 * i] = jointOrigins[3 * i] * m;
      idxStart_6Row = (i + 3) * 6;
      invAd[idxStart_6Row] = -S[i];
      invAd[6 * i + 3] = S[3 * i];
      invAd[idxStart_6Row + 3] = tmp2[3 * i] - tmp2[i];
      O_Htm_tmp = 3 * i + 1;
      invAd[6 * i + 1] = jointOrigins[O_Htm_tmp] * m;
      invAd[idxStart_6Row + 1] = -S[i + 3];
      invAd[6 * i + 4] = S[O_Htm_tmp];
      invAd[idxStart_6Row + 4] = tmp2[O_Htm_tmp] - tmp2[i + 3];
      O_Htm_tmp = 3 * i + 2;
      invAd[6 * i + 2] = jointOrigins[O_Htm_tmp] * m;
      invAd[idxStart_6Row + 2] = -S[i + 6];
      invAd[6 * i + 5] = S[O_Htm_tmp];
      invAd[idxStart_6Row + 5] = tmp2[O_Htm_tmp] - tmp2[i + 6];
    }

    planar_robot3dof_FD_mtimes_jfux(J_data, J_size_0, invAd, tmp_data_2,
      tmp_size_4);
    J_size[0] = 6;
    J_size[1] = ROBOT_Mass_tmp + 1;
    for (i = 0; i <= ROBOT_Mass_tmp; i++) {
      for (O_Htm_tmp = 0; O_Htm_tmp < 6; O_Htm_tmp++) {
        J_pre[O_Htm_tmp + 6 * i] = J[6 * i + O_Htm_tmp];
      }
    }

    planar_robot3dof_FD0_mtimes_jfu(tmp_data_2, tmp_size_4, J_pre, J_size, b_I,
      tmp_size_1);
    J_size[0] = 6;
    J_size[1] = ROBOT_Mass_tmp + 1;
    for (i = 0; i <= ROBOT_Mass_tmp; i++) {
      for (O_Htm_tmp = 0; O_Htm_tmp < 6; O_Htm_tmp++) {
        J_pre[O_Htm_tmp + 6 * i] = dJ[6 * i + O_Htm_tmp];
      }
    }

    planar_robot3dof_FD0_mtimes_jfu(dJ_pre, Htm_size, J_pre, J_size, y,
      tmp_size_2);
    J_size[0] = 6;
    J_size[1] = ROBOT_Mass_tmp + 1;
    for (i = 0; i <= ROBOT_Mass_tmp; i++) {
      for (O_Htm_tmp = 0; O_Htm_tmp < 6; O_Htm_tmp++) {
        J_pre[O_Htm_tmp + 6 * i] = J[6 * i + O_Htm_tmp];
      }
    }

    for (i = 0; i < 3; i++) {
      invAd[6 * i] = jointOrigins[3 * i] * m;
      idxStart_6Row = (i + 3) * 6;
      invAd[idxStart_6Row] = -S[i];
      invAd[6 * i + 3] = S[3 * i];
      invAd[idxStart_6Row + 3] = tmp2[3 * i] - tmp2[i];
      O_Htm_tmp = 3 * i + 1;
      invAd[6 * i + 1] = jointOrigins[O_Htm_tmp] * m;
      invAd[idxStart_6Row + 1] = -S[i + 3];
      invAd[6 * i + 4] = S[O_Htm_tmp];
      invAd[idxStart_6Row + 4] = tmp2[O_Htm_tmp] - tmp2[i + 3];
      O_Htm_tmp = 3 * i + 2;
      invAd[6 * i + 2] = jointOrigins[O_Htm_tmp] * m;
      invAd[idxStart_6Row + 2] = -S[i + 6];
      invAd[6 * i + 5] = S[O_Htm_tmp];
      invAd[idxStart_6Row + 5] = tmp2[O_Htm_tmp] - tmp2[i + 6];
    }

    planar_robot3dof_FD_mtimes_jfux(J_pre, J_size, invAd, tmp_data_2, tmp_size_4);
    J_size[0] = 6;
    J_size[1] = ROBOT_Mass_tmp + 1;
    for (i = 0; i <= ROBOT_Mass_tmp; i++) {
      for (O_Htm_tmp = 0; O_Htm_tmp < 6; O_Htm_tmp++) {
        J_pre[O_Htm_tmp + 6 * i] = J[6 * i + O_Htm_tmp];
      }
    }

    planar_robot3dof_FD0_mtimes_jfu(tmp_data_2, tmp_size_4, J_pre, J_size, y,
      tmp_size_3);
    J_size[0] = 6;
    J_size[1] = ROBOT_Mass_tmp + 1;
    for (i = 0; i <= ROBOT_Mass_tmp; i++) {
      for (O_Htm_tmp = 0; O_Htm_tmp < 6; O_Htm_tmp++) {
        J_pre[O_Htm_tmp + 6 * i] = dJ[6 * i + O_Htm_tmp];
      }
    }

    planar_robot3dof_FD0_mtimes_jfu(dJ_pre, Htm_size, J_pre, J_size, y,
      tmp_size_4);
    if ((ROBOT_Mass_tmp + 1 == tmp_size[0]) && (ROBOT_Mass_tmp + 1 ==
         tmp_size_0[1]) && ((ROBOT_Mass_tmp + 1 == 1 ? tmp_size_1[0] :
          ROBOT_Mass_tmp + 1) == tmp_size_2[0]) && ((ROBOT_Mass_tmp + 1 == 1 ?
          tmp_size_3[1] : ROBOT_Mass_tmp + 1) == tmp_size_4[1])) {
      J_size[0] = 6;
      J_size[1] = ROBOT_Mass_tmp + 1;
      for (i = 0; i <= ROBOT_Mass_tmp; i++) {
        for (O_Htm_tmp = 0; O_Htm_tmp < 6; O_Htm_tmp++) {
          J_pre[O_Htm_tmp + 6 * i] = J[6 * i + O_Htm_tmp];
        }
      }

      for (i = 0; i < 3; i++) {
        invAd[6 * i] = jointOrigins[3 * i] * m;
        idxStart_6Row = (i + 3) * 6;
        invAd[idxStart_6Row] = -S[i];
        invAd[6 * i + 3] = S[3 * i];
        invAd[idxStart_6Row + 3] = tmp2[3 * i] - tmp2[i];
        O_Htm_tmp = 3 * i + 1;
        invAd[6 * i + 1] = jointOrigins[O_Htm_tmp] * m;
        invAd[idxStart_6Row + 1] = -S[i + 3];
        invAd[6 * i + 4] = S[O_Htm_tmp];
        invAd[idxStart_6Row + 4] = tmp2[O_Htm_tmp] - tmp2[i + 3];
        O_Htm_tmp = 3 * i + 2;
        invAd[6 * i + 2] = jointOrigins[O_Htm_tmp] * m;
        invAd[idxStart_6Row + 2] = -S[i + 6];
        invAd[6 * i + 5] = S[O_Htm_tmp];
        invAd[idxStart_6Row + 5] = tmp2[O_Htm_tmp] - tmp2[i + 6];
      }

      planar_robot3dof_FD_mtimes_jfux(J_pre, J_size, invAd, tmp_data_2,
        tmp_size_4);
      J_size[0] = 6;
      J_size[1] = ROBOT_Mass_tmp + 1;
      for (i = 0; i <= ROBOT_Mass_tmp; i++) {
        for (O_Htm_tmp = 0; O_Htm_tmp < 6; O_Htm_tmp++) {
          J_pre[O_Htm_tmp + 6 * i] = J[6 * i + O_Htm_tmp];
        }
      }

      planar_robot3dof_FD0_mtimes_jfu(tmp_data_2, tmp_size_4, J_pre, J_size, y,
        tmp_size);
      J_size[0] = 6;
      J_size[1] = ROBOT_Mass_tmp + 1;
      for (i = 0; i <= ROBOT_Mass_tmp; i++) {
        for (O_Htm_tmp = 0; O_Htm_tmp < 6; O_Htm_tmp++) {
          J_pre[O_Htm_tmp + 6 * i] = dJ[6 * i + O_Htm_tmp];
        }
      }

      planar_robot3dof_FD0_mtimes_jfu(dJ_pre, Htm_size, J_pre, J_size, b_y,
        tmp_size_0);
      tmp_size_1[0] = ROBOT_Mass_tmp + 1;
      tmp_size_1[1] = ROBOT_Mass_tmp + 1;
      for (i = 0; i <= ROBOT_Mass_tmp; i++) {
        for (O_Htm_tmp = 0; O_Htm_tmp <= ROBOT_Mass_tmp; O_Htm_tmp++) {
          b_I[O_Htm_tmp + tmp_size_1[0] * i] = (planar_robot3dof_FD0_B.CC[3 * i
            + O_Htm_tmp] + y[tmp_size[0] * i + O_Htm_tmp]) + b_y[tmp_size_0[0] *
            i + O_Htm_tmp];
        }
      }

      O_Htm_tmp_0 = tmp_size_1[1];
      idxStart_4Row = tmp_size_1[0];
      for (i = 0; i < O_Htm_tmp_0; i++) {
        for (O_Htm_tmp = 0; O_Htm_tmp < idxStart_4Row; O_Htm_tmp++) {
          planar_robot3dof_FD0_B.CC[O_Htm_tmp + 3 * i] = b_I[tmp_size_1[0] * i +
            O_Htm_tmp];
        }
      }
    } else {
      planar_robot_binary_expand_op_h(planar_robot3dof_FD0_B.CC, ROBOT_Mass_tmp,
        J, m, jointOrigins, S, tmp2, dJ_pre, Htm_size, dJ);
    }

    /* :  g(1:iLink) = g(1:iLink) + tmp(1:iLink, 1:3) * O_Htm(1:3, 1:3)' * ROBOT.g_vec; */
    tmp_size_5[0] = ROBOT_Mass_tmp + 1;
    tmp_size_5[1] = 3;
    for (i = 0; i < 3; i++) {
      for (O_Htm_tmp = 0; O_Htm_tmp <= ROBOT_Mass_tmp; O_Htm_tmp++) {
        y[O_Htm_tmp + tmp_size_5[0] * i] = dJ_pre[Htm_size[0] * i + O_Htm_tmp];
      }

      O_Htm_tmp_0 = i << 2;
      tmp2[3 * i] = O_Htm[O_Htm_tmp_0];
      tmp2[3 * i + 1] = O_Htm[O_Htm_tmp_0 + 1];
      tmp2[3 * i + 2] = O_Htm[O_Htm_tmp_0 + 2];
    }

    planar_robot3dof_F_mtimes_jfuxr(y, tmp_size_5, tmp2, b_y, tmp_size);
    planar_robot3dof__mtimes_jfuxri(b_y, tmp_size, tmp_data_0, &i);
    if (ROBOT_Mass_tmp + 1 == i) {
      tmp_size_5[0] = ROBOT_Mass_tmp + 1;
      tmp_size_5[1] = 3;
      for (i = 0; i < 3; i++) {
        for (O_Htm_tmp = 0; O_Htm_tmp <= ROBOT_Mass_tmp; O_Htm_tmp++) {
          y[O_Htm_tmp + tmp_size_5[0] * i] = dJ_pre[Htm_size[0] * i + O_Htm_tmp];
        }

        O_Htm_tmp_0 = i << 2;
        tmp2[3 * i] = O_Htm[O_Htm_tmp_0];
        tmp2[3 * i + 1] = O_Htm[O_Htm_tmp_0 + 1];
        tmp2[3 * i + 2] = O_Htm[O_Htm_tmp_0 + 2];
      }

      planar_robot3dof_F_mtimes_jfuxr(y, tmp_size_5, tmp2, b_y, tmp_size);
      planar_robot3dof__mtimes_jfuxri(b_y, tmp_size, tmp_data_0, &i);
      idxStart_6Row = ROBOT_Mass_tmp + 1;
      for (i = 0; i < idxStart_6Row; i++) {
        tmp_data_3[i] = planar_robot3dof_FD0_B.g[i] + tmp_data_0[i];
      }

      O_Htm_tmp_0 = idxStart_6Row;
      std::memcpy(&planar_robot3dof_FD0_B.g[0], &tmp_data_3[0],
                  static_cast<uint32_T>(O_Htm_tmp_0) * sizeof(real_T));
    } else {
      planar_robot3d_binary_expand_op(planar_robot3dof_FD0_B.g, ROBOT_Mass_tmp,
        dJ_pre, Htm_size, O_Htm);
    }

    /* :  J_pre = J; */
    /* :  dJ_pre = dJ; */
    std::memcpy(&J_pre[0], &J[0], 18U * sizeof(real_T));
    std::memcpy(&dJ_pre[0], &dJ[0], 18U * sizeof(real_T));

    /* :  inertialTwist_pre = inertialTwist; */
    for (i = 0; i < 6; i++) {
      inertialTwist_pre[i] = inertialTwist[i];
    }

    /* :  O_Htm_pre = O_Htm; */
    std::memcpy(&O_Htm_pre[0], &O_Htm[0], sizeof(real_T) << 4U);
  }

  /* :  Htm_TCP = O_Htm(1:4,1:4) * ROBOT.tcp_t_ee; */
  /* :  pos_tcp = Htm_TCP(1:3,4); */
  for (i = 0; i < 3; i++) {
    ROBOT_Mass_tmp = i << 2;
    O_Htm_pre[ROBOT_Mass_tmp] = E_tmp[3 * i];
    O_Htm_pre[ROBOT_Mass_tmp + 1] = E_tmp[3 * i + 1];
    O_Htm_pre[ROBOT_Mass_tmp + 2] = E_tmp[3 * i + 2];
  }

  O_Htm_pre[12] = planar_robot3dof_FD0_U.arm_length[2];
  O_Htm_pre[13] = 0.0;
  O_Htm_pre[14] = 0.0;
  O_Htm_pre[3] = 0.0;
  O_Htm_pre[7] = 0.0;
  O_Htm_pre[11] = 0.0;
  O_Htm_pre[15] = 1.0;
  for (i = 0; i < 4; i++) {
    ROBOT_Mass_tmp = i << 2;
    b_m = O_Htm_pre[ROBOT_Mass_tmp];
    c_m = O_Htm_pre[ROBOT_Mass_tmp + 1];
    body_CenterOfMass_idx_0 = O_Htm_pre[ROBOT_Mass_tmp + 2];
    m_tmp_0 = O_Htm_pre[ROBOT_Mass_tmp + 3];
    for (O_Htm_tmp = 0; O_Htm_tmp < 4; O_Htm_tmp++) {
      m = b_m * O_Htm[O_Htm_tmp];
      m += O_Htm[O_Htm_tmp + 4] * c_m;
      m += O_Htm[O_Htm_tmp + 8] * body_CenterOfMass_idx_0;
      m += O_Htm[O_Htm_tmp + 12] * m_tmp_0;
      O_Htm_0[O_Htm_tmp + ROBOT_Mass_tmp] = m;
    }
  }

  /* Outport: '<Root>/TCP_pos' incorporates:
   *  MATLAB Function: '<S1>/calcSysMatrices'
   */
  /* :  B_J_TCP = InvAdjoint(ROBOT.tcp_t_ee) * J(1:6, 1:ndof); */
  /* :  O_J_TCP = [Htm_TCP(1:3, 1:3)* B_J_TCP(1:3, 1:ndof);Htm_TCP(1:3, 1:3)*B_J_TCP(4:6, 1:ndof)]; */
  m = O_Htm_0[12];
  planar_robot3dof_FD0_Y.TCP_pos[0] = m;

  /* SampleTimeMath: '<S2>/TSamp' incorporates:
   *  Outport: '<Root>/TCP_pos'
   *
   * About '<S2>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  m *= 1000.0;

  /* End of Outputs for SubSystem: '<Root>/planar_robot3dof_FD' */
  planar_robot3dof_FD0_B.TSamp[0] = m;

  /* Outputs for Atomic SubSystem: '<Root>/planar_robot3dof_FD' */
  /* UnitDelay: '<S2>/UD' */
  b_m = planar_robot3dof_FD0_DW.UD_DSTATE[0];

  /* End of Outputs for SubSystem: '<Root>/planar_robot3dof_FD' */
  planar_robot3dof_FD0_B.Uk1[0] = b_m;

  /* Outputs for Atomic SubSystem: '<Root>/planar_robot3dof_FD' */
  /* Outport: '<Root>/TCP_vel' incorporates:
   *  Sum: '<S2>/Diff'
   */
  m -= b_m;

  /* End of Outputs for SubSystem: '<Root>/planar_robot3dof_FD' */
  planar_robot3dof_FD0_Y.TCP_vel[0] = m;

  /* Outputs for Atomic SubSystem: '<Root>/planar_robot3dof_FD' */
  /* SampleTimeMath: '<S3>/TSamp' incorporates:
   *  Outport: '<Root>/TCP_vel'
   *
   * About '<S3>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  m *= 1000.0;

  /* End of Outputs for SubSystem: '<Root>/planar_robot3dof_FD' */
  planar_robot3dof_FD0_B.TSamp_m[0] = m;

  /* Outputs for Atomic SubSystem: '<Root>/planar_robot3dof_FD' */
  /* UnitDelay: '<S3>/UD' */
  b_m = planar_robot3dof_FD0_DW.UD_DSTATE_n[0];

  /* End of Outputs for SubSystem: '<Root>/planar_robot3dof_FD' */
  planar_robot3dof_FD0_B.Uk1_c[0] = b_m;

  /* Outputs for Atomic SubSystem: '<Root>/planar_robot3dof_FD' */
  /* Outport: '<Root>/TCP_acc' incorporates:
   *  Sum: '<S3>/Diff'
   */
  planar_robot3dof_FD0_Y.TCP_acc[0] = m - b_m;

  /* Outport: '<Root>/TCP_pos' incorporates:
   *  MATLAB Function: '<S1>/calcSysMatrices'
   */
  m = O_Htm_0[13];
  planar_robot3dof_FD0_Y.TCP_pos[1] = m;

  /* SampleTimeMath: '<S2>/TSamp' incorporates:
   *  Outport: '<Root>/TCP_pos'
   *
   * About '<S2>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  m *= 1000.0;

  /* End of Outputs for SubSystem: '<Root>/planar_robot3dof_FD' */
  planar_robot3dof_FD0_B.TSamp[1] = m;

  /* Outputs for Atomic SubSystem: '<Root>/planar_robot3dof_FD' */
  /* UnitDelay: '<S2>/UD' */
  b_m = planar_robot3dof_FD0_DW.UD_DSTATE[1];

  /* End of Outputs for SubSystem: '<Root>/planar_robot3dof_FD' */
  planar_robot3dof_FD0_B.Uk1[1] = b_m;

  /* Outputs for Atomic SubSystem: '<Root>/planar_robot3dof_FD' */
  /* Outport: '<Root>/TCP_vel' incorporates:
   *  Sum: '<S2>/Diff'
   */
  m -= b_m;

  /* End of Outputs for SubSystem: '<Root>/planar_robot3dof_FD' */
  planar_robot3dof_FD0_Y.TCP_vel[1] = m;

  /* Outputs for Atomic SubSystem: '<Root>/planar_robot3dof_FD' */
  /* SampleTimeMath: '<S3>/TSamp' incorporates:
   *  Outport: '<Root>/TCP_vel'
   *
   * About '<S3>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  m *= 1000.0;

  /* End of Outputs for SubSystem: '<Root>/planar_robot3dof_FD' */
  planar_robot3dof_FD0_B.TSamp_m[1] = m;

  /* Outputs for Atomic SubSystem: '<Root>/planar_robot3dof_FD' */
  /* UnitDelay: '<S3>/UD' */
  b_m = planar_robot3dof_FD0_DW.UD_DSTATE_n[1];

  /* End of Outputs for SubSystem: '<Root>/planar_robot3dof_FD' */
  planar_robot3dof_FD0_B.Uk1_c[1] = b_m;

  /* Outputs for Atomic SubSystem: '<Root>/planar_robot3dof_FD' */
  /* Outport: '<Root>/TCP_acc' incorporates:
   *  Sum: '<S3>/Diff'
   */
  planar_robot3dof_FD0_Y.TCP_acc[1] = m - b_m;

  /* Outport: '<Root>/TCP_pos' incorporates:
   *  MATLAB Function: '<S1>/calcSysMatrices'
   */
  m = O_Htm_0[14];
  planar_robot3dof_FD0_Y.TCP_pos[2] = m;

  /* SampleTimeMath: '<S2>/TSamp' incorporates:
   *  Outport: '<Root>/TCP_pos'
   *
   * About '<S2>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  m *= 1000.0;

  /* End of Outputs for SubSystem: '<Root>/planar_robot3dof_FD' */
  planar_robot3dof_FD0_B.TSamp[2] = m;

  /* Outputs for Atomic SubSystem: '<Root>/planar_robot3dof_FD' */
  /* UnitDelay: '<S2>/UD' */
  b_m = planar_robot3dof_FD0_DW.UD_DSTATE[2];

  /* End of Outputs for SubSystem: '<Root>/planar_robot3dof_FD' */
  planar_robot3dof_FD0_B.Uk1[2] = b_m;

  /* Outputs for Atomic SubSystem: '<Root>/planar_robot3dof_FD' */
  /* Outport: '<Root>/TCP_vel' incorporates:
   *  Sum: '<S2>/Diff'
   */
  m -= b_m;

  /* End of Outputs for SubSystem: '<Root>/planar_robot3dof_FD' */
  planar_robot3dof_FD0_Y.TCP_vel[2] = m;

  /* Outputs for Atomic SubSystem: '<Root>/planar_robot3dof_FD' */
  /* SampleTimeMath: '<S3>/TSamp' incorporates:
   *  Outport: '<Root>/TCP_vel'
   *
   * About '<S3>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  m *= 1000.0;

  /* End of Outputs for SubSystem: '<Root>/planar_robot3dof_FD' */
  planar_robot3dof_FD0_B.TSamp_m[2] = m;

  /* Outputs for Atomic SubSystem: '<Root>/planar_robot3dof_FD' */
  /* UnitDelay: '<S3>/UD' */
  b_m = planar_robot3dof_FD0_DW.UD_DSTATE_n[2];

  /* End of Outputs for SubSystem: '<Root>/planar_robot3dof_FD' */
  planar_robot3dof_FD0_B.Uk1_c[2] = b_m;

  /* Outputs for Atomic SubSystem: '<Root>/planar_robot3dof_FD' */
  /* Outport: '<Root>/TCP_acc' incorporates:
   *  Sum: '<S3>/Diff'
   */
  planar_robot3dof_FD0_Y.TCP_acc[2] = m - b_m;

  /* Product: '<S1>/Product5' */
  rt_invd3x3_snf(planar_robot3dof_FD0_B.M, planar_robot3dof_FD0_B.Product5);

  /* Product: '<S1>/Product3' incorporates:
   *  Outport: '<Root>/joint_vel'
   */
  std::memcpy(&E_tmp[0], &planar_robot3dof_FD0_B.CC[0], 9U * sizeof(real_T));
  body_CenterOfMass_idx_0 = planar_robot3dof_FD0_Y.joint_vel[0];
  m = planar_robot3dof_FD0_Y.joint_vel[1];
  b_m = planar_robot3dof_FD0_Y.joint_vel[2];
  for (i = 0; i < 3; i++) {
    c_m = E_tmp[i] * body_CenterOfMass_idx_0;
    c_m += E_tmp[i + 3] * m;
    c_m += E_tmp[i + 6] * b_m;

    /* Product: '<S1>/Product3' */
    planar_robot3dof_FD0_B.Product3[i] = c_m;

    /* Sum: '<S1>/Sum4' incorporates:
     *  Inport: '<Root>/joint_torque'
     */
    planar_robot3dof_FD0_B.Sum4[i] = (planar_robot3dof_FD0_U.joint_torque[i] -
      c_m) - planar_robot3dof_FD0_B.g[i];
  }

  /* End of Product: '<S1>/Product3' */

  /* Product: '<S1>/Product1' incorporates:
   *  Product: '<S1>/Product5'
   */
  std::memcpy(&E_tmp[0], &planar_robot3dof_FD0_B.Product5[0], 9U * sizeof(real_T));
  body_CenterOfMass_idx_0 = planar_robot3dof_FD0_B.Sum4[0];
  m = planar_robot3dof_FD0_B.Sum4[1];
  b_m = planar_robot3dof_FD0_B.Sum4[2];

  /* Update for DiscreteIntegrator: '<S1>/Discrete-Time Integrator1' */
  planar_robot3dof_FD0_DW.DiscreteTimeIntegrator1_IC_LOAD = 0U;
  for (i = 0; i < 3; i++) {
    /* Product: '<S1>/Product1' */
    c_m = E_tmp[i] * body_CenterOfMass_idx_0;
    c_m += E_tmp[i + 3] * m;
    c_m += E_tmp[i + 6] * b_m;

    /* Outport: '<Root>/joint_acc' incorporates:
     *  Product: '<S1>/Product1'
     */
    planar_robot3dof_FD0_Y.joint_acc[i] = c_m;

    /* Update for DiscreteIntegrator: '<S1>/Discrete-Time Integrator1' incorporates:
     *  Outport: '<Root>/joint_vel'
     */
    planar_robot3dof_FD0_DW.DiscreteTimeIntegrator1_DSTATE[i] += 0.001 *
      planar_robot3dof_FD0_Y.joint_vel[i];

    /* Update for DiscreteIntegrator: '<S1>/Discrete-Time Integrator' incorporates:
     *  Outport: '<Root>/joint_acc'
     */
    planar_robot3dof_FD0_DW.DiscreteTimeIntegrator_DSTATE[i] += 0.001 * c_m;

    /* Update for UnitDelay: '<S2>/UD' */
    planar_robot3dof_FD0_DW.UD_DSTATE[i] = planar_robot3dof_FD0_B.TSamp[i];

    /* Update for UnitDelay: '<S3>/UD' */
    planar_robot3dof_FD0_DW.UD_DSTATE_n[i] = planar_robot3dof_FD0_B.TSamp_m[i];
  }

  /* End of Outputs for SubSystem: '<Root>/planar_robot3dof_FD' */

  /* Matfile logging */
  rt_UpdateTXYLogVars((&planar_robot3dof_FD0_M)->rtwLogInfo,
                      (&(&planar_robot3dof_FD0_M)->Timing.taskTime0));

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.001s, 0.0s] */
    if ((rtmGetTFinal((&planar_robot3dof_FD0_M))!=-1) &&
        !((rtmGetTFinal((&planar_robot3dof_FD0_M))-(&planar_robot3dof_FD0_M)
           ->Timing.taskTime0) > (&planar_robot3dof_FD0_M)->Timing.taskTime0 *
          (DBL_EPSILON))) {
      rtmSetErrorStatus((&planar_robot3dof_FD0_M), "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  (&planar_robot3dof_FD0_M)->Timing.taskTime0 =
    ((time_T)(++(&planar_robot3dof_FD0_M)->Timing.clockTick0)) *
    (&planar_robot3dof_FD0_M)->Timing.stepSize0;
}

/* Model initialize function */
void planar_robot3dof_FD0::initialize()
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));
  rtmSetTFinal((&planar_robot3dof_FD0_M), 5.0);
  (&planar_robot3dof_FD0_M)->Timing.stepSize0 = 0.001;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = (nullptr);
    (&planar_robot3dof_FD0_M)->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo((&planar_robot3dof_FD0_M)->rtwLogInfo, (nullptr));
    rtliSetLogXSignalPtrs((&planar_robot3dof_FD0_M)->rtwLogInfo, (nullptr));
    rtliSetLogT((&planar_robot3dof_FD0_M)->rtwLogInfo, "");
    rtliSetLogX((&planar_robot3dof_FD0_M)->rtwLogInfo, "");
    rtliSetLogXFinal((&planar_robot3dof_FD0_M)->rtwLogInfo, "");
    rtliSetLogVarNameModifier((&planar_robot3dof_FD0_M)->rtwLogInfo, "rt_");
    rtliSetLogFormat((&planar_robot3dof_FD0_M)->rtwLogInfo, 1);
    rtliSetLogMaxRows((&planar_robot3dof_FD0_M)->rtwLogInfo, 0);
    rtliSetLogDecimation((&planar_robot3dof_FD0_M)->rtwLogInfo, 1);
    rtliSetLogY((&planar_robot3dof_FD0_M)->rtwLogInfo, "");
    rtliSetLogYSignalInfo((&planar_robot3dof_FD0_M)->rtwLogInfo, (nullptr));
    rtliSetLogYSignalPtrs((&planar_robot3dof_FD0_M)->rtwLogInfo, (nullptr));
  }

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime((&planar_robot3dof_FD0_M)->rtwLogInfo, 0.0,
    rtmGetTFinal((&planar_robot3dof_FD0_M)), (&planar_robot3dof_FD0_M)
    ->Timing.stepSize0, (&rtmGetErrorStatus((&planar_robot3dof_FD0_M))));

  /* SystemInitialize for Atomic SubSystem: '<Root>/planar_robot3dof_FD' */
  /* InitializeConditions for DiscreteIntegrator: '<S1>/Discrete-Time Integrator1' */
  planar_robot3dof_FD0_DW.DiscreteTimeIntegrator1_IC_LOAD = 1U;

  /* End of SystemInitialize for SubSystem: '<Root>/planar_robot3dof_FD' */
}

/* Model terminate function */
void planar_robot3dof_FD0::terminate()
{
  /* (no terminate code required) */
}

/* Constructor */
planar_robot3dof_FD0::planar_robot3dof_FD0() :
  planar_robot3dof_FD0_U(),
  planar_robot3dof_FD0_Y(),
  planar_robot3dof_FD0_B(),
  planar_robot3dof_FD0_DW(),
  planar_robot3dof_FD0_M()
{
  /* Currently there is no constructor body generated.*/
}

/* Destructor */
/* Currently there is no destructor body generated.*/
planar_robot3dof_FD0::~planar_robot3dof_FD0() = default;

/* Real-Time Model get method */
RT_MODEL_planar_robot3dof_FD0_T * planar_robot3dof_FD0::getRTM()
{
  return (&planar_robot3dof_FD0_M);
}
