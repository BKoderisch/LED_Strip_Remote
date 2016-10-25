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

void setup(){ 
  pinMode(btnPin, INPUT);
  irrecv.enableIRIn();
}  

void loop(){ 
  Driver.begin();
  Serial.begin(9200);
  
  
  if(irrecv.decode(&results)){
    Serial.println(results.value);
    switch(sFlag){
      case 0:
        break;
    }
    irrecv.resume();
  }
  
}


