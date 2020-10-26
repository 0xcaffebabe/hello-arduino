int beepPin = 11;

void setup() {
  pinMode(beepPin, OUTPUT);

}

void loop() {
  for(int i = 0;i<100;i++){
    digitalWrite(beepPin, HIGH);
    delay(1);
    digitalWrite(beepPin, LOW
    );
    delay(1);
  }

}
