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

#include "clock.h"
#include "sp_common.h"
#include "stdlib.h"

char buffer[100];
/** ---------------------------- Actions ---------------------------------- **/

static void CLOCK__dispatch_Wrapper(EVENT_t ev, CLOCK_Active_Widget_t widget);
static void CLOCK__dispatch_KL_Hours();
static void CLOCK__increment1Minute();
static void CLOCK__dispatch_KL_HoursMin();
static void CLOCK__dispatch_KR_Hours();
static void CLOCK__dispatch_KRLP_Hours();
static void CLOCK__dispatch_250MS_Hours();
static void CLOCK__dispatch_KL_Min();
static void CLOCK__dispatch_KR_Min();
static void CLOCK__dispatch_KRLP_Min();
static void CLOCK__dispatch_250MS_Min();
static void CLOCK__setEditFonts();
static void CLOCK__incrementWidget();
static void CLOCK__setDisplayFonts();
static void CLOCK__updateDisplay();
static void CLOCK__updateTime();
static void CLOCK__incrementHourandDisplay();
static void CLOCK__incrementMinuteandDisplay();

/** ---------------------------- Actions ---------------------------------- **/


/** ------------------------------------- Transitions Table Start ------------------------------------------- **/

/**============================== Container ================================ **/

/** ========= CLOCK_C_ISDISPLAYING ========== **/
const STATE_stateInnerTransition_t STATE_CLOCK_C_ISDISPLAYING_Transitions[] = 
{
    /*  Event               ToState                         Guard           Action                      */
    {   EV_KEYLEFT,         CLOCK_C_ISEDITINGHOURS,         0,              CLOCK__dispatch_KL_Hours     },
    {   EV_1MIN,            CLOCK_C_ISDISPLAYING,           0,              CLOCK__increment1Minute      },
};

/** ========= CLOCK_C_ISEDITINGHOURS ========== **/
const STATE_stateInnerTransition_t STATE_CLOCK_C_ISEDITINGHOURS_Transitions[] = 
{
    /*  Event                       ToState                           Guard           Action                         */
    {   EV_KEYLEFT,                 CLOCK_C_ISEDITINGMINUTES,         0,              CLOCK__dispatch_KL_HoursMin    },
    {   EV_KEYRIGHT,                CLOCK_C_ISEDITINGHOURS,           0,              CLOCK__dispatch_KR_Hours       },
    {   EV_KEYRIGHTLONGPRESS,       CLOCK_C_ISEDITINGHOURS,           0,              CLOCK__dispatch_KRLP_Hours     },
    {   EV_250MS,                   CLOCK_C_ISEDITINGHOURS,           0,              CLOCK__dispatch_250MS_Hours    },
};

/** ========= CLOCK_C_ISEDITINGMINUTES ========== **/
const STATE_stateInnerTransition_t STATE_CLOCK_C_ISEDITINGMINUTES_Transitions[] = 
{
    /*  Event                       ToState                         Guard           Action                      */
    {   EV_KEYLEFT,                 CLOCK_C_ISDISPLAYING,           0,              CLOCK__dispatch_KL_Min       },
    {   EV_KEYRIGHT,                CLOCK_C_ISEDITINGMINUTES,       0,              CLOCK__dispatch_KR_Min       },
    {   EV_KEYRIGHTLONGPRESS,       CLOCK_C_ISEDITINGMINUTES,       0,              CLOCK__dispatch_KRLP_Min     },
    {   EV_250MS,                   CLOCK_C_ISEDITINGMINUTES,       0,              CLOCK__dispatch_250MS_Min    },
};

static const STATE_stateOuterTransitionTable_t CLOCK_Container_Transitions = 
{
    /*  fromState                     Pointer to table                                        Size of table [Elements]                                                                    */
    {   CLOCK_C_ISDISPLAYING,         &STATE_CLOCK_C_ISDISPLAYING_Transitions,                sizeof(STATE_CLOCK_C_ISDISPLAYING_Transitions)/sizeof(STATE_stateInnerTransition_t)         },
    {   CLOCK_C_ISEDITINGHOURS,       &STATE_CLOCK_C_ISEDITINGHOURS_Transitions,              sizeof(STATE_CLOCK_C_ISEDITINGHOURS_Transitions)/sizeof(STATE_stateInnerTransition_t)       },
    {   CLOCK_C_ISEDITINGMINUTES,     &STATE_CLOCK_C_ISEDITINGMINUTES_Transitions,            sizeof(STATE_CLOCK_C_ISEDITINGMINUTES_Transitions)/sizeof(STATE_stateInnerTransition_t)     },
};
static const uint16_t CLOCK_Container_Transitions_size = sizeof(CLOCK_Container_Transitions)/sizeof(STATE_stateOuterTransition_t);

