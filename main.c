#include "sys.h"
#include "delay.h"
#include "timer.h" 
#include "vmotor_driver.h"
#include "servo_ctrl.h"

float test_pos = 0, amplitude = 300, time = 0;
int main(void)
{ 
	delay_init(168);
	voiceBspInit();
	SYS_CLOCK_TIMER_Init(100,84-1);
	servoCtrlInit();
	delay_ms(100);
	
	while(1)
	{	
		if(getControlPeriodFlag()) //位置更新1000HZ
		{
			time += 0.00628;
			test_pos = amplitude * sin(time); //正弦位置测试
			servoSetGoalPos(test_pos);	
			setControlPeriodFlag(0);
		}
		
		servoCtrlLoop();  //伺服控制
	}
}





