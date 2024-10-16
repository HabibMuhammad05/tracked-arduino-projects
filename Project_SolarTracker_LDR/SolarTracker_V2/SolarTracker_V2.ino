#include <Servo.h>

Servo servoswing; //horizontal servo(BOTTOM SERVO)
uint8_t swingpos = 0; //assign servo at 0 degree
uint8_t SwingHighLimit = 180; //maximum range of servo is 180 degree(it is variable you can also change)
uint8_t SwingLowLimit = 10;   //minimum range of servo is 10 degree(it is variable you can also change)

Servo servotilt; //vertical servo(TOP SERVO) 
uint8_t tiltpos = 0; 
uint8_t TiltHighLimit = 180;
uint8_t TiltLowLimit = 10;

uint8_t TopR = A0; //top right LDR A1 pin
uint8_t TopL = A1; //top left LDR A2 pin

uint8_t BotR = A2; // bottom right LDR A0 pin
uint8_t BotL = A3; // bottom left LDR A3 pin

uint8_t setpoint = 20;
 void setup () {
  servoswing.attach(10); //horizontal servo connected to arduino pin 10
  servoswing.write(0);
  
  servotilt.attach(9); //vertical servo connected to arduino pin 9
  servotilt.write(0);
  delay(500); //delay
}

void loop(){
  swingpos = servoswing.read();
  tiltpos = servotilt.read();
  
  
  uint8_t ValTopL = analogRead(TopL) / 10; //read analog values from top left LDR
  uint8_t ValTopR = analogRead(TopR) / 10; //read analog values from top right LDR
  uint8_t ValBotL = analogRead(BotL) / 10; //read analog values from bottom left LDR
  uint8_t ValBotR = analogRead(BotR) / 10; //read analog values from bottom right LDR
  
  
  uint8_t TopAVG = (ValTopL + ValTopR) / 2; //average of top LDRs
  uint8_t BotAVG = (ValBotL + ValBotR) / 2; //average of bottom LDRs
  uint8_t LeftAVG = (ValTopL + ValBotL) / 2; //average of left LDRs
  uint8_t RightAVG = (ValTopR + ValBotR) / 2; //average of right LDRs

  if (TopAVG < BotAVG  && BotAVG - TopAVG >= setpoint){
    servotilt.write(tiltpos -1);
    if (tiltpos > TiltHighLimit) { 
        tiltpos = TiltHighLimit;}
    delay(8);
  }
  
  else if (BotAVG < TopAVG && TopAVG - BotAVG >= setpoint){
    servotilt.write(tiltpos +1);
    if (tiltpos < TiltLowLimit){
        tiltpos = TiltLowLimit;}
    delay(8);
  }
  
  else {
    servotilt.write(tiltpos);
  }
  
  if (LeftAVG > RightAVG && LeftAVG - RightAVG >= setpoint){
    servoswing.write(swingpos -1);
    if (swingpos > SwingHighLimit){
        swingpos = SwingHighLimit;}
    delay(8);
  }
  
  else if (RightAVG > LeftAVG && RightAVG - LeftAVG >= setpoint){
    servoswing.write(swingpos +1);
    if (swingpos < SwingLowLimit){
        swingpos = SwingLowLimit;}
    delay(8);
  }
  
  else {
    servoswing.write(swingpos);
  }
  delay(50);
}