/** ============= Container Action ============== **/
static const STATE_stateActionTable_t CLOCK_Container_Actions = 
{
    /*  fromState                   actionEntry                   actionExit          */
    {   CLOCK_C_ISDISPLAYING,       CLOCK__updateDisplay,         0                   },
};
static const uint16_t CLOCK_Container_Actions_size = sizeof(CLOCK_Container_Actions)/sizeof(STATE_stateAction_t);

/**============================== WIDGET ================================ **/

/** ========= CLOCK_W_ISDISPLAYING =========== **/
const STATE_stateInnerTransition_t STATE_CLOCK_W_ISDISPLAYING_Transitions[] = 
{
    /*  Event               ToState                    Guard           Action                  */
    {   EV_KEYLEFT,         CLOCK_W_ISEDITING,         0,              CLOCK__setEditFonts     },
};

/** ========= CLOCK_W_ISEDITING ============== **/
const STATE_stateInnerTransition_t STATE_CLOCK_W_ISEDITING_Transitions[] = 
{
    /*  Event                       ToState                         Guard           Action                     */
    {   EV_KEYRIGHT,                CLOCK_W_ISEDITING,              0,              CLOCK__incrementWidget     },
    {   EV_KEYRIGHTLONGPRESS,       CLOCK_W_ISAUTOINCREMENT,        0,              0                          },
    {   EV_KEYLEFT,                 CLOCK_W_ISDISPLAYING,           0,              CLOCK__setDisplayFonts     },
};

/** ========= CLOCK_W_ISAUTOINCREMENT ========== **/
const STATE_stateInnerTransition_t STATE_CLOCK_W_ISAUTOINCREMENT_Transitions[] = 
{
    /*  Event                       ToState                         Guard           Action                     */
    {   EV_KEYRIGHT,                CLOCK_W_ISEDITING,              0,              CLOCK__incrementWidget     },
    {   EV_250MS,                   CLOCK_W_ISAUTOINCREMENT,        0,              CLOCK__incrementWidget     },
    {   EV_KEYLEFT,                 CLOCK_W_ISEDITING,              0,              CLOCK__setDisplayFonts     },
};

static const STATE_stateOuterTransitionTable_t CLOCK_Widget_Transitions = 
{
    /*  fromState                   Pointer to table                                Size of table [Elements]                                                                */
    {   CLOCK_W_ISDISPLAYING,       &STATE_CLOCK_W_ISDISPLAYING_Transitions,        sizeof(STATE_CLOCK_W_ISDISPLAYING_Transitions)/sizeof(STATE_stateInnerTransition_t)     },
    {   CLOCK_W_ISEDITING,          &STATE_CLOCK_W_ISEDITING_Transitions,           sizeof(STATE_CLOCK_W_ISEDITING_Transitions)/sizeof(STATE_stateInnerTransition_t)        },
    {   CLOCK_W_ISAUTOINCREMENT,    &STATE_CLOCK_W_ISAUTOINCREMENT_Transitions,     sizeof(STATE_CLOCK_W_ISAUTOINCREMENT_Transitions)/sizeof(STATE_stateInnerTransition_t)  },
};
static const uint16_t CLOCK_Widget_Transitions_size = sizeof(CLOCK_Widget_Transitions)/sizeof(STATE_stateOuterTransition_t);

/** ============= Widget Action ============== **/
static const STATE_stateActionTable_t CLOCK_Widget_Actions = 
{
    /*  fromState                   actionEntry                  actionExit          */
    {   CLOCK_W_ISDISPLAYING,       CLOCK__updateDisplay,        0                   },
    {   CLOCK_W_ISEDITING,          CLOCK__updateDisplay,        0                   },
    {   CLOCK_W_ISAUTOINCREMENT,    CLOCK__updateDisplay,        0                   },
};
static const uint16_t CLOCK_Widget_Actions_size = sizeof(CLOCK_Widget_Actions)/sizeof(STATE_stateAction_t);

/** ------------------------------------- Transitions Table End ------------------------------------------- **/
STATE_t containerFSM = {
    &CLOCK_Container_Transitions, 
    sizeof(CLOCK_Container_Transitions)/sizeof(STATE_stateOuterTransition_t), 
    &CLOCK_Container_Actions, 
    sizeof(CLOCK_Container_Actions)/sizeof(STATE_stateAction_t),
    CLOCK_C_ISDISPLAYING
};

