const int buttonPin = D4;
void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
}

int count = 0;
void loop() {
  Serial.println("Something");
  if(digitalRead(buttonPin)==0) {
    count++;
    Serial.print("Pressed ");
    Serial.print(count);
    Serial.println(" times");
  }
}
