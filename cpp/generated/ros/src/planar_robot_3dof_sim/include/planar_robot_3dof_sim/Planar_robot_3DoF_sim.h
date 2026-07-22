/*
 * Planar_robot_3DoF_sim.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Planar_robot_3DoF_sim".
 *
 * Model version              : 12.41
 * Simulink Coder version : 9.9 (R2023a) 19-Nov-2022
 * C++ source code generated on : Thu Nov 23 04:14:45 2023
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objective: Debugging
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Planar_robot_3DoF_sim_h_
#define RTW_HEADER_Planar_robot_3DoF_sim_h_
#include <stdlib.h>
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_logging.h"
#include "Planar_robot_3DoF_sim_types.h"

extern "C"
{

#include "rt_nonfinite.h"

}

extern "C"
{

#include "rtGetInf.h"

}

#include <cfloat>
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

#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
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

#ifndef rtmGetRTWLogInfo
#define rtmGetRTWLogInfo(rtm)          ((rtm)->rtwLogInfo)
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

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

/* Block signals (default storage) */
struct B_Planar_robot_3DoF_sim_T {
  real_T j1_torque;                    /* '<Root>/Sine Wave Function3' */
  real_T j2_torque;                    /* '<Root>/Sine Wave Function1' */
  real_T j3_torque;                    /* '<Root>/Sine Wave Function2' */
  real_T joint_torque[3];
  real_T TmpSignalConversionAtToWorkspac[18];
  real_T q[3];                         /* '<S2>/Integrator1' */
  real_T dq[3];                        /* '<S2>/Integrator' */
  real_T Derivative1[3];               /* '<S2>/Derivative1' */
  real_T Derivative[3];                /* '<S2>/Derivative' */
  real_T Product5[9];                  /* '<S2>/Product5' */
  real_T Product3[3];                  /* '<S2>/Product3' */
  real_T Sum4[3];                      /* '<S2>/Sum4' */
  real_T Product1[3];                  /* '<S2>/Product1' */
  real_T M[9];                         /* '<S2>/calcSysMatrices' */
  real_T CC[9];                        /* '<S2>/calcSysMatrices' */
  real_T g[3];                         /* '<S2>/calcSysMatrices' */
  real_T pos_tcp[3];                   /* '<S2>/calcSysMatrices' */
};

/* Block states (default storage) for system '<Root>' */
struct DW_Planar_robot_3DoF_sim_T {
  real_T TimeStampA;                   /* '<S2>/Derivative1' */
  real_T LastUAtTimeA[3];              /* '<S2>/Derivative1' */
  real_T TimeStampB;                   /* '<S2>/Derivative1' */
  real_T LastUAtTimeB[3];              /* '<S2>/Derivative1' */
  real_T TimeStampA_f;                 /* '<S2>/Derivative' */
  real_T LastUAtTimeA_n[3];            /* '<S2>/Derivative' */
  real_T TimeStampB_b;                 /* '<S2>/Derivative' */
  real_T LastUAtTimeB_j[3];            /* '<S2>/Derivative' */
  real_T Product5_DWORK1[9];           /* '<S2>/Product5' */
  real_T Product5_DWORK3[9];           /* '<S2>/Product5' */
  real_T Product5_DWORK4[9];           /* '<S2>/Product5' */
  struct {
    void *LoggedData;
  } ToWorkspace_PWORK;                 /* '<Root>/To Workspace' */

  struct {
    void *LoggedData;
  } ToWorkspace1_PWORK;                /* '<Root>/To Workspace1' */

  int32_T Product5_DWORK2[3];          /* '<S2>/Product5' */
};

/* Continuous states (default storage) */
struct X_Planar_robot_3DoF_sim_T {
  real_T Integrator1_CSTATE[3];        /* '<S2>/Integrator1' */
  real_T Integrator_CSTATE[3];         /* '<S2>/Integrator' */
};

/* State derivatives (default storage) */
struct XDot_Planar_robot_3DoF_sim_T {
  real_T Integrator1_CSTATE[3];        /* '<S2>/Integrator1' */
  real_T Integrator_CSTATE[3];         /* '<S2>/Integrator' */
};

/* State disabled  */
struct XDis_Planar_robot_3DoF_sim_T {
  boolean_T Integrator1_CSTATE[3];     /* '<S2>/Integrator1' */
  boolean_T Integrator_CSTATE[3];      /* '<S2>/Integrator' */
};

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
struct ODE3_IntgData {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
};

#endif

/* Real-time Model Data Structure */
struct tag_RTM_Planar_robot_3DoF_sim_T {
  const char_T *errorStatus;
  RTWLogInfo *rtwLogInfo;
  RTWSolverInfo solverInfo;
  X_Planar_robot_3DoF_sim_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  XDis_Planar_robot_3DoF_sim_T *contStateDisabled;
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
    time_T tFinal;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Class declaration for model Planar_robot_3DoF_sim */
class Planar_robot_3DoF_sim final
{
  /* public data and function members */
 public:
  /* Copy Constructor */
  Planar_robot_3DoF_sim(Planar_robot_3DoF_sim const&) = delete;

