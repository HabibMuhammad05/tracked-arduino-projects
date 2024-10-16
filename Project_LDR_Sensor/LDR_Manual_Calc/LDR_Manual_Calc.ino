#define topR A0
#define topL A1
#define botR A2
#define botL A3
void setup() {
  Serial.begin(115200);
  pinMode(topR, INPUT);
  pinMode(topL, INPUT);
  pinMode(botR, INPUT);
  pinMode(botL, INPUT);
}

void loop() {
  int data1 = analogRead(topR);
  int data2 = analogRead(topL);
  int data3 = analogRead(botR);
  int data4 = analogRead(botL);
  Serial.print("analogRead1 = ");
  Serial.println(data1);
  Serial.print("analogRead2 = ");
  Serial.println(data2);
  Serial.print("analogRead3 = ");
  Serial.println(data3);
  Serial.print("analogRead4 = ");
  Serial.println(data4);
  
  int cdata1 = map(data1, 0, 1023, 0, 255);
  int cdata2 = map(data2, 0, 1023, 0, 255);
  int cdata3 = map(data3, 0, 1023, 0, 255);
  int cdata4 = map(data4, 0, 1023, 0, 255);
  Serial.print("calculated = ");
  Serial.println(cdata1);
  Serial.print("calculated2 = ");
  Serial.println(cdata2);
  Serial.print("calculated3 = ");
  Serial.println(cdata3);
  Serial.print("calculated4 = ");
  Serial.println(cdata4);
  Serial.println();
  
  int avgdataT = (cdata1 + cdata2) / 2;
  int avgdataB = (cdata3 + cdata4) /2;
  int avgdataR = (cdata1 + cdata3) / 2;
  int avgdataL = (cdata2 + cdata4) /2;
  Serial.print("top avg = ");
  Serial.println(avgdataT);
  Serial.print("bottom avg = ");
  Serial.println(avgdataB);
  Serial.print("right avg = ");
  Serial.println(avgdataR);
  Serial.print("left avg = ");
  Serial.println(avgdataL);
  Serial.println();
  Serial.println();
  delay(100);
}
