#include "RX.h"

#include "ss-serial.h"
#include "boards.h"
#include "cam.h"
#include "gyro.h"
#include "tools.h"

// D18 -> RXD Inverted SBUS
// SBUS x8r(Serial1); // MEGA

SBUS x8r(Serial); // NANO

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

// Timers
unsigned long timer = 0;
float timeStep = 1;
float pitch = 0;
float roll = 0;
float yaw = 0;

void setup() {
  // if( isMega() ){
    Serial.begin( 57600 );
    Serial.println("[SBUS] end");
    Serial.println("[SBUS] begin");
  // }
    
  // x8r.begin();

  // if( isMega() ){
    Serial.println("[SBUS] end");
    Serial.println("done.");
  // }

  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G)){
    Serial.println("!mpu");
    delay(500);
  }

  pinMode(CAM_PIN, OUTPUT);
  initCam();
  initSSerial();

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

  Serial.println("SS:inited");

}

void loop() {

  // look for a good SBUS packet from the receiver

  // readState = x8r.read(&channels[0], &failSafe, &lostFrame);

  // if( !readState ){
  //   Serial.println("readState: "+( (uint8_t)readState ));
  //   delay(500);
  //   return;
  // }

  if( failSafe || lostFrame ){
    Serial.println("failSafe: "+( (uint8_t)failSafe ));
    Serial.println(" lostFrame: "+( (uint8_t)lostFrame ));
    delay(500);
    return;
  }

  if( isChannelLow( RX_SE ) ){
    Serial.println("RX_SE is LOW");
    delay(500);
    return;
  }

  // Serial.println( mapChannelTo( RX_S1, CAM_MIN, CAM_MAX ) );
  // Serial.println( mapChannel( RX_SA ) );

  timer = millis();

  mGyro = mpu.readNormalizeGyro();
  // gyro_x = clampGyro( mGyro.XAxis - gyroOffset_x );
  // gyro_y = clampGyro( mGyro.YAxis - gyroOffset_y );
  // gyro_z = clampGyro( mGyro.ZAxis - gyroOffset_z );

  pitch = pitch + mGyro.YAxis * timeStep;
  gyro_y = pitch;

  Serial.print("gyro_y: "); Serial.println(gyro_y);

  // pitch = pitch + norm.YAxis * timeStep;
  // roll = roll + norm.XAxis * timeStep;
  // yaw = yaw + norm.ZAxis * timeStep;

  uint8_t gyroManualMull = isChannelMiddle( RX_SE );
  uint8_t allowAdjustGimbal = isChannelHight( RX_SE );

  // tripple-pos Cam mode - ON
  if( isChannelLow( RX_SA ) ){
    Serial.print(" RX_SA: LOW: (tripple-pos Cam mode - ON) ");

    if( isChannelLow( RX_SB ) ){
      Serial.print("    RX_SB: LOW ");
      camSet( CAM_HOME + (-CAM_DEFAULT_ANGLE) + (gyro_y * gyroManualMull) );

    }else if( isChannelMiddle( RX_SB ) ){
      Serial.print("    RX_SB: MIDDLE ");
      camSet( CAM_HOME + (0) + (gyro_y * gyroManualMull) );

    }else if( isChannelHight( RX_SB ) ){
      Serial.print("    RX_SB: HIGHT ");
      camSet( CAM_HOME + (+CAM_DEFAULT_ANGLE) + (gyro_y * gyroManualMull) );

    }

  }

  // Manual Cam mode - ON
  if( isChannelMiddle( RX_SA ) ){
    Serial.print(" RX_SA: MIDDLE: (Manual Cam mode - ON) ");
    uint16_t camPos = mapChannelTo( RX_S1, CAM_MIN, CAM_MAX );
    camSet( camPos + (0) + (gyro_y * gyroManualMull) );
  }

  // Gimbal Cam mode - ON
  if( isChannelHight( RX_SA ) ){
    Serial.print(" RX_SA: HIGHT: (Gimbal Cam mode - ON) ");

    uint16_t camPos = mapChannelTo( RX_S1, CAM_MIN, CAM_MAX );
    // TODO .....
    uint16_t endPos = ( (gyro_y * GYRO_COMP_COEF) * 1 ) + ( camPos * allowAdjustGimbal );
    camSet( endPos );

  }

  uint16_t gyroDelay = (timeStep*1000) - (millis() - timer);
  Serial.println("gyroDelay: "+gyroDelay);

  delay(gyroDelay);
  // delay(500);
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
