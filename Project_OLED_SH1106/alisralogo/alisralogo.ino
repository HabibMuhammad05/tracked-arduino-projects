#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h> // library requires for IIC communication

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

const unsigned char epd_bitmap_alisralogo__1_ [] U8X8_PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0x00, 0x00, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 
  0xf8, 0x00, 0x0c, 0xfc, 0x7f, 0xe0, 0x00, 0x00, 0xf0, 0x03, 0x70, 0x00, 0x00, 0xf0, 0x00, 0x0e, 
  0xfc, 0x7f, 0x60, 0x00, 0x06, 0xe0, 0x03, 0x70, 0x00, 0x00, 0xe0, 0x00, 0x1e, 0xfe, 0xff, 0x70, 
  0x00, 0x07, 0xe0, 0x03, 0x38, 0x00, 0x00, 0xf0, 0x00, 0x0f, 0xff, 0x7f, 0x38, 0x1c, 0x87, 0xe1, 
  0x03, 0x3c, 0x00, 0x00, 0x78, 0x00, 0x0f, 0xff, 0x7f, 0x38, 0xfc, 0x83, 0xf0, 0x01, 0x0c, 0x00, 
  0x00, 0x38, 0x84, 0x07, 0xff, 0x70, 0x38, 0x80, 0x03, 0xf0, 0x21, 0x04, 0x00, 0x00, 0x3c, 0x80, 
  0x87, 0x7f, 0x30, 0x7c, 0x80, 0x01, 0xf8, 0x00, 0x06, 0x00, 0x00, 0x1c, 0x80, 0x87, 0x7f, 0x30, 
  0xfc, 0x83, 0x01, 0x7c, 0x00, 0x06, 0x00, 0x00, 0x0f, 0x80, 0xc3, 0xf1, 0x1f, 0x1e, 0xc3, 0x71, 
  0x78, 0x00, 0x1e, 0x00, 0x80, 0x0f, 0x83, 0x03, 0xf0, 0x1f, 0x0e, 0xc2, 0x20, 0x38, 0x1c, 0x0e, 
  0x00, 0xc0, 0x87, 0x83, 0x01, 0xf8, 0x0f, 0x0c, 0x60, 0x20, 0x18, 0x1c, 0x0c, 0x00, 0xf0, 0x83, 
  0x83, 0x00, 0xfc, 0x07, 0x06, 0x20, 0x10, 0x0c, 0x0e, 0x06, 0x00, 0xf8, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd7, 0x26, 0xfe, 0xff, 0xff, 0xff, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xcf, 
  0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x2d, 0xfe, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x1f, 0x06, 0x00, 0x41, 0x08, 0x03, 0x00, 
  0x01, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x9e, 0xef, 0x6b, 0x5f, 0x28, 0x5f, 0xfb, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0xc0, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 
  0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


void setup(void) {

  u8g2.begin(); // start the u8g2 library
  
  u8g2.clearBuffer();
  u8g2.setFontMode(1);
  u8g2.setBitmapMode(1);

  u8g2.drawXBMP(16, 15, 100, 40, epd_bitmap_alisralogo__1_);
  
  u8g2.sendBuffer();
}

void loop(void) {

}