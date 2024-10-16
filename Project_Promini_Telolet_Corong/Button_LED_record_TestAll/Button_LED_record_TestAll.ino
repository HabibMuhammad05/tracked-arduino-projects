/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/

const uint8_t led[] = {7, 6, 5, 4, 3, 2};
const uint8_t but[] = {8, 9, A0, A1, A2, A3};

bool buttonState[6] = {LOW};

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
  
  for ( int i = 0 ; i < 6 ; i++) {
    pinMode(but[i], INPUT);
    pinMode(led[i], OUTPUT);
    digitalWrite(led[i], LOW);
  }
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));   // turn the LED on (HIGH is the voltage level)
  for ( int i = 0 ; i < 6 ; i++) {
    buttonState[i] = digitalRead(but[i]);
    Serial.print(buttonState[i]);
  }
  Serial.println("");
  delay(1000);
  
//  for ( int i = 0 ; i < 6 ; i++) {
//    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//    digitalWrite(led[i], HIGH);
//    
//    buttonState[i] = digitalRead(but[i]);
//    Serial.print(buttonState[i]);
//    delay(1000);
//  }
//  Serial.println("");
//  delay(1000);
//  for ( int i = 0 ; i < 6 ; i++) {
//    digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
//    digitalWrite(led[i], LOW);
//
//    buttonState[i] = digitalRead(but[i]);
//    Serial.print(buttonState[i]);
//    delay(1000);
//  }
//  Serial.println("");
//  delay(1000);

}



//  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(100);                       // wait for a second
//  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
//  delay(100);                       // wait for a second
