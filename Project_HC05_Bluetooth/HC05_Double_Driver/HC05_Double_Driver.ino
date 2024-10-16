#include <SoftwareSerial.h>
SoftwareSerial bt (8,9);
String speedData;
uint8_t perintah;

//modul 1, L293D, trailer
uint8_t Dpwm1 = 10;
uint8_t Din1 = A0;
uint8_t Din2 = A1;
uint8_t Din3 = 12;
uint8_t Din4 = A2;
uint8_t Dpwm2 = 11;

//modul 2, L298N
uint8_t Npwm1 = 5;
uint8_t Nin1 = 2;
uint8_t Nin2 = 3;
uint8_t Nin3 = 4;
uint8_t Nin4 = 7;
uint8_t Npwm2 = 6;

uint8_t spdmajuN = 255;
uint8_t spdmundurN = 255;
uint8_t spdkir1N = 255;
uint8_t spdkan1N = 255;


uint8_t spdData = 255;
uint8_t belokData = 255;

void setup() {
  Serial.begin(9600);
  bt.begin(9600);
  pinMode(Dpwm1,OUTPUT);
  pinMode(Din1,OUTPUT);
  pinMode(Din2,OUTPUT);
  pinMode(Din3,OUTPUT);
  pinMode(Din4,OUTPUT);
  digitalWrite(Din4, LOW);
  pinMode(Dpwm2,OUTPUT);
  
  pinMode(Npwm1,OUTPUT);
  pinMode(Nin1,OUTPUT);
  pinMode(Nin2,OUTPUT);
  pinMode(Nin3,OUTPUT);
  pinMode(Nin4,OUTPUT);
  pinMode(Npwm2,OUTPUT);
}

void loop() {
    if(bt.available()){
        perintah = bt.read();
//        speedData = bt.readString();
        Serial.println(perintah);

//       if (speedData.startsWith("maju")){ speedData.replace("maju", ""); spdData = speedData.toInt();}
//       if (speedData.startsWith("belok")){ speedData.replace("belok", ""); belokData = speedData.toInt();}

       
       if (perintah == 1)  { spdData = 255; belokData = 255;        }
       if (perintah == 2)  { spdData = 180; belokData = 180;        }

       
       if (perintah == 4)  { majuDepan();     majuTrailer();        }
       if (perintah == 3)  { mundurDepan();   mundurTrailer();      }
       if (perintah == 6)  { kananDepan();    berhentiTrailer();    }
       if (perintah == 8)  { serongkanan();   majuTrailer(); }
       if (perintah == 7)  { kiriDepan();     berhentiTrailer();    }
       if (perintah == 9)  { serongkiri();    majuTrailer();  }
       if (perintah == 5)  { berhentidepan(); berhentiTrailer();    }
    }
}

//---------------------------------modul 2----------------------------------------//
void majuDepan(){
  digitalWrite(Nin1,HIGH);
  digitalWrite(Nin2,LOW);
  
  digitalWrite(Nin3,HIGH);
  digitalWrite(Nin4,LOW);
  
  analogWrite(Npwm2, spdData);
  analogWrite(Npwm1, spdData);
}
void mundurDepan(){
  digitalWrite(Nin1,LOW);
  digitalWrite(Nin2,HIGH);
  
  digitalWrite(Nin3,LOW);
  digitalWrite(Nin4,HIGH);
  
  analogWrite(Npwm2, spdData);
  analogWrite(Npwm1, spdData);
}
void kananDepan(){
  digitalWrite(Nin1,LOW);
  digitalWrite(Nin2,HIGH);
  
  digitalWrite(Nin3,HIGH);
  digitalWrite(Nin4,LOW);

  analogWrite(Npwm2, belokData);
  analogWrite(Npwm1, belokData);
}
void kiriDepan(){
  digitalWrite(Nin1,HIGH);
  digitalWrite(Nin2,LOW);
  
  digitalWrite(Nin3,LOW);
  digitalWrite(Nin4,HIGH);

  analogWrite(Npwm2, belokData);
  analogWrite(Npwm1, belokData);
}
void serongkanan(){
  digitalWrite(Nin1,HIGH);
  digitalWrite(Nin2,LOW);
  
  digitalWrite(Nin3,HIGH);
  digitalWrite(Nin4,LOW);
  
  analogWrite(Npwm2, belokData);
  analogWrite(Npwm1, 0);
}
void serongkiri(){
  digitalWrite(Nin1,HIGH);
  digitalWrite(Nin2,LOW);
  
  digitalWrite(Nin3,HIGH);
  digitalWrite(Nin4,LOW);
  
  analogWrite(Npwm2, 0);
  analogWrite(Npwm1, belokData);
}

void berhentidepan(){
  digitalWrite(Nin1,LOW);
  digitalWrite(Nin2,LOW);
  digitalWrite(Nin4,LOW);
  digitalWrite(Nin3,LOW);

  analogWrite(Npwm1, 0);
  analogWrite(Npwm2, 0);
}

//---------------------------------modul 1----------------------------------------//

void majuTrailer(){
  digitalWrite(Din1,HIGH);
  digitalWrite(Din2,LOW);
  
  digitalWrite(Din4,HIGH);
  digitalWrite(Din3,LOW);
  
  analogWrite(Dpwm2, spdData);
  analogWrite(Dpwm1, spdData);
}
void mundurTrailer(){
  digitalWrite(Din1,LOW);
  digitalWrite(Din2,HIGH);
  
  digitalWrite(Din4,LOW);
  digitalWrite(Din3,HIGH);
  
  analogWrite(Dpwm2, spdData);
  analogWrite(Dpwm1, spdData);
}
void serongkananTrailer(){
  digitalWrite(Din1,HIGH);
  digitalWrite(Din2,LOW);
  
  digitalWrite(Din4,HIGH);
  digitalWrite(Din3,LOW);
  
  analogWrite(Dpwm2, belokData);
  analogWrite(Dpwm1, belokData - 120);
}
void serongkiriTrailer(){
  digitalWrite(Din1,HIGH);
  digitalWrite(Din2,LOW);
  
  digitalWrite(Din4,HIGH);
  digitalWrite(Din3,LOW);
  
  analogWrite(Dpwm2, belokData - 120);
  analogWrite(Dpwm1, belokData);
}
void berhentiTrailer(){
  digitalWrite(Din1,LOW);
  digitalWrite(Din2,LOW);
  digitalWrite(Din4,LOW);
  digitalWrite(Din3,LOW);

  analogWrite(Dpwm1, 0);
  analogWrite(Dpwm2, 0);
}
