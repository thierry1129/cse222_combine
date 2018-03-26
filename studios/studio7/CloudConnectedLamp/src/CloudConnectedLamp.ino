/*
 * Project CloudConnectedLamp
 * Description:
 * Author:
 * Date:
 */
 int redPin = A4;    // RED pin of the LED to PWM pin **A4**
 int greenPin = D0;  // GREEN pin of the LED to PWM pin **D0**
 int bluePin = D1;   // BLUE pin of the LED to PWM pin **D1**

 int buttonPin = D5;
int buttonState = LOW;

 int redValue = 0; // Full brightness for an Cathode RGB LED is 0, and off 255
 int greenValue = 0; // Full brightness for an Cathode RGB LED is 0, and off 255
 int blueValue = 0; // Full brightness for an Cathode RGB LED is 0, and off 255</td>
 bool lightStat = true;

  long lastDebounceTime = 0;
  long debounceDelay = 50;

// setup() runs once, when the device is first turned on.
void setup() {

pinMode(redPin,OUTPUT);
pinMode(greenPin,OUTPUT);
pinMode(bluePin,OUTPUT);

pinMode(buttonPin,INPUT);
analogWrite(redPin,redValue);
analogWrite(bluePin,blueValue);
analogWrite(greenPin,greenValue);
analogWrite(buttonPin,buttonState);
bool success = Particle.function("led", setLampPower);


}
  // Put initialization like pinMode and begin functions here.

int setLampPower(String state){
  if (state=="true"){
    lightStat = true;
    analogWrite(redPin,0);
    analogWrite(bluePin,0);
    analogWrite(greenPin,0);
}else{
  lightStat = false;
  analogWrite(redPin,255);
  analogWrite(bluePin,255);
  analogWrite(greenPin,255);
}

}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.
  buttonState = digitalRead(buttonPin);
  if ((millis()-lastDebounceTime)>debounceDelay){
    if ((buttonState == HIGH)&& (lightStat == false)){
        setLampPower("true");
        Serial.println("trying to turn on lamp");

        lastDebounceTime = millis();

    }else if ((buttonState == HIGH) && (lightStat == true)){
      setLampPower("false");
        Serial.println("trying to turn off lamp");
      lastDebounceTime = millis();
    }
  }


}