STATE_t widgetFSM = {
        &CLOCK_Widget_Transitions,
        sizeof(CLOCK_Widget_Transitions)/sizeof(STATE_stateOuterTransition_t),
        &CLOCK_Widget_Actions,
        sizeof(CLOCK_Widget_Actions)/sizeof(STATE_stateAction_t),
        CLOCK_W_ISDISPLAYING
};

void statemachine_init()
{   
    //UART_LOG_PutString("statemachine_init");
    SC_CONTROL_data_t control = SC_CONTROL_INIT_DATA;
    containerFSM.m_state = CLOCK_C_ISDISPLAYING;
    
    control = RTE_SC_CONTROL_get(&SO_CONTROL_signal);
    
    control.hour.font_type.size = 4;
    control.minute.font_type.size = 4;
    
    control.hour.font_type.x_pos = 10;
    control.hour.font_type.y_pos = 60;
    
    control.minute.font_type.x_pos = 75;
    control.minute.font_type.y_pos = 60;
    
    control.hour.font_type.bg_colour = BLACK;
    control.minute.font_type.bg_colour = BLACK;
    
    control.hour.font_type.widget = WHITE;
    control.minute.font_type.widget = WHITE;
    
    containerFSM.m_state = CLOCK_C_ISDISPLAYING;
    STATE_initState(&containerFSM);
    
    STATE_initState(&containerFSM);
    RTE_SC_CONTROL_set(&SO_CONTROL_signal, control);
}
void ProcessEvent(STATE_event_t event)
{
    SC_INPUT_data_t input;
    
    STATE_event_t local_event = event;
    STATE_processEvent(&containerFSM,local_event);
    
    input = RTE_SC_INPUT_get(&SO_INPUT_signal);
    input.m_clock_data.m_containerState = containerFSM.m_state;
    
    /*char buffer[100];
    UART_LOG_PutString("ProcessEvent: container state post process: ");
    itoa(containerFSM.m_state, buffer, 10);
    UART_LOG_PutString(buffer);
    UART_LOG_PutString("\n");
    
    UART_LOG_PutString("ProcessEvent: hr state: ");
    itoa(containerFSM.m_state, buffer, 10);
    UART_LOG_PutString(buffer);
    UART_LOG_PutString("\n");
    
    UART_LOG_PutString("ProcessEvent: min state: ");
    itoa(containerFSM.m_state, buffer, 10);
    UART_LOG_PutString(buffer);
    UART_LOG_PutString("\n");*/
}

void CLOCK__dispatch_Wrapper(EVENT_t ev, CLOCK_Active_Widget_t widget)
{
    SC_INPUT_data_t input = RTE_SC_INPUT_get(&SO_INPUT_signal);
    
    //UART_LOG_PutString("CLOCK__dispatch_Wrapper active widget: ");
    /*
    itoa(input.m_ev, buffer, 10);
    UART_LOG_PutString(buffer);
    UART_LOG_PutString("\n");
    */
    
    //to clear prev event
    input.m_ev = EV_NONE;
    //UART_LOG_PutString("CLOCK__dispatch_Wrapper active widget: ");
    input.m_clock_data.m_activeWidget = widget;
    
    RTE_SC_INPUT_set(&SO_INPUT_signal, input);
    
    /*
    itoa(input.m_clock_data.m_activeWidget, buffer, 10);
    UART_LOG_PutString(buffer);
    UART_LOG_PutString("\n");
    */
    if(widget == CLOCK_HOURWIDGET)
    {
        CLOCK_state_t localstate = input.m_clock_data.m_hours.m_widgetState;
        
        /*UART_LOG_PutString("Hour widget state from signal: ");
       itoa(localstate, buffer, 10);
        UART_LOG_PutString(buffer);
        UART_LOG_PutString("\n");
        UART_LOG_PutString("Hour widget state from state machine obj: ");
       itoa(widgetFSM.m_state, buffer, 10);
        UART_LOG_PutString(buffer);
        UART_LOG_PutString("\n");*/
        
        widgetFSM.m_state = localstate;
        STATE_processEvent(&widgetFSM,ev);
        
        /*
        UART_LOG_PutString("after process event state: ");
        itoa(widgetFSM.m_state, buffer, 10);
        UART_LOG_PutString(buffer);
        UART_LOG_PutString("\n");*/
        
        input = RTE_SC_INPUT_get(&SO_INPUT_signal);
        input.m_clock_data.m_hours.m_widgetState = widgetFSM.m_state;
        RTE_SC_INPUT_set(&SO_INPUT_signal, input);
    }
    else if(widget == CLOCK_MINWIDGET)
    {
        CLOCK_state_t localstate = input.m_clock_data.m_minutes.m_widgetState;
        
        /*UART_LOG_PutString("Minute widget state: ");
        itoa(localstate, buffer, 10);
        UART_LOG_PutString(buffer);
        UART_LOG_PutString("\n");*/
        
        widgetFSM.m_state = localstate;
        STATE_processEvent(&widgetFSM,ev);
        /*UART_LOG_PutString("Minute widget state: after process ");
        itoa(widgetFSM.m_state, buffer, 10);
        UART_LOG_PutString(buffer);
        UART_LOG_PutString("\n");*/
        input = RTE_SC_INPUT_get(&SO_INPUT_signal);
        
        input.m_clock_data.m_minutes.m_widgetState = widgetFSM.m_state;
        
        RTE_SC_INPUT_set(&SO_INPUT_signal, input);
    }
}

