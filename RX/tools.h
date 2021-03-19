#ifndef __TOOLS_H__ 
#define __TOOLS_H__ 

uint16_t mapChannelTo( uint16_t ch, uint16_t min, uint16_t max ){
  uint16_t ch_v = channels[ ch ];
  return map( ch_v, RX_SWITCH_MIN, RX_SWITCH_MAX, min, max);
}

uint16_t mapChannel( uint16_t ch ){
  return mapChannelTo( ch, 0, 180);
}

uint16_t isChannelLow( uint16_t ch ){
  return mapChannel( ch ) == 0; // RX_SWITCH_MIN;
}

uint16_t isChannelMiddle( uint16_t ch ){
  return mapChannel( ch ) == 90; // RX_SWITCH_MIDDLE;
}

uint16_t isChannelHight( uint16_t ch ){
  return mapChannel( ch ) == 180; // RX_SWITCH_MAX;
}

int16_t clampGyro( int16_t val ){
  val = val > GYRO_MAX ? GYRO_MAX : val < GYRO_MIN ? GYRO_MIN : val;
  return val;
}

#endif
