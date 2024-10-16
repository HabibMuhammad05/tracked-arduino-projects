/*------------MD_MAX7219_RunningText_V2-----------------*/
/*-------------Source Code by---------------------------*/
/*------Modified & Adapted by Habib.m @Hab_mz-----------*/
/*-----------------------V1.1---------------------------*/

#include <MD_Parola.h>
#include <MD_MAX72xx.h>

#define MAX_DEVICES 4

MD_Parola P = MD_Parola(MD_MAX72XX::FC16_HW, 10, MAX_DEVICES);
MD_MAX72XX mx = MD_MAX72XX(MD_MAX72XX::FC16_HW, 10, MAX_DEVICES);


void setup(){
  P.begin();
  mx.begin();
}

void loop(){
  P.print("Hello!");
  delay(500);
  CloseTransition();
}




void CloseTransition(){
#define SpiralSpeed  35
#define WipeSpeed 50
  int  rmin = 0, rmax = ROW_SIZE-1;
  int  cmin = 0, cmax = (COL_SIZE*MAX_DEVICES)-1;
  while ((rmax > rmin) && (cmax > cmin)){
    // do row
    for (int i=cmin; i<=cmax; i++){
      mx.setPoint(rmin, i, true);
      delay(SpiralSpeed/MAX_DEVICES);}
    rmin++;
    // do column
    for (uint8_t i=rmin; i<=rmax; i++){
      mx.setPoint(i, cmax, true);
      delay(SpiralSpeed/MAX_DEVICES);}
    cmax--;
    // do row
    for (int i=cmax; i>=cmin; i--){
      mx.setPoint(rmax, i, true);
      delay(SpiralSpeed/MAX_DEVICES);}
    rmax--;
    // do column
    for (uint8_t i=rmax; i>=rmin; i--){
      mx.setPoint(i, cmin, true);
      delay(SpiralSpeed/MAX_DEVICES);}
    cmin++;
  }
  const uint16_t maxCol = MAX_DEVICES*ROW_SIZE;
  const uint8_t stripeWidth = 10;
  for (uint16_t col=0; col<maxCol + ROW_SIZE + stripeWidth; col++){
    for (uint8_t row=0; row < ROW_SIZE; row++){
      mx.setPoint(row, col-row, true);
      mx.setPoint(row, col-row - stripeWidth, false);}
    delay(WipeSpeed);}
}
