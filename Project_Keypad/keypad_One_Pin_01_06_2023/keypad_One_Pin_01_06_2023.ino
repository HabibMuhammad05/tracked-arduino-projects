int thresholds[16] = {530, 461, 375, 257, 542, 475, 393, 282, 554, 488, 411, 306, 565, 502, 429, 326};
char key[16]       = {'1', '2', '3', 'A', '4', '5', '6', 'B', '7', '8', '9', 'C', '*', '0', '#', 'D'};
bool state = true;
void setup() {
  pinMode(A0, INPUT);
  pinMode(13, INPUT_PULLUP);
  Serial.begin(115200);
}

void loop() {
  int val = analogRead(A0);
//  Serial.println(val);
//  delay(100);

    for (uint8_t i = 0; i < 16; i++){
    if( abs(val - thresholds[i]) < 5){
      Serial.println(key[i]);
      while(analogRead(A0) < 1000) {
        delay(100); }
    }
  }
  

//  if(state){
//    Serial.println("WifiMode");
//  }else{
//    Serial.println("ketyMode");}
//    
}
//void stateCheck(){
//  if(digitalRead(13) == 0){
//  state = !state;}
//}
