/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "global.h"
#include "tft.h"

//ISR which will increment the systick counter every ms
ISR(systick_handler)
{
    CounterTick(cnt_systick);
}
void callback_function()
{
    ActivateTask(tsk_input);
    ActivateTask(tsk_system);
}
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    //Set systick period to 1 ms. Enable the INT and start it.
	EE_systick_set_period(MILLISECONDS_TO_TICKS(1, BCLK__BUS_CLK__HZ));
	EE_systick_enable_int();

    for(;;)
    {
        /* Place your application code here. */
        StartOS(OSDEFAULTAPPMODE);
    }
}
void unhandledException()
{
    //Ooops, something terrible happened....check the call stack to see how we got here...
    __asm("bkpt");
}
TASK(tsk_init)
{
    
    //Init MCAL Drivers   
    TFT_init();
    UART_LOG_Start();
    TFT_setColors(BLACK, WHITE);
    TFT_printf("   EAA Assignment 2  \n\n");
    TFT_setColors(WHITE, BLACK);
    TFT_print("   Electronic Clock  ");
    
    //Reconfigure ISRs with OS parameters.
    //This line MUST be called after the hardware driver initialisation!
    EE_system_init();
	
    //Start SysTick
	//Must be done here, because otherwise the isr vector is not overwritten yet
    EE_systick_start();  
 
    SetRelAlarm(alrm_1ms,1,1);
    
    ActivateTask(tsk_control);
    ActivateTask(tsk_background);
    
    TerminateTask();
    
}
TASK(tsk_background)
{
    while(1)
    {
        //do something with low prioroty
        __asm("nop");
    }
}
/********************************************************************************
 * ISR Definitions
 ********************************************************************************/
ISR2(isr_button)
{
    // Set event for button task to handle button press
    if ((Button_1_Read() == 1) || (Button_2_Read() == 1)) SetEvent(tsk_control,ev_button); 
}
/* [] END OF FILE */
