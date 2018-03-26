// rgb led pins
const int redPin = D2;
const int greenPin = D0;
const int bluePin = D1;

// button variables
const int buttonPin = D6;
int buttonState;
int lastButtonState = LOW;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

// rgb values
int redValue = 255;
int greenValue = 255;
int blueValue = 255;

bool lightIsOn = true;

void setup() {

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  Particle.function("led", setLampPower);
  Particle.function("setCurrColor", setCurrColor);
  Particle.variable("lightIsOn", lightIsOn);
  Particle.function("publishState", publishState);

  pinMode(buttonPin, INPUT);

  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
  Serial.begin(9600);
}

int setLampPower(String value) {
    if (value == "true") {
        lightIsOn = true;
        analogWrite(redPin, redValue);
        analogWrite(greenPin, greenValue);
        analogWrite(bluePin, blueValue);
    } else if (value == "false") {
        lightIsOn = false;
        analogWrite(redPin, 0);
        analogWrite(greenPin, 0);
        analogWrite(bluePin, 0);
    }
    publishState("");
    return 0;
}

int setCurrColor(String value) {
    int commaIndex = value.indexOf(',');
    int secondCommaIndex = value.indexOf(',', commaIndex + 1);
    String redV = value.substring(0, commaIndex);
    String greenV = value.substring(commaIndex + 1, secondCommaIndex);
    String blueV = value.substring(secondCommaIndex + 1);
    redValue = redV.toInt();
    greenValue = greenV.toInt();
    blueValue = blueV.toInt();
    analogWrite(redPin, redValue);
    analogWrite(greenPin, greenValue);
    analogWrite(bluePin, blueValue);
    publishState("");
    return 0;
}

const String topic = "cse222Lights/thisLamp/color";

 int publishState(String arg) {
   String data = "{";
   if(lightIsOn) {
     data += "\"powered\":true";
   } else {
     data += "\"powered\":false";
 }
   data += ", ";
   data += "\"r\":";
   data += redValue;
   data += ", ";
   data += "\"g\":";
   data += greenValue;
   data += ", ";
   data += "\"b\":";
   data += blueValue;
   data += "}";


   Serial.println("Publishing:");
   Serial.println(data);

   Particle.publish(topic, data, 60, PRIVATE);
   return 0;
 }

// loop() runs over and over again, as quickly as it can execute.
void loop() {

    int reading = digitalRead(buttonPin);


    if (reading != lastButtonState) {
        lastDebounceTime = millis();
    }
    if ((millis() - lastDebounceTime) > debounceDelay) {
      //  Serial.println(reading);
        if (reading != buttonState) {
          Serial.println(reading);
            buttonState = reading;
            if (buttonState == HIGH) {
                if (lightIsOn) {
                    setLampPower("false");
                    lightIsOn = false;
                    Serial.println("in on");
                } else {
                    setLampPower("true");
                    lightIsOn = true;
                    Serial.println("in onff");
                }
            }
        }
    }
}
