/*----------------ARDUINO PRO MINI TELOLET 6 CORONG---------------------*/
/*-----------------Source Code by some dude on yt-----------------------*/
/*--------------Modified & Adapted by Habib.m @Hab_mz-------------------*/
/*------------------------------V11.3------------------------------------*/
/*----------------------------------------------------------------------*/

//UPLOAD SKETCH ON ARDUINO PRO OR PROMINI

//FOR DEBUG SEARCH "//Serial.print" then change it to "Serial.print"


#include <Wire.h>
#include <PCF8574.h>
PCF8574 pcf20(0x27);

#include <U8g2lib.h>
//U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
U8X8_SH1106_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);

#include "variables.h"
#include "functions.h"

void setup(){
  //Serial.begin(9600);
  Wire.begin();
  pcf20.begin();
  u8x8.setI2CAddress(0x78);
  u8x8.begin(); // start the u8g2 library
  
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  digitalWrite(DATA_PIN, LOW);
  digitalWrite(CLOCK_PIN, LOW);
  digitalWrite(LATCH_PIN, LOW);
  
  for ( int i = 0 ; i < 6 ; i++) {
    pinMode(but[i], INPUT);
    pinMode(led[i], OUTPUT);
    digitalWrite(led[i], LOW);
  }
 getIndex(maxNum, true);
 
//  u8g2.firstPage();
//  do {
//    u8g2.clearBuffer();
//    u8g2.setFontMode(1);
//    u8g2.setBitmapMode(1);
//    u8g2.setFont(u8g2_font_helvB08_tr);
//    u8g2.drawStr(105, 8, "V3.1");
//    u8g2.drawXBMP(0, 0, 128, 64, logoLOGOV2);
//  } while ( u8g2.nextPage() ); // Continue drawing on the next page if any
//  delay(3000);
//  for (int i = 0; i <= 100; i = i + 5) {
//    u8g2.firstPage();
//      do {
//        u8g2.clearBuffer();
//        u8g2.drawXBMP(0, 0, 128, 45, logoLOGOV2);
//        u8g2.drawRFrame(10, 48, 108, 14, 3); // Draw the frame of the progress bar
//        u8g2.drawBox(12, 50, i, 10); // Draw the progress bar fill
//      } while ( u8g2.nextPage() ); // Continue drawing on the next page if any
//  }
}

