#ifndef SERVO_DRIVER_H
#define SERVO_DRIVER_H
#include <math.h>
#include <stdint.h> 
#include <sys.h>

#define     MOTOR_DIR_IN1    PAout(2)  //电机方向控制IO
#define     MOTOR_DIR_IN2    PAout(3)

void voiceBspInit();
float getMotorPos();
void setMotorPos(float pos);
float getMotorVel();
void setMotorCur(float cur);

#endif 



