#define satu 264
#define dua 297
#define tiga 330
#define empat 352
#define lima 396
#define enam 440
#define tujuh 495
#define delapan 528

int lagu2[] = {satu, dua, tiga, empat, lima, enam, tujuh, delapan};
int tempo2[] = {200, 500, 200, 500, 200,500, 200, 500};

bool lagu1stat = true;
bool next = 1;
uint8_t buzpin = 10;
void setup() {
  Serial.begin(115200);
  pinMode(8,OUTPUT);
  digitalWrite(8,LOW);

  pinMode(buzpin, OUTPUT);
  pinMode(7, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(7) == LOW){ lagu1stat = true;}
  else{lagu1stat = false;}
  Serial.println(lagu1stat);
  
  if (lagu1stat){
  la1();}
//  delay(2000);
//  la2();
}

uint8_t count = 0;
unsigned long pM = 0;
int lagu[] = {satu, dua, tiga, empat, lima, enam, tujuh, delapan};
int tempo[] = {200, 200, 200, 200, 200,200, 200, 200};
int notcount = 7;

  void la1(){
    int cM = millis();
    if (next && count <= notcount){
      tone(buzpin, lagu[count], tempo[count]);
      if(cM - pM >= tempo[count]){
        pM = cM;
        if(count <= notcount){
          count++;
//          Serial.println("count = " + String(count));
          next = true;
        }
//        else {next = false; count == 0; Serial.println("reset count = " + String(count));}
      }
    }
    else if (count >= notcount){count = 0; Serial.println("reset count = " + String(count)); lagu1stat = false;}
  }




  
  void la2(){
    int cM = millis();
    Serial.println(cM);
    
    if (next && count <=7){
      tone(buzpin, lagu2[count], tempo2[count]);
   
    if(cM - pM >= tempo2[count]){
      pM = cM;
      if(count <= 7){
      count++;
      Serial.println(count);
       next = true;
      }
      else {next = false;}
    }
    }
    else{ noTone(buzpin);}
  }
