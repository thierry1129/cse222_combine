#if 0
#include "Arduino.h"

#include"GarageHardware.h"

const int whitePin = D0;
 const int greenPin = D1;
 const int bluePin = D2;
 const int regularButton = D6;
 const int stopOpen = D5;
 const int stopClose = D4;
 const int faultSwitch = D3;

 void setupHardware() {
   Serial.begin(9600);
  //  publishStateString(state,garageLightStat);
  //  Particle.function("webRequest", webRequest);
   pinMode(whitePin, OUTPUT);
   pinMode(greenPin, OUTPUT);
   pinMode(bluePin, OUTPUT);



   pinMode(regularButton, INPUT_PULLUP);
   pinMode(stopOpen, INPUT_PULLUP);
   pinMode(stopClose,INPUT_PULLUP);
   pinMode(faultSwitch,INPUT_PULLUP);


 }



/**
 * Return true if the door open/close button is pressed
 *
 * Note: this is directly based on hardware.  No debouncing or
 *       other processing is performed.
 *
 * return  true if buttons is currently pressed, false otherwise
 */
 boolean isButtonPressed() {
   if (digitalRead(regularButton)==LOW){
     return true;
   }else{
     return false;
   }
 }


/**
 * Return true if the door is fully closed
 *
 * Note: This is directly based on hardware.  No debouncing or
 *       other processing is performed.
 *
 * return  true if the door is completely closed, false otherwise
 */
 boolean isDoorFullyClosed() {
   if (digitalRead(stopClose) == LOW){
     return true;
   }else{
     return false;
   }
 }


/**
 * Return true if the door has experienced a fault
 *
 * Note: This is directly based on hardware.  No debouncing or
 *       other processing is performed.
 *
 * return  true if the door is has experienced a fault
 */
 boolean isFaultActive() {
   if (digitalRead(faultSwitch) == LOW){
     return true;
   }else{
     return false;
   }
 }

/**
 * Return true if the door is fully open
 *
 * Note: This is directly based on hardware.  No debouncing or
 *       other processing is performed.
 *
 * return  true if the door is completely open, false otherwise
 */
 boolean isDoorFullyOpen() {
   if (digitalRead(stopOpen) == LOW){
     return true;
   }else{
     return false;
   }
 }


/**
 * This function will start the motor moving in a direction that opens the door.
 *
 * Note: This is a non-blocking function.  It will return immediately
 *       and the motor will continue to opperate until stopped or reversed.
 *
 * return void
 */
 void startMotorOpening() {
   digitalWrite(greenPin,HIGH);

 }

/**
 * This function will start the motor moving in a direction closes the door.
 *
 * Note: This is a non-blocking function.  It will return immediately
 *       and the motor will continue to opperate until stopped or reversed.
 *
 * return void
 */
 void startMotorClosing() {
   digitalWrite(bluePin,HIGH);



 }

/**
 * This function will stop all motor movement.
 *
 * Note: This is a non-blocking function.  It will return immediately.
 *
 * return void
 */
 void stopMotor() {
   digitalWrite(greenPin,LOW);
   digitalWrite(bluePin,LOW);
 }

/**
 * This function will control the state of the light on the opener.
 *
 * Parameter: on: true indicates the light should enter the "on" state;
 *                false indicates the light should enter the "off" state
 *
 * Note: This is a non-blocking function.  It will return immediately.
 *
 * return void
 */
 void setLight(boolean on) {
  if(on == true){
    analogWrite(whitePin,255);

 }
  else{
    analogWrite(whitePin,0);
  }
 }




/**
 * This function will control the state of the light on the opener.
 *
 * Parameter: cycle (0-100).  0 indicates completely Off, 100 indicates completely on.
 *            intermediate values are the duty cycle (as a percent)
 *
 * Note: This is a non-blocking function.  It will return immediately.
 *
 * return void
 */
void setLightPWM(int cyclePct) {

  double data;
  if(cyclePct == 0)
    data = 0;
  else if(cyclePct == 100)
    data = 255;
  else if(cyclePct>100)
    data = 0;
  else
    data = cyclePct/100.0*255;

  analogWrite(whitePin,(int)data);


}

/**
 * This function will send a debugging message.
 *
 * Parameter: message. The message (no more tha 200 bytes)
 *
 * Note: This is a non-blocking function.  It will return immediately.
 *
 * return void
 */
 void sendDebug(String message) {
   Serial.println(message);
 }



#endif
