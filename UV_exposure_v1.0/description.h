/*
 * description.h
 *
 * Created: 10/11/2015 12:49:42 PM
 *  Author: Prabhus
 */ 


#ifndef DESCRIPTION_H_
#define DESCRIPTION_H_

/*
 * 1        -   RESET
 * 2 PD0    -   SEGMENT A
 * 3 PD1    -   SEGMENT B
 * 4 PD2    -   SEGMENT C
 * 5 PD3    -   SEDMENT D
 * 6 PD4    -   SEGMENT E
 * 7        -   VCC
 * 8        -   GND
 * 9        -   XTAL1
 * 10       -   XTAL2
 * 11 PD5   -   SEGMENT F
 * 12 PD6   -   SEGMENT G
 * 13 PD7   -   PAUSE
 * 14       -
 * 15 PB1   -   BUZZER
 * 16 PB2   -   KEY PRESET
 * 17 PB3   -   UV LED
 * 18 PB4   -   KEY START
 * 19 PB5   -   KEY UP
 * 20       -   AVCC
 * 21       -
 * 22       -   GND
 * 23 PC0   -   KEY DOWN
 * 24 PC1   -   KEY MIN_SELECT
 * 25 PC2   -   DIGIT_4
 * 26 PC3   -   DIGIT_3
 * 27 PC4   -   DIGIT_2
 * 28 PC5   -   DIGIT_1
 *
 * uC           =   ATMEGA8L
 * Clock        =   Internal 8Mhz RC oscillator
 * Low Fuse     =   0xE4
 * High Fuse    =   0xc9
 *
1.	 Internal 8MHZ oscillator.
2.	 Timer2 for RTC.
3.	 Timer0 for display refresh.

Timer0:
	 Clock Source	 :	  Internal 8MHZ
	 Prescale			 :	  64

	 Timer0 input => 8000000/64 => 125000 Hz => 0.000008 => 8 uS
	 Timer0 interrupt => 256 * 8uS => 2.048 mS

	 Each digit got refreshed by 2.048 mS.

Timer2:
	 Clock Source	 :	  32.768kHz 
	 Prescale		 :	  128

	 Timer2 input => 32768/128 => 256 => 0.00390625

	 Timer2 interrupt => 256 * 0.00390625 => 1 Sec

*/



#endif /* DESCRIPTION_H_ */