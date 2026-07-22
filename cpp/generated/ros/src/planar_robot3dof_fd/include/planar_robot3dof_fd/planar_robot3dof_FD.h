/*
 * planar_robot3dof_FD.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "planar_robot3dof_FD".
 *
 * Model version              : 12.34
 * Simulink Coder version : 9.9 (R2023a) 19-Nov-2022
 * C++ source code generated on : Wed Nov 22 18:33:49 2023
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_planar_robot3dof_FD_h_
#define RTW_HEADER_planar_robot3dof_FD_h_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "planar_robot3dof_FD_types.h"

extern "C"
{

#include "rt_nonfinite.h"

}

extern "C"
{

#include "rtGetInf.h"

}

#include <cstring>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetContStateDisabled
#define rtmGetContStateDisabled(rtm)   ((rtm)->contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
#define rtmSetContStateDisabled(rtm, val) ((rtm)->contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
#define rtmGetContStates(rtm)          ((rtm)->contStates)
#endif

#ifndef rtmSetContStates
#define rtmSetContStates(rtm, val)     ((rtm)->contStates = (val))
#endif

#ifndef rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm) ((rtm)->CTOutputIncnstWithState)
#endif

#ifndef rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm, val) ((rtm)->CTOutputIncnstWithState = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
#define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
#define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetIntgData
#define rtmGetIntgData(rtm)            ((rtm)->intgData)
#endif

#ifndef rtmSetIntgData
#define rtmSetIntgData(rtm, val)       ((rtm)->intgData = (val))
#endif

#ifndef rtmGetOdeF
#define rtmGetOdeF(rtm)                ((rtm)->odeF)
#endif

#ifndef rtmSetOdeF
#define rtmSetOdeF(rtm, val)           ((rtm)->odeF = (val))
#endif

#ifndef rtmGetOdeY
#define rtmGetOdeY(rtm)                ((rtm)->odeY)
#endif

#ifndef rtmSetOdeY
#define rtmSetOdeY(rtm, val)           ((rtm)->odeY = (val))
#endif

#ifndef rtmGetPeriodicContStateIndices
#define rtmGetPeriodicContStateIndices(rtm) ((rtm)->periodicContStateIndices)
#endif

#ifndef rtmSetPeriodicContStateIndices
#define rtmSetPeriodicContStateIndices(rtm, val) ((rtm)->periodicContStateIndices = (val))
#endif

#ifndef rtmGetPeriodicContStateRanges
#define rtmGetPeriodicContStateRanges(rtm) ((rtm)->periodicContStateRanges)
#endif

#ifndef rtmSetPeriodicContStateRanges
#define rtmSetPeriodicContStateRanges(rtm, val) ((rtm)->periodicContStateRanges = (val))
#endif

#ifndef rtmGetZCCacheNeedsReset
#define rtmGetZCCacheNeedsReset(rtm)   ((rtm)->zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
#define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetdX
#define rtmGetdX(rtm)                  ((rtm)->derivs)
#endif

#ifndef rtmSetdX
#define rtmSetdX(rtm, val)             ((rtm)->derivs = (val))
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
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

/* Block signals (default storage) */
struct B_planar_robot3dof_FD_T {
  real_T dq[3];                        /* '<S1>/joint_vel_int' */
  real_T Derivative_pos_tcp[3];        /* '<S1>/Derivative_pos_tcp' */
  real_T Product1[3];                  /* '<S1>/Product1' */
  real_T pos_tcp[3];                   /* '<S1>/calcSysMatrices' */
};

