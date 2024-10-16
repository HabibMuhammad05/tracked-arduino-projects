/*----------Soil Moisture Sensor Reading----------------*/
/*-------------Source Code by---------------------------*/
/*------Modified & Adapted by Habib.m @Hab_mz-----------*/
/*-----------------------V1.1---------------------------*/
void setup() {
  Serial.begin(115200);
}

void loop() {
  float lembab = ( 100.00 - ( (analogRead(A0)/1024.00) * 100.00 ) );
  float teg = analogRead(A0);
  teg = map(teg, 0, 1024, 1024,0);
  float tegangan = ( 5.00 - ( (teg/1024.00) * 5.00 ) );
  Serial.print("Soil Moisture = "); 
  Serial.print(lembab); Serial.print("% - ");
  Serial.print(tegangan); Serial.println("V");
  
  delay(1000);
}
//------------------------V1.0--------------------------//
/*  Serial.print("kelembaban tanah = ");
  Serial.print(lembab);
  Serial.println("%");
  Serial.print("tegangan melewati sensor = ");
  Serial.print(tegangan);
  Serial.println("V"); 
  
  float lembab = ( 100.00 - ( (analogRead(sensor_pin)/1024.00) * 100.00 ) );
  int tegangan = analogRead(sensor_pin);
  tegangan = map(tegangan, 0, 1024, 0, 5000);
  Serial.print("kelembaban tanah = ");
  Serial.print(lembab); Serial.println("%");
  Serial.print("tegangan melewati sensor = ");
  Serial.print(tegangan); Serial.println("mV"); */
