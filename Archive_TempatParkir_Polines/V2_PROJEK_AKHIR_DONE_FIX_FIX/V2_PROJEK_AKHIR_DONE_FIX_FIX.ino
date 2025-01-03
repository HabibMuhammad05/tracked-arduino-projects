/*-------------------------------------------------------------------------------*/
/*---Sistem Pendataan Parkir dengan identitas Kartu Biner Berbasis Arduino Uno---*/
/*-------------------Source Code by Kelompok 3 Mikrokontroler--------------------*/
/*-----------------------Modified & Adapted by Habib M.Z.------------------------*/
/*------------------------------------V2.2---------------------------------------*/
/*-------------------------------------------------------------------------------*/

//-----------------------Deklarasi Library Layar LCD I2C-------------------------//
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); 

//---------------------------Deklarasi Library Servo-----------------------------//
#include <Servo.h>
Servo servoMasuk;
Servo servoKeluar;
uint8_t portalIn = 10;
uint8_t portalOut = 9;
unsigned long portalMillis = 0;

//------------------------Deklarasi Pin LED dan Sensor---------------------------//
uint8_t redLed = 8;
uint8_t greenLed = 7;
uint8_t sensorIn = 11;
uint8_t sensorOut = 12;

//--------------------Deklarasi Variabel dan pin Input Biner---------------------//
uint8_t binPin[4] = {2, 3, 4, 5};
uint8_t cardPin = 6;

uint8_t carCount = 0;
const uint8_t IdValid[7] = {0b0001, 0b0010, 0b0100, 0b0111, 0b1000, 0b1100, 0b1111};
String namaId[7] =         {"Udin", "Agus", "Miftah", "Tama", "Onana", "Asep", "Wahyu"};

//===============================================================================//
//=================================Void Setup()==================================//
void setup() {
  //----------------------Setup Serial Monitor dan Layar LCD-----------------------//
//  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();

  //----------------------Setup pin sebagai Input atau Output----------------------//
  for (int i = 0; i < 4; i++) {
    pinMode(binPin[i], INPUT_PULLUP);
  }
  pinMode(cardPin, INPUT_PULLUP);
  pinMode(sensorIn, INPUT_PULLUP);
  pinMode(sensorOut, INPUT_PULLUP);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);

  //---------------------Setup Pin Servo dan Posisi Awal Servo---------------------//
  servoMasuk.attach(portalIn);
  servoMasuk.write(0);
  servoKeluar.attach(portalOut);
  servoKeluar.write(0);
}

//===============================================================================//
//=================================Void Loop()===================================//
void loop() {
  //-----------------Pengecekan Keadaan Kendaraan dan Tempat Parkir----------------//
  if (!digitalRead(sensorIn) && (carCount < 7)) {
    modeMasuk();
  }
  else if (!digitalRead(sensorOut) && (carCount > 0)) {
    modeKeluar();
  }
  else {
    modeStandby();
  }

  //-------------------Millis Untuk Penutupan Portal Masuk/Keluar------------------//
  if ((portalMillis != 0) && (millis() - portalMillis >= 5000)) {
    bukaPortal(0);
  }
  delay(50);
}

//===============================================================================//
//======================Fungsi untuk Handle kendaraan Masuk======================//
void modeMasuk() {
  uint8_t memberBin, memberIndex;
  bool statMember = false;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Selamat Datang!!");
  lcd.setCursor(2, 1);
  lcd.print("Masukkan ID");
//  Serial.print("Kendaraan Masuk: ");

  unsigned long startTime = millis();
  while (digitalRead(cardPin)) {
    if ((millis() - startTime > 3000) && (digitalRead(sensorIn))) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Maaf ID Timeout!");
      lcd.setCursor(2, 1);
      lcd.print("Mohon Ulang");
      delay(2000);
      return;
    }
  }
  delay(500);
  memberBin = bacaBiner();

  for (int i = 0; i < 8; i++) {
    if (memberBin == IdValid[i]) {
      statMember = true;
      memberIndex = i;
      break;
    }
  }

  if (statMember) {
    carCount++;
    bukaPortal(1);
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("ID Dikenali!");
    lcd.setCursor(0, 1);
    lcd.print("Halo ");
    lcd.print(namaId[memberIndex]);
//    Serial.println("Member telah masuk");
  } else {
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Mohon Maaf");
    lcd.setCursor(0, 1);
    lcd.print("ID Tidak Dikenal");
//    Serial.println("Ditolak - ID tidak Dikenal");
  }
  while (!digitalRead(cardPin) || !digitalRead(sensorIn));
