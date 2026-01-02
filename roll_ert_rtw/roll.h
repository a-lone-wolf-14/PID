//
// File: roll.h
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
    real_T TmpRTBAtSubtract1Inport1;   // '<Root>/PID Controller'
    real_T Filter_DSTATE;              // '<S85>/Filter'
    real_T Integrator_DSTATE;          // '<S38>/Integrator'
    real_T TmpRTBAtSubtract1Inport1_Buffer;// synthesized block
  };

  // External inputs (root inport signals with default storage)
  struct ExtU {
    real_T roll_goal;                  // '<Root>/roll_goal'
    real_T roll_h;                     // '<Root>/roll'
    real_T roll_rate;                  // '<Root>/roll_rate'
    real_T heave;                      // '<Root>/heave'
  };

  // External outputs (root outports fed by signals with default storage)
  struct ExtY {
    real_T FL;                         // '<Root>/FL'
    real_T FR;                         // '<Root>/FR'
    real_T BL;                         // '<Root>/BL'
    real_T BR;                         // '<Root>/BR'
  };

  // Real-time Model Data Structure
  struct RT_MODEL {
    //
    //  Timing:
    //  The following substructure contains information regarding
    //  the timing information for the model.

    struct {
      struct {
        uint8_T TID0_1;
      } RateInteraction;
    } Timing;
  };

  // Copy Constructor
  roll(roll const&) = delete;

  // Assignment Operator
  roll& operator= (roll const&) & = delete;

  // Move Constructor
  roll(roll &&) = delete;

  // Move Assignment Operator
  roll& operator= (roll &&) = delete;

  // Real-Time Model get method
  roll::RT_MODEL * getRTM();

  // External inputs
  ExtU rtU;

  // External outputs
  ExtY rtY;

  // model initialize function
  static void initialize();

  // model step function
  void step0();

  // model step function
  void step1();

  // Constructor
  roll();

  // Destructor
  ~roll();

  // private data and function members
 private:
  // Block states
  DW rtDW;

  // Real-Time Model
  RT_MODEL rtM;
};

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
//  '<S1>'   : 'roll/PID Controller'
//  '<S2>'   : 'roll/PID Controller1'
//  '<S3>'   : 'roll/Thruster Allocation'
//  '<S4>'   : 'roll/PID Controller/Anti-windup'
//  '<S5>'   : 'roll/PID Controller/D Gain'
//  '<S6>'   : 'roll/PID Controller/External Derivative'
//  '<S7>'   : 'roll/PID Controller/Filter'
//  '<S8>'   : 'roll/PID Controller/Filter ICs'
//  '<S9>'   : 'roll/PID Controller/I Gain'
//  '<S10>'  : 'roll/PID Controller/Ideal P Gain'
//  '<S11>'  : 'roll/PID Controller/Ideal P Gain Fdbk'
//  '<S12>'  : 'roll/PID Controller/Integrator'
//  '<S13>'  : 'roll/PID Controller/Integrator ICs'
//  '<S14>'  : 'roll/PID Controller/N Copy'
//  '<S15>'  : 'roll/PID Controller/N Gain'
//  '<S16>'  : 'roll/PID Controller/P Copy'
//  '<S17>'  : 'roll/PID Controller/Parallel P Gain'
//  '<S18>'  : 'roll/PID Controller/Reset Signal'
//  '<S19>'  : 'roll/PID Controller/Saturation'
//  '<S20>'  : 'roll/PID Controller/Saturation Fdbk'
//  '<S21>'  : 'roll/PID Controller/Sum'
//  '<S22>'  : 'roll/PID Controller/Sum Fdbk'
//  '<S23>'  : 'roll/PID Controller/Tracking Mode'
//  '<S24>'  : 'roll/PID Controller/Tracking Mode Sum'
//  '<S25>'  : 'roll/PID Controller/Tsamp - Integral'
//  '<S26>'  : 'roll/PID Controller/Tsamp - Ngain'
//  '<S27>'  : 'roll/PID Controller/postSat Signal'
//  '<S28>'  : 'roll/PID Controller/preInt Signal'
//  '<S29>'  : 'roll/PID Controller/preSat Signal'
//  '<S30>'  : 'roll/PID Controller/Anti-windup/Passthrough'
//  '<S31>'  : 'roll/PID Controller/D Gain/Disabled'
//  '<S32>'  : 'roll/PID Controller/External Derivative/Disabled'
//  '<S33>'  : 'roll/PID Controller/Filter/Disabled'
//  '<S34>'  : 'roll/PID Controller/Filter ICs/Disabled'
//  '<S35>'  : 'roll/PID Controller/I Gain/Internal Parameters'
//  '<S36>'  : 'roll/PID Controller/Ideal P Gain/Passthrough'
//  '<S37>'  : 'roll/PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S38>'  : 'roll/PID Controller/Integrator/Discrete'
//  '<S39>'  : 'roll/PID Controller/Integrator ICs/Internal IC'
//  '<S40>'  : 'roll/PID Controller/N Copy/Disabled wSignal Specification'
//  '<S41>'  : 'roll/PID Controller/N Gain/Disabled'
//  '<S42>'  : 'roll/PID Controller/P Copy/Disabled'
//  '<S43>'  : 'roll/PID Controller/Parallel P Gain/Internal Parameters'
//  '<S44>'  : 'roll/PID Controller/Reset Signal/Disabled'
//  '<S45>'  : 'roll/PID Controller/Saturation/Passthrough'
//  '<S46>'  : 'roll/PID Controller/Saturation Fdbk/Disabled'
//  '<S47>'  : 'roll/PID Controller/Sum/Sum_PI'
//  '<S48>'  : 'roll/PID Controller/Sum Fdbk/Disabled'
//  '<S49>'  : 'roll/PID Controller/Tracking Mode/Disabled'
//  '<S50>'  : 'roll/PID Controller/Tracking Mode Sum/Passthrough'
//  '<S51>'  : 'roll/PID Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S52>'  : 'roll/PID Controller/Tsamp - Ngain/Passthrough'
//  '<S53>'  : 'roll/PID Controller/postSat Signal/Forward_Path'
//  '<S54>'  : 'roll/PID Controller/preInt Signal/Internal PreInt'
//  '<S55>'  : 'roll/PID Controller/preSat Signal/Forward_Path'
//  '<S56>'  : 'roll/PID Controller1/Anti-windup'
//  '<S57>'  : 'roll/PID Controller1/D Gain'
//  '<S58>'  : 'roll/PID Controller1/External Derivative'
//  '<S59>'  : 'roll/PID Controller1/Filter'
//  '<S60>'  : 'roll/PID Controller1/Filter ICs'
//  '<S61>'  : 'roll/PID Controller1/I Gain'
//  '<S62>'  : 'roll/PID Controller1/Ideal P Gain'
//  '<S63>'  : 'roll/PID Controller1/Ideal P Gain Fdbk'
//  '<S64>'  : 'roll/PID Controller1/Integrator'
//  '<S65>'  : 'roll/PID Controller1/Integrator ICs'
//  '<S66>'  : 'roll/PID Controller1/N Copy'
//  '<S67>'  : 'roll/PID Controller1/N Gain'
//  '<S68>'  : 'roll/PID Controller1/P Copy'
//  '<S69>'  : 'roll/PID Controller1/Parallel P Gain'
//  '<S70>'  : 'roll/PID Controller1/Reset Signal'
//  '<S71>'  : 'roll/PID Controller1/Saturation'
//  '<S72>'  : 'roll/PID Controller1/Saturation Fdbk'
//  '<S73>'  : 'roll/PID Controller1/Sum'
//  '<S74>'  : 'roll/PID Controller1/Sum Fdbk'
//  '<S75>'  : 'roll/PID Controller1/Tracking Mode'
//  '<S76>'  : 'roll/PID Controller1/Tracking Mode Sum'
//  '<S77>'  : 'roll/PID Controller1/Tsamp - Integral'
//  '<S78>'  : 'roll/PID Controller1/Tsamp - Ngain'
//  '<S79>'  : 'roll/PID Controller1/postSat Signal'
//  '<S80>'  : 'roll/PID Controller1/preInt Signal'
//  '<S81>'  : 'roll/PID Controller1/preSat Signal'
//  '<S82>'  : 'roll/PID Controller1/Anti-windup/Disabled'
//  '<S83>'  : 'roll/PID Controller1/D Gain/Internal Parameters'
//  '<S84>'  : 'roll/PID Controller1/External Derivative/Error'
//  '<S85>'  : 'roll/PID Controller1/Filter/Disc. Forward Euler Filter'
//  '<S86>'  : 'roll/PID Controller1/Filter ICs/Internal IC - Filter'
//  '<S87>'  : 'roll/PID Controller1/I Gain/Disabled'
//  '<S88>'  : 'roll/PID Controller1/Ideal P Gain/Passthrough'
//  '<S89>'  : 'roll/PID Controller1/Ideal P Gain Fdbk/Disabled'
//  '<S90>'  : 'roll/PID Controller1/Integrator/Disabled'
//  '<S91>'  : 'roll/PID Controller1/Integrator ICs/Disabled'
//  '<S92>'  : 'roll/PID Controller1/N Copy/Disabled'
//  '<S93>'  : 'roll/PID Controller1/N Gain/Internal Parameters'
//  '<S94>'  : 'roll/PID Controller1/P Copy/Disabled'
//  '<S95>'  : 'roll/PID Controller1/Parallel P Gain/Internal Parameters'
//  '<S96>'  : 'roll/PID Controller1/Reset Signal/Disabled'
//  '<S97>'  : 'roll/PID Controller1/Saturation/Passthrough'
//  '<S98>'  : 'roll/PID Controller1/Saturation Fdbk/Disabled'
//  '<S99>'  : 'roll/PID Controller1/Sum/Sum_PD'
//  '<S100>' : 'roll/PID Controller1/Sum Fdbk/Disabled'
//  '<S101>' : 'roll/PID Controller1/Tracking Mode/Disabled'
//  '<S102>' : 'roll/PID Controller1/Tracking Mode Sum/Passthrough'
//  '<S103>' : 'roll/PID Controller1/Tsamp - Integral/TsSignalSpecification'
//  '<S104>' : 'roll/PID Controller1/Tsamp - Ngain/Passthrough'
//  '<S105>' : 'roll/PID Controller1/postSat Signal/Forward_Path'
//  '<S106>' : 'roll/PID Controller1/preInt Signal/Internal PreInt'
//  '<S107>' : 'roll/PID Controller1/preSat Signal/Forward_Path'

#endif                                 // roll_h_

//
// File trailer for generated code.
//
// [EOF]
//
