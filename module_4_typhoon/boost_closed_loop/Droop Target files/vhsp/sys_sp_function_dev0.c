// generated using template: cop_main.template---------------------------------------------
/******************************************************************************************
**
**  Module Name: cop_main.c
**  NOTE: Automatically generated file. DO NOT MODIFY!
**  Description:
**            Main file
**
******************************************************************************************/
// generated using template: arm/custom_include.template-----------------------------------

// x86 libraries:
#include "../include/sp_functions_dev0.h"

// H files from Advanced C Function components
//#include "example_dll.h"

// Header files from additional sources (Advanced C Function)
// ----------------------------------------------------------------------------------------
// generated using template: VirtualHIL/custom_defines.template----------------------------

typedef unsigned char X_UnInt8;
typedef char X_Int8;
typedef signed short X_Int16;
typedef unsigned short X_UnInt16;
typedef int X_Int32;
typedef unsigned int X_UnInt32;
typedef unsigned int uint;
typedef double real;

// ----------------------------------------------------------------------------------------
// generated using template: custom_consts.template----------------------------------------

// arithmetic constants
#define C_SQRT_2                    1.4142135623730950488016887242097f
#define C_SQRT_3                    1.7320508075688772935274463415059f
#define C_PI                        3.1415926535897932384626433832795f
#define C_E                         2.7182818284590452353602874713527f
#define C_2PI                       6.283185307179586476925286766559f

//@cmp.def.start
//component defines











//@cmp.def.end


//-----------------------------------------------------------------------------------------
// generated using template: common_variables.template-------------------------------------
// true global variables


//@cmp.var.start
// variables
float _vbrms_vinst_va1__out;
float _vbrms_rms_calc_fast__var_eff_s;
X_UnInt32 _vbrms_rms_calc_fast__period;
X_UnInt8 _vbrms_rms_calc_fast__var_zc;
float _vbrms_rms_calc_fast__var_filt_old;
float _vbrms_rms_calc_slow__var_rms;
//@cmp.var.end

//@cmp.svar.start
// state variables
float _vbrms_rt2_output__out =  0.0;

float _vbrms_rt1_output__out =  0.0;

float _vbrms_rms_calc_fast__v_sq_sum_state;
X_UnInt32 _vbrms_rms_calc_fast__pc_cnt_1_state;
float _vbrms_rms_calc_fast__var_filt;
//@cmp.svar.end
// generated using template: virtual_hil/custom_functions.template---------------------------------
void ReInit_sys_sp_cpu_dev0() {
#if DEBUG_MODE
    printf("\n\rReInitTimer");
#endif
    //@cmp.init.block.start
    _vbrms_rt2_output__out =  0.0;
    _vbrms_rt1_output__out =  0.0;
    _vbrms_rms_calc_fast__var_eff_s = 0;
    _vbrms_rms_calc_fast__period = 0;
    _vbrms_rms_calc_fast__var_filt = 0.0f;
    _vbrms_rms_calc_fast__v_sq_sum_state = 0.0f;
    _vbrms_rms_calc_fast__pc_cnt_1_state = 0;
    HIL_OutAO(0x4000, 0.0f);
    //@cmp.init.block.end
}

void ReInit_sp_scope_sys_sp_cpu_dev0() {
    // initialise SP Scope buffer pointer
}
// generated using template: common_timer_counter_handler.template-------------------------

/*****************************************************************************************/
/**
* This function is the handler which performs processing for the timer counter.
* It is called from an interrupt context such that the amount of processing
* performed should be minimized.  It is called when the timer counter expires
* if interrupts are enabled.
*
*
* @param    None
*
* @return   None
*
* @note     None
*
*****************************************************************************************/

