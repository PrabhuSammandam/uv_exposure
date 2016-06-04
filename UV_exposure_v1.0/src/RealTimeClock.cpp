/*
 * rtc.cpp
 *
 * Created: 10/11/2015 10:41:26 AM
 *  Author: Prabhus
 */ 

 #include "RealTimeClock.h"

 rtc_callback RealTimeClock::_cb_fcn = 0;

 RealTimeClock::RealTimeClock()
 {
	 
 }

 void RealTimeClock::Init()
 {
 	/*Disable Timer/Counter2 interrupts*/
	TIMSK	&=	~((1 << OCIE2) | (1 << TOIE2));

	/*	set Timer/Counter2 to be asynchronous from the CPU clock
		with a second external clock(32,768kHz)driving it.
	*/
	ASSR	|=	(1 << AS2);
    
	TCNT2	=	0x00;

	/*Wait until TCNT2 is updated*/
	while(ASSR & (1 << TCN2UB));
 }

 void RealTimeClock::Start()
 {
 	/*	prescale the timer to be clock source / 128 to make it
		exactly 1 second for every overflow to occur
	*/
	TCCR2	|=	((1 << CS22) | (1 << CS20));

	/*set 8-bit Timer/Counter2 Overflow Interrupt Enable*/
	TIMSK	|=	(1 << TOIE2);
 }

 void RealTimeClock::Stop()
 {
 	/*	prescale the timer to be clock source / 128 to make it
		exactly 1 second for every overflow to occur
	*/
	TCCR2	&=	~((1 << CS22) | (1 << CS20));

	/*set 8-bit Timer/Counter2 Overflow Interrupt Enable*/
	TIMSK	&=	~(1 << TOIE2);
 }

 void RealTimeClock::RegisterRTCCallback(rtc_callback callback_fcn)
 {
	 _cb_fcn = callback_fcn;
 }

 ISR(TIMER2_OVF_vect)
 {
	 if (RealTimeClock::_cb_fcn != 0)
	 {
		  RealTimeClock::_cb_fcn();
	 }
 }