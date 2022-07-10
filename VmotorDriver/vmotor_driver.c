#include "timer.h"
#include "adc.h"
#include "dac.h"
#include "encoder.h" 
#include "vmotor_driver.h"

//针对硬盘音圈电机驱动程序

float motor_pos = 0, motor_vel = 0;

/**
  * @brief  Kalman滤波器
  * @param 
  * @return 
  */
static double KalmanFilterSpeed(const double ResrcData,double ProcessNiose_Q,double MeasureNoise_R)
{
    double R = MeasureNoise_R;
    double Q = ProcessNiose_Q;

    static double x_last;
    double x_mid = x_last;
    double x_now;

    static double p_last;
    double p_mid ;
    double p_now;

    double kg;

    x_mid=x_last;   
    p_mid=p_last+Q;             
    
    kg=p_mid/(p_mid+R);                 
    x_now=x_mid+kg*(ResrcData-x_mid);   
    p_now=(1-kg)*p_mid;                 
    p_last = p_now;                     
    x_last = x_now;                     

    return x_now;
}

/**
  * @brief  音圈电机IO初始化
  * @param  
  * @return 
  */
void voiceCtrlIO_Init(void)
{    	 
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_SetBits(GPIOA, GPIO_Pin_2 | GPIO_Pin_3);
}

/**
  * @brief  速度计算函数
  * @param   
  * @return 
  */
void voiceMotorSpeedComput()
{
	static float last_pos = 0;
	motor_pos = getEncoderCount();
	motor_vel = KalmanFilterSpeed((motor_pos - last_pos), 0.001, 1.0);
	last_pos = motor_pos;
}

/**
  * @brief  
  * @param   
  * @return 
  */
void voiceBspInit()
{
	registTimerCallBack(voiceMotorSpeedComput);
	EncoderTimerInit();
	voiceCtrlIO_Init();
	Dac1_Init();
}

/**
  * @brief  
  * @param   
  * @return 
  */
float getMotorPos()
{
	return motor_pos;
}

/**
  * @brief  
  * @param   
  * @return 
  */
float getMotorVel()
{
	return motor_vel;
}

/**
  * @brief  
  * @param   
  * @return 
  */
void setMotorCur(float cur)
{
	DacSetVol(1, cur);
}







