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

//��Ϣ���п��ƿ�ָ��
rt_mq_t message_queue;


//-------------------------------------------------------------------------------------------------------------------
//  @brief      �߳����
//  @param      parameter   ����
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void thread1_entry(void *paremeter)
{
    uint8 recv_test;
    rt_thread_mdelay(10);               //�ȴ�FINSH��ʼ�����
    while(1)
    {
        //����Ϣ���л�ȡ��Ϣ
        rt_mq_recv(message_queue,       //��Ϣ���п��ƿ�
                   (void *)&recv_test,  //�������ݵĵ�ַ
                   1,                   //��������
                   RT_WAITING_FOREVER); //һֱ�ȴ������ݲ��˳����պ���

        //����յ������� �뷢������ƥ��Ļ� ������յ���Ϣ
        if(10 == recv_test)
        {
            rt_kprintf("Received data = %d\n", 10);
        }
    }
    rt_kprintf("\n thread1 exit!\n");
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      �߳����
//  @param      parameter   ����
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void thread2_entry(void *paremeter)
{
    rt_uint8_t send_test = 10;
    static rt_uint8_t count = 0;
    rt_thread_t tid = rt_thread_find("thread1");  //�߳̿��ƿ�
    rt_thread_mdelay(10);                         //�ȴ�FINSH��ʼ�����
    while(1)
    {
        //����һ����Ϣ����Ϣ����
        rt_mq_send(message_queue,       //��Ϣ���п��ƿ�
                   (void *)&send_test,  //�������ݵĵ�ַ
                   1);                  //�����ֽ���

        //��ʱ100���� �ͷ�CPU����Ȩ
        rt_thread_mdelay(100);
        if(count++ > 10)
        {
            rt_thread_delete(tid);      //ɾ���߳�1
            rt_kprintf("\n delete thread1!\n");
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
int message_queue_example(void)
{
    //�߳̿��ƿ�ָ��
    rt_thread_t thread1,thread2;

    //��������
    message_queue = rt_mq_create("mq1",             //��Ϣ��������
                                  1,                //һ����Ϣ�Ĵ�СΪһ���ֽ�
                                  10,               //һ���ܴ��10����Ϣ
                                  RT_IPC_FLAG_FIFO);//����ж���̵߳ȴ������������ȵ÷���


    //������̬�߳�
    thread1 = rt_thread_create("thread1",           //�߳�����
                                thread1_entry,      //�߳����
                                RT_NULL,            //�̲߳���
                                512,                //�߳�ջ��С
                                3,                  //�߳����ȼ�
                                10);                //�߳�ʱ��Ƭ
    //����߳̿��ƿ鲻Ϊ���������߳�
    if(thread1 != RT_NULL)
    {
        rt_thread_startup(thread1);
    }

    //������̬�߳�
    thread2 = rt_thread_create("thread2",           //�߳�����
                                thread2_entry,      //�߳����
                                RT_NULL,            //�̲߳���
                                512,                //�߳�ջ��С
                                4,                  //�߳����ȼ�
                                10);                //�߳�ʱ��Ƭ
    //����߳̿��ƿ鲻Ϊ���������߳�
    if(thread2 != RT_NULL)
    {
        rt_thread_startup(thread2);
    }
    return 0;
}

//ʹ��INIT_APP_EXPORT���Զ���ʼ����Ҳ����ͨ���������߳��ڵ���message_queue_example�������г�ʼ��
INIT_APP_EXPORT(message_queue_example);

int main(void)
{
    //ʹ��ǰ��Ҫ��Libraries\rtthread_libraries\bsp\rtconfig.h�д�RT_USING_MESSAGEQUEUE�궨��

    //�˴���д�û�����(���磺�����ʼ�������)
    gpio_init(B15, GPO, 0, GPIO_PIN_CONFIG);
    while(1)
    {
        gpio_toggle(B15);
        rt_thread_mdelay(100);
    }
}
