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
rt_uint32_t count = 0;
//-------------------------------------------------------------------------------------------------------------------
//  @brief      �߳�1��ں���
//  @param      parameter   ����
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void thread_slice_10_entry(void *parameter)
{
    rt_thread_mdelay(10);           //�ȴ�FINSH��ʼ�����

    while(1)
    {
        if(0 == (count % 5))
        {
            rt_enter_critical();
            rt_kprintf("time slice 10 is running, count = %d\n", count);
            rt_exit_critical();
            if(200 <= count)
            {
                return;
            }
        }
        count++;
    }
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      �߳�2��ں���
//  @param      parameter   ����
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void thread_slice_20_entry(void *parameter)
{
    rt_thread_mdelay(10);           //�ȴ�FINSH��ʼ�����
    while(1)
    {
        if(0 == (count % 5))
        {
            rt_enter_critical();
            rt_kprintf("time slice 20 is running, count = %d\n", count);
            rt_exit_critical();
            if(200 <= count)
            {
                break;
            }
        }
        count++;
    }
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      �̴߳����Լ�����
//  @param      void
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
int time_slice_20_thread_example(void)
{
    //�߳̿��ƿ�ָ��
    rt_thread_t tid1;
    //������̬�߳�
    tid1 = rt_thread_create("thread_20",    //�߳�����
            thread_slice_20_entry,          //�߳���ں���
            RT_NULL,                        //�̲߳���
            512,                            //512���ֽڵ�ջ�ռ�
            5,                              //�߳����ȼ�Ϊ5����ֵԽС�����ȼ�Խ�ߣ�0Ϊ������ȼ���
                                            //����ͨ���޸�rt_config.h�е�RT_THREAD_PRIORITY_MAX�궨��(Ĭ��ֵΪ8)���޸����֧�ֵ����ȼ�
            10);                            //ʱ��Ƭ

    rt_kprintf("create time slice 20 thread...\n\n");
    if(tid1 != RT_NULL)                     //�̴߳����ɹ�
    {
        rt_kprintf("time slice 20 thread create OK...\n\n");
        rt_thread_startup(tid1);            //���и��߳�
    }
    else                                    //�̴߳���ʧ��
    {
        rt_kprintf("time slice 20 thread create ERROR...\n\n");
        return 1;
    }

    return 0;
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��̬�̴߳����Լ�����
//  @param      void        ��
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
int time_slice_10_thread_example(void)
{
    //�߳̿��ƿ�ָ��
    rt_thread_t tid1;
    //������̬�߳�
    tid1 = rt_thread_create("thread_10",    //�߳�����
            thread_slice_10_entry,          //�߳���ں���
            RT_NULL,                        //�̲߳���
            512,                            //512���ֽڵ�ջ�ռ�
            5,                              //�߳����ȼ�Ϊ5����ֵԽС�����ȼ�Խ�ߣ�0Ϊ������ȼ���
                                            //����ͨ���޸�rt_config.h�е�RT_THREAD_PRIORITY_MAX�궨��(Ĭ��ֵΪ8)���޸����֧�ֵ����ȼ�
            20);                            //ʱ��ƬΪ20

    rt_kprintf("create time slice 10 thread...\n\n");
    if(tid1 != RT_NULL)                     //�̴߳����ɹ�
    {
        rt_kprintf("time slice 10 thread create OK...\n\n");
        rt_thread_startup(tid1);            //���и��߳�
    }
    else                                    //�̴߳���ʧ��
    {
        rt_kprintf("time slice 10 thread create ERROR...\n\n");
        return 1;
    }

    return 0;
}


//ʹ��INIT_APP_EXPORT���Զ���ʼ����Ҳ����ͨ���������߳��ڵ���time_slice_10_thread_example�������г�ʼ��
INIT_APP_EXPORT(time_slice_10_thread_example);
//ʹ��INIT_APP_EXPORT���Զ���ʼ����Ҳ����ͨ���������߳��ڵ���time_slice_20_thread_example�������г�ʼ��
INIT_APP_EXPORT(time_slice_20_thread_example);

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



