// Define the pins for the shift registers
#define DATA_PIN 10
#define LATCH_PIN 11
#define CLOCK_PIN 12

// Define the segments for common anode and common cathode displays

void setup() {
  // Set the shift register pins as outputs
  Serial.begin(9600);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
}

void loop() {
  for (int i = 0; i <= 99; i++) {
    Serial.println(i);
    displayNumber(i);
    delay(500); // Display for 1 second
  }
}

void displayNumber(int number) {
  
  const byte commonAnodeSegments[] = {
    B10000001, // 0
    B11101101, // 1
    B01000011, // 2
    B01001001, // 3
    B00101101, // 4
    B00011001, // 5
    B00010001, // 6
    B11001101, // 7
    B00000001, // 8
    B00001001  // 9
  };
  const byte commonCathodeSegments[] = {
  B01111110, // 0
  B00010010, // 1
  B10111100, // 2
  B10110110, // 3
  B11010010, // 4
  B11100110, // 5
  B11101110, // 6
  B00110010, // 7
  B11111110, // 8
  B11110110  // 9
};
  
  int tens = number / 10;
  int units = number % 10;
  
  shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, commonCathodeSegments[units]);
  shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, commonAnodeSegments[tens]);
  
  digitalWrite(LATCH_PIN, HIGH);
  digitalWrite(LATCH_PIN, LOW);
}
                                                                                                                                                                                                                                                                                                  
