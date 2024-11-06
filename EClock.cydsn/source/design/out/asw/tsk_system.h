
/*
 * Filename: tsk_system.h
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 *
 * Description: System task
 */

#ifndef _H_DEFINE_TSK_SYSTEM
#define _H_DEFINE_TSK_SYSTEM

#include "project.h"
#include "global.h"
#include "rte_types.h"

/* USER CODE START TSK_SYSTEM_INCLUDES */

/* USER CODE END TSK_SYSTEM_INCLUDES */



/*
 * description: System task
 * events: 
 * mode: System
 * name: tsk_system
 * shortname: system
 * signalpoolsRO: sp_common
 * signalpoolsRW: sp_common
 * tickEvent: 0
 * timertickperiod: 1
 */
DeclareTask(tsk_system);

/* USER CODE START TSK_SYSTEM_TASKUSERFUNCTION */

/* USER CODE END TSK_SYSTEM_TASKUSERFUNCTION */


#endif