  /* Assignment Operator */
  Planar_robot_3DoF_sim& operator= (Planar_robot_3DoF_sim const&) & = delete;

  /* Move Constructor */
  Planar_robot_3DoF_sim(Planar_robot_3DoF_sim &&) = delete;

  /* Move Assignment Operator */
  Planar_robot_3DoF_sim& operator= (Planar_robot_3DoF_sim &&) = delete;

  /* Real-Time Model get method */
  RT_MODEL_Planar_robot_3DoF_si_T * getRTM();

  /* model start function */
  void start();

  /* Initial conditions function */
  void initialize();

  /* model step function */
  void step();

  /* model terminate function */
  static void terminate();

  /* Constructor */
  Planar_robot_3DoF_sim();

  /* Destructor */
  ~Planar_robot_3DoF_sim();

  /* private data and function members */
 private:
  /* Block signals */
  B_Planar_robot_3DoF_sim_T Planar_robot_3DoF_sim_B;

  /* Block states */
  DW_Planar_robot_3DoF_sim_T Planar_robot_3DoF_sim_DW;

  /* Block continuous states */
  X_Planar_robot_3DoF_sim_T Planar_robot_3DoF_sim_X;

  /* private member function(s) for subsystem '<Root>'*/
  void Planar_robot_3DoF_sim_eye(real_T b_I[9]);
  void Planar_robot_3DoF_sim_diag(const real_T v[3], real_T d[9]);
  void Planar_robot_3DoF_sim_repmat(real_T b[18]);
  boolean_T Planar_robot_3DoF_sim_all(const boolean_T x[3]);
  void Planar_robot_3DoF_sim_mtimes(const real_T A_data[], const int32_T A_size
    [2], const real_T B[16], real_T C_data[], int32_T C_size[2]);
  void Planar_robot_3DoF_sim_mtimes_p(const real_T A[36], const real_T B_data[],
    const int32_T B_size[2], real_T C_data[], int32_T C_size[2]);
  void Planar_rob_binary_expand_op_ccy(real_T in1[18], int32_T in2, const real_T
    in3[36], const real_T in4[18], const real_T in5[9], const real_T in6[6],
    const real_T in7[18]);
  void Planar_robot_3DoF_sim_mtimes_pn(const real_T A_data[], const int32_T
    A_size[2], const real_T B_data[], const int32_T B_size[2], real_T C_data[],
    int32_T C_size[2]);
  void Planar_robot_3DoF_si_mtimes_pnc(const real_T A_data[], const int32_T
    A_size[2], const real_T B_data[], const int32_T B_size[2], real_T C_data[],
    int32_T C_size[2]);
  void Planar_robo_binary_expand_op_cc(real_T in1[9], int32_T in2, const real_T
    in3_data[], const int32_T in3_size[2], const real_T in4[18]);
  void Planar_robot_3DoF_s_mtimes_pnc5(const real_T A_data[], const int32_T
    A_size[2], const real_T B[36], real_T C_data[], int32_T C_size[2]);
  void Planar_robot_binary_expand_op_c(real_T in1[9], int32_T in2, const real_T
    in3[18], real_T in4, const real_T in5[9], const real_T in6[9], const real_T
    in7[9], const real_T in8_data[], const int32_T in8_size[2], const real_T
    in9[18]);
  void Planar_robot_3DoF__mtimes_pnc5a(const real_T A_data[], const int32_T
    A_size[2], const real_T B[9], real_T C_data[], int32_T C_size[2]);
  void Planar_robot_3DoF_mtimes_pnc5ag(const real_T A_data[], const int32_T
    A_size[2], real_T C_data[], int32_T *C_size);
  void Planar_robot_3_binary_expand_op(real_T in1[3], int32_T in2, const real_T
    in3_data[], const int32_T in3_size[2], const real_T in4[16]);

  /* Continuous states update member function*/
  void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si );

  /* Derivatives member function */
  void Planar_robot_3DoF_sim_derivatives();

  /* Real-Time Model */
  RT_MODEL_Planar_robot_3DoF_si_T Planar_robot_3DoF_sim_M;
};

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/joint_torque' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Planar_robot_3DoF_sim'
 * '<S1>'   : 'Planar_robot_3DoF_sim/Subsystem'
 * '<S2>'   : 'Planar_robot_3DoF_sim/Subsystem/planar_robot3dof_FD'
 * '<S3>'   : 'Planar_robot_3DoF_sim/Subsystem/planar_robot3dof_FD/calcSysMatrices'
 */
#endif                                 /* RTW_HEADER_Planar_robot_3DoF_sim_h_ */
