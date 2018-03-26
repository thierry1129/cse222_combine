#if 1
#include "Arduino.h"

#include"GarageHardware.h"

const int whitePin = D0;
 const int greenPin = D1;
 const int bluePin = D2;
 const int regularButton = D6;
 const int stopOpen = D5;
 const int stopClose = D4;
 const int faultSwitch = D3;

 bool closedDoor = true;
 bool openedDoor = false;

 bool autoCloseDoorbool = false;
 int autoCloseDoorTime = 0;

 bool garageLightStat = false;

 int state = 0;
 boolean buttonPressed;
 int buttonTime;
 boolean trigger = true;
 int lightBrightness = 255;
 Timer dimLightTimer(100, fadeLight);

 Timer stopDimLightTimer(5000, stopDimLightTimerFunction);

 Timer autoCloseDoorTimer(100000,closeGarageFromTimer,true);


/**
 * Setup the door hardware (all I/O should be configured here)
 *
 * This routine should be called only once from setup()
 */

void setupHardware() {
  Serial.begin(9600);
  publishStateString(state,garageLightStat);


  Particle.function("webRequest", webRequest);
  //Particle.function("autoCloseDoorF", autoCloseDoorF);
  Serial.println("trying to set hardware");
  pinMode(whitePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  //SETTING UP BUTTONS AND SWITCHES

  pinMode(regularButton, INPUT_PULLUP);
  pinMode(stopOpen, INPUT_PULLUP);
  pinMode(stopClose,INPUT_PULLUP);
  pinMode(faultSwitch,INPUT_PULLUP);
  // TODO
}

void closeGarageFromTimer(){

  //if (autoCloseDoorbool){
    autoCloseDoorTimer.stop();
    state = 4;
   //Particle.publish("State", String(state));

   //setLight(true);// turn on garage light, because we are mid opening

   startMotorClosing();
   Serial.println("from timer the door is door going to mid closing state ");
   //
   //timer.stop();
//}

}

void publishStateString(int state, boolean lightOn){
  String concatString = String(state);
  if (lightOn == true){
    concatString  = concatString + "t";
  }else{
    concatString = concatString + "f";
  }

  if (autoCloseDoorbool == true){
  concatString = concatString + "t";
  }else{
  concatString = concatString +"f";
  }
  concatString = concatString + String(autoCloseDoorTime);

//Particle.publish("State",state);
            Particle.publish("State",concatString);
}

void stopDimLightTimerFunction(){
dimLightTimer.stop();
stopDimLightTimer.stop();
garageLightStat = false;
publishStateString(state,garageLightStat);
lightBrightness = 255;
}

void fadeLight(){


  if (lightBrightness<=0){
    analogWrite(whitePin,0);
    garageLightStat = false;
    // now light is fully off
  }

  lightBrightness = lightBrightness - 6;

    analogWrite(whitePin, lightBrightness);
    dimLightTimer.start();

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

 }

 void turnOff(){
  setLight(false);
  garageLightStat = false;
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
   garageLightStat = true;
   closedDoor = false;
   Serial.println("trying to motor open");
   publishStateString(state,garageLightStat);
   //Particle.publish("State",String(state));
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
    garageLightStat = true;
   Serial.println("trying to motor close");
   publishStateString(state,garageLightStat);
  // Particle.publish("State",String(state));
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
     garageLightStat = true;
   publishStateString(state,garageLightStat);
   //Particle.publish("State",String(state));
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
     garageLightStat = true;
      publishStateString(state,garageLightStat);

    //digitalWrite(whitePin,HIGH);
 }
 else{
    analogWrite(whitePin,0);
     garageLightStat = false;
       publishStateString(state,garageLightStat);
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
  // Particle.publish("State", String(state));
   //setLight(true);// turn on garage light, because we are mid opening
   startMotorOpening();
   Serial.println("door going to mid opening state ");
   //timer.stop();

 }
 void midClose(){
   state = 4;
   //Particle.publish("State", String(state));

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
     //Particle.publish("State",String(state));
     stopMotor();
     Serial.println("door at open fault state");
     sendDebug("open fault");
     dimLightTimer.start();
     stopDimLightTimer.start();
     //timer.start();
   }

 }

 void closeFault(){
 if(isFaultActive() && state == 4){
     state = 5; // this is the closing fault state
     //Particle.publish("State",String(state));
     stopMotor();
     Serial.println("door at close fault state");
     sendDebug("close fault");
          dimLightTimer.start();
          stopDimLightTimer.start();
     //timer.start();
   }

 }

 void faultEnd(){

   // the only condition for a fault to end is to press the regular button
   if (isButtonPressed() == true && state == 5)// now we are in close fault
   {
     //timer.stop();
     state = 4;
     //Particle.publish("State",String(state));
     startMotorClosing();
     // go back to mid close state
     Serial.println("door exiting close fault, going back to closing ");

   }else if (isButtonPressed() == true && state == 2){
     //timer.stop();
     state = 1;  // go back to mid open state ;
     //Particle.publish("State",String(state));
     startMotorOpening();
     Serial.println("door exiting opening fault, going back to mid Particle ");
   }
 }

 void opened(){
   // if I am in mid open state and I read the fully open button pressed
   if (state == 1 && isDoorFullyOpen()){
     state = 3;
     //Particle.publish("state", String(state));

     stopMotor();
     Serial.println("door at opened state");
         dimLightTimer.start();
         stopDimLightTimer.start();
         if (autoCloseDoorbool == true){
                autoCloseDoorTimer.start();
                }
     //timer.start();

   }
 }

 void closed (){
   if (state == 4 && isDoorFullyClosed()){
     state = 0 ;
     //Particle.publish("state", String(state));
     stopMotor();
     Serial.println("door at closed state");
         dimLightTimer.start();
         stopDimLightTimer.start();
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
   //Particle.publish("State", String(state));

   //timer.start();
   Serial.println("preparing to open door, only garage light is on, and turn off after 5 sec ");
         dimLightTimer.start();
         stopDimLightTimer.start();

 }
 void midClosePrepare(){
   state = 6;
   stopMotor();
   //Particle.publish("State", String(state));

   Serial.println("preparing to close door, only garage light is on, and turn off after 5 sec ");
       dimLightTimer.start();
       stopDimLightTimer.start();


 }

 int webRequest(String input){
   Serial.println("the input in web request is "+input);

     if (input == "regButton"){
     // now the regular door button is pressed
     changeState(state);
     return 1;

     }
     if (input == "initialState"){
       publishStateString(state,false);
       return 1;
       //Particle.publish("State", String(state));
     }
     if (input.charAt(0) == 'a'){

       autoCloseDoor(input.substring(1,input.length()));
       return 1;
     }
     if (input.charAt(0) == 'l'){

           if (input.charAt(1) == 'f'){
           setLight(false);
           garageLightStat = false;
           Serial.println("tryinggggggto turn light offffff");
           }else{
           setLight(true);
                      garageLightStat = true;
                      Serial.println("tryinggggggto turn light onnnnf");
           }
           return 1;
          }

     return -1;
 }

String timeString = "";
void autoCloseDoor (String input ){
  Serial.println("the input in autoCloseDoor is "+ input);
    if (input.charAt(0) == 't'){
        autoCloseDoorbool = true;
        timeString = input.substring(1,input.length());
        autoCloseDoorTime = timeString.toInt();
        Serial.println("the auto close door time is ");
        Serial.println(autoCloseDoorTime);

      

        autoCloseDoorTimer.changePeriod(autoCloseDoorTime*1000);

//        autoCloseDoorTimer.start();
//        Serial.println("timer started");

    }else{
        autoCloseDoorbool  = false;
        autoCloseDoorTime = 0;
        //reset timer if running, or start timer if stopped.

       //autoCloseDoorTimer.reset();



   }

 return ;


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
