#include "timer.h"
#include "pid_controller.h"
#include "vmotor_driver.h"
#include "servo_ctrl.h"
#include "encoder.h" 

TargetPID pid_pos_loop, pid_vel_loop;  //位置环和速度环对象
float Kp_pos_loop = 0.1, Ki_pos_loop = 0.0, Kd_pos_loop = 0;  //pid参数
float Kp_vel_loop = 0.1, Ki_vel_loop = 0.0, Kd_vel_loop = 0;
float goal_pos_loop = 0, goal_vel_loop = 0, goal_cur_loop; //目标值
float current_max = 1.5;

/**
  * @brief  
  * @param   
  * @return 
  */
void servoCtrlInit()
{
    pid_pos_loop.getFeedbackVal = getMotorPos;
    pid_vel_loop.getFeedbackVal = getMotorVel;

    PID_SetPidPara(&pid_pos_loop, Kp_pos_loop, Ki_pos_loop, Kd_pos_loop);
    PID_SetPidPara(&pid_vel_loop, Kp_vel_loop, Ki_vel_loop, Kd_vel_loop);
}

/**
  * @brief  
  * @param   
  * @return 
  */
void servoSetGoalPos(float pos)
{
    goal_pos_loop = pos;
}

/**
  * @brief  
  * @param   
  * @return 
  */
void servoCtrlLoop()
{
    getEncoderCount();
    PID_SetPidPara(&pid_pos_loop, Kp_pos_loop, Ki_pos_loop, Kd_pos_loop);
    PID_SetPidPara(&pid_vel_loop, Kp_vel_loop, Ki_vel_loop, Kd_vel_loop);
    PID_SetGoalVal(&pid_pos_loop, goal_pos_loop);   //设置位置环目标值
    goal_vel_loop = PID_Control(&pid_pos_loop);      //速度环目标 = 位置环输出
    PID_SetGoalVal(&pid_vel_loop, goal_vel_loop);   //设置速度环目标值
    goal_cur_loop = PID_Control(&pid_vel_loop);      //电流环目标 = 速度环输出
    
    if(goal_cur_loop > current_max)
        goal_cur_loop = current_max;
    if(goal_cur_loop < -current_max)
        goal_cur_loop = -current_max;

    if(goal_cur_loop > 0)
    {
        MOTOR_DIR_IN1 = 0;
        MOTOR_DIR_IN2 = 1;
    }
    else
    {
        MOTOR_DIR_IN1 = 1;
        MOTOR_DIR_IN2 = 0;
    }
    setMotorCur(fabs(goal_cur_loop));
}


