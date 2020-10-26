#include <Servo.h>//之间要有空格，否则编译时会报错。
Servo myservo;
void setup() {
  myservo.attach(9);
}
int i =0;
void loop() {
  for(i=0;i<180;i++){
    myservo.write(i);//设置舵机旋转的角度 
    delay(10);   
  }
  for(i=180;i>0;i--){
    myservo.write(i);//设置舵机旋转的角度 
    delay(10);   
  }
}
