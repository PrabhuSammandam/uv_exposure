/*
* seven_seg_disp.cpp
*
* Created: 10/11/2015 7:47:56 AM
*  Author: Prabhus
*/
#include <avr/io.h>
#include <avr/interrupt.h>

#include "SevenSegmentDisplay.h"
#include "io_port.h"

#define SEGMENT_A IOPORT_CREATE_PIN(PORT_D, 0)
#define SEGMENT_B IOPORT_CREATE_PIN(PORT_D, 1)
#define SEGMENT_C IOPORT_CREATE_PIN(PORT_D, 2)
#define SEGMENT_D IOPORT_CREATE_PIN(PORT_D, 3)
#define SEGMENT_E IOPORT_CREATE_PIN(PORT_D, 4)
#define SEGMENT_F IOPORT_CREATE_PIN(PORT_D, 5)
#define SEGMENT_G IOPORT_CREATE_PIN(PORT_D, 6)

#define DIGIT_1 IOPORT_CREATE_PIN(PORT_C, 5)
#define DIGIT_2 IOPORT_CREATE_PIN(PORT_C, 4)
#define DIGIT_3 IOPORT_CREATE_PIN(PORT_C, 3)
#define DIGIT_4 IOPORT_CREATE_PIN(PORT_C, 2)

#define STANDBY_TIME 200

uint8_t gs_digit_pin_list[] = { DIGIT_1, DIGIT_2, DIGIT_3, DIGIT_4};
uint8_t gs_digit_bitmap[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x98};
uint16_t gs_display_time_cnt = 0;
uint8_t gs_enable_stand_by = 1;
uint8_t gs_display_off = 0;

SevenSegmentDisplay::SevenSegmentDisplay()
{
    _cur_display_digit = 0;

    for(unsigned char i = 0; i < sizeof(_digits); i++)
    {
        _digits[i] = 0;
    }
}

void SevenSegmentDisplay::Init()
{
    /*configure the segment pins as output*/
    io_port_set_pin_output(SEGMENT_A);
    io_port_set_pin_output(SEGMENT_B);
    io_port_set_pin_output(SEGMENT_C);
    io_port_set_pin_output(SEGMENT_D);
    io_port_set_pin_output(SEGMENT_E);
    io_port_set_pin_output(SEGMENT_F);
    io_port_set_pin_output(SEGMENT_G);

    /*configure the digit pins as output*/
    io_port_set_pin_output(DIGIT_1);
    io_port_set_pin_output(DIGIT_2);
    io_port_set_pin_output(DIGIT_3);
    io_port_set_pin_output(DIGIT_4);

    InitDisplayTimer();
}

/* set the digit value*/
void SevenSegmentDisplay::SetDigit(unsigned char digitIndex, unsigned char digitValue)
{
    _digits[digitIndex] = digitValue;
}

/* set the minute and seconds as passed as time value */
void SevenSegmentDisplay::SetTime(TimeValue& timeValue)
{
    SetDigit(0, timeValue.GetSecond() %10);
    SetDigit(1, timeValue.GetSecond() /10);
    SetDigit(2, timeValue.GetMinute() %10);
    SetDigit(3, timeValue.GetMinute() /10);
}

/* set the current display digit. */
void SevenSegmentDisplay::SelectDisplayDigit(unsigned char displayDigit)
{
    if(displayDigit > 3) return;

    SwitchOffDisplay();
    io_port_set_pin_high(gs_digit_pin_list[displayDigit]);
}

void SevenSegmentDisplay::SwitchOffDisplay()
{
    io_port_set_pin_low(DIGIT_1);
    io_port_set_pin_low(DIGIT_2);
    io_port_set_pin_low(DIGIT_3);
    io_port_set_pin_low(DIGIT_4);
}

void SevenSegmentDisplay::DisplayDigitValue(unsigned char displayValue)
{
    if(displayValue > 9) return;
    PORTD |= 0x7F;
    PORTD &= gs_digit_bitmap[displayValue];
}

void SevenSegmentDisplay::InitDisplayTimer()
{
    TCNT0	=	0; // Initialize the Timer/Counter Register to 0
    
    TIMSK	|=	(1 << TOIE0);//enable timer0 overflow interrupt

    TCCR0 |= (1 << CS01) | (1 << CS00); // pre-scale by 64
}

void SevenSegmentDisplay::SetStandBy(bool is_standby)
{
    gs_enable_stand_by = is_standby;
    gs_display_off = 0;
}

void SevenSegmentDisplay::RefreshDisplay()
{
    if (gs_enable_stand_by == 1)
    {
        if (gs_display_time_cnt++ > STANDBY_TIME)
        {
            gs_display_time_cnt = 0;
            gs_display_off = !gs_display_off;
        }
    }

    if (gs_display_off)
    {
        SwitchOffDisplay();
        return;
    }

    SelectDisplayDigit(_cur_display_digit);
    DisplayDigitValue(_digits[_cur_display_digit]);

    if(_cur_display_digit == 3)
    {
        _cur_display_digit = 0;
    }
    else
    {
        _cur_display_digit++;
    }
}

void SevenSegmentDisplay::SetNumber(unsigned short num)
{
    unsigned char i=0;
    unsigned char j;

    if(num>9999) return;

    while(num)
    {
        SetDigit(i, num%10);
        i++;

        num=num/10;
    }
    
    /* set remaining digit value as 0*/
    for(j=i;j<4;j++)
    {
        SetDigit(j, 0);
    }
}


ISR(TIMER0_OVF_vect)
{
    extern SevenSegmentDisplay sevenSegmentDisplay;

    sevenSegmentDisplay.RefreshDisplay();
}
