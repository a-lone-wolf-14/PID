//
// Sponsored License - for use in support of a program or activity
// sponsored by MathWorks.  Not for government, commercial or other
// non-sponsored organizational use.
//
// File: roll.h
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
#ifndef roll_h_
#define roll_h_
#include <cmath>
#include "rtwtypes.h"

// Class declaration for model roll
class roll final
{
  // public data and function members
 public:
  // Block signals and states (default storage) for system '<Root>'
  struct DW {
    real_T Integrator_DSTATE;          // '<S38>/Integrator'
    real_T Integrator_DSTATE_m;        // '<S90>/Integrator'
    real_T Filter_DSTATE;              // '<S85>/Filter'
    real_T PrevY;                      // '<Root>/Rate Limiter'
  };

  // External inputs (root inport signals with default storage)
  struct ExtU {
    real_T roll_goal;                  // '<Root>/roll_goal'
    real_T roll_p;                     // '<Root>/roll'
    real_T omega_x;                    // '<Root>/omega_x'
  };

  // External outputs (root outports fed by signals with default storage)
  struct ExtY {
    real_T fl;                         // '<Root>/fl'
    real_T fr;                         // '<Root>/fr'
    real_T bl;                         // '<Root>/bl'
    real_T br;                         // '<Root>/br'
  };

  // Copy Constructor
  roll(roll const&) = delete;

  // Assignment Operator
  roll& operator= (roll const&) & = delete;

  // Move Constructor
  roll(roll &&) = delete;

  // Move Assignment Operator
  roll& operator= (roll &&) = delete;

  // External inputs
  ExtU rtU;

  // External outputs
  ExtY rtY;

  // model initialize function
  static void initialize();

  // model step function
  void step();

  // Constructor
  roll();

  // Destructor
  ~roll();

