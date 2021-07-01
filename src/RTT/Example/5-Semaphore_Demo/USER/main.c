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

//�ź������ƿ�ָ��
static rt_sem_t dynamic_sem = RT_NULL;
//-------------------------------------------------------------------------------------------------------------------
//  @brief      �ͷ��ź����߳���ں���
//  @param      parameter   ����
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void release_semaphore_thread_entry(void *parameter)
{
    static rt_uint16_t num = 0;
    //�߳̿��ƿ�ָ��
    rt_thread_t tid = rt_thread_find("get_semaphore");
    rt_thread_mdelay(10);           //�ȴ�FINSH��ʼ�����
    while(1)
    {
        if(num++ < 10)
        {
            rt_kprintf("\n release_semaphore_thread_entry release a semaphore. \n");
            rt_sem_release(dynamic_sem);            //�ͷ��ź���
            rt_thread_mdelay(1000);                 //��ʱ1000ms�����ó�CPUʹ��Ȩ
        }
        else
        {
            rt_sem_delete(dynamic_sem);             //ɾ���ź���
            rt_kprintf("\n delete dynamic_sem!\n");

            rt_thread_delete(tid);                  //ɾ���߳�1
            rt_kprintf("\n delete get_semaphore_thread\n");

            break;
        }
    }
    rt_kprintf("\n release_semaphore exit!\n");
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ȡ�ź����߳���ں���
//  @param      parameter   ����
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void get_semaphore_thread_entry(void *parameter)
{
    static rt_err_t result;
    static rt_uint8_t sum = 0;
    rt_thread_mdelay(10);           //�ȴ�FINSH��ʼ�����
    while(1)
    {
        /* ͨ�����õȴ��ķ�ʽ��ȡ�ź�������ȡ������ִ��sum++�Ĳ���*/
        result = rt_sem_take(dynamic_sem, RT_WAITING_FOREVER);

        if(result == RT_EOK)    //��ȡ�ź����ɹ�
        {
            sum++;
            rt_kprintf("\n get_semaphore_thread_entry take a semaphore. sum semaphore = %d \n", sum);
        }
    }
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      �̴����Լ�����
//  @param      void
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
int semaphore_example(void)
{
    //�����ź���
    dynamic_sem = rt_sem_create("dynamic_semaphore", 0 ,RT_IPC_FLAG_FIFO);

    //�߳̿��ƿ�ָ��
    rt_thread_t tid;
    //������̬�߳�
    tid = rt_thread_create(
            "release_semaphore",            //�߳�����
            release_semaphore_thread_entry, //�߳���ں���
            RT_NULL,                        //�̲߳���
            512,                            //ջ�ռ��С
            4,                              //�����߳����ȼ�����ֵԽС�����ȼ�Խ�ߣ�0Ϊ������ȼ���
                                            //����ͨ���޸�rt_config.h�е�RT_THREAD_PRIORITY_MAX�궨��(Ĭ��ֵΪ8)���޸����֧�ֵ����ȼ�
            10);                            //ʱ��Ƭ

    if(tid != RT_NULL)                      //�̴߳����ɹ�
    {
        rt_thread_startup(tid);             //���и��߳�
    }

    tid = rt_thread_create(
            "get_semaphore",                //�߳�����
            get_semaphore_thread_entry,     //�߳���ں���
            RT_NULL,                        //�̲߳���
            512,                           //ջ�ռ��С
            3,                              //�����߳����ȼ�����ֵԽС�����ȼ�Խ�ߣ�0Ϊ������ȼ���
                                            //����ͨ���޸�rt_config.h�е�RT_THREAD_PRIORITY_MAX�궨��(Ĭ��ֵΪ8)���޸����֧�ֵ����ȼ�
            10);                            //ʱ��Ƭ

    if(tid != RT_NULL)                      //�̴߳����ɹ�
    {
        rt_thread_startup(tid);             //���и��߳�
    }


    return 0;
}


//ʹ��INIT_APP_EXPORT���Զ���ʼ����Ҳ����ͨ���������߳��ڵ���semaphore_example�������г�ʼ��
INIT_APP_EXPORT(semaphore_example);      //Ӧ�ó�ʼ��

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



