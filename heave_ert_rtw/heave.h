//
// File: heave.h
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
#ifndef heave_h_
#define heave_h_
#include <cmath>
#include "rtwtypes.h"

// Class declaration for model heave
class heave final
{
  // public data and function members
 public:
  // Block signals and states (default storage) for system '<Root>'
  struct DW {
    real_T Integrator_DSTATE;          // '<S38>/Integrator'
    real_T Filter_DSTATE;              // '<S33>/Filter'
  };

  // External inputs (root inport signals with default storage)
  struct ExtU {
    real_T depth_goal;                 // '<Root>/depth_goal'
    real_T depth;                      // '<Root>/depth'
  };

  // External outputs (root outports fed by signals with default storage)
  struct ExtY {
    real_T FL;                         // '<Root>/FL'
    real_T FR;                         // '<Root>/FR'
    real_T BL;                         // '<Root>/BL'
    real_T BR;                         // '<Root>/BR'
  };

  // Copy Constructor
  heave(heave const&) = delete;

  // Assignment Operator
  heave& operator= (heave const&) & = delete;

  // Move Constructor
  heave(heave &&) = delete;

  // Move Assignment Operator
  heave& operator= (heave &&) = delete;

  // External inputs
  ExtU rtU;

  // External outputs
  ExtY rtY;

  // model initialize function
  static void initialize();

  // model step function
  void step();

  // model step function
  void step1();

  // Constructor
  heave();

  // Destructor
  ~heave();

  // private data and function members
 private:
  // Block states
  DW rtDW;
};

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S30>/Kb' : Eliminated nontunable gain of 1
//  Block '<S45>/Saturation' : Eliminated Saturate block


//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'heave'
//  '<S1>'   : 'heave/PID'
//  '<S2>'   : 'heave/Thruster Allocation'
//  '<S3>'   : 'heave/PID/PID Controller'
//  '<S4>'   : 'heave/PID/PID Controller/Anti-windup'
//  '<S5>'   : 'heave/PID/PID Controller/D Gain'
//  '<S6>'   : 'heave/PID/PID Controller/External Derivative'
//  '<S7>'   : 'heave/PID/PID Controller/Filter'
//  '<S8>'   : 'heave/PID/PID Controller/Filter ICs'
//  '<S9>'   : 'heave/PID/PID Controller/I Gain'
//  '<S10>'  : 'heave/PID/PID Controller/Ideal P Gain'
//  '<S11>'  : 'heave/PID/PID Controller/Ideal P Gain Fdbk'
//  '<S12>'  : 'heave/PID/PID Controller/Integrator'
//  '<S13>'  : 'heave/PID/PID Controller/Integrator ICs'
//  '<S14>'  : 'heave/PID/PID Controller/N Copy'
//  '<S15>'  : 'heave/PID/PID Controller/N Gain'
//  '<S16>'  : 'heave/PID/PID Controller/P Copy'
//  '<S17>'  : 'heave/PID/PID Controller/Parallel P Gain'
//  '<S18>'  : 'heave/PID/PID Controller/Reset Signal'
//  '<S19>'  : 'heave/PID/PID Controller/Saturation'
//  '<S20>'  : 'heave/PID/PID Controller/Saturation Fdbk'
//  '<S21>'  : 'heave/PID/PID Controller/Sum'
//  '<S22>'  : 'heave/PID/PID Controller/Sum Fdbk'
//  '<S23>'  : 'heave/PID/PID Controller/Tracking Mode'
//  '<S24>'  : 'heave/PID/PID Controller/Tracking Mode Sum'
//  '<S25>'  : 'heave/PID/PID Controller/Tsamp - Integral'
//  '<S26>'  : 'heave/PID/PID Controller/Tsamp - Ngain'
//  '<S27>'  : 'heave/PID/PID Controller/postSat Signal'
//  '<S28>'  : 'heave/PID/PID Controller/preInt Signal'
//  '<S29>'  : 'heave/PID/PID Controller/preSat Signal'
//  '<S30>'  : 'heave/PID/PID Controller/Anti-windup/Back Calculation'
//  '<S31>'  : 'heave/PID/PID Controller/D Gain/Internal Parameters'
//  '<S32>'  : 'heave/PID/PID Controller/External Derivative/Error'
//  '<S33>'  : 'heave/PID/PID Controller/Filter/Disc. Forward Euler Filter'
//  '<S34>'  : 'heave/PID/PID Controller/Filter ICs/Internal IC - Filter'
//  '<S35>'  : 'heave/PID/PID Controller/I Gain/Internal Parameters'
//  '<S36>'  : 'heave/PID/PID Controller/Ideal P Gain/Passthrough'
//  '<S37>'  : 'heave/PID/PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S38>'  : 'heave/PID/PID Controller/Integrator/Discrete'
//  '<S39>'  : 'heave/PID/PID Controller/Integrator ICs/Internal IC'
//  '<S40>'  : 'heave/PID/PID Controller/N Copy/Disabled'
//  '<S41>'  : 'heave/PID/PID Controller/N Gain/Internal Parameters'
//  '<S42>'  : 'heave/PID/PID Controller/P Copy/Disabled'
//  '<S43>'  : 'heave/PID/PID Controller/Parallel P Gain/Internal Parameters'
//  '<S44>'  : 'heave/PID/PID Controller/Reset Signal/Disabled'
//  '<S45>'  : 'heave/PID/PID Controller/Saturation/Enabled'
//  '<S46>'  : 'heave/PID/PID Controller/Saturation Fdbk/Disabled'
//  '<S47>'  : 'heave/PID/PID Controller/Sum/Sum_PID'
//  '<S48>'  : 'heave/PID/PID Controller/Sum Fdbk/Disabled'
//  '<S49>'  : 'heave/PID/PID Controller/Tracking Mode/Disabled'
//  '<S50>'  : 'heave/PID/PID Controller/Tracking Mode Sum/Passthrough'
//  '<S51>'  : 'heave/PID/PID Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S52>'  : 'heave/PID/PID Controller/Tsamp - Ngain/Passthrough'
//  '<S53>'  : 'heave/PID/PID Controller/postSat Signal/Forward_Path'
//  '<S54>'  : 'heave/PID/PID Controller/preInt Signal/Internal PreInt'
//  '<S55>'  : 'heave/PID/PID Controller/preSat Signal/Forward_Path'

#endif                                 // heave_h_

//
// File trailer for generated code.
//
// [EOF]
//
