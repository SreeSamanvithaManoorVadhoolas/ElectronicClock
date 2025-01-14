
/*
 * Filename: tsk_control.h
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 *
 * Description: Task for handling the state machine
 */

#ifndef _H_DEFINE_TSK_CONTROL
#define _H_DEFINE_TSK_CONTROL

#include "project.h"
#include "global.h"
#include "rte_types.h"

/* USER CODE START TSK_CONTROL_INCLUDES */

/* USER CODE END TSK_CONTROL_INCLUDES */



/*
 * description: Task for handling the state machine
 * events: ev_button|ev_onData
 * mode: Event
 * name: tsk_control
 * shortname: control
 * signalpoolsRO: sp_common
 * signalpoolsRW: sp_common
 * tickEvent: 0
 * timertickperiod: 0
 */
DeclareTask(tsk_control);

/* USER CODE START TSK_CONTROL_TASKUSERFUNCTION */

/* USER CODE END TSK_CONTROL_TASKUSERFUNCTION */


#endif