void TimerCounterHandler_0_sys_sp_cpu_dev0() {
#if DEBUG_MODE
    printf("\n\rTimerCounterHandler_0");
#endif
    //////////////////////////////////////////////////////////////////////////
    // Output block
    //////////////////////////////////////////////////////////////////////////
    //@cmp.out.block.start
    // Generated from the component: VbRMS.Vinst.Va1
    _vbrms_vinst_va1__out = HIL_InAO(0x207);
    // Generated from the component: VbRMS.sys1
    // Generated from the component: VbRMS.rms_calc_fast
    _vbrms_rms_calc_fast__v_sq_sum_state = _vbrms_rms_calc_fast__v_sq_sum_state + _vbrms_vinst_va1__out * _vbrms_vinst_va1__out;
    _vbrms_rms_calc_fast__var_filt_old = _vbrms_rms_calc_fast__var_filt;
    _vbrms_rms_calc_fast__var_filt = (_vbrms_rms_calc_fast__var_filt_old * 0.909 + _vbrms_vinst_va1__out * 0.0909);
    if((_vbrms_rms_calc_fast__var_filt >= 0.0f) && (_vbrms_rms_calc_fast__var_filt_old < 0.0f)) {
        _vbrms_rms_calc_fast__var_zc = 1;
    }
    else {
        _vbrms_rms_calc_fast__var_zc = 0;
    }
    //square sum and period update on signal zero cross
    if ((_vbrms_rms_calc_fast__var_zc == 1) || (5000 == _vbrms_rms_calc_fast__pc_cnt_1_state)) {
        _vbrms_rms_calc_fast__var_eff_s = _vbrms_rms_calc_fast__v_sq_sum_state;
        _vbrms_rms_calc_fast__period = (float)_vbrms_rms_calc_fast__pc_cnt_1_state;
        _vbrms_rms_calc_fast__v_sq_sum_state = 0.0f;
    }
    // Generated from the component: VbRMS.t1
    // Generated from the component: VbRMS.rt2.Input
    _vbrms_rt2_output__out = _vbrms_rms_calc_fast__period;
    // Generated from the component: VbRMS.rt1.Input
    _vbrms_rt1_output__out = _vbrms_rms_calc_fast__var_eff_s;
    //@cmp.out.block.end
    //////////////////////////////////////////////////////////////////////////
    // Update block
    //////////////////////////////////////////////////////////////////////////
    //@cmp.update.block.start
    // Generated from the component: VbRMS.rms_calc_fast
    if ((_vbrms_rms_calc_fast__var_zc == 1) || (5000 == _vbrms_rms_calc_fast__pc_cnt_1_state)) {
        _vbrms_rms_calc_fast__pc_cnt_1_state = 0;
    }
    _vbrms_rms_calc_fast__pc_cnt_1_state ++;
    //@cmp.update.block.end
}
void TimerCounterHandler_1_sys_sp_cpu_dev0() {
#if DEBUG_MODE
    printf("\n\rTimerCounterHandler_1");
#endif
    //////////////////////////////////////////////////////////////////////////
    // Output block
    //////////////////////////////////////////////////////////////////////////
    //@cmp.out.block.start
    // Generated from the component: VbRMS.rt2.Output
    // Generated from the component: VbRMS.rt1.Output
    // Generated from the component: VbRMS.rms_calc_slow
    if(_vbrms_rt2_output__out > 0.0f) {
        _vbrms_rms_calc_slow__var_rms = sqrtf(_vbrms_rt1_output__out / _vbrms_rt2_output__out);
    }
    else {
        _vbrms_rms_calc_slow__var_rms = 0.0f;
    }
    // Generated from the component: VbRMS.sys2
    // Generated from the component: VbRMS.rms
    HIL_OutAO(0x4000, _vbrms_rms_calc_slow__var_rms);
    //@cmp.out.block.end
    //////////////////////////////////////////////////////////////////////////
    // Update block
    //////////////////////////////////////////////////////////////////////////
    //@cmp.update.block.start
    //@cmp.update.block.end
}
// ----------------------------------------------------------------------------------------  //-----------------------------------------------------------------------------------------