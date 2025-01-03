#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

#include <Servo.h>    
Servo portalServo;

uint8_t binPin[4] = {2, 3, 4, 5};
uint8_t portalPin = 6;        
uint8_t LED_GREEN = 7;          
uint8_t LED_RED = 8;         

uint8_t SENSOR_IN = 9;    
uint8_t SENSOR_OUT = 10;     

uint8_t jumlahSlot = 3;    
uint8_t senSlot[3] = {11, 12, 13};
bool slotStatus[3];  

const int IdValid[] = {0b0001, 0b0010, 0b0011, 0b0100, 0b0101}; 
String namaId[] = {"user1", "user2", "user3", "user4", "user5"}; 

unsigned long portalOpenTime = 0;
const unsigned long portalDelay = 5000;

void setup() {
    Serial.begin(9600);
    
    for(int i = 0; i < 4; i++){
      pinMode(binPin[i], INPUT_PULLUP);
    }
    for(int i = 0; i < 3; i++){
      pinMode(senSlot[i], INPUT_PULLUP);
    }
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_RED, OUTPUT);
    pinMode(SENSOR_IN, INPUT);
    pinMode(SENSOR_OUT, INPUT);
    
    portalServo.attach(portalPin);
    portalServo.write(0); 
    
    lcd.begin();
    lcd.backlight();
    
    updateSlotStatus();
    updateStatus();
}

void loop() {
    int memberID = readBinaryInput();

    if (digitalRead(SENSOR_IN) == HIGH) {
        if (isMemberValid(memberID)) {
            int availableSlot = findAvailableSlot();
            if (availableSlot != -1) {
                portalState(true);
                slotStatus[availableSlot] = true;
                updateStatus();
                lcd.setCursor(0, 2);
                lcd.print("Welcome, Member: ");
                lcd.print(memberID, BIN);
                Serial.println("Member masuk");
            } else {
                lcd.setCursor(0, 2);
                lcd.print("Parking Full!        ");
                Serial.println("Parking full");
            }
        } else {
            lcd.setCursor(0, 2);
            lcd.print("Access Denied        ");
            Serial.println("Access Denied");
        }
    }

    if (digitalRead(SENSOR_OUT) == HIGH) {
        int occupiedSlot = findOccupiedSlot();
        if (occupiedSlot != -1) {
            slotStatus[occupiedSlot] = false; 
            updateStatus();
            portalState(false);
            lcd.setCursor(0, 2);
            lcd.print("Goodbye, Member      ");
            Serial.println("Member keluar");
        }
    }

    if (portalOpenTime != 0 && (millis() - portalOpenTime >= portalDelay)) {
        portalState(false);
    }

    updateSlotStatus();
    
    delay(1000); 
}

int readBinaryInput() {
    int b0 = digitalRead(binPin[0]);
    int b1 = digitalRead(binPin[1]);
    int b2 = digitalRead(binPin[2]);
    int b3 = digitalRead(binPin[3]);
    
    int binaryValue = (b3 << 3) | (b2 << 2) | (b1 << 1) | b0; 
    Serial.print("Binary Value: ");
    Serial.println(binaryValue, BIN);
    
    return binaryValue;
}

bool isMemberValid(int memberID) {
    for (int i = 0; i < sizeof(IdValid) / sizeof(IdValid[0]); i++) {
        if (memberID == IdValid[i]) {
            return true;
        }
    }
    return false;
}

void portalState(bool stat) {
  if (stat){
    portalServo.write(90); 
    portalOpenTime = millis(); 
  }else{
    portalServo.write(0); 
    portalOpenTime = 0; 
  }
}


void updateStatus() {
    int occupiedSlots = 0;
    for (int i = 0; i < jumlahSlot; i++) {
        if (slotStatus[i]) occupiedSlots++;
    }
    
    lcd.clear();
    lcd.setCursor(0, 0); 
    lcd.print("Occupied: ");
    lcd.print(occupiedSlots);
    lcd.print(" Slot ");
    lcd.setCursor(0, 1); 
    lcd.print("Available: ");
    lcd.print(jumlahSlot - occupiedSlots);
    
    if (occupiedSlots < jumlahSlot) {
        digitalWrite(LED_GREEN, HIGH);
        digitalWrite(LED_RED, LOW);
    } else {
        digitalWrite(LED_GREEN, LOW);
        digitalWrite(LED_RED, HIGH);
    }
}

void updateSlotStatus() {
    slotStatus[0] = digitalRead(senSlot[0]) == HIGH;
    slotStatus[1] = digitalRead(senSlot[1]) == HIGH;
    slotStatus[2] = digitalRead(senSlot[2]) == HIGH;
}

int findAvailableSlot() {
    for (int i = 0; i < jumlahSlot; i++) {
        if (!slotStatus[i]) return i;
    }
    return -1; 
}

int findOccupiedSlot() {
    for (int i = 0; i < jumlahSlot; i++) {
        if (slotStatus[i]) return i;
    }
    return -1; 
}
