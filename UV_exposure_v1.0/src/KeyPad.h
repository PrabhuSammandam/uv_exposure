/*
* KeyPad.h
*
* Created: 10/12/2015 9:35:27 AM
*  Author: Prabhus
*/


#ifndef KEYPAD_H_
#define KEYPAD_H_

#define KEY_NONE							0
#define KEY_START_STOP					1
#define KEY_TIMER_UP						2
#define KEY_TIMER_DOWN					3
#define KEY_TIMER_MINUTE_SELECT		4
#define KEY_TIMER_PRESET		5

class KeyPad
{
    public:
    KeyPad();

    public:
    void Init();

    unsigned char GetPressedKey();
};



#endif /* KEYPAD_H_ */