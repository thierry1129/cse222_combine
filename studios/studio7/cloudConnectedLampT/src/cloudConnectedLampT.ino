/*
 * Project cloudConnectedLampT
 * Description:
 * Author:
 * Date:
 */

const int redPin = A4;
const int greenPin = D0;
const int bluePin = D1;

const int buttonPin = D2;
int buttonState;
int lastButtonState = LOW;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

int redValue = 255;
int greenValue = 255;
int blueValue = 255;

boolean lightIsOn = true;

// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  Particle.function("led", setLampPower);
  Particle.variable("lightIsOn", lightIsOn);

  pinMode(buttonPin, INPUT);

  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}

int setLampPower(String value) {
    if (value == true) {
        lightIsOn = true;
        analogWrite(redPin, redValue);
        analogWrite(greenPin, greenValue);
        analogWrite(bluePin, blueValue);
    } else if (value == false) {
        lightIsOn = false;
        analogWrite(redPin, 0);
        analogWrite(greenPin, 0);
        analogWrite(bluePin, 0);
    }
    return 0;
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
    int reading = digitalRead(buttonPin);
    if (reading != lastButtonState) {
        lastDebounceTime = millis();
    }
    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (reading != buttonState) {
            buttonState = reading;
            if (buttonState == HIGH) {
                setLampPower(!lightIsOn);
            }
        }
    }
}
