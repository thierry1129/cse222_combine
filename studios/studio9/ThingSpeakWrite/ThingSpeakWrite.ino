int channelid =  453893;
int field = 1;

void setup() {
  ThingSpeak.begin(client);
  pinMode( redPin, OUTPUT);
  pinMode( greenPin, OUTPUT);
  pinMode( bluePin, OUTPUT);
  pinMode( button, INPUT_PULLUP);

  analogWrite( redPin, redValue);
  analogWrite( greenPin, greenValue);
  analogWrite( bluePin, blueValue);

}
void loop() {
  void isButtonClicked(){

  }
  delay(5000);
  writeField(int ChannelNumber, int Field, float Value, String API Key){
    ChannelNumber = channelid;
    Field = field;
    API Key = ETL2AQAXFL3HXWT7;
    value =
  }
}
