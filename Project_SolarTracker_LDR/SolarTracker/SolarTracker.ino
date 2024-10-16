#include <Servo.h>
#include <Blynk.h>
BlynkTimer m;
Servo UpDownServo, LeftRightServo;
int LDR1 = A0, LDR2 = A1, LDR3 = A2, LDR4 = A3;
int data1, data2, data3, data4;
int topData, botData, finalData;
int ser1 = 50, ser2=0;

void setup() {
  Serial.begin(115200);
  UpDownServo.attach(5);
  LeftRightServo.attach(6);
  pinMode(8,INPUT);
  digitalWrite(8,HIGH);
  pinMode(9,OUTPUT);
  
  m.setInterval(500L, isr);

  UpDownServo.write(ser1);}
void loop() {

  m.run();
  data1 = analogRead(LDR1) ;
  data2 = analogRead(LDR2) ;
  data3 = analogRead(LDR3) ;
  data4 = analogRead(LDR4) ;

  topData = max(data1, data2);
  botData = max(data3, data4);
  finalData = max(topData, botData);
  
  Serial.println(String(finalData));
  Serial.println(String(data1) +", "+String(data2) +", "+String(data3) +", "+String(data4));


  if(data1<finalData && data2<finalData){
    Serial.println("servo1 +" + String(ser1));
    if(ser1<140)
      ser1+=1;
  //  UpDownServo.write(ser1);
  
  }
    
  if(data3<finalData && data4<finalData){
    Serial.println("servo1 -" + String(ser1));
    if(ser1>0)
      ser1-=1;
    //UpDownServo.write(ser1);
    
  }

  if(data2<finalData && data3<finalData){
    Serial.println("servo2 +" + String(ser2));
    if(ser2<180)
      ser2+=1;
    LeftRightServo.write(ser2); }
    
  if(data1<finalData && data4<finalData){
    Serial.println("servo2 -" + String(ser2));
    if(ser2>0)
      ser2-=1;
    LeftRightServo.write(ser2);
  }
  delay(20);

}

void isr(){
  digitalWrite (9, digitalRead(8));
}
