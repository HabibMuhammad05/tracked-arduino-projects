#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>    

LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD 16x2
Servo portalServo;

// Deklarasi Pin
uint8_t binPin[3] = {2, 3, 4};  
uint8_t portalPin = 5;          
uint8_t LED_GREEN = 6;          
uint8_t LED_RED = 7;            
uint8_t SENSOR_IN = 8;          
uint8_t SENSOR_OUT = 9;         

uint8_t jumlahSlot = 4;         
uint8_t senSlot[4] = {10, 11, 12, 13}; 
bool slotStatus[4];             

const int IdValid[] = {0b000, 0b001, 0b010, 0b011, 0b100, 0b101, 0b110}; 
String namaId[] = {"user0", "user1", "user2", "user3", "user4", "user5", "user6"}; 

unsigned long portalOpenTime = 0;
const unsigned long portalDelay = 5000;
uint8_t globalStat;

void setup() {
    Serial.begin(9600);

    for (int i = 0; i < 3; i++) {
        pinMode(binPin[i], INPUT_PULLUP);
    }

    for (int i = 0; i < jumlahSlot; i++) {
        pinMode(senSlot[i], INPUT_PULLUP);
    }

    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_RED, OUTPUT);
    
    pinMode(SENSOR_IN, INPUT_PULLUP);
    pinMode(SENSOR_OUT, INPUT_PULLUP);
    
    portalServo.attach(portalPin);
    portalServo.write(0);
    
    lcd.begin();
    lcd.backlight();
    
    updateSlotStatus();
//    updateStatus();
}

void loop() {
  if (!digitalRead(SENSOR_IN) == HIGH) { globalStat = 1; }
  else if (!digitalRead(SENSOR_OUT) == HIGH) { globalStat = 2; }
  else{ globalStat = 0; }
  switch(globalStat){
    case 1: modeMasuk(); break;
    case 2 : modeKeluar(); break;
    default : modeStandby(); break;
  }
  
    if (portalOpenTime != 0 && (millis() - portalOpenTime >= portalDelay)) {
        portalState(false);
    }

    updateSlotStatus();
    delay(1000); 
}

void modeMasuk(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Selamat Datang!");
  lcd.setCursor(0, 1);
  lcd.print("Masukkan ID");
  Serial.println("Proses masuk dimulai");

  delay(3000); // Waktu untuk memasukkan ID
  int memberID = readBinaryInput(); 
  if (isMemberValid(memberID)) {
    int availableSlot = findAvailableSlot();
    if (availableSlot != -1) {
       portalState(true);
       slotStatus[availableSlot] = true;
       updateStatus();
       lcd.setCursor(0, 1);
       lcd.print("Welcome, ");
       lcd.print(namaId[memberID]);
       Serial.println("Member masuk");
    } else {
       lcd.setCursor(0, 1);
       lcd.print("Parking Full!");
       Serial.println("Parking full");
    }
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Access Denied");
    Serial.println("Access Denied");
  }
  delay(2000); 
}

void modeKeluar(){
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Silakan keluar");
        lcd.setCursor(0, 1);
        lcd.print("Masukkan ID");
        Serial.println("Proses keluar dimulai");

        delay(3000); // Waktu untuk memasukkan ID
        int memberID = readBinaryInput(); 

        if (isMemberValid(memberID)) {
            int occupiedSlot = findOccupiedSlot();
            if (occupiedSlot != -1) {
                slotStatus[occupiedSlot] = false;
                updateStatus();
                portalState(false);
                lcd.setCursor(0, 1);
                lcd.print("Goodbye, ");
                lcd.print(namaId[memberID]);
                Serial.println("Member keluar");
            } else {
                lcd.setCursor(0, 1);
                lcd.print("Slot Kosong");
                Serial.println("Tidak ada slot terisi");
            }
        } else {
            lcd.setCursor(0, 1);
            lcd.print("Access Denied");
            Serial.println("Access Denied");
        }
        delay(2000); 
}

void modeStandby(){
          lcd.setCursor(0, 0);
        lcd.print("PARKIR EKSKLUSIF");
        lcd.setCursor(1, 1);
        lcd.print("SLOT: ");
        lcd.print(jumlahSlot - countOccupiedSlots());
        lcd.print(" : ");
        for (int i = 0; i < jumlahSlot; i++) {
            lcd.print(slotStatus[i] ? "X" : "O");
        }
}

int readBinaryInput() {
    int b0 = digitalRead(binPin[0]);
    int b1 = digitalRead(binPin[1]);
    int b2 = digitalRead(binPin[2]);
    
    int binaryValue = (b2 << 2) | (b1 << 1) | b0;
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
    if (stat) {
        portalServo.write(90);
        portalOpenTime = millis();
    } else {
        portalServo.write(0);
        portalOpenTime = 0;
    }
}

void updateStatus() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SISA SLOT: ");
    for (int i = 0; i < jumlahSlot; i++) {
        lcd.print(slotStatus[i] ? "X" : "O");
    }
    lcd.setCursor(0, 1);
    lcd.print(" : ");
    lcd.print(jumlahSlot - countOccupiedSlots());
}

void updateSlotStatus() {
    for (int i = 0; i < jumlahSlot; i++) {
        slotStatus[i] = digitalRead(senSlot[i]) == LOW;
    }
}

int countOccupiedSlots() {
    int occupied = 0;
    for (int i = 0; i < jumlahSlot; i++) {
        if (slotStatus[i]) occupied++;
    }
    return occupied;
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
