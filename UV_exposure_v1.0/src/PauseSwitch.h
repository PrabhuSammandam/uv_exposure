/*
 * PauseSwitch.h
 *
 * Created: 10/12/2015 2:51:55 PM
 *  Author: Prabhus
 */ 


#ifndef PAUSESWITCH_H_
#define PAUSESWITCH_H_

#define PAUSE_SWITCH_OFF	 0
#define PAUSE_SWITCH_ON		 1

typedef void (*pfnPauseSwitchStateChanged)();

class PauseSwitch
{
	 public:
		  PauseSwitch();

	 public:
		  void Init();
		  bool IsOn();

		  static void RegisterPauseSwitchStateChangeHandler(pfnPauseSwitchStateChanged pauseSwitchStateChangeHandler);

	 public:
		  static pfnPauseSwitchStateChanged _pauseSwitchStateChangeHandler;
};



#endif /* PAUSESWITCH_H_ */