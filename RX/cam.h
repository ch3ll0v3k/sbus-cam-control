#ifndef __CAM_H__ 
#define __CAM_H__ 

#define CAM_PIN A0
#define CAM_HOME 150
#define CAM_MIN 40
#define CAM_MAX 180 - 20
#define CAM_DEFAULT_ANGLE 15

Servo cam;

void camSet( uint16_t val ){
  val = val > CAM_MAX ? CAM_MAX : val < CAM_MIN ? CAM_MIN : val;
  // cam.writeMicroseconds( val );
  cam.write( val );
}

void initCam(){
  cam.attach( CAM_PIN );
  camSet( CAM_HOME );
}

#endif
