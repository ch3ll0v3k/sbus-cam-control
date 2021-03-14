#ifndef __RX_H__ 
#define __RX_H__ 

#include <math.h>
#include <Wire.h>
#include <MPU6050.h>
#include <Servo.h>

#define RX_CHANNELS 16

#define RX_S1 11
#define RX_SE 10
#define RX_SA 8
#define RX_SB 9

#define RX_SWITCH_MIN 172
#define RX_SWITCH_MIDDLE 992
#define RX_SWITCH_MAX 1810
#define RX_SWITCH_RANGE RX_SWITCH_MAX - RX_SWITCH_MIN // == 1638
#define RX_SWITCH_RANGE_2 RX_SWITCH_RANGE /2 // 819

uint16_t channels[RX_CHANNELS];









#endif
