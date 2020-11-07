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
int t;
char c;
char buffer[64];
int pos = 0;
bool inProcess = false;
int r,g,b;

void readline(){
  t = wifi.read();
  c = (char)t;
  if (pos >= 63){
    for(int i = 0;i<64;i++) buffer[i] = '\0';
    pos = 0;
  }
  buffer[pos++] = t;
  if (c == 'F'){
    Serial.println("got it");
    resolveReuqest();
    Serial.println(r);
    Serial.println(g);
    Serial.println(b);
    setLightColor();
    for(int i = 0;i<64;i++) buffer[i] = '\0';
    pos = 0;
  }
}

void setLightColor(){
   analogWrite(rPin, r);
   analogWrite(gPin, g);
   analogWrite(bPin, b);
}

void resolveReuqest(){
  char rA[4];
  char gA[4];
  char bA[4];
  for(int i = 0;i<64;i++){
    if (buffer[i] == ':'){
      rA[0]=buffer[i+1];
      rA[1]=buffer[i+2];
      rA[2]=buffer[i+3];
      rA[3]='\0';
      r =String(rA).toInt();
      gA[0]=buffer[i+5];
      gA[1]=buffer[i+6];
      gA[2]=buffer[i+7];
      gA[3]='\0';
      g =String(gA).toInt();
      bA[0]=buffer[i+9];
      bA[1]=buffer[i+10];
      bA[2]=buffer[i+11];
      bA[3]='\0';
      b =String(bA).toInt();
    }
  }
}

void loop() {
  if(wifi.available()){
    readline();
  }
  
  if(Serial.available()){
    wifi.write(Serial.read());
  }
}
