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


static rt_uint32_t count = 0;
//-------------------------------------------------------------------------------------------------------------------
//  @brief      �߳�1��ں���
//  @param      parameter   ����
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void thread1_entry(void *parameter)
{
    rt_thread_mdelay(10);           //�ȴ�FINSH��ʼ�����
    while(1)
    {

        rt_enter_critical();        //�����������������󽫲����л��������̣߳�����Ӧ�ж�
        //���½����ٽ���
        count += 10;                //����ֵ+10
        rt_exit_critical();         //����������

        rt_kprintf("thread = %d , count = %d\n", 10, count);
        rt_thread_mdelay(1000);
        if(count >= 100)
        {
            break;
        }
    }
    rt_kprintf("\n thread1 exit!\n");
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      �߳�2��ں���
//  @param      parameter   ����
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void thread2_entry(void *parameter)
{
    rt_thread_mdelay(10);           //�ȴ�FINSH��ʼ�����
    while(1)
    {

        rt_enter_critical();        //�����������������󽫲����л��������̣߳�����Ӧ�ж�
        //���½����ٽ���
        count += 20;                //����ֵ+20
        rt_exit_critical();         //����������

        rt_kprintf("thread = %d , count = %d\n", 20, count);
        rt_thread_mdelay(2000);
        if(count >= 100)
        {
            break;
        }
    }
    rt_kprintf("\n thread2 exit!\n");
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      �̴߳����Լ�����
//  @param      void        ��
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
int critical_section_example(void)
{
    //�߳̿��ƿ�ָ��
    rt_thread_t tid;
    //������̬�߳�
    tid = rt_thread_create("thread_10",     //�߳�����
            thread1_entry,                  //�߳���ں���
            RT_NULL,                        //�̲߳���
            512,                            //ջ�ռ�
            5,                              //�߳����ȼ�Ϊ5����ֵԽС�����ȼ�Խ�ߣ�0Ϊ������ȼ���
                                            //����ͨ���޸�rt_config.h�е�RT_THREAD_PRIORITY_MAX�궨��(Ĭ��ֵΪ8)���޸����֧�ֵ����ȼ�
            10);                            //ʱ��Ƭ
    if(tid != RT_NULL)                      //�̴߳����ɹ�
    {
        rt_thread_startup(tid);             //���и��߳�
    }

    tid = rt_thread_create("thread_20",     //�߳�����
            thread2_entry,                  //�߳���ں���
            RT_NULL,                        //�̲߳���
            512,                            //ջ�ռ�
            3,                              //�߳����ȼ�Ϊ3����ֵԽС�����ȼ�Խ�ߣ�0Ϊ������ȼ���
                                            //����ͨ���޸�rt_config.h�е�RT_THREAD_PRIORITY_MAX�궨��(Ĭ��ֵΪ8)���޸����֧�ֵ����ȼ�
            10);                            //ʱ��Ƭ
    if(tid != RT_NULL)                      //�̴߳����ɹ�
    {
        rt_thread_startup(tid);             //���и��߳�
    }


    return 0;
}

//ʹ��INIT_APP_EXPORT���Զ���ʼ����Ҳ����ͨ���������߳��ڵ���critical_section_example�������г�ʼ��
INIT_APP_EXPORT(critical_section_example);      //Ӧ�ó�ʼ��

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



