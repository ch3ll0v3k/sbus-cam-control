#ifndef __BOARDS_H__ 
#define __BOARDS_H__ 

uint8_t isMega(){
  #ifdef AVR_MEGA2560
  return 1;
  #endif
  return 0;
}

uint8_t isNano(){
  #ifdef AVR_NANO
  return 1;
  #endif
  return 0;
}

// AVR_ADK
// AVR_BT
// AVR_DUEMILANOVE
// AVR_ESPLORA
// AVR_ETHERNET
// AVR_FIO
// AVR_GEMMA
// AVR_LEONARDO
// AVR_LILYPAD
// AVR_LILYPAD_USB
// AVR_MEGA
// AVR_MEGA2560
// AVR_MICRO
// AVR_MINI
// AVR_NANO
// AVR_NG
// AVR_PRO
// AVR_ROBOT_CONTROL
// AVR_ROBOT_MOTOR
// AVR_UNO
// AVR_YUN

#endif 
