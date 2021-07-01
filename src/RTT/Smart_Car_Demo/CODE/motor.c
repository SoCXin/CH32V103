#include "motor.h"

#define MOTOR1_A   B10              //定义1电机正反转引脚
#define MOTOR1_B   PWM4_CH3_B8      //定义1电机PWM引脚

#define MOTOR2_A   B11              //定义2电机正反转引脚
#define MOTOR2_B   PWM4_CH4_B9      //定义2电机PWM引脚

#define MOTOR3_A   A15              //定义3电机正反转引脚
#define MOTOR3_B   PWM4_CH1_B6      //定义3电机PWM引脚

#define MOTOR4_A   B3               //定义4电机正反转引脚
#define MOTOR4_B   PWM4_CH2_B7      //定义4电机PWM引脚

void motor_init(void)
{
    //初始化电机PWM引脚和方向引脚

    //桌大大的推文中，建议电磁组电机频率选用13K-17K
    //最大占空比值PWM_DUTY_MAX 可以在fsl_pwm.h文件中修改 默认为50000
    //对于一个PWM模块 包含的所有通道只能输出频率一样 占空比不一样的 PWM CH32V103R8T6只有四个PWM模块 每个模块有4个通道
    gpio_init(MOTOR1_A, GPO, 0, GPIO_PIN_CONFIG);
    pwm_init(MOTOR1_B,17000,0);
    gpio_init(MOTOR2_A, GPO, 0, GPIO_PIN_CONFIG);
    pwm_init(MOTOR2_B,17000,0);
    gpio_init(MOTOR3_A, GPO, 0, GPIO_PIN_CONFIG);
    pwm_init(MOTOR3_B,17000,0);
    gpio_init(MOTOR4_A, GPO, 0, GPIO_PIN_CONFIG);
    pwm_init(MOTOR4_B,17000,0);
}

void motor_pid(int16 expect_speed)
{
    
}


void motor_control(int32 duty_1, int32 duty_2, int32 duty_3, int32 duty_4)
{
    //对占空比限幅
    if(duty_1>PWM_DUTY_MAX) duty_1 = PWM_DUTY_MAX;
    else                    duty_1 = -PWM_DUTY_MAX;

    if(duty_2>PWM_DUTY_MAX) duty_2 = PWM_DUTY_MAX;
    else                    duty_2 = -PWM_DUTY_MAX;

    if(duty_3>PWM_DUTY_MAX) duty_3 = PWM_DUTY_MAX;
    else                    duty_3 = -PWM_DUTY_MAX;
    
    if(duty_4>PWM_DUTY_MAX) duty_4 = PWM_DUTY_MAX;
    else                    duty_4 = -PWM_DUTY_MAX;
    
    if(0<=duty_1) //电机1   正转 设置占空比为 百分之 (1000/TIMER1_PWM_DUTY_MAX*100)
    {
        gpio_set(MOTOR1_A, 1);
        pwm_duty(MOTOR1_B, duty_1);
    }
    else                //电机1   反转
    {
        gpio_set(MOTOR1_A, 0);
        pwm_duty(MOTOR1_B, -duty_1);
    }

    if(0<=duty_2) //电机2   正转
    {
        gpio_set(MOTOR2_A, 1);
        pwm_duty(MOTOR2_B, duty_2);
    }
    else                //电机2   反转
    {
        gpio_set(MOTOR2_A, 0);
        pwm_duty(MOTOR2_B, -duty_2);
    }

    if(0<=duty_3) //电机3   正转
    {
        gpio_set(MOTOR3_A, 1);
        pwm_duty(MOTOR3_B, duty_3);
    }
    else                //电机3   反转
    {
        gpio_set(MOTOR3_A, 0);
        pwm_duty(MOTOR3_B, -duty_3);
    }

    if(0<=duty_4) //电机3   正转
    {
        gpio_set(MOTOR4_A, 1);
        pwm_duty(MOTOR4_B, duty_4);
    }
    else                //电机3   反转
    {
        gpio_set(MOTOR4_A, 0);
        pwm_duty(MOTOR4_B, -duty_4);
    }
}
