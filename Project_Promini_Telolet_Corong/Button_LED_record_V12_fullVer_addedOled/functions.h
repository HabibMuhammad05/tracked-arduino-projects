//void oledDisp(uint8_t mod, uint8_t num, uint8_t index){
//  bool plus = false;
//  uint8_t tempo = spd;
//  
//  char numStr[4];         
//  sprintf(numStr, "%03d", num);
//  
//  if (tempo >= 10) {
//    tempo = tempo - 10;
//    plus = true;
//  }
//  String tmpoStr = String(tempo);
//  
//  u8g2.clearBuffer();
//  switch (mod){ // determine which screen is displayed
//    case 0: u8g2.drawXBMP(0, 1, 128, 52, stopSc); break;
//    case 1: u8g2.drawXBMP(0, 1, 128, 52, playSc); break;
//    case 2: u8g2.drawXBMP(0, 1, 128, 52, chooseSc); break;
//    case 3: u8g2.drawXBMP(0, 1, 128, 52, recSc); break;
//  }
//  
//  u8g2.setFont(u8g2_font_haxrcorp4089_tr);
//  if (plus) u8g2.drawStr(110, 8, "+");  //change between tempo plus mode or minus mode
//  else u8g2.drawStr(110, 8, "-");
//  
//  u8g2.setFont(u8g2_font_6x10_tr);      //display the number and tempo
//  u8g2.drawStr(116, 8, tmpoStr.c_str());
//  u8g2.setFont(u8g2_font_profont29_tr);
//  u8g2.drawStr(40, 33, numStr);
//
//  u8g2.setFont(u8g2_font_t0_13b_tr); //display the pressed note
//  switch(index){
//    case 0: u8g2.drawStr(1, 64, "DO"); break;
//    case 1: u8g2.drawStr(22, 64, "RE"); break;
//    case 2: u8g2.drawStr(43, 64, "MI"); break;
//    case 3: u8g2.drawStr(64, 64, "FA"); break;
//    case 4: u8g2.drawStr(85, 64, "SOL"); break;
//    case 5: u8g2.drawStr(113, 64, "LA"); break;
//    case 6: break;
//  }
//  u8g2.sendBuffer();
//}

//===================================DISPLAY FUNCTIONS==================================//
void displayNumber(uint8_t number) {
  int tens = number / 10;
  int units = number % 10;
//  String num = String(number);
  
  shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, commonCathodeSegments[units]);
  shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, commonAnodeSegments[tens]);
  
  digitalWrite(LATCH_PIN, HIGH);
  digitalWrite(LATCH_PIN, LOW);
  
//  oledDisp(0, num, 6);
}

void displayRec(uint8_t index, bool mod) {
  if(mod == 0){
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, putar[index]);
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, r);
  }else if (mod == 1){
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, l);
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, p);
//    oledDisp(1, num, 6);
  }
  
  digitalWrite(LATCH_PIN, HIGH);
  digitalWrite(LATCH_PIN, LOW);
}

void displayTempo(uint8_t num){
    if(num >= 10){
      shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, commonCathodeSegments[num-10]);
    }else{
      shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, commonCathodeSegments[num]);
    }
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, t);
    
    digitalWrite(LATCH_PIN, HIGH);
    digitalWrite(LATCH_PIN, LOW);
}


//===================================EEPROM FUNCTIONS==================================//
void readEEPROM(int address, uint16_t &data) {
  Wire.beginTransmission(EEPROM_ADDR);
  Wire.write((int)(address >> 8));   // MSB of address
  Wire.write((int)(address & 0xFF)); // LSB of address
  Wire.endTransmission();
  Wire.requestFrom(EEPROM_ADDR, 2); // Request 2 bytes of data
  data = Wire.read() << 8; // MSB
  data |= Wire.read();     // LSB
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

void writeArrayToExternalEEPROM(int index) {
  int address = index * ARRAY_SIZE_X * ARRAY_SIZE_Y * sizeof(uint16_t);
  Serial.println("simpan index : " + String(index) + ", ADDR : " + String(address));
    for (int j = 0; j < ARRAY_SIZE_X; j++) {
      for (int i = 0; i < ARRAY_SIZE_Y; i++) {
        uint16_t data = relPlayPause[j][i];
        writeEEPROM(address, data);
        address += sizeof(uint16_t);
      }
    }
  }

void assignValues(){
       for (int j = 0; j < ARRAY_SIZE_X; j++) {
        Serial.print("{");
         for(int i = 0; i < ARRAY_SIZE_Y; i++){
          relRepPlayPause[j][i] = relPlayPause[j][i];
          Serial.print(relRepPlayPause[j][i]);
          if(i < (ARRAY_SIZE_Y - 1)){
            Serial.print(", ");
          }
        }
        Serial.print("},");
        Serial.println();
      }
}

void readAndPrintSingle2DArray(int index) {
  Serial.println("===========EEPROM READ==============");
  int address = index * ARRAY_SIZE_X * ARRAY_SIZE_Y * sizeof(uint16_t);
  Serial.println("ADDR: " + String(address));
  
  for (int i = 0; i < ARRAY_SIZE_X; i++) {
      Serial.print("{");
    for (int j = 0; j < ARRAY_SIZE_Y; j++) {
      uint16_t data;
      readEEPROM(address, data);
      Serial.print(data);
      relPlayPause[i][j] = data;
      relRepPlayPause[i][j] = relPlayPause[i][j];
      Serial.print( (j < (ARRAY_SIZE_Y-1)) ? ", " : "" );
      address += sizeof(uint16_t);
    }
    Serial.println( (i < (ARRAY_SIZE_X-1)) ? "}," : "}" );
  }
}

void getIndex(uint16_t &num, bool mod){
  if (mod){
    readEEPROM(32000, num);
    Serial.println("data on 32k : " + String(num));
  }else{
    writeEEPROM(32000, num);
  }
}

//==================================PLAYBACK FUNCTIONS=================================//
void recPressed(){  
    recordMod = 1;
    playMod = 0;
    Serial.println("Record Mode On");
    displayRec(6, 0);
    
    for(int i = 0; i < ARRAY_SIZE_X; i++){
      //Initialize relay recording variables
      for (int j = 0; j < ARRAY_SIZE_Y; j++) {
        relPlayPause[i][j] = 0;
      }
    }
}

void playPressed(bool stat){
  playMod = 1;
  recordMod = 0;
  if (stat){
    Serial.println("play mode On");
    displayRec(0, 1);
    assignValues();
  }else{
    Serial.println("read mode On");
    displayRec(0, 1);
    readAndPrintSingle2DArray(num);
  }
}



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