#if 1
#include "Arduino.h"

#include"GarageHardware.h"

/**
 * Setup the door hardware (all I/O should be configured here)
 *
 * This routine should be called only once from setup()
 */
 const int whitePin = D0;
 const int greenPin = D1;
 const int bluePin = D2;
 const int regularButton = D6;
 const int stopOpen = D5;
 const int stopClose = D4;
 const int faultSwitch = D3;

 bool closedDoor = true;
 bool openedDoor = false;

 int state = 0;
 boolean buttonPressed;
 int buttonTime;
 boolean trigger = true;

void setupHardware() {
  Serial.begin(9600);
  Particle.publish("State",String(state));
  Serial.println("trying to set hardware");
  pinMode(whitePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  //SETTING UP BUTTONS AND SWITCHES

  pinMode(regularButton, INPUT_PULLUP);
  pinMode(stopOpen, INPUT_PULLUP);
  pinMode(stopClose,INPUT_PULLUP);
  pinMode(faultSwitch,INPUT_PULLUP);
}

void fadeLight(){
  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
    analogWrite(whitePin, fadeValue);
    delay(100);
  }
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
    //Serial.println("regular button pressed");
    return true;
  }else{
    return false;
  }
  // TODO
}

void turnOff(){
  setLight(false);
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
    closedDoor = true;
    openedDoor = false;
    Serial.println("isDoorFullyClosed");
    return closedDoor;
  }
  return closedDoor;
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
    openedDoor = true;
    closedDoor = false;
    Serial.println("isDoorFullyOpen");
    return openedDoor;
  }
  return openedDoor;
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
  setLight(true);
  closedDoor = false;
  Serial.println("trying to motor open");
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
  openedDoor = false;
  setLight(true);
  Serial.println("trying to motor close");
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
  Serial.println("stop motor");
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
   //digitalWrite(whitePin,HIGH);
}
else{
   analogWrite(whitePin,0);
   //digitalWrite(whitePin,LOW);
 }
}

void setOpeningLight (boolean on ){
  if(on == true){
    digitalWrite(greenPin,HIGH);
  }
  else{
    digitalWrite(greenPin,LOW);
  }
}

void setClosingLight(boolean on){
  if(on == true){
    digitalWrite(bluePin,HIGH);
  }
  else
  {
digitalWrite(bluePin,LOW);
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
  // TODO
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

void midOpen(){
  // in mid open state
Serial.println("old state is ");
Serial.print(state);
  state = 1;
  Particle.publish("state", String(state));
  //setLight(true);// turn on garage light, because we are mid opening
  startMotorOpening();
  Serial.println("door going to mid opening state ");
  //timer.stop();

}
void midClose(){
  state = 4;
  Particle.publish("state", String(state));

  //setLight(true);// turn on garage light, because we are mid opening

  startMotorClosing();
  Serial.println("door going to mid closing state ");
  //
  //timer.stop();

}

void openFault(){
  if (isFaultActive()&& state == 1){
    state =2; // entering in to open fault state
    // stop motor, and set timer to close garage light
    stopMotor();
    Serial.println("door at open fault state");
    sendDebug("open fault");
    fadeLight();
    //timer.start();
  }

}

void closeFault(){
if(isFaultActive() && state == 4){
    state = 5; // this is the closing fault state
    stopMotor();
    Serial.println("door at close fault state");
    sendDebug("close fault");
        fadeLight();
    //timer.start();
  }

}

void faultEnd(){

  // the only condition for a fault to end is to press the regular button
  if (isButtonPressed() == true && state == 5)// now we are in close fault
  {
    //timer.stop();
    state = 4;
    startMotorClosing();
    // go back to mid close state
    Serial.println("door exiting close fault, going back to closing ");

  }else if (isButtonPressed() == true && state == 2){
    //timer.stop();
    state = 1;  // go back to mid open state ;
    startMotorOpening();
    Serial.println("door exiting opening fault, going back to mid Particle ");
  }
}

void opened(){
  // if I am in mid open state and I read the fully open button pressed
  if (state == 1 && isDoorFullyOpen()){
    state = 3;
    Particle.publish("state", String(state));
    stopMotor();
    Serial.println("door at opened state");
    fadeLight();
    //timer.start();

  }
}

void closed (){
  if (state == 4 && isDoorFullyClosed()){
    state = 0 ;
    Particle.publish("state", String(state));
    stopMotor();
    Serial.println("door at closed state");
    fadeLight();
    //timer.start();

  }
}
void changeState(int oldState){
  switch (oldState){
    case 0:
      midOpen();
      break;

    case 1: // old state is mid open, then press button
    // new state is mid close prepare
      midClosePrepare();
      break;
    case 3: // old state is fully opened, nid to mid close
      midClose();
      break;
    case 4: // old state is mid close, new state is mid open
    // new state should be before mid open
      midOpenPrepare();
      break;
    case 6:
      midClose();
      break;
    case 7:
      midOpen();
      break;
    //fault ones could be wrong
    case 2:
    //inside open fault, press button
    // go back to mid open
      midOpen();
      break;
    case 5:
      midClose();
      break;




  }
}

void midOpenPrepare(){
  state = 7;
  stopMotor();
  Particle.publish("state", String(state));

  //timer.start();
  Serial.println("preparing to open door, only garage light is on, and turn off after 5 sec ");
    fadeLight();
}
void midClosePrepare(){
  state = 6;
  stopMotor();
  Particle.publish("state", String(state));
    //  fadeLight();
//  timer.start();
  Serial.println("preparing to close door, only garage light is on, and turn off after 5 sec ");
  fadeLight();

}
void timingConfig(){
  if (isButtonPressed() == true && buttonPressed == false){
    Serial.println("trying to see what triggered midOpen call");
    buttonPressed = true;
    buttonTime = millis();
    trigger = false;
  }
}

void  timingStart() {
    if((millis() - buttonTime) > 100 ) {
       if (trigger == false) {
         Serial.println("before changing state in timing start");
         Serial.print(state);
           changeState(state);
          // setLight(true); // call to change light state
          trigger = true; // we have called trigger
       }
       if(buttonPressed!= isButtonPressed()) { // if the button is no longer pressed, change state

            buttonPressed = false;
       }
   }
}

#endif
