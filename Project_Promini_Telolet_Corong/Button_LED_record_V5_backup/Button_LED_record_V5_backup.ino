#include "OneButton.h"
OneButton pb(A0, true, true);  //(Pb_Pin;  true = ActiveLow;  true = button PullUp)
//OneButton pb2(A5, true, true);  //(Pb_Pin;  true = ActiveLow;  true = button PullUp)

const uint8_t but[] = {2, 3, 4, 5, 6, 7};
const uint8_t led[] = {8, 9, 10, 11, 12, 13};

bool buttonState[6] = {LOW};

#define recordPin A0
#define playPin A1

#define recordLED A2
#define playLED A3

bool recordMod = 0;
bool playMod = 0;
//녹음 및 재생 모드 관련 변수 끝



//Start relay 1 storage variable
uint16_t relPlayPause[6][12] = {0};// count, 0=play, 1=pause
uint16_t relRepPlayPause[6][12] = {0};// count, 0=play, 1=pause

uint16_t relStorePlayPause[1][6][12] = {0};
const uint16_t relWarePlayPause[8][6][12] = {
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
    {241, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  },
  {
    {55, 8, 24, 8, 146, 0, 0, 0, 0, 0, 0},
    {70, 8, 25, 9, 129, 0, 0, 0, 0, 0, 0},
    {79, 8, 33, 42, 79, 0, 0, 0, 0, 0, 0},
    {63, 8, 40, 51, 79, 0, 0, 0, 0, 0, 0},
    {48, 8, 39, 9, 137, 0, 0, 0, 0, 0, 0},
    {241, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  },
  {
    {55, 8, 24, 8, 146, 0, 0, 0, 0, 0, 0},
    {70, 8, 25, 9, 129, 0, 0, 0, 0, 0, 0},
    {79, 8, 33, 42, 79, 0, 0, 0, 0, 0, 0},
    {63, 8, 40, 51, 79, 0, 0, 0, 0, 0, 0},
    {48, 8, 39, 9, 137, 0, 0, 0, 0, 0, 0},
    {241, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  },
  {
    {55, 8, 24, 8, 146, 0, 0, 0, 0, 0, 0},
    {70, 8, 25, 9, 129, 0, 0, 0, 0, 0, 0},
    {79, 8, 33, 42, 79, 0, 0, 0, 0, 0, 0},
    {63, 8, 40, 51, 79, 0, 0, 0, 0, 0, 0},
    {48, 8, 39, 9, 137, 0, 0, 0, 0, 0, 0},
    {241, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  },
  {
    {55, 8, 24, 8, 146, 0, 0, 0, 0, 0, 0},
    {70, 8, 25, 9, 129, 0, 0, 0, 0, 0, 0},
    {79, 8, 33, 42, 79, 0, 0, 0, 0, 0, 0},
    {63, 8, 40, 51, 79, 0, 0, 0, 0, 0, 0},
    {48, 8, 39, 9, 137, 0, 0, 0, 0, 0, 0},
    {241, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  },
  {
    {55, 8, 24, 8, 146, 0, 0, 0, 0, 0, 0},
    {70, 8, 25, 9, 129, 0, 0, 0, 0, 0, 0},
    {79, 8, 33, 42, 79, 0, 0, 0, 0, 0, 0},
    {63, 8, 40, 51, 79, 0, 0, 0, 0, 0, 0},
    {48, 8, 39, 9, 137, 0, 0, 0, 0, 0, 0},
    {241, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  },
  {
    {55, 8, 24, 8, 146, 0, 0, 0, 0, 0, 0},
    {70, 8, 25, 9, 129, 0, 0, 0, 0, 0, 0},
    {79, 8, 33, 42, 79, 0, 0, 0, 0, 0, 0},
    {63, 8, 40, 51, 79, 0, 0, 0, 0, 0, 0},
    {48, 8, 39, 9, 137, 0, 0, 0, 0, 0, 0},
    {241, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  }
};// count, 0=play, 1=pause

void setup(void)
{
  Serial.begin(9600);
  pb.attachClick(recPressed);
  pb.attachLongPressStop(playPressed);
  pb.attachDoubleClick(ReadPressed);
  
  for ( int i = 2 ; i <= 7 ; i++) {
    pinMode(i, INPUT_PULLUP);
  }

  for ( int i = 8 ; i <= 13 ; i++ ) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
}

void loop(void)
{

  pb.tick();

  //Operation part when record mode is On
  if ((recordMod == 1) && (playMod == 0)) {
      for(int i = 0; i <= 6; i++){
        buttonState[i] = !digitalRead(but[i]);
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
      else {
        relPlayPause[i][23] = relPlayPause[i][23] + 1;
      }
      //버튼1 눌려있는 것 녹화 끝
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
      //버튼 1 띄워져 있는 것 녹화 끝
    }
  }
    
  }

  //Saat memasuki mode putar
  if ((playMod == 1) && (recordMod == 0)) {

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
//    else if (relRepPlayPause[i][12] != 00) {
//      digitalWrite(led[i], LOW);
//      relRepPlayPause[i][12] = relRepPlayPause[i][12] - 1;
//      delay(8);
//    }
//    else if (relRepPlayPause[i][13] != 00) {
//      digitalWrite(led[i], HIGH);
//      relRepPlayPause[i][13] = relRepPlayPause[i][13] - 1;
//      delay(8);
//    }
//    else if (relRepPlayPause[i][14] != 00) {
//      digitalWrite(led[i], LOW);
//      relRepPlayPause[i][14] = relRepPlayPause[i][14] - 1;
//      delay(8);
//    }
//    else if (relRepPlayPause[i][15] != 00) {
//      digitalWrite(led[i], HIGH);
//      relRepPlayPause[i][15] = relRepPlayPause[i][15] - 1;
//      delay(8);
//    }
//    else if (relRepPlayPause[i][16] != 00) {
//      digitalWrite(led[i], LOW);
//      relRepPlayPause[i][16] = relRepPlayPause[i][16] - 1;
//      delay(8);
//    }
//    else if (relRepPlayPause[i][17] != 00) {
//      digitalWrite(led[i], HIGH);
//      relRepPlayPause[i][17] = relRepPlayPause[i][17] - 1;
//      delay(8);
//    }
//    else if (relRepPlayPause[i][18] != 00) {
//      digitalWrite(led[i], LOW);
//      relRepPlayPause[i][18] = relRepPlayPause[i][18] - 1;
//      delay(8);
//    }
//    else if (relRepPlayPause[i][19] != 00) {
//      digitalWrite(led[i], HIGH);
//      relRepPlayPause[i][19] = relRepPlayPause[i][19] - 1;
//      delay(8);
//    }
//    else if (relRepPlayPause[i][20] != 00) {
//      digitalWrite(led[i], LOW);
//      relRepPlayPause[i][20] = relRepPlayPause[i][20] - 1;
//      delay(8);
//    }
//    else if (relRepPlayPause[i][21] != 00) {
//      digitalWrite(led[i], HIGH);
//      relRepPlayPause[i][21] = relRepPlayPause[i][21] - 1;
//      delay(8);
//    }
//    else if (relRepPlayPause[i][22] != 00) {
//      digitalWrite(led[i], LOW);
//      relRepPlayPause[i][22] = relRepPlayPause[i][22] - 1;
//      delay(8);
//    }
//    else if (relRepPlayPause[i][23] != 00) {
//      digitalWrite(led[i], HIGH);
//      relRepPlayPause[i][23] = relRepPlayPause[i][23] - 1;
//      delay(8);
//    }
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
}

void recPressed(){  
    recordMod = 1;
    playMod = 0;
    Serial.println("Record Mode On");
    digitalWrite(recordLED, HIGH);
    digitalWrite(playLED, LOW);
    
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
      Serial.println("play mode On");
      digitalWrite(playLED, HIGH);
      digitalWrite(recordLED, LOW);
      assignValues();
    
    Serial.println(playMod);
}

void assignValues(){
       for (int j = 0; j < 6; j++) {
        //Initialize by assigning the recording variable to the relay playback variable
        Serial.print("{");
         for(int i = 0; i < 11; i++){
          relRepPlayPause[j][i] = relPlayPause[j][i];
          Serial.print(relRepPlayPause[j][i]);
          if(i < 23){
            Serial.print(", ");
          }
        }
        Serial.print("},");
        Serial.println();
      }
}

void ReadPressed(){
      playMod = 0;
      recordMod = 0;
      Serial.println("read mode On");
      digitalWrite(playLED, HIGH);
      digitalWrite(recordLED, LOW);
      ReadValues(0);
    
    Serial.println(playMod);
}

void ReadValues(uint8_t num){
       for (int j = 0; j < 6; j++) {
        //Initialize by assigning the recording variable to the relay playback variable
        Serial.print("{");
         for(int i = 0; i < 12; i++){
          relRunPlayPause[num][j][i] = relStorePlayPause[0][j][i];
          Serial.print(relRunPlayPause[0][j][i]);
          if(i < 11){
            Serial.print(", ");
          }
        }
        Serial.print("},");
        Serial.println();
      }
      
   for(int i = 0; i < 6; i++){
    //릴레이1 녹화 재생 관련 코드 시작
    if (relStorePlayPause[num][i][0] != 00) {
      digitalWrite(led[i], LOW);
      relStorePlayPause[num][i][0] = relStorePlayPause[num][i][0] - 1;
      delay(8);
    }
    else if (relStorePlayPause[num][i][1] != 00) {
      digitalWrite(led[i], HIGH);
      relStorePlayPause[num][i][1] = relStorePlayPause[num][i][1] - 1;
      delay(8);
    }
    else if (relStorePlayPause[num][i][2] != 00) {
      digitalWrite(led[i], LOW);
      relStorePlayPause[num][i][2] = relStorePlayPause[num][i][2] - 1;
      delay(8);
    }
    else if (relStorePlayPause[num][i][3] != 00) {
      digitalWrite(led[i], HIGH);
      relStorePlayPause[num][i][3] = relStorePlayPause[num][i][3] - 1;
      delay(8);
    }
    else if (relStorePlayPause[num][i][4] != 00) {
      digitalWrite(led[i], LOW);
      relStorePlayPause[num][i][4] = relStorePlayPause[num][i][4] - 1;
      delay(8);
    }
    else if (relStorePlayPause[num][i][5] != 00) {
      digitalWrite(led[i], HIGH);
      relStorePlayPause[num][i][5] = relStorePlayPause[num][i][5] - 1;
      delay(8);
    }
    else if (relStorePlayPause[num][i][6] != 00) {
      digitalWrite(led[i], LOW);
      relStorePlayPause[num][i][6] = relStorePlayPause[num][i][6] - 1;
      delay(8);
    }
    else if (relStorePlayPause[num][i][7] != 00) {
      digitalWrite(led[i], HIGH);
      relStorePlayPause[num][i][7] = relStorePlayPause[num][i][7] - 1;
      delay(8);
    }
    else if (relStorePlayPause[num][i][8] != 00) {
      digitalWrite(led[i], LOW);
      relStorePlayPause[num][i][8] = relStorePlayPause[num][i][8] - 1;
      delay(8);
    }
    else if (relStorePlayPause[num][i][9] != 00) {
      digitalWrite(led[i], HIGH);
      relStorePlayPause[num][i][9] = relStorePlayPause[num][i][9] - 1;
      delay(8);
    }
    else if (relStorePlayPause[num][i][10] != 00) {
      digitalWrite(led[i], LOW);
      relStorePlayPause[num][i][10] = relStorePlayPause[num][i][10] - 1;
      delay(8);
    }
    else if (relStorePlayPause[num][i][11] != 00) {
      digitalWrite(led[i], HIGH);
      relStorePlayPause[num][i][11] = relStorePlayPause[num][i][11] - 1;
      delay(8);
    }
//    else if (relStorePlayPause[num][i][12] != 00) {
//      digitalWrite(led[i], LOW);
//      relStorePlayPause[num][i][12] = relStorePlayPause[num][i][12] - 1;
//      delay(8);
//    }
//    else if (relStorePlayPause[num][i][13] != 00) {
//      digitalWrite(led[i], HIGH);
//      relStorePlayPause[num][i][13] = relStorePlayPause[num][i][13] - 1;
//      delay(8);
//    }
//    else if (relStorePlayPause[num][i][14] != 00) {
//      digitalWrite(led[i], LOW);
//      relStorePlayPause[num][i][14] = relStorePlayPause[num][i][14] - 1;
//      delay(8);
//    }
//    else if (relStorePlayPause[num][i][15] != 00) {
//      digitalWrite(led[i], HIGH);
//      relStorePlayPause[num][i][15] = relStorePlayPause[num][i][15] - 1;
//      delay(8);
//    }
//    else if (relStorePlayPause[num][i][16] != 00) {
//      digitalWrite(led[i], LOW);
//      relStorePlayPause[num][i][16] = relStorePlayPause[num][i][16] - 1;
//      delay(8);
//    }
//    else if (relStorePlayPause[num][i][17] != 00) {
//      digitalWrite(led[i], HIGH);
//      relStorePlayPause[num][i][17] = relStorePlayPause[num][i][17] - 1;
//      delay(8);
//    }
//    else if (relStorePlayPause[num][i][18] != 00) {
//      digitalWrite(led[i], LOW);
//      relStorePlayPause[num][i][18] = relStorePlayPause[num][i][18] - 1;
//      delay(8);
//    }
//    else if (relStorePlayPause[num][i][19] != 00) {
//      digitalWrite(led[i], HIGH);
//      relStorePlayPause[num][i][19] = relStorePlayPause[num][i][19] - 1;
//      delay(8);
//    }
//    else if (relStorePlayPause[num][i][20] != 00) {
//      digitalWrite(led[i], LOW);
//      relStorePlayPause[num][i][20] = relStorePlayPause[num][i][20] - 1;
//      delay(8);
//    }
//    else if (relStorePlayPause[num][i][21] != 00) {
//      digitalWrite(led[i], HIGH);
//      relStorePlayPause[num][i][21] = relStorePlayPause[num][i][21] - 1;
//      delay(8);
//    }
//    else if (relStorePlayPause[num][i][22] != 00) {
//      digitalWrite(led[i], LOW);
//      relStorePlayPause[num][i][22] = relStorePlayPause[num][i][22] - 1;
//      delay(8);
//    }
//    else if (relStorePlayPause[num][i][23] != 00) {
//      digitalWrite(led[i], HIGH);
//      relStorePlayPause[num][i][23] = relStorePlayPause[num][i][23] - 1;
//      delay(8);
//    }
   }

    for(int i = 0; i < 6; i++){
      //When all Relay 1 recording execution variables become 0, reset the recording execution variables
      if ((relStorePlayPause[num][i][0]==0)&&(relStorePlayPause[num][i][0]==relStorePlayPause[num][i][1]) && (relStorePlayPause[num][i][0] == relStorePlayPause[num][i][2]) &&(relStorePlayPause[num][i][0]==relStorePlayPause[num][i][3]) && (relStorePlayPause[num][i][0] == relStorePlayPause[num][i][4]) &&(relStorePlayPause[num][i][0]==relStorePlayPause[num][i][5]) && (relStorePlayPause[num][i][0] == relStorePlayPause[num][i][6]) &&(relStorePlayPause[num][i][0]==relStorePlayPause[num][i][7]) && (relStorePlayPause[num][i][0] == relStorePlayPause[num][i][8]) &&(relStorePlayPause[num][i][0]==relStorePlayPause[num][i][9]) && (relStorePlayPause[num][i][0] == relStorePlayPause[num][i][10]) &&(relStorePlayPause[num][i][0]==relStorePlayPause[num][i][11]))
      {
        for(int j = 0; j <= 11; j++){
          relStorePlayPause[num][j][i] = relRunPlayPause[0][j][i];
        }
      }
    }
  }
