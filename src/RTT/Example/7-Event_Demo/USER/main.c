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

#define EVENT_FLAG3 (1<<3)
#define EVENT_FLAG5 (1<<5)

//�¼����ƿ�ָ��
rt_event_t event;
//-------------------------------------------------------------------------------------------------------------------
//  @brief      �߳����
//  @param      parameter   ����
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void thread1_entry(void *parameter)
{
    rt_uint32_t e;
    rt_thread_mdelay(10);           //�ȴ�FINSH��ʼ�����
    if(rt_event_recv
            (event,                                     //�¼����ƿ�
            (EVENT_FLAG3 | EVENT_FLAG5),                //�¼���־3���¼���־5
            (RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR),  //�¼��봥����������ɺ�����¼���־λ
            RT_WAITING_FOREVER,                         //һֱ�ȴ�
            &e) == RT_EOK)
    {
        rt_kprintf("thread1: AND recv event 0x%x\n", e);
    }
    rt_kprintf("\n thread1 exit!\n");
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �߳����
//  @param      parameter   ����
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void thread2_entry(void *parameter)
{
    rt_thread_mdelay(10);           //�ȴ�FINSH��ʼ�����

    rt_kprintf("thread2: send event3\n");
    rt_event_send(event, EVENT_FLAG3);
    rt_thread_mdelay(200);

    rt_kprintf("thread2: send event5\n");
    rt_event_send(event, EVENT_FLAG5);
    rt_thread_mdelay(200);

    rt_kprintf("\n thread2 exit!\n");
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �̴߳����Լ�����
//  @param      void        ��
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
int event_example(void)
{
    //�߳̿��ƿ�ָ��
    rt_thread_t tid;

    //�����¼�
    event = rt_event_create("event", RT_IPC_FLAG_FIFO);

    //������̬�߳�
    tid = rt_thread_create("thread1",       //�߳�����
            thread1_entry,                  //�߳���ں���
            RT_NULL,                        //�̲߳���
            512,                            //ջ�ռ�
            5,                              //�߳����ȼ�Ϊ5����ֵԽС�����ȼ�Խ�ߣ�0Ϊ������ȼ���
                                            //����ͨ���޸�rt_config.h�е�RT_THREAD_PRIORITY_MAX�궨��(Ĭ��ֵΪ8)���޸����֧�ֵ����ȼ�
            5);                             //ʱ��ƬΪ5

    if(tid != RT_NULL)                      //�̴߳����ɹ�
    {
        rt_kprintf("create thread1 OK\n");
        //���и��߳�
        rt_thread_startup(tid);
    }

    //������̬�߳�
    tid = rt_thread_create("thread2",       //�߳�����
            thread2_entry,                  //�߳���ں���
            RT_NULL,                        //�̲߳���
            512,                            //ջ�ռ�
            5,                              //�߳����ȼ�Ϊ5����ֵԽС�����ȼ�Խ�ߣ�0Ϊ������ȼ���
                                            //����ͨ���޸�rt_config.h�е�RT_THREAD_PRIORITY_MAX�궨��(Ĭ��ֵΪ8)���޸����֧�ֵ����ȼ�
            5);                             //ʱ��ƬΪ5

    if(tid != RT_NULL)                      //�̴߳����ɹ�
    {
        rt_kprintf("create thread2 OK\n");
        //���и��߳�
        rt_thread_startup(tid);
    }

    return 1;
}

//ʹ��INIT_APP_EXPORT���Զ���ʼ����Ҳ����ͨ���������߳��ڵ���event_example�������г�ʼ��
INIT_APP_EXPORT(event_example);      //Ӧ�ó�ʼ��

int main(void)
{
    //ʹ��ǰ��Ҫ��Libraries\rtthread_libraries\bsp\rtconfig.h�д� RT_USING_EVENT�궨��

    //�˴���д�û�����(���磺�����ʼ�������)
    gpio_init(B15, GPO, 0, GPIO_PIN_CONFIG);
    while(1)
    {
        gpio_toggle(B15);
        rt_thread_mdelay(100);
    }
}



