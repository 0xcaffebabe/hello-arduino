#include <IRremote.h>
int infraReadPin = 11;
IRrecv recv(infraReadPin);
decode_results result;
void setup() {
  Serial.begin(9600);
  recv.enableIRIn();
}

void loop() {
  if (recv.decode(&result)){
    Serial.println(result.value, HEX);
    recv.resume();
  }

}
