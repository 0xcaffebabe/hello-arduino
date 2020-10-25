int ledPin = 13; // arduino 内置的LED灯脚
void setup() {
  
  pinMode(ledPin, OUTPUT); // 设置该针脚为输出模式
}

void loop() {
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
  delay(500);
}
