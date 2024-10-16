//-----------------------------------------------------------------SCROLLING TEXT

/*
-----------------------------------------------------------------------------------------------------------------------------------------
DMD.h - Function and support library for the Freetronics DMD, a 512 LED matrix display panel arranged in a 32 x 16 layout.
Copyright (C) 2011 Marc Alexander (info <at> freetronics <dot> com) http://www.freetronics.com/dmd
-----------------------------------------------------------------------------------------------------------------------------------------

-----------------------------------------------------------------------------------------------------------------------------------------
      Installation:
Arduino Uno    P10 Panel
    13 ---------> S / CLK
    11 ---------> R
     9 ---------> nOE / OE
     8 ---------> L / SCLK
     7 ---------> B
     6 ---------> A
   GND ---------> GND


The P10 panel can still turn on without 5V Power Input if it only uses one panel, but to increase brightness it must be added with 5V Power Input. 
5V Power Input must also be used if using more than one P10 Panel.
-----------------------------------------------------------------------------------------------------------------------------------------
*/

#include <SPI.h>       
#include <DMD.h>    
#include <TimerOne.h>  
#include "Arial_black_16.h"
#include "Arial_Black_16_ISO_8859_1.h"
#include "Arial14.h"
#include "SystemFont5x7.h"

#define DISPLAYS_ACROSS 1 //-> Number of P10 panels used, side to side.
#define DISPLAYS_DOWN 1
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);

char *Text = "";

void ScanDMD() { 
  dmd.scanDisplayBySPI();
}

void setup(void) {
  Timer1.initialize(1000);          
  Timer1.attachInterrupt(ScanDMD);   
  dmd.clearScreen(true);   
  Serial.begin(115200);
}

void loop(void) {
  dmd.selectFont(Arial_Black_16_ISO_8859_1);
//  dmd.selectFont(Arial_Black_16);
  //dmd.selectFont(Arial_14);
  //dmd.selectFont(SystemFont5x7);

  //-----------------------------------------------------------By using "millis()"
  Text = "hello! lorem ipsum";
  dmd.drawMarquee(Text,strlen(Text),(32*DISPLAYS_ACROSS)-1,0);
  long start=millis();
  long timer=start;
  boolean ret=false;
  int interval=50;
  while(!ret){
    if ((timer+interval) < millis()) {
      ret=dmd.stepMarquee(-1,0);
      timer=millis();
      Serial.println(ret);
    }
  }

  //-----------------------------------------------------------By using "delay()"
  /*
  Text = "Uteh Str Channel Don't Forget to Subscribe on YouTube";
  dmd.drawMarquee(Text,strlen(Text),(32*DISPLAYS_ACROSS)-1,0);
  boolean ret=false;
  while(!ret){
    ret=dmd.stepMarquee(-1,0);
    delay(100);
  }
  */
}
