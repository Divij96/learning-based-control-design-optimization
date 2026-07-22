/*
 * planar_robot3dof_FD0.h
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

#ifndef RTW_HEADER_planar_robot3dof_FD0_h_
#define RTW_HEADER_planar_robot3dof_FD0_h_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_logging.h"
#include "planar_robot3dof_FD0_types.h"
#include <cfloat>

extern "C"
{

#include "rt_nonfinite.h"

}

/* Macros for accessing real-time model data structure */
#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetRTWLogInfo
#define rtmGetRTWLogInfo(rtm)          ((rtm)->rtwLogInfo)
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   ((rtm)->Timing.taskTime0)
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                (&(rtm)->Timing.taskTime0)
#endif

/* Block signals (default storage) */
struct B_planar_robot3dof_FD0_T {
  real_T TSamp[3];                     /* '<S2>/TSamp' */
  real_T Uk1[3];                       /* '<S2>/UD' */
  real_T TSamp_m[3];                   /* '<S3>/TSamp' */
  real_T Uk1_c[3];                     /* '<S3>/UD' */
  real_T Product5[9];                  /* '<S1>/Product5' */
  real_T Product3[3];                  /* '<S1>/Product3' */
  real_T Sum4[3];                      /* '<S1>/Sum4' */
  real_T M[9];                         /* '<S1>/calcSysMatrices' */
  real_T CC[9];                        /* '<S1>/calcSysMatrices' */
  real_T g[3];                         /* '<S1>/calcSysMatrices' */
};

/* Block states (default storage) for system '<Root>' */
struct DW_planar_robot3dof_FD0_T {
  real_T DiscreteTimeIntegrator1_DSTATE[3];/* '<S1>/Discrete-Time Integrator1' */
  real_T DiscreteTimeIntegrator_DSTATE[3];/* '<S1>/Discrete-Time Integrator' */
  real_T UD_DSTATE[3];                 /* '<S2>/UD' */
  real_T UD_DSTATE_n[3];               /* '<S3>/UD' */
  real_T Product5_DWORK1[9];           /* '<S1>/Product5' */
  real_T Product5_DWORK3[9];           /* '<S1>/Product5' */
  real_T Product5_DWORK4[9];           /* '<S1>/Product5' */
  int32_T Product5_DWORK2[3];          /* '<S1>/Product5' */
  uint8_T DiscreteTimeIntegrator1_IC_LOAD;/* '<S1>/Discrete-Time Integrator1' */
};

/* External inputs (root inport signals with default storage) */
struct ExtU_planar_robot3dof_FD0_T {
  real_T joint_torque[3];              /* '<Root>/joint_torque' */
  real_T rho;                          /* '<Root>/rho' */
  real_T arm_link_radius;              /* '<Root>/arm_link_radius' */
  real_T arm_length[3];                /* '<Root>/arm_length' */
  real_T init_pos[3];                  /* '<Root>/init_pos' */
};

/* External outputs (root outports fed by signals with default storage) */
struct ExtY_planar_robot3dof_FD0_T {
  real_T joint_pos[3];                 /* '<Root>/joint_pos' */
  real_T joint_vel[3];                 /* '<Root>/joint_vel' */
  real_T joint_acc[3];                 /* '<Root>/joint_acc' */
  real_T TCP_pos[3];                   /* '<Root>/TCP_pos' */
  real_T TCP_vel[3];                   /* '<Root>/TCP_vel' */
  real_T TCP_acc[3];                   /* '<Root>/TCP_acc' */
};

/* Real-time Model Data Structure */
struct tag_RTM_planar_robot3dof_FD0_T {
  const char_T *errorStatus;
  RTWLogInfo *rtwLogInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T taskTime0;
    uint32_T clockTick0;
    time_T stepSize0;
    time_T tFinal;
    boolean_T stopRequestedFlag;
  } Timing;
};

/* Class declaration for model planar_robot3dof_FD0 */
class planar_robot3dof_FD0 final
{
  /* public data and function members */
 public:
  /* Copy Constructor */
  planar_robot3dof_FD0(planar_robot3dof_FD0 const&) = delete;

  /* Assignment Operator */
  planar_robot3dof_FD0& operator= (planar_robot3dof_FD0 const&) & = delete;

  /* Move Constructor */
  planar_robot3dof_FD0(planar_robot3dof_FD0 &&) = delete;

  /* Move Assignment Operator */
  planar_robot3dof_FD0& operator= (planar_robot3dof_FD0 &&) = delete;

