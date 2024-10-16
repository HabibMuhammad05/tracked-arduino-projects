/**
 *  @file
 *  @Author Septillion (https://github.com/sseptillion)
 *  @date 2016-05-20
 *  @brief Example how to use buttonRead()
 *  
 *  Because of the quasi-bidirectional port on the PCF8574 it's 
 *  possible to use the same pin as input and output at the same time.
 *  
 *  For this, connect the LED (or other device) between Vcc and the pin and
 *  a button between GND and the pin.
 *  
 *  In order to read the pin the output is shortly (460us @ normal I2C speed)
 *  set high during the read. So only use devices that can handle the small break
 *  in state. It's not visable for the human eye with a LED.
 *  
 *  buttonRead() can also be used for pins that are input only.
 *  
 *  In this example pin 0 of the PCF8574 (address 0x20) is used to blink a 
 *  LED but at the same time it can be used to toggle the onboard LED of 
 *  the Arduino.
 *  
 *  NOTE: The button will affect the LED on the same pin. The led will light up 
 *  no matter the set output state when you press the button.
 */


#include <PCF8574.h>
#include <Wire.h>

#define EEPROM_ADDR 0x50 // I2C address of AT24C256
#define ARRAY_SIZE_X 6   // Assuming your array size is 6x12
#define ARRAY_SIZE_Y 12

PCF8574 pcf20(0x27);

const byte onboardLed = 13;
const byte pcfButtonPins[] = {0, 1, 2, 3, 4, 5}; // Pins for the buttons on PCF8574
const byte ledPins[] = {7, 6, 5, 4, 3, 2};    // Pins for the LEDs

unsigned int buttonMillis;
bool previousButtonStates[6] = {false};

void setup() {
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCF8574_LIB_VERSION: ");
  Serial.println(PCF8574_LIB_VERSION);

  Wire.begin();
  pcf20.begin();

  pinMode(onboardLed, OUTPUT);

  for (int i = 0; i < 6; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  unsigned int currentMillis = millis();

  if (Serial.available()) {
    String numStr = Serial.readString();
    readAndPrintSingle2DArray(numStr.toInt());
  }
  
  if ((currentMillis - buttonMillis) >= 100) {
    buttonMillis = currentMillis;

    for (int i = 0; i < 6; i++) {
      bool buttonState = pcf20.readButton(pcfButtonPins[i]);
      if (buttonState != previousButtonStates[i]) {
        previousButtonStates[i] = buttonState;

        if (buttonState) {
          // Toggle the LED corresponding to the button
          digitalWrite(ledPins[i], !digitalRead(ledPins[i]));
          Serial.print("LED ");
          Serial.print(i + 1); // Index + 1 to match button number
          readAndPrintSingle2DArray(i);
          Serial.println(" toggled");
        }
      }
    }
  }
}



void readAndPrintSingle2DArray(int index) {
  int address = index * ARRAY_SIZE_X * ARRAY_SIZE_Y * sizeof(uint16_t);
  for (int i = 0; i < ARRAY_SIZE_X; i++) {
      Serial.print("{");
    for (int j = 0; j < ARRAY_SIZE_Y; j++) {
      uint16_t data;
      readEEPROM(address, data);
      Serial.print(data);
      Serial.print( (j < (ARRAY_SIZE_Y-1)) ? ", " : "" );
      address += sizeof(uint16_t);
    }
    Serial.println( (i < (ARRAY_SIZE_X-1)) ? "}," : "}" );
  }
    Serial.println("ADDR: " + String(address));
}

void readEEPROM(int address, uint16_t &data) {
  Wire.beginTransmission(EEPROM_ADDR);
  Wire.write((int)(address >> 8));   // MSB of address
  Wire.write((int)(address & 0xFF)); // LSB of address
  Wire.endTransmission();
  Wire.requestFrom(EEPROM_ADDR, 2); // Request 2 bytes of data
  data = Wire.read() << 8; // MSB
  data |= Wire.read();     // LSB
}


//  -- END OF FILE --
