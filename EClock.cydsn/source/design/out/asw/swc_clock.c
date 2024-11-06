/*
 * Filename: swc_clock.c
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 *
 * description: Software component that displays time (hours and minutes)
 * name: swc_clock
 * shortname: clock
 *
 */

#include "project.h"
#include "global.h"
#include "rte.h"
#include "rte_types.h"
#include "swc_clock.h"



/* USER CODE START SWC_CLOCK_INCLUDE */

/* USER CODE END SWC_CLOCK_INCLUDE */


#include "sp_common.h"

/* USER CODE START SWC_CLOCK_USERDEFINITIONS */

/* USER CODE END SWC_CLOCK_USERDEFINITIONS */



/*
 * component: swc_clock
 * cycletime: 50
 * description: Runnable
 * events: 
 * name: CLOCK_input_run
 * shortname: input
 * signalIN: 
 * signalOUT: so_input
 * task: tsk_input
 */
void CLOCK_input_run(RTE_event ev){
	
	/* USER CODE START CLOCK_input_run */

    /* USER CODE END CLOCK_input_run */
}

/*
 * component: swc_clock
 * cycletime: 0
 * description: Runnable
 * events: ev_onData|ev_button
 * name: CLOCK_control_run
 * shortname: control
 * signalIN: so_input
 * signalOUT: so_control
 * task: tsk_control
 */
void CLOCK_control_run(RTE_event ev){
	
	/* USER CODE START CLOCK_control_run */

    /* USER CODE END CLOCK_control_run */
}

/*
 * component: swc_clock
 * cycletime: 250
 * description: Runnable
 * events: 
 * name: CLOCK_display_run
 * shortname: display
 * signalIN: so_control
 * signalOUT: so_display
 * task: tsk_input
 */
void CLOCK_display_run(RTE_event ev){
	
	/* USER CODE START CLOCK_display_run */

    /* USER CODE END CLOCK_display_run */
}

/* USER CODE START SWC_CLOCK_FUNCTIONS */

/* USER CODE END SWC_CLOCK_FUNCTIONS */

