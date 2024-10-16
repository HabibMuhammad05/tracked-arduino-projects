#include <SoftwareSerial.h>
SoftwareSerial bt (6,7);

String perintah;

void setup() {
  Serial.begin(9600);
  bt.begin(9600);
}

void loop() {    
      if(bt.available()!=0){
      perintah = bt.readString();
      Serial.print(perintah);
      Serial.println();
      bt.print("ok-" + perintah);
      }
}
