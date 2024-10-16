#include <SoftwareSerial.h>
SoftwareSerial nodemcuConnect (2, 3);

#include <Blynk.h>
BlynkTimer VoltageDataSendEvent;
BlynkTimer LightDataSendEvent;
void setup() {
  Serial.begin(115200);
  nodemcuConnect.begin(115200);
  VoltageDataSendEvent.setInterval(500L, voltageSending);
  LightDataSendEvent.setInterval(900L, lightMeasure);
}

void loop() {
  VoltageDataSendEvent.run();
  LightDataSendEvent.run();
}

void voltageSending(){
  pinMode(A5, INPUT);
  int voltagesend = analogRead(A5);
  voltagesend = voltagesend + 2000;
  nodemcuConnect.println(voltagesend);
  Serial.print("send = "); Serial.println(voltagesend);
  
  float voltage = analogRead(A5) * (6.13/880);
  Serial.print("volt= "); Serial.println(voltage);
}

void lightMeasure(){
  pinMode(A0, INPUT);
  int lightsend = analogRead(A0);
  lightsend = lightsend + 4000;
  nodemcuConnect.println(lightsend);
  Serial.print("lightsend = "); Serial.println(lightsend);
  
  float light = analogRead(A0);
  light = map(light, 130, 950, 0, 1023);
  Serial.print("light= "); Serial.println(light);
}
