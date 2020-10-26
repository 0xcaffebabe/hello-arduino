int ledPin = 10;
int humanSensor = A5;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}
int i=0;
void loop() {
  i = analogRead(5);
  if (i>512){
    digitalWrite(ledPin,HIGH);
  }else{
    digitalWrite(ledPin, LOW);  
  }
}
