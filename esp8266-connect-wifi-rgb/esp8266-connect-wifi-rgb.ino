#include <SoftwareSerial.h>


#define WIFI_TX       3 // 可能芯片上面标错了 这里需要根芯片的TX RX相反
#define WIFI_RX       2
#define rPin           A0
#define gPin           A1
#define bPin           A2
SoftwareSerial wifi(WIFI_RX, WIFI_TX);   //RX, TX
//char[] data = "";
void setup() {
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
int r,g,b;
void loop() {
  if(wifi.available()){
    c= char(wifi.read());
    Serial.println(c);
    if (c == '+'){
      inProcess = true;
    }
    if (c == 'O' && inProcess){
      Serial.println("open");
      inProcess = false;
      r = random(0,256);
      g = random(0,256);
      b = random(0,256);
      analogWrite(rPin, r);
      analogWrite(gPin, g);
      analogWrite(bPin, b);
    }else if (c == 'C' && inProcess){
      Serial.println("close");
      analogWrite(rPin, 0);
      analogWrite(gPin, 0);
      analogWrite(bPin, 0);
      inProcess = false;
    }
  }
  
  if(Serial.available()){
    wifi.write(Serial.read());
  }
//  delay(1000);
}
