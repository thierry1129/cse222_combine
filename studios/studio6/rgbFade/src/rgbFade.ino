/*
 * Project rgbFade
 * Description:
 * Author:
 * Date:
 */

int redPin = A4;    // RED pin of the LED to PWM pin **A4**
int greenPin = D0;  // GREEN pin of the LED to PWM pin **D0**
int bluePin = D1;   // BLUE pin of the LED to PWM pin **D1**
int redValue = 255; // Full brightness for an Cathode RGB LED is 0, and off 255
int greenValue = 255; // Full brightness for an Cathode RGB LED is 0, and off 255
int blueValue = 255; // Full brightness for an Cathode RGB LED is 0, and off 255</td>

// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
    pinMode( redPin, OUTPUT);
    pinMode( greenPin, OUTPUT);
    pinMode( bluePin, OUTPUT);

    // turn them all off...
    analogWrite( redPin, redValue);
    analogWrite( greenPin, greenValue);
    analogWrite( bluePin, blueValue);
}
// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.

}
