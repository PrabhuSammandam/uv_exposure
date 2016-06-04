/*
 * KeyPad.cpp
 *
 * Created: 10/12/2015 9:39:03 AM
 *  Author: Prabhus
 */ 

 #include <avr/io.h>
 #include <avr/interrupt.h>

 #include "KeyPad.h"
 #include "io_port.h"

 extern void delay_ms(unsigned int   ms_delay);

 #define KEY_PRESET_PIN IOPORT_CREATE_PIN(PORT_B, 2)
 #define KEY_START_PIN IOPORT_CREATE_PIN(PORT_B, 4)
 #define KEY_UP_PIN IOPORT_CREATE_PIN(PORT_B, 5)
 #define KEY_DOWN_PIN IOPORT_CREATE_PIN(PORT_C, 0)
 #define KEY_MIN_SELECT_PIN IOPORT_CREATE_PIN(PORT_C, 1)

 KeyPad::KeyPad()
 {
 }

 void KeyPad::Init()
 {
    /* set all key pins as input*/
    io_port_set_pin_input(KEY_PRESET_PIN);
    io_port_set_pin_input(KEY_START_PIN);
    io_port_set_pin_input(KEY_UP_PIN);
    io_port_set_pin_input(KEY_DOWN_PIN);
    io_port_set_pin_input(KEY_MIN_SELECT_PIN);

    /* set all key pins internal pull up*/
    io_port_set_pin_high(KEY_START_PIN);
    io_port_set_pin_high(KEY_PRESET_PIN);
    io_port_set_pin_high(KEY_UP_PIN);
    io_port_set_pin_high(KEY_DOWN_PIN);
    io_port_set_pin_high(KEY_MIN_SELECT_PIN);
 }

 unsigned char KeyPad::GetPressedKey()
 {
 	 if (io_port_is_pin_low(KEY_START_PIN))
 	 {
	 	 delay_ms(25);

	 	 if (io_port_is_pin_low(KEY_START_PIN))
	 	 {
		 	 return KEY_START_STOP;
	 	 }
 	 }

	 if (io_port_is_pin_low(KEY_UP_PIN))
	 {
		  delay_ms(25);

		  if (io_port_is_pin_low(KEY_UP_PIN))
		  {
			  	return KEY_TIMER_UP;
		  }
	 }

	 if (io_port_is_pin_low(KEY_DOWN_PIN))
	 {
		 delay_ms(25);

		 if (io_port_is_pin_low(KEY_DOWN_PIN))
		 {
			 return KEY_TIMER_DOWN;
		 }
	 }
	 if (io_port_is_pin_low(KEY_MIN_SELECT_PIN))
	 {
		 delay_ms(25);

		 if (io_port_is_pin_low(KEY_MIN_SELECT_PIN))
		 {
			 return KEY_TIMER_MINUTE_SELECT;
		 }
	 }

	 if (io_port_is_pin_low(KEY_PRESET_PIN))
	 {
    	 delay_ms(25);

    	 if (io_port_is_pin_low(KEY_PRESET_PIN))
    	 {
        	 return KEY_TIMER_PRESET;
    	 }
	 }

	 return KEY_NONE;
 }