  /* Real-Time Model get method */
  RT_MODEL_planar_robot3dof_FD0_T * getRTM();

  /* External inputs */
  ExtU_planar_robot3dof_FD0_T planar_robot3dof_FD0_U;

  /* External outputs */
  ExtY_planar_robot3dof_FD0_T planar_robot3dof_FD0_Y;

  /* Initial conditions function */
  void initialize();

  /* model step function */
  void step();

  /* model terminate function */
  static void terminate();

  /* Constructor */
  planar_robot3dof_FD0();

  /* Destructor */
  ~planar_robot3dof_FD0();

  /* private data and function members */
 private:
  /* Block signals */
  B_planar_robot3dof_FD0_T planar_robot3dof_FD0_B;

  /* Block states */
  DW_planar_robot3dof_FD0_T planar_robot3dof_FD0_DW;

  /* private member function(s) for subsystem '<Root>'*/
  void planar_robot3dof_FD0_eye(real_T b_I[9]);
  void planar_robot3dof_FD0_diag(const real_T v[3], real_T d[9]);
  void planar_robot3dof_FD0_repmat(real_T b[18]);
  boolean_T planar_robot3dof_FD0_all(const boolean_T x[3]);
  void planar_robot3dof_FD0_mtimes(const real_T A_data[], const int32_T A_size[2],
    const real_T B[16], real_T C_data[], int32_T C_size[2]);
  void planar_robot3dof_FD0_mtimes_j(const real_T A[36], const real_T B_data[],
    const int32_T B_size[2], real_T C_data[], int32_T C_size[2]);
  void planar_rob_binary_expand_op_hym(real_T in1[18], int32_T in2, const real_T
    in3[36], const real_T in4[18], const real_T in5[9], const real_T in6[6],
    const real_T in7[18]);
  void planar_robot3dof_FD0_mtimes_jf(const real_T A_data[], const int32_T
    A_size[2], const real_T B_data[], const int32_T B_size[2], real_T C_data[],
    int32_T C_size[2]);
  void planar_robot3dof_FD0_mtimes_jfu(const real_T A_data[], const int32_T
    A_size[2], const real_T B_data[], const int32_T B_size[2], real_T C_data[],
    int32_T C_size[2]);
  void planar_robo_binary_expand_op_hy(real_T in1[9], int32_T in2, const real_T
    in3_data[], const int32_T in3_size[2], const real_T in4[18]);
  void planar_robot3dof_FD_mtimes_jfux(const real_T A_data[], const int32_T
    A_size[2], const real_T B[36], real_T C_data[], int32_T C_size[2]);
  void planar_robot_binary_expand_op_h(real_T in1[9], int32_T in2, const real_T
    in3[18], real_T in4, const real_T in5[9], const real_T in6[9], const real_T
    in7[9], const real_T in8_data[], const int32_T in8_size[2], const real_T
    in9[18]);
  void planar_robot3dof_F_mtimes_jfuxr(const real_T A_data[], const int32_T
    A_size[2], const real_T B[9], real_T C_data[], int32_T C_size[2]);
  void planar_robot3dof__mtimes_jfuxri(const real_T A_data[], const int32_T
    A_size[2], real_T C_data[], int32_T *C_size);
  void planar_robot3d_binary_expand_op(real_T in1[3], int32_T in2, const real_T
    in3_data[], const int32_T in3_size[2], const real_T in4[16]);

  /* Real-Time Model */
  RT_MODEL_planar_robot3dof_FD0_T planar_robot3dof_FD0_M;
};

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S2>/Data Type Duplicate' : Unused code path elimination
 * Block '<S3>/Data Type Duplicate' : Unused code path elimination
 */

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
 * hilite_system('Planar_robot_3DoF_sim/planar_robot3dof_FD')    - opens subsystem Planar_robot_3DoF_sim/planar_robot3dof_FD
 * hilite_system('Planar_robot_3DoF_sim/planar_robot3dof_FD/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Planar_robot_3DoF_sim'
 * '<S1>'   : 'Planar_robot_3DoF_sim/planar_robot3dof_FD'
 * '<S2>'   : 'Planar_robot_3DoF_sim/planar_robot3dof_FD/Discrete Derivative'
 * '<S3>'   : 'Planar_robot_3DoF_sim/planar_robot3dof_FD/Discrete Derivative1'
 * '<S4>'   : 'Planar_robot_3DoF_sim/planar_robot3dof_FD/calcSysMatrices'
 */
#endif                                 /* RTW_HEADER_planar_robot3dof_FD0_h_ */
