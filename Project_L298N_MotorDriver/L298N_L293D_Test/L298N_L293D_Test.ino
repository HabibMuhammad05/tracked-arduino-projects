//modul 1, L293D, trailer
int Dpwm1 = 10;
int Din1 = A0;
int Din2 = 9;
int Din3 = 12;
int Din4 = 13;
int Dpwm2 = 11;

//modul 2, L298N
int Npwm1 = 5;
int Nin1 = 2;
int Nin2 = 3;
int Nin3 = 4;
int Nin4 = 7;
int Npwm2 = 6;

String perintah;

void setup() {
  Serial.begin(115200);
  pinMode(Dpwm1,OUTPUT);
  pinMode(Din1,OUTPUT);
  pinMode(Din2,OUTPUT);
  pinMode(Din3,OUTPUT);
  pinMode(Din4,OUTPUT);
  pinMode(Dpwm2,OUTPUT);
  
  pinMode(Npwm1,OUTPUT);
  pinMode(Nin1,OUTPUT);
  pinMode(Nin2,OUTPUT);
  pinMode(Nin3,OUTPUT);
  pinMode(Nin4,OUTPUT);
  pinMode(Npwm2,OUTPUT);
}

void loop() {

    if(Serial.available()!=0){
        perintah = Serial.readString();
        Serial.print(perintah);
        Serial.println();
    
       if (perintah == "4")  { majuDepan(200); majuTrailer(200);  }
       if (perintah == "3")  { mundurDepan(200); mundurTrailer(200);        }
       if (perintah == "6")  { kananDepan(200,0); kiriTrailer(200,0);       }
       if (perintah == "8")  { serongkanan(255,100); serongkananTrailer(255,100);}
       if (perintah == "7")  { kiriDepan(0,200); kiriTrailer(0,200);         }
       if (perintah == "9")  { serongkiri(100,255); serongkiriTrailer(100,255); }
       if (perintah == "5")  { berhenti();          }
       delay(10);
    }
}


//---------------------------------modul 1----------------------------------------//
void mundurTrailer(int spdmundur){
  digitalWrite(Din1,LOW);
  digitalWrite(Din2,HIGH);
  
  digitalWrite(Din4,LOW);
  digitalWrite(Din3,HIGH);
  
  analogWrite(Dpwm1, spdmundur);
  analogWrite(Dpwm2, spdmundur);
}
void majuTrailer(int spdmaju){
  digitalWrite(Din1,HIGH);
  digitalWrite(Din2,LOW);
  
  digitalWrite(Din4,HIGH);
  digitalWrite(Din3,LOW);
  
  analogWrite(Dpwm1, spdmaju);
  analogWrite(Dpwm2, spdmaju);
}
void kananTrailer(int spdkir, int spdkan){
  digitalWrite(Din1,HIGH);
  digitalWrite(Din2,LOW);
  
  digitalWrite(Din4,HIGH);
  digitalWrite(Din3,LOW);

  analogWrite(Dpwm1, spdkir);
  analogWrite(Dpwm2, spdkan);
}
void kiriTrailer(int spdkir2, int spdkan2){
  digitalWrite(Din1,HIGH);
  digitalWrite(Din2,LOW);
  
  digitalWrite(Din4,HIGH);
  digitalWrite(Din3,LOW);

  analogWrite(Dpwm1, spdkir2);
  analogWrite(Dpwm2, spdkan2);
}
void serongkananTrailer(int spdkiriD, int spdkananD){
  digitalWrite(Din1,HIGH);
  digitalWrite(Din2,LOW);
  
  digitalWrite(Din3,HIGH);
  digitalWrite(Din4,LOW);
  
  analogWrite(Dpwm1, spdkiriD);
  analogWrite(Dpwm2, spdkananD);
}
void serongkiriTrailer(int spdkiri2D, int spdkanan2D){
  digitalWrite(Din1,HIGH);
  digitalWrite(Din2,LOW);
  
  digitalWrite(Din3,HIGH);
  digitalWrite(Din4,LOW);
  
  analogWrite(Dpwm1, spdkiri2D);
  analogWrite(Dpwm2, spdkanan2D);
}
void berhenti(){
  digitalWrite(Din1,LOW);
  digitalWrite(Din2,LOW);
  digitalWrite(Din4,LOW);
  digitalWrite(Din3,LOW);

  analogWrite(Dpwm1, 0);
  analogWrite(Dpwm2, 0);
  
  digitalWrite(Nin1,LOW);
  digitalWrite(Nin2,LOW);
  digitalWrite(Nin4,LOW);
  digitalWrite(Nin3,LOW);

  analogWrite(Npwm1, 0);
  analogWrite(Npwm2, 0);
}

//---------------------------------modul 2----------------------------------------//
void mundurDepan(int spdmundurN){
  digitalWrite(Nin1,LOW);
  digitalWrite(Nin2,HIGH);
  
  digitalWrite(Nin4,LOW);
  digitalWrite(Nin3,HIGH);
  
  analogWrite(Npwm1, spdmundurN);
  analogWrite(Npwm2, spdmundurN);
}
void majuDepan(int spdmajuN){
  digitalWrite(Nin1,HIGH);
  digitalWrite(Nin2,LOW);
  
  digitalWrite(Nin4,HIGH);
  digitalWrite(Nin3,LOW);
  
  analogWrite(Npwm1, spdmajuN);
  analogWrite(Npwm2, spdmajuN);
}
void kananDepan(int spdkir1N, int spdkan1N){
  digitalWrite(Nin1,HIGH);
  digitalWrite(Nin2,LOW);
  
  digitalWrite(Nin4,HIGH);
  digitalWrite(Nin3,LOW);

  analogWrite(Npwm1, spdkir1N);
  analogWrite(Npwm2, spdkan1N);
}
void kiriDepan(int spdkir2N, int spdkan2N){
  digitalWrite(Nin1,HIGH);
  digitalWrite(Nin2,LOW);
  
  digitalWrite(Nin4,HIGH);
  digitalWrite(Nin3,LOW);

  analogWrite(Npwm1, spdkir2N);
  analogWrite(Npwm2, spdkan2N);
}
void serongkanan(int spdkiri, int spdkanan){
  digitalWrite(Nin1,HIGH);
  digitalWrite(Nin2,LOW);
  
  digitalWrite(Nin3,HIGH);
  digitalWrite(Nin4,LOW);
  
  analogWrite(Npwm1, spdkiri);
  analogWrite(Npwm2, spdkanan);
}
void serongkiri(int spdkiri2, int spdkanan2){
  digitalWrite(Nin1,HIGH);
  digitalWrite(Nin2,LOW);
  
  digitalWrite(Nin3,HIGH);
  digitalWrite(Nin4,LOW);
  
  analogWrite(Npwm1, spdkiri2);
  analogWrite(Npwm2, spdkanan2);
}
