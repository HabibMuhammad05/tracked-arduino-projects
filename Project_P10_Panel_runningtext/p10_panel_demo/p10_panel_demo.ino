//-----------------------------------------------------------------Some Demo Examples

/*
-----------------------------------------------------------------------------------------------------------------------------------------
DMD.h - Function and support library for the Freetronics DMD, a 512 LED matrix display panel arranged in a 32 x 16 layout.
Copyright (C) 2011 Marc Alexander (info <at> freetronics <dot> com) http://www.freetronics.com/dmd
-----------------------------------------------------------------------------------------------------------------------------------------

-----------------------------------------------------------------------------------------------------------------------------------------
I only tried this code on a single P10 panel and used SystemFont5x7
 ____________     ____________
|            |   |            | 
|            |-->|            | If you use two or more P10 panels connected to the side, the code will still work.
|            |   |            |
 ¯¯¯¯¯¯¯¯¯¯¯¯     ¯¯¯¯¯¯¯¯¯¯¯¯
 ____________
|            |
|            |
|            |
 ¯¯¯¯¯¯¯¯¯¯¯¯
      ↓        If you use two or more P10 panels that are connected to the bottom, displaying scrolling text from the side will be fine, 
 ____________  but for scrolling text display from top to bottom it might be problematic.
|            |
|            |
|            |
 ¯¯¯¯¯¯¯¯¯¯¯¯
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

String s,sdis;
char c[1];
int p=0;
char *Text = "";
boolean ret=false;

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
//  dmd.selectFont(Arial_14);
  dmd.selectFont(SystemFont5x7);
//  dmd.selectFont(Arial_Black_16);
  
  //----------------------------------------------
  s="This";
  p=0;
  
  for (int i=4; i <= 23; i=i+6) {
    sdis = s.substring(p,p+1);
    sdis.toCharArray(c,2);
    for (int j=-7; j <= 0; j++) {
      dmd.drawString(i,j, c, 1, GRAPHICS_NORMAL);
      delay(50);
    }
    p++;
  }
//  //----------------------------------------------
  
  delay(100);
  
//  //----------------------------------------------
  s="is";
  p=0;
  
  for (int i=11; i <= 23; i=i+6) {
    sdis = s.substring(p,p+1);
    sdis.toCharArray(c,2);
    for (int j=17; j >= 9; j--) {
      dmd.drawString(i,j, c, 1, GRAPHICS_NORMAL);
      delay(50);
    }
    p++;
  }
//  //----------------------------------------------
  
  delay(1000);
  
//  //----------------------------------------------
  for (int i=0; i >= -7; i--) {
    dmd.drawString(4,i, "This", 4, GRAPHICS_NORMAL);
    delay(50);
  }
//  //----------------------------------------------
  
  delay(100);
  
//  //----------------------------------------------
  for (int i=9; i <= 17; i++) {
    dmd.drawString(11,i, "is", 2, GRAPHICS_NORMAL);
    delay(50);
    dmd.clearScreen(true);
  }
//  //----------------------------------------------
  
  delay(500);
  
////  dmd.selectFont(Arial_14);
////  dmd.selectFont(SystemFont5x7);
  dmd.selectFont(Arial_Black_16);
//  //----------------------------------------------
  Text = "Running Text";
  dmd.drawMarquee(Text,strlen(Text),(32*DISPLAYS_ACROSS)-1,0);
  while(!ret){
    ret=dmd.stepMarquee(-1,0);
    delay(100);
  }
  ret=false;
//  //----------------------------------------------
  
  delay(1000);
  
  //----------------------------------------------
  for (int i=0; i <= 16; i++) {
    int b=i-9;
    dmd.drawString(b,0, "b", 1, GRAPHICS_NORMAL);
    int y=33-i;
    dmd.drawString(y,0, "y", 1, GRAPHICS_NORMAL);
    delay(50);
  }
  //----------------------------------------------
  
  delay(500);
  
  //----------------------------------------------
  for (int i=0; i <= 4; i++) {
    dmd.drawString(7,0, "by", 2, GRAPHICS_TOGGLE);
    delay(500);
  }  
  //----------------------------------------------
  
  delay(500);
  
//  ----------------------------------------------
  Text = "Sample text";
  dmd.drawMarquee(Text,strlen(Text),(32*DISPLAYS_ACROSS)-1,0);
  while(!ret){
    ret=dmd.stepMarquee(-1,0);
    delay(100);
  }
  ret=false;
//  ----------------------------------------------
  
  delay(500);
}
