/*
 * aeroelastic_control_updated_2023a.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "aeroelastic_control_updated_2023a".
 *
 * Model version              : 1.7
 * Simulink Coder version : 9.9 (R2023a) 19-Nov-2022
 * C++ source code generated on : Sun Nov 26 17:30:25 2023
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objective: Debugging
 * Validation result: Not run
 */

#include "aeroelastic_control_updated_2023a.h"
#include <cstring>
#include "rtwtypes.h"
#include "aeroelastic_control_updated_2023a_private.h"

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
void aeroelastic_control_updated_2023a::rt_ertODEUpdateContinuousStates
  (RTWSolverInfo *si )
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
  aeroelastic_control_updated_2023a_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  this->step();
  aeroelastic_control_updated_2023a_derivatives();

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
  aeroelastic_control_updated_2023a_derivatives();

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
void aeroelastic_control_updated_2023a::step()
{
  /* local block i/o variables */
  real_T rtb_TSamp;
  real_T tmp;
  int32_T i;
  int32_T i_0;
  if (rtmIsMajorTimeStep((&aeroelastic_control_updated__M))) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&(&aeroelastic_control_updated__M)->solverInfo,
                          (((&aeroelastic_control_updated__M)->Timing.clockTick0
      +1)*(&aeroelastic_control_updated__M)->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep((&aeroelastic_control_updated__M))) {
    (&aeroelastic_control_updated__M)->Timing.t[0] = rtsiGetT
      (&(&aeroelastic_control_updated__M)->solverInfo);
  }

  /* Outputs for Atomic SubSystem: '<Root>/aerofoil' */
  /* SignalConversion generated from: '<S1>/Vector Concatenate' incorporates:
   *  Concatenate: '<S1>/Vector Concatenate'
   *  Integrator: '<S1>/Integrator'
   */
  aeroelastic_control_updated_2_B.VectorConcatenate[0] =
    aeroelastic_control_updated_2_X.Integrator_CSTATE[0];

  /* SignalConversion generated from: '<S1>/Vector Concatenate' incorporates:
   *  Concatenate: '<S1>/Vector Concatenate'
   *  Integrator: '<S1>/Integrator'
   */
  aeroelastic_control_updated_2_B.VectorConcatenate[1] =
    aeroelastic_control_updated_2_X.Integrator_CSTATE[1];

  /* SignalConversion generated from: '<S1>/Vector Concatenate' incorporates:
   *  Concatenate: '<S1>/Vector Concatenate'
   *  Constant: '<Root>/control_input'
   */
  aeroelastic_control_updated_2_B.VectorConcatenate[2] = 5.0;

  /* SignalConversion generated from: '<S1>/Vector Concatenate' incorporates:
   *  Concatenate: '<S1>/Vector Concatenate'
   *  Integrator: '<S1>/Integrator'
   */
  aeroelastic_control_updated_2_B.VectorConcatenate[3] =
    aeroelastic_control_updated_2_X.Integrator_CSTATE[3];
  aeroelastic_control_updated_2_B.VectorConcatenate[4] =
    aeroelastic_control_updated_2_X.Integrator_CSTATE[4];
  if (rtmIsMajorTimeStep((&aeroelastic_control_updated__M))) {
    /* SampleTimeMath: '<S2>/TSamp' incorporates:
     *  Constant: '<Root>/control_input'
     *
     * About '<S2>/TSamp':
     *  y = u * K where K = 1 / ( w * Ts )
     */
    rtb_TSamp = 5000.0;

    /* Sum: '<S2>/Diff' incorporates:
     *  Concatenate: '<S1>/Vector Concatenate'
     *  UnitDelay: '<S2>/UD'
     */
    aeroelastic_control_updated_2_B.VectorConcatenate[5] = 5000.0 -
      aeroelastic_control_updated__DW.UD_DSTATE;
  }

  /* SignalConversion generated from: '<S1>/Vector Concatenate' incorporates:
   *  Concatenate: '<S1>/Vector Concatenate'
   *  Integrator: '<S1>/Integrator'
   */
  for (i = 0; i < 6; i++) {
    aeroelastic_control_updated_2_B.VectorConcatenate[i + 6] =
      aeroelastic_control_updated_2_X.Integrator_CSTATE[i + 6];
  }

  /* End of SignalConversion generated from: '<S1>/Vector Concatenate' */
  for (i = 0; i < 12; i++) {
    /* Sum: '<S1>/Add' incorporates:
     *  Concatenate: '<S1>/Vector Concatenate'
     *  Constant: '<Root>/A'
     *  Product: '<S1>/Matrix Multiply1'
     */
    tmp = 0.0;
    for (i_0 = 0; i_0 < 12; i_0++) {
      tmp += 0.0 * aeroelastic_control_updated_2_B.VectorConcatenate[i_0];
    }

    aeroelastic_control_updated_2_B.Add[i] = tmp;

    /* End of Sum: '<S1>/Add' */
  }

  /* End of Outputs for SubSystem: '<Root>/aerofoil' */

  /* Update for Atomic SubSystem: '<Root>/aerofoil' */
  if (rtmIsMajorTimeStep((&aeroelastic_control_updated__M))) {
    /* Update for UnitDelay: '<S2>/UD' */
    aeroelastic_control_updated__DW.UD_DSTATE = rtb_TSamp;
  }

  /* End of Update for SubSystem: '<Root>/aerofoil' */
  if (rtmIsMajorTimeStep((&aeroelastic_control_updated__M))) {
    rt_ertODEUpdateContinuousStates(&(&aeroelastic_control_updated__M)
      ->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++(&aeroelastic_control_updated__M)->Timing.clockTick0;
    (&aeroelastic_control_updated__M)->Timing.t[0] = rtsiGetSolverStopTime
      (&(&aeroelastic_control_updated__M)->solverInfo);

    {
      /* Update absolute timer for sample time: [0.001s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.001, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      (&aeroelastic_control_updated__M)->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void aeroelastic_control_updated_2023a::
  aeroelastic_control_updated_2023a_derivatives()
{
  XDot_aeroelastic_control_upda_T *_rtXdot;
  _rtXdot = ((XDot_aeroelastic_control_upda_T *)
             (&aeroelastic_control_updated__M)->derivs);

  /* Derivatives for Atomic SubSystem: '<Root>/aerofoil' */
  /* Derivatives for Integrator: '<S1>/Integrator' incorporates:
   *  Sum: '<S1>/Add'
   */
  std::memcpy(&_rtXdot->Integrator_CSTATE[0],
              &aeroelastic_control_updated_2_B.Add[0], 12U * sizeof(real_T));

  /* End of Derivatives for SubSystem: '<Root>/aerofoil' */
}

/* Model initialize function */
void aeroelastic_control_updated_2023a::initialize()
{
  /* Registration code */
  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&(&aeroelastic_control_updated__M)->solverInfo,
                          &(&aeroelastic_control_updated__M)->Timing.simTimeStep);
    rtsiSetTPtr(&(&aeroelastic_control_updated__M)->solverInfo, &rtmGetTPtr
                ((&aeroelastic_control_updated__M)));
    rtsiSetStepSizePtr(&(&aeroelastic_control_updated__M)->solverInfo,
                       &(&aeroelastic_control_updated__M)->Timing.stepSize0);
    rtsiSetdXPtr(&(&aeroelastic_control_updated__M)->solverInfo,
                 &(&aeroelastic_control_updated__M)->derivs);
    rtsiSetContStatesPtr(&(&aeroelastic_control_updated__M)->solverInfo, (real_T
      **) &(&aeroelastic_control_updated__M)->contStates);
    rtsiSetNumContStatesPtr(&(&aeroelastic_control_updated__M)->solverInfo,
      &(&aeroelastic_control_updated__M)->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&(&aeroelastic_control_updated__M)
      ->solverInfo, &(&aeroelastic_control_updated__M)
      ->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&(&aeroelastic_control_updated__M)
      ->solverInfo, &(&aeroelastic_control_updated__M)->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&(&aeroelastic_control_updated__M)
      ->solverInfo, &(&aeroelastic_control_updated__M)->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&(&aeroelastic_control_updated__M)->solverInfo,
                          (&rtmGetErrorStatus((&aeroelastic_control_updated__M))));
    rtsiSetRTModelPtr(&(&aeroelastic_control_updated__M)->solverInfo,
                      (&aeroelastic_control_updated__M));
  }

  rtsiSetSimTimeStep(&(&aeroelastic_control_updated__M)->solverInfo,
                     MAJOR_TIME_STEP);
  (&aeroelastic_control_updated__M)->intgData.y =
    (&aeroelastic_control_updated__M)->odeY;
  (&aeroelastic_control_updated__M)->intgData.f[0] =
    (&aeroelastic_control_updated__M)->odeF[0];
  (&aeroelastic_control_updated__M)->intgData.f[1] =
    (&aeroelastic_control_updated__M)->odeF[1];
  (&aeroelastic_control_updated__M)->intgData.f[2] =
    (&aeroelastic_control_updated__M)->odeF[2];
  (&aeroelastic_control_updated__M)->contStates =
    ((X_aeroelastic_control_updated_T *) &aeroelastic_control_updated_2_X);
  rtsiSetSolverData(&(&aeroelastic_control_updated__M)->solverInfo, static_cast<
                    void *>(&(&aeroelastic_control_updated__M)->intgData));
  rtsiSetIsMinorTimeStepWithModeChange(&(&aeroelastic_control_updated__M)
    ->solverInfo, false);
  rtsiSetSolverName(&(&aeroelastic_control_updated__M)->solverInfo,"ode3");
  rtmSetTPtr((&aeroelastic_control_updated__M),
             &(&aeroelastic_control_updated__M)->Timing.tArray[0]);
  (&aeroelastic_control_updated__M)->Timing.stepSize0 = 0.001;

  /* SystemInitialize for Atomic SubSystem: '<Root>/aerofoil' */
  /* InitializeConditions for Integrator: '<S1>/Integrator' */
  std::memset(&aeroelastic_control_updated_2_X.Integrator_CSTATE[0], 0, 12U *
              sizeof(real_T));

  /* End of SystemInitialize for SubSystem: '<Root>/aerofoil' */
}

/* Model terminate function */
void aeroelastic_control_updated_2023a::terminate()
{
  /* (no terminate code required) */
}

/* Constructor */
aeroelastic_control_updated_2023a::aeroelastic_control_updated_2023a() :
  aeroelastic_control_updated_2_B(),
  aeroelastic_control_updated__DW(),
  aeroelastic_control_updated_2_X(),
  aeroelastic_control_updated__M()
{
  /* Currently there is no constructor body generated.*/
}

/* Destructor */
/* Currently there is no destructor body generated.*/
aeroelastic_control_updated_2023a::~aeroelastic_control_updated_2023a() =
  default;

/* Real-Time Model get method */
RT_MODEL_aeroelastic_control__T * aeroelastic_control_updated_2023a::getRTM()
{
  return (&aeroelastic_control_updated__M);
}
