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

//����һ���ַ���
static char mb_str1[] = "i am a mail!";

//������ƿ��ָ��
static rt_mailbox_t mb;
//-------------------------------------------------------------------------------------------------------------------
//  @brief      �߳����
//  @param      parameter   ����
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void thread1_entry(void *parameter)
{
    char* str;
    rt_thread_mdelay(10);                                                       //�ȴ�FINSH��ʼ�����
    rt_kprintf("thread1:try to recv a mail.\n");

    if(rt_mb_recv(mb,                                                           //������ƿ�
            (rt_uint32_t *)&str,                                                //����������ַ���
            RT_WAITING_FOREVER)                                                 //һֱ�ȴ�
            == RT_EOK)
    {
        rt_kprintf("thread1:get a mail from mailbox.the content :%s\n", str);   //���������Ϣ
    }
    rt_mb_delete(mb);                                                           //ɾ������
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
    rt_thread_mdelay(10);                                                       //�ȴ�FINSH��ʼ�����
    rt_kprintf("thread2:try to send a mail.\n");
    rt_mb_send(mb, (rt_uint32_t)&mb_str1);                                      //��������
    rt_kprintf("\n thread2 exit!\n");
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���䴴���Լ�����
//  @param      void
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
int mailbox_example(void)
{
    //�߳̿��ƿ�ָ��
    rt_thread_t t1,t2;

    //��������
    mb = rt_mb_create("mb",
            4,                              //4x32���ֽڵı���
            RT_IPC_FLAG_FIFO                //�Ƚ��ȳ�
            );

    //������̬�߳�
    t1 = rt_thread_create(
          "thread1",                        //�߳�����
          thread1_entry,                    //�߳���ں���
          RT_NULL,                          //�̲߳���
          512,                              //ջ�ռ��С
          4,                                //�����߳����ȼ�
          5);                               //ʱ��Ƭ

    if(t1 != RT_NULL)                       //�̴߳����ɹ�
    {
        rt_thread_startup(t1);              //���и��߳�
    }

    //������̬�߳�
    t2 = rt_thread_create(
            "thread2",                      //�߳�����
            thread2_entry,                  //�߳���ں���
            RT_NULL,                        //�̲߳���
            512,                            //ջ�ռ��С
            3,                              //�����߳����ȼ�
            5);                             //ʱ��Ƭ

    if(t2 != RT_NULL)                       //�̴߳����ɹ�
    {
        rt_thread_startup(t2);              //���и��߳�
    }

    return 0;
}

//ʹ��INIT_APP_EXPORT���Զ���ʼ����Ҳ����ͨ���������߳��ڵ���mailbox_example�������г�ʼ��
INIT_APP_EXPORT(mailbox_example);           //Ӧ�ó�ʼ��

int main(void)
{
    //ʹ��ǰ��Ҫ��Libraries\rtthread_libraries\bsp\rtconfig.h�д�RT_USING_MUTEX�궨��

    //�˴���д�û�����(���磺�����ʼ�������)
    gpio_init(B15, GPO, 0, GPIO_PIN_CONFIG);
    while(1)
    {
        gpio_toggle(B15);
        rt_thread_mdelay(100);
    }
}

