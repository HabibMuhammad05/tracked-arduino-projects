//int thresholds[16] = {396, 384, 363, 320, 530, 518, 501, 469, 641, 621, 607, 582, 716, 707, 693, 674};
//char key[16]       = {'1', '2', '3', 'A', '4', '5', '6', 'B', '7', '8', '9', 'C', '*', '0', '#', 'D'};


//int thresholds[16] = {1024, 975, 914, 727, 671, 642, 545, 514, 496, 427, 444, 410, 847, 608, 477, 397};
//char key[16]       = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '*', '#', 'A', 'B', 'C', 'D'};

//int thresholds[16] = {1024, 1006, 920, 731, 685, 645, 546, 522, 498, 430, 447, 412, 850, 609, 478, 397};
//char key[16]       = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '*', '#', 'A', 'B', 'C', 'D'};

//int thresholds[16] = {1024, 967, 906, 730, 667, 637, 546, 513, 495, 425, 445, 410, 840, 605, 475, 393};
//char key[16]       = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '*', '#', 'A', 'B', 'C', 'D'};

int thresholds[16] = {1024, 1006, 920, 731, 685, 645, 547, 522, 498, 429, 447, 415, 851, 609, 478, 395};
char key[16]       = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '*', '#', 'A', 'B', 'C', 'D'};
uint16_t nada;

void setup() {
  pinMode(A0, INPUT);
  pinMode(13, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  int val = analogRead(A0);
  
  Serial.println(val);
  delay(100);

//  for (int i = 0; i < 16; i++){
//    if( abs(val - thresholds[i]) < 7){
//      Serial.println(key[i]);
//      
//      Serial.println(val);
//      if(i >= 10){ nada = 200; beep(true); beep(false); beep(true); }
//      else{ nada = 2320; beep(true); }
//      while(analogRead(A0) > 100) {delay(150); beep(true); beep(false);}
//    }
//  }
//  delay(20);
}

void beep(bool hidup){
  bool state;
  if(hidup){
    state = true;
    if (state) { tone(13, nada); } 
    else { noTone(13); } 
  }
  else{ noTone(13); }
}

//void beep(bool hidup){
//  if(hidup){ state = true; digitalWrite(LED_BUILTIN, (state)? HIGH : LOW ); }
//  else{ digitalWrite(LED_BUILTIN, LOW); }
//}
