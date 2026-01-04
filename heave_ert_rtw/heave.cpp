//
// File: heave.cpp
//
// Code generated for Simulink model 'heave'.
//
// Model version                  : 1.1
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Fri Jan  2 02:29:01 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Linux 64)
// Code generation objectives:
//    1. Execution efficiency
//    2. RAM efficiency
// Validation result: Not run
//
#include "heave.h"
#include "rtwtypes.h"

// Model step function for TID0
void heave::step()                     // Sample time: [0.001s, 0.0s]
{
  // (no output/update code required)
}

// Model step function for TID1
void heave::step1()                    // Sample time: [0.01s, 0.0s]
{
  float Kp = 876.859951030588;
  float Ki = 464.069533746115;
  float Kd = 404.881844274437;
  float filter_coeff = 175.900303588767;
  real_T rtb_FilterCoefficient;
  real_T rtb_Gain;
  real_T rtb_Subtract;
  real_T rtb_Sum;

  // Sum: '<Root>/Subtract' incorporates:
  //   Inport: '<Root>/depth'
  //   Inport: '<Root>/depth_goal'

  rtb_Subtract = rtU.depth_goal - rtU.depth;

  // Gain: '<S41>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S33>/Filter'
  //   Gain: '<S31>/Derivative Gain'
  //   Sum: '<S33>/SumD'

  rtb_FilterCoefficient = (Kd * rtb_Subtract - rtDW.Filter_DSTATE)
    * filter_coeff; //Kd

  // Sum: '<S47>/Sum' incorporates:
  //   DiscreteIntegrator: '<S38>/Integrator'
  //   Gain: '<S43>/Proportional Gain'

  rtb_Sum = (Kp * rtb_Subtract + rtDW.Integrator_DSTATE) +
    rtb_FilterCoefficient;  //Kp

  // Saturate: '<Root>/Saturation'
  if (rtb_Sum > 263.8) {
    rtb_Gain = 263.8;
  } else if (rtb_Sum < -197.6) {
    rtb_Gain = -197.6;
  } else {
    rtb_Gain = rtb_Sum;
  }

  // Gain: '<S2>/Gain' incorporates:
  //   Saturate: '<Root>/Saturation'

  rtb_Gain *= 0.25;

  // Outport: '<Root>/FL'
  rtY.FL = rtb_Gain;

  // Outport: '<Root>/FR'
  rtY.FR = rtb_Gain;

  // Outport: '<Root>/BL'
  rtY.BL = rtb_Gain;

  // Outport: '<Root>/BR'
  rtY.BR = rtb_Gain;

  // Update for DiscreteIntegrator: '<S38>/Integrator' incorporates:
  //   Gain: '<S35>/Integral Gain'
  //   Sum: '<S30>/SumI2'
  //   Sum: '<S30>/SumI4'

  rtDW.Integrator_DSTATE += ((rtb_Sum - rtb_Sum) + Ki *
    rtb_Subtract) * 0.01; //Ki

  // Update for DiscreteIntegrator: '<S33>/Filter'
  rtDW.Filter_DSTATE += 0.01 * rtb_FilterCoefficient;
}

// Model initialize function
void heave::initialize()
{
  // (no initialization code required)
}

// Constructor
heave::heave():
  rtU(),
  rtY(),
  rtDW()
{
  // Currently there is no constructor body generated.
}

// Destructor
// Currently there is no destructor body generated.
heave::~heave() = default;

//
// File trailer for generated code.
//
// [EOF]
//
