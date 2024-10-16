/*-----------------4CH RELAY MODULE RESPONSE TEST PROGRAM----------------------*/
/*----------------------Source Code by Habib Muhammad--------------------------*/
/*-------------------Modified & Adapted by Habib.m @Hab_mz---------------------*/
/*------------------------------------V1.0-------------------------------------*/

//=============================ATUR SESUAI PENGGUNAAN BOARD ANDA, COMMENT SALAH SATU==================================//

//uint8_t relays[] = {8, 7, 6, 5};  // UNCOMMENT JIKA MENGGUNAKAN ARDUINO UNO
uint8_t relays[] = {D8, D7, D6, D5};  // UNCOMMENT JIKA MENGGUNAKAN ESP8266

//=============================ATUR SESUAI PENGGUNAAN BOARD ANDA, COMMENT SALAH SATU==================================//


//------------------------------Mulai setup---------------------------------------//
void setup() {
  for ( int i = 0 ; i < 4 ; i++) {
    pinMode(relays[i], OUTPUT);
    digitalWrite(relays[i], LOW);
  }
}

void loop() {
  //---------------ANIMATION 1---------------------//
  for ( int i = 0 ; i < 4 ; i++) {
    digitalWrite(relays[i], HIGH);
    delay(200);
  }
    
  for ( int i = 0 ; i < 4 ; i++) {
    digitalWrite(relays[i], LOW);
    delay(200);
  }
  
  delay(600);
  
  //---------------ANIMATION 2---------------------//
  for ( int u = 0 ; u < 5 ; u++) {
    for ( int i = 0 ; i < 4 ; i++) {
      digitalWrite(relays[i], HIGH);
    }
    delay(200);
    for ( int i = 0 ; i < 4 ; i++) {
      digitalWrite(relays[i], LOW);
    }
    delay(200);
  }
  
  delay(600);
    
  //---------------ANIMATION 3---------------------//
  for ( int i = 0 ; i < 5 ; i++) {
    digitalWrite(relays[0], HIGH);
    digitalWrite(relays[3], HIGH);
    digitalWrite(relays[1], LOW);
    digitalWrite(relays[2], LOW);
      delay(200);
    digitalWrite(relays[0], LOW);
    digitalWrite(relays[3], LOW);
    digitalWrite(relays[1], HIGH);
    digitalWrite(relays[2], HIGH);
      delay(200);
  }
  
  for ( int i = 0 ; i < 4 ; i++) {
    digitalWrite(relays[i], LOW);
  }
  delay(600);
  
  //---------------ANIMATION 4---------------------//
  for ( int i = 0 ; i < 3 ; i++) {
      digitalWrite(relays[0], HIGH);
      digitalWrite(relays[1], LOW);
      digitalWrite(relays[2], LOW);
      digitalWrite(relays[3], LOW);
        delay(200);
      digitalWrite(relays[0], LOW);
      digitalWrite(relays[1], HIGH);
      digitalWrite(relays[2], LOW);
      digitalWrite(relays[3], LOW);
        delay(200);
      digitalWrite(relays[0], LOW);
      digitalWrite(relays[1], LOW);
      digitalWrite(relays[2], HIGH);
      digitalWrite(relays[3], LOW);
        delay(200);
      digitalWrite(relays[0], LOW);
      digitalWrite(relays[1], LOW);
      digitalWrite(relays[2], LOW);
      digitalWrite(relays[3], HIGH);
        delay(200);
      digitalWrite(relays[0], LOW);
      digitalWrite(relays[1], LOW);
      digitalWrite(relays[2], LOW);
      digitalWrite(relays[3], LOW);
        delay(200);
  } 
  
  delay(600);  
  
  //---------------ANIMATION 5---------------------//
  for ( int i = 0 ; i < 2 ; i++) {
    for ( int J = 0 ; J < 5 ; J++) {
      digitalWrite(relays[0], HIGH);
      digitalWrite(relays[1], HIGH);
      digitalWrite(relays[2], LOW);
      digitalWrite(relays[3], LOW);
        delay(50);
      digitalWrite(relays[0], LOW);
      digitalWrite(relays[1], LOW);
      digitalWrite(relays[2], HIGH);
      digitalWrite(relays[3], HIGH);
        delay(50);
    }
    for ( int J = 0 ; J < 5 ; J++) {
      digitalWrite(relays[0], HIGH);
      digitalWrite(relays[1], HIGH);
      digitalWrite(relays[2], LOW);
      digitalWrite(relays[3], LOW);
        delay(50);
      digitalWrite(relays[0], LOW);
      digitalWrite(relays[1], LOW);
      digitalWrite(relays[2], HIGH);
      digitalWrite(relays[3], HIGH);
        delay(50);
    }
  }
  
  for ( int i = 0 ; i < 4 ; i++) {
    digitalWrite(relays[i], LOW);
  }
    
  delay(600);  
  
  //---------------ANIMATION 6---------------------//
  for ( int i = 4 ; i < 0 ; i--) {
    digitalWrite(relays[i], HIGH);
    delay(200);
  }
    
  for ( int i = 4 ; i < 0 ; i--) {
    digitalWrite(relays[i], LOW);
    delay(200);
  }



//==========================================FAST MODE=========================================//

  //---------------ANIMATION 1---------------------//
  for ( int i = 0 ; i < 4 ; i++) {
    digitalWrite(relays[i], HIGH);
    delay(100);
  }
    
  for ( int i = 0 ; i < 4 ; i++) {
    digitalWrite(relays[i], LOW);
    delay(100);
  }
  
  delay(600);
  
  //---------------ANIMATION 2---------------------//
  for ( int u = 0 ; u < 5 ; u++) {
    for ( int i = 0 ; i < 4 ; i++) {
      digitalWrite(relays[i], HIGH);
    }
    delay(100);
    for ( int i = 0 ; i < 4 ; i++) {
      digitalWrite(relays[i], LOW);
    }
    delay(100);
  }
  
  delay(600);
    
  //---------------ANIMATION 3---------------------//
  for ( int i = 0 ; i < 5 ; i++) {
    digitalWrite(relays[0], HIGH);
    digitalWrite(relays[3], HIGH);
    digitalWrite(relays[1], LOW);
    digitalWrite(relays[2], LOW);
      delay(100);
    digitalWrite(relays[0], LOW);
    digitalWrite(relays[3], LOW);
    digitalWrite(relays[1], HIGH);
    digitalWrite(relays[2], HIGH);
      delay(100);
  }
  
  for ( int i = 0 ; i < 4 ; i++) {
    digitalWrite(relays[i], LOW);
  }
  delay(600);
  
  //---------------ANIMATION 4---------------------//
  for ( int i = 0 ; i < 3 ; i++) {
      digitalWrite(relays[0], HIGH);
      digitalWrite(relays[1], LOW);
      digitalWrite(relays[2], LOW);
      digitalWrite(relays[3], LOW);
        delay(100);
      digitalWrite(relays[0], LOW);
      digitalWrite(relays[1], HIGH);
      digitalWrite(relays[2], LOW);
      digitalWrite(relays[3], LOW);
        delay(100);
      digitalWrite(relays[0], LOW);
      digitalWrite(relays[1], LOW);
      digitalWrite(relays[2], HIGH);
      digitalWrite(relays[3], LOW);
        delay(100);
      digitalWrite(relays[0], LOW);
      digitalWrite(relays[1], LOW);
      digitalWrite(relays[2], LOW);
      digitalWrite(relays[3], HIGH);
        delay(100);
      digitalWrite(relays[0], LOW);
      digitalWrite(relays[1], LOW);
      digitalWrite(relays[2], LOW);
      digitalWrite(relays[3], LOW);
        delay(100);
  } 
  
  delay(600);  
  
  //---------------ANIMATION 5---------------------//
  for ( int i = 0 ; i < 2 ; i++) {
    for ( int J = 0 ; J < 5 ; J++) {
      digitalWrite(relays[0], HIGH);
      digitalWrite(relays[1], HIGH);
      digitalWrite(relays[2], LOW);
      digitalWrite(relays[3], LOW);
        delay(50);
      digitalWrite(relays[0], LOW);
      digitalWrite(relays[1], LOW);
      digitalWrite(relays[2], HIGH);
      digitalWrite(relays[3], HIGH);
        delay(50);
    }
    for ( int J = 0 ; J < 5 ; J++) {
      digitalWrite(relays[0], HIGH);
      digitalWrite(relays[1], HIGH);
      digitalWrite(relays[2], LOW);
      digitalWrite(relays[3], LOW);
        delay(50);
      digitalWrite(relays[0], LOW);
      digitalWrite(relays[1], LOW);
      digitalWrite(relays[2], HIGH);
      digitalWrite(relays[3], HIGH);
        delay(50);
    }
  }
  
  for ( int i = 0 ; i < 4 ; i++) {
    digitalWrite(relays[i], LOW);
  }
    
  delay(600);  
  
  //---------------ANIMATION 6---------------------//
  for ( int i = 4 ; i < 0 ; i--) {
    digitalWrite(relays[i], HIGH);
    delay(100);
  }
    
  for ( int i = 4 ; i < 0 ; i--) {
    digitalWrite(relays[i], LOW);
    delay(100);
  }
}
/*------------------------------------@hab_mz-------------------------------------*/