//  delay(1000);
}

//===============================================================================//
//=====================Fungsi untuk Handle kendaraan Keluar======================//
void modeKeluar() {
  uint8_t memberBin, memberIndex;
  bool statMember;

  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Silakan keluar");
  lcd.setCursor(2, 1);
  lcd.print("masukkan ID ");
//  Serial.print("Kendaraan Keluar: ");

  unsigned long startTime = millis();
  while (digitalRead(cardPin)) {
    if ((millis() - startTime > 3000) && digitalRead(sensorOut)) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Maaf ID Timeout!");
      lcd.setCursor(2, 1);
      lcd.print("Mohon Ulang");
      delay(2000);
      return;
    }
  }
  delay(500);
  memberBin = bacaBiner();

  for (int i = 0; i < 8; i++) {
    if (memberBin == IdValid[i]) {
      statMember = true;
      memberIndex = i;
      break;
    }
  }

  if (statMember) {
    carCount--;
    bukaPortal(2);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("ID Dikenali!");
    lcd.setCursor(0, 1);
    lcd.print("bye, ");
    lcd.print(namaId[memberIndex]);
//    Serial.println("Member Telah keluar");
  } else {
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Mohon Maaf");
    lcd.setCursor(0, 1);
    lcd.print("ID Tidak Dikenal");
//    Serial.println("Ditolak - ID tidak Dikenal");
  }
  while ((digitalRead(cardPin) == LOW) || (digitalRead(sensorOut) == LOW));
//  delay(1000);
}

//===============================================================================//
//======================Fungsi untuk Handle Keadaan Standby======================//
unsigned long stateMillis = 0;
bool state;
void modeStandby() {
  lcd.setCursor(0, 0);
  lcd.print("PARKIR EKSKLUSIF");

  if (millis() - stateMillis >= 1000) {
    stateMillis = millis();
    state = !state;
  }

  if (state) {
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    
    lcd.setCursor(0, 1);
    lcd.print("SLOT TERSEDIA: ");
    lcd.print(7 - carCount);
  }
  else {
    
    if (carCount < 7) {
      digitalWrite(redLed, LOW);
      digitalWrite(greenLed, HIGH);
    
      lcd.setCursor(0, 1);
      lcd.print(" Silakan Masuk! ");
    }
    else {
      digitalWrite(redLed, HIGH);
      digitalWrite(greenLed, LOW);
      
      lcd.setCursor(0, 1);
      lcd.print("Maaf Slot Penuh!");
    }
  }
}

//===============================================================================//
//==============Fungsi untuk Mengatur keadaan Portal Masuk/Keluar================//
void bukaPortal(uint8_t lok) {
  if (lok == 1) {
//    Serial.println("Portal masuk Terbuka");
    servoMasuk.write(90);
    portalMillis = millis();
  }
  else if (lok == 2) {
//    Serial.println("Portal keluar Terbuka");
    servoKeluar.write(90);
    portalMillis = millis();
  }
  else {
//    Serial.println("Portal tertutup");
    servoMasuk.write(0);
    servoKeluar.write(0);
    portalMillis = 0;
  }
}

//===============================================================================//
//=================Fungsi untuk Membaca nilai Biner Pengguna=====================//
int bacaBiner() {
  bool b0 = digitalRead(binPin[0]);
  bool b1 = digitalRead(binPin[1]);
  bool b2 = digitalRead(binPin[2]);
  bool b3 = digitalRead(binPin[3]);

  uint8_t nilaiBin = (b3 << 3) | (b2 << 2) | (b1 << 1) | b0;
//  Serial.print(b3); Serial.print(b2); Serial.print(b1); Serial.println(b0);

  return nilaiBin;
}
