const int buttonPins[] = {2, 3, 4, 5, 6, 7};
const int ledPins[] = {8, 9, 10, 11, 12, 13};
bool buttonState[6] = {LOW};
bool anyButtonPressed = false;
int recordedSequence[100][4];  // [button index, start time, duration, delay]
int sequenceLength = 0;
bool isRecording = false;
bool ledState[6] = {LOW}; // Keep track of LED state for each button

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 6; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  anyButtonPressed = false;

  for (int i = 0; i < 6; i++) {
    int currentButtonState = digitalRead(buttonPins[i]);

    if (currentButtonState != buttonState[i]) {
      if (currentButtonState == LOW) {
        if (isRecording) {
          digitalWrite(ledPins[i], HIGH);
          recordButtonPress(i);
        }
        // Turn on the corresponding LED when the button is pressed
        ledState[i] = HIGH;
      } else {
        // Turn off the corresponding LED when the button is released
        ledState[i] = LOW;
      }
      buttonState[i] = currentButtonState;
    }

    // Check if any button is currently pressed
    anyButtonPressed |= currentButtonState == LOW;
  }

  // Update LED states based on button presses
  for (int i = 0; i < 6; i++) {
    digitalWrite(ledPins[i], ledState[i]);
  }

  // Serial communication for recording and playback
  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == 'r') {
      startRecording();
    } else if (command == 's') {
      stopRecording();
    } else if (command == 'p') {
      playRecordedSequence();
    }
  }
}

void recordButtonPress(int buttonIndex) {
  if (sequenceLength < 100) {
    unsigned long currentTime = millis();

    // Record the button index and start time
    recordedSequence[sequenceLength][0] = buttonIndex;
    recordedSequence[sequenceLength][1] = currentTime;

    // Calculate the duration and delay based on the timestamps
    if (sequenceLength > 0) {
      unsigned long prevTime = recordedSequence[sequenceLength - 1][1];
      recordedSequence[sequenceLength - 1][2] = currentTime - prevTime;
      recordedSequence[sequenceLength - 1][3] = 0;  // Initialize delay (may be adjusted)
    }

    sequenceLength++;
  }
}

void startRecording() {
  sequenceLength = 0;
  isRecording = true;
  Serial.println("Recording started");
}

void stopRecording() {
  isRecording = false;
  Serial.println("Recording stopped");
  Serial.println("Recorded Data:");
  for (int i = 0; i < sequenceLength; i++) {
    int buttonIndex = recordedSequence[i][0];
    unsigned long startTime = recordedSequence[i][1];
    unsigned long duration = recordedSequence[i][2];
    unsigned long delayBetweenPresses = recordedSequence[i][3];
    Serial.print("{");
    Serial.print(buttonIndex + 1);
    Serial.print(", ");
    Serial.print(startTime);
    Serial.print(", ");
    Serial.print(duration);
    Serial.print(", ");
    Serial.print(delayBetweenPresses);
    Serial.println("}");
  }
}

void playRecordedSequence() {
  Serial.println("Playback started");
  for (int i = 0; i < sequenceLength; i++) {
    int buttonIndex = recordedSequence[i][0];
    unsigned long duration = recordedSequence[i][2];
    unsigned long delayBetweenPresses = recordedSequence[i][3];

    // Play the tone and turn on the corresponding LED
    digitalWrite(ledPins[buttonIndex], HIGH);
    delay(duration);
    digitalWrite(ledPins[buttonIndex], LOW);

    // Add a delay between tones (adjust as needed)
    delay(delayBetweenPresses);
  }
  Serial.println("Playback finished");
}
