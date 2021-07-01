/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897(����)  ��Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file            main
 * @company         �ɶ���ɿƼ����޹�˾
 * @author          ��ɿƼ�(QQ790875685)
 * @version         �鿴doc��version�ļ� �汾˵��
 * @Software        MounRiver Studio V1.3
 * @Target core     CH32V103R8T6
 * @Taobao          https://seekfree.taobao.com/
 * @date            2020-12-04
 ********************************************************************************************************************/
//�����Ƽ�IO�鿴Projecct�ļ����µ�TXT�ı�

//���µĹ��̻��߹����ƶ���λ�����ִ�����²���
//�Ҽ��������̣�ѡ��ˢ��

#include "headfile.h"

//��ʱ�����ƿ�ָ��
rt_timer_t timer1;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ʱ����ʱ����
//  @param      parameter   ����
//  @return     void
//  @note       ��ʱ����ʱ��������ʱ�䵽֮����Զ����иú���
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void timerout1(void *parameter)
{
    static rt_uint8_t count = 0;
    rt_kprintf("timerout!!!\n");

    //ִ��10�κ�ֹͣ�ö�ʱ��
    if(count++ >= 10)
    {
        rt_timer_stop(timer1);
        rt_kprintf("stop timer1!\n");

        rt_timer_delete(timer1);
        rt_kprintf("delete timer1!!!\n");
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �̴߳����Լ�����
//  @param      void        ��
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
int timer_example(void)
{
    //����һ����ʱ�� ����100��tick
    timer1 = rt_timer_create(
            "timer1",                  //timer1��ʾ��ʱ�������ƣ�8���ַ��ڡ�
            timerout1,                 //timerout1��ʾʱ�䵽��֮����Ҫִ�еĺ���
            RT_NULL,                   //RT_NULL��ʾ����Ҫ���ݲ�����
            100,                       //100��ʾ��ʱ���ĳ�ʱʱ��Ϊ100��ϵͳtick��ϵͳ����Ϊ1���룬��100��ʾ100����
            RT_TIMER_FLAG_PERIODIC);   //RT_TIMER_FLAG_PERIODIC��ʾ��ʱ������������  �������ΪRT_TIMER_FLAG_ONE_SHOT��ֻ������һ��

    //���ȼ�鶨ʱ�����ƿ鲻�ǿգ���������ʱ��
    if(timer1 != RT_NULL)
    {
        rt_timer_start(timer1);
    }

    return 0;
}

//ʹ��INIT_APP_EXPORT���Զ���ʼ����Ҳ����ͨ���������߳��ڵ���timer_example�������г�ʼ��
INIT_APP_EXPORT(timer_example);

int main(void)
{

    //�˴���д�û�����(���磺�����ʼ�������)
    gpio_init(B15, GPO, 0, GPIO_PIN_CONFIG);

    while(1)
    {
        gpio_toggle(B15);
        rt_thread_mdelay(100);
    }
}
