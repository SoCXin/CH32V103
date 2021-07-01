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

/*ʹ�û�����֮ǰ�����Ȳ鿴 rtconfig.h�е� RT_USING_MUTEX �궨���Ƿ���*/


//���������ƿ�ָ��
static rt_mutex_t dynamic_mutex = RT_NULL;

static rt_uint32_t num1 = 0;
static rt_uint32_t num2 = 0;
//-------------------------------------------------------------------------------------------------------------------
//  @brief      �ͷ��ź����߳���ں���
//  @param      parameter   ����
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void thread1_entry(void *parameter)
{
    rt_thread_mdelay(10);           //�ȴ�FINSH��ʼ�����
    while(1)
    {
        rt_mutex_take(dynamic_mutex, RT_WAITING_FOREVER);           //��ȡ��������һֱ�ȴ�
        num1++;
        rt_thread_mdelay(100);
        num2++;
        rt_mutex_release(dynamic_mutex);                            //�ͷŻ�����
        if(num1 > 10)
        {
            break;
        }
    }

    rt_kprintf("\n thread1 exit!\n");
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ȡ�ź����߳���ں���
//  @param      parameter   ����
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void thread2_entry(void *parameter)
{
    rt_thread_mdelay(10);           //�ȴ�FINSH��ʼ�����
    while(1)
    {
        //�߳�2��ȡ�����������ж�num1��num2 ��ֵ�Ƿ���ͬ����ͬ��ʾ�����������������á�
        rt_mutex_take(dynamic_mutex, RT_WAITING_FOREVER);           //��ȡ��������һֱ�ȴ�
        if(num1 == num2)
        {
            rt_kprintf("\n num1 = num2 , num1 = %d  num2 = %d\n", num1, num2);
        }
        else
        {
            rt_kprintf("\n num1 != num2, num1 = %d  num2 = %d\n", num1, num2);
        }

        rt_mutex_release(dynamic_mutex);                            //�ͷŻ�����
        if(num1 > 10)
        {
            break;
        }
    }

    rt_kprintf("\n thread2 exit!\n");
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �̴߳����Լ�����
//  @param      void
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
int mutex_example(void)
{
    //�����߳̿��ƿ�
    rt_thread_t tid;

    //������̬������
    dynamic_mutex = rt_mutex_create("dynamic mutex", RT_IPC_FLAG_FIFO);
    if (dynamic_mutex == RT_NULL)           //�߳̿��ƿ鴴���ɹ�
    {
        rt_kprintf("create dynamic mutex failed.\n");
        return -1;
    }

    //������̬�߳�
    tid = rt_thread_create(
            "thread1",                      //�߳�����
            thread1_entry,                  //�߳���ں���
            RT_NULL,                        //�̲߳���
            512,                            //ջ�ռ��С
            3,                              //�����߳����ȼ�����ֵԽС�����ȼ�Խ�ߣ�0Ϊ������ȼ���
                                            //����ͨ���޸�rt_config.h�е�RT_THREAD_PRIORITY_MAX�궨��(Ĭ��ֵΪ8)���޸����֧�ֵ����ȼ�
            10);                            //ʱ��Ƭ

    if(tid != RT_NULL)                      //�̴߳����ɹ�
    {
        //���и��߳�
        rt_thread_startup(tid);
    }

    tid = rt_thread_create(
            "thread2",                      //�߳�����
            thread2_entry,                  //�߳���ں���
            RT_NULL,                        //�̲߳���
            512,                            //ջ�ռ��С
            4,                              //�����߳����ȼ�����ֵԽС�����ȼ�Խ�ߣ�0Ϊ������ȼ���
                                            //����ͨ���޸�rt_config.h�е�RT_THREAD_PRIORITY_MAX�궨��(Ĭ��ֵΪ8)���޸����֧�ֵ����ȼ�
            10);                            //ʱ��Ƭ

    if(tid != RT_NULL)                      //�̴߳����ɹ�
    {
        //���и��߳�
        rt_thread_startup(tid);
    }

    return 0;
}

//ʹ��INIT_APP_EXPORT���Զ���ʼ����Ҳ����ͨ���������߳��ڵ���mutex_example�������г�ʼ��
INIT_APP_EXPORT(mutex_example);

int main(void)
{
    //ʹ��ǰ��Ҫ��Libraries\rtthread_libraries\bsp\rtconfig.h�д�RT_USING_MAILBOX�궨��

    //�˴���д�û�����(���磺�����ʼ�������)
    gpio_init(B15, GPO, 0, GPIO_PIN_CONFIG);

    while(1)
    {
        gpio_toggle(B15);
        rt_thread_mdelay(100);
    }
}



