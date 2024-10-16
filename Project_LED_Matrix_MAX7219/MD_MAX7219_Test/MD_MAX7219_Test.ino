/*-------MD_MAX7219_RunningText With Effect-------------*/
/*-------------Source Code by---------------------------*/
/*------Modified & Adapted by Habib.m @Hab_mz-----------*/
/*-----------------------V1.1---------------------------*/
/*------------------------------------------------------*/
/*---------------SPI Wiring Connections-----------------*/
/*--------------CLK_PIN   13  // or SCK-----------------*/
/*--------------DATA_PIN  11  // or MOSI----------------*/
/*---------------CS_PIN   10  // or SS------------------*/
/*------------------------------------------------------*/

#include <MD_MAX72xx.h>
#define PRINT(s, x) { Serial.print(F(s)); Serial.print(x); }
#define PRINTS(x) Serial.print(F(x))
#define PRINTD(x) Serial.println(x, DEC)

#define MAX_DEVICES  4
#define DELAYTIME  100

MD_MAX72XX mx = MD_MAX72XX(MD_MAX72XX::FC16_HW, 10, MAX_DEVICES);
//------------------------(HARDWARE_TYPE, CS_PIN, MAX_DEVICES)


void setup(){
  mx.begin();
  Serial.begin(57600);
  PRINTS("\n[MD_MAX72XX Test & Demo]");
}

void loop(){
  scrollText("Hello!   ");
  delay(500);
  spiral(35);
  stripe(50);
  
}
