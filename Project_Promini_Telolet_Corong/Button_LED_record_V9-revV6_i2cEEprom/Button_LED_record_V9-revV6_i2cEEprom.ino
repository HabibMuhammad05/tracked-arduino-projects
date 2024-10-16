//#include "OneButton.h"
//OneButton pb(13, true, true);  //(Pb_Pin;  true = ActiveLow;  true = button PullUp)
//OneButton pb2(A5, true, true);  //(Pb_Pin;  true = ActiveLow;  true = button PullUp)


const uint8_t led[] = {7, 6, 5, 4, 3, 2};
const uint8_t but[] = {8, 9, A0, A1, A2, A3};

bool buttonState[6] = {LOW};

//#define recordLED A2
//#define playLED A3

bool recordMod = 0;
bool playMod = 0;
bool readMod = 0;

uint8_t num = 2;

//Start relay 1 storage variable
uint16_t relPlayPause[6][12] = {0};// count, 0=play, 1=pause
uint16_t relRepPlayPause[6][12] = {0};// count, 0=play, 1=pause

uint16_t relStorePlayPause[1][6][12] = {0};
const uint16_t relWarePlayPause[3][6][12] = {
  {
    {25, 6, 18, 3, 66, 2, 40, 0, 0, 0, 0},
    {62, 7, 44, 2, 45, 0, 0, 0, 0, 0, 0},
    {39, 6, 29, 2, 31, 3, 50, 0, 0, 0, 0},
    {69, 4, 4, 3, 22, 3, 55, 0, 0, 0, 0},
    {33, 6, 14, 10, 22, 3, 8, 2, 62, 0, 0},
    {17, 9, 21, 3, 41, 3, 66, 0, 0, 0, 0}
  },
  {
    {55, 8, 24, 8, 146, 0, 0, 0, 0, 0, 0},
    {70, 8, 25, 9, 129, 0, 0, 0, 0, 0, 0},
    {79, 8, 33, 42, 79, 0, 0, 0, 0, 0, 0},
    {63, 8, 40, 51, 79, 0, 0, 0, 0, 0, 0},
    {48, 8, 39, 9, 137, 0, 0, 0, 0, 0, 0},
    {241, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  },
  {
    {37, 4, 13, 5, 34, 5, 86, 13, 17, 23, 210, 0},
    {73, 6, 74, 46, 49, 23, 47, 17, 35, 6, 86, 0},
    {92, 6, 38, 24, 120, 4, 59, 5, 36, 15, 74, 0},
    {48, 12, 12, 7, 7, 13, 19, 19, 10, 53, 236, 0},
    {32, 10, 25, 11, 27, 74, 35, 23, 56, 13, 148, 0},
    {473, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  }
};// count, 0=play, 1=pause

void setup(void)
{
//  pb.attachClick(recPressed);
//  pb.attachLongPressStop(playPressed);
//  pb.attachDoubleClick(ReadPressed);
  
  for ( int i = 0 ; i < 6 ; i++) {
    pinMode(but[i], INPUT);
    pinMode(led[i], OUTPUT);
    digitalWrite(led[i], LOW);
  }
  Serial.begin(9600);
  Serial.println("Setup Arduino....");
}

void loop(void)
{
  if (Serial.available() > 0) { // Check if data is available to read
    String receivedString = Serial.readStringUntil('\n'); // Read the incoming data until a newline character is received
    Serial.println(receivedString); // Print the received string back to the Serial Monitor
    
    if(receivedString == "rec"){ recPressed(); }
    else if(receivedString == "play"){ playPressed(); }
    else if(receivedString == "read"){ ReadPressed(); }
  }
  
  //Operation part when record mode is On
  if ((recordMod == 1) && (playMod == 0 ) && (readMod == 0)) {
      for(int i = 0; i <= 6; i++){
        buttonState[i] = digitalRead(but[i]);
    }

  for(int i = 0; i <6; i++){
    //버튼1이 눌려있을 때
    if (buttonState[i] == HIGH) {
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
      delay(8);
    }
    else if (relRepPlayPause[i][1] != 00) {
      digitalWrite(led[i], HIGH);
      relRepPlayPause[i][1] = relRepPlayPause[i][1] - 1;
      delay(8);
    }
    else if (relRepPlayPause[i][2] != 00) {
      digitalWrite(led[i], LOW);
      relRepPlayPause[i][2] = relRepPlayPause[i][2] - 1;
      delay(8);
    }
    else if (relRepPlayPause[i][3] != 00) {
      digitalWrite(led[i], HIGH);
      relRepPlayPause[i][3] = relRepPlayPause[i][3] - 1;
      delay(8);
    }
    else if (relRepPlayPause[i][4] != 00) {
      digitalWrite(led[i], LOW);
      relRepPlayPause[i][4] = relRepPlayPause[i][4] - 1;
      delay(8);
    }
    else if (relRepPlayPause[i][5] != 00) {
      digitalWrite(led[i], HIGH);
      relRepPlayPause[i][5] = relRepPlayPause[i][5] - 1;
      delay(8);
    }
    else if (relRepPlayPause[i][6] != 00) {
      digitalWrite(led[i], LOW);
      relRepPlayPause[i][6] = relRepPlayPause[i][6] - 1;
      delay(8);
    }
    else if (relRepPlayPause[i][7] != 00) {
      digitalWrite(led[i], HIGH);
      relRepPlayPause[i][7] = relRepPlayPause[i][7] - 1;
      delay(8);
    }
    else if (relRepPlayPause[i][8] != 00) {
      digitalWrite(led[i], LOW);
      relRepPlayPause[i][8] = relRepPlayPause[i][8] - 1;
      delay(8);
    }
    else if (relRepPlayPause[i][9] != 00) {
      digitalWrite(led[i], HIGH);
      relRepPlayPause[i][9] = relRepPlayPause[i][9] - 1;
      delay(8);
    }
    else if (relRepPlayPause[i][10] != 00) {
      digitalWrite(led[i], LOW);
      relRepPlayPause[i][10] = relRepPlayPause[i][10] - 1;
      delay(8);
    }
    else if (relRepPlayPause[i][11] != 00) {
      digitalWrite(led[i], HIGH);
      relRepPlayPause[i][11] = relRepPlayPause[i][11] - 1;
      delay(8);
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
    if (relStorePlayPause[0][i][0] != 00) {
      digitalWrite(led[i], LOW);
      relStorePlayPause[0][i][0] = relStorePlayPause[0][i][0] - 1;
      delay(8);
    }
    else if (relStorePlayPause[0][i][1] != 00) {
      digitalWrite(led[i], HIGH);
      relStorePlayPause[0][i][1] = relStorePlayPause[0][i][1] - 1;
      delay(8);
    }
    else if (relStorePlayPause[0][i][2] != 00) {
      digitalWrite(led[i], LOW);
      relStorePlayPause[0][i][2] = relStorePlayPause[0][i][2] - 1;
      delay(8);
    }
    else if (relStorePlayPause[0][i][3] != 00) {
      digitalWrite(led[i], HIGH);
      relStorePlayPause[0][i][3] = relStorePlayPause[0][i][3] - 1;
      delay(8);
    }
    else if (relStorePlayPause[0][i][4] != 00) {
      digitalWrite(led[i], LOW);
      relStorePlayPause[0][i][4] = relStorePlayPause[0][i][4] - 1;
      delay(8);
    }
    else if (relStorePlayPause[0][i][5] != 00) {
      digitalWrite(led[i], HIGH);
      relStorePlayPause[0][i][5] = relStorePlayPause[0][i][5] - 1;
      delay(8);
    }
    else if (relStorePlayPause[0][i][6] != 00) {
      digitalWrite(led[i], LOW);
      relStorePlayPause[0][i][6] = relStorePlayPause[0][i][6] - 1;
      delay(8);
    }
    else if (relStorePlayPause[0][i][7] != 00) {
      digitalWrite(led[i], HIGH);
      relStorePlayPause[0][i][7] = relStorePlayPause[0][i][7] - 1;
      delay(8);
    }
    else if (relStorePlayPause[0][i][8] != 00) {
      digitalWrite(led[i], LOW);
      relStorePlayPause[0][i][8] = relStorePlayPause[0][i][8] - 1;
      delay(8);
    }
    else if (relStorePlayPause[0][i][9] != 00) {
      digitalWrite(led[i], HIGH);
      relStorePlayPause[0][i][9] = relStorePlayPause[0][i][9] - 1;
      delay(8);
    }
    else if (relStorePlayPause[0][i][10] != 00) {
      digitalWrite(led[i], LOW);
      relStorePlayPause[0][i][10] = relStorePlayPause[0][i][10] - 1;
      delay(8);
    }
    else if (relStorePlayPause[0][i][11] != 00) {
      digitalWrite(led[i], HIGH);
      relStorePlayPause[0][i][11] = relStorePlayPause[0][i][11] - 1;
      delay(8);
    }
   }

    for(int i = 0; i < 6; i++){
      //When all Relay 1 recording execution variables become 0, reset the recording execution variables
      if ((relStorePlayPause[0][i][0]==0)&&(relStorePlayPause[0][i][0]==relStorePlayPause[0][i][1]) && (relStorePlayPause[0][i][0] == relStorePlayPause[0][i][2]) &&(relStorePlayPause[0][i][0]==relStorePlayPause[0][i][3]) && (relStorePlayPause[0][i][0] == relStorePlayPause[0][i][4]) &&(relStorePlayPause[0][i][0]==relStorePlayPause[0][i][5]) && (relStorePlayPause[0][i][0] == relStorePlayPause[0][i][6]) &&(relStorePlayPause[0][i][0]==relStorePlayPause[0][i][7]) && (relStorePlayPause[0][i][0] == relStorePlayPause[0][i][8]) &&(relStorePlayPause[0][i][0]==relStorePlayPause[0][i][9]) && (relStorePlayPause[0][i][0] == relStorePlayPause[0][i][10]) &&(relStorePlayPause[0][i][0]==relStorePlayPause[0][i][11]))
      {
        ReadValues();
      }
    }
  }
}

void recPressed(){  
    recordMod = 1;
    playMod = 0;
    readMod = 0;
    Serial.println("Record Mode On");
//    digitalWrite(recordLED, HIGH);
//    digitalWrite(playLED, LOW);
    
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
//      digitalWrite(playLED, HIGH);
//      digitalWrite(recordLED, LOW);
      assignValues();
    
    Serial.println(playMod);
}
void ReadPressed(){
    playMod = 0;
    recordMod = 0;
    readMod = 1;
      Serial.println("read mode On");
//      digitalWrite(playLED, HIGH);
//      digitalWrite(recordLED, LOW);
      ReadValues();
    
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
          relStorePlayPause[0][j][i] = relWarePlayPause[num][j][i];
          Serial.print(relStorePlayPause[0][j][i]);
          if(i < 11){
            Serial.print(", ");
          }
        }
        Serial.print("},");
        Serial.println();
      }

  }
