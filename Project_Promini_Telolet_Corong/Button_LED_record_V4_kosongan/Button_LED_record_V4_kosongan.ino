#include "OneButton.h"
OneButton pb(A0, true, true);  //(Pb_Pin;  true = ActiveLow;  true = button PullUp)
//OneButton pb2(A5, true, true);  //(Pb_Pin;  true = ActiveLow;  true = button PullUp)

const int but[] = {2, 3, 4, 5, 6, 7};
const int led[] = {8, 9, 10, 11, 12, 13};

bool buttonState[6] = {LOW};

#define recordPin A0
#define playPin A1

#define recordLED A2
#define playLED A3


//Start variables related to recording and playback mode
int recordPushed = 0;
int playPushed = 0;

int recordButtonLastState  = 0;
int playButtonLastState  = 0;

int recordButtonPressDetected  = 0;
int recordButtonReleaseDetected = 0;

int playButtonPressDetected  = 0;
int playButtonReleaseDetected  = 0;

int recordMod = 0;
int playMod = 0;
int readMod = 0;
//녹음 및 재생 모드 관련 변수 끝

uint8_t num = 0;

//Start relay 1 storage variable
uint16_t relPlayPause[6][24] = {0};// count, 0=play, 1=pause
uint16_t relRepPlayPause[6][24] = {0};// count, 0=play, 1=pause


