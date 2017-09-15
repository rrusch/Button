/**
 * Button library
 *
 * @author Roland Rusch <roland@rusch.lu>
 * @version 0.0.1
 */


#ifndef RRUSCH_BUTTON_H
#define RRUSCH_BUTTON_H

#include <Arduino.h>


class Button;
typedef void (*buttonEventHandler)(Button&);


class Button
{
public:
	static const uint8_t PULLUP = HIGH;
	static const uint8_t PULLUP_INTERNAL = 2;
	static const uint8_t PULLDOWN = LOW;
	
public:
	Button(uint8_t pin, uint8_t mode = Button::PULLUP_INTERNAL);
	void setup();
	void update();
	bool isPin();
	void pullup(uint8_t mode = Button::PULLUP_INTERNAL);
	void pulldown();
	
	bool isKeyDown();
	bool isKeyUp();
	bool isKeyPressed();
	bool isKeyReleased();
	
	void onKeyDown(buttonEventHandler handler);
	void onKeyUp(buttonEventHandler handler);
	void onKeyPressed(buttonEventHandler handler);
	void onKeyReleased(buttonEventHandler handler);
	
	unsigned long getPressedTime();
	
private:
	static const unsigned long INTERVAL = 0;
	bool _digitalWrite(uint8_t val);
	uint8_t _pin;
	uint8_t _mode;
	unsigned long _lastRunTime;
	
	int _value;
	int _previousValue;
	
	unsigned long _lastPressed;
	unsigned long _numPressed;
	unsigned long _lastReleased;
	unsigned long _numReleased;
	
	buttonEventHandler cb_onKeyDown;
	buttonEventHandler cb_onKeyUp;
	buttonEventHandler cb_onKeyPressed;
	buttonEventHandler cb_onKeyReleased;
	
};




#endif /* RRUSCH_BUTTON_H */
