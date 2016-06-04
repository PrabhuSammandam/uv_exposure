/*
 * rtc.h
 *
 * Created: 10/11/2015 10:39:51 AM
 *  Author: Prabhus
 */ 


#ifndef RTC_H_
#define RTC_H_

#include <avr/io.h>
#include <avr/interrupt.h>

typedef void(*rtc_callback)();

class RealTimeClock
{
	 public:
		  RealTimeClock();

	 public:
		  void Init();
		  void Start();
		  void Stop();

		  static void RegisterRTCCallback(rtc_callback callback_fcn);

	 public:
		  static rtc_callback _cb_fcn;
};


#endif /* RTC_H_ */