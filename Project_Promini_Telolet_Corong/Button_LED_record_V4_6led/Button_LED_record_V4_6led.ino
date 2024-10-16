const int but[] = {2, 3, 4, 5, 6, 7};
const int led[] = {8, 9, 10, 11, 12, 13};

bool buttonState[6] = {LOW};

#define rEcord A0
#define pLay A1

#define rEcordLED A2
#define pLayLED A3


//Start variables related to recording and playback mode
int recordPushed = 0;
int playPushed = 0;

int recordLast = 0;
int playLast = 0;

int recordPushToNot = 0;
int recordNotToPush = 0;

int playPushToNot = 0;
int playNotToPush = 0;

int recordMod = 0;
int playMod = 0;
//녹음 및 재생 모드 관련 변수 끝


//Start relay 1 storage variable
unsigned int relPlayPause[6][24] = {0};// count, 0=play, 1=pause
unsigned int relRepPlayPause[6][24] = {0};// count, 0=play, 1=pause


//unsigned int relPlayPause[0][24] = {0};// count, 0=play, 1=pause
//unsigned int rel1RepPlayPause[24] = {0};// count, 0=play, 1=pause

//unsigned int relPlayPause[1][24] = {0};// count, 0=play, 1=pause
//unsigned int relRepPlayPause[1][24] = {0};// count, 0=play, 1=pause

//unsigned int relPlayPause[2][24] = {0};// count, 0=play, 1=pause
//unsigned int relRepPlayPause[2][24] = {0};// count, 0=play, 1=pause

//unsigned int relPlayPause[3][24] = {0};// count, 0=play, 1=pause
//unsigned int relRepPlayPause[3][24] = {0};// count, 0=play, 1=pause

unsigned int relPlayPause[4][24] = {0};// count, 0=play, 1=pause
unsigned int rel5RepPlayPause[24] = {0};// count, 0=play, 1=pause

unsigned int rel6PlayPause[24] = {0};// count, 0=play, 1=pause
unsigned int rel6RepPlayPause[24] = {0};// count, 0=play, 1=pause

void setup(void)
{
  for ( int i = 2 ; i <= 7 ; i++) {
    pinMode(i, INPUT_PULLUP);
  }

  for ( int i = 8 ; i <= 13 ; i++ ) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);

  }

  pinMode(rEcord, INPUT_PULLUP);
  pinMode(pLay, INPUT_PULLUP);

  pinMode(rEcordLED, OUTPUT);
  pinMode(pLayLED, OUTPUT);

  digitalWrite(rEcordLED, LOW);
  digitalWrite(pLayLED, LOW);
  
  Serial.begin(9600);

}

