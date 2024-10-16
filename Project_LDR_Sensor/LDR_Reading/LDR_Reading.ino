uint8_t data0;
uint8_t data1;
uint8_t data2;
uint8_t data3;
void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
}

void loop() {
  data0 = map(analogRead(A0), 0, 1023, 0, 50);
  Serial.println("A0=" + String(data0));
  delay(10);
  data1 = map(analogRead(A1), 0, 1023, 0, 50);
  Serial.println("A1=" + String(data1));
  delay(10);
  data2 = map(analogRead(A2), 0, 1023, 0, 50);
  Serial.println("A2=" + String(data2));
  delay(10);
  data3 = map(analogRead(A3), 0, 1023, 0, 50);
  Serial.println("A3=" + String(data3));
  Serial.println("");
  delay(1000);
}