/* Block states (default storage) for system '<Root>' */
struct DW_planar_robot3dof_FD_T {
  real_T TimeStampA;                   /* '<S1>/Derivative_pos_tcp' */
  real_T LastUAtTimeA[3];              /* '<S1>/Derivative_pos_tcp' */
  real_T TimeStampB;                   /* '<S1>/Derivative_pos_tcp' */
  real_T LastUAtTimeB[3];              /* '<S1>/Derivative_pos_tcp' */
  real_T TimeStampA_j;                 /* '<S1>/Derivative_vel_tcp' */
  real_T LastUAtTimeA_k[3];            /* '<S1>/Derivative_vel_tcp' */
  real_T TimeStampB_n;                 /* '<S1>/Derivative_vel_tcp' */
  real_T LastUAtTimeB_f[3];            /* '<S1>/Derivative_vel_tcp' */
  real_T Product5_DWORK4[9];           /* '<S1>/Product5' */
  int_T joint_pos_int_IWORK;           /* '<S1>/joint_pos_int' */
};

/* Continuous states (default storage) */
struct X_planar_robot3dof_FD_T {
  real_T joint_pos_int_CSTATE[3];      /* '<S1>/joint_pos_int' */
  real_T joint_vel_int_CSTATE[3];      /* '<S1>/joint_vel_int' */
};

/* State derivatives (default storage) */
struct XDot_planar_robot3dof_FD_T {
  real_T joint_pos_int_CSTATE[3];      /* '<S1>/joint_pos_int' */
  real_T joint_vel_int_CSTATE[3];      /* '<S1>/joint_vel_int' */
};

/* State disabled  */
struct XDis_planar_robot3dof_FD_T {
  boolean_T joint_pos_int_CSTATE[3];   /* '<S1>/joint_pos_int' */
  boolean_T joint_vel_int_CSTATE[3];   /* '<S1>/joint_vel_int' */
};

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
struct ODE3_IntgData {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
};

#endif

/* External inputs (root inport signals with default storage) */
struct ExtU_planar_robot3dof_FD_T {
  real_T joint_torque[3];              /* '<Root>/joint_torque' */
  real_T rho;                          /* '<Root>/rho' */
  real_T arm_link_radius;              /* '<Root>/arm_link_radius' */
  real_T arm_length[3];                /* '<Root>/arm_length' */
  real_T init_pos[3];                  /* '<Root>/init_pos' */
};

/* External outputs (root outports fed by signals with default storage) */
struct ExtY_planar_robot3dof_FD_T {
  real_T joint_pos[3];                 /* '<Root>/joint_pos' */
  real_T joint_vel[3];                 /* '<Root>/joint_vel' */
  real_T joint_acc[3];                 /* '<Root>/joint_acc' */
  real_T TCP_pos[3];                   /* '<Root>/TCP_pos' */
  real_T TCP_vel[3];                   /* '<Root>/TCP_vel' */
  real_T TCP_acc[3];                   /* '<Root>/TCP_acc' */
};

/* Real-time Model Data Structure */
struct tag_RTM_planar_robot3dof_FD_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_planar_robot3dof_FD_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  XDis_planar_robot3dof_FD_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[6];
  real_T odeF[3][6];
  ODE3_IntgData intgData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    boolean_T firstInitCondFlag;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Class declaration for model planar_robot3dof_FD */
class planar_robot3dof_FD final
{
  /* public data and function members */
 public:
  /* Copy Constructor */
  planar_robot3dof_FD(planar_robot3dof_FD const&) = delete;

  /* Assignment Operator */
  planar_robot3dof_FD& operator= (planar_robot3dof_FD const&) & = delete;

  /* Move Constructor */
  planar_robot3dof_FD(planar_robot3dof_FD &&) = delete;

  /* Move Assignment Operator */
  planar_robot3dof_FD& operator= (planar_robot3dof_FD &&) = delete;

  /* Real-Time Model get method */
  RT_MODEL_planar_robot3dof_FD_T * getRTM();

  /* External inputs */
  ExtU_planar_robot3dof_FD_T planar_robot3dof_FD_U;

  /* External outputs */
  ExtY_planar_robot3dof_FD_T planar_robot3dof_FD_Y;

  /* Initial conditions function */
  void initialize();

  /* model step function */
  void step();

