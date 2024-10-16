//--------------------------------------------------------------------------------Arduino P10 Digital Clock Demo 2------------------------------------
/*
######################################################################################################################################################
# DMD.h - Function and support library for the Freetronics DMD, a 512 LED matrix display panel arranged in a 32 x 16 layout.                         #
# Copyright (C) 2011 Marc Alexander (info <at> freetronics <dot> com) http://www.freetronics.com/dmd                                                 #
#                                                                                                                                                    #
#      Installation:                                                                                                                                 #
# Arduino Uno    P10 Panel                                                                                                                           #
#    13 ---------> S / CLK                                                                                                                           #
#    11 ---------> R                                                                                                                                 #
#     9 ---------> nOE / OE                                                                                                                          #
#     8 ---------> L / SCLK                                                                                                                          #
#     7 ---------> B                                                                                                                                 #
#     6 ---------> A                                                                                                                                 #
#   GND ---------> GND                                                                                                                               #
#                                                                                                                                                    #
# The P10 panel can still turn on without 5V Power Input if it only uses one panel, but to increase brightness it must be added with 5V Power Input. # 
# 5V Power Input must also be used if using more than one P10 Panel.                                                                                 #
######################################################################################################################################################
*/
#include <TimeLib.h>
#define TIME_REQUEST  7    

//--------------------------------------------------------------------------------------The SPI, DMD, TimerOne and Font libraries are used.
#include <SPI.h>       
#include <DMD.h>    
#include <TimerOne.h>  
#include "SystemFont5x7.h"
#include "Font_6x14.h" //-> This font only contains numbers from 0-9
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------Configuration P10
#define DISPLAYS_ACROSS 1 //-> Number of P10 panels used, side to side.
#define DISPLAYS_DOWN 1
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);
//--------------------------------------------------------------------------------------Variables for time and date
int _day, _month, _year, _hour24, _hour12, _minute, _second, _dtw;
int hr24;
String st;
//char nameoftheday[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
char month_name[12][12] = {"Jan","Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------Variable for Millis
const long interval = 1000; //-> Retrieve time and date data every 1 second
unsigned long previousMillis = 0;

const long interval_for_date = 60; //-> For scroll speed
unsigned long previousMillis_for_date = 0;
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------Variable to display hours and minutes
char hr_24 [3];
String str_hr_24;
char mn [3];
String str_mn;
char sc [3];
String str_sc;
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------ScanDMD()
void ScanDMD() { 
  dmd.scanDisplayBySPI();
}

time_t requestSync(){
  Serial.write(7);  // ASCII bell character requests a time sync message 
  return 0; // the time will be sent later in response to serial mesg
}

//--------------------------------------------------------------------------------------setup
void setup() {
  Serial.begin(115200);
  setSyncProvider(requestSync);  //set function to call when sync required
  Serial.println("Waiting for sync message");
  Timer1.initialize(1000);          
  Timer1.attachInterrupt(ScanDMD);   
  dmd.clearScreen(true);  

  SetupPrintClock();
  
  Serial.println("sync ok");
}
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------loop
void loop() {
  PrintClock();
  delay(1000);
}
//--------------------------------------------------------------------------------------

//------------------------------------------------------------------------Subroutine to retrieve or update the time and date from DS1307
void GetDateTime() {
//  DateTime now = rtc.now();
  _day=day();
  _month=month();
  _year=year();
  _hour24=hour();
  _minute=minute();
  _second=second();
//  _dtw=dayOfTheWeek();

  hr24=_hour24;
  if (hr24>12) {
    _hour12=hr24-12;
  }
  else if (hr24==0) {
    _hour12=12;
  }
  else {
    _hour12=hr24;
  }

  if (hr24<12) {
    st="AM";
  }
  else {
    st="PM"; 
  } 

//  if(_day == day()+1){
//    unsigned int secondset = millis();
//    if(secondset == 15000){
//    _second == second() - 14;
//  }
   
}
//------------------------------------------------------------------------

//------------------------------------------------------------------------Subroutine to display days, months and years
void scrolling_date() {
  dmd.clearScreen(true);
  delay(100);

  //=====================================================Holds date data to display
//nameoftheday[_dtw]) + ", " + 
  String Date = String(String(_day) + "-" + String(month_name[_month-1]) + "-" + String(_year));
  char dt[50];
  Date.toCharArray(dt,50);
  int i=32+10;
  int j=strlen(dt)+(strlen(dt)*5);
  //=====================================================

  dmd.selectFont(SystemFont5x7);

  while(1) {
    //_____________________________________________________millis() to display time
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis; //-> save the last time 
      
      //=====================================================Showing the clock in P10
      str_hr_24=String(_hour24);
      str_hr_24.toCharArray(hr_24,3);
  
      if (_hour24<10) {
        dmd.drawString(2, 0, "0", 1, GRAPHICS_NORMAL);
        dmd.drawString(8, 0, hr_24, 1, GRAPHICS_NORMAL);
      }
      else {
        dmd.drawString(2, 0, hr_24, 2, GRAPHICS_NORMAL);
      }
      //=====================================================
      
      //=====================================================Showing ":" in P10
      GetDateTime(); //-> Retrieve time and date data from DS1307
      if (_second %2 == 0) {
        dmd.drawString(14, 0, ":", 2, GRAPHICS_OR);
      }
      else {
        dmd.drawString(14, 0, ":", 2, GRAPHICS_NOR);
      }
      //=====================================================
      
      //=====================================================Showing minutes in P10
      str_mn=String(_minute);
      str_mn.toCharArray(mn,3);
  
      if (_minute<10) {
        dmd.drawString(19, 0, "0", 1, GRAPHICS_NORMAL);
        dmd.drawString(25, 0, mn, 1, GRAPHICS_NORMAL);
      }
      else {
        dmd.drawString(19, 0, mn, 2, GRAPHICS_NORMAL);
      }
      //=====================================================
    }
    //_____________________________________________________

    //_____________________________________________________millis() for display & scrolling date
    unsigned long currentMillis_for_date = millis();
    if (currentMillis_for_date - previousMillis_for_date >= interval_for_date) {
      previousMillis_for_date = currentMillis_for_date; //-> save the last time 
      
      i--;
      dmd.drawString(i, 9, dt, strlen(dt), GRAPHICS_NORMAL);
      if (i<=~j) {
        dmd.clearScreen(true);
        delay(100);
        return;
      }
    }
    //_____________________________________________________
  }
}

