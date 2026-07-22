/*
 * custom_scara_fd.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "custom_scara_fd".
 *
 * Model version              : 12.44
 * Simulink Coder version : 9.9 (R2023a) 19-Nov-2022
 * C++ source code generated on : Thu Nov 23 05:14:10 2023
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objective: Debugging
 * Validation result: Not run
 */

#ifndef RTW_HEADER_custom_scara_fd_h_
#define RTW_HEADER_custom_scara_fd_h_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "custom_scara_fd_types.h"

extern "C"
{

#include "rt_nonfinite.h"

}

extern "C"
{

#include "rtGetInf.h"

}

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

/* Block signals (default storage) */
struct B_custom_scara_fd_T {
  real_T Derivative1[3];               /* '<S1>/Derivative1' */
};

/* Block states (default storage) for system '<Root>' */
struct DW_custom_scara_fd_T {
  real_T TimeStampA;                   /* '<S1>/Derivative1' */
  real_T LastUAtTimeA[3];              /* '<S1>/Derivative1' */
  real_T TimeStampB;                   /* '<S1>/Derivative1' */
  real_T LastUAtTimeB[3];              /* '<S1>/Derivative1' */
  real_T TimeStampA_b;                 /* '<S1>/Derivative' */
  real_T LastUAtTimeA_d[3];            /* '<S1>/Derivative' */
  real_T TimeStampB_g;                 /* '<S1>/Derivative' */
  real_T LastUAtTimeB_p[3];            /* '<S1>/Derivative' */
  real_T Product5_DWORK4[9];           /* '<S1>/Product5' */
};

/* External inputs (root inport signals with default storage) */
struct ExtU_custom_scara_fd_T {
  real_T joint_torque[3];              /* '<Root>/joint_torque' */
  real_T rho;                          /* '<Root>/rho' */
  real_T arm_link_radius;              /* '<Root>/arm_link_radius' */
  real_T arm_length[3];                /* '<Root>/arm_length' */
  real_T joint_pos[3];                 /* '<Root>/q' */
  real_T joint_vel[3];                 /* '<Root>/dq' */
};

/* External outputs (root outports fed by signals with default storage) */
struct ExtY_custom_scara_fd_T {
  real_T joint_acc[3];                 /* '<Root>/joint_acc' */
  real_T TCP_pos[3];                   /* '<Root>/TCP_pos' */
  real_T TCP_vel[3];                   /* '<Root>/TCP_vel' */
  real_T TCP_acc[3];                   /* '<Root>/TCP_acc' */
};

/* Real-time Model Data Structure */
struct tag_RTM_custom_scara_fd_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    SimTimeStep simTimeStep;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Class declaration for model custom_scara_fd */
class custom_scara_fd final
{
  /* public data and function members */
 public:
  /* Copy Constructor */
  custom_scara_fd(custom_scara_fd const&) = delete;

  /* Assignment Operator */
  custom_scara_fd& operator= (custom_scara_fd const&) & = delete;

  /* Move Constructor */
  custom_scara_fd(custom_scara_fd &&) = delete;

  /* Move Assignment Operator */
  custom_scara_fd& operator= (custom_scara_fd &&) = delete;

  /* Real-Time Model get method */
  RT_MODEL_custom_scara_fd_T * getRTM();

  /* External inputs */
  ExtU_custom_scara_fd_T custom_scara_fd_U;

  /* External outputs */
  ExtY_custom_scara_fd_T custom_scara_fd_Y;

  /* Initial conditions function */
  void initialize();

  /* model step function */
  void step();

  /* model terminate function */
  static void terminate();

  /* Constructor */
  custom_scara_fd();

  /* Destructor */
  ~custom_scara_fd();

  /* private data and function members */
 private:
  /* Block signals */
  B_custom_scara_fd_T custom_scara_fd_B;

  /* Block states */
  DW_custom_scara_fd_T custom_scara_fd_DW;

  /* private member function(s) for subsystem '<Root>'*/
  void custom_scara_fd_eye(real_T b_I[9]);
  void custom_scara_fd_diag(const real_T v[3], real_T d[9]);
  void custom_scara_fd_repmat(real_T b[18]);
  boolean_T custom_scara_fd_all(const boolean_T x[3]);
  void custom_scara_fd_mtimes(const real_T A_data[], const int32_T A_size[2],
    const real_T B[16], real_T C_data[], int32_T C_size[2]);
  void custom_scara_fd_mtimes_m(const real_T A[36], const real_T B_data[], const
    int32_T B_size[2], real_T C_data[], int32_T C_size[2]);
  void custom_sca_binary_expand_op_ih2(real_T in1[18], int32_T in2, const real_T
    in3[36], const real_T in4[18], const real_T in5[9], const real_T in6[6],
    const real_T in7[18]);
  void custom_scara_fd_mtimes_mn(const real_T A_data[], const int32_T A_size[2],
    const real_T B_data[], const int32_T B_size[2], real_T C_data[], int32_T
    C_size[2]);
  void custom_scara_fd_mtimes_mni(const real_T A_data[], const int32_T A_size[2],
    const real_T B_data[], const int32_T B_size[2], real_T C_data[], int32_T
    C_size[2]);
  void custom_scar_binary_expand_op_ih(real_T in1[9], int32_T in2, const real_T
    in3_data[], const int32_T in3_size[2], const real_T in4[18]);
  void custom_scara_fd_mtimes_mnik(const real_T A_data[], const int32_T A_size[2],
    const real_T B[36], real_T C_data[], int32_T C_size[2]);
  void custom_scara_binary_expand_op_i(real_T in1[9], int32_T in2, const real_T
    in3[18], real_T in4, const real_T in5[9], const real_T in6[9], const real_T
    in7[9], const real_T in8_data[], const int32_T in8_size[2], const real_T
    in9[18]);
  void custom_scara_fd_mtimes_mnik3(const real_T A_data[], const int32_T A_size
    [2], const real_T B[9], real_T C_data[], int32_T C_size[2]);
  void custom_scara_fd_mtimes_mnik3n(const real_T A_data[], const int32_T
    A_size[2], real_T C_data[], int32_T *C_size);
  void custom_scara_f_binary_expand_op(real_T in1[3], int32_T in2, const real_T
    in3_data[], const int32_T in3_size[2], const real_T in4[16]);

  /* Real-Time Model */
  RT_MODEL_custom_scara_fd_T custom_scara_fd_M;
};

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('custom_forward_dynamics/custom_scara_fd')    - opens subsystem custom_forward_dynamics/custom_scara_fd
 * hilite_system('custom_forward_dynamics/custom_scara_fd/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'custom_forward_dynamics'
 * '<S1>'   : 'custom_forward_dynamics/custom_scara_fd'
 * '<S2>'   : 'custom_forward_dynamics/custom_scara_fd/calcSysMatrices'
 */
#endif                                 /* RTW_HEADER_custom_scara_fd_h_ */
