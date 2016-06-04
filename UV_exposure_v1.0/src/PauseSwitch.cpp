/*
 * PauseSwitch.cpp
 *
 * Created: 10/12/2015 2:53:14 PM
 *  Author: Prabhus
 */ 

 #include <avr/io.h>
 #include <avr/interrupt.h>

 #include "PauseSwitch.h"

 pfnPauseSwitchStateChanged PauseSwitch::_pauseSwitchStateChangeHandler = 0;

 PauseSwitch::PauseSwitch()
 {
 }

 void PauseSwitch::Init()
 {
	 DDRD &= ~(1 << PD3); // make as input
	 PORTD |= (1 << PD3); // Enable internal pullup

	 GICR |= (1 << INT1);
	 MCUCR |= (1 << ISC10); // logical change will interrupt
 }

 bool PauseSwitch::IsOn()
 {
	 return (PIND & (1 << PD3));;
 }

 void PauseSwitch::RegisterPauseSwitchStateChangeHandler(pfnPauseSwitchStateChanged pauseSwitchStateChangeHandler)
 {
	 _pauseSwitchStateChangeHandler = pauseSwitchStateChangeHandler;
 }

 ISR(INT1_vect)
 {
	 if (PauseSwitch::_pauseSwitchStateChangeHandler != 0)
	 {
		  PauseSwitch::_pauseSwitchStateChangeHandler();
	 }
 }
