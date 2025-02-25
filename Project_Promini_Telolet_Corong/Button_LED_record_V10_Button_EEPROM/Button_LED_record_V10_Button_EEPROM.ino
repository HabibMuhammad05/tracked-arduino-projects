#include <Wire.h>
#define EEPROM_ADDR 0x50 // I2C address of AT24C256
#define ARRAY_SIZE_X 6   // Assuming your array size is 6x12
#define ARRAY_SIZE_Y 12

#include <PCF8574.h>
PCF8574 pcf20(0x27);
const byte pcfButtonPins[] = {0, 1, 2, 3, 4, 5}; // Pins for the buttons on PCF8574
const byte ledPins[] = {7, 6, 5, 4, 3, 2};    // Pins for the LEDs
unsigned int buttonMillis;
bool previousButtonStates[6] = {false};

#define DATA_PIN 10
#define LATCH_PIN 11
#define CLOCK_PIN 12

const uint8_t led[] = {7, 6, 5, 4, 3, 2};
const uint8_t but[] = {8, 9, A0, A1, A2, A3};

bool buttonState[6] = {LOW};

#define recordPin A0
#define playPin A1


bool recordMod = 0;
bool playMod = 0;
bool readMod = 0;
//녹음 및 재생 모드 관련 변수 끝

uint8_t num = 0;
uint8_t maxNum = 6;

uint8_t spd = 15;
//String numStr = "0";

//Start relay 1 storage variable
uint16_t relPlayPause[6][12] = {0};
uint16_t relRepPlayPause[6][12] = {0};

uint16_t relStorePlayPause[6][12] = {0};
uint16_t relWarePlayPause[6][12] = {0};

void setup(){
  Serial.begin(9600);
  Wire.begin();
  pcf20.begin();
  
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  
  for ( int i = 0 ; i < 6 ; i++) {
    pinMode(but[i], INPUT);
    pinMode(led[i], OUTPUT);
    digitalWrite(led[i], LOW);
  }
}