void digitalClockDisplay(){
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; //-> save the last time

    GetDateTime(); //-> Retrieve time and date data from DS1307

    //=====================================================Showing hour in P10
    dmd.selectFont(Font_6x14);
    
    str_hr_24=String(_hour24);
    str_hr_24.toCharArray(hr_24,3);

    if (_hour24<10) {
      dmd.drawString(1, 0, "0", 1, GRAPHICS_NORMAL);
      dmd.drawString(8, 0, hr_24, 1, GRAPHICS_NORMAL);
    }
    else {
      dmd.drawString(1, 0, hr_24, 2, GRAPHICS_NORMAL);
    }
    //=====================================================

    //=====================================================Showing ":" in P10
    if (_second %2 == 0) {    
        dmd.drawFilledBox(16,3,17,4, GRAPHICS_OR);
        dmd.drawFilledBox(16,11,17,12, GRAPHICS_OR); 
//        dmd.drawString(14, 0, ":", 2, GRAPHICS_OR);
      }
     else {
        dmd.drawFilledBox(16,3,17,4, GRAPHICS_NOR);
        dmd.drawFilledBox(16,11,17,12, GRAPHICS_NOR); 
//        dmd.drawString(14, 0, ":", 2, GRAPHICS_NOR);
      }
    //=====================================================

    //=====================================================Showing minute and second in P10
    dmd.selectFont(SystemFont5x7);
    
    str_mn=String(_minute);
    str_mn.toCharArray(mn,3);

    if (_minute<10) {
      dmd.drawString(20, 0, "0", 1, GRAPHICS_NORMAL);
      dmd.drawString(26, 0, mn, 1, GRAPHICS_NORMAL);
    }
    else {
      dmd.drawString(20, 0, mn, 2, GRAPHICS_NORMAL);
    }

    str_sc=String(_second);
    str_sc.toCharArray(sc,3);

    if (_second<10) {
      dmd.drawString(20, 9, "0", 1, GRAPHICS_NORMAL);
      dmd.drawString(26, 9, sc, 1, GRAPHICS_NORMAL);
    }
    else {
      dmd.drawString(20, 9, sc, 2, GRAPHICS_NORMAL);
    }
    //=====================================================

    //=====================================================Call the scrolling_date() subroutine to display the date.
    if (_second==11) { //-> Display the date when seconds equal to 11
      scrolling_date();
    }
    if(_second==41){
      gambar_masjid();
    }
    //=====================================================
  }
}

void processSyncMessage() {
  if(Serial.find("T")) {
     unsigned long pctime = Serial.parseInt();
     if( pctime >= 1357041600) { // epoch Jan 1 2013  check the integer is a valid time (greater than Jan 1 2013)
       setTime(pctime); // Sync Arduino clock to the time received on the serial port
     }
  }
}
void SetupPrintClock(){
  while (timeStatus() != timeSet){
    if (Serial.available()) {processSyncMessage();}
    Serial.println("sync needed");
    dmd.selectFont(SystemFont5x7);
    dmd.drawString(4,0, "SYNC", 4, GRAPHICS_NORMAL);  
    dmd.drawString(2,9, "ERROR", 5, GRAPHICS_NORMAL);
    delay(500);
    dmd.clearScreen(true);
    delay(500);
  }
}

void PrintClock(){
  if (Serial.available()) {processSyncMessage();}
  if (timeStatus()!= timeNotSet) {digitalClockDisplay(); Serial.println("sync ok"); }
//  else {Serial.println("sync needed");}
}

