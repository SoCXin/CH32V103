#include "encoder.h"
#include "motor.h"
#include "timer_pit.h"
#include "elec.h"

void timer1_pit_entry(void *parameter)
{
    static uint32 time;
    time++;

    //�ɼ�����������
    encoder_get();
    
    //��������ٶȻ�
    
    
    //�ɼ�����������
    get_icm20602_gyro_spi();
    
    //�ɼ�����ź�
    elec_get();
    
    //���ݵ���źż��㳵��λ��
    elec_calculate();
    
    
    //��ͼ���������ĳ���λ�������źż�����ĳ���λ�ý����ںϵõ���������
    //Ȼ����г�ģ����
    

    
    //���Ƶ��ת��
    motor_control(1000, 1000, 1000, 1000);

}


void timer_pit_init(void)
{
    rt_timer_t timer;
    
    //����һ����ʱ�� ��������
    timer = rt_timer_create("timer1", timer1_pit_entry, RT_NULL, 2, RT_TIMER_FLAG_PERIODIC);
    
    //������ʱ��
    if(RT_NULL != timer)
    {
        rt_timer_start(timer);
    }

    
}