void CLOCK__dispatch_KL_Hours()
{
    //UART_LOG_PutString("CLOCK__dispatch_KL_Hours\n");
    SC_INPUT_data_t input = RTE_SC_INPUT_get(&SO_INPUT_signal);
    input.m_clock_data.m_hours.m_widgetState = CLOCK_W_ISDISPLAYING;
    RTE_SC_INPUT_set(&SO_INPUT_signal, input);
    CLOCK__dispatch_Wrapper(EV_KEYLEFT, CLOCK_HOURWIDGET);
}

void CLOCK__increment1Minute()
{
    CLOCK__updateTime();
}

void CLOCK__dispatch_KL_HoursMin()
{
    //UART_LOG_PutString("CLOCK__dispatch_KL_HoursMin\n");
    SC_INPUT_data_t input = RTE_SC_INPUT_get(&SO_INPUT_signal);
    input.m_clock_data.m_hours.m_widgetState = CLOCK_W_ISEDITING;
    input.m_clock_data.m_minutes.m_widgetState = CLOCK_W_ISDISPLAYING;
    RTE_SC_INPUT_set(&SO_INPUT_signal, input);
    
    CLOCK__dispatch_Wrapper(EV_KEYLEFT, CLOCK_HOURWIDGET);
    CLOCK__dispatch_Wrapper(EV_KEYLEFT, CLOCK_MINWIDGET);
}

void CLOCK__dispatch_KR_Hours()
{
    //UART_LOG_PutString("CLOCK__dispatch_KR_Hours\n");
    CLOCK__dispatch_Wrapper(EV_KEYRIGHT, CLOCK_HOURWIDGET);
}

void CLOCK__dispatch_KRLP_Hours()
{
    //UART_LOG_PutString("CLOCK__dispatch_KRLP_Hours\n");
    SC_INPUT_data_t input = RTE_SC_INPUT_get(&SO_INPUT_signal);
    input.m_clock_data.m_hours.m_widgetState = CLOCK_W_ISEDITING;
    RTE_SC_INPUT_set(&SO_INPUT_signal, input);
    CLOCK__dispatch_Wrapper(EV_KEYRIGHTLONGPRESS, CLOCK_HOURWIDGET);
}

void CLOCK__dispatch_250MS_Hours()
{
    //UART_LOG_PutString("CLOCK__dispatch_250MS_Hours\n");
    CLOCK__dispatch_Wrapper(EV_250MS, CLOCK_HOURWIDGET);
}

void CLOCK__dispatch_KL_Min()
{
    //UART_LOG_PutString("CLOCK__dispatch_KL_Min\n");
    CLOCK__dispatch_Wrapper(EV_KEYLEFT, CLOCK_MINWIDGET);
}

void CLOCK__dispatch_KR_Min()
{
    //UART_LOG_PutString("CLOCK__dispatch_KR_Min\n");
    CLOCK__dispatch_Wrapper(EV_KEYRIGHT, CLOCK_MINWIDGET);
}

void CLOCK__dispatch_KRLP_Min()
{
    //UART_LOG_PutString("CLOCK__dispatch_KRLP_Min\n");
    SC_INPUT_data_t input = RTE_SC_INPUT_get(&SO_INPUT_signal);
    input.m_clock_data.m_minutes.m_widgetState = CLOCK_W_ISEDITING;
    RTE_SC_INPUT_set(&SO_INPUT_signal, input);
    CLOCK__dispatch_Wrapper(EV_KEYRIGHTLONGPRESS, CLOCK_MINWIDGET);
}