uint16_t relStorePlayPause[1][6][24] = {0};
const uint16_t relWarePlayPause[2][6][24] = {
  {
    {25, 6, 18, 3, 66, 2, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {62, 7, 44, 2, 45, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {39, 6, 29, 2, 31, 3, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {69, 4, 4, 3, 22, 3, 55, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {33, 6, 14, 10, 22, 3, 8, 2, 62, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {17, 9, 21, 3, 41, 3, 66, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  },
  {
    {55, 8, 24, 8, 146, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {70, 8, 25, 9, 129, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {79, 8, 33, 42, 79, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {63, 8, 40, 51, 79, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {48, 8, 39, 9, 137, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {241, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  }
};// count, 0=play, 1=pause

void setup(void)
{
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

//  pinMode(recordPin, INPUT_PULLUP);
//  pinMode(playPin, INPUT_PULLUP);

//  pinMode(recordLED, OUTPUT);
//  pinMode(playLED, OUTPUT);
//
//  digitalWrite(recordLED, LOW);
//  digitalWrite(playLED, LOW);
  
  Serial.begin(9600);

}

void loop(void)
{

  pb.tick();
bool isRecordButtonPressed = !digitalRead(recordPin);
bool isPlayButtonPressed = !digitalRead(playPin);


  //Operation part when record mode is On
  if ((recordMod == 1) && (playMod == 0 ) && (readMod == 0)) {
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
    else if (relRepPlayPause[i][12] != 00) {
      digitalWrite(led[i], LOW);
      relRepPlayPause[i][12] = relRepPlayPause[i][12] - 1;
      delay(8);
    }
    else if (relRepPlayPause[i][13] != 00) {
      digitalWrite(led[i], HIGH);
      relRepPlayPause[i][13] = relRepPlayPause[i][13] - 1;
      delay(8);
    }
    else if (relRepPlayPause[i][14] != 00) {
      digitalWrite(led[i], LOW);
      relRepPlayPause[i][14] = relRepPlayPause[i][14] - 1;
      delay(8);
    }
    else if (relRepPlayPause[i][15] != 00) {
      digitalWrite(led[i], HIGH);
      relRepPlayPause[i][15] = relRepPlayPause[i][15] - 1;
      delay(8);
    }
    else if (relRepPlayPause[i][16] != 00) {
      digitalWrite(led[i], LOW);
      relRepPlayPause[i][16] = relRepPlayPause[i][16] - 1;
      delay(8);
    }
    else if (relRepPlayPause[i][17] != 00) {
      digitalWrite(led[i], HIGH);
      relRepPlayPause[i][17] = relRepPlayPause[i][17] - 1;
      delay(8);
    }
    else if (relRepPlayPause[i][18] != 00) {
      digitalWrite(led[i], LOW);
      relRepPlayPause[i][18] = relRepPlayPause[i][18] - 1;
      delay(8);
    }
    else if (relRepPlayPause[i][19] != 00) {
      digitalWrite(led[i], HIGH);
      relRepPlayPause[i][19] = relRepPlayPause[i][19] - 1;
      delay(8);
    }
    else if (relRepPlayPause[i][20] != 00) {
      digitalWrite(led[i], LOW);
      relRepPlayPause[i][20] = relRepPlayPause[i][20] - 1;
      delay(8);
    }
    else if (relRepPlayPause[i][21] != 00) {
      digitalWrite(led[i], HIGH);
      relRepPlayPause[i][21] = relRepPlayPause[i][21] - 1;
      delay(8);
    }
    else if (relRepPlayPause[i][22] != 00) {
      digitalWrite(led[i], LOW);
      relRepPlayPause[i][22] = relRepPlayPause[i][22] - 1;
      delay(8);
    }
    else if (relRepPlayPause[i][23] != 00) {
      digitalWrite(led[i], HIGH);
      relRepPlayPause[i][23] = relRepPlayPause[i][23] - 1;
      delay(8);
    }
    //릴레이1 녹화 재생 관련 코드 끝
   }

    for(int i = 0; i < 6; i++){
      //When all Relay 1 recording execution variables become 0, reset the recording execution variables
      if ((relRepPlayPause[i][0]==0)&&(relRepPlayPause[i][0]==relRepPlayPause[i][1]) && (relRepPlayPause[i][0] == relRepPlayPause[i][2]) &&(relRepPlayPause[i][0]==relRepPlayPause[i][3]) && (relRepPlayPause[i][0] == relRepPlayPause[i][4]) &&(relRepPlayPause[i][0]==relRepPlayPause[i][5]) && (relRepPlayPause[i][0] == relRepPlayPause[i][6]) &&(relRepPlayPause[i][0]==relRepPlayPause[i][7]) && (relRepPlayPause[i][0] == relRepPlayPause[i][8]) &&(relRepPlayPause[i][0]==relRepPlayPause[i][9]) && (relRepPlayPause[i][0] == relRepPlayPause[i][10]) &&(relRepPlayPause[i][0]==relRepPlayPause[i][11]) && (relRepPlayPause[i][0] == relRepPlayPause[i][12]) &&(relRepPlayPause[i][0]==relRepPlayPause[i][13]) && (relRepPlayPause[i][0] == relRepPlayPause[i][14]) &&(relRepPlayPause[i][0]==relRepPlayPause[i][15]) && (relRepPlayPause[i][0] == relRepPlayPause[i][16]) &&(relRepPlayPause[i][0]==relRepPlayPause[i][17]) && (relRepPlayPause[i][0] == relRepPlayPause[i][18]) &&(relRepPlayPause[i][0]==relRepPlayPause[i][19]) && (relRepPlayPause[i][0] == relRepPlayPause[i][20]) &&(relRepPlayPause[i][0]==relRepPlayPause[i][21]) && (relRepPlayPause[i][0] == relRepPlayPause[i][22]) &&(relRepPlayPause[i][0]==relRepPlayPause[i][23]))
      {
        for(int j = 0; j <= 23; j++){
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
    else if (relStorePlayPause[0][i][12] != 00) {
      digitalWrite(led[i], LOW);
      relStorePlayPause[0][i][12] = relStorePlayPause[0][i][12] - 1;
      delay(8);
    }
    else if (relStorePlayPause[0][i][13] != 00) {
      digitalWrite(led[i], HIGH);
      relStorePlayPause[0][i][13] = relStorePlayPause[0][i][13] - 1;
      delay(8);
    }
    else if (relStorePlayPause[0][i][14] != 00) {
      digitalWrite(led[i], LOW);
      relStorePlayPause[0][i][14] = relStorePlayPause[0][i][14] - 1;
      delay(8);
    }
    else if (relStorePlayPause[0][i][15] != 00) {
      digitalWrite(led[i], HIGH);
      relStorePlayPause[0][i][15] = relStorePlayPause[0][i][15] - 1;
      delay(8);
    }
    else if (relStorePlayPause[0][i][16] != 00) {
      digitalWrite(led[i], LOW);
      relStorePlayPause[0][i][16] = relStorePlayPause[0][i][16] - 1;
      delay(8);
    }
    else if (relStorePlayPause[0][i][17] != 00) {
      digitalWrite(led[i], HIGH);
      relStorePlayPause[0][i][17] = relStorePlayPause[0][i][17] - 1;
      delay(8);
    }
    else if (relStorePlayPause[0][i][18] != 00) {
      digitalWrite(led[i], LOW);
      relStorePlayPause[0][i][18] = relStorePlayPause[0][i][18] - 1;
      delay(8);
    }
    else if (relStorePlayPause[0][i][19] != 00) {
      digitalWrite(led[i], HIGH);
      relStorePlayPause[0][i][19] = relStorePlayPause[0][i][19] - 1;
      delay(8);
    }
    else if (relStorePlayPause[0][i][20] != 00) {
      digitalWrite(led[i], LOW);
      relStorePlayPause[0][i][20] = relStorePlayPause[0][i][20] - 1;
      delay(8);
    }
    else if (relStorePlayPause[0][i][21] != 00) {
      digitalWrite(led[i], HIGH);
      relStorePlayPause[0][i][21] = relStorePlayPause[0][i][21] - 1;
      delay(8);
    }
    else if (relStorePlayPause[0][i][22] != 00) {
      digitalWrite(led[i], LOW);
      relStorePlayPause[0][i][22] = relStorePlayPause[0][i][22] - 1;
      delay(8);
    }
    else if (relStorePlayPause[0][i][23] != 00) {
      digitalWrite(led[i], HIGH);
      relStorePlayPause[0][i][23] = relStorePlayPause[0][i][23] - 1;
      delay(8);
    }
   }

    for(int i = 0; i < 6; i++){
      //When all Relay 1 recording execution variables become 0, reset the recording execution variables
      if ((relStorePlayPause[0][i][0]==0)&&(relStorePlayPause[0][i][0]==relStorePlayPause[0][i][1]) && (relStorePlayPause[0][i][0] == relStorePlayPause[0][i][2]) &&(relStorePlayPause[0][i][0]==relStorePlayPause[0][i][3]) && (relStorePlayPause[0][i][0] == relStorePlayPause[0][i][4]) &&(relStorePlayPause[0][i][0]==relStorePlayPause[0][i][5]) && (relStorePlayPause[0][i][0] == relStorePlayPause[0][i][6]) &&(relStorePlayPause[0][i][0]==relStorePlayPause[0][i][7]) && (relStorePlayPause[0][i][0] == relStorePlayPause[0][i][8]) &&(relStorePlayPause[0][i][0]==relStorePlayPause[0][i][9]) && (relStorePlayPause[0][i][0] == relStorePlayPause[0][i][10]) &&(relStorePlayPause[0][i][0]==relStorePlayPause[0][i][11]) && (relStorePlayPause[0][i][0] == relStorePlayPause[0][i][12]) &&(relStorePlayPause[0][i][0]==relStorePlayPause[0][i][13]) && (relStorePlayPause[0][i][0] == relStorePlayPause[0][i][14]) &&(relStorePlayPause[0][i][0]==relStorePlayPause[0][i][15]) && (relStorePlayPause[0][i][0] == relStorePlayPause[0][i][16]) &&(relStorePlayPause[0][i][0]==relStorePlayPause[0][i][17]) && (relStorePlayPause[0][i][0] == relStorePlayPause[0][i][18]) &&(relStorePlayPause[0][i][0]==relStorePlayPause[0][i][19]) && (relStorePlayPause[0][i][0] == relStorePlayPause[0][i][20]) &&(relStorePlayPause[0][i][0]==relStorePlayPause[0][i][21]) && (relStorePlayPause[0][i][0] == relStorePlayPause[0][i][22]) &&(relStorePlayPause[0][i][0]==relStorePlayPause[0][i][23]))
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
    digitalWrite(recordLED, HIGH);
    digitalWrite(playLED, LOW);
    
    for(int i = 0; i <= 23; i++){
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
      digitalWrite(playLED, HIGH);
      digitalWrite(recordLED, LOW);
      assignValues();
    
    Serial.println(playMod);
}
void ReadPressed(){
    playMod = 0;
    recordMod = 0;
    readMod = 1;
      Serial.println("read mode On");
      digitalWrite(playLED, HIGH);
      digitalWrite(recordLED, LOW);
      ReadValues();
    
    Serial.println(playMod);
}

void assignValues(){
       for (int j = 0; j < 6; j++) {
        //Initialize by assigning the recording variable to the relay playback variable
        Serial.print("{");
         for(int i = 0; i < 24; i++){
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
void ReadValues(){
       for (int j = 0; j < 6; j++) {
        //Initialize by assigning the recording variable to the relay playback variable
        Serial.print("{");
         for(int i = 0; i < 24; i++){
          relStorePlayPause[0][j][i] = relWarePlayPause[num][j][i];
          Serial.print(relStorePlayPause[0][j][i]);
          if(i < 23){
            Serial.print(", ");
          }
        }
        Serial.print("},");
        Serial.println();
      }

  }
