//
// File: roll.cpp
//
// Code generated for Simulink model 'roll'.
//
// Model version                  : 1.3
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Fri Jan  2 09:15:50 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Linux 64)
// Code generation objectives:
//    1. Execution efficiency
//    2. RAM efficiency
// Validation result: Not run
//
#include "roll.h"
#include "rtwtypes.h"

// Model step function for TID0
void roll::step0()                     // Sample time: [0.001s, 0.0s]
{
  real_T rtb_BR_;
  real_T rtb_FilterCoefficient;
  real_T u0;

  // Update the flag to indicate when data transfers from
  //   Sample time: [0.001s, 0.0s] to Sample time: [0.01s, 0.0s]
  ((&rtM)->Timing.RateInteraction.TID0_1)++;
  if (((&rtM)->Timing.RateInteraction.TID0_1) > 9) {
    (&rtM)->Timing.RateInteraction.TID0_1 = 0;
  }

  // RateTransition generated from: '<Root>/Subtract1'
  if ((&rtM)->Timing.RateInteraction.TID0_1 == 1) {
    // RateTransition generated from: '<Root>/Subtract1'
    rtDW.TmpRTBAtSubtract1Inport1 = rtDW.TmpRTBAtSubtract1Inport1_Buffer;
  }

  // End of RateTransition generated from: '<Root>/Subtract1'

  // Sum: '<Root>/Subtract1' incorporates:
  //   Inport: '<Root>/roll_rate'

  rtb_BR_ = rtDW.TmpRTBAtSubtract1Inport1 - rtU.roll_rate;

  // Gain: '<S93>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S85>/Filter'
  //   Gain: '<S83>/Derivative Gain'
  //   Sum: '<S85>/SumD'

  rtb_FilterCoefficient = (0.08 * rtb_BR_ - rtDW.Filter_DSTATE) * 100.0;

  // Sum: '<S99>/Sum' incorporates:
  //   Gain: '<S95>/Proportional Gain'

  u0 = 1.5 * rtb_BR_ + rtb_FilterCoefficient;

  // Saturate: '<Root>/Saturation'
  if (u0 > 34.605) {
    u0 = 34.605;
  } else if (u0 < -34.605) {
    u0 = -34.605;
  }

  // Gain: '<S3>/1//l' incorporates:
  //   Saturate: '<Root>/Saturation'

  rtb_BR_ = 6.666666666666667 * u0;

  // Sum: '<S3>/FL_' incorporates:
  //   Inport: '<Root>/heave'

  u0 = rtU.heave + rtb_BR_;

  // Saturate: '<S3>/Saturation'
  if (u0 > 65.95) {
    // Outport: '<Root>/FL'
    rtY.FL = 65.95;
  } else if (u0 < -49.4) {
    // Outport: '<Root>/FL'
    rtY.FL = -49.4;
  } else {
    // Outport: '<Root>/FL'
    rtY.FL = u0;
  }

  // End of Saturate: '<S3>/Saturation'

  // Sum: '<S3>/FR_' incorporates:
  //   Inport: '<Root>/heave'

  rtb_BR_ = rtU.heave - rtb_BR_;

  // Saturate: '<S3>/Saturation1'
  if (rtb_BR_ > 65.95) {
    // Outport: '<Root>/FR'
    rtY.FR = 65.95;
  } else if (rtb_BR_ < -49.4) {
    // Outport: '<Root>/FR'
    rtY.FR = -49.4;
  } else {
    // Outport: '<Root>/FR'
    rtY.FR = rtb_BR_;
  }

  // End of Saturate: '<S3>/Saturation1'

  // Saturate: '<S3>/Saturation2' incorporates:
  //   Sum: '<S3>/BL_ '

  if (u0 > 65.95) {
    // Outport: '<Root>/BL'
    rtY.BL = 65.95;
  } else if (u0 < -49.4) {
    // Outport: '<Root>/BL'
    rtY.BL = -49.4;
  } else {
    // Outport: '<Root>/BL'
    rtY.BL = u0;
  }

  // End of Saturate: '<S3>/Saturation2'

  // Saturate: '<S3>/Saturation3' incorporates:
  //   Sum: '<S3>/BR_'

  if (rtb_BR_ > 65.95) {
    // Outport: '<Root>/BR'
    rtY.BR = 65.95;
  } else if (rtb_BR_ < -49.4) {
    // Outport: '<Root>/BR'
    rtY.BR = -49.4;
  } else {
    // Outport: '<Root>/BR'
    rtY.BR = rtb_BR_;
  }

  // End of Saturate: '<S3>/Saturation3'

  // Update for DiscreteIntegrator: '<S85>/Filter'
  rtDW.Filter_DSTATE += 0.001 * rtb_FilterCoefficient;
}

// Model step function for TID1
void roll::step1()                     // Sample time: [0.01s, 0.0s]
{
  real_T rtb_Integrator;
  real_T rtb_Sum;

  // Sum: '<Root>/Subtract' incorporates:
  //   Inport: '<Root>/roll'
  //   Inport: '<Root>/roll_goal'

  rtb_Integrator = rtU.roll_goal - rtU.roll_h;

  // Sum: '<S47>/Sum' incorporates:
  //   DiscreteIntegrator: '<S38>/Integrator'
  //   Gain: '<S43>/Proportional Gain'

  rtb_Sum = 3.0 * rtb_Integrator + rtDW.Integrator_DSTATE;

  // RateTransition generated from: '<Root>/Subtract1'
  rtDW.TmpRTBAtSubtract1Inport1_Buffer = rtb_Sum;

  // Update for DiscreteIntegrator: '<S38>/Integrator' incorporates:
  //   Gain: '<S35>/Integral Gain'

  rtDW.Integrator_DSTATE += 4.0 * rtb_Integrator * 0.01;
}

// Model initialize function
void roll::initialize()
{
  // (no initialization code required)
}

// Constructor
roll::roll() :
  rtU(),
  rtY(),
  rtDW(),
  rtM()
{
  // Currently there is no constructor body generated.
}

// Destructor
// Currently there is no destructor body generated.
roll::~roll() = default;

// Real-Time Model get method
roll::RT_MODEL * roll::getRTM()
{
  return (&rtM);
}

//
// File trailer for generated code.
//
// [EOF]
//
