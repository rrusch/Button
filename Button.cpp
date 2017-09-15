/**
 * Button library.
 *
 * @author Roland Rusch <roland@rusch.lu>
 */


#include "Button.h"


Button::Button(uint8_t pin, uint8_t mode)
{
	this->_pin=pin;
	pinMode(this->_pin, INPUT);
	mode==Button::PULLDOWN ? pulldown() : pullup(mode);
	
	this->_lastRunTime=0;
	this->_value=0;
	this->_previousValue=0;
	this->_lastPressed=0;
	this->_lastReleased=0;
	this->_numPressed=0;
	this->_numReleased=0;
	
	this->cb_onKeyDown=0;
	this->cb_onKeyUp=0;
	this->cb_onKeyPressed=0;
	this->cb_onKeyReleased=0;
	
	
};



bool Button::isPin()
{
	return this->_pin != NOT_A_PIN;
}



/**
 * Run the setup function.
 */
void Button::setup()
{
	if( !this->isPin() ) return;
	
};



void Button::pullup(uint8_t mode)
{
	this->_mode=Button::PULLUP;
	if(mode == Button::PULLUP_INTERNAL) 
	{
		digitalWrite(this->_pin, HIGH);
	}
}



void Button::pulldown(void)
{
	this->_mode=Button::PULLDOWN;
	digitalWrite(this->_pin, LOW);
}



void Button::update()
{
	this->_previousValue=this->_value;
	if( (Button::INTERVAL == 0) || ((millis() - this->_lastRunTime) >= Button::INTERVAL) )
	{
		this->_lastRunTime=millis();
		this->_value=(digitalRead(this->_pin) == this->_mode) ? 0 : 1;
		
		if( this->isKeyPressed() )
		{
			this->_lastPressed=this->_lastRunTime;
			this->_numPressed++;
			if( cb_onKeyPressed != 0 ) cb_onKeyPressed(*this);
		}
		
		if( this->isKeyReleased() )
		{
			this->_lastReleased=this->_lastRunTime;
			this->_numReleased++;
			if( cb_onKeyReleased != 0 ) cb_onKeyReleased(*this);
		}
		
		if( (cb_onKeyDown != 0) && this->isKeyDown()) cb_onKeyDown(*this);
		if( (cb_onKeyUp != 0) && this->isKeyUp()) cb_onKeyUp(*this);
		
	}
};



bool Button::_digitalWrite(uint8_t val)
{
	if( !this->isPin() ) return false;
	digitalWrite(this->_pin, val);
	return true;
}



bool Button::isKeyDown()
{
	return this->_value == HIGH;
}



bool Button::isKeyUp()
{
	return this->_value == LOW;
}



bool Button::isKeyPressed()
{
	return this->_value > this->_previousValue;
}



bool Button::isKeyReleased()
{
	return this->_value < this->_previousValue;
}



void Button::onKeyDown(buttonEventHandler handler)
{
	cb_onKeyDown = handler;
}



void Button::onKeyUp(buttonEventHandler handler)
{
	cb_onKeyUp = handler;
}



void Button::onKeyPressed(buttonEventHandler handler)
{
	cb_onKeyPressed = handler;
}



void Button::onKeyReleased(buttonEventHandler handler)
{
	cb_onKeyReleased = handler;
}



unsigned long Button::getPressedTime()
{
	return ( millis() - this->_lastPressed );
}



