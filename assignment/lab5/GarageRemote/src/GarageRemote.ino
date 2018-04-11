/*
 * Project GarageRemote
 * Description:
 * Author:
 * Date:
 */
 #include "Adafruit_SSD1306/Adafruit_SSD1306.h"
 #define OLED_DC     D0
 #define OLED_CS     D1
 #define OLED_RESET  D2
 Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);
 int  x, minX; // variables for scrolling code
const int doorButton = D4;
const int lightButton = D3;
 boolean buttonPressed = false;
 boolean lightButPressed;
 int buttonTime;
 int lightButtonTime;
boolean trigger = true;
boolean lightTrigger = true;
boolean initialState = true;
// setup() runs once, when the device is first turned on.
String processedCombined = "something wrong when processing state";
void setup() {
  Serial.begin(9600);
    pinMode(doorButton, INPUT_PULLUP);
      pinMode(lightButton, INPUT_PULLUP);
      pinMode(D5,OUTPUT);
  // Put initialization like pinMode and begin functions here.
 display.begin(SSD1306_SWITCHCAPVCC);
 display.setTextSize(7);       // text size
 display.setTextColor(WHITE); // text color
 display.setTextWrap(false);
 x    = display.width(); // set scrolling frame to display width
 minX = -1500; // 630 = 6 pixels/character * text size 7 * 15 chara
 Particle.subscribe("State_TEL_PHO", newStateHandler);
 Particle.publish("State_rem_ini","initalLaunch");
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
   if (digitalRead(doorButton)==LOW){
     return true;
   }else{
     return false;
   }

 }

boolean isLightPressed(){
  if (digitalRead(lightButton)==LOW){
    //Serial.println("regular button pressed");
    return true;
  }else{
    return false;
  }

}

// the handler to print new state to the OLED board
void newStateHandler(String event, String data){
  if (initialState == true){
    initialState = false;
  }
    String stateReceived0 = String(data.charAt(0));
    int stateReceived = stateReceived0.toInt();
    String processedState;
    String lightState = String(data.charAt(1));
    String processedLight ;


    if (lightState == "t"){
      processedLight = " light on ";

    }else if (lightState == "f"){
      processedLight = " light f";
    }

    switch(stateReceived){
      case 0:
        processedState = "door closed";
        break;

      case 1:
        processedState = "opening";
        break;

      case 2:
          processedState = "open fault";
          break;

      case 3:
          processedState = "opened";
          break;

      case 4:
            processedState = "closing";
            break;
      case 5:
            processedState = "close fault";
            break;

      case 6:
              processedState = "close prepare";
              break;

      case 7:
              processedState = "open prepare";
              break;



    }

    processedCombined = processedState + processedLight;

    //processedCombined = data;
     display.print(processedCombined);

}

void doortimingConfig(){
  if (digitalRead(doorButton)==LOW && buttonPressed == false){
    Serial.println("trying to see what triggered midOpen call");
    buttonPressed = true;
    buttonTime = millis();
    trigger = false;
  }
}

void  doortimingStart() {
    if((millis() - buttonTime) > 100 ) {
       if (trigger == false && initialState == false) {
         Particle.publish("Terry_Garageremo","doorPressed");
         Serial.println("doorPressed " );
           //changeState(state);
          // setLight(true); // call to change light state
          trigger = true; // we have called trigger
       }
       if(buttonPressed!= isButtonPressed()) { // if the button is no longer pressed, change state

            buttonPressed = false;
       }
   }
}

void lighttimingConfig(){
  if (isLightPressed() == true && lightButPressed == false && initialState == false){
    lightButPressed = true;
    lightButtonTime = millis();
    lightTrigger = false;
  }
}

void  lighttimingStart() {
    if((millis() - lightButtonTime) > 100 ) {
       if (lightTrigger  == false && initialState == false) {
        Particle.publish("Terry_Garageremo","lightPressed");
           //changeState(state);
          lightTrigger = true; // we have called trigger
       }
       if(lightButPressed!= isLightPressed()) { // if the button is no longer pressed, change state

            lightButPressed = false;
       }
   }
}


// loop() runs over and over again, as quickly as it can execute.
void loop() {
  display.clearDisplay();
  display.setCursor(x/2,7);
  display.print(processedCombined);
  display.display();
  if (--x<minX) x = display.width()*2;
  doortimingConfig();
  doortimingStart();
  lighttimingConfig();
  lighttimingStart();
}
