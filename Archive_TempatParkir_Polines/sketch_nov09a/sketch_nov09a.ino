#include <Servo.h>
Servo portal;

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

uint8_t binPin[4] = {2, 3, 4, 5};
uint8_t portalPin = 6;
uint8_t ledRed = 7;
uint8_t ledGreen = 8;

uint8_t senPortal = 9;
uint8_t senSlot[4] = {10, 11, 12, 13};

bool slotStatus[4];     
uint8_t validId[] = {0b0001, 0b0010, 0b0011, 0b0100, 0b0101};
String namaId[] = {"user1", "user2", "user3", "user4", "user5"}; 



void setup() { 
  Serial.begin(115200);
  lcd.begin();
  lcd.backlight();

  for(int i = 0; i < 4; i++){
    pinMode(binPin, INPUT_PULLUP);
    pinMode(senSlot, INPUT_PULLUP);
  }

  portal.attach(portalPin);
  portal.write(0);

}

void loop() {
  // put your main code here, to run repeatedly:

}

void readBin(){
  uint8_t binData = (digitalRead(binPin[0]) << 3) | (digitalRead(binPin[1]) << 2) | (digitalRead(binPin[2]) << 1) | (digitalRead(binPin[3]) << 0);
  for(int i = 0; i < 4; i++){
    Serial.print(digitalRead[i]);
  }
  Serial.println();
}
