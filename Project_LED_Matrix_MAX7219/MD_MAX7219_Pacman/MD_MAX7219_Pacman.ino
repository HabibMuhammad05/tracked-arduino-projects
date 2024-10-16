/*------------MD_MAX7219_pacman animation---------------*/
/*-------------Source Code by---------------------------*/
/*------Modified & Adapted by Habib.m @Hab_mz-----------*/
/*-----------------------V1.1---------------------------*/
/*------------------------------------------------------*/
/*---------------SPI Wiring Connections-----------------*/
/*--------------CLK_PIN   13  // or SCK-----------------*/
/*--------------DATA_PIN  11  // or MOSI----------------*/
/*---------------CS_PIN   10  // or SS------------------*/
/*------------------------------------------------------*/

#include <MD_MAX72xx.h>

#define MAX_DEVICES 4
#define ANIMATION_DELAY 75
#define MAX_FRAMES 4  

MD_MAX72XX mx = MD_MAX72XX(MD_MAX72XX::FC16_HW, 10, MAX_DEVICES);

uint32_t prevTimeAnim = 0;  // remember the millis() value in animations
int16_t idx;                // display index (column)
uint8_t frame;              // current animation frame
uint8_t deltaFrame;         // the animation frame offset for the next frame

const uint8_t pacman[MAX_FRAMES][18] =
{
  { 0xfe, 0x73, 0xfb, 0x7f, 0xf3, 0x7b, 0xfe, 0x00, 0x00, 0x00, 0x3c, 0x7e, 0x7e, 0xff, 0xe7, 0xc3, 0x81, 0x00 },
  { 0xfe, 0x7b, 0xf3, 0x7f, 0xfb, 0x73, 0xfe, 0x00, 0x00, 0x00, 0x3c, 0x7e, 0xff, 0xff, 0xe7, 0xe7, 0x42, 0x00 },
  { 0xfe, 0x73, 0xfb, 0x7f, 0xf3, 0x7b, 0xfe, 0x00, 0x00, 0x00, 0x3c, 0x7e, 0xff, 0xff, 0xff, 0xe7, 0x66, 0x24 },
  { 0xfe, 0x7b, 0xf3, 0x7f, 0xf3, 0x7b, 0xfe, 0x00, 0x00, 0x00, 0x3c, 0x7e, 0xff, 0xff, 0xff, 0xff, 0x7e, 0x3c },
};
const uint8_t DATA_WIDTH = (sizeof(pacman[0])/sizeof(pacman[0][0]));

void setup(){
  mx.begin();
  Serial.begin(57600);
  Serial.print("[MD_MAX72XX Pacman]");
  prevTimeAnim = millis();
  resetMatrix();
}

void loop(){
  pacmanStart();
}

void resetMatrix(){
  mx.control(MD_MAX72XX::INTENSITY, MAX_INTENSITY/2);
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
  mx.clear();
}

void pacmanStart(){
  static boolean bInit = true;  // initialise the animation

  // Is it time to animate?
  if (millis()-prevTimeAnim < ANIMATION_DELAY)
    return;
  prevTimeAnim = millis();      // starting point for next time

  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);

  // Initialize
  if (bInit)
  {
    mx.clear();
    idx = -DATA_WIDTH;
    frame = 0;
    deltaFrame = 1;
    bInit = false;

    // Lay out the dots
//    for (uint8_t i=0; i<MAX_DEVICES; i++)
//    {
//      mx.setPoint(3, (i*COL_SIZE) + 3, true);
//      mx.setPoint(4, (i*COL_SIZE) + 3, true);
//      mx.setPoint(3, (i*COL_SIZE) + 4, true);
//      mx.setPoint(4, (i*COL_SIZE) + 4, true);
//    }
  }

  // clear old graphic
  for (uint8_t i=0; i<DATA_WIDTH; i++)
    mx.setColumn(idx-DATA_WIDTH+i, 0);
  // move reference column and draw new graphic
  idx++;
  for (uint8_t i=0; i<DATA_WIDTH; i++)
    mx.setColumn(idx-DATA_WIDTH+i, pacman[frame][i]);

  // advance the animation frame
  frame += deltaFrame;
  if (frame == 0 || frame == MAX_FRAMES-1)
    deltaFrame = -deltaFrame;

  // check if we are completed and set initialise for next time around
  bInit = (idx == mx.getColumnCount()+DATA_WIDTH);

  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);

  return;
}
