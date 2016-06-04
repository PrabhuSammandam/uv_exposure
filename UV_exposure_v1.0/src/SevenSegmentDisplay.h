/*
 * SevenSegDisp.h
 *
 * Created: 10/11/2015 7:48:20 AM
 *  Author: Prabhus
 */ 


#ifndef SEVENSEGDISP_H_
#define SEVENSEGDISP_H_

#include "TimeValue.h"

class SevenSegmentDisplay
{
	 public:
		  SevenSegmentDisplay();

	 public:
		  void Init();

		  void DisplayDigitValue(unsigned char displayValue);
		  void SelectDisplayDigit(unsigned char displayDigit);

		  void RefreshDisplay();

		  void SetDigit(unsigned char digitIndex, unsigned char digitValue);

		  void SetTime(TimeValue& timeValue);

		  void SetNumber(unsigned short num);

          void SwitchOffDisplay();

          void SetStandBy(uint8_t is_standby);
		  
	 private:
		  void InitDisplayTimer();

	 private:
		  unsigned char _digits[4];
		  unsigned char _cur_display_digit;

};

#endif /* SEVENSEGDISP_H_ */