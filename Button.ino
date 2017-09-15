/**
 * This is the test program for the Button library.
 *
 * @author Roland Rusch <roland@rusch.lu>
 */


#include "Arduino.h"
#include <Led.h>
#include "Button.h"


// use the on board Led
const int pinLed = LED_BUILTIN;
// Initialize the Led object
Led led(pinLed);

// Initialize the Button objects
const int pinB1 = 4;
Button b1(pinB1);
const int pinB2 = 5;
Button b2(pinB2, Button::PULLDOWN);

void keyDown(Button &button)
{
	// Erst nach 1000ms
	if( button.getPressedTime() > 1000) led.toggle();
}

void keyUp(Button &button)
{
	led.toggle();
}

void keyPressed(Button &button)
{
	// Erst nach 1000ms
	led.toggle();
}

void keyReleased(Button &button)
{
	led.toggle();
}

void keyOn(Button &button)
{
	led.setOn();
}

void keyOff(Button &button)
{
	led.setOff();
}



//The setup function is called once at startup of the sketch
void setup()
{
	// Add your initialization code here
	led.setup();
	b1.setup();
	b2.setup();
	// Test: onKeyDown() wird ausgeführt, während die Taste gedrückt ist
//	b1.onKeyDown(keyDown);
	
	// Test: onKeyUp() wird ausgeführt, während die Taste gedrückt ist
//	b1.onKeyUp(keyUp);
	
	// Test: onKeyPressed() wird ausgeführt, während die Taste gedrückt ist
//	b1.onKeyPressed(keyPressed);
	
	// Test: onKeyUp() wird ausgeführt, während die Taste gedrückt ist
//	b1.onKeyReleased(keyReleased);
	
	
	// Test: onKeyPressed() wird ausgeführt, während die Taste gedrückt ist
	b1.onKeyPressed(keyReleased);
	b2.onKeyPressed(keyReleased);

}



// The loop function is called in an endless loop
void loop()
{
	//Add your repeated code here
	led.update();
	b1.update();
	b2.update();
	
	// Test: isKeyDown() ist wahr, während die Taste gedrückt ist
//	b1.isKeyDown() ? led.setOn() : led.setOff();
	
	// Test: isKeyUp() ist wahr, während die Taste losgelassen ist
//	b1.isKeyUp() ? led.setOn() : led.setOff();
	
	// Test: isKeyPressed() ist während eines loop()'s wahr nach einer positiven Flanke
//	if( b1.isKeyPressed() ) led.toggle();
	
	// Test: isKeyPressed() ist während eines loop()'s wahr nach einer negativen Flanke
//	if( b1.isKeyReleased() ) led.toggle();
	

	
	
	
	
	
	
	
	delay(20);
}
