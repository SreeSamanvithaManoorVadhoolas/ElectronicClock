
/*
 * Filename: sp_common.h
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 *
 * Description: 
 */

#ifndef _H_DEFINE_SP_COMMON
#define _H_DEFINE_SP_COMMON

#include "project.h"
#include "global.h"
#include "rte_types.h"

/* USER CODE START SP_COMMON_INCLUDES */

/* USER CODE END SP_COMMON_INCLUDES */



#include "sc_input.h"
#include "sc_control.h"
#include "sc_display.h"



/*
 * description: A Signal for input event
 * indriver: default
 * name: so_input
 * onDataError: 0
 * onDataUpdate: ev_onData
 * outdriver: 0
 * resource: None
 * shortname: input
 * signalclass: sc_input
 * signalpool: sp_common
 */
extern SC_INPUT_t SO_INPUT_signal;


/*
 * description: A Signal
 * indriver: 0
 * name: so_control
 * onDataError: 0
 * onDataUpdate: 0
 * outdriver: 0
 * resource: None
 * shortname: control
 * signalclass: sc_control
 * signalpool: sp_common
 */
extern SC_CONTROL_t SO_CONTROL_signal;


/*
 * description: A Signal
 * indriver: 0
 * name: so_display
 * onDataError: 0
 * onDataUpdate: 0
 * outdriver: default
 * resource: None
 * shortname: display
 * signalclass: sc_display
 * signalpool: sp_common
 */
extern SC_DISPLAY_t SO_DISPLAY_signal;



/*
 * Increments the age of the signals in this pool 
 */
void RTE_timertick_sp_common_tick(uint32_t tick);

/*
 * Reset all signals in this pool
 */
void RTE_reset_sp_common();

#endif