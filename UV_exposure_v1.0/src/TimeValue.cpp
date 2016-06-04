/*
 * TimeValue.cpp
 *
 * Created: 10/11/2015 11:20:57 AM
 *  Author: Prabhus
 */ 

 #include "TimeValue.h"

TimeValue::TimeValue()
{
	 _seconds = 0;
	 _minutes = 0;
}

unsigned char TimeValue::GetSecond()
{
	 return _seconds;
}

void TimeValue::SetSecond(unsigned char second)
{
	 _seconds = second;
}

unsigned char TimeValue::GetMinute()
{
	 return _minutes;
}

void TimeValue::SetMinute(unsigned char minute)
{
	 _minutes = minute;
}

void TimeValue::IncreaseMinute()
{
	 if (_minutes == 99)
	 {
		  _minutes = 0;
	 }
	 else
	 {
		  _minutes++;
	 }
}

void TimeValue::DecreaseMinute(bool overroll)
{
	 if (_minutes == 0)
	 {
		  if (overroll == true)
		  {
		  	  _minutes = 99;
	 	  }
	 }
	 else
	 {
		  _minutes--;
	 }
}
 
void TimeValue::IncreaseSecond()
{
	 if (_seconds == 59)
	 {
		  _seconds = 0;

		  IncreaseMinute();
	 }
	 else
	 {
		  _seconds++;
	 }
}

void TimeValue::DecreaseSecond(bool overroll)
{
	 if(_seconds == 0)
	 {
		  _seconds = 59;

		  DecreaseMinute(overroll);
	 }
	 else
	 {
		  _seconds--;
	 }
}

bool TimeValue::IsValid()
{
	 if ((_minutes > 0) || (_seconds > 0))
	 {
		  return true;
	 }

	 return false;
}

void TimeValue::Reset()
{
	 _minutes = 0;
	 _seconds = 0;
}