  /* model terminate function */
  static void terminate();

  /* Constructor */
  planar_robot3dof_FD();

  /* Destructor */
  ~planar_robot3dof_FD();

  /* private data and function members */
 private:
  /* Block signals */
  B_planar_robot3dof_FD_T planar_robot3dof_FD_B;

  /* Block states */
  DW_planar_robot3dof_FD_T planar_robot3dof_FD_DW;

  /* Block continuous states */
  X_planar_robot3dof_FD_T planar_robot3dof_FD_X;

  /* private member function(s) for subsystem '<Root>'*/
  void planar_robot3dof_FD_eye(real_T b_I[9]);
  void planar_robot3dof_FD_diag(const real_T v[3], real_T d[9]);
  void planar_robot3dof_FD_repmat(real_T b[18]);
  boolean_T planar_robot3dof_FD_all(const boolean_T x[3]);
  void planar_robot3dof_FD_mtimes(const real_T A_data[], const int32_T A_size[2],
    const real_T B[16], real_T C_data[], int32_T C_size[2]);
  void planar_robot3dof_FD_mtimes_d(const real_T A[36], const real_T B_data[],
    const int32_T B_size[2], real_T C_data[], int32_T C_size[2]);
  void planar_rob_binary_expand_op_ozv(real_T in1[18], int32_T in2, const real_T
    in3[36], const real_T in4[18], const real_T in5[9], const real_T in6[6],
    const real_T in7[18]);
  void planar_robot3dof_FD_mtimes_dg(const real_T A_data[], const int32_T
    A_size[2], const real_T B_data[], const int32_T B_size[2], real_T C_data[],
    int32_T C_size[2]);
  void planar_robot3dof_FD_mtimes_dgo(const real_T A_data[], const int32_T
    A_size[2], const real_T B_data[], const int32_T B_size[2], real_T C_data[],
    int32_T C_size[2]);
  void planar_robo_binary_expand_op_oz(real_T in1[9], int32_T in2, const real_T
    in3_data[], const int32_T in3_size[2], const real_T in4[18]);
  void planar_robot3dof_FD_mtimes_dgo5(const real_T A_data[], const int32_T
    A_size[2], const real_T B[36], real_T C_data[], int32_T C_size[2]);
  void planar_robot_binary_expand_op_o(real_T in1[9], int32_T in2, const real_T
    in3[18], real_T in4, const real_T in5[9], const real_T in6[9], const real_T
    in7[9], const real_T in8_data[], const int32_T in8_size[2], const real_T
    in9[18]);
  void planar_robot3dof_F_mtimes_dgo5v(const real_T A_data[], const int32_T
    A_size[2], const real_T B[9], real_T C_data[], int32_T C_size[2]);
  void planar_robot3dof__mtimes_dgo5ve(const real_T A_data[], const int32_T
    A_size[2], real_T C_data[], int32_T *C_size);
  void planar_robot3d_binary_expand_op(real_T in1[3], int32_T in2, const real_T
    in3_data[], const int32_T in3_size[2], const real_T in4[16]);

  /* Continuous states update member function*/
  void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si );

  /* Derivatives member function */
  void planar_robot3dof_FD_derivatives();

  /* Real-Time Model */
  RT_MODEL_planar_robot3dof_FD_T planar_robot3dof_FD_M;
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
 * hilite_system('Planar_robot_3DoF_sim/planar_robot3dof_FD')    - opens subsystem Planar_robot_3DoF_sim/planar_robot3dof_FD
 * hilite_system('Planar_robot_3DoF_sim/planar_robot3dof_FD/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Planar_robot_3DoF_sim'
 * '<S1>'   : 'Planar_robot_3DoF_sim/planar_robot3dof_FD'
 * '<S2>'   : 'Planar_robot_3DoF_sim/planar_robot3dof_FD/calcSysMatrices'
 */
#endif                                 /* RTW_HEADER_planar_robot3dof_FD_h_ */