void loop(void)
{

  recordPushed = !digitalRead(rEcord);
  playPushed = !digitalRead(pLay);

  if (recordLast != recordPushed) {
    if (recordPushed == 1) {
      recordNotToPush = 1;
    }
    else {
      recordPushToNot = 1;
    }
  }

  if (playLast != playPushed) {
    if (playPushed == 1) {
      playNotToPush = 1;
    }
    else {
      playPushToNot = 1;
    }
  }

  recordLast = recordPushed;
  playLast = playPushed;

if ((recordPushToNot == 1) && (recordNotToPush == 1)) {
    recordMod = 1;
    playMod = 0;
    Serial.println("Record Mode On");
    digitalWrite(rEcordLED, HIGH);
    digitalWrite(pLayLED, LOW);
    
    for(int i = 0; i <= 23; i++){
      //Initialize relay recording variables
      for (int j = 0; j < 6; j++) {
        relPlayPause[j][i] = 0;
      }
    }

    Serial.println(recordMod);
    recordPushToNot = 0;
    recordNotToPush = 0;
  }


//
//  if ((recordPushToNot == 1) && (recordNotToPush == 1)) {
//    recordMod = 1;
//    playMod = 0;
//    Serial.println("Record Mode On");
//    digitalWrite(rEcordLED, HIGH);
//    digitalWrite(pLayLED, LOW);
//    
//    for(int i = 0; i <= 23; i++){
//      //Initialize relay 1 recording variables
//      rel1PlayPause[i] = 0;
//      rel2PlayPause[i] = 0;
//      rel3PlayPause[i] = 0;
//      rel4PlayPause[i] = 0;
//      rel5PlayPause[i] = 0;
//      rel6PlayPause[i] = 0;
//    }
//
//    Serial.println(recordMod);
//    recordPushToNot = 0;
//    recordNotToPush = 0;
//  }

if ((playPushToNot == 1) && (playNotToPush == 1)) {
    if (playMod == 0) {
      playMod = 1;
      recordMod = 0;
      Serial.println("play mode On");
      digitalWrite(pLayLED, HIGH);
      digitalWrite(rEcordLED, LOW);

      for(int i = 0; i <= 23; i++){
        //Initialize by assigning the recording variable to the relay playback variable
        for (int j = 0; j < 6; j++) {
          relRepPlayPause[j][i] = relPlayPause[j][i];
          Serial.print(relRepPlayPause[j][i]);
          Serial.print(", ");
        }
        Serial.println();
      }
    }
    Serial.println(playMod);
    playPushToNot = 0;
    playNotToPush = 0;
  }

//
//  if ((playPushToNot == 1) && (playNotToPush == 1)) {
//    if (playMod == 0) {
//      playMod = 1;
//      recordMod = 0;
//      Serial.println("play mode On");
//      digitalWrite(pLayLED, HIGH);
//      digitalWrite(rEcordLED, LOW);
//
//      for(int i = 0; i <= 23; i++){
//        //Initialize by assigning the recording variable to the relay playback variable
//        rel1RepPlayPause[i] = rel1PlayPause[i];
//        Serial.print(rel1RepPlayPause[i]);
//        Serial.print(", ");
//        rel2RepPlayPause[i] = rel2PlayPause[i];
//        Serial.print(rel2RepPlayPause[i]);
//        Serial.print(", ");
//        rel3RepPlayPause[i] = rel3PlayPause[i];
//        Serial.print(rel3RepPlayPause[i]);
//        Serial.print(", ");
//        rel4RepPlayPause[i] = rel4PlayPause[i];
//        Serial.print(rel4RepPlayPause[i]);
//        Serial.print(", ");
//        rel5RepPlayPause[i] = rel5PlayPause[i];
//        Serial.print(rel5RepPlayPause[i]);
//        Serial.print(", ");
//        rel6RepPlayPause[i] = rel6PlayPause[i];
//        Serial.println(rel6RepPlayPause[i]);
//      }
//    }
//    Serial.println(playMod);
//    playPushToNot = 0;
//    playNotToPush = 0;
//  }


  //Operation part when record mode is On
  if ((recordMod == 1) && (playMod == 0)) {
      for(int i = 0; i <= 6; i++){
        buttonState[i] = !digitalRead(but[i]);
    }

    //버튼1이 눌려있을 때
    if (buttonState[0] == HIGH) {
      digitalWrite(led[0], HIGH);
      delay(10);

      //버튼1 눌려있는 것 녹화 시작
      if ((relPlayPause[0][0] != 0) && (relPlayPause[0][2] == 0)) {
        relPlayPause[0][1] = relPlayPause[0][1] + 1;
      }
      else if (relPlayPause[0][4] == 0) {
        relPlayPause[0][3] = relPlayPause[0][3] + 1;
      }
      else if (relPlayPause[0][6] == 0) {
        relPlayPause[0][5] = relPlayPause[0][5] + 1;
      }
      else if (relPlayPause[0][8] == 0) {
        relPlayPause[0][7] = relPlayPause[0][7] + 1;
      }
      else if (relPlayPause[0][10] == 0) {
        relPlayPause[0][9] = relPlayPause[0][9] + 1;
      }
      else if (relPlayPause[0][12] == 0) {
        relPlayPause[0][11] = relPlayPause[0][11] + 1;
      }
      else if (relPlayPause[0][14] == 0) {
        relPlayPause[0][13] = relPlayPause[0][13] + 1;
      }
      else if (relPlayPause[0][16] == 0) {
        relPlayPause[0][15] = relPlayPause[0][15] + 1;
      }
      else if (relPlayPause[0][18] == 0) {
        relPlayPause[0][17] = relPlayPause[0][17] + 1;
      }
      else if (relPlayPause[0][20] == 0) {
        relPlayPause[0][19] = relPlayPause[0][19] + 1;
      }
      else if (relPlayPause[0][22] == 0) {
        relPlayPause[0][21] = relPlayPause[0][21] + 1;
      }
      else {
        relPlayPause[0][23] = relPlayPause[0][23] + 1;
      }
      //버튼1 눌려있는 것 녹화 끝
    }
    //버튼1이 띄워져 있을 때
    else {
      digitalWrite(led[0], LOW);
      delay(10);

      //버튼 1 띄워져 있는 것 녹화 시작
      if (relPlayPause[0][1] == 0) {
        relPlayPause[0][0] = relPlayPause[0][0] + 1;
      }
      else if (relPlayPause[0][3] == 0) {
        relPlayPause[0][2] = relPlayPause[0][2] + 1;
      }
      else if (relPlayPause[0][5] == 0) {
        relPlayPause[0][4] = relPlayPause[0][4] + 1;
      }
      else if (relPlayPause[0][7] == 0) {
        relPlayPause[0][6] = relPlayPause[0][6] + 1;
      }
      else if (relPlayPause[0][9] == 0) {
        relPlayPause[0][8] = relPlayPause[0][8] + 1;
      }
      else if (relPlayPause[0][11] == 0) {
        relPlayPause[0][10] = relPlayPause[0][10] + 1;
      }
      else if (relPlayPause[0][13] == 0) {
        relPlayPause[0][12] = relPlayPause[0][12] + 1;
      }
      else if (relPlayPause[0][15] == 0) {
        relPlayPause[0][14] = relPlayPause[0][14] + 1;
      }
      else if (relPlayPause[0][17] == 0) {
        relPlayPause[0][16] = relPlayPause[0][16] + 1;
      }
      else if (relPlayPause[0][19] == 0) {
        relPlayPause[0][18] = relPlayPause[0][18] + 1;
      }
      else if (relPlayPause[0][21] == 0) {
        relPlayPause[0][20] = relPlayPause[0][20] + 1;
      }
      else if (relPlayPause[0][23] == 0) {
        relPlayPause[0][22] = relPlayPause[0][22] + 1;
      }
      //버튼 1 띄워져 있는 것 녹화 끝
    }

    //버튼2가 눌려있을 때
    if (buttonState[1] == HIGH) {
      digitalWrite(led[1], HIGH);

      //버튼2 눌려있는 것 녹화 시작
      if ((relPlayPause[1][0] != 0) && (relPlayPause[1][2] == 0)) {
        relPlayPause[1][1] = relPlayPause[1][1] + 1;
      }
      else if (relPlayPause[1][4] == 0) {
        relPlayPause[1][2] = relPlayPause[1][2] + 1;
      }
      else if (relPlayPause[1][6] == 0) {
        relPlayPause[1][5] = relPlayPause[1][5] + 1;
      }
      else if (relPlayPause[1][8] == 0) {
        relPlayPause[1][7] = relPlayPause[1][7] + 1;
      }
      else if (relPlayPause[1][10] == 0) {
        relPlayPause[1][9] = relPlayPause[1][9] + 1;
      }
      else if (relPlayPause[1][12] == 0) {
        relPlayPause[1][11] = relPlayPause[1][11] + 1;
      }
      else if (relPlayPause[1][14] == 0) {
        relPlayPause[1][13] = relPlayPause[1][13] + 1;
      }
      else if (relPlayPause[1][16] == 0) {
        relPlayPause[1][15] = relPlayPause[1][15] + 1;
      }
      else if (relPlayPause[1][18] == 0) {
        relPlayPause[1][17] = relPlayPause[1][17] + 1;
      }
      else if (relPlayPause[1][20] == 0) {
        relPlayPause[1][19] = relPlayPause[1][19] + 1;
      }
      else if (relPlayPause[1][22] == 0) {
        relPlayPause[1][21] = relPlayPause[1][21] + 1;
      }
      else {
        relPlayPause[1][23] = relPlayPause[1][23] + 1;
      }
      //버튼2 눌려있는 것 녹화 끝
    }
    //버튼2가 띄워져 있을 때
    else {
      digitalWrite(led[1], LOW);
      delay(10);

      //버튼2 띄워져 있는 것 녹화 시작
      if (relPlayPause[1][1] == 0) {
        relPlayPause[1][0] = relPlayPause[1][0] + 1;
      }
      else if (relPlayPause[1][2] == 0) {
        relPlayPause[1][2] = relPlayPause[1][2] + 1;
      }
      else if (relPlayPause[1][5] == 0) {
        relPlayPause[1][4] = relPlayPause[1][4] + 1;
      }
      else if (relPlayPause[1][7] == 0) {
        relPlayPause[1][6] = relPlayPause[1][6] + 1;
      }
      else if (relPlayPause[1][9] == 0) {
        relPlayPause[1][8] = relPlayPause[1][8] + 1;
      }
      else if (relPlayPause[1][11] == 0) {
        relPlayPause[1][10] = relPlayPause[1][10] + 1;
      }
      else if (relPlayPause[1][13] == 0) {
        relPlayPause[1][12] = relPlayPause[1][12] + 1;
      }
      else if (relPlayPause[1][15] == 0) {
        relPlayPause[1][14] = relPlayPause[1][14] + 1;
      }
      else if (relPlayPause[1][17] == 0) {
        relPlayPause[1][16] = relPlayPause[1][16] + 1;
      }
      else if (relPlayPause[1][19] == 0) {
        relPlayPause[1][18] = relPlayPause[1][18] + 1;
      }
      else if (relPlayPause[1][21] == 0) {
        relPlayPause[1][20] = relPlayPause[1][20] + 1;
      }
      else if (relPlayPause[1][23] == 0) {
        relPlayPause[1][22] = relPlayPause[1][22] + 1;
      }
      //버튼2 띄워져 있는 것 녹화 끝
    }

    //버튼3가 눌러져 있을 때
    if (buttonState[2] == HIGH) {
      digitalWrite(led[2], HIGH);
      delay(10);

      //버튼3 눌려있는 것 녹화 시작
      if ((relPlayPause[2][0] != 0) && (relPlayPause[2][2] == 0)) {
        relPlayPause[2][1] = relPlayPause[2][1] + 1;
      }
      else if (relPlayPause[2][4] == 0) {
        relPlayPause[2][3] = relPlayPause[2][3] + 1;
      }
      else if (relPlayPause[2][6] == 0) {
        relPlayPause[2][5] = relPlayPause[2][5] + 1;
      }
      else if (relPlayPause[2][8] == 0) {
        relPlayPause[2][7] = relPlayPause[2][7] + 1;
      }
      else if (relPlayPause[2][10] == 0) {
        relPlayPause[2][9] = relPlayPause[2][9] + 1;
      }
      else if (relPlayPause[2][12] == 0) {
        relPlayPause[2][11] = relPlayPause[2][11] + 1;
      }
      else if (relPlayPause[2][14] == 0) {
        relPlayPause[2][13] = relPlayPause[2][13] + 1;
      }
      else if (relPlayPause[2][16] == 0) {
        relPlayPause[2][15] = relPlayPause[2][15] + 1;
      }
      else if (relPlayPause[2][18] == 0) {
        relPlayPause[2][17] = relPlayPause[2][17] + 1;
      }
      else if (relPlayPause[2][20] == 0) {
        relPlayPause[2][19] = relPlayPause[2][19] + 1;
      }
      else if (relPlayPause[2][22] == 0) {
        relPlayPause[2][21] = relPlayPause[2][21] + 1;
      }
      else {
        relPlayPause[2][23] = relPlayPause[2][23] + 1;
      }
      //버튼3 눌려있는 것 녹화 끝
    }
    //버튼3가 띄워져 있을 때
    else {
      digitalWrite(led[2], LOW);
      delay(10);

      //버튼3 띄워져 있는 것 녹화 시작
      if (relPlayPause[2][1] == 0) {
        relPlayPause[2][0] = relPlayPause[2][0] + 1;
      }
      else if (relPlayPause[2][3] == 0) {
        relPlayPause[2][2] = relPlayPause[2][2] + 1;
      }
      else if (relPlayPause[2][5] == 0) {
        relPlayPause[2][4] = relPlayPause[2][4] + 1;
      }
      else if (relPlayPause[2][7] == 0) {
        relPlayPause[2][6] = relPlayPause[2][6] + 1;
      }
      else if (relPlayPause[2][9] == 0) {
        relPlayPause[2][8] = relPlayPause[2][8] + 1;
      }
      else if (relPlayPause[2][11] == 0) {
        relPlayPause[2][10] = relPlayPause[2][10] + 1;
      }
      else if (relPlayPause[2][13] == 0) {
        relPlayPause[2][12] = relPlayPause[2][12] + 1;
      }
      else if (relPlayPause[2][15] == 0) {
        relPlayPause[2][14] = relPlayPause[2][14] + 1;
      }
      else if (relPlayPause[2][17] == 0) {
        relPlayPause[2][16] = relPlayPause[2][16] + 1;
      }
      else if (relPlayPause[2][19] == 0) {
        relPlayPause[2][18] = relPlayPause[2][18] + 1;
      }
      else if (relPlayPause[2][21] == 0) {
        relPlayPause[2][20] = relPlayPause[2][20] + 1;
      }
      else if (relPlayPause[2][23] == 0) {
        relPlayPause[2][22] = relPlayPause[2][22] + 1;
      }
      //버튼3 띄워져 있는 것 녹화 끝
    }

    //버튼4가 눌러져 있을 때
    if (buttonState[3] == HIGH) {
      digitalWrite(led[3], HIGH);
      delay(10);

      //버튼4 눌려있는 것 녹화 시작
      if ((relPlayPause[3][0] != 0) && (relPlayPause[3][2] == 0)) {
        relPlayPause[3][1] = relPlayPause[3][1] + 1;
      }
      else if (rel4PlayPause[4] == 0) {
        relPlayPause[3][3] = relPlayPause[3][3] + 1;
      }
      else if (relPlayPause[3][6] == 0) {
        relPlayPause[3][5] = relPlayPause[3][5] + 1;
      }
      else if (relPlayPause[3][8] == 0) {
        relPlayPause[3][7] = relPlayPause[3][7] + 1;
      }
      else if (relPlayPause[3][10] == 0) {
        relPlayPause[3][9] = relPlayPause[3][9] + 1;
      }
      else if (relPlayPause[3][12] == 0) {
        relPlayPause[3][11] = relPlayPause[3][11] + 1;
      }
      else if (relPlayPause[3][14] == 0) {
        relPlayPause[3][13] = relPlayPause[3][13] + 1;
      }
      else if (relPlayPause[3][16] == 0) {
        relPlayPause[3][15] = relPlayPause[3][15] + 1;
      }
      else if (relPlayPause[3][18] == 0) {
        relPlayPause[3][17] = relPlayPause[3][17] + 1;
      }
      else if (relPlayPause[3][20] == 0) {
        relPlayPause[3][19] = relPlayPause[3][19] + 1;
      }
      else if (relPlayPause[3][22] == 0) {
        relPlayPause[3][21] = relPlayPause[3][21] + 1;
      }
      else {
        relPlayPause[3][23] = relPlayPause[3][23] + 1;
      }
      //버튼4 눌려있는 것 녹화 끝
    }
    //버튼4가 띄워져 있을 때
    else {
      digitalWrite(led[3], LOW);
      delay(10);
      
      //버튼4 띄워져 있는 것 녹화 시작
      if (relPlayPause[3][1] == 0) {
        relPlayPause[3][0] = relPlayPause[3][0] + 1;
      }
      else if (relPlayPause[3][3] == 0) {
        relPlayPause[3][2] = relPlayPause[3][2] + 1;
      }
      else if (relPlayPause[3][5] == 0) {
        rel4PlayPause[4] = rel4PlayPause[4] + 1;
      }
      else if (relPlayPause[3][7] == 0) {
        relPlayPause[3][6] = relPlayPause[3][6] + 1;
      }
      else if (relPlayPause[3][9] == 0) {
        relPlayPause[3][8] = relPlayPause[3][8] + 1;
      }
      else if (relPlayPause[3][11] == 0) {
        relPlayPause[3][10] = relPlayPause[3][10] + 1;
      }
      else if (relPlayPause[3][13] == 0) {
        relPlayPause[3][12] = relPlayPause[3][12] + 1;
      }
      else if (relPlayPause[3][15] == 0) {
        relPlayPause[3][14] = relPlayPause[3][14] + 1;
      }
      else if (relPlayPause[3][17] == 0) {
        relPlayPause[3][16] = relPlayPause[3][16] + 1;
      }
      else if (relPlayPause[3][19] == 0) {
        relPlayPause[3][18] = relPlayPause[3][18] + 1;
      }
      else if (relPlayPause[3][21] == 0) {
        relPlayPause[3][20] = relPlayPause[3][20] + 1;
      }
      else if (relPlayPause[3][23] == 0) {
        relPlayPause[3][22] = relPlayPause[3][22] + 1;
      }
      //버튼4 띄워져 있는 것 녹화 끝
    }    
    
    //버튼4가 눌러져 있을 때
    if (buttonState[4] == HIGH) {
      digitalWrite(led[4], HIGH);
      delay(10);

      //버튼4 눌려있는 것 녹화 시작
      if ((relPlayPause[4][0] != 0) && (relPlayPause[4][2] == 0)) {
        relPlayPause[4][1] = relPlayPause[4][1] + 1;
      }
      else if (relPlayPause[4][4] == 0) {
        relPlayPause[4][3] = relPlayPause[4][3] + 1;
      }
      else if (relPlayPause[4][6] == 0) {
        relPlayPause[4][5] = relPlayPause[4][5] + 1;
      }
      else if (relPlayPause[4]8] == 0) {
        relPlayPause[4][7] = relPlayPause[4][7] + 1;
      }
      else if (relPlayPause[4][10] == 0) {
        relPlayPause[4][9] = relPlayPause[4][9] + 1;
      }
      else if (relPlayPause[4][12] == 0) {
        relPlayPause[4][11] = relPlayPause[4][11] + 1;
      }
      else if (relPlayPause[4][14] == 0) {
        relPlayPause[4][13] = relPlayPause[4][13] + 1;
      }
      else if (relPlayPause[4][16] == 0) {
        relPlayPause[4][15] = relPlayPause[4][15] + 1;
      }
      else if (relPlayPause[4][18] == 0) {
        relPlayPause[4][17] = relPlayPause[4][17] + 1;
      }
      else if (relPlayPause[4][20] == 0) {
        relPlayPause[4][19] = relPlayPause[4][19] + 1;
      }
      else if (relPlayPause[4][22] == 0) {
        relPlayPause[4][21] = relPlayPause[4][21] + 1;
      }
      else {
        relPlayPause[4][23] = relPlayPause[4][23] + 1;
      }
      //버튼4 눌려있는 것 녹화 끝
    }
    //버튼4가 띄워져 있을 때
    else {
      digitalWrite(led[4], LOW);
      delay(10);
      
      //버튼4 띄워져 있는 것 녹화 시작
      if (relPlayPause[4][1] == 0) {
        relPlayPause[4][0] = relPlayPause[4][0] + 1;
      }
      else if (relPlayPause[4][3] == 0) {
        relPlayPause[4][2] = relPlayPause[4][2] + 1;
      }
      else if (relPlayPause[4][5] == 0) {
        relPlayPause[4][4] = relPlayPause[4][4] + 1;
      }
      else if (relPlayPause[4][7] == 0) {
        relPlayPause[4][6] = relPlayPause[4][6] + 1;
      }
      else if (relPlayPause[4][9] == 0) {
        relPlayPause[4]8] = relPlayPause[4]8] + 1;
      }
      else if (relPlayPause[4][11] == 0) {
        relPlayPause[4][10] = relPlayPause[4][10] + 1;
      }
      else if (relPlayPause[4][13] == 0) {
        relPlayPause[4][12] = relPlayPause[4][12] + 1;
      }
      else if (relPlayPause[4][15] == 0) {
        relPlayPause[4][14] = relPlayPause[4][14] + 1;
      }
      else if (relPlayPause[4][17] == 0) {
        relPlayPause[4][16] = relPlayPause[4][16] + 1;
      }
      else if (relPlayPause[4][19] == 0) {
        relPlayPause[4][18] = relPlayPause[4][18] + 1;
      }
      else if (relPlayPause[4][21] == 0) {
        relPlayPause[4][20] = relPlayPause[4][20] + 1;
      }
      else if (relPlayPause[4][23] == 0) {
        relPlayPause[4][22] = relPlayPause[4][22] + 1;
      }
      //버튼4 띄워져 있는 것 녹화 끝
    }
    
    //버튼4가 눌러져 있을 때
    if (buttonState[5] == HIGH) {
      digitalWrite(led[5], HIGH);
      delay(10);

      //버튼4 눌려있는 것 녹화 시작
      if ((rel6PlayPause[0] != 0) && (rel6PlayPause[2] == 0)) {
        rel6PlayPause[1] = rel6PlayPause[1] + 1;
      }
      else if (rel6PlayPause[4] == 0) {
        rel6PlayPause[3] = rel6PlayPause[3] + 1;
      }
      else if (rel6PlayPause[6] == 0) {
        rel6PlayPause[5] = rel6PlayPause[5] + 1;
      }
      else if (rel6PlayPause[8] == 0) {
        rel6PlayPause[7] = rel6PlayPause[7] + 1;
      }
      else if (rel6PlayPause[10] == 0) {
        rel6PlayPause[9] = rel6PlayPause[9] + 1;
      }
      else if (rel6PlayPause[12] == 0) {
        rel6PlayPause[11] = rel6PlayPause[11] + 1;
      }
      else if (rel6PlayPause[14] == 0) {
        rel6PlayPause[13] = rel6PlayPause[13] + 1;
      }
      else if (rel6PlayPause[16] == 0) {
        rel6PlayPause[15] = rel6PlayPause[15] + 1;
      }
      else if (rel6PlayPause[18] == 0) {
        rel6PlayPause[17] = rel6PlayPause[17] + 1;
      }
      else if (rel6PlayPause[20] == 0) {
        rel6PlayPause[19] = rel6PlayPause[19] + 1;
      }
      else if (rel6PlayPause[22] == 0) {
        rel6PlayPause[21] = rel6PlayPause[21] + 1;
      }
      else {
        rel6PlayPause[23] = rel6PlayPause[23] + 1;
      }
      //버튼4 눌려있는 것 녹화 끝
    }
    //버튼4가 띄워져 있을 때
    else {
      digitalWrite(led[5], LOW);
      delay(10);
      
      //버튼4 띄워져 있는 것 녹화 시작
      if (rel6PlayPause[1] == 0) {
        rel6PlayPause[0] = rel6PlayPause[0] + 1;
      }
      else if (rel6PlayPause[3] == 0) {
        rel6PlayPause[2] = rel6PlayPause[2] + 1;
      }
      else if (rel6PlayPause[5] == 0) {
        rel6PlayPause[4] = rel6PlayPause[4] + 1;
      }
      else if (rel6PlayPause[7] == 0) {
        rel6PlayPause[6] = rel6PlayPause[6] + 1;
      }
      else if (rel6PlayPause[9] == 0) {
        rel6PlayPause[8] = rel6PlayPause[8] + 1;
      }
      else if (rel6PlayPause[11] == 0) {
        rel6PlayPause[10] = rel6PlayPause[10] + 1;
      }
      else if (rel6PlayPause[13] == 0) {
        rel6PlayPause[12] = rel6PlayPause[12] + 1;
      }
      else if (rel6PlayPause[15] == 0) {
        rel6PlayPause[14] = rel6PlayPause[14] + 1;
      }
      else if (rel6PlayPause[17] == 0) {
        rel6PlayPause[16] = rel6PlayPause[16] + 1;
      }
      else if (rel6PlayPause[19] == 0) {
        rel6PlayPause[18] = rel6PlayPause[18] + 1;
      }
      else if (rel6PlayPause[21] == 0) {
        rel6PlayPause[20] = rel6PlayPause[20] + 1;
      }
      else if (rel6PlayPause[23] == 0) {
        rel6PlayPause[22] = rel6PlayPause[22] + 1;
      }
      //버튼4 띄워져 있는 것 녹화 끝
    }

    /*
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
    */
  }

  
  //Saat memasuki mode putar
  if ((playMod == 1) && (recordMod == 0)) {
    //릴레이1 녹화 재생 관련 코드 시작
    if (relRepPlayPause[0][0] != 00) {
      digitalWrite(led[0], LOW);
      relRepPlayPause[0][0] = relRepPlayPause[0][0] - 1;
      delay(8);
    }
    else if (relRepPlayPause[0][1] != 00) {
      digitalWrite(led[0], HIGH);
      relRepPlayPause[0][1] = relRepPlayPause[0][1] - 1;
      delay(8);
    }
    else if (relRepPlayPause[0][2] != 00) {
      digitalWrite(led[0], LOW);
      relRepPlayPause[0][2] = relRepPlayPause[0][2] - 1;
      delay(8);
    }
    else if (relRepPlayPause[0][3] != 00) {
      digitalWrite(led[0], HIGH);
      relRepPlayPause[0][3] = relRepPlayPause[0][3] - 1;
      delay(8);
    }
    else if (relRepPlayPause[0][4] != 00) {
      digitalWrite(led[0], LOW);
      relRepPlayPause[0][4] = relRepPlayPause[0][4] - 1;
      delay(8);
    }
    else if (relRepPlayPause[0][5] != 00) {
      digitalWrite(led[0], HIGH);
      relRepPlayPause[0][5] = relRepPlayPause[0][5] - 1;
      delay(8);
    }
    else if (relRepPlayPause[0][6] != 00) {
      digitalWrite(led[0], LOW);
      relRepPlayPause[0][6] = relRepPlayPause[0][6] - 1;
      delay(8);
    }
    else if (relRepPlayPause[0][7] != 00) {
      digitalWrite(led[0], HIGH);
      relRepPlayPause[0][7] = relRepPlayPause[0][7] - 1;
      delay(8);
    }
    else if (relRepPlayPause[0][8] != 00) {
      digitalWrite(led[0], LOW);
      relRepPlayPause[0][8] = relRepPlayPause[0][8] - 1;
      delay(8);
    }
    else if (relRepPlayPause[0][9] != 00) {
      digitalWrite(led[0], HIGH);
      relRepPlayPause[0][9] = relRepPlayPause[0][9] - 1;
      delay(8);
    }
    else if (relRepPlayPause[0][10] != 00) {
      digitalWrite(led[0], LOW);
      relRepPlayPause[0][10] = relRepPlayPause[0][10] - 1;
      delay(8);
    }
    else if (relRepPlayPause[0][11] != 00) {
      digitalWrite(led[0], HIGH);
      relRepPlayPause[0][11] = relRepPlayPause[0][11] - 1;
      delay(8);
    }
    else if (relRepPlayPause[0][12] != 00) {
      digitalWrite(led[0], LOW);
      relRepPlayPause[0][12] = relRepPlayPause[0][12] - 1;
      delay(8);
    }
    else if (relRepPlayPause[0][13] != 00) {
      digitalWrite(led[0], HIGH);
      relRepPlayPause[0][13] = relRepPlayPause[0][13] - 1;
      delay(8);
    }
    else if (relRepPlayPause[0][14] != 00) {
      digitalWrite(led[0], LOW);
      relRepPlayPause[0][14] = relRepPlayPause[0][14] - 1;
      delay(8);
    }
    else if (relRepPlayPause[0][15] != 00) {
      digitalWrite(led[0], HIGH);
      relRepPlayPause[0][15] = relRepPlayPause[0][15] - 1;
      delay(8);
    }
    else if (relRepPlayPause[0][16] != 00) {
      digitalWrite(led[0], LOW);
      relRepPlayPause[0][16] = relRepPlayPause[0][16] - 1;
      delay(8);
    }
    else if (relRepPlayPause[0][17] != 00) {
      digitalWrite(led[0], HIGH);
      relRepPlayPause[0][17] = relRepPlayPause[0][17] - 1;
      delay(8);
    }
    else if (relRepPlayPause[0][18] != 00) {
      digitalWrite(led[0], LOW);
      relRepPlayPause[0][18] = relRepPlayPause[0][18] - 1;
      delay(8);
    }
    else if (relRepPlayPause[0][19] != 00) {
      digitalWrite(led[0], HIGH);
      relRepPlayPause[0][19] = relRepPlayPause[0][19] - 1;
      delay(8);
    }
    else if (relRepPlayPause[0][20] != 00) {
      digitalWrite(led[0], LOW);
      relRepPlayPause[0][20] = relRepPlayPause[0][20] - 1;
      delay(8);
    }
    else if (relRepPlayPause[0][21] != 00) {
      digitalWrite(led[0], HIGH);
      relRepPlayPause[0][21] = relRepPlayPause[0][21] - 1;
      delay(8);
    }
    else if (relRepPlayPause[0][22] != 00) {
      digitalWrite(led[0], LOW);
      relRepPlayPause[0][22] = relRepPlayPause[0][22] - 1;
      delay(8);
    }
    else if (relRepPlayPause[0][23] != 00) {
      digitalWrite(led[0], HIGH);
      relRepPlayPause[0][23] = relRepPlayPause[0][23] - 1;
      delay(8);
    }
    //릴레이1 녹화 재생 관련 코드 끝

    //릴레이2 녹화 재생 관련 코드 시작
    if (relRepPlayPause[1][0] != 00) {
      digitalWrite(led[1], LOW);
      relRepPlayPause[1][0] = relRepPlayPause[1][0] - 1;
      delay(8);
    }
    else if (relRepPlayPause[1][1] != 00) {
      digitalWrite(led[1], HIGH);
      relRepPlayPause[1][1] = relRepPlayPause[1][1] - 1;
      delay(8);
    }
    else if (relRepPlayPause[1][2] != 00) {
      digitalWrite(led[1], LOW);
      relRepPlayPause[1][2] = relRepPlayPause[1][2] - 1;
      delay(8);
    }
    else if (relRepPlayPause[1][3] != 00) {
      digitalWrite(led[1], HIGH);
      relRepPlayPause[1][3] = relRepPlayPause[1][3] - 1;
      delay(8);
    }
    else if (relRepPlayPause[1][4] != 00) {
      digitalWrite(led[1], LOW);
      relRepPlayPause[1][4] = relRepPlayPause[1][4] - 1;
      delay(8);
    }
    else if (relRepPlayPause[1][5] != 00) {
      digitalWrite(led[1], HIGH);
      relRepPlayPause[1][5] = relRepPlayPause[1][5] - 1;
      delay(8);
    }
    else if (relRepPlayPause[1][6] != 00) {
      digitalWrite(led[1], LOW);
      relRepPlayPause[1][6] = relRepPlayPause[1][6] - 1;
      delay(8);
    }
    else if (relRepPlayPause[1][7] != 00) {
      digitalWrite(led[1], HIGH);
      relRepPlayPause[1][7] = relRepPlayPause[1][7] - 1;
      delay(8);
    }
    else if (relRepPlayPause[1][8] != 00) {
      digitalWrite(led[1], LOW);
      relRepPlayPause[1][8] = relRepPlayPause[1][8] - 1;
      delay(8);
    }
    else if (relRepPlayPause[1][9] != 00) {
      digitalWrite(led[1], HIGH);
      relRepPlayPause[1][9] = relRepPlayPause[1][9] - 1;
      delay(8);
    }
    else if (relRepPlayPause[1][10] != 00) {
      digitalWrite(led[1], LOW);
      relRepPlayPause[1][10] = relRepPlayPause[1][10] - 1;
      delay(8);
    }
    else if (relRepPlayPause[1][11] != 00) {
      digitalWrite(led[1], HIGH);
      relRepPlayPause[1][11] = relRepPlayPause[1][11] - 1;
      delay(8);
    }
    else if (relRepPlayPause[1][12] != 00) {
      digitalWrite(led[1], LOW);
      relRepPlayPause[1][12] = relRepPlayPause[1][12] - 1;
      delay(8);
    }
    else if (relRepPlayPause[1][13] != 00) {
      digitalWrite(led[1], HIGH);
      relRepPlayPause[1][13] = relRepPlayPause[1][13] - 1;
      delay(8);
    }
    else if (relRepPlayPause[1][14] != 00) {
      digitalWrite(led[1], LOW);
      relRepPlayPause[1][14] = relRepPlayPause[1][14] - 1;
      delay(8);
    }
    else if (relRepPlayPause[1][15] != 00) {
      digitalWrite(led[1], HIGH);
      relRepPlayPause[1][15] = relRepPlayPause[1][15] - 1;
      delay(8);
    }
    else if (relRepPlayPause[1][6] != 00) {
      digitalWrite(led[1], LOW);
      relRepPlayPause[1][6] = relRepPlayPause[1][6] - 1;
      delay(8);
    }
    else if (relRepPlayPause[1][17] != 00) {
      digitalWrite(led[1], HIGH);
      relRepPlayPause[1][17] = relRepPlayPause[1][17] - 1;
      delay(8);
    }
    else if (relRepPlayPause[1][18] != 00) {
      digitalWrite(led[1], LOW);
      relRepPlayPause[1][18] = relRepPlayPause[1][18] - 1;
      delay(8);
    }
    else if (relRepPlayPause[1][19] != 00) {
      digitalWrite(led[1], HIGH);
      relRepPlayPause[1][19] = relRepPlayPause[1][19] - 1;
      delay(8);
    }
    else if (relRepPlayPause[1][20] != 00) {
      digitalWrite(led[1], LOW);
      relRepPlayPause[1][20] = relRepPlayPause[1][20] - 1;
      delay(8);
    }
    else if (relRepPlayPause[1][21] != 00) {
      digitalWrite(led[1], HIGH);
      relRepPlayPause[1][21] = relRepPlayPause[1][21] - 1;
      delay(8);
    }
    else if (relRepPlayPause[1][22] != 00) {
      digitalWrite(led[1], LOW);
      relRepPlayPause[1][22] = relRepPlayPause[1][22] - 1;
      delay(8);
    }
    else if (relPlayPause[1][23] != 00) {
      digitalWrite(led[1], HIGH);
      relRepPlayPause[1][23] = relRepPlayPause[1][23] - 1;
      delay(8);
    }
    //릴레이2 녹화 재생 관련 코드 끝


    //릴레이3 녹화 재생 관련 코드 시작
    if (relRepPlayPause[2][0] != 00) {
      digitalWrite(led[2], LOW);
      relRepPlayPause[2][0] = relRepPlayPause[2][0] - 1;
      delay(8);
    }
    else if (relRepPlayPause[2][1] != 00) {
      digitalWrite(led[2], HIGH);
      relRepPlayPause[2][1] = relRepPlayPause[2][1] - 1;
      delay(8);
    }
    else if (relRepPlayPause[2][2] != 00) {
      digitalWrite(led[2], LOW);
      relRepPlayPause[2][2] = relRepPlayPause[2][2] - 1;
      delay(8);
    }
    else if (relRepPlayPause[2][3] != 00) {
      digitalWrite(led[2], HIGH);
      relRepPlayPause[2][3] = relRepPlayPause[2][3] - 1;
      delay(8);
    }
    else if (relRepPlayPause[2][4] != 00) {
      digitalWrite(led[2], LOW);
      relRepPlayPause[2][4] = relRepPlayPause[2][4] - 1;
      delay(8);
    }
    else if (relRepPlayPause[2][5] != 00) {
      digitalWrite(led[2], HIGH);
      relRepPlayPause[2][5] = relRepPlayPause[2][5] - 1;
      delay(8);
    }
    else if (relRepPlayPause[2][6] != 00) {
      digitalWrite(led[2], LOW);
      relRepPlayPause[2][6] = relRepPlayPause[2][6] - 1;
      delay(8);
    }
    else if (relRepPlayPause[2][7] != 00) {
      digitalWrite(led[2], HIGH);
      relRepPlayPause[2][7] = relRepPlayPause[2][7] - 1;
      delay(8);
    }
    else if (relRepPlayPause[2][8] != 00) {
      digitalWrite(led[2], LOW);
      relRepPlayPause[2][8] = relRepPlayPause[2][8] - 1;
      delay(8);
    }
    else if (relRepPlayPause[2][9] != 00) {
      digitalWrite(led[2], HIGH);
      relRepPlayPause[2][9] = relRepPlayPause[2][9] - 1;
      delay(8);
    }
    else if (relRepPlayPause[2][10] != 00) {
      digitalWrite(led[2], LOW);
      relRepPlayPause[2][10] = relRepPlayPause[2][10] - 1;
      delay(8);
    }
    else if (relRepPlayPause[2][11] != 00) {
      digitalWrite(led[2], HIGH);
      relRepPlayPause[2][11] = relRepPlayPause[2][11] - 1;
      delay(8);
    }
    else if (relRepPlayPause[2][12] != 00) {
      digitalWrite(led[2], LOW);
      relRepPlayPause[2][12] = relRepPlayPause[2][12] - 1;
      delay(8);
    }
    else if (relRepPlayPause[2][13] != 00) {
      digitalWrite(led[2], HIGH);
      relRepPlayPause[2][13] = relRepPlayPause[2][13] - 1;
      delay(8);
    }
    else if (relRepPlayPause[2][14] != 00) {
      digitalWrite(led[2], LOW);
      relRepPlayPause[2][14] = relRepPlayPause[2][14] - 1;
      delay(8);
    }
    else if (relRepPlayPause[2][15] != 00) {
      digitalWrite(led[2], HIGH);
      relRepPlayPause[2][15] = relRepPlayPause[2][15] - 1;
      delay(8);
    }
    else if (relRepPlayPause[2][16] != 00) {
      digitalWrite(led[2], LOW);
      relRepPlayPause[2][16] = relRepPlayPause[2][16] - 1;
      delay(8);
    }
    else if (relRepPlayPause[2][17] != 00) {
      digitalWrite(led[2], HIGH);
      relRepPlayPause[2][17] = relRepPlayPause[2][17] - 1;
      delay(8);
    }
    else if (relRepPlayPause[2][18] != 00) {
      digitalWrite(led[2], LOW);
      relRepPlayPause[2][18] = relRepPlayPause[2][18] - 1;
      delay(8);
    }
    else if (relRepPlayPause[2][19] != 00) {
      digitalWrite(led[2], HIGH);
      relRepPlayPause[2][19] = relRepPlayPause[2][19] - 1;
      delay(8);
    }
    else if (relRepPlayPause[2][20] != 00) {
      digitalWrite(led[2], LOW);
      relRepPlayPause[2][20] = relRepPlayPause[2][20] - 1;
      delay(8);
    }
    else if (relRepPlayPause[2][21] != 00) {
      digitalWrite(led[2], HIGH);
      relRepPlayPause[2][21] = relRepPlayPause[2][21] - 1;
      delay(8);
    }
    else if (relRepPlayPause[2][22] != 00) {
      digitalWrite(led[2], LOW);
      relRepPlayPause[2][22] = relRepPlayPause[2][22] - 1;
      delay(8);
    }
    else if (relRepPlayPause[2][23] != 00) {
      digitalWrite(led[2], HIGH);
      relRepPlayPause[2][23] = relRepPlayPause[2][23] - 1;
      delay(8);
    }
    //릴레이3 녹화 재생 관련 코드 


    //Start code related to Relay 4 recording playback
    if (relRepPlayPause[3][0] != 00) {
      digitalWrite(led[3], LOW);
      relRepPlayPause[3][0] = relRepPlayPause[3][0] - 1;
      delay(8);
    }
    else if (relRepPlayPause[3][1] != 00) {
      digitalWrite(led[3], HIGH);
      relRepPlayPause[3][1] = relRepPlayPause[3][1] - 1;
      delay(8);
    }
    else if (relRepPlayPause[3][2] != 00) {
      digitalWrite(led[3], LOW);
      relRepPlayPause[3][2] = relRepPlayPause[3][2] - 1;
      delay(8);
    }
    else if (relRepPlayPause[3][3] != 00) {
      digitalWrite(led[3], HIGH);
      relRepPlayPause[3][3] = relRepPlayPause[3][3] - 1;
      delay(8);
    }
    else if (relRepPlayPause[3][4] != 00) {
      digitalWrite(led[3], LOW);
      relRepPlayPause[3][4] = relRepPlayPause[3][4] - 1;
      delay(8);
    }
    else if (relRepPlayPause[3][5] != 00) {
      digitalWrite(led[3], HIGH);
      relRepPlayPause[3][5] = relRepPlayPause[3][5] - 1;
      delay(8);
    }
    else if (relRepPlayPause[3][6] != 00) {
      digitalWrite(led[3], LOW);
      relRepPlayPause[3][6] = relRepPlayPause[3][6] - 1;
      delay(8);
    }
    else if (relRepPlayPause[3][7] != 00) {
      digitalWrite(led[3], HIGH);
      relRepPlayPause[3][7] = relRepPlayPause[3][7] - 1;
      delay(8);
    }
    else if (relRepPlayPause[3][8] != 00) {
      digitalWrite(led[3], LOW);
      relRepPlayPause[3][8] = relRepPlayPause[3][8] - 1;
      delay(8);
    }
    else if (relRepPlayPause[3][9] != 00) {
      digitalWrite(led[3], HIGH);
      relRepPlayPause[3][9] = relRepPlayPause[3][9] - 1;
      delay(8);
    }
    else if (relRepPlayPause[3][10] != 00) {
      digitalWrite(led[3], LOW);
      relRepPlayPause[3][10] = relRepPlayPause[3][10] - 1;
      delay(8);
    }
    else if (relRepPlayPause[3][11] != 00) {
      digitalWrite(led[3], HIGH);
      relRepPlayPause[3][11] = relRepPlayPause[3][11] - 1;
      delay(8);
    }
    else if (relRepPlayPause[3][12] != 00) {
      digitalWrite(led[3], LOW);
      relRepPlayPause[3][12] = relRepPlayPause[3][12] - 1;
      delay(8);
    }
    else if (relRepPlayPause[3][13] != 00) {
      digitalWrite(led[3], HIGH);
      relRepPlayPause[3][13] = relRepPlayPause[3][13] - 1;
      delay(8);
    }
    else if (relRepPlayPause[3][14] != 00) {
      digitalWrite(led[3], LOW);
      relRepPlayPause[3][14] = relRepPlayPause[3][14] - 1;
      delay(8);
    }
    else if (relRepPlayPause[3][15] != 00) {
      digitalWrite(led[3], HIGH);
      relRepPlayPause[3][15] = relRepPlayPause[3][15] - 1;
      delay(8);
    }
    else if (relRepPlayPause[3][16] != 00) {
      digitalWrite(led[3], LOW);
      relRepPlayPause[3][16] = relRepPlayPause[3][16] - 1;
      delay(8);
    }
    else if (relRepPlayPause[3][17] != 00) {
      digitalWrite(led[3], HIGH);
      relRepPlayPause[3][17] = relRepPlayPause[3][17] - 1;
      delay(8);
    }
    else if (relRepPlayPause[3][18] != 00) {
      digitalWrite(led[3], LOW);
      relRepPlayPause[3][18] = relRepPlayPause[3][18] - 1;
      delay(8);
    }
    else if (relRepPlayPause[3][19] != 00) {
      digitalWrite(led[3], HIGH);
      relRepPlayPause[3][19] = relRepPlayPause[3][19] - 1;
      delay(8);
    }
    else if (relRepPlayPause[3][20] != 00) {
      digitalWrite(led[3], LOW);
      relRepPlayPause[3][20] = relRepPlayPause[3][20] - 1;
      delay(8);
    }
    else if (relRepPlayPause[3][21] != 00) {
      digitalWrite(led[3], HIGH);
      relRepPlayPause[3][21] = relRepPlayPause[3][21] - 1;
      delay(8);
    }
    else if (relRepPlayPause[3][22] != 00) {
      digitalWrite(led[3], LOW);
      relRepPlayPause[3][22] = relRepPlayPause[3][22] - 1;
      delay(8);
    }
    else if (relRepPlayPause[3][23] != 00) {
      digitalWrite(led[3], HIGH);
      relRepPlayPause[3][23] = relRepPlayPause[3][23] - 1;
      delay(8);
    }
    //릴레이4 녹화 재생 관련 코드 끝

    
    //Start code related to Relay 5 recording playback
    if (relPlayPause[4][0] != 00) {
      digitalWrite(led[4], LOW);
      relPlayPause[4][0] = relPlayPause[4][0] - 1;
      delay(8);
    }
    else if (relPlayPause[4][1] != 00) {
      digitalWrite(led[4], HIGH);
      relPlayPause[4][1] = relPlayPause[4][1] - 1;
      delay(8);
    }
    else if (relPlayPause[4][2] != 00) {
      digitalWrite(led[4], LOW);
      relPlayPause[4][2] = relPlayPause[4][2] - 1;
      delay(8);
    }
    else if (relPlayPause[4][3] != 00) {
      digitalWrite(led[4], HIGH);
      relPlayPause[4][3] = relPlayPause[4][3] - 1;
      delay(8);
    }
    else if (relPlayPause[4][4] != 00) {
      digitalWrite(led[4], LOW);
      relPlayPause[4][4] = relPlayPause[4][4] - 1;
      delay(8);
    }
    else if (relPlayPause[4][5] != 00) {
      digitalWrite(led[4], HIGH);
      relPlayPause[4][5] = relPlayPause[4][5] - 1;
      delay(8);
    }
    else if (relPlayPause[4][6] != 00) {
      digitalWrite(led[4], LOW);
      relPlayPause[4][6] = relPlayPause[4][6] - 1;
      delay(8);
    }
    else if (relPlayPause[4][7] != 00) {
      digitalWrite(led[4], HIGH);
      relPlayPause[4][7] = relPlayPause[4][7] - 1;
      delay(8);
    }
    else if (relPlayPause[4]8] != 00) {
      digitalWrite(led[4], LOW);
      relPlayPause[4]8] = relPlayPause[4]8] - 1;
      delay(8);
    }
    else if (relPlayPause[4][9] != 00) {
      digitalWrite(led[4], HIGH);
      relPlayPause[4][9] = relPlayPause[4][9] - 1;
      delay(8);
    }
    else if (relPlayPause[4][10] != 00) {
      digitalWrite(led[4], LOW);
      relPlayPause[4][10] = relPlayPause[4][10] - 1;
      delay(8);
    }
    else if (relPlayPause[4][11] != 00) {
      digitalWrite(led[4], HIGH);
      relPlayPause[4][11] = relPlayPause[4][11] - 1;
      delay(8);
    }
    else if ( != 00) {
      digitalWrite(led[4], LOW);
      rel5RepPlayPause[12] = rel5RepPlayPause[12] - 1;
      delay(8);
    }
    else if (rel5RepPlayPause[13] != 00) {
      digitalWrite(led[4], HIGH);
      rel5RepPlayPause[13] = rel5RepPlayPause[13] - 1;
      delay(8);
    }
    else if (rel5RepPlayPause[14] != 00) {
      digitalWrite(led[4], LOW);
      rel5RepPlayPause[14] = rel5RepPlayPause[14] - 1;
      delay(8);
    }
    else if (rel5RepPlayPause[15] != 00) {
      digitalWrite(led[4], HIGH);
      rel5RepPlayPause[15] = rel5RepPlayPause[15] - 1;
      delay(8);
    }
    else if (rel5RepPlayPause[16] != 00) {
      digitalWrite(led[4], LOW);
      rel5RepPlayPause[16] = rel5RepPlayPause[16] - 1;
      delay(8);
    }
    else if (rel5RepPlayPause[17] != 00) {
      digitalWrite(led[4], HIGH);
      rel5RepPlayPause[17] = rel5RepPlayPause[17] - 1;
      delay(8);
    }
    else if (rel5RepPlayPause[18] != 00) {
      digitalWrite(led[4], LOW);
      rel5RepPlayPause[18] = rel5RepPlayPause[18] - 1;
      delay(8);
    }
    else if (rel5RepPlayPause[19] != 00) {
      digitalWrite(led[4], HIGH);
      rel5RepPlayPause[19] = rel5RepPlayPause[19] - 1;
      delay(8);
    }
    else if (rel5RepPlayPause[20] != 00) {
      digitalWrite(led[4], LOW);
      rel5RepPlayPause[20] = rel5RepPlayPause[20] - 1;
      delay(8);
    }
    else if (rel5RepPlayPause[21] != 00) {
      digitalWrite(led[4], HIGH);
      rel5RepPlayPause[21] = rel5RepPlayPause[21] - 1;
      delay(8);
    }
    else if (rel5RepPlayPause[22] != 00) {
      digitalWrite(led[4], LOW);
      rel5RepPlayPause[22] = rel5RepPlayPause[22] - 1;
      delay(8);
    }
    else if (rel5RepPlayPause[23] != 00) {
      digitalWrite(led[4], HIGH);
      rel5RepPlayPause[23] = rel5RepPlayPause[23] - 1;
      delay(8);
    }
    //릴레이65녹화 재생 관련 코드 끝
    
    //Start code related to Relay 6 recording playback
    if (rel6RepPlayPause[0] != 00) {
      digitalWrite(led[5], LOW);
      rel6RepPlayPause[0] = rel6RepPlayPause[0] - 1;
      delay(8);
    }
    else if (rel6RepPlayPause[1] != 00) {
      digitalWrite(led[5], HIGH);
      rel6RepPlayPause[1] = rel6RepPlayPause[1] - 1;
      delay(8);
    }
    else if (rel6RepPlayPause[2] != 00) {
      digitalWrite(led[5], LOW);
      rel6RepPlayPause[2] = rel6RepPlayPause[2] - 1;
      delay(8);
    }
    else if (rel6RepPlayPause[3] != 00) {
      digitalWrite(led[5], HIGH);
      rel6RepPlayPause[3] = rel6RepPlayPause[3] - 1;
      delay(8);
    }
    else if (rel6RepPlayPause[4] != 00) {
      digitalWrite(led[5], LOW);
      rel6RepPlayPause[4] = rel6RepPlayPause[4] - 1;
      delay(8);
    }
    else if (rel6RepPlayPause[5] != 00) {
      digitalWrite(led[5], HIGH);
      rel6RepPlayPause[5] = rel6RepPlayPause[5] - 1;
      delay(8);
    }
    else if (rel6RepPlayPause[6] != 00) {
      digitalWrite(led[5], LOW);
      rel6RepPlayPause[6] = rel6RepPlayPause[6] - 1;
      delay(8);
    }
    else if (rel6RepPlayPause[7] != 00) {
      digitalWrite(led[5], HIGH);
      rel6RepPlayPause[7] = rel6RepPlayPause[7] - 1;
      delay(8);
    }
    else if (rel6RepPlayPause[8] != 00) {
      digitalWrite(led[5], LOW);
      rel6RepPlayPause[8] = rel6RepPlayPause[8] - 1;
      delay(8);
    }
    else if (rel6RepPlayPause[9] != 00) {
      digitalWrite(led[5], HIGH);
      rel6RepPlayPause[9] = rel6RepPlayPause[9] - 1;
      delay(8);
    }
    else if (rel6RepPlayPause[10] != 00) {
      digitalWrite(led[5], LOW);
      rel6RepPlayPause[10] = rel6RepPlayPause[10] - 1;
      delay(8);
    }
    else if (rel6RepPlayPause[11] != 00) {
      digitalWrite(led[5], HIGH);
      rel6RepPlayPause[11] = rel6RepPlayPause[11] - 1;
      delay(8);
    }
    else if (rel6RepPlayPause[12] != 00) {
      digitalWrite(led[5], LOW);
      rel6RepPlayPause[12] = rel6RepPlayPause[12] - 1;
      delay(8);
    }
    else if (rel6RepPlayPause[13] != 00) {
      digitalWrite(led[5], HIGH);
      rel6RepPlayPause[13] = rel6RepPlayPause[13] - 1;
      delay(8);
    }
    else if (rel6RepPlayPause[14] != 00) {
      digitalWrite(led[5], LOW);
      rel6RepPlayPause[14] = rel6RepPlayPause[14] - 1;
      delay(8);
    }
    else if (rel6RepPlayPause[15] != 00) {
      digitalWrite(led[5], HIGH);
      rel6RepPlayPause[15] = rel6RepPlayPause[15] - 1;
      delay(8);
    }
    else if (rel6RepPlayPause[16] != 00) {
      digitalWrite(led[5], LOW);
      rel6RepPlayPause[16] = rel6RepPlayPause[16] - 1;
      delay(8);
    }
    else if (rel6RepPlayPause[17] != 00) {
      digitalWrite(led[5], HIGH);
      rel6RepPlayPause[17] = rel6RepPlayPause[17] - 1;
      delay(8);
    }
    else if (rel6RepPlayPause[18] != 00) {
      digitalWrite(led[5], LOW);
      rel6RepPlayPause[18] = rel6RepPlayPause[18] - 1;
      delay(8);
    }
    else if (rel6RepPlayPause[19] != 00) {
      digitalWrite(led[5], HIGH);
      rel6RepPlayPause[19] = rel6RepPlayPause[19] - 1;
      delay(8);
    }
    else if (rel6RepPlayPause[20] != 00) {
      digitalWrite(led[5], LOW);
      rel6RepPlayPause[20] = rel6RepPlayPause[20] - 1;
      delay(8);
    }
    else if (rel6RepPlayPause[21] != 00) {
      digitalWrite(led[5], HIGH);
      rel6RepPlayPause[21] = rel6RepPlayPause[21] - 1;
      delay(8);
    }
    else if (rel6RepPlayPause[22] != 00) {
      digitalWrite(led[5], LOW);
      rel6RepPlayPause[22] = rel6RepPlayPause[22] - 1;
      delay(8);
    }
    else if (rel6RepPlayPause[23] != 00) {
      digitalWrite(led[5], HIGH);
      rel6RepPlayPause[23] = rel6RepPlayPause[23] - 1;
      delay(8);
    }
    //릴레이6 녹화 재생 관련 코드 끝
    


    //When all Relay 1 recording execution variables become 0, reset the recording execution variables
    if ((relRepPlayPause[0][0]==0)&&(relRepPlayPause[0][0]==relRepPlayPause[0][1]) && (relRepPlayPause[0][0] == relRepPlayPause[0][2]) &&(relRepPlayPause[0][0]==relRepPlayPause[0][3]) && (relRepPlayPause[0][0] == relRepPlayPause[0][4]) &&(relRepPlayPause[0][0]==relRepPlayPause[0][5]) && (relRepPlayPause[0][0] == relRepPlayPause[0][6]) &&(relRepPlayPause[0][0]==relRepPlayPause[0][7]) && (relRepPlayPause[0][0] == relRepPlayPause[0][8]) &&(relRepPlayPause[0][0]==relRepPlayPause[0][9]) && (relRepPlayPause[0][0] == relRepPlayPause[0][10]) &&(relRepPlayPause[0][0]==relRepPlayPause[0][11]) && (relRepPlayPause[0][0] == relRepPlayPause[0][12]) &&(relRepPlayPause[0][0]==relRepPlayPause[0][13]) && (relRepPlayPause[0][0] == relRepPlayPause[0][14]) &&(relRepPlayPause[0][0]==relRepPlayPause[0][15]) && (relRepPlayPause[0][0] == relRepPlayPause[0][16]) &&(relRepPlayPause[0][0]==relRepPlayPause[0][17]) && (relRepPlayPause[0][0] == relRepPlayPause[0][18]) &&(relRepPlayPause[0][0]==relRepPlayPause[0][19]) && (relRepPlayPause[0][0] == relRepPlayPause[0][20]) &&(relRepPlayPause[0][0]==relRepPlayPause[0][21]) && (relRepPlayPause[0][0] == relRepPlayPause[0][22]) &&(relRepPlayPause[0][0]==relRepPlayPause[0][23]))
    {
      for(int i = 0; i <= 23; i++){
        rel1RepPlayPause[i] = rel1PlayPause[i];
      }
    }

    //When all Relay 2 recording execution variables become 0, reset the recording execution variables
    if ((relRepPlayPause[1][0]==0)&&(relRepPlayPause[1][0]==relRepPlayPause[1][1]) && (relRepPlayPause[1][0] == relRepPlayPause[1][2]) &&(relRepPlayPause[1][0]==relRepPlayPause[1][3]) && (relRepPlayPause[1][0] == relRepPlayPause[1][4]) &&(relRepPlayPause[1][0]==relRepPlayPause[1][5]) && (relRepPlayPause[1][0] == relRepPlayPause[1][6]) &&(relRepPlayPause[1][0]==relRepPlayPause[1][7]) && (relRepPlayPause[1][0] == relRepPlayPause[1][8]) &&(relRepPlayPause[1][0]==relRepPlayPause[1][9]) && (relRepPlayPause[1][0] == relRepPlayPause[1][10]) &&(relRepPlayPause[1][0]==relRepPlayPause[1][11]) && (relRepPlayPause[1][0] == relRepPlayPause[1][12]) &&(relRepPlayPause[1][0]==relRepPlayPause[1][13]) && (relRepPlayPause[1][0] == relRepPlayPause[1][14]) &&(relRepPlayPause[1][0]==relRepPlayPause[1][15]) && (relRepPlayPause[1][0] == relRepPlayPause[1][16]) &&(relRepPlayPause[1][0]==relRepPlayPause[1][17]) && (relRepPlayPause[1][0] == relRepPlayPause[1][18]) &&(relRepPlayPause[1][0]==relRepPlayPause[1][19]) && (relRepPlayPause[1][0] == relRepPlayPause[1][20]) &&(relRepPlayPause[1][0]==relRepPlayPause[1][21]) && (relRepPlayPause[1][0] == relRepPlayPause[1][22]) &&(relRepPlayPause[1][0]==relRepPlayPause[1][23]))
    {
      for(int i = 0; i <= 23; i++){
        rel2RepPlayPause[i] = rel2PlayPause[i];
      }
    }

    //When all Relay 3 recording execution variables become 0, reset the recording execution variables
    if ((relRepPlayPause[2][0]==0)&&(relRepPlayPause[2][0]==relRepPlayPause[2][1]) && (relRepPlayPause[2][0] == relRepPlayPause[2][2]) &&(relRepPlayPause[2][0]==relRepPlayPause[2][3]) && (relRepPlayPause[2][0] == relRepPlayPause[2][4]) &&(relRepPlayPause[2][0]==relRepPlayPause[2][5]) && (relRepPlayPause[2][0] == relRepPlayPause[2][6]) &&(relRepPlayPause[2][0]==relRepPlayPause[2][7]) && (relRepPlayPause[2][0] == relRepPlayPause[2][8]) &&(relRepPlayPause[2][0]==relRepPlayPause[2][9]) && (relRepPlayPause[2][0] == relRepPlayPause[2][10]) &&(relRepPlayPause[2][0]==relRepPlayPause[2][11]) && (relRepPlayPause[2][0] == relRepPlayPause[2][12]) &&(relRepPlayPause[2][0]==relRepPlayPause[2][13]) && (relRepPlayPause[2][0] == relRepPlayPause[2][14]) &&(relRepPlayPause[2][0]==relRepPlayPause[2][15]) && (relRepPlayPause[2][0] == relRepPlayPause[2][16]) &&(relRepPlayPause[2][0]==relRepPlayPause[2][17]) && (relRepPlayPause[2][0] == relRepPlayPause[2][18]) &&(relRepPlayPause[2][0]==relRepPlayPause[2][19]) && (relRepPlayPause[2][0] == relRepPlayPause[2][20]) &&(relRepPlayPause[2][0]==relRepPlayPause[2][21]) && (relRepPlayPause[2][0] == relRepPlayPause[2][22]) &&(relRepPlayPause[2][0]==relRepPlayPause[2][23]))
    {
      for(int i = 0; i <= 23; i++){
        rel3RepPlayPause[i] = rel3PlayPause[i];
      }
    }

    //When all Relay 4 recording execution variables become 0, reset the recording execution variables
    if ((relRepPlayPause[3][0]==0)&&(relRepPlayPause[3][0]==relRepPlayPause[3][1]) && (relRepPlayPause[3][0] == relRepPlayPause[3][2]) &&(relRepPlayPause[3][0]==relRepPlayPause[3][3]) && (relRepPlayPause[3][0] == relRepPlayPause[3][4]) &&(relRepPlayPause[3][0]==relRepPlayPause[3][5]) && (relRepPlayPause[3][0] == relRepPlayPause[3][6]) &&(relRepPlayPause[3][0]==relRepPlayPause[3][7]) && (relRepPlayPause[3][0] == relRepPlayPause[3][8]) &&(relRepPlayPause[3][0]==relRepPlayPause[3][9]) && (relRepPlayPause[3][0] == relRepPlayPause[3][10]) &&(relRepPlayPause[3][0]==relRepPlayPause[3][11]) && (relRepPlayPause[3][0] == relRepPlayPause[3][12]) &&(relRepPlayPause[3][0]==relRepPlayPause[3][13]) && (relRepPlayPause[3][0] == relRepPlayPause[3][14]) &&(relRepPlayPause[3][0]==relRepPlayPause[3][15]) && (relRepPlayPause[3][0] == relRepPlayPause[3][16]) &&(relRepPlayPause[3][0]==relRepPlayPause[3][17]) && (relRepPlayPause[3][0] == rel4RepPlayPause[18]) &&(relRepPlayPause[3][0]==relRepPlayPause[3][19]) && (relRepPlayPause[3][0] == relRepPlayPause[3][20]) &&(relRepPlayPause[3][0]==relRepPlayPause[3][21]) && (relRepPlayPause[3][0] == relRepPlayPause[3][22]) &&(relRepPlayPause[3][0]==relRepPlayPause[3][23]))
    {
      for(int i = 0; i <= 23; i++){
        rel4RepPlayPause[i] = rel4PlayPause[i];
      }
    }
    
    //When all Relay 5 recording execution variables become 0, reset the recording execution variables
    if ((relPlayPause[4][0]==0)&&(relPlayPause[4][0]==relPlayPause[4][1]) && (relPlayPause[4][0] == relPlayPause[4][2]) &&(relPlayPause[4][0]==relPlayPause[4][3]) && (relPlayPause[4][0] == relPlayPause[4][4]) &&(relPlayPause[4][0]==relPlayPause[4][5]) && (relPlayPause[4][0] == relPlayPause[4][6]) &&(relPlayPause[4][0]==relPlayPause[4][7]) && (relPlayPause[4][0] == relPlayPause[4][8]) &&(relPlayPause[4][0]==relPlayPause[4][9]) && (relPlayPause[4][0] == relPlayPause[4][10]) &&(relPlayPause[4][0]==relPlayPause[4][11]) && (relPlayPause[4][0] == rel5RepPlayPause[12]) &&(relPlayPause[4][0]==rel5RepPlayPause[13]) && (relPlayPause[4][0] == rel5RepPlayPause[14]) &&(relPlayPause[4][0]==rel5RepPlayPause[15]) && (relPlayPause[4][0] == rel5RepPlayPause[16]) &&(relPlayPause[4][0]==rel5RepPlayPause[17]) && (relPlayPause[4][0] == rel5RepPlayPause[18]) &&(relPlayPause[4][0]==rel5RepPlayPause[19]) && (relPlayPause[4][0] == rel5RepPlayPause[20]) &&(relPlayPause[4][0]==rel5RepPlayPause[21]) && (relPlayPause[4][0] == rel5RepPlayPause[22]) &&(relPlayPause[4][0]==rel5RepPlayPause[23]))
    {
      for(int i = 0; i <= 23; i++){
        rel5RepPlayPause[i] = rel5PlayPause[i];
      }
    }
    
    //When all Relay 6 recording execution variables become 0, reset the recording execution variables
    if ((rel6RepPlayPause[0]==0)&&(rel6RepPlayPause[0]==rel6RepPlayPause[1]) && (rel6RepPlayPause[0] == rel6RepPlayPause[2]) &&(rel6RepPlayPause[0]==rel6RepPlayPause[3]) && (rel6RepPlayPause[0] == rel6RepPlayPause[4]) &&(rel6RepPlayPause[0]==rel6RepPlayPause[5]) && (rel6RepPlayPause[0] == rel6RepPlayPause[6]) &&(rel6RepPlayPause[0]==rel6RepPlayPause[7]) && (rel6RepPlayPause[0] == rel6RepPlayPause[8]) &&(rel6RepPlayPause[0]==rel6RepPlayPause[9]) && (rel6RepPlayPause[0] == rel6RepPlayPause[10]) &&(rel6RepPlayPause[0]==rel6RepPlayPause[11]) && (rel6RepPlayPause[0] == rel6RepPlayPause[12]) &&(rel6RepPlayPause[0]==rel6RepPlayPause[13]) && (rel6RepPlayPause[0] == rel6RepPlayPause[14]) &&(rel6RepPlayPause[0]==rel6RepPlayPause[15]) && (rel6RepPlayPause[0] == rel6RepPlayPause[16]) &&(rel6RepPlayPause[0]==rel6RepPlayPause[17]) && (rel6RepPlayPause[0] == rel6RepPlayPause[18]) &&(rel6RepPlayPause[0]==rel6RepPlayPause[19]) && (rel6RepPlayPause[0] == rel6RepPlayPause[20]) &&(rel6RepPlayPause[0]==rel6RepPlayPause[21]) && (rel6RepPlayPause[0] == rel6RepPlayPause[22]) &&(rel6RepPlayPause[0]==rel6RepPlayPause[23]))
    {
      for(int i = 0; i <= 23; i++){
        rel6RepPlayPause[i] = rel5PlayPause[i];
      }
    }
  }
}