void loop(){
    unsigned int currentMillis = millis();

    if ((currentMillis - buttonMillis) >= 50) {
    buttonMillis = currentMillis;
    for (int i = 0; i < 6; i++) {
      bool buttonState = pcf20.readButton(pcfPushButtonPins[i]);
      if (buttonState != previousButtonStates[i]) {
        previousButtonStates[i] = buttonState;
        if (buttonState) {
          if (i == 0){
            if (isSaved){
            Serial.println("But 1 Pressed, index save");
            num++;
            displayNumber(num);
            }else{
            Serial.println("But 1 Pressed, adding...");
            if (num < maxNum){ num++; }
            else{ num = maxNum; }
            displayNumber(num);
            }
          }
          
          else if (i == 1){
//            isSaved = false;
            Serial.println("But 2 Pressed, subtracting...");
            if (num > 0){ num--; }
            else{ num = 0; }
            displayNumber(num);
          }
          
          else if (i == 2){
            isSaved = false;
            Serial.println("But 3 Pressed, tempo adding...");
            if (spd < maxSpd){ spd++; }
            else{ spd = maxSpd; }
            displayTempo(spd);
          }
          
          else if (i == 3){
            isSaved = false;
            Serial.println("But 4 Pressed, tempo subtracting...");
            if (spd > 1){ spd--; }
            else{ spd = 1; }
            displayTempo(spd);
          }
          
          else if (i == 4){
            if(isSaved){
              Serial.println("menyimpan data bos");
              getIndex(maxNum, true);
              Serial.println("maxNum : " + String(maxNum));
              Serial.println("num : " + String(num));
              
              uint16_t save;
              if (maxNum >= num){  save = maxNum; }
              else{ save = num; }
              
              getIndex(save, false);
              Serial.println("saved data : " + String(save));
              writeArrayToExternalEEPROM(num);
              getIndex(maxNum, true);
              displayNumber(save);
              isSaved = false;
              playPressed(true);
            }else{
               if(isPlaying){
                  playMod = 0;
                  for ( int i = 0 ; i < 6 ; i++) {
                    digitalWrite(led[i], LOW);
                  }
                  Serial.println("But 5 Pressed, stop...");
                  displayNumber(num);
                  isPlaying = false;
               }else{
                  Serial.println("But 5 Pressed, Reading...");
                  playPressed(false);
               }
            }
          }
          
          else if (i == 5){
            recordMod = 0;
            playMod = 0;
            displayNumber(0);
          }
        }
      }
    }
  }
  
  if ((currentMillis - switchMillis) >= 50) {
    switchMillis = currentMillis;

    for (int i = 0; i < 2; i++) {
      bool switchState = !pcf20.readButton(pcfSwitchPins[i]); // Inverted logic for toggle switches
      if (switchState != previousSwitchStates[i]) {
        previousSwitchStates[i] = switchState;
        
          if (i == 0){
            if (switchState){ 
              Serial.println("But 6 is 0N"); 
              led[0] = 2;
              led[1] = 3;
              led[2] = 4;
              led[3] = 5;
              led[4] = 6;
              led[5] = 7;
            }else{ 
              Serial.println("But 6 is 0FF"); 
              led[0] = 7;
              led[1] = 6;
              led[2] = 5;
              led[3] = 4;
              led[4] = 3;
              led[5] = 2;
            }
          }else if (i == 1){
            if (switchState){ 
              Serial.println("But 7 is 0N");
              Serial.println("recording bro");
              isRecording = true;
              recPressed();
              
            }else{ 
              Serial.println("But 7 is 0FF"); 
              if (isRecording){
                Serial.println("saving the data bro");
                assignValues();
                isRecording = false;
                isSaved = true;
                recordMod = 0;
                playMod = 0;
              }
            }
          }
        // Toggle the LED corresponding to the switch
//        int ledIndex = i + 5; // LEDs start from index 5 in the array
//        digitalWrite(ledPins[ledIndex], switchState);
//        Serial.print("Switch ");
//        Serial.print(i + 1); // Index + 1 to match switch number
//        Serial.print(" state: ");
//        Serial.println(switchState ? "ON" : "OFF");
      }
    }
  }
  
  //Operation part when record mode is On
  if ((recordMod == 1) && (playMod == 0)) {
      for(int i = 0; i <= 6; i++){
        buttonState[i] = !digitalRead(but[i]);
      }
  for(int i = 0; i <6; i++){
    if (buttonState[i] == LOW) {
      displayRec(i, 0);
      digitalWrite(led[i], HIGH);
      delay(10);

      if ((relPlayPause[i][0] != 0) && (relPlayPause[i][2] == 0)) {
        relPlayPause[i][1] = relPlayPause[i][1] + 1;
      }
      else if (relPlayPause[i][4] == 0) {
        relPlayPause[i][3] = relPlayPause[i][3] + 1;
      }
      else if (relPlayPause[i][6] == 0) {
        relPlayPause[i][5] = relPlayPause[i][5] + 1;
      }
      else if (relPlayPause[i][8] == 0) {
        relPlayPause[i][7] = relPlayPause[i][7] + 1;
      }
      else if (relPlayPause[i][10] == 0) {
        relPlayPause[i][9] = relPlayPause[i][9] + 1;
      }
      else if (relPlayPause[i][12] == 0) {
        relPlayPause[i][11] = relPlayPause[i][11] + 1;
      }
      else if (relPlayPause[i][14] == 0) {
        relPlayPause[i][13] = relPlayPause[i][13] + 1;
      }
      else if (relPlayPause[i][16] == 0) {
        relPlayPause[i][15] = relPlayPause[i][15] + 1;
      }
      else if (relPlayPause[i][18] == 0) {
        relPlayPause[i][17] = relPlayPause[i][17] + 1;
      }
      else if (relPlayPause[i][20] == 0) {
        relPlayPause[i][19] = relPlayPause[i][19] + 1;
      }
      else if (relPlayPause[i][22] == 0) {
        relPlayPause[i][21] = relPlayPause[i][21] + 1;
      }
    }
    else {
      digitalWrite(led[i], LOW);
      delay(10);

      if (relPlayPause[i][1] == 0) {
        relPlayPause[i][0] = relPlayPause[i][0] + 1;
      }
      else if (relPlayPause[i][3] == 0) {
        relPlayPause[i][2] = relPlayPause[i][2] + 1;
      }
      else if (relPlayPause[i][5] == 0) {
        relPlayPause[i][4] = relPlayPause[i][4] + 1;
      }
      else if (relPlayPause[i][7] == 0) {
        relPlayPause[i][6] = relPlayPause[i][6] + 1;
      }
      else if (relPlayPause[i][9] == 0) {
        relPlayPause[i][8] = relPlayPause[i][8] + 1;
      }
      else if (relPlayPause[i][11] == 0) {
        relPlayPause[i][10] = relPlayPause[i][10] + 1;
      }
      else if (relPlayPause[i][13] == 0) {
        relPlayPause[i][12] = relPlayPause[i][12] + 1;
      }
      else if (relPlayPause[i][15] == 0) {
        relPlayPause[i][14] = relPlayPause[i][14] + 1;
      }
      else if (relPlayPause[i][17] == 0) {
        relPlayPause[i][16] = relPlayPause[i][16] + 1;
      }
      else if (relPlayPause[i][19] == 0) {
        relPlayPause[i][18] = relPlayPause[i][18] + 1;
      }
      else if (relPlayPause[i][21] == 0) {
        relPlayPause[i][20] = relPlayPause[i][20] + 1;
      }
      else if (relPlayPause[i][23] == 0) {
        relPlayPause[i][22] = relPlayPause[i][22] + 1;
      }
    }
  }
      Serial.print(buttonState[0]);
      Serial.print(" ");
      Serial.print(buttonState[1]);
      Serial.print(" ");
      Serial.print(buttonState[2]);
      Serial.print(" ");
      Serial.print(buttonState[3]);
      Serial.print(" ");
      Serial.print(buttonState[4]);
      Serial.print(" ");
      Serial.println(buttonState[5]);
    
  }
 
  //Saat memasuki mode putar
  if ((playMod == 1) && (recordMod == 0)) {
    isPlaying = true;
   for(int i = 0; i < 6; i++){
    if (relRepPlayPause[i][0] != 00) {
      digitalWrite(led[i], LOW);
      relRepPlayPause[i][0] = relRepPlayPause[i][0] - 1;
      delay(spd);
    }
    else if (relRepPlayPause[i][1] != 00) {
      digitalWrite(led[i], HIGH);
      relRepPlayPause[i][1] = relRepPlayPause[i][1] - 1;
      delay(spd);
    }
    else if (relRepPlayPause[i][2] != 00) {
      digitalWrite(led[i], LOW);
      relRepPlayPause[i][2] = relRepPlayPause[i][2] - 1;
      delay(spd);
    }
    else if (relRepPlayPause[i][3] != 00) {
      digitalWrite(led[i], HIGH);
      relRepPlayPause[i][3] = relRepPlayPause[i][3] - 1;
      delay(spd);
    }
    else if (relRepPlayPause[i][4] != 00) {
      digitalWrite(led[i], LOW);
      relRepPlayPause[i][4] = relRepPlayPause[i][4] - 1;
      delay(spd);
    }
    else if (relRepPlayPause[i][5] != 00) {
      digitalWrite(led[i], HIGH);
      relRepPlayPause[i][5] = relRepPlayPause[i][5] - 1;
      delay(spd);
    }
    else if (relRepPlayPause[i][6] != 00) {
      digitalWrite(led[i], LOW);
      relRepPlayPause[i][6] = relRepPlayPause[i][6] - 1;
      delay(spd);
    }
    else if (relRepPlayPause[i][7] != 00) {
      digitalWrite(led[i], HIGH);
      relRepPlayPause[i][7] = relRepPlayPause[i][7] - 1;
      delay(spd);
    }
    else if (relRepPlayPause[i][8] != 00) {
      digitalWrite(led[i], LOW);
      relRepPlayPause[i][8] = relRepPlayPause[i][8] - 1;
      delay(spd);
    }
    else if (relRepPlayPause[i][9] != 00) {
      digitalWrite(led[i], HIGH);
      relRepPlayPause[i][9] = relRepPlayPause[i][9] - 1;
      delay(spd);
    }
    else if (relRepPlayPause[i][10] != 00) {
      digitalWrite(led[i], LOW);
      relRepPlayPause[i][10] = relRepPlayPause[i][10] - 1;
      delay(spd);
    }
    else if (relRepPlayPause[i][11] != 00) {
      digitalWrite(led[i], HIGH);
      relRepPlayPause[i][11] = relRepPlayPause[i][11] - 1;
      delay(spd);
    }
    else if (relRepPlayPause[i][12] != 00) {
      digitalWrite(led[i], LOW);
      relRepPlayPause[i][12] = relRepPlayPause[i][12] - 1;
      delay(spd);
    }
    else if (relRepPlayPause[i][13] != 00) {
      digitalWrite(led[i], HIGH);
      relRepPlayPause[i][13] = relRepPlayPause[i][13] - 1;
      delay(spd);
    }
    else if (relRepPlayPause[i][14] != 00) {
      digitalWrite(led[i], LOW);
      relRepPlayPause[i][14] = relRepPlayPause[i][14] - 1;
      delay(spd);
    }
    else if (relRepPlayPause[i][15] != 00) {
      digitalWrite(led[i], HIGH);
      relRepPlayPause[i][15] = relRepPlayPause[i][15] - 1;
      delay(spd);
    }
    else if (relRepPlayPause[i][16] != 00) {
      digitalWrite(led[i], LOW);
      relRepPlayPause[i][16] = relRepPlayPause[i][16] - 1;
      delay(spd);
    }
    else if (relRepPlayPause[i][17] != 00) {
      digitalWrite(led[i], HIGH);
      relRepPlayPause[i][17] = relRepPlayPause[i][17] - 1;
      delay(spd);
    }
    else if (relRepPlayPause[i][18] != 00) {
      digitalWrite(led[i], LOW);
      relRepPlayPause[i][18] = relRepPlayPause[i][18] - 1;
      delay(spd);
    }
    else if (relRepPlayPause[i][19] != 00) {
      digitalWrite(led[i], HIGH);
      relRepPlayPause[i][19] = relRepPlayPause[i][19] - 1;
      delay(spd);
    }
    else if (relRepPlayPause[i][20] != 00) {
      digitalWrite(led[i], LOW);
      relRepPlayPause[i][20] = relRepPlayPause[i][20] - 1;
      delay(spd);
    }
    else if (relRepPlayPause[i][21] != 00) {
      digitalWrite(led[i], HIGH);
      relRepPlayPause[i][21] = relRepPlayPause[i][21] - 1;
      delay(spd);
    }
    else if (relRepPlayPause[i][22] != 00) {
      digitalWrite(led[i], LOW);
      relRepPlayPause[i][22] = relRepPlayPause[i][22] - 1;
      delay(spd);
    }
    else if (relRepPlayPause[i][23] != 00) {
      digitalWrite(led[i], HIGH);
      relRepPlayPause[i][23] = relRepPlayPause[i][23] - 1;
      delay(spd);
    }
   }

    for(int i = 0; i < 6; i++){
      if ((relRepPlayPause[i][0]==0)&&(relRepPlayPause[i][0]==relRepPlayPause[i][1]) && (relRepPlayPause[i][0] == relRepPlayPause[i][2]) &&(relRepPlayPause[i][0]==relRepPlayPause[i][3]) && (relRepPlayPause[i][0] == relRepPlayPause[i][4]) &&(relRepPlayPause[i][0]==relRepPlayPause[i][5]) && (relRepPlayPause[i][0] == relRepPlayPause[i][6]) &&(relRepPlayPause[i][0]==relRepPlayPause[i][7]) && (relRepPlayPause[i][0] == relRepPlayPause[i][8]) &&(relRepPlayPause[i][0]==relRepPlayPause[i][9]) && (relRepPlayPause[i][0] == relRepPlayPause[i][10]) &&(relRepPlayPause[i][0]==relRepPlayPause[i][11]) && (relRepPlayPause[i][0] == relRepPlayPause[i][12]) &&(relRepPlayPause[i][0]==relRepPlayPause[i][13]) && (relRepPlayPause[i][0] == relRepPlayPause[i][14]) &&(relRepPlayPause[i][0]==relRepPlayPause[i][15]) && (relRepPlayPause[i][0] == relRepPlayPause[i][16]) &&(relRepPlayPause[i][0]==relRepPlayPause[i][17]) && (relRepPlayPause[i][0] == relRepPlayPause[i][18]) &&(relRepPlayPause[i][0]==relRepPlayPause[i][19]) && (relRepPlayPause[i][0] == relRepPlayPause[i][20]) &&(relRepPlayPause[i][0]==relRepPlayPause[i][21]) && (relRepPlayPause[i][0] == relRepPlayPause[i][22]) &&(relRepPlayPause[i][0]==relRepPlayPause[i][23]))
      {
        for(int j = 0; j < ARRAY_SIZE_Y; j++){
          relRepPlayPause[i][j] = relPlayPause[i][j];
        }
      }
    }
  }
}  
