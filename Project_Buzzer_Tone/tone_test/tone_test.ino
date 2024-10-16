#define NOTE_C 262
#define NOTE_D 294
#define NOTE_E 330
#define NOTE_F 349
#define NOTE_G 392
#define NOTE_A 440

#define ACTIVATED LOW

const int PIEZO = D3;

const int BUTTON_C = D2; // GPIO 4
const int BUTTON_D = D1; // GPIO 5
const int BUTTON_E = D7; // GPIO 13
const int BUTTON_F = D6; // GPIO 12
const int BUTTON_G = D5; // GPIO 14
const int BUTTON_A = RX; // GPIO 3
const int MOD_BUTTON = A0; // Analog pin A0

const float pitchVariations[5] = {1.0, 1.2, 1.4, 1.8, 2}; // Define 5 pitch variations
int currentVariation = 0;

void setup()
{
  Serial.begin(9600);

  pinMode(PIEZO, OUTPUT);

  // Configure buttons with internal pull-up resistors
  pinMode(BUTTON_C, INPUT_PULLUP);
  pinMode(BUTTON_D, INPUT_PULLUP);
  pinMode(BUTTON_E, INPUT_PULLUP);
  pinMode(BUTTON_F, INPUT_PULLUP);
  pinMode(BUTTON_G, INPUT_PULLUP);
  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(MOD_BUTTON, INPUT);

  Serial.println("System Initialized");
}

void loop()
{
  int totalNotes = 0;
  long sumFrequency = 0;
  bool anyButtonPressed = false;

  // Check if the mod button is pressed and cycle through variations
  if (analogRead(MOD_BUTTON) < 200) { // assuming a threshold for button press
    currentVariation = (currentVariation + 1) % 5; // Cycle to next variation
    Serial.print("Switched to variation: ");
    Serial.println(currentVariation);
    delay(300); // Debounce delay for mod button
  }

  // Read and print button states
  Serial.print(digitalRead(BUTTON_C));
  Serial.print(digitalRead(BUTTON_D));
  Serial.print(digitalRead(BUTTON_E));
  Serial.print(digitalRead(BUTTON_F));
  Serial.print(digitalRead(BUTTON_G));
  Serial.println(digitalRead(BUTTON_A));

  if (digitalRead(BUTTON_C) == ACTIVATED) {
    sumFrequency += NOTE_C * pitchVariations[currentVariation];
    totalNotes++;
    Serial.println("Button C pressed");
    anyButtonPressed = true;
  }
  if (digitalRead(BUTTON_D) == ACTIVATED) {
    sumFrequency += NOTE_D * pitchVariations[currentVariation];
    totalNotes++;
    Serial.println("Button D pressed");
    anyButtonPressed = true;
  }
  if (digitalRead(BUTTON_E) == ACTIVATED) {
    sumFrequency += NOTE_E * pitchVariations[currentVariation];
    totalNotes++;
    Serial.println("Button E pressed");
    anyButtonPressed = true;
  }
  if (digitalRead(BUTTON_F) == ACTIVATED) {
    sumFrequency += NOTE_F * pitchVariations[currentVariation];
    totalNotes++;
    Serial.println("Button F pressed");
    anyButtonPressed = true;
  }
  if (digitalRead(BUTTON_G) == ACTIVATED) {
    sumFrequency += NOTE_G * pitchVariations[currentVariation];
    totalNotes++;
    Serial.println("Button G pressed");
    anyButtonPressed = true;
  }
  if (digitalRead(BUTTON_A) == ACTIVATED) {
    sumFrequency += NOTE_A * pitchVariations[currentVariation];
    totalNotes++;
    Serial.println("Button A pressed");
    anyButtonPressed = true;
  }

  if (totalNotes > 0) {
    int averageFrequency = sumFrequency / totalNotes;
    tone(PIEZO, averageFrequency);
    Serial.print("Average Frequency: ");
    Serial.println(averageFrequency);
  } else {
    noTone(PIEZO);
    if (!anyButtonPressed) {
      Serial.println("No button pressed");
    }
  }

  delay(100);  // Small delay to debounce buttons and avoid flooding the serial monitor
}
