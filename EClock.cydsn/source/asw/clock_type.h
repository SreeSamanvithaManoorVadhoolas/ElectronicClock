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
#ifndef CLOCK_TYPE_H
#define CLOCK_TYPE_H

#include "global.h"
#include "tft.h"
    
    
typedef enum
{
    EV_NONE,
    EV_KEYLEFT,
    EV_KEYRIGHT,
    EV_KEYRIGHTLONGPRESS,
    EV_250MS,
    EV_1MIN
    
}EVENT_t;

typedef EVENT_t Event_data_t;

#define EVENT_INIT_DATA EV_NONE

typedef enum 
{
    //Container
    CLOCK_C_ISDISPLAYING,         
    CLOCK_C_ISEDITINGHOURS,    
    CLOCK_C_ISEDITINGMINUTES,  
    //Widget  
    CLOCK_W_ISDISPLAYING,
    CLOCK_W_ISEDITING,
    CLOCK_W_ISAUTOINCREMENT
    
}CLOCK_state_t;

typedef EVENT_t STATE_event_t;

#define STATE_INITIALSTATE CLOCK_C_ISDISPLAYING 

typedef enum
{
    CLOCK_HOURWIDGET,
    CLOCK_MINWIDGET,
    NONE,
}CLOCK_Active_Widget_t;

typedef struct
{
    uint8_t size;
    TFT_colors_t bg_colour;
    TFT_colors_t widget;
    uint8_t x_pos;
    uint8_t y_pos;
}CLOCK_font_t;

typedef struct
{
    CLOCK_Active_Widget_t widget;
    CLOCK_font_t font_type;
    uint8_t value;
} CLOCK_display_t;

#endif
/* [] END OF FILE */
