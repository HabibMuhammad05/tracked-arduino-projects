#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>    

LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD 16x2
Servo portalServo;

// Deklarasi Pin
uint8_t binPin[4] = {2, 3, 4, 5};  
uint8_t ID_DETECT_PIN = 6;        
uint8_t LED_GREEN = 7;            
uint8_t LED_RED = 8;              
uint8_t SENSOR_IN = 11;           
uint8_t SENSOR_OUT = 12;  
        
uint8_t PORTAL_IN = 9;   
uint8_t PORTAL_OUT = 10;             

int carCount = 0;                 
const int maxSlot = 4;            

const int IdValid[] = {0b0000, 0b0001, 0b0010, 0b0011, 0b0100, 0b0101, 0b1011}; 
String namaId[] = {"user0", "user1", "user2", "user3", "user4", "user5", "user6"}; 

unsigned long portalOpenTime = 0;
const unsigned long portalDelay = 5000;
unsigned long idCheckTimeout = 10000;
uint8_t globalStat;

void setup() {
    Serial.begin(9600);
    Serial.println("Setup Start...");

    for (int i = 0; i < 4; i++) {
        pinMode(binPin[i], INPUT_PULLUP);
    }

    pinMode(ID_DETECT_PIN, INPUT_PULLUP);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_RED, OUTPUT);
    
    pinMode(SENSOR_IN, INPUT_PULLUP);
    pinMode(SENSOR_OUT, INPUT_PULLUP);
    
    portalServo.attach(PORTAL_IN);
    portalServo.write(0);
    
    lcd.begin();
    lcd.backlight();
//    updateStatus();
}

void loop() {
    
  if (digitalRead(SENSOR_IN) == LOW) { modeMasuk(); }
  else if (digitalRead(SENSOR_OUT) == LOW) { modeKeluar(); }
  else{ modeStandby(); }
    
    if (portalOpenTime != 0 && (millis() - portalOpenTime >= portalDelay)) {
        portalState(false);
    }
    delay(100); 
}

void modeMasuk() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Selamat Datang!");
    lcd.setCursor(0, 1);
    lcd.print("Masukkan ID Card");
    Serial.println("Proses masuk dimulai");

    unsigned long startTime = millis();
    while (digitalRead(ID_DETECT_PIN) == HIGH) {
        if (millis() - startTime > idCheckTimeout) {
            lcd.clear();
            lcd.print("ID Timeout");
            delay(2000);
            return;
        }
    }


    int memberID = readBinaryInput();
    int index = getMemberIndex(memberID);
    if (isMemberValid(memberID)) {
        if (carCount <= maxSlot) {
            carCount++;
            portalState(true);
//            updateStatus();
            lcd.clear();
            lcd.setCursor(1, 0);
            lcd.print("ID Dikenali!");
            lcd.setCursor(0, 1);
            lcd.print("Welcome, ");
            lcd.print(namaId[index]);
            Serial.println("Member masuk");
        } else {
            lcd.clear();
            lcd.setCursor(2, 0);
            lcd.print("Mohon Maaf");
            lcd.setCursor(2, 1);
            lcd.print("Slot Penuh");
            Serial.println("Parkir Penuh");
        }
    } else {
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("Mohon Maaf");
        lcd.setCursor(0, 1);
        lcd.print("ID Tidak Dikenal");
        Serial.println("Akses Ditolak");
    }
    delay(5000);
}

void modeKeluar() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Silakan keluar");
    lcd.setCursor(1, 1);
    lcd.print("masukkan ID");
    Serial.println("Proses keluar dimulai");

    unsigned long startTime = millis();
    while (digitalRead(ID_DETECT_PIN) == HIGH) {
        if (millis() - startTime > idCheckTimeout) {
            lcd.clear();
            lcd.print("ID Timeout");
            delay(2000);
            return;
        }
    }

    int memberID = readBinaryInput();
    int index = getMemberIndex(memberID);
    if (isMemberValid(memberID)) {
        if (carCount > 0) {
            carCount--;
            portalState(false);
//            updateStatus();
            lcd.clear();
            lcd.setCursor(1, 0);
            lcd.print("ID Dikenali!");
            lcd.setCursor(0, 1);
            lcd.print("Goodbye, ");
            lcd.print(namaId[index]);
            Serial.println("Member keluar");
        } else {
            lcd.clear();
            lcd.print("Tidak Ada Mobil");
            Serial.println("Tidak ada mobil");
        }
    } else {
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("Mohon Maaf");
        lcd.setCursor(0, 1);
        lcd.print("ID Tidak Dikenal");
        Serial.println("Akses Ditolak");
    }
    delay(2000);
}

void modeStandby() {
    lcd.setCursor(0, 0);
    lcd.print("PARKIR EKSKLUSIF");
    lcd.setCursor(0, 1);
    lcd.print("SLOT TERSEDIA: ");
    lcd.print(maxSlot - carCount);
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
    if (stat) {
        portalServo.write(90);
        portalOpenTime = millis();
    } else {
        portalServo.write(0);
        portalOpenTime = 0;
    }
}

int getMemberIndex(int binaryID) {
    for (int i = 0; i < sizeof(IdValid) / sizeof(IdValid[0]); i++) {
        if (IdValid[i] == binaryID) {
            return i; // Return the index of the matching ID
        }
    }
    return -1; // Return -1 if ID is not valid
}

//void updateStatus() {
//    lcd.clear();
//    lcd.setCursor(0, 0);
//    lcd.print("SISA SLOT: ");
//    lcd.print(maxSlot - carCount);
//}
