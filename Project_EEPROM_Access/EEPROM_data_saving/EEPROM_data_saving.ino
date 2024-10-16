#include <EEPROM.h>
const int ARRAY_SIZE_X = 6; // Assuming your array size is 6x12
const int ARRAY_SIZE_Y = 12;

const uint16_t relWarePlayPause[7][6][12] = {
  {
    {25, 6, 18, 3, 66, 2, 40, 0, 0, 0, 0},
    {62, 7, 44, 2, 45, 0, 0, 0, 0, 0, 0},
    {39, 6, 29, 2, 31, 3, 50, 0, 0, 0, 0},
    {69, 4, 4, 3, 22, 3, 55, 0, 0, 0, 0},
    {33, 6, 14, 10, 22, 3, 8, 2, 62, 0, 0},
    {17, 9, 21, 3, 41, 3, 66, 0, 0, 0, 0}
  },
  {
    {55, 8, 24, 8, 146, 0, 0, 0, 0, 0, 0},
    {70, 8, 25, 9, 129, 0, 0, 0, 0, 0, 0},
    {79, 8, 33, 42, 79, 0, 0, 0, 0, 0, 0},
    {63, 8, 40, 51, 79, 0, 0, 0, 0, 0, 0},
    {48, 8, 39, 9, 137, 0, 0, 0, 0, 0, 0},
    {241, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  },
  {
    {37, 4, 13, 5, 34, 5, 86, 13, 17, 23, 210, 0},
    {73, 6, 74, 46, 49, 23, 47, 17, 35, 6, 86, 0},
    {92, 6, 38, 24, 120, 4, 59, 5, 36, 15, 74, 0},
    {48, 12, 12, 7, 7, 13, 19, 19, 10, 53, 236, 0},
    {32, 10, 25, 11, 27, 74, 35, 23, 56, 13, 148, 0},
    {473, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  },
  {
    {155, 9, 52, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {65, 8, 26, 13, 22, 30, 52, 0, 0, 0, 0, 0},
    {60, 6, 2, 6, 17, 22, 16, 37, 50, 0, 0, 0},
    {41, 33, 16, 23, 103, 0, 0, 0, 0, 0, 0, 0},
    {35, 28, 20, 17, 1, 3, 112, 0, 0, 0, 0, 0},
    {216, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  },
  {
    {48, 49, 93, 14, 3, 16, 48, 2, 3, 1, 101, 0},
    {68, 28, 39, 34, 142, 3, 66, 0, 0, 0, 0, 0},
    {81, 15, 30, 26, 1, 17, 119, 2, 3, 1, 80, 0},
    {65, 31, 21, 52, 84, 2, 3, 2, 2, 3, 115, 0},
    {48, 49, 12, 62, 61, 1, 3, 2, 2, 4, 130, 0},
    {380, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  },
  {
    {34, 7, 21, 7, 21, 7, 23, 8, 47, 0, 0, 0},
    {31, 12, 13, 17, 10, 15, 12, 20, 45, 0, 0, 0},
    {175, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {31, 6, 3, 3, 13, 17, 10, 16, 11, 20, 45, 0},
    {33, 9, 19, 8, 21, 7, 21, 11, 46, 0, 0, 0},
    {175, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  },
  {
    {46, 3, 3, 3, 3, 3, 3, 3, 4, 2, 62, 0},
    {135, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {89, 3, 43, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {135, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {44, 2, 4, 2, 4, 2, 4, 2, 4, 3, 61, 0},
    {135, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  }
};// count, 0=play, 1=pause
void setup() {
  Serial.begin(9600);
  
  // Write the 3D array to EEPROM
//  writeArrayToEEPROM();
//  delay(1000);
  readAndPrintSingle2DArray(6);
}

void loop() {
  // Nothing to do here in this example
}

void writeArrayToEEPROM() {
  int address = 0;

  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < ARRAY_SIZE_X; j++) {
      for (int k = 0; k < ARRAY_SIZE_Y; k++) {
        EEPROM.put(address, relWarePlayPause[i][j][k]); // Write each element to EEPROM
        address += sizeof(uint16_t); // Move to the next EEPROM address
      }
    }
  }

  Serial.println("Array stored in EEPROM successfully!");
}

void readAndPrintSingle2DArray(int index) {
  int address = index * ARRAY_SIZE_X * ARRAY_SIZE_Y * sizeof(uint16_t);

  for (int i = 0; i < ARRAY_SIZE_X; i++) {
      Serial.print("{");
    for (int j = 0; j < ARRAY_SIZE_Y; j++) {
      uint16_t data;
      EEPROM.get(address, data); // Read data from EEPROM
      Serial.print(data);
      Serial.print( (j < (ARRAY_SIZE_Y-1)) ? ", " : "" );
      address += sizeof(uint16_t); // Move to the next EEPROM address
    }
    Serial.println("}");
  }
}
