#include "GarageHardware.h"



bool closedDoor = true;
bool openedDoor = false;

bool autoCloseDoorbool = false;
int autoCloseDoorTime = 0;

bool garageLightStat = false;

int state = 0;
boolean buttonPressed;
int buttonTime;
boolean trigger = true;
int lightMaxBright = 255;
int lightBrightness = 255;

int autoCloseLightTime = 10;

boolean autoLightTimerRunning = false;

Timer dimLightTimer(100, fadeLight);

Timer stopDimLightTimer(5000, stopDimLightTimerFunction);

Timer autoCloseDoorTimer(100000,closeGarageFromTimer,true);

Timer autoCloseLightTimer (autoCloseLightTime*1000,closeLightFromTimer);


void setup() {
  setupHardware();
  setupParticle();
}

void loop() {
openFault();
closeFault();
opened();
closed();
timingStart();
timingConfig();
}

void setupParticle() {
  Serial.begin(9600);
  publishStateString(state,garageLightStat);
  Particle.function("webRequest", webRequest);
  Particle.subscribe("State_rem_ini",iniRemoteHandler);
  Particle.subscribe("Terry_Garageremo",reHandler);
}




void turnLightPartialOn(){
  double percentPassed = lightMaxBright*100.0/255;
  garageLightStat = true;
   setLightPWM((int)percentPassed);
 Serial.println(" the state is "+String(state));
   if (state == 0 || state == 3){

     Serial.println("inside if stmt");
     autoLightTimerRunning = true;
     autoCloseLightTimer.start();

   }
    publishStateString(state,garageLightStat);

}
 void iniRemoteHandler(String event, String data){
   publishStateString(state,garageLightStat);
 }

 void reHandler(String event, String data){
   if (data == "doorPressed"){
     webRequest("regButton");
   }
   if (data == "lightPressed"){
     if (garageLightStat == true){
       setLight(false);
        publishStateString(state,false);
       garageLightStat = false;
     }else{
       turnLightPartialOn();
       garageLightStat = true;
     }
   }
 }

 void closeGarageFromTimer(){
    autoCloseDoorTimer.stop();
    state = 4;
    startMotorClosing();
    //setLight(true);
    turnLightPartialOn();
    garageLightStat = true;
    publishStateString(state,garageLightStat);
 }

 void closeLightFromTimer(){
     autoCloseLightTimer.stop();
     autoLightTimerRunning = false;
     dimLightTimer.start();
     stopDimLightTimer.start();
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
   Particle.publish("State_TEL_PHO",concatString);
 }

 void stopDimLightTimerFunction(){
   dimLightTimer.stop();
   stopDimLightTimer.stop();
   garageLightStat = false;
   publishStateString(state,garageLightStat);
   lightBrightness = lightMaxBright;
 }

 void fadeLight(){
   if (lightBrightness<=0){
     setLight(false);
     garageLightStat = false;
   }
   lightBrightness = lightBrightness - 6;
   double percentPassed = lightBrightness*100.0/255;
   setLightPWM((int)percentPassed);
   dimLightTimer.start();
 }

void midOpen(){
  autoCloseLightTimer.stop();
  state = 1;
  startMotorOpening();
  //setLight(true);
  turnLightPartialOn();
  garageLightStat = true;
  publishStateString(state,garageLightStat);
}

void midClose(){
  autoCloseLightTimer.stop();
  autoLightTimerRunning = false;
  state = 4;
  startMotorClosing();
  //setLight(true);
  turnLightPartialOn();
  garageLightStat = true;
  publishStateString(state,garageLightStat);
}

void openFault(){
  if (isFaultActive()&& state == 1){
    state =2; // entering in to open fault state
    stopMotor();
    //setLight(true);
    turnLightPartialOn();

    Serial.println("door at open fault state");
    sendDebug("open fault");
    garageLightStat = true;
    publishStateString(state,garageLightStat);
    autoLightTimerRunning = true;
    autoCloseLightTimer.start();
  }
}

