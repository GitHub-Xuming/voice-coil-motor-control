#ifndef SERVO_CONTROL_H
#define SERVO_CONTROL_H
#include <math.h>
#include <stdint.h> 
#include <sys.h>

void servoCtrlInit();
void servoCtrlLoop();
void servoExternSetCurrent(float cur);
void servoSetGoalPos(float pos);

#endif 