void loop(){
  
//  for(int i=0; i<26; i++){
//    displayChar(i);
//  
//    delay(1000);
//  }
  
  unsigned int currentMillis = millis();
  if (Serial.available()) {
    String numStr = Serial.readString();
    num = numStr.toInt();
    
//    if(numStr == "rec"){ recPressed(); }
//    else if(numStr == "play"){ playPressed(); }
//    else if(numStr == "read"){ ReadPressed(); }
    
//    readAndPrintSingle2DArray(numStr.toInt());
  }

    if ((currentMillis - buttonMillis) >= 50) {
    buttonMillis = currentMillis;
    for (int i = 0; i < 6; i++) {
      bool buttonState = pcf20.readButton(pcfButtonPins[i]);
      if (buttonState != previousButtonStates[i]) {
        previousButtonStates[i] = buttonState;
        if (buttonState) {
          if (i == 0){
            Serial.println("But 1 Pressed, Recording...");
            recPressed();
          }else if (i == 1){
            Serial.println("But 2 Pressed, playing...");
            playPressed();
          }else if (i == 2){
            Serial.println("But 3 Pressed, Reading...");
            ReadPressed();
          }else if (i == 3){
            Serial.println("But 4 Pressed, adding...");
            if (num < maxNum){ num++; }
            else{ num = maxNum; }
            displayNumber(num);
          }else if (i == 4){
            Serial.println("But 5 Pressed, subtracting...");
            if (num > 0){ num--; }
            else{ num = 0; }
            displayNumber(num);
          }
        }
      }
    }
  }
  
  
  //Operation part when record mode is On
  if ((recordMod == 1) && (playMod == 0 ) && (readMod == 0)) {
      for(int i = 0; i <= 6; i++){
        buttonState[i] = !digitalRead(but[i]);
    }

  for(int i = 0; i <6; i++){
    //버튼1이 눌려있을 때
    if (buttonState[i] == LOW) {
      displayRec(i, 0);
      digitalWrite(led[i], HIGH);
      delay(10);

      //버튼1 눌려있는 것 녹화 시작
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
    }
    //버튼1이 띄워져 있을 때
    else {
      digitalWrite(led[i], LOW);
      delay(10);

      //버튼 1 띄워져 있는 것 녹화 시작
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
      //버튼 1 띄워져 있는 것 녹화 끝
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
  if ((playMod == 1) && (recordMod == 0) && (readMod == 0)) {

   for(int i = 0; i < 6; i++){
    //릴레이1 녹화 재생 관련 코드 시작
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
    //릴레이1 녹화 재생 관련 코드 끝
   }

    for(int i = 0; i < 6; i++){
      //When all Relay 1 recording execution variables become 0, reset the recording execution variables
      if ((relRepPlayPause[i][0]==0)&&(relRepPlayPause[i][0]==relRepPlayPause[i][1]) && (relRepPlayPause[i][0] == relRepPlayPause[i][2]) &&(relRepPlayPause[i][0]==relRepPlayPause[i][3]) && (relRepPlayPause[i][0] == relRepPlayPause[i][4]) &&(relRepPlayPause[i][0]==relRepPlayPause[i][5]) && (relRepPlayPause[i][0] == relRepPlayPause[i][6]) &&(relRepPlayPause[i][0]==relRepPlayPause[i][7]) && (relRepPlayPause[i][0] == relRepPlayPause[i][8]) &&(relRepPlayPause[i][0]==relRepPlayPause[i][9]) && (relRepPlayPause[i][0] == relRepPlayPause[i][10]) &&(relRepPlayPause[i][0]==relRepPlayPause[i][11]))
      {
        for(int j = 0; j <= 11; j++){
          relRepPlayPause[i][j] = relPlayPause[i][j];
        }
      }
    }
  }
  
  //Saat memasuki mode bavca
  if ((playMod == 0) && (recordMod == 0) && (readMod == 1)) {
      
   for(int i = 0; i < 6; i++){
    //릴레이1 녹화 재생 관련 코드 시작
    if (relStorePlayPause[i][0] != 00) {
      digitalWrite(led[i], LOW);
      relStorePlayPause[i][0] = relStorePlayPause[i][0] - 1;
      delay(8);
    }
    else if (relStorePlayPause[i][1] != 00) {
      digitalWrite(led[i], HIGH);
      relStorePlayPause[i][1] = relStorePlayPause[i][1] - 1;
      delay(8);
    }
    else if (relStorePlayPause[i][2] != 00) {
      digitalWrite(led[i], LOW);
      relStorePlayPause[i][2] = relStorePlayPause[i][2] - 1;
      delay(8);
    }
    else if (relStorePlayPause[i][3] != 00) {
      digitalWrite(led[i], HIGH);
      relStorePlayPause[i][3] = relStorePlayPause[i][3] - 1;
      delay(8);
    }
    else if (relStorePlayPause[i][4] != 00) {
      digitalWrite(led[i], LOW);
      relStorePlayPause[i][4] = relStorePlayPause[i][4] - 1;
      delay(8);
    }
    else if (relStorePlayPause[i][5] != 00) {
      digitalWrite(led[i], HIGH);
      relStorePlayPause[i][5] = relStorePlayPause[i][5] - 1;
      delay(8);
    }
    else if (relStorePlayPause[i][6] != 00) {
      digitalWrite(led[i], LOW);
      relStorePlayPause[i][6] = relStorePlayPause[i][6] - 1;
      delay(8);
    }
    else if (relStorePlayPause[i][7] != 00) {
      digitalWrite(led[i], HIGH);
      relStorePlayPause[i][7] = relStorePlayPause[i][7] - 1;
      delay(8);
    }
    else if (relStorePlayPause[i][8] != 00) {
      digitalWrite(led[i], LOW);
      relStorePlayPause[i][8] = relStorePlayPause[i][8] - 1;
      delay(8);
    }
    else if (relStorePlayPause[i][9] != 00) {
      digitalWrite(led[i], HIGH);
      relStorePlayPause[i][9] = relStorePlayPause[i][9] - 1;
      delay(8);
    }
    else if (relStorePlayPause[i][10] != 00) {
      digitalWrite(led[i], LOW);
      relStorePlayPause[i][10] = relStorePlayPause[i][10] - 1;
      delay(8);
    }
    else if (relStorePlayPause[i][11] != 00) {
      digitalWrite(led[i], HIGH);
      relStorePlayPause[i][11] = relStorePlayPause[i][11] - 1;
      delay(8);
    }
   }

    for(int i = 0; i < 6; i++){
      //When all Relay 1 recording execution variables become 0, reset the recording execution variables
      if ((relStorePlayPause[i][0]==0)&&(relStorePlayPause[i][0]==relStorePlayPause[i][1]) && (relStorePlayPause[i][0] == relStorePlayPause[i][2]) &&(relStorePlayPause[i][0]==relStorePlayPause[i][3]) && (relStorePlayPause[i][0] == relStorePlayPause[i][4]) &&(relStorePlayPause[i][0]==relStorePlayPause[i][5]) && (relStorePlayPause[i][0] == relStorePlayPause[i][6]) &&(relStorePlayPause[i][0]==relStorePlayPause[i][7]) && (relStorePlayPause[i][0] == relStorePlayPause[i][8]) &&(relStorePlayPause[i][0]==relStorePlayPause[i][9]) && (relStorePlayPause[i][0] == relStorePlayPause[i][10]) &&(relStorePlayPause[i][0]==relStorePlayPause[i][11]))
      {
        for(int j = 0; j <= 11; j++){
          relStorePlayPause[i][j] = relWarePlayPause[i][j];
        }
      }
    }
  }
}

//=======================PLAYBACK FUNCTIONS=========================//
void recPressed(){  
    recordMod = 1;
    playMod = 0;
    readMod = 0;
    Serial.println("Record Mode On");
    displayRec(6, 0);
    
    for(int i = 0; i <= 11; i++){
      //Initialize relay recording variables
      for (int j = 0; j < 6; j++) {
        relPlayPause[j][i] = 0;
      }
    }
    Serial.println(recordMod);
}

void playPressed(){
    playMod = 1;
    recordMod = 0;
    readMod = 0;
    Serial.println("play mode On");
    displayRec(0, 1);
    assignValues();
    
    Serial.println(playMod);
}

void ReadPressed(){
    playMod = 0;
    recordMod = 0;
    readMod = 1;
    Serial.println("read mode On");
    displayNumber(num);
    readAndPrintSingle2DArray(num);
    
    Serial.println(playMod);
}

void assignValues(){
       for (int j = 0; j < 6; j++) {
        //Initialize by assigning the recording variable to the relay playback variable
        Serial.print("{");
         for(int i = 0; i < 12; i++){
          relRepPlayPause[j][i] = relPlayPause[j][i];
          Serial.print(relRepPlayPause[j][i]);
          if(i < 11){
            Serial.print(", ");
          }
        }
        Serial.print("},");
        Serial.println();
      }
}

void ReadValues(){
       Serial.println("===========storePlayPause==============");
       for (int j = 0; j < 6; j++) {
        //Initialize by assigning the recording variable to the relay playback variable
        Serial.print("{");
         for(int i = 0; i < 12; i++){
          relStorePlayPause[j][i] = relWarePlayPause[j][i];
          Serial.print(relStorePlayPause[j][i]);
          if(i < 11){
            Serial.print(", ");
          }
        }
        Serial.print("},");
        Serial.println();
      }

  }

//=======================EEPROM FUNCTIONS=========================//
//void writeArrayToExternalEEPROM() {
//  int address = 0;
//  for (int i = 0; i < 7; i++) { // Assuming you have 7 2D arrays
//    for (int j = 0; j < ARRAY_SIZE_X; j++) {
//      for (int k = 0; k < ARRAY_SIZE_Y; k++) {
//        uint16_t data = relWarePlayPause[i][j][k];
//        writeEEPROM(address, data);
//        address += sizeof(uint16_t);
//      }
//    }
//  }
//}

void readAndPrintSingle2DArray(int index) {
  Serial.println("===========EEPROM READ==============");
  int address = index * ARRAY_SIZE_X * ARRAY_SIZE_Y * sizeof(uint16_t);
  for (int i = 0; i < ARRAY_SIZE_X; i++) {
      Serial.print("{");
    for (int j = 0; j < ARRAY_SIZE_Y; j++) {
      uint16_t data;
      readEEPROM(address, data);
      Serial.print(data);
      relWarePlayPause[j][i] = data;
      relStorePlayPause[j][i] = relWarePlayPause[j][i];
      Serial.print( (j < (ARRAY_SIZE_Y-1)) ? ", " : "" );
      address += sizeof(uint16_t);
    }
    Serial.println( (i < (ARRAY_SIZE_X-1)) ? "}," : "}" );
  }
    Serial.println("ADDR: " + String(address));
}

void writeEEPROM(int address, uint16_t data) {
  Wire.beginTransmission(EEPROM_ADDR);
  Wire.write((int)(address >> 8));   // MSB of address
  Wire.write((int)(address & 0xFF)); // LSB of address
  Wire.write((uint8_t)(data >> 8));  // MSB of data
  Wire.write((uint8_t)(data & 0xFF)); // LSB of data
  Wire.endTransmission();
  delay(5); // Delay to allow EEPROM write cycle to complete
}

void readEEPROM(int address, uint16_t &data) {
  Wire.beginTransmission(EEPROM_ADDR);
  Wire.write((int)(address >> 8));   // MSB of address
  Wire.write((int)(address & 0xFF)); // LSB of address
  Wire.endTransmission();
  Wire.requestFrom(EEPROM_ADDR, 2); // Request 2 bytes of data
  data = Wire.read() << 8; // MSB
  data |= Wire.read();     // LSB
}

void displayNumber(uint8_t number) {
  
  const byte commonAnodeSegments[] = {
    B10000001, // 0
    B11101101, // 1
    B01000011, // 2
    B01001001, // 3
    B00101101, // 4
    B00011001, // 5
    B00010001, // 6
    B11001101, // 7
    B00000001, // 8
    B00001001  // 9
  };
  const byte commonCathodeSegments[] = {
  B01111110, // 0
  B00010010, // 1
  B10111100, // 2
  B10110110, // 3
  B11010010, // 4
  B11100110, // 5
  B11101110, // 6
  B00110010, // 7
  B11111110, // 8
  B11110110  // 9
};
  
  int tens = number / 10;
  int units = number % 10;
  
  shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, commonCathodeSegments[units]);
  shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, commonAnodeSegments[tens]);
  
  digitalWrite(LATCH_PIN, HIGH);
  digitalWrite(LATCH_PIN, LOW);
}


void displayRec(uint8_t index, uint8_t mod) {
 const byte putar[7] = {B01000000, B00100000, B00010000, B00000010, B00000100, B00001000, B00000000}; 
 const byte blank = B00000000;
 const byte r = B10010111;
 const byte p = B00000111;
 const byte l = B01001100;
 
  if(mod == 0){
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, putar[index]);
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, r);
  }else if (mod == 1){
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, l);
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, p);
  }
  
  digitalWrite(LATCH_PIN, HIGH);
  digitalWrite(LATCH_PIN, LOW);
}

//const byte character[] = {
//    B11111010,//A
//    B11001110,//B
//    B01101100,//C
//    B10011110,//D
//    B11111100,//E
//    B11101000,//F
//    B11110110,//G
//    B11011010,//H
//    B01001000,//I
//    B00010110,//J
//    B11101010,//K
//    B01001100,//L
//    B10110110,//M
//    B01111010,//N
//    B10001110,//O
//    B11111000,//P
//    B01111111,//Q
//    B01101000,//R17
//    B11100110,//S
//    B11001100,//T
//    B01011110,//U
//    B00001110,//V
//    B11101100,//W
//    B11011010,//X
//    B11011100,//Y
//    B10111100//Z
//  };
