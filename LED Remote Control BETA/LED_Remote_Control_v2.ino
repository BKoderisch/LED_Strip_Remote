//author: Benjamin Koderisch
//version: 0.3.1 beta, 26.10.16

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
int vipFlag; // when the sFlag is 0 and a button is pressed it switches 
             // to Flag 1 and go into the if loop 

void setup(){ 
  pinMode(btnPin, INPUT);
  irrecv.enableIRIn();
}  

void loop(){ 
  Driver.begin();
  Serial.begin(9200);
  switch(sFlag){
    case 0:
      case0();
      break;
    case 1:
      case1();
      break;
    case 2:
      case2();
      break;
  }
}


void newMFlag(){
  switch(mFlag){
    // off
    case 0:
      setColor(0,0,0);
      break;
    case 1:
      setColor(255,255,255);
      break;
    case 2:
      setColor(0, 255, 255);
      break;
    case 3:
      setColor(255, 0, 255);
      break;
    case 4:
      setColor(255, 255, 0);
      break;
    case 5:
      setColor(0, 0, 255);
      break;
    case 6:
      setColor(0, 255, 0);
      break;
    case 7:
      setColor(255, 0, 0);
      break;
    case 8:
      setColor(0, 255, 0);
      break;
    case 9:
      setColor(0, 0, 0);
      break;
    
  }
}

// sFlag = 0
void case0();
  setColor(0,0,0);
  if(irrecv.decode(&results)){
    sFlag = 1
    btn = btnPressed(results.value);
    vipFlag = 1;
  }

// sFlag = 1
void case1(){
  if(irrecv.decode(&results) || vipFlag == 1){
    Serial.println(btn);
    if(vipFlag != 1){
      btn = btnPressed(results.value);
    }
    if(mFlag != btn || btn < 10){
      mFlag = btn;
    }
    else{
      
      // right
      if(btn == 13){
        mFlag = mFlag+1;
        if(mFlag == 10)
          mFlag = 1;
      }
       
      // left
      if(btn == 11){
        mFlag = mFlag-1;
        if(mFlag == 0)
          mFlag = 9;  
      } 

      // 0, ok when vipFlag is 0
      if((vipFlag == 0)&&(btn == 16 || btn == 12)){
        sFlag = 0;
      }     
    }
    vipFlag = 0;
    newMFlag();
    irrecv.resume();
  } 
} 

// set the color
void setColor(int r, int g, int b){
  Driver.SetColor(r,g,b);
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

    // 0  
    case 0xff4ab5:
      return 16;
      break;

    // #  
    case 0xff52ad:
      return 17;
      break;

    // up  
    case 0xff629d:
      return 10;
      break;

    // left  
    case 0xff22dd:
      return 11;
      break;

    // ok  
    case 0xff02fd:
      return 12;
      break;

    // right  
    case 0xffc23d:
      return 13;
      break;

    // down  
    case 0xffa857:
      return 14;
      break;
  }
}

