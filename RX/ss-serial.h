#ifndef __SS_SERIAL_H__
#define __SS_SERIAL_H__

#include <SoftwareSerial.h> 

#define SS_RX 2 // RX is digital pin 2 (connect to TX of other device)
#define SS_TX 3 // TX is digital pin 3 (connect to RX of other device)
#define SS_BAUDRATE 38400

SoftwareSerial ss(SS_RX, SS_TX); // RX, TX

void initSSerial(){
  ss.begin( SS_BAUDRATE );
}



#endif
