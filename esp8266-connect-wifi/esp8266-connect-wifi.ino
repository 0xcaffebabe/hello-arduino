#include <SoftwareSerial.h>


#define WIFI_TX       3
#define WIFI_RX       2
#define LED           13
SoftwareSerial wifi(WIFI_RX, WIFI_TX);   //RX, TX
//char[] data = "";
void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  Serial.println("hardware serial!");
  wifi.begin(115200);
  Serial.println("software serial!");
  wifi.println("AT\r\n");
  while(!wifi.available());
  Serial.println("wifi start!");
  wifi.print("AT\r\n");
  // ESP8266初始化需要执行下面注释的两句，当连接上wifi之后，以后没次上电就会自动连接了
//  delay(1000);
//  wifi.print("AT+CWMODE=1\r\n");
//  delay(1000);
//  wifi.print("AT+CWJAP=\"NULL\",\"rm-rf1024\"");
  delay(1000);
  wifi.print("AT+CIPMUX=1\r\n");
  delay(1000);
  wifi.print("AT+CIPSERVER=1,1999\r\n");
}
char c;
bool inProcess = false;
void loop() {
  if(wifi.available()){
    c= char(wifi.read());
    if (c == '+'){
      inProcess = true;
    }
    if (c == 'O' && inProcess){
      Serial.println("open");
      inProcess = false;
      digitalWrite(13, HIGH);
    }else if (c == 'C' && inProcess){
      Serial.println("close");
      inProcess = false;
      digitalWrite(13, LOW);
    }
  }
  
  if(Serial.available()){
    wifi.write(Serial.read());
  }
//  delay(1000);
}