  // private data and function members
 private:
  // Block states
  DW rtDW;
};

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S30>/Kb' : Eliminated nontunable gain of 1
//  Block '<S43>/Proportional Gain' : Eliminated nontunable gain of 1
//  Block '<S82>/Kb' : Eliminated nontunable gain of 1


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
//  '<Root>' : 'roll'
//  '<S1>'   : 'roll/PI'
//  '<S2>'   : 'roll/PID Controller'
//  '<S3>'   : 'roll/thruster_alloc'
//  '<S4>'   : 'roll/PI/Anti-windup'
//  '<S5>'   : 'roll/PI/D Gain'
//  '<S6>'   : 'roll/PI/External Derivative'
//  '<S7>'   : 'roll/PI/Filter'
//  '<S8>'   : 'roll/PI/Filter ICs'
//  '<S9>'   : 'roll/PI/I Gain'
//  '<S10>'  : 'roll/PI/Ideal P Gain'
//  '<S11>'  : 'roll/PI/Ideal P Gain Fdbk'
//  '<S12>'  : 'roll/PI/Integrator'
//  '<S13>'  : 'roll/PI/Integrator ICs'
//  '<S14>'  : 'roll/PI/N Copy'
//  '<S15>'  : 'roll/PI/N Gain'
//  '<S16>'  : 'roll/PI/P Copy'
//  '<S17>'  : 'roll/PI/Parallel P Gain'
//  '<S18>'  : 'roll/PI/Reset Signal'
//  '<S19>'  : 'roll/PI/Saturation'
//  '<S20>'  : 'roll/PI/Saturation Fdbk'
//  '<S21>'  : 'roll/PI/Sum'
//  '<S22>'  : 'roll/PI/Sum Fdbk'
//  '<S23>'  : 'roll/PI/Tracking Mode'
//  '<S24>'  : 'roll/PI/Tracking Mode Sum'
//  '<S25>'  : 'roll/PI/Tsamp - Integral'
//  '<S26>'  : 'roll/PI/Tsamp - Ngain'
//  '<S27>'  : 'roll/PI/postSat Signal'
//  '<S28>'  : 'roll/PI/preInt Signal'
//  '<S29>'  : 'roll/PI/preSat Signal'
//  '<S30>'  : 'roll/PI/Anti-windup/Back Calculation'
//  '<S31>'  : 'roll/PI/D Gain/Disabled'
//  '<S32>'  : 'roll/PI/External Derivative/Disabled'
//  '<S33>'  : 'roll/PI/Filter/Disabled'
//  '<S34>'  : 'roll/PI/Filter ICs/Disabled'
//  '<S35>'  : 'roll/PI/I Gain/Internal Parameters'
//  '<S36>'  : 'roll/PI/Ideal P Gain/Passthrough'
//  '<S37>'  : 'roll/PI/Ideal P Gain Fdbk/Disabled'
//  '<S38>'  : 'roll/PI/Integrator/Discrete'
//  '<S39>'  : 'roll/PI/Integrator ICs/Internal IC'
//  '<S40>'  : 'roll/PI/N Copy/Disabled wSignal Specification'
//  '<S41>'  : 'roll/PI/N Gain/Disabled'
//  '<S42>'  : 'roll/PI/P Copy/Disabled'
//  '<S43>'  : 'roll/PI/Parallel P Gain/Internal Parameters'
//  '<S44>'  : 'roll/PI/Reset Signal/Disabled'
//  '<S45>'  : 'roll/PI/Saturation/Enabled'
//  '<S46>'  : 'roll/PI/Saturation Fdbk/Disabled'
//  '<S47>'  : 'roll/PI/Sum/Sum_PI'
//  '<S48>'  : 'roll/PI/Sum Fdbk/Disabled'
//  '<S49>'  : 'roll/PI/Tracking Mode/Disabled'
//  '<S50>'  : 'roll/PI/Tracking Mode Sum/Passthrough'
//  '<S51>'  : 'roll/PI/Tsamp - Integral/TsSignalSpecification'
//  '<S52>'  : 'roll/PI/Tsamp - Ngain/Passthrough'
//  '<S53>'  : 'roll/PI/postSat Signal/Forward_Path'
//  '<S54>'  : 'roll/PI/preInt Signal/Internal PreInt'
//  '<S55>'  : 'roll/PI/preSat Signal/Forward_Path'
//  '<S56>'  : 'roll/PID Controller/Anti-windup'
//  '<S57>'  : 'roll/PID Controller/D Gain'
//  '<S58>'  : 'roll/PID Controller/External Derivative'
//  '<S59>'  : 'roll/PID Controller/Filter'
//  '<S60>'  : 'roll/PID Controller/Filter ICs'
//  '<S61>'  : 'roll/PID Controller/I Gain'
//  '<S62>'  : 'roll/PID Controller/Ideal P Gain'
//  '<S63>'  : 'roll/PID Controller/Ideal P Gain Fdbk'
//  '<S64>'  : 'roll/PID Controller/Integrator'
//  '<S65>'  : 'roll/PID Controller/Integrator ICs'
//  '<S66>'  : 'roll/PID Controller/N Copy'
//  '<S67>'  : 'roll/PID Controller/N Gain'
//  '<S68>'  : 'roll/PID Controller/P Copy'
//  '<S69>'  : 'roll/PID Controller/Parallel P Gain'
//  '<S70>'  : 'roll/PID Controller/Reset Signal'
//  '<S71>'  : 'roll/PID Controller/Saturation'
//  '<S72>'  : 'roll/PID Controller/Saturation Fdbk'
//  '<S73>'  : 'roll/PID Controller/Sum'
//  '<S74>'  : 'roll/PID Controller/Sum Fdbk'
//  '<S75>'  : 'roll/PID Controller/Tracking Mode'
//  '<S76>'  : 'roll/PID Controller/Tracking Mode Sum'
//  '<S77>'  : 'roll/PID Controller/Tsamp - Integral'
//  '<S78>'  : 'roll/PID Controller/Tsamp - Ngain'
//  '<S79>'  : 'roll/PID Controller/postSat Signal'
//  '<S80>'  : 'roll/PID Controller/preInt Signal'
//  '<S81>'  : 'roll/PID Controller/preSat Signal'
//  '<S82>'  : 'roll/PID Controller/Anti-windup/Back Calculation'
//  '<S83>'  : 'roll/PID Controller/D Gain/Internal Parameters'
//  '<S84>'  : 'roll/PID Controller/External Derivative/Error'
//  '<S85>'  : 'roll/PID Controller/Filter/Disc. Forward Euler Filter'
//  '<S86>'  : 'roll/PID Controller/Filter ICs/Internal IC - Filter'
//  '<S87>'  : 'roll/PID Controller/I Gain/Internal Parameters'
//  '<S88>'  : 'roll/PID Controller/Ideal P Gain/Passthrough'
//  '<S89>'  : 'roll/PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S90>'  : 'roll/PID Controller/Integrator/Discrete'
//  '<S91>'  : 'roll/PID Controller/Integrator ICs/Internal IC'
//  '<S92>'  : 'roll/PID Controller/N Copy/Disabled'
//  '<S93>'  : 'roll/PID Controller/N Gain/Internal Parameters'
//  '<S94>'  : 'roll/PID Controller/P Copy/Disabled'
//  '<S95>'  : 'roll/PID Controller/Parallel P Gain/Internal Parameters'
//  '<S96>'  : 'roll/PID Controller/Reset Signal/Disabled'
//  '<S97>'  : 'roll/PID Controller/Saturation/Enabled'
//  '<S98>'  : 'roll/PID Controller/Saturation Fdbk/Disabled'
//  '<S99>'  : 'roll/PID Controller/Sum/Sum_PID'
//  '<S100>' : 'roll/PID Controller/Sum Fdbk/Disabled'
//  '<S101>' : 'roll/PID Controller/Tracking Mode/Disabled'
//  '<S102>' : 'roll/PID Controller/Tracking Mode Sum/Passthrough'
//  '<S103>' : 'roll/PID Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S104>' : 'roll/PID Controller/Tsamp - Ngain/Passthrough'
//  '<S105>' : 'roll/PID Controller/postSat Signal/Forward_Path'
//  '<S106>' : 'roll/PID Controller/preInt Signal/Internal PreInt'
//  '<S107>' : 'roll/PID Controller/preSat Signal/Forward_Path'

#endif                                 // roll_h_

//
// File trailer for generated code.
//
// [EOF]
//
