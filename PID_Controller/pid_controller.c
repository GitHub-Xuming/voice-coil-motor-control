#include "pid_controller.h"

/**
  * @brief  pid控制核心函数
  * @param  target 控制对象
  * @return pid控制输出量 
  */
float PID_Control(TargetPID *target)
{
	float bias = 0;

	target->input_val = target->getFeedbackVal(); //采集输入

	bias = target->goal_val - target->input_val;
	target->integral_i += bias;
	target->out_val = target->Kp * bias + target->Ki * target->integral_i + target->Kd * (bias - target->last_out_val);
	target->last_out_val = bias;

	if (target->integral_i > MAX_INTEGRAL_VAL)  //积分限幅
	{
		target->integral_i = MAX_INTEGRAL_VAL;
	}
	if (target->integral_i < -MAX_INTEGRAL_VAL)
	{
		target->integral_i = -MAX_INTEGRAL_VAL;
	}	

	if (target->out_val > MAX_OUT_VAL)    //输出限幅
	{
		target->out_val = MAX_OUT_VAL;
	}
	if (target->out_val < -MAX_OUT_VAL)
	{
		target->out_val = -MAX_OUT_VAL;
	}		

	return target->out_val;
}

/**
  * @brief  设置目标值
  * @param   target 控制对象
  * @return 
  */
void PID_SetGoalVal(TargetPID *target, float goal_val)
{
	target->goal_val = goal_val;
}

/**
  * @brief  设置控制参数
  * @param   target 控制对象
  * @return 
  */
void PID_SetPidPara(TargetPID *target, float kp, float ki, float kd)
{
	target->Kp = kp;
	target->Ki = ki;
	target->Kd = kd;
}







