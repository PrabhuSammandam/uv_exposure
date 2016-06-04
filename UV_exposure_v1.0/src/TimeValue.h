/*
 * TimeValue.h
 *
 * Created: 10/11/2015 11:18:14 AM
 *  Author: Prabhus
 */ 


#ifndef TIMEVALUE_H_
#define TIMEVALUE_H_

class TimeValue
{
	 private:
		  unsigned char _minutes;
		  unsigned char _seconds;

	 public:
		  TimeValue();

	 public:
		  unsigned char GetSecond();
		  void SetSecond(unsigned char second);

		  unsigned char GetMinute();
		  void SetMinute(unsigned char minute);

		  void IncreaseSecond();
		  void DecreaseSecond(bool overroll = true);
		  void IncreaseMinute();
		  void DecreaseMinute(bool overroll = true);

		  bool IsValid();
		  void Reset();
};



#endif /* TIMEVALUE_H_ */