void CLOCK__dispatch_250MS_Min()
{
    //UART_LOG_PutString("CLOCK__dispatch_250MS_Min\n");
    CLOCK__dispatch_Wrapper(EV_250MS, CLOCK_MINWIDGET);
}

void CLOCK__incrementWidget()
{
    SC_INPUT_data_t input = RTE_SC_INPUT_get(&SO_INPUT_signal);
    if(input.m_clock_data.m_activeWidget == CLOCK_HOURWIDGET)
    {
        //UART_LOG_PutString("CLOCK__incrementWidget hr\n");
        CLOCK__incrementHourandDisplay();
    }
    else if(input.m_clock_data.m_activeWidget == CLOCK_MINWIDGET)
    {
        //UART_LOG_PutString("CLOCK__incrementWidget min\n");
        CLOCK__incrementMinuteandDisplay();
    }
}

void CLOCK__setDisplayFonts()
{
    SC_CONTROL_data_t control = RTE_SC_CONTROL_get(&SO_CONTROL_signal);;
    control.hour.font_type.bg_colour = BLACK;
    control.hour.font_type.widget = WHITE;
    control.minute.font_type.bg_colour   = BLACK;
    control.minute.font_type.widget = WHITE;
    RTE_SC_CONTROL_set(&SO_CONTROL_signal, control);
}

void CLOCK__setEditFonts()
{
    SC_INPUT_data_t input = RTE_SC_INPUT_get(&SO_INPUT_signal);
    SC_CONTROL_data_t control =RTE_SC_CONTROL_get(&SO_CONTROL_signal);
    if(input.m_clock_data.m_activeWidget == CLOCK_HOURWIDGET)
    {
        //UART_LOG_PutString("hr edit font\n");
        control.hour.font_type.bg_colour = WHITE;
        control.hour.font_type.widget = BLACK;
        control.minute.font_type.bg_colour   = BLACK;
        control.minute.font_type.widget = WHITE;
    }
    else if(input.m_clock_data.m_activeWidget == CLOCK_MINWIDGET)
    {
        //UART_LOG_PutString("min edit font\n");        
        control.hour.font_type.bg_colour = BLACK;
        control.hour.font_type.widget = WHITE;
        control.minute.font_type.bg_colour   = WHITE;
        control.minute.font_type.widget = BLACK;
    }
    RTE_SC_CONTROL_set(&SO_CONTROL_signal, control);
}

void CLOCK__updateDisplay()
{
    SC_CONTROL_data_t control = RTE_SC_CONTROL_get(&SO_CONTROL_signal);
    RTE_SC_CONTROL_set(&SO_CONTROL_signal, control);   
}

void CLOCK__updateTime()
{
    //UART_LOG_PutString("CLOCK__updateTime\n");
    SC_CONTROL_data_t time = RTE_SC_CONTROL_get(&SO_CONTROL_signal);
    time.minute.value++;
    if(time.minute.value%60 == 0)
    {
        //UART_LOG_PutString("1 hr\n");
        time.hour.value++;
        if(time.hour.value%24 == 0)
        {
            time.hour.value = 0;
        }
        time.minute.value = 0;
    }
    RTE_SC_CONTROL_set(&SO_CONTROL_signal, time);
}

void CLOCK__incrementHourandDisplay()
{
    SC_CONTROL_data_t control = RTE_SC_CONTROL_get(&SO_CONTROL_signal);
    control.hour.value++;
    if(control.hour.value%24 == 0)
    {
        control.hour.value = 0;
    }    
    /*itoa(clock_hour.hour.value, buffer, 10);
    UART_LOG_PutString("hr value: ");
    UART_LOG_PutString(buffer);
    UART_LOG_PutString("\n");*/
    CLOCK__updateDisplay(); 
    
    RTE_SC_CONTROL_set(&SO_CONTROL_signal, control);
}

void CLOCK__incrementMinuteandDisplay()
{
    SC_CONTROL_data_t control = RTE_SC_CONTROL_get(&SO_CONTROL_signal);   
    control.minute.value++;
    if(control.minute.value%60 == 0)
    {
        control.minute.value = 0;
        CLOCK__incrementHourandDisplay();
    }
    /*itoa(clock_minute.minute.value, buffer, 10);
    UART_LOG_PutString("min value: ");
    UART_LOG_PutString(buffer);
    UART_LOG_PutString("\n");*/
    CLOCK__updateDisplay();
    RTE_SC_CONTROL_set(&SO_CONTROL_signal, control);
}

/* [] END OF FILE */
