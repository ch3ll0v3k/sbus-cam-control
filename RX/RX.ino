#include "SBUS.h"
#include "RX.h"
#include "cam.h"
#include "gyro.h"
#include "tools.h"

// D18 -> RXD Inverted SBUS
SBUS x8r(Serial1); // MEGA
// SBUS x8r(Serial); // NANO
MPU6050 mpu;
Vector mGyro;

bool isArmed = 0;
bool failSafe = 0;
bool lostFrame = 0;
int32_t readState = 0;

int16_t gyroOffset_x = 0;
int16_t gyroOffset_y = 0;
int16_t gyroOffset_z = 0;

int16_t gyro_x = 0;
int16_t gyro_y = 0;
int16_t gyro_z = 0;

void setup() {
  // Serial.begin( 57600 );
  // Serial.println("[Searial] is ready");
  // Serial.println("[SBUS] begin");
  x8r.begin();
  // Serial.println("[SBUS] end");
  // Serial.println("done.");

  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G)){
    delay(100);
  }

  pinMode(CAM_PIN, OUTPUT);
  camSet( CAM_HOME );
  digitalWrite( LED_BUILTIN, isArmed );

  mpu.calibrateGyro();
  // mpu.setThreshold(3);

  gyroOffset_x = mpu.getGyroOffsetX();
  gyroOffset_y = mpu.getGyroOffsetY();
  gyroOffset_z = mpu.getGyroOffsetZ();

  // mpu.setGyroOffsetX(155);
  // mpu.setGyroOffsetY(15);
  // mpu.setGyroOffsetZ(15);

}

void loop() {

  // look for a good SBUS packet from the receiver

  readState = x8r.read(&channels[0], &failSafe, &lostFrame);

  if( !readState ){
    //
    return;
  }

  if( failSafe || lostFrame ){
    //
    return;
  }

  if( isChannelLow( RX_SE ) ) return;

  mGyro = mpu.readNormalizeGyro();
  gyro_x = clampGyro( mGyro.XAxis - gyroOffset_x );
  gyro_y = clampGyro( mGyro.YAxis - gyroOffset_y );
  gyro_z = clampGyro( mGyro.ZAxis - gyroOffset_z );

  uint8_t gyroManualMull = isChannelMiddle( RX_SE );
  uint8_t allowAdjustGimbal = isChannelHight( RX_SE );

  // tripple-pos Cam mode - ON
  if( isChannelLow( RX_SA ) ){

    if( isChannelLow( RX_SB ) ){
      camSet( CAM_HOME + (-CAM_DEFAULT_ANGLE) + (gyro_y * gyroManualMull) );

    }else if( isChannelMiddle( RX_SB ) ){
      camSet( CAM_HOME + (0) + (gyro_y * gyroManualMull) );

    }else if( isChannelHight( RX_SB ) ){
      camSet( CAM_HOME + (+CAM_DEFAULT_ANGLE) + (gyro_y * gyroManualMull) );

    }

  }

  // Manual Cam mode - ON
  if( isChannelMiddle( RX_SA ) ){
    uint16_t camPos = mapChannelTo( RX_S1, CAM_MIN, CAM_MAX );
    camSet( camPos + (0) + (gyro_y * gyroManualMull) );
  }

  // Gimbal Cam mode - ON
  if( isChannelHight( RX_SA ) ){
    uint16_t camPos = mapChannelTo( RX_S1, CAM_MIN, CAM_MAX );
    // TODO .....
    uint16_t endPos = ( (gyro_y * GYRO_COMP_COEF) * -1 ) + ( camPos * allowAdjustGimbal );
    camSet( endPos );

  }

}


/*

uint8_t chi = 0;
// for(;chi < 4; chi++){
for(;chi < RX_CHANNELS; chi++){
  Serial.print(" chi-"); 
  Serial.print( chi );
  Serial.print(" ");
  Serial.print( channels[ chi ] );
  // Serial.println("");
  // Serial.print("chi-"); Serial.print( chi );
  // Serial.print(" ");
  // Serial.print( channels[ chi ] );
  // Serial.print(" ");
}

Serial.println("");
delay( 1000 );

// write the SBUS packet to an SBUS compatible servo
// x8r.write(&channels[0]);


*/