int buttonPin = 7;
int ledPin = 12;
void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  bool val = digitalRead(buttonPin);
  Serial.println(val);
  if (val) {
    digitalWrite(ledPin, HIGH);
  }else {
    digitalWrite(ledPin, LOW);
  }
}
