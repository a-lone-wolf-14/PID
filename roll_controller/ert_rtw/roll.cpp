//
// Sponsored License - for use in support of a program or activity
// sponsored by MathWorks.  Not for government, commercial or other
// non-sponsored organizational use.
//
// File: roll.cpp
//
// Code generated for Simulink model 'roll'.
//
// Model version                  : 1.11
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Sun Apr  5 18:33:48 2026
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
  real_T rtb_Filter;
  real_T rtb_Integrator_k;
  real_T rtb_NProdOut;
  real_T rtb_Saturation;
  real_T rtb_Sum;
  real_T rtb_rate_err;

  // Sum: '<Root>/angle_err' incorporates:
  //   Inport: '<Root>/roll'
  //   Inport: '<Root>/roll_goal'

  rtb_Filter = rtU.roll_goal - rtU.roll_p;

  // Sum: '<S47>/Sum' incorporates:
  //   DiscreteIntegrator: '<S38>/Integrator'
  //   Inport: '<Root>/pi_kp'
  //   Product: '<S43>/PProd Out'

  rtb_Integrator_k = rtb_Filter * rtU.pi_kp + rtDW.Integrator_DSTATE;

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

  // Product: '<S93>/NProd Out' incorporates:
  //   DiscreteIntegrator: '<S85>/Filter'
  //   Inport: '<Root>/pid_kd'
  //   Inport: '<Root>/pid_kn'
  //   Product: '<S83>/DProd Out'
  //   Sum: '<S85>/SumD'

  rtb_NProdOut = (rtb_rate_err * rtU.pid_kd - rtDW.Filter_DSTATE) * rtU.pid_kn;

  // Sum: '<S99>/Sum' incorporates:
  //   DiscreteIntegrator: '<S90>/Integrator'
  //   Inport: '<Root>/pid_kp'
  //   Product: '<S95>/PProd Out'

  rtb_Sum = (rtb_rate_err * rtU.pid_kp + rtDW.Integrator_DSTATE_m) +
    rtb_NProdOut;

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
  //   Inport: '<Root>/pi_ki'
  //   Product: '<S35>/IProd Out'
  //   Sum: '<S30>/SumI4'

  rtDW.Integrator_DSTATE += (rtb_Filter * rtU.pi_ki + rtb_Integrator_k) * 0.01;

  // Update for DiscreteIntegrator: '<S90>/Integrator' incorporates:
  //   Inport: '<Root>/pid_ki'
  //   Product: '<S87>/IProd Out'
  //   Sum: '<S82>/SumI4'

  rtDW.Integrator_DSTATE_m += (rtb_rate_err * rtU.pid_ki + rtb_Sum) * 0.01;

  // Update for DiscreteIntegrator: '<S85>/Filter'
  rtDW.Filter_DSTATE += 0.01 * rtb_NProdOut;
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
