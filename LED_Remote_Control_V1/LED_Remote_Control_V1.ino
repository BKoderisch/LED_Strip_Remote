//author: Benjamin Koderisch
//version: 1.0, 4.10.16

#include "RGBdriver.h"
#include <IRremote.h>

int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;

#define CLK 2//pins definitions for the driver        
#define DIO 3

int btnPin = 7;
RGBdriver Driver(CLK,DIO);
int mFlag = 1; //flag for the current modus | bsp. 1, 2, 3...
int sFlag = 0; //flag for the current status | bsp. 1 for off
int btn;

void setup(){ 
  pinMode(btnPin, INPUT);
  irrecv.enableIRIn();
}  

void loop(){ 
  Driver.begin();
  Serial.begin(9200);
  
  
  if(irrecv.decode(&results)){
    Serial.println(btn);
    btn = btnPressed(results.value);
    if(mFlag != btn){
      mFlag = btn;
      newMFlag();
    }
    irrecv.resume();
  }


  
}

void newMFlag(){
  switch(mFlag){
    case 1:
      Driver.SetColor(255,255,255);
      break;
    case 2:
      Driver.SetColor(0, 255, 255);
      break;
    case 3:
      Driver.SetColor(255, 0, 255);
      break;
    case 4:
      Driver.SetColor(255, 255, 0);
      break;
    case 5:
      Driver.SetColor(0, 0, 255);
      break;
    case 6:
      Driver.SetColor(0, 255, 0);
      break;
    case 7:
      Driver.SetColor(255, 0, 0);
      break;
    case 8:
      Driver.SetColor(0, 255, 0);
      break;
    case 9:
      Driver.SetColor(0, 0, 0);
      break;
  }
}

int btnPressed(int value){
  switch(value){
    case 0xff6897:
      return 1;
      break;
    case 0xff9867:
      return 2;
      break;
    case 0xffb04f:
      return 3;
      break;
    case 0xff30cf:
      return 4;
      break;
    case 0xff18e7:
      return 5;
      break;
    case 0xff7a85:
      return 6;
      break;
    case 0xff10ef:
      return 7;
      break;
    case 0xff38c7:
      return 8;
      break;
    case 0xff5aa5:
      return 9;
      break;
    case 0xff42bd:
      // *
      return 15;
      break;
    case 0xff4ab5:
      // 0
      return 16;
      break;
    case 0xff52ad:
      // #
      return 17;
      break;
    case 0xff629d:
      // up
      return 10;
      break;
    case 0xff22dd:
      // left
      return 11;
      break;
    case 0xff02fd:
      // ok
      return 12;
      break;
    case 0xffc23d:
      // right
      return 13;
      break;
    case 0xffa857:
      // down
      return 14;
      break;
  }
}

