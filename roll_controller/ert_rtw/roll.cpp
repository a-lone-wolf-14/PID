//
// Sponsored License - for use in support of a program or activity
// sponsored by MathWorks.  Not for government, commercial or other
// non-sponsored organizational use.
//
// File: roll.cpp
//
// Code generated for Simulink model 'roll'.
//
// Model version                  : 1.10
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Sat Apr  4 20:04:06 2026
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

// Model step function
void roll::step()
{
  real_T rateLimiterRate;
  real_T rtb_FilterCoefficient;
  real_T rtb_IntegralGain;
  real_T rtb_Integrator_k;
  real_T rtb_Saturation;
  real_T rtb_Sum;
  real_T rtb_rate_err;

  // Sum: '<Root>/angle_err' incorporates:
  //   Inport: '<Root>/roll'
  //   Inport: '<Root>/roll_goal'

  rtb_Integrator_k = rtU.roll_goal - rtU.roll_p;

  // Gain: '<S35>/Integral Gain'
  rtb_IntegralGain = 0.1 * rtb_Integrator_k;

  // Sum: '<S47>/Sum' incorporates:
  //   DiscreteIntegrator: '<S38>/Integrator'

  rtb_Integrator_k += rtDW.Integrator_DSTATE;

  // Saturate: '<S45>/Saturation'
  if (rtb_Integrator_k > 0.6) {
    rtb_rate_err = 0.6;
  } else if (rtb_Integrator_k < -0.6) {
    rtb_rate_err = -0.6;
  } else {
    rtb_rate_err = rtb_Integrator_k;
  }

  // End of Saturate: '<S45>/Saturation'

  // Sum: '<S30>/SumI2'
  rtb_Integrator_k = rtb_rate_err - rtb_Integrator_k;

  // Sum: '<Root>/rate_err' incorporates:
  //   Inport: '<Root>/omega_x'

  rtb_rate_err -= rtU.omega_x;

  // Gain: '<S93>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S85>/Filter'
  //   Gain: '<S83>/Derivative Gain'
  //   Sum: '<S85>/SumD'

  rtb_FilterCoefficient = (0.411399278827112 * rtb_rate_err - rtDW.Filter_DSTATE)
    * 99.5946650002;

  // Sum: '<S99>/Sum' incorporates:
  //   DiscreteIntegrator: '<S90>/Integrator'
  //   Gain: '<S95>/Proportional Gain'

  rtb_Sum = (11.8622255037614 * rtb_rate_err + rtDW.Integrator_DSTATE_m) +
    rtb_FilterCoefficient;

  // Saturate: '<S97>/Saturation'
  if (rtb_Sum > 12.1) {
    rtb_Saturation = 12.1;
  } else if (rtb_Sum < -12.1) {
    rtb_Saturation = -12.1;
  } else {
    rtb_Saturation = rtb_Sum;
  }

  // End of Saturate: '<S97>/Saturation'

  // Sum: '<S82>/SumI2'
  rtb_Sum = rtb_Saturation - rtb_Sum;

  // RateLimiter: '<Root>/Rate Limiter'
  rateLimiterRate = rtb_Saturation - rtDW.PrevY;
  if (rateLimiterRate > 1.5) {
    rtb_Saturation = rtDW.PrevY + 1.5;
  } else if (rateLimiterRate < -1.5) {
    rtb_Saturation = rtDW.PrevY - 1.5;
  }

  rtDW.PrevY = rtb_Saturation;

  // End of RateLimiter: '<Root>/Rate Limiter'

  // Saturate: '<Root>/Saturation'
  if (rtb_Saturation > 12.1) {
    rtb_Saturation = 12.1;
  } else if (rtb_Saturation < -12.1) {
    rtb_Saturation = -12.1;
  }

  // Gain: '<S3>/Gain2' incorporates:
  //   Saturate: '<Root>/Saturation'

  rtb_Saturation *= 2.8121484814398197;

  // Outport: '<Root>/fl' incorporates:
  //   Gain: '<S3>/Gain1'
  //   Saturate: '<S3>/Saturation'

  rtY.fl = -rtb_Saturation;

  // Outport: '<Root>/fr' incorporates:
  //   Saturate: '<S3>/Saturation'

  rtY.fr = rtb_Saturation;

  // Outport: '<Root>/bl' incorporates:
  //   Gain: '<S3>/Gain1'
  //   Saturate: '<S3>/Saturation'

  rtY.bl = -rtb_Saturation;

  // Outport: '<Root>/br' incorporates:
  //   Saturate: '<S3>/Saturation'

  rtY.br = rtb_Saturation;

  // Update for DiscreteIntegrator: '<S38>/Integrator' incorporates:
  //   Sum: '<S30>/SumI4'

  rtDW.Integrator_DSTATE += (rtb_Integrator_k + rtb_IntegralGain) * 0.01;

  // Update for DiscreteIntegrator: '<S90>/Integrator' incorporates:
  //   Gain: '<S87>/Integral Gain'
  //   Sum: '<S82>/SumI4'

  rtDW.Integrator_DSTATE_m += (58.1740518423554 * rtb_rate_err + rtb_Sum) * 0.01;

  // Update for DiscreteIntegrator: '<S85>/Filter'
  rtDW.Filter_DSTATE += 0.01 * rtb_FilterCoefficient;
}

// Model initialize function
void roll::initialize()
{
  // (no initialization code required)
}

// Constructor
roll::roll():
  rtU(),
  rtY(),
  rtDW()
{
  // Currently there is no constructor body generated.
}

// Destructor
// Currently there is no destructor body generated.
roll::~roll() = default;

//
// File trailer for generated code.
//
// [EOF]
//
