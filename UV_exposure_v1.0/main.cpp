/*
* UV_exposure_v1.0.cpp
*
* Created: 10/11/2015 7:47:08 AM
* Author : Prabhus
*/

#define __HAS_DELAY_CYCLES 1
#define F_CPU              8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "io_port.h"
#include "SevenSegmentDisplay.h"
#include "RealTimeClock.h"
#include "TimeValue.h"
#include "KeyPad.h"
#include "UvLed.h"

void StopCountDownTimer();
void BeepBuzzer();
bool IsPauseSwitchOn();

#define COUNT_DOWN_TIMER_STATE_NONE		 0
#define COUNT_DOWN_TIMER_STATE_STARTED	 1
#define COUNT_DOWN_TIMER_STATE_STOPPED	 2
#define COUNT_DOWN_TIMER_STATE_PAUSED	 3

#define BUZZER IOPORT_CREATE_PIN(PORT_B, 1)
#define PAUSE_SWITCH IOPORT_CREATE_PIN(PORT_D, 7)

SevenSegmentDisplay sevenSegmentDisplay;
RealTimeClock realTimeClock;
TimeValue timeValue;
KeyPad keyPad;
UvLed uvLed;

unsigned char	 current_key = KEY_NONE;
unsigned char	 countDownTimerState = COUNT_DOWN_TIMER_STATE_STOPPED;
bool				 minuteSelect = false;
bool				 beepBuzz = false;
uint8_t preset_time[] = {5, 8, 10, 15, 18, 20};
uint8_t preset_idx = 0;

void delay_ms(unsigned int   ms_delay)
{
    for(unsigned int i = 0; i < ms_delay; i++)
    {
        _delay_ms(1);
    }
}

void rtc_callback_function()
{
    timeValue.DecreaseSecond(false);

    sevenSegmentDisplay.SetTime(timeValue);

    if (timeValue.IsValid() == false)
    {
        StopCountDownTimer();
    }
}

void StopCountDownTimer()
{
    realTimeClock.Stop();

    uvLed.Stop();
    
    countDownTimerState = COUNT_DOWN_TIMER_STATE_STOPPED;

    timeValue.Reset();

    sevenSegmentDisplay.SetTime(timeValue);
    sevenSegmentDisplay.SetStandBy(1);

    beepBuzz = true;
}

void PauseCountDownTimer()
{
    realTimeClock.Stop();

    uvLed.Stop();
    
    countDownTimerState = COUNT_DOWN_TIMER_STATE_PAUSED;
}

void StartCountDownTimer()
{
    if (IsPauseSwitchOn() == true)
    {
        return;
    }

    if (timeValue.IsValid())
    {
        sevenSegmentDisplay.SetStandBy(0);

        countDownTimerState = COUNT_DOWN_TIMER_STATE_STARTED;

        realTimeClock.Start();

        uvLed.Start();
    }
    else
    {
        StopCountDownTimer();
    }
}