void gambar_masjid(){
int GRAPHICS_ON=GRAPHICS_NORMAL;
dmd.clearScreen(true);
//dmd.drawBox(32,0,63,15,GRAPHICS_ON);
//gambar masjid
//kiri
dmd.drawLine(0,6,0,6,GRAPHICS_NORMAL);
dmd.drawLine(1,5,1,15,GRAPHICS_ON);
dmd.drawLine(2,0,2,13,GRAPHICS_ON);
dmd.drawLine(3,5,3,15,GRAPHICS_ON);
dmd.drawLine(4,6,4,6,GRAPHICS_ON);
//tengah

dmd.drawLine(15,0,15,0,GRAPHICS_ON);
dmd.drawLine(14,1,16,1,GRAPHICS_ON);
dmd.drawLine(13,2,17,2,GRAPHICS_ON);
dmd.drawLine(12,3,18,3,GRAPHICS_ON);
dmd.drawLine(11,4,19,4,GRAPHICS_ON);
dmd.drawLine(11,5,19,5,GRAPHICS_ON);
dmd.drawLine(12,6,18,6,GRAPHICS_ON);
dmd.drawLine(13,7,17,7,GRAPHICS_ON);
dmd.drawLine(5,8,25,8,GRAPHICS_ON);
dmd.drawLine(5,10,25,10,GRAPHICS_ON);
dmd.drawLine(5,11,7,11,GRAPHICS_ON);dmd.drawLine(9,11,14,11,GRAPHICS_ON);dmd.drawLine(16,11,21,11,GRAPHICS_ON);dmd.drawLine(23,11,25,11,GRAPHICS_ON);
dmd.drawLine(5,12,6,12,GRAPHICS_ON);dmd.drawLine(10,12,13,12,GRAPHICS_ON);dmd.drawLine(17,12,20,12,GRAPHICS_ON);dmd.drawLine(24,12,25,12,GRAPHICS_ON);
dmd.drawLine(5,13,6,13,GRAPHICS_ON);dmd.drawLine(10,13,13,13,GRAPHICS_ON);dmd.drawLine(17,13,20,13,GRAPHICS_ON);dmd.drawLine(24,13,25,13,GRAPHICS_ON);
dmd.drawLine(5,14,6,14,GRAPHICS_ON);dmd.drawLine(10,14,13,14,GRAPHICS_ON);dmd.drawLine(17,14,20,14,GRAPHICS_ON);dmd.drawLine(24,14,25,14,GRAPHICS_ON);
dmd.drawLine(5,15,25,15,GRAPHICS_ON);
//kanan
dmd.drawLine(26,6,26,6,GRAPHICS_ON);
dmd.drawLine(27,5,27,15,GRAPHICS_ON);
dmd.drawLine(28,0,28,13,GRAPHICS_ON);
dmd.drawLine(29,5,29,15,GRAPHICS_ON);
dmd.drawLine(30,6,30,6,GRAPHICS_ON);
delay(2000);
dmd.clearScreen(true);

}


//  unsigned long currentMillis = millis();
//  if (currentMillis - previousMillis >= interval) {
//    previousMillis = currentMillis; //-> save the last time
//
//    GetDateTime(); //-> Retrieve time and date data from DS1307
//    
//    dmd.selectFont(Font_6x14);
//
//    //=====================================================Showing the clock in P10
//    str_hr_24=String(_hour24);
//    str_hr_24.toCharArray(hr_24,3);
//
//    if (_hour24<10) {
//      dmd.drawString(0, 0, "0", 1, GRAPHICS_NORMAL);
//      dmd.drawString(7, 0, hr_24, 1, GRAPHICS_NORMAL);
//    }
//    else {
//      dmd.drawString(0, 0, hr_24, 2, GRAPHICS_NORMAL);
//    }
//    //=====================================================
//
//    //=====================================================Showing ":" in P10
//    if (_second %2 == 0) {
//      dmd.drawFilledBox(15,3,16,4, GRAPHICS_OR);
//      dmd.drawFilledBox(15,11,16,12, GRAPHICS_OR);
//    }
//    else {
//      dmd.drawFilledBox(15,3,16,4, GRAPHICS_NOR);
//      dmd.drawFilledBox(15,11,16,12, GRAPHICS_NOR);
//    }
//    //=====================================================
//
//    //=====================================================Showing minutes in P10
//    str_mn=String(_minute);
//    str_mn.toCharArray(mn,3);
//
//    if (_minute<10) {
//      dmd.drawString(19, 0, "0", 1, GRAPHICS_NORMAL);
//      dmd.drawString(26, 0, mn, 1, GRAPHICS_NORMAL);
//    }
//    else {
//      dmd.drawString(19, 0, mn, 2, GRAPHICS_NORMAL);
//    }
//    //=====================================================
//
//    //=====================================================Call the scrolling_date() subroutine to display the date.
//    if (_second==11) { //-> Display the date when seconds equal to 11
//      scrolling_date();
//    }
//    //=====================================================
//  }
//}
