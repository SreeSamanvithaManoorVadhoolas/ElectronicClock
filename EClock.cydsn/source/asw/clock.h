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
#ifndef CLOCK_H
#define CLOCK_H
    
#include "global.h"
#include "clock_type.h"    
#include "statemachine.h"

typedef struct
{
    CLOCK_state_t m_widgetState;
    STATE_stateInnerTransitionTable_t* m_transitions;
    STATE_stateAction_t* m_stateActions;
    uint8_t m_value;
    CLOCK_font_t m_font;
}CLOCK_widget_t;

typedef struct
{
    CLOCK_state_t m_containerState;
    STATE_stateInnerTransitionTable_t* m_transitions;
    STATE_stateAction_t* m_stateActions;
    CLOCK_Active_Widget_t m_activeWidget;
    CLOCK_widget_t m_hours;
    CLOCK_widget_t m_minutes;
}CLOCK_data_t;

void statemachine_init(); 
void ProcessEvent(STATE_event_t event);

#endif
/* [] END OF FILE */
