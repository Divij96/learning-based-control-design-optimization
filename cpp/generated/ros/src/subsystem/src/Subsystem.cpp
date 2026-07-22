/*
 * Subsystem.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Subsystem".
 *
 * Model version              : 1.5
 * Simulink Coder version : 9.9 (R2023a) 19-Nov-2022
 * C++ source code generated on : Fri Nov 24 17:37:46 2023
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objective: Debugging
 * Validation result: Not run
 */

#include "Subsystem.h"
#include "rtwtypes.h"
#include <cstring>
#include "Subsystem_private.h"

extern "C"
{

#include "rt_nonfinite.h"

}

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
void Subsystem::rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
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
  int_T nXc { 12 };

  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) std::memcpy(y, x,
                     static_cast<uint_T>(nXc)*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  Subsystem_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  this->step();
  Subsystem_derivatives();

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
  Subsystem_derivatives();

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

/* Model step function */
void Subsystem::step()
{
  const real_T *tmp_0;
  real_T MatrixMultiply1;
  real_T MatrixMultiply3;
  real_T tmp;
  real_T *tmp_1;
  int32_T i;
  int32_T i_0;
  if (rtmIsMajorTimeStep((&Subsystem_M))) {
    /* set solver stop time */
    if (!((&Subsystem_M)->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&(&Subsystem_M)->solverInfo, (((&Subsystem_M)
        ->Timing.clockTickH0 + 1) * (&Subsystem_M)->Timing.stepSize0 *
        4294967296.0));
    } else {
      rtsiSetSolverStopTime(&(&Subsystem_M)->solverInfo, (((&Subsystem_M)
        ->Timing.clockTick0 + 1) * (&Subsystem_M)->Timing.stepSize0 +
        (&Subsystem_M)->Timing.clockTickH0 * (&Subsystem_M)->Timing.stepSize0 *
        4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep((&Subsystem_M))) {
    (&Subsystem_M)->Timing.t[0] = rtsiGetT(&(&Subsystem_M)->solverInfo);
  }

  /* Outputs for Atomic SubSystem: '<Root>/Subsystem' */
  /* Integrator: '<S1>/Integrator' */
  std::memcpy(&Subsystem_B.Integrator[0], &Subsystem_X.Integrator_CSTATE[0], 12U
              * sizeof(real_T));

  /* SignalConversion generated from: '<S1>/Vector Concatenate' incorporates:
   *  Concatenate: '<S1>/Vector Concatenate'
   */
  Subsystem_B.VectorConcatenate[0] = Subsystem_B.Integrator[0];

  /* SignalConversion generated from: '<S1>/Vector Concatenate' incorporates:
   *  Concatenate: '<S1>/Vector Concatenate'
   */
  Subsystem_B.VectorConcatenate[1] = Subsystem_B.Integrator[1];

  /* SignalConversion generated from: '<S1>/Vector Concatenate' incorporates:
   *  Concatenate: '<S1>/Vector Concatenate'
   *  Inport: '<Root>/In4'
   */
  Subsystem_B.VectorConcatenate[2] = Subsystem_U.In4;

  /* SignalConversion generated from: '<S1>/Vector Concatenate' incorporates:
   *  Concatenate: '<S1>/Vector Concatenate'
   */
  Subsystem_B.VectorConcatenate[3] = Subsystem_B.Integrator[3];
  Subsystem_B.VectorConcatenate[4] = Subsystem_B.Integrator[4];
  if (rtmIsMajorTimeStep((&Subsystem_M))) {
    /* SampleTimeMath: '<S2>/TSamp' incorporates:
     *  Inport: '<Root>/In4'
     *
     * About '<S2>/TSamp':
     *  y = u * K where K = 1 / ( w * Ts )
     */
    Subsystem_B.TSamp = Subsystem_U.In4 * Subsystem_P.TSamp_WtEt;

    /* UnitDelay: '<S2>/UD' */
    Subsystem_B.Uk1 = Subsystem_DW.UD_DSTATE;

    /* Sum: '<S2>/Diff' incorporates:
     *  Concatenate: '<S1>/Vector Concatenate'
     */
    Subsystem_B.VectorConcatenate[5] = Subsystem_B.TSamp - Subsystem_B.Uk1;
  }

  /* SignalConversion generated from: '<S1>/Vector Concatenate' incorporates:
   *  Concatenate: '<S1>/Vector Concatenate'
   */
  for (i = 0; i < 6; i++) {
    Subsystem_B.VectorConcatenate[i + 6] = Subsystem_B.Integrator[i + 6];
  }

  /* End of SignalConversion generated from: '<S1>/Vector Concatenate' */

  /* Product: '<S1>/Matrix Multiply1' incorporates:
   *  Concatenate: '<S1>/Vector Concatenate'
   *  Inport: '<Root>/In1'
   *  Product: '<S1>/Matrix Multiply2'
   *  Product: '<S1>/Matrix Multiply3'
   */
  tmp_0 = &Subsystem_U.In1[0];
  tmp_1 = &Subsystem_B.VectorConcatenate[0];

  /* Product: '<S1>/Matrix Multiply2' */
  tmp = 0.0;
  for (i = 0; i < 12; i++) {
    /* Product: '<S1>/Matrix Multiply1' */
    MatrixMultiply1 = 0.0;
    for (i_0 = 0; i_0 < 12; i_0++) {
      /* Product: '<S1>/Matrix Multiply1' */
      MatrixMultiply1 += tmp_0[12 * i_0 + i] * tmp_1[i_0];
    }

    /* Product: '<S1>/Matrix Multiply1' */
    Subsystem_B.MatrixMultiply1[i] = MatrixMultiply1;

    /* Product: '<S1>/Matrix Multiply3' incorporates:
     *  Inport: '<Root>/In2'
     */
    MatrixMultiply3 = Subsystem_U.In2[i];

    /* Product: '<S1>/Matrix Multiply3' incorporates:
     *  Inport: '<Root>/In4'
     */
    MatrixMultiply3 *= Subsystem_U.In4;
    Subsystem_B.MatrixMultiply3[i] = MatrixMultiply3;

    /* Sum: '<S1>/Add' incorporates:
     *  Product: '<S1>/Matrix Multiply1'
     *  Product: '<S1>/Matrix Multiply3'
     */
    Subsystem_B.Add[i] = MatrixMultiply1 + MatrixMultiply3;

    /* Product: '<S1>/Matrix Multiply2' incorporates:
     *  Inport: '<Root>/In3'
     *  Integrator: '<S1>/Integrator'
     */
    MatrixMultiply3 = Subsystem_U.In3[i];
    MatrixMultiply1 = Subsystem_B.Integrator[i];
    tmp += MatrixMultiply3 * MatrixMultiply1;
  }

  /* Product: '<S1>/Matrix Multiply2' */
  Subsystem_B.MatrixMultiply2 = tmp;

  /* End of Outputs for SubSystem: '<Root>/Subsystem' */

  /* Outport: '<Root>/pitch' */
  Subsystem_Y.pitch = Subsystem_B.Integrator[0];

  /* Outport: '<Root>/plunge' */
  Subsystem_Y.plunge = Subsystem_B.Integrator[1];

  /* Outport: '<Root>/flap' */
  Subsystem_Y.flap = Subsystem_B.Integrator[2];

  /* Outport: '<Root>/C_L' */
  Subsystem_Y.C_L = Subsystem_B.MatrixMultiply2;
  if (rtmIsMajorTimeStep((&Subsystem_M))) {
    /* Matfile logging */
    rt_UpdateTXYLogVars((&Subsystem_M)->rtwLogInfo, ((&Subsystem_M)->Timing.t));
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep((&Subsystem_M))) {
    /* Update for Atomic SubSystem: '<Root>/Subsystem' */
    if (rtmIsMajorTimeStep((&Subsystem_M))) {
      /* Update for UnitDelay: '<S2>/UD' */
      Subsystem_DW.UD_DSTATE = Subsystem_B.TSamp;
    }

    /* End of Update for SubSystem: '<Root>/Subsystem' */
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep((&Subsystem_M))) {
    /* signal main to stop simulation */
    {                                  /* Sample time: [0.0s, 0.0s] */
      if ((rtmGetTFinal((&Subsystem_M))!=-1) &&
          !((rtmGetTFinal((&Subsystem_M))-((((&Subsystem_M)->Timing.clockTick1+(
                &Subsystem_M)->Timing.clockTickH1* 4294967296.0)) * 2.0)) > ((((
               &Subsystem_M)->Timing.clockTick1+(&Subsystem_M)
              ->Timing.clockTickH1* 4294967296.0)) * 2.0) * (DBL_EPSILON))) {
        rtmSetErrorStatus((&Subsystem_M), "Simulation finished");
      }
    }

    rt_ertODEUpdateContinuousStates(&(&Subsystem_M)->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++(&Subsystem_M)->Timing.clockTick0)) {
      ++(&Subsystem_M)->Timing.clockTickH0;
    }

    (&Subsystem_M)->Timing.t[0] = rtsiGetSolverStopTime(&(&Subsystem_M)
      ->solverInfo);

    {
      /* Update absolute timer for sample time: [2.0s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 2.0, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      (&Subsystem_M)->Timing.clockTick1++;
      if (!(&Subsystem_M)->Timing.clockTick1) {
        (&Subsystem_M)->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void Subsystem::Subsystem_derivatives()
{
  XDot_Subsystem_T *_rtXdot;
  _rtXdot = ((XDot_Subsystem_T *) (&Subsystem_M)->derivs);

  /* Derivatives for Atomic SubSystem: '<Root>/Subsystem' */
  /* Derivatives for Integrator: '<S1>/Integrator' incorporates:
   *  Sum: '<S1>/Add'
   */
  std::memcpy(&_rtXdot->Integrator_CSTATE[0], &Subsystem_B.Add[0], 12U * sizeof
              (real_T));

  /* End of Derivatives for SubSystem: '<Root>/Subsystem' */
}

/* Model initialize function */
void Subsystem::initialize()
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&(&Subsystem_M)->solverInfo, &(&Subsystem_M)
                          ->Timing.simTimeStep);
    rtsiSetTPtr(&(&Subsystem_M)->solverInfo, &rtmGetTPtr((&Subsystem_M)));
    rtsiSetStepSizePtr(&(&Subsystem_M)->solverInfo, &(&Subsystem_M)
                       ->Timing.stepSize0);
    rtsiSetdXPtr(&(&Subsystem_M)->solverInfo, &(&Subsystem_M)->derivs);
    rtsiSetContStatesPtr(&(&Subsystem_M)->solverInfo, (real_T **) &(&Subsystem_M)
                         ->contStates);
    rtsiSetNumContStatesPtr(&(&Subsystem_M)->solverInfo, &(&Subsystem_M)
      ->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&(&Subsystem_M)->solverInfo, &(&Subsystem_M
      )->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&(&Subsystem_M)->solverInfo,
      &(&Subsystem_M)->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&(&Subsystem_M)->solverInfo,
      &(&Subsystem_M)->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&(&Subsystem_M)->solverInfo, (&rtmGetErrorStatus
      ((&Subsystem_M))));
    rtsiSetRTModelPtr(&(&Subsystem_M)->solverInfo, (&Subsystem_M));
  }

  rtsiSetSimTimeStep(&(&Subsystem_M)->solverInfo, MAJOR_TIME_STEP);
  (&Subsystem_M)->intgData.y = (&Subsystem_M)->odeY;
  (&Subsystem_M)->intgData.f[0] = (&Subsystem_M)->odeF[0];
  (&Subsystem_M)->intgData.f[1] = (&Subsystem_M)->odeF[1];
  (&Subsystem_M)->intgData.f[2] = (&Subsystem_M)->odeF[2];
  (&Subsystem_M)->contStates = ((X_Subsystem_T *) &Subsystem_X);
  rtsiSetSolverData(&(&Subsystem_M)->solverInfo, static_cast<void *>
                    (&(&Subsystem_M)->intgData));
  rtsiSetIsMinorTimeStepWithModeChange(&(&Subsystem_M)->solverInfo, false);
  rtsiSetSolverName(&(&Subsystem_M)->solverInfo,"ode3");
  rtmSetTPtr((&Subsystem_M), &(&Subsystem_M)->Timing.tArray[0]);
  rtmSetTFinal((&Subsystem_M), 100.0);
  (&Subsystem_M)->Timing.stepSize0 = 2.0;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = (nullptr);
    (&Subsystem_M)->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo((&Subsystem_M)->rtwLogInfo, (nullptr));
    rtliSetLogXSignalPtrs((&Subsystem_M)->rtwLogInfo, (nullptr));
    rtliSetLogT((&Subsystem_M)->rtwLogInfo, "tout");
    rtliSetLogX((&Subsystem_M)->rtwLogInfo, "");
    rtliSetLogXFinal((&Subsystem_M)->rtwLogInfo, "");
    rtliSetLogVarNameModifier((&Subsystem_M)->rtwLogInfo, "rt_");
    rtliSetLogFormat((&Subsystem_M)->rtwLogInfo, 1);
    rtliSetLogMaxRows((&Subsystem_M)->rtwLogInfo, 0);
    rtliSetLogDecimation((&Subsystem_M)->rtwLogInfo, 1);

    /*
     * Set pointers to the data and signal info for each output
     */
    {
      static void * rt_LoggedOutputSignalPtrs[4];
      rt_LoggedOutputSignalPtrs[0] = &Subsystem_Y.pitch;
      rt_LoggedOutputSignalPtrs[1] = &Subsystem_Y.plunge;
      rt_LoggedOutputSignalPtrs[2] = &Subsystem_Y.flap;
      rt_LoggedOutputSignalPtrs[3] = &Subsystem_Y.C_L;
      rtliSetLogYSignalPtrs((&Subsystem_M)->rtwLogInfo, ((LogSignalPtrsType)
        rt_LoggedOutputSignalPtrs));
    }

    {
      static int_T rt_LoggedOutputWidths[] {
        1,
        1,
        1,
        1
      };

      static int_T rt_LoggedOutputNumDimensions[] {
        2,
        2,
        2,
        2
      };

      static int_T rt_LoggedOutputDimensions[] {
        1, 1,
        1, 1,
        1, 1,
        1, 1
      };

      static boolean_T rt_LoggedOutputIsVarDims[] {
        0,
        0,
        0,
        0
      };

      static void* rt_LoggedCurrentSignalDimensions[] {
        (nullptr), (nullptr),
        (nullptr), (nullptr),
        (nullptr), (nullptr),
        (nullptr), (nullptr)
      };

      static int_T rt_LoggedCurrentSignalDimensionsSize[] {
        4, 4,
        4, 4,
        4, 4,
        4, 4
      };

      static BuiltInDTypeId rt_LoggedOutputDataTypeIds[] {
        SS_DOUBLE,
        SS_DOUBLE,
        SS_DOUBLE,
        SS_DOUBLE
      };

      static int_T rt_LoggedOutputComplexSignals[] {
        0,
        0,
        0,
        0
      };

      static RTWPreprocessingFcnPtr rt_LoggingPreprocessingFcnPtrs[] {
        (nullptr),
        (nullptr),
        (nullptr),
        (nullptr)
      };

      static const char_T *rt_LoggedOutputLabels[]{
        "",
        "",
        "",
        "" };

      static const char_T *rt_LoggedOutputBlockNames[]{
        "Subsystem/pitch",
        "Subsystem/plunge",
        "Subsystem/flap",
        "Subsystem/C_L" };

      static RTWLogDataTypeConvert rt_RTWLogDataTypeConvert[] {
        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 },

        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 },

        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 },

        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 }
      };

      static RTWLogSignalInfo rt_LoggedOutputSignalInfo[] {
        {
          4,
          rt_LoggedOutputWidths,
          rt_LoggedOutputNumDimensions,
          rt_LoggedOutputDimensions,
          rt_LoggedOutputIsVarDims,
          rt_LoggedCurrentSignalDimensions,
          rt_LoggedCurrentSignalDimensionsSize,
          rt_LoggedOutputDataTypeIds,
          rt_LoggedOutputComplexSignals,
          (nullptr),
          rt_LoggingPreprocessingFcnPtrs,

          { rt_LoggedOutputLabels },
          (nullptr),
          (nullptr),
          (nullptr),

          { rt_LoggedOutputBlockNames },

          { (nullptr) },
          (nullptr),
          rt_RTWLogDataTypeConvert
        }
      };

      rtliSetLogYSignalInfo((&Subsystem_M)->rtwLogInfo,
                            rt_LoggedOutputSignalInfo);

      /* set currSigDims field */
      rt_LoggedCurrentSignalDimensions[0] = &rt_LoggedOutputWidths[0];
      rt_LoggedCurrentSignalDimensions[1] = &rt_LoggedOutputWidths[0];
      rt_LoggedCurrentSignalDimensions[2] = &rt_LoggedOutputWidths[1];
      rt_LoggedCurrentSignalDimensions[3] = &rt_LoggedOutputWidths[1];
      rt_LoggedCurrentSignalDimensions[4] = &rt_LoggedOutputWidths[2];
      rt_LoggedCurrentSignalDimensions[5] = &rt_LoggedOutputWidths[2];
      rt_LoggedCurrentSignalDimensions[6] = &rt_LoggedOutputWidths[3];
      rt_LoggedCurrentSignalDimensions[7] = &rt_LoggedOutputWidths[3];
    }

    rtliSetLogY((&Subsystem_M)->rtwLogInfo, "yout");
  }

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime((&Subsystem_M)->rtwLogInfo, 0.0, rtmGetTFinal
    ((&Subsystem_M)), (&Subsystem_M)->Timing.stepSize0, (&rtmGetErrorStatus
    ((&Subsystem_M))));

  /* SystemInitialize for Atomic SubSystem: '<Root>/Subsystem' */
  /* InitializeConditions for Integrator: '<S1>/Integrator' */
  for (int32_T i{0}; i < 12; i++) {
    Subsystem_X.Integrator_CSTATE[i] = Subsystem_P.Integrator_IC;
  }

  /* End of InitializeConditions for Integrator: '<S1>/Integrator' */

  /* InitializeConditions for UnitDelay: '<S2>/UD' */
  Subsystem_DW.UD_DSTATE = Subsystem_P.DiscreteDerivative_ICPrevScaled;

  /* End of SystemInitialize for SubSystem: '<Root>/Subsystem' */
}

/* Model terminate function */
void Subsystem::terminate()
{
  /* (no terminate code required) */
}

/* Constructor */
Subsystem::Subsystem() :
  Subsystem_U(),
  Subsystem_Y(),
  Subsystem_B(),
  Subsystem_DW(),
  Subsystem_X(),
  Subsystem_M()
{
  /* Currently there is no constructor body generated.*/
}

/* Destructor */
/* Currently there is no destructor body generated.*/
Subsystem::~Subsystem() = default;

/* Real-Time Model get method */
RT_MODEL_Subsystem_T * Subsystem::getRTM()
{
  return (&Subsystem_M);
}