void closeFault(){
  if(isFaultActive() && state == 4){
   state = 5; // this is the closing fault state
   stopMotor();
   //setLight(true);
   turnLightPartialOn();
   sendDebug("close fault");
   garageLightStat = true;
   publishStateString(state,garageLightStat);
   autoLightTimerRunning = true;
   autoCloseLightTimer.start();
  }
}

void faultEnd(){
  // the only condition for a fault to end is to press the regular button
  if (isButtonPressed() == true && state == 5){
        autoCloseLightTimer.stop();
        autoLightTimerRunning = false;
        state = 4;
  }else if (isButtonPressed() == true && state == 2){
        autoCloseLightTimer.stop();
        autoLightTimerRunning = false;
        state = 1;  // go back to mid open state ;
        startMotorOpening();
        //setLight(true);
        turnLightPartialOn();
        garageLightStat = true;
        publishStateString(state,garageLightStat);
  }
}

void opened(){
  // if I am in mid open state and I read the fully open button pressed
  if (state == 1 && isDoorFullyOpen()){
    state = 3;
    stopMotor();
    //setLight(true);
    turnLightPartialOn();
    garageLightStat = true;
    publishStateString(state,garageLightStat);
    autoLightTimerRunning = true;
    autoCloseLightTimer.start();
  if (autoCloseDoorbool == true){
     autoCloseDoorTimer.start();
   }
  }
}

void closed (){
  if (state == 4 && isDoorFullyClosed()){
    state = 0 ;
    stopMotor();
    //setLight(true);
    turnLightPartialOn();
    autoLightTimerRunning = true;
    autoCloseLightTimer.start();
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
  //setLight(true);
  turnLightPartialOn();
  garageLightStat = true;
  publishStateString(state,garageLightStat);
  autoLightTimerRunning = true;
  autoCloseLightTimer.start();
}

void midClosePrepare(){
  state = 6;
  stopMotor();
  //setLight(true);
  turnLightPartialOn();
  garageLightStat = true;
  publishStateString(state,garageLightStat);
  autoLightTimerRunning = true;
  autoCloseLightTimer.start();
}

int webRequest(String input){
    if (input == "regButton"){
    // now the regular door button is pressed
     changeState(state);
     return 1;
    }

    if (input == "initialState"){
      publishStateString(state,false);
      return 1;
    }

    if (input.charAt(0) == 'a'){
      autoCloseDoor(input.substring(1,input.length()));
      return 1;
    }

    if (input.charAt(0) == 'l'){
      if (input.charAt(1) == 'f'){
          setLight(false);
          garageLightStat = false;

          autoCloseLightTimer.stop();
          publishStateString(state,false);
       }else{
         //setLight(true);
         turnLightPartialOn();
           garageLightStat = true;
           publishStateString(state,garageLightStat);

       }
          return 1;
       }

     if (input.charAt(0) == 'o'){
           autoCloseLightTime = (input.substring(1,input.length())).toInt();
           autoCloseLightTimer.changePeriod(autoCloseLightTime*1000);
           return 1;
     }
     if (input.charAt(0) == 'b'){
       lightMaxBright = (input.substring(1,input.length())).toInt();
         return 1;
     }
    return -1;
}


String timeString = "";
void autoCloseDoor (String input ){
   if (input.charAt(0) == 't'){
       autoCloseDoorbool = true;
       timeString = input.substring(1,input.length());
       autoCloseDoorTime = timeString.toInt();
       autoCloseDoorTimer.changePeriod(autoCloseDoorTime*1000);

   }else{
       autoCloseDoorbool  = false;
       autoCloseDoorTime = 0;
  }

return ;


}
void timingConfig(){
  if (isButtonPressed() == true && buttonPressed == false){
    buttonTime = millis();
    trigger = false;
  }
}

void  timingStart() {
    if((millis() - buttonTime) > 100 ) {
       if (trigger == false) {
           changeState(state);
           trigger = true; // we have called trigger
       }
       if(buttonPressed!= isButtonPressed()) { // if the button is no longer pressed, change stat
            buttonPressed = false;
       }
   }
}
