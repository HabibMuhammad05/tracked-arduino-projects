const int but[] = {2, 3, 4, 5};
const int led[] = {8, 9, 10, 11};

bool buttonState[4] = {LOW};

#define rEcord 6
#define pLay 7

#define rEcordLED 12
#define pLayLED 13


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
unsigned int rel1PlayPause[24] = {0};// count, 0=play, 1=pause
unsigned int rel1RepPlayPause[24] = {0};// count, 0=play, 1=pause

unsigned int rel2PlayPause[24] = {0};// count, 0=play, 1=pause
unsigned int rel2RepPlayPause[24] = {0};// count, 0=play, 1=pause

unsigned int rel3PlayPause[24] = {0};// count, 0=play, 1=pause
unsigned int rel3RepPlayPause[24] = {0};// count, 0=play, 1=pause

unsigned int rel4PlayPause[24] = {0};// count, 0=play, 1=pause
unsigned int rel4RepPlayPause[24] = {0};// count, 0=play, 1=pause

void setup(void)
{
  for ( int i = 2 ; i <= 5 ; i++) {
    pinMode(i, INPUT_PULLUP);
  }

  for ( int i = 8 ; i <= 11 ; i++ ) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);

  }

  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);

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
      //Initialize relay 1 recording variables
      rel1PlayPause[i] = 0;
      rel2PlayPause[i] = 0;
      rel3PlayPause[i] = 0;
      rel4PlayPause[i] = 0;
    }

    Serial.println(recordMod);
    recordPushToNot = 0;
    recordNotToPush = 0;
  }


  if ((playPushToNot == 1) && (playNotToPush == 1)) {
    if (playMod == 0) {
      playMod = 1;
      recordMod = 0;
      Serial.println("play mode On");
      digitalWrite(pLayLED, HIGH);
      digitalWrite(rEcordLED, LOW);

      for(int i = 0; i <= 23; i++){
        //Initialize by assigning the recording variable to the relay 1 playback variable
        rel1RepPlayPause[i] = rel1PlayPause[i];
        rel2RepPlayPause[i] = rel2PlayPause[i];
        rel3RepPlayPause[i] = rel3PlayPause[i];
        rel4RepPlayPause[i] = rel4PlayPause[i];
      }
    }
    Serial.println(playMod);
    playPushToNot = 0;
    playNotToPush = 0;
  }


  //Operation part when record mode is On
  if ((recordMod == 1) && (playMod == 0)) {
      for(int i = 0; i <= 4; i++){
        buttonState[i] = !digitalRead(but[i]);
    }

    //버튼1이 눌려있을 때
    if (buttonState[0] == HIGH) {
      digitalWrite(led[0], HIGH);
      delay(10);

      //버튼1 눌려있는 것 녹화 시작
      if ((rel1PlayPause[0] != 0) && (rel1PlayPause[2] == 0)) {
        rel1PlayPause[1] = rel1PlayPause[1] + 1;
      }
      else if (rel1PlayPause[4] == 0) {
        rel1PlayPause[3] = rel1PlayPause[3] + 1;
      }
      else if (rel1PlayPause[6] == 0) {
        rel1PlayPause[5] = rel1PlayPause[5] + 1;
      }
      else if (rel1PlayPause[8] == 0) {
        rel1PlayPause[7] = rel1PlayPause[7] + 1;
      }
      else if (rel1PlayPause[10] == 0) {
        rel1PlayPause[9] = rel1PlayPause[9] + 1;
      }
      else if (rel1PlayPause[12] == 0) {
        rel1PlayPause[11] = rel1PlayPause[11] + 1;
      }
      else if (rel1PlayPause[14] == 0) {
        rel1PlayPause[13] = rel1PlayPause[13] + 1;
      }
      else if (rel1PlayPause[16] == 0) {
        rel1PlayPause[15] = rel1PlayPause[15] + 1;
      }
      else if (rel1PlayPause[18] == 0) {
        rel1PlayPause[17] = rel1PlayPause[17] + 1;
      }
      else if (rel1PlayPause[20] == 0) {
        rel1PlayPause[19] = rel1PlayPause[19] + 1;
      }
      else if (rel1PlayPause[22] == 0) {
        rel1PlayPause[21] = rel1PlayPause[21] + 1;
      }
      else {
        rel1PlayPause[23] = rel1PlayPause[23] + 1;
      }
      //버튼1 눌려있는 것 녹화 끝
    }
    //버튼1이 띄워져 있을 때
    else {
      digitalWrite(led[0], LOW);
      delay(10);

      //버튼 1 띄워져 있는 것 녹화 시작
      if (rel1PlayPause[1] == 0) {
        rel1PlayPause[0] = rel1PlayPause[0] + 1;
      }
      else if (rel1PlayPause[3] == 0) {
        rel1PlayPause[2] = rel1PlayPause[2] + 1;
      }
      else if (rel1PlayPause[5] == 0) {
        rel1PlayPause[4] = rel1PlayPause[4] + 1;
      }
      else if (rel1PlayPause[7] == 0) {
        rel1PlayPause[6] = rel1PlayPause[6] + 1;
      }
      else if (rel1PlayPause[9] == 0) {
        rel1PlayPause[8] = rel1PlayPause[8] + 1;
      }
      else if (rel1PlayPause[11] == 0) {
        rel1PlayPause[10] = rel1PlayPause[10] + 1;
      }
      else if (rel1PlayPause[13] == 0) {
        rel1PlayPause[12] = rel1PlayPause[12] + 1;
      }
      else if (rel1PlayPause[15] == 0) {
        rel1PlayPause[14] = rel1PlayPause[14] + 1;
      }
      else if (rel1PlayPause[17] == 0) {
        rel1PlayPause[16] = rel1PlayPause[16] + 1;
      }
      else if (rel1PlayPause[19] == 0) {
        rel1PlayPause[18] = rel1PlayPause[18] + 1;
      }
      else if (rel1PlayPause[21] == 0) {
        rel1PlayPause[20] = rel1PlayPause[20] + 1;
      }
      else if (rel1PlayPause[23] == 0) {
        rel1PlayPause[22] = rel1PlayPause[22] + 1;
      }
      //버튼 1 띄워져 있는 것 녹화 끝
    }

    //버튼2가 눌려있을 때
    if (buttonState[1] == HIGH) {
      digitalWrite(led[1], HIGH);

      //버튼2 눌려있는 것 녹화 시작
      if ((rel2PlayPause[0] != 0) && (rel2PlayPause[2] == 0)) {
        rel2PlayPause[1] = rel2PlayPause[1] + 1;
      }
      else if (rel2PlayPause[4] == 0) {
        rel2PlayPause[2] = rel2PlayPause[2] + 1;
      }
      else if (rel2PlayPause[6] == 0) {
        rel2PlayPause[5] = rel2PlayPause[5] + 1;
      }
      else if (rel2PlayPause[8] == 0) {
        rel2PlayPause[7] = rel2PlayPause[7] + 1;
      }
      else if (rel2PlayPause[10] == 0) {
        rel2PlayPause[9] = rel2PlayPause[9] + 1;
      }
      else if (rel2PlayPause[12] == 0) {
        rel2PlayPause[11] = rel2PlayPause[11] + 1;
      }
      else if (rel2PlayPause[14] == 0) {
        rel2PlayPause[13] = rel2PlayPause[13] + 1;
      }
      else if (rel2PlayPause[16] == 0) {
        rel2PlayPause[15] = rel2PlayPause[15] + 1;
      }
      else if (rel2PlayPause[18] == 0) {
        rel2PlayPause[17] = rel2PlayPause[17] + 1;
      }
      else if (rel2PlayPause[20] == 0) {
        rel2PlayPause[19] = rel2PlayPause[19] + 1;
      }
      else if (rel2PlayPause[22] == 0) {
        rel2PlayPause[21] = rel2PlayPause[21] + 1;
      }
      else {
        rel2PlayPause[23] = rel2PlayPause[23] + 1;
      }
      //버튼2 눌려있는 것 녹화 끝
    }
    //버튼2가 띄워져 있을 때
    else {
      digitalWrite(led[1], LOW);
      delay(10);

      //버튼2 띄워져 있는 것 녹화 시작
      if (rel2PlayPause[1] == 0) {
        rel2PlayPause[0] = rel2PlayPause[0] + 1;
      }
      else if (rel2PlayPause[2] == 0) {
        rel2PlayPause[2] = rel2PlayPause[2] + 1;
      }
      else if (rel2PlayPause[5] == 0) {
        rel2PlayPause[4] = rel2PlayPause[4] + 1;
      }
      else if (rel2PlayPause[7] == 0) {
        rel2PlayPause[6] = rel2PlayPause[6] + 1;
      }
      else if (rel2PlayPause[9] == 0) {
        rel2PlayPause[8] = rel2PlayPause[8] + 1;
      }
      else if (rel2PlayPause[11] == 0) {
        rel2PlayPause[10] = rel2PlayPause[10] + 1;
      }
      else if (rel2PlayPause[13] == 0) {
        rel2PlayPause[12] = rel2PlayPause[12] + 1;
      }
      else if (rel2PlayPause[15] == 0) {
        rel2PlayPause[14] = rel2PlayPause[14] + 1;
      }
      else if (rel2PlayPause[17] == 0) {
        rel2PlayPause[16] = rel2PlayPause[16] + 1;
      }
      else if (rel2PlayPause[19] == 0) {
        rel2PlayPause[18] = rel2PlayPause[18] + 1;
      }
      else if (rel2PlayPause[21] == 0) {
        rel2PlayPause[20] = rel2PlayPause[20] + 1;
      }
      else if (rel2PlayPause[23] == 0) {
        rel2PlayPause[22] = rel2PlayPause[22] + 1;
      }
      //버튼2 띄워져 있는 것 녹화 끝
    }

    //버튼3가 눌러져 있을 때
    if (buttonState[2] == HIGH) {
      digitalWrite(led[2], HIGH);
      delay(10);

      //버튼3 눌려있는 것 녹화 시작
      if ((rel3PlayPause[0] != 0) && (rel3PlayPause[2] == 0)) {
        rel3PlayPause[1] = rel3PlayPause[1] + 1;
      }
      else if (rel3PlayPause[4] == 0) {
        rel3PlayPause[3] = rel3PlayPause[3] + 1;
      }
      else if (rel3PlayPause[6] == 0) {
        rel3PlayPause[5] = rel3PlayPause[5] + 1;
      }
      else if (rel3PlayPause[8] == 0) {
        rel3PlayPause[7] = rel3PlayPause[7] + 1;
      }
      else if (rel3PlayPause[10] == 0) {
        rel3PlayPause[9] = rel3PlayPause[9] + 1;
      }
      else if (rel3PlayPause[12] == 0) {
        rel3PlayPause[11] = rel3PlayPause[11] + 1;
      }
      else if (rel3PlayPause[14] == 0) {
        rel3PlayPause[13] = rel3PlayPause[13] + 1;
      }
      else if (rel3PlayPause[16] == 0) {
        rel3PlayPause[15] = rel3PlayPause[15] + 1;
      }
      else if (rel3PlayPause[18] == 0) {
        rel3PlayPause[17] = rel3PlayPause[17] + 1;
      }
      else if (rel3PlayPause[20] == 0) {
        rel3PlayPause[19] = rel3PlayPause[19] + 1;
      }
      else if (rel3PlayPause[22] == 0) {
        rel3PlayPause[21] = rel3PlayPause[21] + 1;
      }
      else {
        rel3PlayPause[23] = rel3PlayPause[23] + 1;
      }
      //버튼3 눌려있는 것 녹화 끝
    }
    //버튼3가 띄워져 있을 때
    else {
      digitalWrite(led[2], LOW);
      delay(10);

      //버튼3 띄워져 있는 것 녹화 시작
      if (rel3PlayPause[1] == 0) {
        rel3PlayPause[0] = rel3PlayPause[0] + 1;
      }
      else if (rel3PlayPause[3] == 0) {
        rel3PlayPause[2] = rel3PlayPause[2] + 1;
      }
      else if (rel3PlayPause[5] == 0) {
        rel3PlayPause[4] = rel3PlayPause[4] + 1;
      }
      else if (rel3PlayPause[7] == 0) {
        rel3PlayPause[6] = rel3PlayPause[6] + 1;
      }
      else if (rel3PlayPause[9] == 0) {
        rel3PlayPause[8] = rel3PlayPause[8] + 1;
      }
      else if (rel3PlayPause[11] == 0) {
        rel3PlayPause[10] = rel3PlayPause[10] + 1;
      }
      else if (rel3PlayPause[13] == 0) {
        rel3PlayPause[12] = rel3PlayPause[12] + 1;
      }
      else if (rel3PlayPause[15] == 0) {
        rel3PlayPause[14] = rel3PlayPause[14] + 1;
      }
      else if (rel3PlayPause[17] == 0) {
        rel3PlayPause[16] = rel3PlayPause[16] + 1;
      }
      else if (rel3PlayPause[19] == 0) {
        rel3PlayPause[18] = rel3PlayPause[18] + 1;
      }
      else if (rel3PlayPause[21] == 0) {
        rel3PlayPause[20] = rel3PlayPause[20] + 1;
      }
      else if (rel3PlayPause[23] == 0) {
        rel3PlayPause[22] = rel3PlayPause[22] + 1;
      }
      //버튼3 띄워져 있는 것 녹화 끝
    }

    //버튼4가 눌러져 있을 때
    if (buttonState[3] == HIGH) {
      digitalWrite(led[3], HIGH);
      delay(10);

      //버튼4 눌려있는 것 녹화 시작
      if ((rel4PlayPause[0] != 0) && (rel4PlayPause[2] == 0)) {
        rel4PlayPause[1] = rel4PlayPause[1] + 1;
      }
      else if (rel4PlayPause[4] == 0) {
        rel4PlayPause[3] = rel4PlayPause[3] + 1;
      }
      else if (rel4PlayPause[6] == 0) {
        rel4PlayPause[5] = rel4PlayPause[5] + 1;
      }
      else if (rel4PlayPause[8] == 0) {
        rel4PlayPause[7] = rel4PlayPause[7] + 1;
      }
      else if (rel4PlayPause[10] == 0) {
        rel4PlayPause[9] = rel4PlayPause[9] + 1;
      }
      else if (rel4PlayPause[12] == 0) {
        rel4PlayPause[11] = rel4PlayPause[11] + 1;
      }
      else if (rel4PlayPause[14] == 0) {
        rel4PlayPause[13] = rel4PlayPause[13] + 1;
      }
      else if (rel4PlayPause[16] == 0) {
        rel4PlayPause[15] = rel4PlayPause[15] + 1;
      }
      else if (rel4PlayPause[18] == 0) {
        rel4PlayPause[17] = rel4PlayPause[17] + 1;
      }
      else if (rel4PlayPause[20] == 0) {
        rel4PlayPause[19] = rel4PlayPause[19] + 1;
      }
      else if (rel4PlayPause[22] == 0) {
        rel4PlayPause[21] = rel4PlayPause[21] + 1;
      }
      else {
        rel4PlayPause[23] = rel4PlayPause[23] + 1;
      }
      //버튼4 눌려있는 것 녹화 끝
    }
    //버튼4가 띄워져 있을 때
    else {
      digitalWrite(led[3], LOW);
      delay(10);
      
      //버튼4 띄워져 있는 것 녹화 시작
      if (rel4PlayPause[1] == 0) {
        rel4PlayPause[0] = rel4PlayPause[0] + 1;
      }
      else if (rel4PlayPause[3] == 0) {
        rel4PlayPause[2] = rel4PlayPause[2] + 1;
      }
      else if (rel4PlayPause[5] == 0) {
        rel4PlayPause[4] = rel4PlayPause[4] + 1;
      }
      else if (rel4PlayPause[7] == 0) {
        rel4PlayPause[6] = rel4PlayPause[6] + 1;
      }
      else if (rel4PlayPause[9] == 0) {
        rel4PlayPause[8] = rel4PlayPause[8] + 1;
      }
      else if (rel4PlayPause[11] == 0) {
        rel4PlayPause[10] = rel4PlayPause[10] + 1;
      }
      else if (rel4PlayPause[13] == 0) {
        rel4PlayPause[12] = rel4PlayPause[12] + 1;
      }
      else if (rel4PlayPause[15] == 0) {
        rel4PlayPause[14] = rel4PlayPause[14] + 1;
      }
      else if (rel4PlayPause[17] == 0) {
        rel4PlayPause[16] = rel4PlayPause[16] + 1;
      }
      else if (rel4PlayPause[19] == 0) {
        rel4PlayPause[18] = rel4PlayPause[18] + 1;
      }
      else if (rel4PlayPause[21] == 0) {
        rel4PlayPause[20] = rel4PlayPause[20] + 1;
      }
      else if (rel4PlayPause[23] == 0) {
        rel4PlayPause[22] = rel4PlayPause[22] + 1;
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
      Serial.println(buttonState[3]);
    */
  }


  //재생 모드로 들어갔을 때
  if ((playMod == 1) && (recordMod == 0)) {
    //릴레이1 녹화 재생 관련 코드 시작
    if (rel1RepPlayPause[0] != 00) {
      digitalWrite(led[0], LOW);
      rel1RepPlayPause[0] = rel1RepPlayPause[0] - 1;
      delay(8);
    }
    else if (rel1RepPlayPause[1] != 00) {
      digitalWrite(led[0], HIGH);
      rel1RepPlayPause[1] = rel1RepPlayPause[1] - 1;
      delay(8);
    }
    else if (rel1RepPlayPause[2] != 00) {
      digitalWrite(led[0], LOW);
      rel1RepPlayPause[2] = rel1RepPlayPause[2] - 1;
      delay(8);
    }
    else if (rel1RepPlayPause[3] != 00) {
      digitalWrite(led[0], HIGH);
      rel1RepPlayPause[3] = rel1RepPlayPause[3] - 1;
      delay(8);
    }
    else if (rel1RepPlayPause[4] != 00) {
      digitalWrite(led[0], LOW);
      rel1RepPlayPause[4] = rel1RepPlayPause[4] - 1;
      delay(8);
    }
    else if (rel1RepPlayPause[5] != 00) {
      digitalWrite(led[0], HIGH);
      rel1RepPlayPause[5] = rel1RepPlayPause[5] - 1;
      delay(8);
    }
    else if (rel1RepPlayPause[6] != 00) {
      digitalWrite(led[0], LOW);
      rel1RepPlayPause[6] = rel1RepPlayPause[6] - 1;
      delay(8);
    }
    else if (rel1RepPlayPause[7] != 00) {
      digitalWrite(led[0], HIGH);
      rel1RepPlayPause[7] = rel1RepPlayPause[7] - 1;
      delay(8);
    }
    else if (rel1RepPlayPause[8] != 00) {
      digitalWrite(led[0], LOW);
      rel1RepPlayPause[8] = rel1RepPlayPause[8] - 1;
      delay(8);
    }
    else if (rel1RepPlayPause[9] != 00) {
      digitalWrite(led[0], HIGH);
      rel1RepPlayPause[9] = rel1RepPlayPause[9] - 1;
      delay(8);
    }
    else if (rel1RepPlayPause[10] != 00) {
      digitalWrite(led[0], LOW);
      rel1RepPlayPause[10] = rel1RepPlayPause[10] - 1;
      delay(8);
    }
    else if (rel1RepPlayPause[11] != 00) {
      digitalWrite(led[0], HIGH);
      rel1RepPlayPause[11] = rel1RepPlayPause[11] - 1;
      delay(8);
    }
    else if (rel1RepPlayPause[12] != 00) {
      digitalWrite(led[0], LOW);
      rel1RepPlayPause[12] = rel1RepPlayPause[12] - 1;
      delay(8);
    }
    else if (rel1RepPlayPause[13] != 00) {
      digitalWrite(led[0], HIGH);
      rel1RepPlayPause[13] = rel1RepPlayPause[13] - 1;
      delay(8);
    }
    else if (rel1RepPlayPause[14] != 00) {
      digitalWrite(led[0], LOW);
      rel1RepPlayPause[14] = rel1RepPlayPause[14] - 1;
      delay(8);
    }
    else if (rel1RepPlayPause[15] != 00) {
      digitalWrite(led[0], HIGH);
      rel1RepPlayPause[15] = rel1RepPlayPause[15] - 1;
      delay(8);
    }
    else if (rel1RepPlayPause[16] != 00) {
      digitalWrite(led[0], LOW);
      rel1RepPlayPause[16] = rel1RepPlayPause[16] - 1;
      delay(8);
    }
    else if (rel1RepPlayPause[17] != 00) {
      digitalWrite(led[0], HIGH);
      rel1RepPlayPause[17] = rel1RepPlayPause[17] - 1;
      delay(8);
    }
    else if (rel1RepPlayPause[18] != 00) {
      digitalWrite(led[0], LOW);
      rel1RepPlayPause[18] = rel1RepPlayPause[18] - 1;
      delay(8);
    }
    else if (rel1RepPlayPause[19] != 00) {
      digitalWrite(led[0], HIGH);
      rel1RepPlayPause[19] = rel1RepPlayPause[19] - 1;
      delay(8);
    }
    else if (rel1RepPlayPause[20] != 00) {
      digitalWrite(led[0], LOW);
      rel1RepPlayPause[20] = rel1RepPlayPause[20] - 1;
      delay(8);
    }
    else if (rel1RepPlayPause[21] != 00) {
      digitalWrite(led[0], HIGH);
      rel1RepPlayPause[21] = rel1RepPlayPause[21] - 1;
      delay(8);
    }
    else if (rel1RepPlayPause[22] != 00) {
      digitalWrite(led[0], LOW);
      rel1RepPlayPause[22] = rel1RepPlayPause[22] - 1;
      delay(8);
    }
    else if (rel1RepPlayPause[23] != 00) {
      digitalWrite(led[0], HIGH);
      rel1RepPlayPause[23] = rel1RepPlayPause[23] - 1;
      delay(8);
    }
    //릴레이1 녹화 재생 관련 코드 끝

    //릴레이2 녹화 재생 관련 코드 시작
    if (rel2RepPlayPause[0] != 00) {
      digitalWrite(led[1], LOW);
      rel2RepPlayPause[0] = rel2RepPlayPause[0] - 1;
      delay(8);
    }
    else if (rel2RepPlayPause[1] != 00) {
      digitalWrite(led[1], HIGH);
      rel2RepPlayPause[1] = rel2RepPlayPause[1] - 1;
      delay(8);
    }
    else if (rel2RepPlayPause[2] != 00) {
      digitalWrite(led[1], LOW);
      rel2RepPlayPause[2] = rel2RepPlayPause[2] - 1;
      delay(8);
    }
    else if (rel2RepPlayPause[3] != 00) {
      digitalWrite(led[1], HIGH);
      rel2RepPlayPause[3] = rel2RepPlayPause[3] - 1;
      delay(8);
    }
    else if (rel2RepPlayPause[4] != 00) {
      digitalWrite(led[1], LOW);
      rel2RepPlayPause[4] = rel2RepPlayPause[4] - 1;
      delay(8);
    }
    else if (rel2RepPlayPause[5] != 00) {
      digitalWrite(led[1], HIGH);
      rel2RepPlayPause[5] = rel2RepPlayPause[5] - 1;
      delay(8);
    }
    else if (rel2RepPlayPause[6] != 00) {
      digitalWrite(led[1], LOW);
      rel2RepPlayPause[6] = rel2RepPlayPause[6] - 1;
      delay(8);
    }
    else if (rel2RepPlayPause[7] != 00) {
      digitalWrite(led[1], HIGH);
      rel2RepPlayPause[7] = rel2RepPlayPause[7] - 1;
      delay(8);
    }
    else if (rel2RepPlayPause[8] != 00) {
      digitalWrite(led[1], LOW);
      rel2RepPlayPause[8] = rel2RepPlayPause[8] - 1;
      delay(8);
    }
    else if (rel2RepPlayPause[9] != 00) {
      digitalWrite(led[1], HIGH);
      rel2RepPlayPause[9] = rel2RepPlayPause[9] - 1;
      delay(8);
    }
    else if (rel2RepPlayPause[10] != 00) {
      digitalWrite(led[1], LOW);
      rel2RepPlayPause[10] = rel2RepPlayPause[10] - 1;
      delay(8);
    }
    else if (rel2RepPlayPause[11] != 00) {
      digitalWrite(led[1], HIGH);
      rel2RepPlayPause[11] = rel2RepPlayPause[11] - 1;
      delay(8);
    }
    else if (rel2RepPlayPause[12] != 00) {
      digitalWrite(led[1], LOW);
      rel2RepPlayPause[12] = rel2RepPlayPause[12] - 1;
      delay(8);
    }
    else if (rel2RepPlayPause[13] != 00) {
      digitalWrite(led[1], HIGH);
      rel2RepPlayPause[13] = rel2RepPlayPause[13] - 1;
      delay(8);
    }
    else if (rel2RepPlayPause[14] != 00) {
      digitalWrite(led[1], LOW);
      rel2RepPlayPause[14] = rel2RepPlayPause[14] - 1;
      delay(8);
    }
    else if (rel2RepPlayPause[15] != 00) {
      digitalWrite(led[1], HIGH);
      rel2RepPlayPause[15] = rel2RepPlayPause[15] - 1;
      delay(8);
    }
    else if (rel2RepPlayPause[16] != 00) {
      digitalWrite(led[1], LOW);
      rel2RepPlayPause[16] = rel2RepPlayPause[16] - 1;
      delay(8);
    }
    else if (rel2RepPlayPause[17] != 00) {
      digitalWrite(led[1], HIGH);
      rel2RepPlayPause[17] = rel2RepPlayPause[17] - 1;
      delay(8);
    }
    else if (rel2RepPlayPause[18] != 00) {
      digitalWrite(led[1], LOW);
      rel2RepPlayPause[18] = rel2RepPlayPause[18] - 1;
      delay(8);
    }
    else if (rel2RepPlayPause[19] != 00) {
      digitalWrite(led[1], HIGH);
      rel2RepPlayPause[19] = rel2RepPlayPause[19] - 1;
      delay(8);
    }
    else if (rel2RepPlayPause[20] != 00) {
      digitalWrite(led[1], LOW);
      rel2RepPlayPause[20] = rel2RepPlayPause[20] - 1;
      delay(8);
    }
    else if (rel2RepPlayPause[21] != 00) {
      digitalWrite(led[1], HIGH);
      rel2RepPlayPause[21] = rel2RepPlayPause[21] - 1;
      delay(8);
    }
    else if (rel2RepPlayPause[22] != 00) {
      digitalWrite(led[1], LOW);
      rel2RepPlayPause[22] = rel2RepPlayPause[22] - 1;
      delay(8);
    }
    else if (rel2PlayPause[23] != 00) {
      digitalWrite(led[1], HIGH);
      rel2RepPlayPause[23] = rel2RepPlayPause[23] - 1;
      delay(8);
    }
    //릴레이2 녹화 재생 관련 코드 끝


    //릴레이3 녹화 재생 관련 코드 시작
    if (rel3RepPlayPause[0] != 00) {
      digitalWrite(led[2], LOW);
      rel3RepPlayPause[0] = rel3RepPlayPause[0] - 1;
      delay(8);
    }
    else if (rel3RepPlayPause[1] != 00) {
      digitalWrite(led[2], HIGH);
      rel3RepPlayPause[1] = rel3RepPlayPause[1] - 1;
      delay(8);
    }
    else if (rel3RepPlayPause[2] != 00) {
      digitalWrite(led[2], LOW);
      rel3RepPlayPause[2] = rel3RepPlayPause[2] - 1;
      delay(8);
    }
    else if (rel3RepPlayPause[3] != 00) {
      digitalWrite(led[2], HIGH);
      rel3RepPlayPause[3] = rel3RepPlayPause[3] - 1;
      delay(8);
    }
    else if (rel3RepPlayPause[4] != 00) {
      digitalWrite(led[2], LOW);
      rel3RepPlayPause[4] = rel3RepPlayPause[4] - 1;
      delay(8);
    }
    else if (rel3RepPlayPause[5] != 00) {
      digitalWrite(led[2], HIGH);
      rel3RepPlayPause[5] = rel3RepPlayPause[5] - 1;
      delay(8);
    }
    else if (rel3RepPlayPause[6] != 00) {
      digitalWrite(led[2], LOW);
      rel3RepPlayPause[6] = rel3RepPlayPause[6] - 1;
      delay(8);
    }
    else if (rel3RepPlayPause[7] != 00) {
      digitalWrite(led[2], HIGH);
      rel3RepPlayPause[7] = rel3RepPlayPause[7] - 1;
      delay(8);
    }
    else if (rel3RepPlayPause[8] != 00) {
      digitalWrite(led[2], LOW);
      rel3RepPlayPause[8] = rel3RepPlayPause[8] - 1;
      delay(8);
    }
    else if (rel3RepPlayPause[9] != 00) {
      digitalWrite(led[2], HIGH);
      rel3RepPlayPause[9] = rel3RepPlayPause[9] - 1;
      delay(8);
    }
    else if (rel3RepPlayPause[10] != 00) {
      digitalWrite(led[2], LOW);
      rel3RepPlayPause[10] = rel3RepPlayPause[10] - 1;
      delay(8);
    }
    else if (rel3RepPlayPause[11] != 00) {
      digitalWrite(led[2], HIGH);
      rel3RepPlayPause[11] = rel3RepPlayPause[11] - 1;
      delay(8);
    }
    else if (rel3RepPlayPause[12] != 00) {
      digitalWrite(led[2], LOW);
      rel3RepPlayPause[12] = rel3RepPlayPause[12] - 1;
      delay(8);
    }
    else if (rel3RepPlayPause[13] != 00) {
      digitalWrite(led[2], HIGH);
      rel3RepPlayPause[13] = rel3RepPlayPause[13] - 1;
      delay(8);
    }
    else if (rel3RepPlayPause[14] != 00) {
      digitalWrite(led[2], LOW);
      rel3RepPlayPause[14] = rel3RepPlayPause[14] - 1;
      delay(8);
    }
    else if (rel3RepPlayPause[15] != 00) {
      digitalWrite(led[2], HIGH);
      rel3RepPlayPause[15] = rel3RepPlayPause[15] - 1;
      delay(8);
    }
    else if (rel3RepPlayPause[16] != 00) {
      digitalWrite(led[2], LOW);
      rel3RepPlayPause[16] = rel3RepPlayPause[16] - 1;
      delay(8);
    }
    else if (rel3RepPlayPause[17] != 00) {
      digitalWrite(led[2], HIGH);
      rel3RepPlayPause[17] = rel3RepPlayPause[17] - 1;
      delay(8);
    }
    else if (rel3RepPlayPause[18] != 00) {
      digitalWrite(led[2], LOW);
      rel3RepPlayPause[18] = rel3RepPlayPause[18] - 1;
      delay(8);
    }
    else if (rel3RepPlayPause[19] != 00) {
      digitalWrite(led[2], HIGH);
      rel3RepPlayPause[19] = rel3RepPlayPause[19] - 1;
      delay(8);
    }
    else if (rel3RepPlayPause[20] != 00) {
      digitalWrite(led[2], LOW);
      rel3RepPlayPause[20] = rel3RepPlayPause[20] - 1;
      delay(8);
    }
    else if (rel3RepPlayPause[21] != 00) {
      digitalWrite(led[2], HIGH);
      rel3RepPlayPause[21] = rel3RepPlayPause[21] - 1;
      delay(8);
    }
    else if (rel3RepPlayPause[22] != 00) {
      digitalWrite(led[2], LOW);
      rel3RepPlayPause[22] = rel3RepPlayPause[22] - 1;
      delay(8);
    }
    else if (rel3RepPlayPause[23] != 00) {
      digitalWrite(led[2], HIGH);
      rel3RepPlayPause[23] = rel3RepPlayPause[23] - 1;
      delay(8);
    }
    //릴레이3 녹화 재생 관련 코드 


    //Start code related to Relay 4 recording playback
    if (rel4RepPlayPause[0] != 00) {
      digitalWrite(led[3], LOW);
      rel4RepPlayPause[0] = rel4RepPlayPause[0] - 1;
      delay(8);
    }
    else if (rel4RepPlayPause[1] != 00) {
      digitalWrite(led[3], HIGH);
      rel4RepPlayPause[1] = rel4RepPlayPause[1] - 1;
      delay(8);
    }
    else if (rel4RepPlayPause[2] != 00) {
      digitalWrite(led[3], LOW);
      rel4RepPlayPause[2] = rel4RepPlayPause[2] - 1;
      delay(8);
    }
    else if (rel4RepPlayPause[3] != 00) {
      digitalWrite(led[3], HIGH);
      rel4RepPlayPause[3] = rel4RepPlayPause[3] - 1;
      delay(8);
    }
    else if (rel4RepPlayPause[4] != 00) {
      digitalWrite(led[3], LOW);
      rel4RepPlayPause[4] = rel4RepPlayPause[4] - 1;
      delay(8);
    }
    else if (rel4RepPlayPause[5] != 00) {
      digitalWrite(led[3], HIGH);
      rel4RepPlayPause[5] = rel4RepPlayPause[5] - 1;
      delay(8);
    }
    else if (rel4RepPlayPause[6] != 00) {
      digitalWrite(led[3], LOW);
      rel4RepPlayPause[6] = rel4RepPlayPause[6] - 1;
      delay(8);
    }
    else if (rel4RepPlayPause[7] != 00) {
      digitalWrite(led[3], HIGH);
      rel4RepPlayPause[7] = rel4RepPlayPause[7] - 1;
      delay(8);
    }
    else if (rel4RepPlayPause[8] != 00) {
      digitalWrite(led[3], LOW);
      rel4RepPlayPause[8] = rel4RepPlayPause[8] - 1;
      delay(8);
    }
    else if (rel4RepPlayPause[9] != 00) {
      digitalWrite(led[3], HIGH);
      rel4RepPlayPause[9] = rel4RepPlayPause[9] - 1;
      delay(8);
    }
    else if (rel4RepPlayPause[10] != 00) {
      digitalWrite(led[3], LOW);
      rel4RepPlayPause[10] = rel4RepPlayPause[10] - 1;
      delay(8);
    }
    else if (rel4RepPlayPause[11] != 00) {
      digitalWrite(led[3], HIGH);
      rel4RepPlayPause[11] = rel4RepPlayPause[11] - 1;
      delay(8);
    }
    else if (rel4RepPlayPause[12] != 00) {
      digitalWrite(led[3], LOW);
      rel4RepPlayPause[12] = rel4RepPlayPause[12] - 1;
      delay(8);
    }
    else if (rel4RepPlayPause[13] != 00) {
      digitalWrite(led[3], HIGH);
      rel4RepPlayPause[13] = rel4RepPlayPause[13] - 1;
      delay(8);
    }
    else if (rel4RepPlayPause[14] != 00) {
      digitalWrite(led[3], LOW);
      rel4RepPlayPause[14] = rel4RepPlayPause[14] - 1;
      delay(8);
    }
    else if (rel4RepPlayPause[15] != 00) {
      digitalWrite(led[3], HIGH);
      rel4RepPlayPause[15] = rel4RepPlayPause[15] - 1;
      delay(8);
    }
    else if (rel4RepPlayPause[16] != 00) {
      digitalWrite(led[3], LOW);
      rel4RepPlayPause[16] = rel4RepPlayPause[16] - 1;
      delay(8);
    }
    else if (rel4RepPlayPause[17] != 00) {
      digitalWrite(led[3], HIGH);
      rel4RepPlayPause[17] = rel4RepPlayPause[17] - 1;
      delay(8);
    }
    else if (rel4RepPlayPause[18] != 00) {
      digitalWrite(led[3], LOW);
      rel4RepPlayPause[18] = rel4RepPlayPause[18] - 1;
      delay(8);
    }
    else if (rel4RepPlayPause[19] != 00) {
      digitalWrite(led[3], HIGH);
      rel4RepPlayPause[19] = rel4RepPlayPause[19] - 1;
      delay(8);
    }
    else if (rel4RepPlayPause[20] != 00) {
      digitalWrite(led[3], LOW);
      rel4RepPlayPause[20] = rel4RepPlayPause[20] - 1;
      delay(8);
    }
    else if (rel4RepPlayPause[21] != 00) {
      digitalWrite(led[3], HIGH);
      rel4RepPlayPause[21] = rel4RepPlayPause[21] - 1;
      delay(8);
    }
    else if (rel4RepPlayPause[22] != 00) {
      digitalWrite(led[3], LOW);
      rel4RepPlayPause[22] = rel4RepPlayPause[22] - 1;
      delay(8);
    }
    else if (rel4RepPlayPause[23] != 00) {
      digitalWrite(led[3], HIGH);
      rel4RepPlayPause[23] = rel4RepPlayPause[23] - 1;
      delay(8);
    }
    //릴레이4 녹화 재생 관련 코드 끝


    //When all Relay 1 recording execution variables become 0, reset the recording execution variables
    if ((rel1RepPlayPause[0]==0)&&(rel1RepPlayPause[0]==rel1RepPlayPause[1]) && (rel1RepPlayPause[0] == rel1RepPlayPause[2]) &&(rel1RepPlayPause[0]==rel1RepPlayPause[3]) && (rel1RepPlayPause[0] == rel1RepPlayPause[4]) &&(rel1RepPlayPause[0]==rel1RepPlayPause[5]) && (rel1RepPlayPause[0] == rel1RepPlayPause[6]) &&(rel1RepPlayPause[0]==rel1RepPlayPause[7]) && (rel1RepPlayPause[0] == rel1RepPlayPause[8]) &&(rel1RepPlayPause[0]==rel1RepPlayPause[9]) && (rel1RepPlayPause[0] == rel1RepPlayPause[10]) &&(rel1RepPlayPause[0]==rel1RepPlayPause[11]) && (rel1RepPlayPause[0] == rel1RepPlayPause[12]) &&(rel1RepPlayPause[0]==rel1RepPlayPause[13]) && (rel1RepPlayPause[0] == rel1RepPlayPause[14]) &&(rel1RepPlayPause[0]==rel1RepPlayPause[15]) && (rel1RepPlayPause[0] == rel1RepPlayPause[16]) &&(rel1RepPlayPause[0]==rel1RepPlayPause[17]) && (rel1RepPlayPause[0] == rel1RepPlayPause[18]) &&(rel1RepPlayPause[0]==rel1RepPlayPause[19]) && (rel1RepPlayPause[0] == rel1RepPlayPause[20]) &&(rel1RepPlayPause[0]==rel1RepPlayPause[21]) && (rel1RepPlayPause[0] == rel1RepPlayPause[22]) &&(rel1RepPlayPause[0]==rel1RepPlayPause[23]))
    {
      for(int i = 0; i <= 23; i++){
        rel1RepPlayPause[i] = rel1PlayPause[i];
      }
    }

    //When all Relay 2 recording execution variables become 0, reset the recording execution variables
    if ((rel2RepPlayPause[0]==0)&&(rel2RepPlayPause[0]==rel2RepPlayPause[1]) && (rel2RepPlayPause[0] == rel2RepPlayPause[2]) &&(rel2RepPlayPause[0]==rel2RepPlayPause[3]) && (rel2RepPlayPause[0] == rel2RepPlayPause[4]) &&(rel2RepPlayPause[0]==rel2RepPlayPause[5]) && (rel2RepPlayPause[0] == rel2RepPlayPause[6]) &&(rel2RepPlayPause[0]==rel2RepPlayPause[7]) && (rel2RepPlayPause[0] == rel2RepPlayPause[8]) &&(rel2RepPlayPause[0]==rel2RepPlayPause[9]) && (rel2RepPlayPause[0] == rel2RepPlayPause[10]) &&(rel2RepPlayPause[0]==rel2RepPlayPause[11]) && (rel2RepPlayPause[0] == rel2RepPlayPause[12]) &&(rel2RepPlayPause[0]==rel2RepPlayPause[13]) && (rel2RepPlayPause[0] == rel2RepPlayPause[14]) &&(rel2RepPlayPause[0]==rel2RepPlayPause[15]) && (rel2RepPlayPause[0] == rel2RepPlayPause[16]) &&(rel2RepPlayPause[0]==rel2RepPlayPause[17]) && (rel2RepPlayPause[0] == rel2RepPlayPause[18]) &&(rel2RepPlayPause[0]==rel2RepPlayPause[19]) && (rel2RepPlayPause[0] == rel2RepPlayPause[20]) &&(rel2RepPlayPause[0]==rel2RepPlayPause[21]) && (rel2RepPlayPause[0] == rel2RepPlayPause[22]) &&(rel2RepPlayPause[0]==rel2RepPlayPause[23]))
    {
      for(int i = 0; i <= 23; i++){
        rel2RepPlayPause[i] = rel2PlayPause[i];
      }
    }

    //When all Relay 3 recording execution variables become 0, reset the recording execution variables
    if ((rel3RepPlayPause[0]==0)&&(rel3RepPlayPause[0]==rel3RepPlayPause[1]) && (rel3RepPlayPause[0] == rel3RepPlayPause[2]) &&(rel3RepPlayPause[0]==rel3RepPlayPause[3]) && (rel3RepPlayPause[0] == rel3RepPlayPause[4]) &&(rel3RepPlayPause[0]==rel3RepPlayPause[5]) && (rel3RepPlayPause[0] == rel3RepPlayPause[6]) &&(rel3RepPlayPause[0]==rel3RepPlayPause[7]) && (rel3RepPlayPause[0] == rel3RepPlayPause[8]) &&(rel3RepPlayPause[0]==rel3RepPlayPause[9]) && (rel3RepPlayPause[0] == rel3RepPlayPause[10]) &&(rel3RepPlayPause[0]==rel3RepPlayPause[11]) && (rel3RepPlayPause[0] == rel3RepPlayPause[12]) &&(rel3RepPlayPause[0]==rel3RepPlayPause[13]) && (rel3RepPlayPause[0] == rel3RepPlayPause[14]) &&(rel3RepPlayPause[0]==rel3RepPlayPause[15]) && (rel3RepPlayPause[0] == rel3RepPlayPause[16]) &&(rel3RepPlayPause[0]==rel3RepPlayPause[17]) && (rel3RepPlayPause[0] == rel3RepPlayPause[18]) &&(rel3RepPlayPause[0]==rel3RepPlayPause[19]) && (rel3RepPlayPause[0] == rel3RepPlayPause[20]) &&(rel3RepPlayPause[0]==rel3RepPlayPause[21]) && (rel3RepPlayPause[0] == rel3RepPlayPause[22]) &&(rel3RepPlayPause[0]==rel3RepPlayPause[23]))
    {
      for(int i = 0; i <= 23; i++){
        rel3RepPlayPause[i] = rel3PlayPause[i];
      }
    }

    //When all Relay 1 recording execution variables become 0, reset the recording execution variables
    if ((rel4RepPlayPause[0]==0)&&(rel4RepPlayPause[0]==rel4RepPlayPause[1]) && (rel4RepPlayPause[0] == rel4RepPlayPause[2]) &&(rel4RepPlayPause[0]==rel4RepPlayPause[3]) && (rel4RepPlayPause[0] == rel4RepPlayPause[4]) &&(rel4RepPlayPause[0]==rel4RepPlayPause[5]) && (rel4RepPlayPause[0] == rel4RepPlayPause[6]) &&(rel4RepPlayPause[0]==rel4RepPlayPause[7]) && (rel4RepPlayPause[0] == rel4RepPlayPause[8]) &&(rel4RepPlayPause[0]==rel4RepPlayPause[9]) && (rel4RepPlayPause[0] == rel4RepPlayPause[10]) &&(rel4RepPlayPause[0]==rel4RepPlayPause[11]) && (rel4RepPlayPause[0] == rel4RepPlayPause[12]) &&(rel4RepPlayPause[0]==rel4RepPlayPause[13]) && (rel4RepPlayPause[0] == rel4RepPlayPause[14]) &&(rel4RepPlayPause[0]==rel4RepPlayPause[15]) && (rel4RepPlayPause[0] == rel4RepPlayPause[16]) &&(rel4RepPlayPause[0]==rel4RepPlayPause[17]) && (rel4RepPlayPause[0] == rel4RepPlayPause[18]) &&(rel4RepPlayPause[0]==rel4RepPlayPause[19]) && (rel4RepPlayPause[0] == rel4RepPlayPause[20]) &&(rel4RepPlayPause[0]==rel4RepPlayPause[21]) && (rel4RepPlayPause[0] == rel4RepPlayPause[22]) &&(rel4RepPlayPause[0]==rel4RepPlayPause[23]))
    {
      for(int i = 0; i <= 23; i++){
        rel4RepPlayPause[i] = rel4PlayPause[i];
      }
    }
  }
}
