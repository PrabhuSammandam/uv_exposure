/*
 * UvLed.cpp
 *
 * Created: 10/12/2015 1:39:21 PM
 *  Author: Prabhus
 */ 
#include <avr/io.h>
#include "UvLed.h"
#include "io_port.h"    

#define UV_LED IOPORT_CREATE_PIN(PORT_B, 3)

void UvLed::Init()
{
    io_port_set_pin_output(UV_LED);
    io_port_set_pin_low(UV_LED);
}

void UvLed::Start()
{
    io_port_set_pin_high(UV_LED);
}

void UvLed::Stop()
{
    io_port_set_pin_low(UV_LED);
}