void ProcessKey()
{
    if (current_key != KEY_NONE)
    {
        switch (current_key)
        {
            case KEY_TIMER_PRESET:
            {
                if(countDownTimerState == COUNT_DOWN_TIMER_STATE_STOPPED)
                {
                    sevenSegmentDisplay.SetStandBy(0);
                    timeValue.Reset();

                    if (preset_idx == sizeof(preset_time)/sizeof(uint8_t))
                    {
                        preset_idx = 0;
                    }

                    for (int i = 0; i < preset_time[preset_idx]; i++)
                    {
                        timeValue.IncreaseMinute();
                    }

                    sevenSegmentDisplay.SetTime(timeValue);
                    preset_idx++;
                }
            }
            break;

            case KEY_START_STOP:
            {
                /*
                * If already stopped then start it
                **/
                if (countDownTimerState == COUNT_DOWN_TIMER_STATE_STOPPED)
                {
                    StartCountDownTimer();
                }
                else if(countDownTimerState == COUNT_DOWN_TIMER_STATE_STARTED)
                {
                    /*
                    * If already started then stop it
                    **/
                    StopCountDownTimer();
                }
            }
            break;

            case KEY_TIMER_UP:
            {
                if(countDownTimerState == COUNT_DOWN_TIMER_STATE_STOPPED)
                {
                    sevenSegmentDisplay.SetStandBy(0);

                    if (minuteSelect == true)
                    {
                        timeValue.IncreaseMinute();
                    }
                    else
                    {
                        for (unsigned char i = 0; i < 10; i++)
                        {
                            timeValue.IncreaseSecond();
                        }
                    }
                    sevenSegmentDisplay.SetTime(timeValue);
                }
            }
            break;

            case KEY_TIMER_DOWN:
            {
                if(countDownTimerState == COUNT_DOWN_TIMER_STATE_STOPPED)
                {
                    sevenSegmentDisplay.SetStandBy(0);

                    if (minuteSelect == true)
                    {
                        timeValue.DecreaseMinute();
                    }
                    else
                    {
                        /* increase second in multiples of 10*/
                        for (unsigned char i = 0; i < 10; i++)
                        {
                            timeValue.DecreaseSecond();
                        }
                    }
                    sevenSegmentDisplay.SetTime(timeValue);
                }
            }
            break;

            case KEY_TIMER_MINUTE_SELECT:
            {
                if(countDownTimerState == COUNT_DOWN_TIMER_STATE_STOPPED)
                {
                    minuteSelect = !minuteSelect;
                }
            }
            break;
        }

        current_key = KEY_NONE;
    }
}


bool IsPauseSwitchOn()
{
    return io_port_is_pin_high(PAUSE_SWITCH);
}

void InitPauseSwitch()
{
    io_port_set_pin_input(PAUSE_SWITCH);
    io_port_set_pin_high(PAUSE_SWITCH);
}

void InitBuzzer()
{
    io_port_set_pin_output(BUZZER);
}

#define BEEP_SOUND_LENGTH 50

void BeepBuzzer()
{
    for(char i = 0; i < 5; i++)
    {
        io_port_set_pin_high(BUZZER);
        delay_ms(BEEP_SOUND_LENGTH);
        io_port_set_pin_low(BUZZER);
        delay_ms(BEEP_SOUND_LENGTH);
        io_port_set_pin_high(BUZZER);
        delay_ms(BEEP_SOUND_LENGTH);
        io_port_set_pin_low(BUZZER);
        delay_ms(BEEP_SOUND_LENGTH);
        io_port_set_pin_high(BUZZER);
        delay_ms(BEEP_SOUND_LENGTH);
        io_port_set_pin_low(BUZZER);
        delay_ms(BEEP_SOUND_LENGTH);
        io_port_set_pin_high(BUZZER);
        delay_ms(BEEP_SOUND_LENGTH);
        io_port_set_pin_low(BUZZER);
        delay_ms(BEEP_SOUND_LENGTH);
        io_port_set_pin_high(BUZZER);
        delay_ms(BEEP_SOUND_LENGTH);
        io_port_set_pin_low(BUZZER);
        delay_ms(600);
    }
}

void inform_startup()
{
    delay_ms(500);
    io_port_set_pin_high(BUZZER);
    delay_ms(1000);
    io_port_set_pin_low(BUZZER);
}

int main(void)
{
    sevenSegmentDisplay.Init();
    InitBuzzer();
    keyPad.Init();
    uvLed.Init();
    InitPauseSwitch();

    realTimeClock.Init();
    realTimeClock.RegisterRTCCallback(rtc_callback_function);

    sei();

    inform_startup();
    sevenSegmentDisplay.SetStandBy(1);

    while (1)
    {
        current_key = keyPad.GetPressedKey();

        if (current_key != KEY_NONE)
        {
            delay_ms(250);
            ProcessKey();
        }

        if(IsPauseSwitchOn() == true)
        {
            if (countDownTimerState == COUNT_DOWN_TIMER_STATE_STARTED)
            {
                PauseCountDownTimer();
            }
        }
        else
        {
            if (countDownTimerState == COUNT_DOWN_TIMER_STATE_PAUSED)
            {
                StartCountDownTimer();
            }
        }

        if (beepBuzz == true)
        {
            BeepBuzzer();
            beepBuzz = false;
        }
    }
}

